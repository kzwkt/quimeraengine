
#ifndef __QFRAMEBUFFER__
#define __QFRAMEBUFFER__

#include "QuimeraEngineIncludesAndUsings.h"
#include <GL/glew.h>


class QFramebuffer
{
public:

    enum EQRenderbufferOperation
    {
        E_Read,
        E_Write
    };

    enum EQRenderTargetType
    {
        E_Renderbuffer,
        E_Texture1D,
        E_Texture2D,
        E_Texture3D,
        E_TextureCubeFacePositiveX,
        E_TextureCubeFaceNegativeX,
        E_TextureCubeFacePositiveY,
        E_TextureCubeFaceNegativeY,
        E_TextureCubeFacePositiveZ,
        E_TextureCubeFaceNegativeZ,
        E_Texture2DMultisample
    };

    struct QRenderTarget
    {
        QHashedString Id;
        EQRenderTargetType Type;
    };

public:

    QFramebuffer(const GLuint framebufferId) : m_framebufferId(framebufferId)
    {
        for (int i = 0; i < GL_MAX_COLOR_ATTACHMENTS; ++i)
            m_arColorBufferStates[i] = false;

        m_bDepthBufferState = false;
        m_bStencilBufferState = false;
        m_bDepthStencilBufferState = false;
    }

    QRenderTarget GetColorBuffer(const u32_q uIndex) const;

    void SetColorBuffer(const u32_q uColorBufferIndex, const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel = 0, const u32_q uLayer = 0);

    void RemoveColorBuffer(const u32_q uColorBufferIndex);

    void SetDepthBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel = 0, const u32_q uLayer = 0);

    void RemoveDepthBuffer();

    QRenderTarget GetDepthBuffer() const;

    void SetStencilBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel = 0, const u32_q uLayer = 0);

    void RemoveStencilBuffer();

    QRenderTarget GetStencilBuffer() const;

    void SetDepthStencilBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel = 0, const u32_q uLayer = 0);

    void RemoveDepthStencilBuffer();

    QRenderTarget GetDepthStencilBuffer() const;

    GLuint GetExternalId() const;
    
protected:

    static GLenum _GetEquivalentRenderbufferTargetOpenGLValue(const EQRenderbufferOperation eTarget);
    static pointer_uint_q _GetIndexOf(const QHashedString strElement, const QArrayDynamic<QRenderTarget> &arContainer);
    static void _SetRenderbuffer();
    static void _SetTexture1D();
    static void _SetTexture2D();
    static void _SetTextureCubeFace();
    static void _SetTexture3D();
    static void _SetBuffer(const GLuint framebufferId, const QHashedString &strRenderTargetId, const GLenum attachment, const EQRenderTargetType eRenderTargetType, const u32_q uMipmapLevel, const u32_q uLayer);
    static void _RemoveBuffer(GLuint framebufferId, const GLenum attachment, const EQRenderTargetType eRenderTargetType);

    static GLenum _ConvertRenderTargetTypeToTextureTarget(const u32_q eRenderTargetType)
    {
        static const GLenum EQUIVALENT_VALUES[] = { GL_RENDERBUFFER,
                                                    GL_TEXTURE_1D,
                                                    GL_TEXTURE_2D,
                                                    GL_TEXTURE_3D,
                                                    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                                    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                                    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                                    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                                    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                                    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                                                    GL_TEXTURE_2D_MULTISAMPLE
                                                };

        return EQUIVALENT_VALUES[eRenderTargetType];
    }

    QRenderTarget m_arColorBuffers[GL_MAX_COLOR_ATTACHMENTS];
    QRenderTarget m_depthBuffer;
    QRenderTarget m_depthStencilBuffer;
    QRenderTarget m_stencilBuffer;
    GLuint m_framebufferId;
    bool m_arColorBufferStates[GL_MAX_COLOR_ATTACHMENTS]; // Enabled / disabled
    bool m_bDepthBufferState;
    bool m_bDepthStencilBufferState;
    bool m_bStencilBufferState;
};


#endif // __QFRAMEBUFFER__