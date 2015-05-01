#ifndef __QTEXTUREBUFFER__
#define __QTEXTUREBUFFER__

#include "QBaseTextureBuffer.h"

class QTextureBuffer : public QBaseTextureBuffer
{
public:

    QTextureBuffer(const GLint textureId, const GLenum format, const QHashedString strBufferId, const u32_q uWidth, const EQTextureFormat::EnumType eFormat)
    {
        m_strBufferId = strBufferId;
        m_uWidth = uWidth;
        m_eFormat = eFormat;
    }

    GLuint GetExternalId() const
    {
        return m_textureId;
    }

    GLenum GetExternalFormat() const
    {
        return m_format;
    }

protected:

    GLuint m_textureId;
    GLenum m_format;

};


#endif // __QTEXTUREBUFFER__
