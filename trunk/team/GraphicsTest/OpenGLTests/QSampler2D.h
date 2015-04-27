
#ifndef __QSAMPLER2D__
#define __QSAMPLER2D__

class QSampler2D
{
public:

    enum EQTextureWrapMode
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

    QSampler2D(GLuint uId) : m_eWrapModeU(E_Border),
                             m_eWrapModeV(E_Border),
                             m_eWrapModeW(E_Border),
                             m_eMinificationFilter(E_LinearMipmaps),
                             m_eMagnificationFilter(E_MagLinear),
                             m_uId(uId)
    {
    }

    GLuint GetOpenGLId()
    {
        return m_uId;
    }

    void SetWrapModeU(const EQTextureWrapMode eWrapMode)
    {
        glSamplerParameteri(m_uId, GL_TEXTURE_WRAP_S, QSampler2D::_GetEquivalentWrapModeOpenGLValue(eWrapMode));
        m_eWrapModeU = eWrapMode;
    }

    void SetWrapModeV(const EQTextureWrapMode eWrapMode)
    {
        glSamplerParameteri(m_uId, GL_TEXTURE_WRAP_T, QSampler2D::_GetEquivalentWrapModeOpenGLValue(eWrapMode));
        m_eWrapModeV = eWrapMode;
    }

    void SetWrapModeW(const EQTextureWrapMode eWrapMode)
    {
        glSamplerParameteri(m_uId, GL_TEXTURE_WRAP_R, QSampler2D::_GetEquivalentWrapModeOpenGLValue(eWrapMode));
        m_eWrapModeW = eWrapMode;
    }

    EQTextureWrapMode GetWrapModeU() const
    {
        return m_eWrapModeU;
    }

    EQTextureWrapMode GetWrapModeV() const
    {
        return m_eWrapModeV;
    }

    EQTextureWrapMode GetWrapModeW() const
    {
        return m_eWrapModeW;
    }

    void SetMinificationFilter(const EQMinificationFilter eFilter)
    {
        glSamplerParameteri(m_uId, GL_TEXTURE_MIN_FILTER, QSampler2D::_GetEquivalentMinificationFilterOpenGLValue(eFilter));
        m_eMinificationFilter = eFilter;
    }

    EQMinificationFilter GetMinificationFilter() const
    {
        return m_eMinificationFilter;
    }

    void SetMagnificationFilter(const EQMagnificationFilter eFilter)
    {
        glSamplerParameteri(m_uId, GL_TEXTURE_MAG_FILTER, QSampler2D::_GetEquivalentMagnificationFilterOpenGLValue(eFilter));
        m_eMagnificationFilter = eFilter;
    }

    EQMagnificationFilter GetMagificationFilter() const
    {
        return m_eMagnificationFilter;
    }

    void SetBorderColor(const QColor &borderColor)
    {
        glSamplerParameterfv(m_uId, GL_TEXTURE_BORDER_COLOR, &borderColor.x);
        m_borderColor = borderColor;
    }

    QColor GetBorderColor() const
    {
        return m_borderColor;
    }

protected:

    static GLint _GetEquivalentMagnificationFilterOpenGLValue(const QSampler2D::EQMagnificationFilter eFilter)
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

        return nFilter;
    }

    static GLint _GetEquivalentMinificationFilterOpenGLValue(const QSampler2D::EQMinificationFilter eFilter)
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

        return nFilter;
    }

    static GLint _GetEquivalentWrapModeOpenGLValue(const QSampler2D::EQTextureWrapMode eWrapMode)
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

        return nWrapMode;
    }

    EQTextureWrapMode m_eWrapModeU;
    EQTextureWrapMode m_eWrapModeV;
    EQTextureWrapMode m_eWrapModeW;
    EQMinificationFilter m_eMinificationFilter;
    EQMagnificationFilter m_eMagnificationFilter;
    QColor m_borderColor;
    GLuint m_uId;

};

#endif // __QSAMPLER2D__