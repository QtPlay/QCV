#include "partitiontrimborder.h"
#include "simageservice.h"
#include <QDebug>
#include <array>
#include <range/v3/core.hpp>
#include <range/v3/view.hpp>

namespace onechchy {

    PartitionTrimBorder::PartitionTrimBorder()
    {
        this->mcErodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    }

    cv::Mat PartitionTrimBorder::trimBorder(const cv::Mat &srcMat, int border, QColor bgColor)
    {
        cv::Mat mat;

        if (srcMat.channels() == 4)
        {
            cv::cvtColor(srcMat, mat, CV_BGRA2GRAY);
        }
        else if (srcMat.channels() == 3)
        {
            cv::cvtColor(srcMat, mat, CV_BGR2GRAY);
        }
        else if (srcMat.channels() == 1)
        {
            mat = srcMat;
        }
        else
        {
            return mat;
        }

        int halfWidth = srcMat.cols / 2;
        int halfHeight = srcMat.rows / 2;

        std::array<cv::Rect, 4> iarray = { cv::Rect{0, 0, halfWidth, halfHeight}, cv::Rect{halfWidth, 0, halfWidth, halfHeight}, cv::Rect{0, halfHeight, halfWidth, halfHeight}, cv::Rect{halfWidth, halfHeight, halfWidth, halfHeight}};
//        cv::Rect ltRect{0, 0, halfWidth, halfHeight};
//        cv::Rect rtRect{halfWidth, 0, halfWidth, halfHeight};
//        cv::Rect lbRect{0, halfHeight, halfWidth, halfHeight};
//        cv::Rect rbRect{halfWidth, halfHeight, halfWidth, halfHeight};
        std::array<cv::Point, 4> iPoint;

         cv::erode(mat, mat, mcErodeElement);

        #pragma omp parallel for
        for (int i = 0; i < 4; ++i)
        {
            cv::Mat tempMat = mat(iarray[i]);

            cv::Canny(tempMat, tempMat, 25, 50);

            if (this->leftTopPoint(tempMat, iPoint[i], i, bgColor)){}
            else if (this->rightTopPoint(tempMat, iPoint[i], i, bgColor)){}
            else if (this->leftBottomPoint(tempMat, iPoint[i], i, bgColor)){}
            else if (this->rightBottomPoint(tempMat, iPoint[i], i, bgColor));
        }

        cv::Rect trimRect;

        // left
        if (abs(iPoint[0].x - iPoint[2].x) < 5)
        {
            trimRect.x = iPoint[0].x > iPoint[2].x ? iPoint[0].x : iPoint[2].x;
        }
        else
        {
            trimRect.x = iPoint[0].x < iPoint[2].x ? iPoint[0].x : iPoint[2].x;
        }

        // top
        if (abs(iPoint[0].y - iPoint[1].y) < 5)
        {
            trimRect.y = iPoint[0].y > iPoint[1].y ? iPoint[0].y : iPoint[1].y;
        }
        else
        {
            trimRect.y = iPoint[0].y < iPoint[1].y ? iPoint[0].y : iPoint[1].y;
        }

        // bottom
        if (abs(iPoint[2].y - iPoint[3].y) < 5)
        {
            trimRect.height = (iPoint[2].y > iPoint[3].y ? iPoint[2].y : iPoint[3].y) - trimRect.y;
        }
        else
        {
            trimRect.height = (iPoint[2].y < iPoint[3].y ? iPoint[2].y : iPoint[3].y) - trimRect.y;
        }

        // right
        if (abs(iPoint[1].x - iPoint[3].x) < 5)
        {
            trimRect.width = (iPoint[1].x > iPoint[3].x ? iPoint[1].x : iPoint[3].x) - trimRect.x;
        }
        else
        {
            trimRect.width = (iPoint[1].x < iPoint[3].x ? iPoint[1].x : iPoint[3].x) - trimRect.x;
        }

        if (trimRect.width > 0 && trimRect.height > 0)
        {
            return srcMat(trimRect);
        }

        return srcMat;
    }

