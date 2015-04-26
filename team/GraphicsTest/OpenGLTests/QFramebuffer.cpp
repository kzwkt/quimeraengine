
#include "QFramebuffer.h"

#include "QuimeraEngine.h"
#include "QTexture1D.h"
#include "QTexture2D.h"
#include "QTexture3D.h"

QFramebuffer::QRenderTarget QFramebuffer::GetColorBufferId(const u32_q uIndex) const
{
    return m_arColorBuffers[uIndex];
}

void QFramebuffer::SetColorBuffer(const u32_q uColorBufferIndex, const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel, const u32_q uLayer)
{
    QE_ASSERT_ERROR(uColorBufferIndex < GL_MAX_COLOR_ATTACHMENTS, "The input index is out of bounds.");
    QE_ASSERT_ERROR(eType != QFramebuffer::E_Texture2DMultisample || uMipmapLevel == 0, "The mipmap level cannot be greater than zero when using a multisample texture.");

    QFramebuffer::_SetBuffer(m_framebufferId, strId, GL_COLOR_ATTACHMENT0 + uColorBufferIndex, eType, uMipmapLevel, uLayer);

    m_arColorBuffers[uColorBufferIndex].Id = strId;
    m_arColorBuffers[uColorBufferIndex].Type = eType;
    m_arColorBufferStates[uColorBufferIndex] = true;
}

void QFramebuffer::RemoveColorBuffer(const u32_q uColorBufferIndex)
{
    QE_ASSERT_WARNING(m_arColorBufferStates[uColorBufferIndex], "No color buffer is attached to the slot of the framebuffer.");
    QE_ASSERT_ERROR(uColorBufferIndex < GL_MAX_COLOR_ATTACHMENTS, "The input index is out of bounds.");

    QFramebuffer::_RemoveBuffer(m_framebufferId, GL_COLOR_ATTACHMENT0 + uColorBufferIndex, m_arColorBuffers[uColorBufferIndex].Type);

    m_arColorBufferStates[uColorBufferIndex] = false;
}

void QFramebuffer::SetDepthBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel, const u32_q uLayer)
{
    QE_ASSERT_ERROR(eType != QFramebuffer::E_Texture2DMultisample || uMipmapLevel == 0, "The mipmap level cannot be greater than zero when using a multisample texture.");

    QFramebuffer::_SetBuffer(m_framebufferId, strId, GL_DEPTH_ATTACHMENT, eType, uMipmapLevel, uLayer);

    m_depthBuffer.Id = strId;
    m_depthBuffer.Type = eType;
    m_bDepthBufferState = true;
}

void QFramebuffer::RemoveDepthBuffer()
{
    QE_ASSERT_WARNING(m_bDepthBufferState, "No depth buffer is attached to the framebuffer.");

    QFramebuffer::_RemoveBuffer(m_framebufferId, GL_DEPTH_ATTACHMENT, m_depthBuffer.Type);

    m_bDepthBufferState = false;
}

QFramebuffer::QRenderTarget QFramebuffer::GetDepthBuffer() const
{
    return m_depthBuffer;
}

void QFramebuffer::SetStencilBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel, const u32_q uLayer)
{
    QE_ASSERT_ERROR(eType != QFramebuffer::E_Texture2DMultisample || uMipmapLevel == 0, "The mipmap level cannot be greater than zero when using a multisample texture.");

    QFramebuffer::_SetBuffer(m_framebufferId, strId, GL_STENCIL_ATTACHMENT, eType, uMipmapLevel, uLayer);

    m_stencilBuffer.Id = strId;
    m_stencilBuffer.Type = eType;
    m_bStencilBufferState = true;
}

void QFramebuffer::RemoveStencilBuffer()
{
    QE_ASSERT_WARNING(m_bStencilBufferState, "No stencil buffer is attached to the framebuffer.");

    QFramebuffer::_RemoveBuffer(m_framebufferId, GL_STENCIL_ATTACHMENT, m_stencilBuffer.Type);

    m_bStencilBufferState = false;
}

QFramebuffer::QRenderTarget QFramebuffer::GetStencilBuffer() const
{
    return m_stencilBuffer;
}

