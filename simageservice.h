#ifndef SIMAGESERVICE_H
#define SIMAGESERVICE_H

#include <QObject>
#include <memory>
#include <QString>
#include <QImage>
#include <QStack>
#include "imageoperaparam.h"

namespace onechchy {
    class SImage;
    class TransformImage;
//    class ImageOperaParam;

    class SImageService : public QObject
    {
        Q_OBJECT
        Q_ENUMS(ImageOpera)
        Q_ENUMS(Border)
        Q_ENUMS(TrimType)
        Q_ENUMS(ImageSplitType)
        Q_ENUMS(GBMethodType)
        Q_ENUMS(RotateType)

        Q_PROPERTY(ImageOperaParam *operaParam READ operaParam WRITE setOperaParam)

    public:
        explicit SImageService(QObject *parent = nullptr);

        enum class ImageOpera
        {
            Rotate = 0,
            TrimBorder = 1,
            ImageSplit = 2,
            Save = 3,
            GrayBinary = 4,
        };

        enum Border{
            Left = 0x01,
            Top = 0x02,
            Right = 0x04,
            Bottom = 0x08
        };

        enum class TrimType{
            Simple = 0x10,
            Count = 0x20,
            Map = 0x40,
            BoundMat = 1,
            SimpleCanny = 2,
            SCannyErode = 3,
            SCannyEroDil = 4,
            PartitionSCanny = 5,
        };

        enum ImageSplitType{
            KMeans = 0x01,
            GMM = 0x02,
            Watershed = 0x04,
            GrabCut = 0x08
        };

        enum class GBMethodType{
            GeneralGrayOpenCV = 1,
            GeneralGrayThird = 2,
            CustomBinaryOpenCV = 3,
            CustomBinaryThird = 4,
            OSTUOpenCV = 5,
            TriangleOpenCV = 6,
        };

        enum class RotateType{
            AutoRectifying,
            ManualRotate,
        };

        ImageOperaParam *operaParam() const;
        void setOperaParam(ImageOperaParam *operaParam);

        Q_INVOKABLE void undo();
        Q_INVOKABLE void redo();

    signals:
        void updateImg(QImage image);

    public slots:
        void sltImageOpera(ImageOpera opera, QImage image);

    private:
        std::unique_ptr<SImage> mpSImage = nullptr;
        // 这里申请为指针类型，是因为QObject不支持复制、赋值构造函数，而qml能够根据指针还是值来进行赋值
        ImageOperaParam* mOperaParam = nullptr;
        QStack<QImage> mUnDoImg;
        QStack<QImage> mReDoImg;
        QImage mCurImg;

        void rectifyingOpera(QImage& image);
        void trimBorderOpera(QImage& image);
        void imageSplitOpera(QImage& image);
        void saveImage(QImage& image);
        void grayBinary(QImage& image);
    };
}

#endif // SIMAGESERVICE_H
