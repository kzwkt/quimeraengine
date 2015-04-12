
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


    QFramebuffer(const GLuint framebufferId) : m_framebufferId(framebufferId)
    {
    }

    QHashedString GetColorBufferId(const u32_q uIndex) const;

    void AddColorBuffer(const QHashedString &strId);

    void RemoveColorBuffer(const QHashedString &strId);

    void QFramebuffer::SetRenderbufferOperation(const QHashedString &strRenderbufferId);

    void SetDepthBuffer(const QHashedString &strId);

    QHashedString GetDepthBuffer() const;

    void SetStencilBuffer(const QHashedString &strId);

    QHashedString GetStencilBuffer() const;

    void SetDepthStencilBuffer(const QHashedString &strId);

    QHashedString GetDepthStencilBuffer() const;

    bool IsValid();

    GLuint GetExternalId() const;
    
protected:

    static GLenum _GetEquivalentRenderbufferTargetOpenGLValue(const EQRenderbufferOperation eTarget);

    GLuint m_framebufferId;
    QArrayDynamic<QHashedString> m_arColorBuffers;
    QHashedString m_strDepthBuffer;
    QHashedString m_strDepthStencilBuffer;
    QHashedString m_strStencilBuffer;
};


#endif // __QFRAMEBUFFER__