void QFramebuffer::SetDepthStencilBuffer(const QHashedString &strId, const QFramebuffer::EQRenderTargetType eType, const u32_q uMipmapLevel, const u32_q uLayer)
{
    QE_ASSERT_ERROR(eType != QFramebuffer::E_Texture2DMultisample || uMipmapLevel == 0, "The mipmap level cannot be greater than zero when using a multisample texture.");

    QFramebuffer::_SetBuffer(m_framebufferId, strId, GL_DEPTH_STENCIL_ATTACHMENT, eType, uMipmapLevel, uLayer);

    m_depthStencilBuffer.Id = strId;
    m_depthStencilBuffer.Type = eType;
    m_bDepthStencilBufferState = true;
}

void QFramebuffer::RemoveDepthStencilBuffer()
{
    QE_ASSERT_WARNING(m_bDepthStencilBufferState, "No depth-stencil buffer is attached to the framebuffer.");

    QFramebuffer::_RemoveBuffer(m_framebufferId, GL_DEPTH_STENCIL_ATTACHMENT, m_depthStencilBuffer.Type);

    m_bDepthStencilBufferState = false;
}

QFramebuffer::QRenderTarget QFramebuffer::GetDepthStencilBuffer() const
{
    return m_depthStencilBuffer;
}


GLuint QFramebuffer::GetExternalId() const
{
    return m_framebufferId;
}

GLenum QFramebuffer::_GetEquivalentRenderbufferTargetOpenGLValue(const QFramebuffer::EQRenderbufferOperation eTarget)
{
    static const GLenum EQUIVALENT_VALUES[] = {
                                                GL_READ_FRAMEBUFFER,
                                                GL_DRAW_FRAMEBUFFER
                                            };
    return EQUIVALENT_VALUES[eTarget];
}

void QFramebuffer::_SetBuffer(const GLuint framebufferId, const QHashedString &strRenderTargetId, const GLenum attachment, const QFramebuffer::EQRenderTargetType eRenderTargetType, const u32_q uMipmapLevel, const u32_q uLayer)
{
    if (eRenderTargetType == QFramebuffer::E_Renderbuffer)
    {
        QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strRenderTargetId);
        glNamedFramebufferRenderbuffer(framebufferId, attachment, GL_RENDERBUFFER, pRenderbuffer->GetExternalId());
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture1D)
    {
        QTexture1D* pTexture = QE->Resources->GetTexture1D(strRenderTargetId);
        glNamedFramebufferTexture1DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), pTexture->GetExternalId(), uMipmapLevel);
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture2D                ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveX ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeX ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveY ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeY ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveZ ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeZ ||
             eRenderTargetType == QFramebuffer::E_Texture2DMultisample)
    {
        QTexture2D* pTexture = QE->Resources->GetTexture2D(strRenderTargetId);
        glNamedFramebufferTexture2DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), pTexture->GetExternalId(), uMipmapLevel);
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture3D)
    {
        QTexture3D* pTexture = QE->Resources->GetTexture3D(strRenderTargetId);
        glNamedFramebufferTexture3DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), pTexture->GetExternalId(), uMipmapLevel, uLayer);
    }

    QE_ASSERT_OPENGL_ERROR("An error occurred when setting the attachment.");
}

void QFramebuffer::_RemoveBuffer(GLuint framebufferId, const GLenum attachment, const EQRenderTargetType eRenderTargetType)
{
    if (eRenderTargetType == QFramebuffer::E_Renderbuffer)
    {
        glNamedFramebufferRenderbuffer(framebufferId, attachment, GL_RENDERBUFFER, 0);
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture1D)
    {
        glNamedFramebufferTexture1DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), 0, 0);
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture2D                ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveX ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeX ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveY ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeY ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFacePositiveZ ||
             eRenderTargetType == QFramebuffer::E_TextureCubeFaceNegativeZ ||
             eRenderTargetType == QFramebuffer::E_Texture2DMultisample)
    {
        glNamedFramebufferTexture2DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), 0, 0);
    }
    else if (eRenderTargetType == QFramebuffer::E_Texture3D)
    {
        glNamedFramebufferTexture3DEXT(framebufferId, attachment, QFramebuffer::_ConvertRenderTargetTypeToTextureTarget(eRenderTargetType), 0, 0, 0);
    }

    QE_ASSERT_OPENGL_ERROR("An error occurred when removing the attachment.");
}
