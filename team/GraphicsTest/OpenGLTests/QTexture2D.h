
#ifndef __QTEXTURE2D__
#define __QTEXTURE2D__

#include "GL/glew.h"

class QTexture2D
{
public:

    enum EQWrapMode
    {
        E_Repeat,
        E_RepeatMirror,
        E_Clamp,
        E_Border
    };

    enum EQMinificationFilter
    {
        E_MinNearest,
        E_MinLinear,
        E_LinearMipmaps
    };

    enum EQMagnificationFilter
    {
        E_MagNearest,
        E_MagLinear
    };

    QTexture2D(GLuint textureId) : m_textureId(textureId)
    {
    }

    void GenerateMipmaps()
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void SetWrapModeS(const EQWrapMode eWrapMode)
    {
        GLint nWrapMode = 0;

        switch (eWrapMode)
        {
        case QTexture2D::E_Border:
            nWrapMode = GL_CLAMP_TO_BORDER;
            break;
        case QTexture2D::E_Clamp:
            nWrapMode = GL_CLAMP_TO_EDGE;
            break;
        case QTexture2D::E_Repeat:
            nWrapMode = GL_MIRRORED_REPEAT;
            break;
        case QTexture2D::E_RepeatMirror:
            nWrapMode = GL_REPEAT;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nWrapMode);
    }

    void SetWrapModeT(const EQWrapMode eWrapMode)
    {
        GLint nWrapMode = 0;

        switch (eWrapMode)
        {
        case QTexture2D::E_Border:
            nWrapMode = GL_CLAMP_TO_BORDER;
            break;
        case QTexture2D::E_Clamp:
            nWrapMode = GL_CLAMP_TO_EDGE;
            break;
        case QTexture2D::E_Repeat:
            nWrapMode = GL_MIRRORED_REPEAT;
            break;
        case QTexture2D::E_RepeatMirror:
            nWrapMode = GL_REPEAT;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, nWrapMode);
    }

    void SetMagnificationFilter(const EQMagnificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QTexture2D::E_MagNearest:
            nFilter = GL_NEAREST;
            break;
        case QTexture2D::E_MagLinear:
            nFilter = GL_LINEAR;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nFilter);
    }

    void SetMinificationFilter(const EQMinificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QTexture2D::E_MinNearest:
            nFilter = GL_NEAREST;
            break;
        case QTexture2D::E_MinLinear:
            nFilter = GL_LINEAR;
            break;
        case QTexture2D::E_LinearMipmaps:
            nFilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nFilter);
    }

    GLuint GetTextureID() const
    {
        return m_textureId;
    }

protected:

    GLuint m_textureId;
    // Sampler
};

#endif // __QTEXTURE2D__
