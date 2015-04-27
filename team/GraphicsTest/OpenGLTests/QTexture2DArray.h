
#ifndef __QTEXTURE2DARRAY__
#define __QTEXTURE2DARRAY__

#include "GL/glew.h"

#include "QAbstractTexture2DArray.h"
#include "QPixelFormatDescriptor.h"
#include "ErrorTracingDefinitions.h"


class QTexture2DArray : public QAbstractTexture2DArray
{
public:

    QTexture2DArray(const GLuint textureId, const GLenum type, const GLenum format, const EQTextureFormat::EnumType eFormat, const u32_q uWidth, const u32_q uHeight, const u32_q uSlices, const u8_q uMipmapLevels, const u8_q uMultisamplingSamples) :
                                                                                                    m_textureId(textureId),
                                                                                                    m_type(type),
                                                                                                    m_format(format)
    {
        m_eFormat = eFormat;
        m_uWidth = uWidth;
        m_uHeight = uHeight;
        m_uSlices = uSlices;
        m_uMipmapLevels = uMipmapLevels;
        m_uSamples = uMultisamplingSamples;
    }

    virtual void GetSubtexture(const i32_q nXOffset, 
                               const i32_q nYOffset, 
                               const i32_q nFirstSlice, 
                               const u32_q uWidth, 
                               const u32_q uHeight, 
                               const u32_q uSlices, 
                               const u8_q uMipmapLevel, 
                               const u32_q uSubtextureSize, 
                               void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(nXOffset + uWidth > m_uWidth, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(nYOffset + uHeight > m_uHeight, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(m_uSamples == 0, "Reading a region of a multisample texture is not supported.");
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(scast_q(m_eFormat, EQPixelFormat::EnumType));

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * uWidth * uHeight * uSlices;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureSubImage(m_textureId, uMipmapLevel, nXOffset, nYOffset, nFirstSlice, uWidth, uHeight, uSlices, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(scast_q(m_eFormat, EQPixelFormat::EnumType));

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth * m_uHeight * m_uSlices;
            uFinalSubtextureSize *= m_uSamples > 0 ? m_uSamples : 1U;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureImage(m_textureId, uMipmapLevel, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    // COPY full and region

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture)
    {
        glTextureSubImage3D(m_textureId, uMipmapLevel, 0, 0, 0, m_uWidth, m_uHeight, m_uSlices, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtexture(const i32_q nXOffset, const i32_q nYOffset, const i32_q nFirstSlice, const u32_q uWidth, const u32_q uHeight, const u32_q uSlices, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nXOffset + uWidth > m_uWidth, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nYOffset + uHeight > m_uHeight, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be written overwrites memory outside the texture's dimensions.");

        glTextureSubImage3D(m_textureId, uMipmapLevel, nXOffset, nYOffset, nFirstSlice, uWidth, uHeight, uSlices, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    // glInvalidate image, texsubimage, framebuffer, subframebuffer -----> No equivalent in DirectX


    GLuint GetExternalId() const
    {
        return m_textureId;
    }

protected:

    GLuint m_textureId;
    GLenum m_format;
    GLenum m_type;
};

#endif // __QTEXTURE2DARRAY__
