
#ifndef __QTEXTURE1D__
#define __QTEXTURE1D__

#include "QAbstractTexture1D.h"

#include <GL/glew.h>
#include "QPixelFormatDescriptor.h"


class QTexture1D : public QAbstractTexture1D
{
public:

    QTexture1D(const GLuint textureId, const GLenum type, const GLenum format, const EQTextureFormat::EnumType eFormat, const u32_q uWidth, const u8_q uMipmapLevels) :
                                                                                                                                        m_textureId(textureId),
                                                                                                                                        m_type(type),
                                                                                                                                        m_format(format)
    {
        m_eFormat = eFormat;
        m_uWidth = uWidth;
        m_uMipmapLevels = uMipmapLevels;

        //glGenerateTextureMipmap(m_textureId);
    }

    virtual void GetSubtexture( const i32_q nOffset,
                                const u32_q uWidth,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(nOffset + uWidth > m_uWidth, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(scast_q(m_eFormat, EQPixelFormat::EnumType));

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * uWidth;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        static const GLint OFFSETY = 0;
        static const GLsizei HEIGHT = 1;
        static const GLint FIRST_SLICE = 0;
        static const GLsizei NUM_SLICES = 1;
        glGetTextureSubImage(m_textureId, uMipmapLevel, nOffset, OFFSETY, FIRST_SLICE, uWidth, HEIGHT, NUM_SLICES, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

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
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureImage(m_textureId, uMipmapLevel, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture)
    {
        glTextureSubImage1D(m_textureId, uMipmapLevel, 0, m_uWidth, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtexture(const i32_q nOffset, const u32_q uWidth, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nOffset + uWidth > m_uWidth, "The region to be written overwrites memory outside the texture's dimensions.");

        glTextureSubImage1D(m_textureId, uMipmapLevel, nOffset, uWidth, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    GLuint GetExternalId() const
    {
        return m_textureId;
    }

protected:

    GLuint m_textureId;
    GLenum m_format;
    GLenum m_type;
};

#endif // __QTEXTURE1D__