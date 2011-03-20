// [TERMS&CONDITIONS]

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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  CONSTANTS INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QMatrix3x4 QMatrix3x4::ZeroMatrix(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0,
                                        QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0,
                                        QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0);

const QMatrix3x4 QMatrix3x4::Identity(QFloat::_1, QFloat::_0, QFloat::_0, QFloat::_0,
                                      QFloat::_0, QFloat::_1, QFloat::_0, QFloat::_0,
                                      QFloat::_0, QFloat::_0, QFloat::_1, QFloat::_0);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################
	
	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QMatrix3x4 QMatrix3x4::operator*(const float_q &fScalar) const
{
	QMatrix3x4 aux;

	aux.ij[0][0] = fScalar * this->ij[0][0];
	aux.ij[0][1] = fScalar * this->ij[0][1];
	aux.ij[0][2] = fScalar * this->ij[0][2];
	aux.ij[0][3] = fScalar * this->ij[0][3];
	aux.ij[1][0] = fScalar * this->ij[1][0];
	aux.ij[1][1] = fScalar * this->ij[1][1];
	aux.ij[1][2] = fScalar * this->ij[1][2];
	aux.ij[1][3] = fScalar * this->ij[1][3];
	aux.ij[2][0] = fScalar * this->ij[2][0];
	aux.ij[2][1] = fScalar * this->ij[2][1];
	aux.ij[2][2] = fScalar * this->ij[2][2];
	aux.ij[2][3] = fScalar * this->ij[2][3];

	return aux;
}

QMatrix3x4 operator*(const float_q &fScalar, const QBaseMatrix3x4 &m) 
{
	QMatrix3x4 aux;

	aux.ij[0][0] = fScalar * m.ij[0][0];
	aux.ij[0][1] = fScalar * m.ij[0][1];
	aux.ij[0][2] = fScalar * m.ij[0][2];
	aux.ij[0][3] = fScalar * m.ij[0][3];
	aux.ij[1][0] = fScalar * m.ij[1][0];
	aux.ij[1][1] = fScalar * m.ij[1][1];
	aux.ij[1][2] = fScalar * m.ij[1][2];
	aux.ij[1][3] = fScalar * m.ij[1][3];
	aux.ij[2][0] = fScalar * m.ij[2][0];
	aux.ij[2][1] = fScalar * m.ij[2][1];
	aux.ij[2][2] = fScalar * m.ij[2][2];
	aux.ij[2][3] = fScalar * m.ij[2][3];
		
	return aux;
}

QMatrix3x4 QMatrix3x4::operator/(const float_q &fScalar) const
{
		
	QE_ASSERT(fScalar != QFloat::_0);

	QMatrix3x4 aux;
		
	aux.ij[0][0] = this->ij[0][0] / fScalar;
	aux.ij[0][1] = this->ij[0][1] / fScalar;
	aux.ij[0][2] = this->ij[0][2] / fScalar;
	aux.ij[0][3] = this->ij[0][3] / fScalar; 
	aux.ij[1][0] = this->ij[1][0] / fScalar;
	aux.ij[1][1] = this->ij[1][1] / fScalar;
	aux.ij[1][2] = this->ij[1][2] / fScalar;
	aux.ij[1][3] = this->ij[1][3] / fScalar; 
	aux.ij[2][0] = this->ij[2][0] / fScalar;
	aux.ij[2][1] = this->ij[2][1] / fScalar;
	aux.ij[2][2] = this->ij[2][2] / fScalar;
	aux.ij[2][3] = this->ij[2][3] / fScalar;

	return aux;
}

QMatrix3x4 QMatrix3x4::operator+(const QBaseMatrix3x4 &m) const
{
	QMatrix3x4 aux;
		
	aux.ij[0][0] = this->ij[0][0] + m.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] + m.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] + m.ij[0][2];
	aux.ij[0][3] = this->ij[0][3] + m.ij[0][3];
	aux.ij[1][0] = this->ij[1][0] + m.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] + m.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] + m.ij[1][2];
	aux.ij[1][3] = this->ij[1][3] + m.ij[1][3];
	aux.ij[2][0] = this->ij[2][0] + m.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] + m.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] + m.ij[2][2];
	aux.ij[2][3] = this->ij[2][3] + m.ij[2][3];

	return aux;
}

QMatrix3x4 QMatrix3x4::operator-(const QBaseMatrix3x4 &m) const
{
	QMatrix3x4 aux;
		
	aux.ij[0][0] = this->ij[0][0] - m.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] - m.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] - m.ij[0][2];
	aux.ij[0][3] = this->ij[0][3] - m.ij[0][3];	
	aux.ij[1][0] = this->ij[1][0] - m.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] - m.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] - m.ij[1][2];
	aux.ij[1][3] = this->ij[1][3] - m.ij[1][3];	
	aux.ij[2][0] = this->ij[2][0] - m.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] - m.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] - m.ij[2][2];
	aux.ij[2][3] = this->ij[2][3] - m.ij[2][3];
	
	return aux;
}

