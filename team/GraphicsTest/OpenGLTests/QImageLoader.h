
#ifndef __QIMAGELOADER__
#define __QIMAGELOADER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "QImage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class QImageLoader
{
public:

    virtual QImage* LoadImage(const void* pImageBuffer, const pointer_uint_q uBufferSize, const QImage::EQImageColorComponents eColorComponents)
    {
        i32_q nWidth = -1;
        i32_q nHeight = -1;
        stbi_uc* pLoadedImage = this->_LoadImageWithStb((u8_q*)pImageBuffer, uBufferSize, eColorComponents, nWidth, nHeight);

        QE_ASSERT_ERROR(pLoadedImage != null_q, string_q("An error occurred when loading the image."));

        QImage* pNewImage = new QImage(pLoadedImage, QPath("LoadedFromMemory"), eColorComponents, scast_q(nWidth, unsigned int), scast_q(nHeight, unsigned int));

        return pNewImage;
    }

    virtual QImage* LoadImage(const QPath &imagePath, const QImage::EQImageColorComponents eColorComponents)
    {
        EQFileSystemError eErrorInfo = EQFileSystemError::E_Unknown;
        EQFileSystemError eGetSizeErrorInfo = EQFileSystemError::E_Unknown;

        QFileStream fs(imagePath, EQFileOpenMode::E_Open, SQFile::GetFileInfo(imagePath, eGetSizeErrorInfo).GetSize(), eErrorInfo);
        QBinaryStreamReader<QFileStream> bs(fs);
        stbi_uc* pImageFile = new stbi_uc[fs.GetLength()];
        bs.ReadBytes(pImageFile, fs.GetLength());

        i32_q nWidth = -1;
        i32_q nHeight = -1;
        stbi_uc* pLoadedImage = this->_LoadImageWithStb(pImageFile, fs.GetLength(), eColorComponents, nWidth, nHeight);

        QImage* pNewImage = null_q;
        
        if(pLoadedImage)
            pNewImage = new QImage(pLoadedImage, imagePath, eColorComponents, scast_q(nWidth, unsigned int), scast_q(nHeight, unsigned int));

        return pNewImage;
    }

protected:

    static stbi_uc* _LoadImageWithStb(u8_q* pImageBuffer, const pointer_uint_q uBufferSize, QImage::EQImageColorComponents eColorComponents, i32_q &nWidth, i32_q &nHeight)
    {
        int nComponents = 0;
        stbi_uc* pImage = null_q;
        int nExpectedComponents = eColorComponents == QImage::E_RGB ? STBI_rgb :
            eColorComponents == QImage::E_RGBA ? STBI_rgb_alpha :
            0;

        pImage = stbi_load_from_memory(pImageBuffer, uBufferSize, &nWidth, &nHeight, &nComponents, nExpectedComponents);

        return pImage;
    }
};

#endif // __QIMAGELOADER__