    bool PartitionTrimBorder::leftTopPoint(const cv::Mat mat, cv::Point &point, int flag, const QColor& bgColor)
    {
        if (flag != 0)
        {
            return false;
        }

        int width = mat.cols;
        int height = mat.rows;
        uchar* pData = mat.data;

        for (const auto& y : ranges::view::ints(0, height))
        {
            uchar* pCurLine = pData + y * width;
            for (const auto& x : ranges::view::ints(0, width))
            {
                if (pCurLine[x] > 0)
                {
                    qDebug() << "pCurLine[x]" << (int)(pCurLine[x]);
                    point.y = x;
                    break;
                }
            }
        }

        for (const auto& x : ranges::view::ints(0, width))
        {
            for (const auto& y : ranges::view::ints(0, height))
            {
                if (pData[y * width + x] > 0)
                {
                    point.x = y;
                    break;
                }
            }
        }

        return true;
    }

    bool PartitionTrimBorder::rightTopPoint(const cv::Mat mat, cv::Point &point, int flag, const QColor &bgColor)
    {
        if (flag != 1)
        {
            return false;
        }

        int width = mat.cols;
        int height = mat.rows;
        uchar* pData = mat.data;

        for (const auto& y : ranges::view::ints(0, height))
        {
            uchar* pCurLine = pData + y * width;
            for (const auto& x : ranges::view::ints(0, width) | ranges::view::reverse)
            {
                if (pCurLine[x] > 0)
                {
                    qDebug() << "pCurLine[x]" << (int)(pCurLine[x]);
                    point.y = x;
                    break;
                }
            }
        }

        for (const auto& x : ranges::view::ints(0, width) | ranges::view::reverse)
        {
            for (const auto& y : ranges::view::ints(0, height))
            {
                if (pData[y * width + x] > 0)
                {
                    point.x = y;
                    break;
                }
            }
        }

        return true;
    }

    bool PartitionTrimBorder::leftBottomPoint(const cv::Mat mat, cv::Point &point, int flag, const QColor &bgColor)
    {
        if (flag != 2)
        {
            return false;
        }

        int width = mat.cols;
        int height = mat.rows;
        uchar* pData = mat.data;

        for (const auto& y : ranges::view::ints(0, height) | ranges::view::reverse)
        {
            uchar* pCurLine = pData + y * width;
            for (const auto& x : ranges::view::ints(0, width))
            {
                if (pCurLine[x] > 0)
                {
                    qDebug() << "pCurLine[x]" << (int)(pCurLine[x]);
                    point.y = x;
                    break;
                }
            }
        }

        for (const auto& x : ranges::view::ints(0, width))
        {
            for (const auto& y : ranges::view::ints(0, height) | ranges::view::reverse)
            {
                if (pData[y * width + x] > 0)
                {
                    point.x = y;
                    break;
                }
            }
        }

        return true;
    }

    bool PartitionTrimBorder::rightBottomPoint(const cv::Mat mat, cv::Point &point, int flag, const QColor &bgColor)
    {
        if (flag != 3)
        {
            return false;
        }

        int width = mat.cols;
        int height = mat.rows;
        uchar* pData = mat.data;

        for (const auto& y : ranges::view::ints(0, height) | ranges::view::reverse)
        {
            uchar* pCurLine = pData + y * width;
            for (const auto& x : ranges::view::ints(0, width) | ranges::view::reverse)
            {
                if (pCurLine[x] > 0)
                {
                    qDebug() << "pCurLine[x]" << (int)(pCurLine[x]);
                    point.y = x;
                    break;
                }
            }
        }

        for (const auto& x : ranges::view::ints(0, width) | ranges::view::reverse)
        {
            for (const auto& y : ranges::view::ints(0, height) | ranges::view::reverse)
            {
                if (pData[y * width + x] > 0)
                {
                    point.x = y;
                    break;
                }
            }
        }

        return true;
    }

}
