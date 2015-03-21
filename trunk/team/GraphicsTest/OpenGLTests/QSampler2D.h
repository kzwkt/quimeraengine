
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
        m_eWrapModeU = eWrapMode;
    }

    void SetWrapModeV(const EQTextureWrapMode eWrapMode)
    {
        m_eWrapModeV = eWrapMode;
    }

    void SetWrapModeW(const EQTextureWrapMode eWrapMode)
    {
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
        m_eMinificationFilter = eFilter;
    }

    EQMinificationFilter GetMinificationFilter() const
    {
        return m_eMinificationFilter;
    }

    void SetMagnificationFilter(const EQMagnificationFilter eFilter)
    {
        m_eMagnificationFilter = eFilter;
    }

    EQMagnificationFilter GetMagificationFilter() const
    {
        return m_eMagnificationFilter;
    }

    void SetBorderColor(const QColor &borderColor)
    {
        m_borderColor = borderColor;
    }

    QColor GetBorderColor() const
    {
        return m_borderColor;
    }

protected:

    EQTextureWrapMode m_eWrapModeU;
    EQTextureWrapMode m_eWrapModeV;
    EQTextureWrapMode m_eWrapModeW;
    EQMinificationFilter m_eMinificationFilter;
    EQMagnificationFilter m_eMagnificationFilter;
    QColor m_borderColor;
    GLuint m_uId;

};

#endif // __QSAMPLER2D__