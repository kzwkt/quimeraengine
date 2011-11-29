// [TERMS&CONDITIONS]

#include "QMatrix3x3.h"

#include "QMatrix4x3.h"

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

const QMatrix4x3 QMatrix4x3::ZeroMatrix(SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0);

const QMatrix4x3 QMatrix4x3::Identity(  SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_1,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0);

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

QMatrix4x3 QMatrix4x3::operator*(const float_q &fScalar) const
{
	QMatrix4x3 aux;

	aux.ij[0][0] = fScalar * this->ij[0][0];
	aux.ij[0][1] = fScalar * this->ij[0][1];
	aux.ij[0][2] = fScalar * this->ij[0][2];
	aux.ij[1][0] = fScalar * this->ij[1][0];
	aux.ij[1][1] = fScalar * this->ij[1][1];
	aux.ij[1][2] = fScalar * this->ij[1][2];
	aux.ij[2][0] = fScalar * this->ij[2][0];
	aux.ij[2][1] = fScalar * this->ij[2][1];
	aux.ij[2][2] = fScalar * this->ij[2][2];
	aux.ij[3][0] = fScalar * this->ij[3][0];
	aux.ij[3][1] = fScalar * this->ij[3][1];
	aux.ij[3][2] = fScalar * this->ij[3][2];

	return aux;
}

QMatrix4x3 operator*(const float_q &fScalar, const QBaseMatrix4x3 &m)
{
	QMatrix4x3 aux;

	aux.ij[0][0] = fScalar * m.ij[0][0];
	aux.ij[0][1] = fScalar * m.ij[0][1];
	aux.ij[0][2] = fScalar * m.ij[0][2];
	aux.ij[1][0] = fScalar * m.ij[1][0];
	aux.ij[1][1] = fScalar * m.ij[1][1];
	aux.ij[1][2] = fScalar * m.ij[1][2];
	aux.ij[2][0] = fScalar * m.ij[2][0];
	aux.ij[2][1] = fScalar * m.ij[2][1];
	aux.ij[2][2] = fScalar * m.ij[2][2];
	aux.ij[3][0] = fScalar * m.ij[3][0];
	aux.ij[3][1] = fScalar * m.ij[3][1];
	aux.ij[3][2] = fScalar * m.ij[3][2];

	return aux;
}

QMatrix4x3 QMatrix4x3::operator*(const QBaseMatrix3x3& m) const
{
	QMatrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];
		
    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
    aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];

    aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

	aux.ij[3][0] = this->ij[3][0]*m.ij[0][0] + this->ij[3][1]*m.ij[1][0] + this->ij[3][2]*m.ij[2][0];
    aux.ij[3][1] = this->ij[3][0]*m.ij[0][1] + this->ij[3][1]*m.ij[1][1] + this->ij[3][2]*m.ij[2][1];
    aux.ij[3][2] = this->ij[3][0]*m.ij[0][2] + this->ij[3][1]*m.ij[1][2] + this->ij[3][2]*m.ij[2][2];

	return aux;
}

QBaseMatrix4x4 QMatrix4x3::operator*(const QBaseMatrix3x4& m) const
{
	QBaseMatrix4x4 aux;

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

	aux.ij[3][0] = this->ij[3][0]*m.ij[0][0] + this->ij[3][1]*m.ij[1][0] + this->ij[3][2]*m.ij[2][0];
    aux.ij[3][1] = this->ij[3][0]*m.ij[0][1] + this->ij[3][1]*m.ij[1][1] + this->ij[3][2]*m.ij[2][1];
    aux.ij[3][2] = this->ij[3][0]*m.ij[0][2] + this->ij[3][1]*m.ij[1][2] + this->ij[3][2]*m.ij[2][2];
    aux.ij[3][3] = this->ij[3][0]*m.ij[0][3] + this->ij[3][1]*m.ij[1][3] + this->ij[3][2]*m.ij[2][3];

	return aux;
}

QMatrix4x3& QMatrix4x3::operator*=(const float_q& fScalar)
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
	this->ij[3][0] *= fScalar;
	this->ij[3][1] *= fScalar;
	this->ij[3][2] *= fScalar;

    return *this;
}

QMatrix4x3& QMatrix4x3::operator*=(const QBaseMatrix3x3& m)
{
	QMatrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
    aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
    aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];
		
    aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
    aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
    aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];
		
    aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
    aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
    aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

	aux.ij[3][0] = this->ij[3][0]*m.ij[0][0] + this->ij[3][1]*m.ij[1][0] + this->ij[3][2]*m.ij[2][0];
    aux.ij[3][1] = this->ij[3][0]*m.ij[0][1] + this->ij[3][1]*m.ij[1][1] + this->ij[3][2]*m.ij[2][1];
    aux.ij[3][2] = this->ij[3][0]*m.ij[0][2] + this->ij[3][1]*m.ij[1][2] + this->ij[3][2]*m.ij[2][2];

	*this = aux;

	return *this;
}

QMatrix4x3 QMatrix4x3::operator/(const float_q &fScalar) const
{

	QE_ASSERT(fScalar);

	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] / fScalar;
	aux.ij[0][1] = this->ij[0][1] / fScalar;
	aux.ij[0][2] = this->ij[0][2] / fScalar;
	aux.ij[1][0] = this->ij[1][0] / fScalar;
	aux.ij[1][1] = this->ij[1][1] / fScalar;
	aux.ij[1][2] = this->ij[1][2] / fScalar;
	aux.ij[2][0] = this->ij[2][0] / fScalar;
	aux.ij[2][1] = this->ij[2][1] / fScalar;
	aux.ij[2][2] = this->ij[2][2] / fScalar;
	aux.ij[3][0] = this->ij[3][0] / fScalar;
	aux.ij[3][1] = this->ij[3][1] / fScalar;
	aux.ij[3][2] = this->ij[3][2] / fScalar;

	return aux;
}

QMatrix4x3 QMatrix4x3::operator+(const QBaseMatrix4x3 &m) const
{
	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] + m.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] + m.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] + m.ij[0][2];
	aux.ij[1][0] = this->ij[1][0] + m.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] + m.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] + m.ij[1][2];
	aux.ij[2][0] = this->ij[2][0] + m.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] + m.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] + m.ij[2][2];
	aux.ij[3][0] = this->ij[3][0] + m.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] + m.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] + m.ij[3][2];

	return aux;
}

QMatrix4x3 QMatrix4x3::operator-(const QBaseMatrix4x3 &m) const
{
	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] - m.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] - m.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] - m.ij[0][2];
	aux.ij[1][0] = this->ij[1][0] - m.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] - m.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] - m.ij[1][2];
	aux.ij[2][0] = this->ij[2][0] - m.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] - m.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] - m.ij[2][2];
	aux.ij[3][0] = this->ij[3][0] - m.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] - m.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] - m.ij[3][2];

	return aux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

