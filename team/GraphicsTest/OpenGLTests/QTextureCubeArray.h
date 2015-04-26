#ifndef __QTEXTURECUBEARRAY__
#define __QTEXTURECUBEARRAY__

#include "QAbstractTextureCubeArray.h"

#include <GL/glew.h>
#include "QPixelFormatDescriptor.h"
#include "ErrorTracingDefinitions.h"

// Every slice is a cube face, so there's a cube every 6 slices. Z offset == face-slice, depth == num faces-slices
class QTextureCubeArray : public QAbstractTextureCubeArray
{
public:

    QTextureCubeArray(const GLuint textureId, const GLenum type, const GLenum format, const EQTextureFormat::EnumType eFormat, const u32_q uWidth, const u32_q uHeight, const u32_q uSlices, const u8_q uMipmapLevels) :
                                                                                                            m_textureId(textureId),
                                                                                                            m_type(type),
                                                                                                            m_format(format)
    {
        m_eFormat = eFormat;
        m_uWidth = uWidth;
        m_uHeight = uHeight;
        m_uMipmapLevels = uMipmapLevels;
        m_uSlices = uSlices;
    }

    virtual void GetSubtextureByFace( const i32_q nXOffset,
                                      const i32_q nYOffset,
                                      const i32_q nFirstSlice,
                                      const QAbstractTextureCubeArray::EQCubeMapFace eFace,
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
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;
        QPixelFormatDescriptor pixelFormatDescriptor(m_eFormat);

        if (ppOutputSubtexture == null_q)
        {
            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * uWidth * uHeight * uSlices * 6U;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        static const GLsizei DEPTH = 1;
        static const u32_q CUBE_SIZE = pixelFormatDescriptor.GetSize() * uWidth * uHeight * 6U;
        static const u32_q CUBE_FACE_SIZE = pixelFormatDescriptor.GetSize() * uWidth * uHeight;
        void** ppSlice = ppOutputSubtexture;
        GLint nCubeFaceSliceInArray = 0;

        // Gets the same face from every slice and copies it sequentially into output data
        for (u32_q i = nFirstSlice; i < uSlices; ++i)
        {
            nCubeFaceSliceInArray = i * 6U + eFace;
            glGetTextureSubImage(m_textureId, uMipmapLevel, nXOffset, nYOffset, nCubeFaceSliceInArray, uWidth, uHeight, DEPTH, m_format, m_type, CUBE_FACE_SIZE, *ppSlice);
            *ppSlice = void*(pointer_uint_q(*ppSlice) + CUBE_SIZE);
        }

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void GetSubtextureBySlice(  const i32_q nFirstSlice,
                                        const u32_q uSlices,
                                        const u8_q uMipmapLevel,
                                        const u32_q uSubtextureSize,
                                        void** ppOutputSubtexture) const
    {
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be read lays outside the texture's dimensions.");
        QE_ASSERT_ERROR(ppOutputSubtexture != null_q, "The output subtexture cannot be null.");

        u32_q uFinalSubtextureSize = uSubtextureSize;
        QPixelFormatDescriptor pixelFormatDescriptor(m_eFormat);

        if (ppOutputSubtexture == null_q)
        {
            // Allocate memory
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth * m_uHeight * uSlices * 6U;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        static const GLint OFFSETX = 0;
        static const GLint OFFSETY = 0;
        glGetTextureSubImage(m_textureId, uMipmapLevel, OFFSETX, OFFSETY, nFirstSlice * 6U, m_uWidth, m_uHeight, uSlices * 6U, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

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
            uFinalSubtextureSize = pixelFormatDescriptor.GetSize() * m_uWidth * m_uHeight * m_uSlices * 6U;
            *ppOutputSubtexture = new u8_q[uFinalSubtextureSize];
        }

        glGetTextureImage(m_textureId, uMipmapLevel, m_format, m_type, uFinalSubtextureSize, *ppOutputSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    // COPY full and region

    virtual void SetFullContent(const u8_q uMipmapLevel, const void* pSubtexture)
    {
        glTextureSubImage3D(m_textureId, uMipmapLevel, 0, 0, 0, m_uWidth, m_uHeight, m_uSlices * 6U, m_format, m_type, pSubtexture);

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtextureByFace(const i32_q nXOffset, const i32_q nYOffset, const i32_q nFirstSlice, const QAbstractTextureCubeArray::EQCubeMapFace eFace, const u32_q uWidth, const u32_q uHeight, const u32_q uSlices, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nXOffset + uWidth > m_uWidth, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nYOffset + uHeight > m_uHeight, "The region to be written overwrites memory outside the texture's dimensions.");
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be written overwrites memory outside the texture's dimensions.");

        QPixelFormatDescriptor pixelFormatDescriptor(m_eFormat);
        static const GLsizei DEPTH = 1;
        static const u32_q CUBE_SIZE = pixelFormatDescriptor.GetSize() * uWidth * uHeight * 6U;
        const void* pSlice = pSubtexture;
        GLint nCubeFaceSliceInArray = 0;

        // The data is copied to the same face for every slice
        for (u32_q i = nFirstSlice; i < uSlices; ++i)
        {
            nCubeFaceSliceInArray = i * 6U + eFace;
            glTextureSubImage3D(m_textureId, uMipmapLevel, nXOffset, nYOffset, nCubeFaceSliceInArray, uWidth, uHeight, DEPTH, m_format, m_type, pSlice);
            pSlice = void*(pointer_uint_q(pSlice) + CUBE_SIZE);
        }

        QE_ASSERT_OPENGL_ERROR("An error occurred when writing to the texture.");
    }

    virtual void SetSubtextureBySlice(const i32_q nFirstSlice, const u32_q uSlices, const u8_q uMipmapLevel, const void* pSubtexture)
    {
        QE_ASSERT_ERROR(nFirstSlice + uSlices > m_uSlices, "The region to be written overwrites memory outside the texture's dimensions.");

        static const GLint OFFSETX = 0;
        static const GLint OFFSETY = 0;

        glTextureSubImage3D(m_textureId, uMipmapLevel, OFFSETX, OFFSETY, nFirstSlice * 6U, m_uWidth, m_uHeight, uSlices * 6U, m_format, m_type, pSubtexture);

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

#endif // __QTEXTURECUBEARRAY__