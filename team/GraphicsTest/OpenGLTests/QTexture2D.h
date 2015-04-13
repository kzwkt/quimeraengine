
#ifndef __QTEXTURE2D__
#define __QTEXTURE2D__

#include "GL/glew.h"

#include "QSampler2D.h"


class QTexture2D
{
public:

    enum EQTextureMapping
    {
        E_UV,
        E_Spherical,
        E_Cylindrical,
        E_Cubic,
        E_Planar
    };


    QTexture2D(GLuint textureId) : m_textureId(textureId)
    {
        glGenerateTextureMipmap(m_textureId);
    }

    void GenerateMipmaps()
    {
        
    }
    /*
    void SetWrapModeS(const QSampler2D::EQTextureWrapMode eWrapMode)
    {
        GLint nWrapMode = 0;

        switch (eWrapMode)
        {
        case QSampler2D::E_Border:
            nWrapMode = GL_CLAMP_TO_BORDER;
            break;
        case QSampler2D::E_Clamp:
            nWrapMode = GL_CLAMP_TO_EDGE;
            break;
        case QSampler2D::E_Repeat:
            nWrapMode = GL_REPEAT;
            break;
        case QSampler2D::E_RepeatMirror:
            nWrapMode = GL_MIRRORED_REPEAT;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nWrapMode);
    }

    void SetWrapModeT(const QSampler2D::EQTextureWrapMode eWrapMode)
    {
        GLint nWrapMode = 0;

        switch (eWrapMode)
        {
        case QSampler2D::E_Border:
            nWrapMode = GL_CLAMP_TO_BORDER;
            break;
        case QSampler2D::E_Clamp:
            nWrapMode = GL_CLAMP_TO_EDGE;
            break;
        case QSampler2D::E_Repeat:
            nWrapMode = GL_MIRRORED_REPEAT;
            break;
        case QSampler2D::E_RepeatMirror:
            nWrapMode = GL_REPEAT;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, nWrapMode);
    }

    void SetMagnificationFilter(const QSampler2D::EQMagnificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QSampler2D::E_MagNearest:
            nFilter = GL_NEAREST;
            break;
        case QSampler2D::E_MagLinear:
            nFilter = GL_LINEAR;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, nFilter);
    }

    void SetMinificationFilter(const QSampler2D::EQMinificationFilter eFilter)
    {
        GLint nFilter = 0;

        switch (eFilter)
        {
        case QSampler2D::E_MinNearest:
            nFilter = GL_NEAREST;
            break;
        case QSampler2D::E_MinLinear:
            nFilter = GL_LINEAR;
            break;
        case QSampler2D::E_LinearMipmaps:
            nFilter = GL_LINEAR_MIPMAP_LINEAR;
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, nFilter);
    }
    */
    void SetMapping(const EQTextureMapping eTextureMapping)
    {
        m_eMapping = eTextureMapping;
    }

    EQTextureMapping GetMapping() const
    {
        return m_eMapping;
    }

    GLuint GetTextureID() const
    {
        return m_textureId;
    }

protected:

    GLuint m_textureId;

    EQTextureMapping m_eMapping;
};

#endif // __QTEXTURE2D__
