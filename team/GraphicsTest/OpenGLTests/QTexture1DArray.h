#ifndef __QTEXTURE1DARRAY__
#define __QTEXTURE1DARRAY__

#include "QAbstractTexture1DArray.h"
#include "QPixelFormatDescriptor.h"
#include "ErrorTracingDefinitions.h"
#include <GL/glew.h>

class QTexture1DArray : public QAbstractTexture1DArray
{
public:

    QTexture1DArray(const GLuint textureId, const GLenum type, const GLenum format, const EQPixelFormat::EnumType eFormat, const u32_q uWidth, const u32_q uSlices, const u8_q uMipmapLevels) :
                                                                                                m_textureId(textureId),
                                                                                                m_type(type),
                                                                                                m_format(format)
    {
        m_eFormat = eFormat;
        m_uWidth = uWidth;
        m_uSlices = uSlices;
        m_uMipmapLevels = uMipmapLevels;
    }

    virtual void GetSubtexture( const i32_q nOffset,
                                const i32_q nFirstSlice,
                                const u32_q uWidth,
                                const u32_q uSlices,
                                const u8_q uMipmapLevel,
                                const u32_q uSubtextureSize,
                                void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(nOffset + uWidth > m_uWidth, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(m_eFormat);

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * uWidth * uSlices;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        static const GLint OFFSETZ= 0;
        static const GLsizei DEPTH = 1;
        static const GLint FIRST_SLICE = 0;
        static const GLsizei NUM_SLICES = 1;
        glGetTextureSubImage(m_textureId, uMipmapLevel, nOffset, nFirstSlice, OFFSETZ, uWidth, uSlices, DEPTH, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void GetFullContent(const u8_q uMipmapLevel, const u32_q uSubtextureSize, void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;

        if (ppOutputSubtexture == null_q)
        {
            QPixelFormatDescriptor pixelFormatDescriptor(m_eFormat);

            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth * m_uSlices;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureImage(m_textureId, uMipmapLevel, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    // COPY full and region

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture)
    {
        glTextureSubImage2D(m_textureId, uMipmapLevel, 0, 0, m_uWidth, m_uSlices, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtexture(const i32_q nOffset, const i32_q nFirstSlice, const u32_q uWidth, const u32_q uSlices, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nOffset + uWidth > m_uWidth, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be written overwrites memory outside the texture's dimensions.");

        glTextureSubImage2D(m_textureId, uMipmapLevel, nOffset, nFirstSlice, uWidth, uSlices, m_format, m_type, pSubtexture);

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

#endif // __QTEXTURE1DARRAY__