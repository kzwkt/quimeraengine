
#ifndef __QRENDERBUFFER__
#define __QRENDERBUFFER__

#include "QuimeraEngineIncludesAndUsings.h"
#include "EQPixelFormat.h"
#include <GL/glew.h>

class QRenderbuffer
{
public:

    enum EQRenderbufferPixelFormat
    {
        E_R8UI_Normalized,
        E_R16UI_Normalized,
        E_RG8UI_Normalized,
        E_RG16UI_Normalized,
        E_R3G3B2UI_Normalized,
        E_RGB4UI_Normalized,
        E_RGB5UI_Normalized,
        E_RGB8UI_Normalized,
        E_RGB10UI_Normalized,
        E_RGB12UI_Normalized,
        E_RGB16UI_Normalized,
        E_RGBA2UI_Normalized,
        E_RGBA4UI_Normalized,
        E_RGB5A1UI_Normalized,
        E_RGBA8UI_Normalized,
        E_RGB10A2UI_Normalized,
        E_RGBA12UI_Normalized,
        E_RGBA16UI_Normalized,
        E_SRGB8_Compressed,
        E_SRGB8A8_Compressed,
        E_R16F,
        E_R32F,
        E_RG16F,
        E_RG32F,
        E_RGB16F,
        E_RGB32F,
        E_RGBA16F,
        E_RGBA32F,
        E_R11FG11FB10F,
        E_RGB9E5,
        E_R8I,
        E_R8UI,
        E_R16I,
        E_R16UI,
        E_R32I,
        E_R32UI,
        E_RG8I,
        E_RG8UI,
        E_RG16I,
        E_RG16UI,
        E_RG32I,
        E_RG32UI,
        E_RGB8I,
        E_RGB8UI,
        E_RGB16I,
        E_RGB16UI,
        E_RGB32I,
        E_RGB32UI,
        E_RGBA8I,
        E_RGBA8UI,
        E_RGBA16I,
        E_RGBA16UI,
        E_RGBA32I,
        E_RGBA32UI,
        E_R8I_Normalized,
        E_R16I_Normalized,
        E_RG8I_Normalized,
        E_RG16I_Normalized,
        E_RGB8I_Normalized,
        E_RGB16I_Normalized,
        E_RGBA8I_Normalized,
        E_RGBA16I_Normalized,
        E_D16 = 80, // Color buffer formats will match texture formats, wich are a superset of these, and the enum is used to access a preloaded equivalency array, so some slots must be reserved from last value to the # 80
        E_D24,
        E_D32,
        E_D32F,
        E_S1 = 90,
        E_S4,
        E_S8,
        E_S16,
        E_D24S8 = 100,
        E_D32FS8
    };

    enum EQRenderbufferType
    {
        E_Color,
        E_Depth,
        E_Stencil,
        E_DepthAndStencil
    };


    QRenderbuffer(const GLuint renderbufferId, const GLenum attachment, const GLenum format, const EQRenderbufferPixelFormat ePixelFormat, const EQRenderbufferType eType) : 
                                                                                                                                                                       m_renderbufferId(renderbufferId),
                                                                                                                                                                       m_attachment(attachment),
                                                                                                                                                                       m_pixelFormat(format),
                                                                                                                                                                       m_ePixelFormat(ePixelFormat),
                                                                                                                                                                       m_eType(eType)
    {
    }

    u32_q GetWidth() const
    {
        return m_uWidth;
    }

    void SetWidth(const u32_q uWidth)
    {
        m_uWidth = uWidth;
    }

    u32_q GetHeight() const
    {
        return m_uHeight;
    }

    void SetHeight(const u32_q uHeight)
    {
        m_uHeight = uHeight;
    }

    EQRenderbufferPixelFormat GetPixelFormat() const
    {
        return m_ePixelFormat;
    }

    void SetPixelFormat(const EQRenderbufferPixelFormat ePixelFormat)
    {
        m_ePixelFormat = ePixelFormat;
    }

    GLuint GetExternalId() const
    {
        return m_renderbufferId;
    }

    GLenum GetExternalAttachment() const
    {
        return m_attachment;
    }

    GLenum GetExternalFormat() const
    {
        return m_pixelFormat;
    }

protected:

    GLuint m_renderbufferId;
    GLenum m_attachment;
    GLenum m_pixelFormat;

    u32_q m_uWidth;
    u32_q m_uHeight;
    EQRenderbufferPixelFormat m_ePixelFormat;
    EQRenderbufferType m_eType;
};

#endif // __QRENDERBUFFER__