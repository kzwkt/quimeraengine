
#ifndef __QCOLORBLENDER__
#define __QCOLORBLENDER__

#include "QuimeraEngineIncludesAndUsings.h"

class QAlphaBlender
{
public:

    enum EQBlendingFunction
    {
        E_Zero,
        E_One,
        E_SourceColor,
        E_DestinationColor,
        E_OneMinusSourceColor,
        E_OneMinusDestinationColor,
        E_SourceAlpha,
        E_DestinationAlpha,
        E_OneMinusSourceAlpha,
        E_OneMinusDestinationAlpha,
        E_ConstantColor,
        E_ConstantAlpha,
        E_OneMinusConstantColor,
        E_OneMinusConstantAlpha,
        E_AlphaSaturate,
        E_SecondSourceColor,
        E_SecondSourceAlpha,
        E_OneMinusSecondSourceColor,
        E_OneMinusSecondSourceAlpha
    };

    QAlphaBlender() : m_eSourceColorFactor(E_One),
                      m_eDestinationColorFactor(E_Zero),
                      m_eSourceAlphaFactor(E_One),
                      m_eDestinationAlphaFactor(E_Zero),
                      m_constantColor(QColor::GetNullVector()),
                      m_bSeparateAlphaBlending(false)
    {
    }

    void SetSourceColorFactor(const EQBlendingFunction eBlendingFunction)
    {
        m_eSourceColorFactor = eBlendingFunction;
    }

    EQBlendingFunction GetSourceColorFactor() const
    {
        return m_eSourceColorFactor;
    }

    void SetDestinationColorFactor(const EQBlendingFunction eBlendingFunction)
    {
        m_eDestinationColorFactor = eBlendingFunction;
    }

    EQBlendingFunction GetDestinationColorFactor() const
    {
        return m_eDestinationColorFactor;
    }

    void SetSourceAlphaFactor(const EQBlendingFunction eBlendingFunction)
    {
        m_eSourceAlphaFactor = eBlendingFunction;
    }

    EQBlendingFunction GetSourceAlphaFactor() const
    {
        return m_eSourceAlphaFactor;
    }

    void SetDestinationAlphaFactor(const EQBlendingFunction eBlendingFunction)
    {
        m_eDestinationAlphaFactor = eBlendingFunction;
    }

    EQBlendingFunction GetDestinationAlphaFactor() const
    {
        return m_eDestinationAlphaFactor;
    }

    QColor GetConstantColor() const
    {
        return m_constantColor;
    }

    void SetConstantColor(const QColor &constantColor)
    {
        m_constantColor = constantColor;
    }

    bool HasSeparateAlphaFactors() const
    {
        return m_bSeparateAlphaBlending;
    }

    void SetSeparateAlphaFactors(const bool bSeparate)
    {
        m_bSeparateAlphaBlending = bSeparate;
    }

protected:

    EQBlendingFunction m_eSourceColorFactor;
    EQBlendingFunction m_eDestinationColorFactor;
    EQBlendingFunction m_eSourceAlphaFactor;
    EQBlendingFunction m_eDestinationAlphaFactor;
    QColor m_constantColor;
    bool m_bSeparateAlphaBlending;

};

#endif // __QCOLORBLENDER__