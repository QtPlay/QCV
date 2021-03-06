#include "imageoperaparam.h"

namespace onechchy {
    ImageOperaParam::ImageOperaParam(QObject *parent) : QObject(parent)
    {

    }

    ImageOperaParam::~ImageOperaParam()
    {

    }

    int ImageOperaParam::trimType() const
    {
        return mParam.trimParam.trimType;
    }

    void ImageOperaParam::setTrimType(int trimType)
    {
        mParam.trimParam.trimType = trimType;
    }

    int ImageOperaParam::trimBorder() const
    {
        return mParam.trimParam.trimBorder;
    }

    void ImageOperaParam::setTrimBorder(int trimBorder)
    {
        mParam.trimParam.trimBorder = trimBorder;
    }

    QColor ImageOperaParam::bgColor() const
    {
        return mParam.trimParam.bgColor;
    }

    void ImageOperaParam::setBgColor(QColor bgColor)
    {
        mParam.trimParam.bgColor = bgColor;
    }
    
    int ImageOperaParam::clusterCount() const
    {
        return mParam.splitParam.clusterCount;
    }
    
    void ImageOperaParam::setClusterCount(int clusterCount)
    {
        mParam.splitParam.clusterCount = clusterCount;
    }
    
    int ImageOperaParam::imageSplitType() const
    {
        return mParam.splitParam.imageSplitType;
    }
    
    void ImageOperaParam::setImageSplitType(int imageSplitType)
    {
        mParam.splitParam.imageSplitType = imageSplitType;
    }
    
    QString ImageOperaParam::selectPath() const
    {
        return mParam.saveParam.selectPath;
    }
    
    void ImageOperaParam::setSelectPath(const QString &selectPath)
    {
        mParam.saveParam.selectPath = selectPath;
    }

    int ImageOperaParam::gbMethod() const
    {
        return mParam.commonParam.intOne;
    }

    void ImageOperaParam::setGBMethod(const int method)
    {
        mParam.commonParam.intOne = method;
    }

    int ImageOperaParam::gbParam() const
    {
        return mParam.commonParam.intTwo;
    }

    void ImageOperaParam::setGBParam(const int param)
    {
        mParam.commonParam.intTwo = param;
    }

    int ImageOperaParam::rotateMethod() const
    {
        return mParam.rotateParam.rotateType;
    }

    void ImageOperaParam::setRotateMethod(const int method)
    {
        mParam.rotateParam.rotateType = method;
    }

    int ImageOperaParam::rotateParam() const
    {
        return mParam.rotateParam.rotateAngle;
    }

    void ImageOperaParam::setRotateParam(const int param)
    {
        mParam.rotateParam.rotateAngle = param;
    }
}
