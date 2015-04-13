
#include "QFramebuffer.h"

#include "QuimeraEngine.h"


QHashedString QFramebuffer::GetColorBufferId(const u32_q uIndex) const
{
    return m_arColorBuffers[uIndex];
}

void QFramebuffer::AddColorBuffer(const QHashedString &strId)
{
    QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strId);

    GLenum attachment = pRenderbuffer->GetExternalAttachment() + m_arColorBuffers.GetCount();

    QE_ASSERT_ERROR(attachment == GL_COLOR_ATTACHMENT0, "The renderbuffer is not a color buffer.");
    QE_ASSERT_ERROR(m_arColorBuffers.GetCount() < GL_MAX_COLOR_ATTACHMENTS, "It is not possible to attach more color buffers, maximum allowed reached.");
    
    glNamedFramebufferRenderbuffer(m_framebufferId, attachment, GL_RENDERBUFFER, pRenderbuffer->GetExternalId());

    QE_ASSERT_OPENGL_ERROR("An error occurred when adding a color buffer (glNamedFramebufferRenderbuffer).");

    m_arColorBuffers.Add(strId);
}

void QFramebuffer::RemoveColorBuffer(const QHashedString &strId)
{
    m_arColorBuffers.Remove(m_arColorBuffers.IndexOf(strId));
}

void QFramebuffer::SetRenderbufferOperation(const QHashedString &strRenderbufferId)
{
    QE_ASSERT_ERROR(m_arColorBuffers.Contains(strRenderbufferId) || m_strDepthBuffer == strRenderbufferId || m_strStencilBuffer == strRenderbufferId, "The specified renderbuffer does not belong to the framebuffer.");

    QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strRenderbufferId);

    glNamedFramebufferRenderbuffer(m_framebufferId, pRenderbuffer->GetExternalAttachment(), GL_RENDERBUFFER, pRenderbuffer->GetExternalId());

    QE_ASSERT_OPENGL_ERROR("An error occurred when setting the operation of a renderbuffer (glNamedFramebufferRenderbuffer).");
}

void QFramebuffer::SetDepthBuffer(const QHashedString &strId)
{
    QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strId);

    GLenum attachment = pRenderbuffer->GetExternalAttachment();

    QE_ASSERT_ERROR(attachment == GL_DEPTH_ATTACHMENT, "The renderbuffer is not a depth buffer.");

    glNamedFramebufferRenderbuffer(m_framebufferId, attachment, GL_RENDERBUFFER, pRenderbuffer->GetExternalId());

    QE_ASSERT_OPENGL_ERROR("An error occurred when setting the depth buffer (glNamedFramebufferRenderbuffer).");

    m_strDepthBuffer = strId;
}

QHashedString QFramebuffer::GetDepthBuffer() const
{

    return m_strDepthBuffer;
}

void QFramebuffer::SetStencilBuffer(const QHashedString &strId)
{
    QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strId);

    GLenum attachment = pRenderbuffer->GetExternalAttachment();

    QE_ASSERT_ERROR(attachment == GL_STENCIL_ATTACHMENT, "The renderbuffer is not a stencil buffer.");

    glNamedFramebufferRenderbuffer(m_framebufferId, attachment, GL_RENDERBUFFER, pRenderbuffer->GetExternalId());

    QE_ASSERT_OPENGL_ERROR("An error occurred when setting the stencil buffer (glFramebufferRenderbuffer).");

    m_strStencilBuffer = strId;
}

QHashedString QFramebuffer::GetStencilBuffer() const
{
    return m_strStencilBuffer;
}

void QFramebuffer::SetDepthStencilBuffer(const QHashedString &strId)
{
    QRenderbuffer* pRenderbuffer = QE->Graphics->GetRenderbuffer(strId);

    GLenum attachment = pRenderbuffer->GetExternalAttachment();

    QE_ASSERT_ERROR(attachment == GL_DEPTH_STENCIL_ATTACHMENT, "The renderbuffer is not a depth-stencil buffer.");

    glNamedFramebufferRenderbuffer(m_framebufferId, attachment, GL_RENDERBUFFER, pRenderbuffer->GetExternalId());

    QE_ASSERT_OPENGL_ERROR("An error occurred when setting the depth-stencil buffer (glFramebufferRenderbuffer).");

    m_strDepthStencilBuffer = strId;
}

QHashedString QFramebuffer::GetDepthStencilBuffer() const
{
    return m_strDepthStencilBuffer;
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