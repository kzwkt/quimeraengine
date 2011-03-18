// [TERMS&CONDITIONS]

#include "QAngle.h"
#include "QMatrix3x3.h"
#include "QMatrix3x4.h"

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

    const QMatrix3x3 QMatrix3x3::ZeroMatrix(QFloat::_0, QFloat::_0, QFloat::_0,
                                            QFloat::_0, QFloat::_0, QFloat::_0,
                                            QFloat::_0, QFloat::_0, QFloat::_0);

    const QMatrix3x3 QMatrix3x3::Identity(  QFloat::_1, QFloat::_0, QFloat::_0,
                                            QFloat::_0, QFloat::_1, QFloat::_0,
                                            QFloat::_0, QFloat::_0, QFloat::_1);
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

    QMatrix3x3 QMatrix3x3::operator*(const float_q &fScalar) const
    {
        QMatrix3x3 aux;

        aux.ij[0][0] = fScalar * this->ij[0][0];
        aux.ij[0][1] = fScalar * this->ij[0][1];
        aux.ij[0][2] = fScalar * this->ij[0][2];
        aux.ij[1][0] = fScalar * this->ij[1][0];
        aux.ij[1][1] = fScalar * this->ij[1][1];
        aux.ij[1][2] = fScalar * this->ij[1][2];
        aux.ij[2][0] = fScalar * this->ij[2][0];
        aux.ij[2][1] = fScalar * this->ij[2][1];
        aux.ij[2][2] = fScalar * this->ij[2][2];

        return aux;
    }

    QMatrix3x3 operator*(const float_q &fScalar, const QBaseMatrix3x3 &m) 
    {

        QMatrix3x3 aux;

        aux.ij[0][0] = fScalar * m.ij[0][0];
        aux.ij[0][1] = fScalar * m.ij[0][1];
        aux.ij[0][2] = fScalar * m.ij[0][2];
        aux.ij[1][0] = fScalar * m.ij[1][0];
        aux.ij[1][1] = fScalar * m.ij[1][1];
        aux.ij[1][2] = fScalar * m.ij[1][2];
        aux.ij[2][0] = fScalar * m.ij[2][0];
        aux.ij[2][1] = fScalar * m.ij[2][1];
        aux.ij[2][2] = fScalar * m.ij[2][2];
        
        return aux;
    }

    QMatrix3x3 QMatrix3x3::operator*(const QBaseMatrix3x3 &m) const
    {
        QMatrix3x3 aux;

        aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

        return aux;
    }

	QBaseMatrix3x4 QMatrix3x3::operator*(const QBaseMatrix3x4& m) const
	{
        QMatrix3x4 aux;

        aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];
		aux.ij[0][3] = this->ij[0][0]*m.ij[0][3] + this->ij[0][1]*m.ij[1][3] + this->ij[0][2]*m.ij[2][3];

        aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];
		aux.ij[1][3] = this->ij[1][0]*m.ij[0][3] + this->ij[1][1]*m.ij[1][3] + this->ij[1][2]*m.ij[2][3];

        aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];
        aux.ij[2][3] = this->ij[2][0]*m.ij[0][3] + this->ij[2][1]*m.ij[1][3] + this->ij[2][2]*m.ij[2][3];

        return aux;

	}

    QMatrix3x3& QMatrix3x3::operator*=(const float_q& fScalar)
    {
        this->ij[0][0] *= fScalar;
		this->ij[0][1] *= fScalar;
		this->ij[0][2] *= fScalar;
		this->ij[1][0] *= fScalar;
		this->ij[1][1] *= fScalar;
		this->ij[1][2] *= fScalar;
		this->ij[2][0] *= fScalar;
		this->ij[2][1] *= fScalar;
		this->ij[2][2] *= fScalar;

        return *this;
    }

    QMatrix3x3 QMatrix3x3::operator/(const float_q &fScalar) const
    {
        
        QE_ASSERT(fScalar != QFloat::_0);

        QMatrix3x3 aux;
        
        aux.ij[0][0] = this->ij[0][0] / fScalar;
        aux.ij[0][1] = this->ij[0][1] / fScalar;
        aux.ij[0][2] = this->ij[0][2] / fScalar;
        aux.ij[1][0] = this->ij[1][0] / fScalar;
        aux.ij[1][1] = this->ij[1][1] / fScalar;
        aux.ij[1][2] = this->ij[1][2] / fScalar;
        aux.ij[2][0] = this->ij[2][0] / fScalar;
        aux.ij[2][1] = this->ij[2][1] / fScalar;
        aux.ij[2][2] = this->ij[2][2] / fScalar;

        return aux;
    }

    QMatrix3x3 QMatrix3x3::operator+(const QBaseMatrix3x3 &m) const
    {
        QMatrix3x3 aux;
        
        aux.ij[0][0] = this->ij[0][0] + m.ij[0][0];
        aux.ij[0][1] = this->ij[0][1] + m.ij[0][1];
        aux.ij[0][2] = this->ij[0][2] + m.ij[0][2];
        aux.ij[1][0] = this->ij[1][0] + m.ij[1][0];
        aux.ij[1][1] = this->ij[1][1] + m.ij[1][1];
        aux.ij[1][2] = this->ij[1][2] + m.ij[1][2];
        aux.ij[2][0] = this->ij[2][0] + m.ij[2][0];
        aux.ij[2][1] = this->ij[2][1] + m.ij[2][1];
        aux.ij[2][2] = this->ij[2][2] + m.ij[2][2];

        return aux;
    }

    QMatrix3x3 QMatrix3x3::operator-(const QBaseMatrix3x3 &m) const
    {
        QMatrix3x3 aux;
        
        aux.ij[0][0] = this->ij[0][0] - m.ij[0][0];
        aux.ij[0][1] = this->ij[0][1] - m.ij[0][1];
        aux.ij[0][2] = this->ij[0][2] - m.ij[0][2];
        aux.ij[1][0] = this->ij[1][0] - m.ij[1][0];
        aux.ij[1][1] = this->ij[1][1] - m.ij[1][1];
        aux.ij[1][2] = this->ij[1][2] - m.ij[1][2];
        aux.ij[2][0] = this->ij[2][0] - m.ij[2][0];
        aux.ij[2][1] = this->ij[2][1] - m.ij[2][1];
        aux.ij[2][2] = this->ij[2][2] - m.ij[2][2];

        return aux;
    }

    QMatrix3x3& QMatrix3x3::operator*=(const QBaseMatrix3x3 &m)
    {
        QMatrix3x3 aux;

        aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

        *this = aux;
        
        return *this;
    }

    void QMatrix3x3::Transpose()
    {
        QMatrix3x3 aux;
        
        aux.ij[0][0] = this->ij[0][0];
        aux.ij[0][1] = this->ij[1][0];
        aux.ij[0][2] = this->ij[2][0];
        aux.ij[1][0] = this->ij[0][1];
        aux.ij[1][1] = this->ij[1][1];
        aux.ij[1][2] = this->ij[2][1];
        aux.ij[2][0] = this->ij[0][2];
        aux.ij[2][1] = this->ij[1][2];
        aux.ij[2][2] = this->ij[2][2];

        *this = aux;
    }
    
    bool QMatrix3x3::Reverse()
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
 
        QMatrix3x3 aux;

        // 1st column of inverse 
        aux.ij[0][0] =  fDet * (this->ij[1][1] * this->ij[2][2] - this->ij[1][2] * this->ij[2][1]);
        aux.ij[1][0] = -fDet * (this->ij[1][0] * this->ij[2][2] - this->ij[1][2] * this->ij[2][0]);
        aux.ij[2][0] =  fDet * (this->ij[1][0] * this->ij[2][1] - this->ij[1][1] * this->ij[2][0]);

        // 2nd column of inverse 
        aux.ij[0][1] = -fDet * (this->ij[0][1] * this->ij[2][2] - this->ij[0][2] * this->ij[2][1]);
        aux.ij[1][1] =  fDet * (this->ij[0][0] * this->ij[2][2] - this->ij[0][2] * this->ij[2][0]);
        aux.ij[2][1] = -fDet * (this->ij[0][0] * this->ij[2][1] - this->ij[0][1] * this->ij[2][0]);

        // 3rd column of inverse 
        aux.ij[0][2] =  fDet * (this->ij[0][1] * this->ij[1][2] - this->ij[0][2] * this->ij[1][1]);
        aux.ij[1][2] = -fDet * (this->ij[0][0] * this->ij[1][2] - this->ij[0][2] * this->ij[1][0]);
        aux.ij[2][2] =  fDet * (this->ij[0][0] * this->ij[1][1] - this->ij[0][1] * this->ij[1][0]);

        *this = aux;

        return true;

    }

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