QBaseMatrix3x3 QMatrix3x4::operator*(const QBaseMatrix4x3& m) const
{
	QBaseMatrix3x3 aux;

	aux.ij[0][0] = this->ij[0][0] * m.ij[0][0] + this->ij[0][1] * m.ij[1][0] + this->ij[0][2] * m.ij[2][0] + this->ij[0][3] * m.ij[3][0];
	aux.ij[0][1] = this->ij[0][0] * m.ij[0][1] + this->ij[0][1] * m.ij[1][1] + this->ij[0][2] * m.ij[2][1] + this->ij[0][3] * m.ij[3][1];
	aux.ij[0][2] = this->ij[0][0] * m.ij[0][2] + this->ij[0][1] * m.ij[1][2] + this->ij[0][2] * m.ij[2][2] + this->ij[0][3] * m.ij[3][2];

	aux.ij[1][0] = this->ij[1][0] * m.ij[0][0] + this->ij[1][1] * m.ij[1][0] + this->ij[1][2] * m.ij[2][0] + this->ij[1][3] * m.ij[3][0];
	aux.ij[1][1] = this->ij[1][0] * m.ij[0][1] + this->ij[1][1] * m.ij[1][1] + this->ij[1][2] * m.ij[2][1] + this->ij[1][3] * m.ij[3][1];
	aux.ij[1][2] = this->ij[1][0] * m.ij[0][2] + this->ij[1][1] * m.ij[1][2] + this->ij[1][2] * m.ij[2][2] + this->ij[1][3] * m.ij[3][2];

	aux.ij[2][0] = this->ij[2][0] * m.ij[0][0] + this->ij[2][1] * m.ij[1][0] + this->ij[2][2] * m.ij[2][0] + this->ij[2][3] * m.ij[3][0];
	aux.ij[2][1] = this->ij[2][0] * m.ij[0][1] + this->ij[2][1] * m.ij[1][1] + this->ij[2][2] * m.ij[2][1] + this->ij[2][3] * m.ij[3][1];
	aux.ij[2][2] = this->ij[2][0] * m.ij[0][2] + this->ij[2][1] * m.ij[1][2] + this->ij[2][2] * m.ij[2][2] + this->ij[2][3] * m.ij[3][2];

	return aux;
}

QBaseMatrix3x4 QMatrix3x4::operator*(const QBaseMatrix4x4& m) const
{
	QBaseMatrix3x4 aux;

	aux.ij[0][0] = this->ij[0][0] * m.ij[0][0] + this->ij[0][1] * m.ij[1][0] + this->ij[0][2] * m.ij[2][0] + this->ij[0][3] * m.ij[3][0];
	aux.ij[0][1] = this->ij[0][0] * m.ij[0][1] + this->ij[0][1] * m.ij[1][1] + this->ij[0][2] * m.ij[2][1] + this->ij[0][3] * m.ij[3][1];
	aux.ij[0][2] = this->ij[0][0] * m.ij[0][2] + this->ij[0][1] * m.ij[1][2] + this->ij[0][2] * m.ij[2][2] + this->ij[0][3] * m.ij[3][2];
	aux.ij[0][3] = this->ij[0][0] * m.ij[0][3] + this->ij[0][1] * m.ij[1][3] + this->ij[0][2] * m.ij[2][3] + this->ij[0][3] * m.ij[3][3];

	aux.ij[1][0] = this->ij[1][0] * m.ij[0][0] + this->ij[1][1] * m.ij[1][0] + this->ij[1][2] * m.ij[2][0] + this->ij[1][3] * m.ij[3][0];
	aux.ij[1][1] = this->ij[1][0] * m.ij[0][1] + this->ij[1][1] * m.ij[1][1] + this->ij[1][2] * m.ij[2][1] + this->ij[1][3] * m.ij[3][1];
	aux.ij[1][2] = this->ij[1][0] * m.ij[0][2] + this->ij[1][1] * m.ij[1][2] + this->ij[1][2] * m.ij[2][2] + this->ij[1][3] * m.ij[3][2];
	aux.ij[1][3] = this->ij[1][0] * m.ij[0][3] + this->ij[1][1] * m.ij[1][3] + this->ij[1][2] * m.ij[2][3] + this->ij[1][3] * m.ij[3][3];

	aux.ij[2][0] = this->ij[2][0] * m.ij[0][0] + this->ij[2][1] * m.ij[1][0] + this->ij[2][2] * m.ij[2][0] + this->ij[2][3] * m.ij[3][0];
	aux.ij[2][1] = this->ij[2][0] * m.ij[0][1] + this->ij[2][1] * m.ij[1][1] + this->ij[2][2] * m.ij[2][1] + this->ij[2][3] * m.ij[3][1];
	aux.ij[2][2] = this->ij[2][0] * m.ij[0][2] + this->ij[2][1] * m.ij[1][2] + this->ij[2][2] * m.ij[2][2] + this->ij[2][3] * m.ij[3][2];
	aux.ij[2][3] = this->ij[2][0] * m.ij[0][3] + this->ij[2][1] * m.ij[1][3] + this->ij[2][2] * m.ij[2][3] + this->ij[2][3] * m.ij[3][3];

	return aux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

