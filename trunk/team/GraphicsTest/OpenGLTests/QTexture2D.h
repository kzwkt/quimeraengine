
#ifndef __QTEXTURE2D__
#define __QTEXTURE2D__

#include "GL/glew.h"

#include "QAbstractTexture2D.h"
#include "QSampler2D.h"
#include "QPixelFormatDescriptor.h"
#include "ErrorTracingDefinitions.h"


class QTexture2D : public QAbstractTexture2D
{
public:

    enum EQTextureMapping
    {
        E_UV,
        E_Spherical,
        E_Cylindrical,
        E_Cubic,
        E_Planar
    };
    
    QTexture2D(const GLuint textureId, const GLenum type, const GLenum format, const EQTextureFormat::EnumType eFormat, const u32_q uWidth, const u32_q uHeight, const u8_q uMipmapLevels, const u8_q uMultisamplingSamples) :
                                                                                                                            m_textureId(textureId),
                                                                                                                            m_type(type),
                                                                                                                            m_format(format)
    {
        m_eFormat = eFormat;
        m_uWidth = uWidth;
        m_uHeight = uHeight;
        m_uMipmapLevels = uMipmapLevels;
        m_uSamples = uMultisamplingSamples;

        //glGenerateTextureMipmap(m_textureId);
    }

    virtual void GetSubtexture( const i32_q nXOffset,
                                const i32_q nYOffset,
                                const u32_q uWidth,
                                const u32_q uHeight,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(nXOffset + uWidth > m_uWidth, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(nYOffset + uHeight > m_uHeight, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(m_uSamples == 0, "Reading a region of a multisample texture is not supported.");
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(scast_q(m_eFormat, EQPixelFormat::EnumType));

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * uWidth * uHeight;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        static const GLint FIRST_SLICE = 0;
        static const GLsizei NUM_SLICES = 1;
        glGetTextureSubImage(m_textureId, uMipmapLevel, nXOffset, nYOffset, FIRST_SLICE, uWidth, uHeight, NUM_SLICES, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

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
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth * m_uHeight;
            uFinalSubtextureSize *= m_uSamples > 0 ? m_uSamples : 1U;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureImage(m_textureId, uMipmapLevel, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    // COPY full and region

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture)
    {
        glTextureSubImage2D(m_textureId, uMipmapLevel, 0, 0, m_uWidth, m_uHeight, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtexture(const i32_q nXOffset, const i32_q nYOffset, const u32_q uWidth, const u32_q uHeight, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nXOffset + uWidth > m_uWidth, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nYOffset + uHeight > m_uHeight, "The region to be written overwrites memory outside the texture's dimensions.");

        glTextureSubImage2D(m_textureId, uMipmapLevel, nXOffset, nYOffset, uWidth, uHeight, m_format, m_type, pSubtexture);

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

#endif // __QTEXTURE2D__
