
#ifndef __QIMAGELOADER__
#define __QIMAGELOADER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QImage.h"

class QImageLoader
{
public:

    virtual QImage* LoadImage(const void* pImageBuffer, const pointer_uint_q uBufferSize, const QImage::EQImageColorComponents eColorComponents);

    virtual QImage* LoadImage(const QPath &imagePath, const QImage::EQImageColorComponents eColorComponents);

protected:

    static u8_q* _LoadImageWithStb(u8_q* pImageBuffer, const pointer_uint_q uBufferSize, QImage::EQImageColorComponents eColorComponents, i32_q &nWidth, i32_q &nHeight);
};

#endif // __QIMAGELOADER__