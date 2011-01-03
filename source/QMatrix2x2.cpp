// [TERMS&CONDITIONS]

#include "QAngle.h"
#include "QMatrix2x2.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QMatrix2x2 QMatrix2x2::ZeroMatrix(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0);
const QMatrix2x2 QMatrix2x2::Identity  (QFloat::_1, QFloat::_0, QFloat::_0, QFloat::_1);
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QMatrix2x2::QMatrix2x2(const float_q &fAngle)
{
    
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q &fAngleRad = DegreesToRadians(fAngle, fAngleRad);

        const float_q& A   = cos(fAngleRad);
        const float_q& B   = sin(fAngleRad);
    #else
        const float_q& A   = cos(fAngle);
        const float_q& B   = sin(fAngle);
    #endif

    ij[0][0]  =  A;
    ij[0][1]  = -B;
    ij[1][0]  =  B;
    ij[1][1]  =  A;
}
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QMatrix2x2 QMatrix2x2::operator*(const float_q &fScalar) const
{
    QMatrix2x2 aux;

    aux.ij[0][0] = fScalar * this->ij[0][0];
    aux.ij[0][1] = fScalar * this->ij[0][1];
    aux.ij[1][0] = fScalar * this->ij[1][0];
    aux.ij[1][1] = fScalar * this->ij[1][1];

    return aux;
}

QMatrix2x2 operator*(const float_q &fScalar, const QBaseMatrix2x2 &m) 
{
    QMatrix2x2 aux;

    aux.ij[0][0] = fScalar * m.ij[0][0];
    aux.ij[0][1] = fScalar * m.ij[0][1];
    aux.ij[1][0] = fScalar * m.ij[1][0];
    aux.ij[1][1] = fScalar * m.ij[1][1];
        
    return aux;
}

QMatrix2x2 QMatrix2x2::operator*(const QBaseMatrix2x2 &m) const
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1];
    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1];

    return aux;
}

QMatrix2x2 QMatrix2x2::operator/(const float_q &fScalar) const
{
        
    QE_ASSERT(fScalar);

    QMatrix2x2 aux;
        
    aux.ij[0][0] = this->ij[0][0] / fScalar;
    aux.ij[0][1] = this->ij[0][1] / fScalar;
    aux.ij[1][0] = this->ij[1][0] / fScalar;
    aux.ij[1][1] = this->ij[1][1] / fScalar;

    return aux;
}

QMatrix2x2 QMatrix2x2::operator+(const QBaseMatrix2x2 &m) const
{
    QMatrix2x2 aux;
        
    aux.ij[0][0] = this->ij[0][0] + m.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + m.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] + m.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + m.ij[1][1];

    return aux;
}

QMatrix2x2 QMatrix2x2::operator-(const QBaseMatrix2x2 &m) const
{
    QMatrix2x2 aux;
        
    aux.ij[0][0] = this->ij[0][0] - m.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - m.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] - m.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - m.ij[1][1];
 
    return aux;
}

QMatrix2x2& QMatrix2x2::operator*=(const QBaseMatrix2x2 &m)
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1];
    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1];

    *this = aux;
        
    return *this;
}

bool QMatrix2x2::Reverse()
{
    // Special case where matrix is identity. Then inverse of the matrix is itself.
    if (this->IsIdentity())
    {
        return true;
    }

    // Gets Determinant.
    float_q fDet = this->GetDeterminant();

    // If Determinant is 0, this matrix has not inverse.
    if (QFloat::IsZero(fDet)) 
        return false;

    // We need inverse of determinant in calculus.
    fDet = QFloat::_1/fDet;
 
    float_q f00  = this->ij[0][0];

    this->ij[0][0] =  fDet * this->ij[1][1];
    this->ij[1][0] *= -fDet;
    this->ij[0][1] *= -fDet;
    this->ij[1][1] =  fDet * f00;

    return true;
}

bool QMatrix2x2::Reverse(QMatrix2x2 &m) const
{
    // Special case where matrix is identity. Then inverse of the matrix is itself.
    if (this->IsIdentity())
    {
        m = *this;
        return true;
    }

    // Gets Determinant.
    float_q fDet = this->GetDeterminant();

    // If Determinant is 0, this matrix has not inverse.
    if (QFloat::IsZero(fDet)) 
        return false;

    // We need inverse of determinant in calculus.
    fDet = QFloat::_1/fDet;
        
    m.ij[0][0] =  fDet * this->ij[1][1];
    m.ij[1][0] = -fDet * this->ij[1][0];
    m.ij[0][1] = -fDet * this->ij[0][1];
    m.ij[1][1] =  fDet * this->ij[0][0];

    return true;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

