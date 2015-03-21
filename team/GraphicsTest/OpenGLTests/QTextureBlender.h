#ifndef __QBLENDER__
#define __QBLENDER__

#include "GL/glew.h"

#include "QuimeraEngineIncludesAndUsings.h"

class QTextureBlender
{
public:

    enum EQTextureBlendOperation
    {
        E_Addition,
        E_Substraction,
        E_Mutiplication,
        E_Division,
        E_SignedAddition,
        E_SmoothAddition
    };

    QTextureBlender() : m_fBlendFactor(SQFloat::_0),
                        m_eBlendOperation(E_Addition)
    {
    }

    EQTextureBlendOperation GetBlendOperation() const
    {
        return m_eBlendOperation;
    }

    void SetBlendOperation(const EQTextureBlendOperation eOperation)
    {
        m_eBlendOperation = eOperation;
    }

    float_q GetBlendFactor() const
    {
        return m_fBlendFactor;
    }

    void SetBlendFactor(const float_q fBlendFactor)
    {
        m_fBlendFactor = fBlendFactor;
    }

protected:
    /*
    static void GetEquivalentBlendOperationOpenGLValue(const EQTextureBlendOperation eOperation, GLenum &eSource, GLenum &eDestination)
    {
        switch (eOperation)
        {
        case QTextureBlender::E_Addition:
            eSource = 0;
            eDestination = 0;
            break;
        case QTextureBlender::E_Substraction:
            eSource = 0;
            eDestination = 0;
            break;
        case QTextureBlender::E_Mutiplication:
            eSource = 0;
            eDestination = 0;
            break;
        case QTextureBlender::E_Division:
            eSource = 0;
            eDestination = 0;
            break;
        case QTextureBlender::E_SmoothAddition:
            eSource = 0;
            eDestination = 0;
            break;
        case QTextureBlender::E_SignedAddition:
            eSource = 0;
            eDestination = 0;
            break;
        }
    }
    */
    float_q m_fBlendFactor;
    EQTextureBlendOperation m_eBlendOperation;

};

#endif // __QBLENDER__