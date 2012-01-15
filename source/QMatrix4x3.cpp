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

QMatrix4x3 operator*(const float_q &fScalar, const QBaseMatrix4x3 &matrix)
{
	QMatrix4x3 aux;

	aux.ij[0][0] = fScalar * matrix.ij[0][0];
	aux.ij[0][1] = fScalar * matrix.ij[0][1];
	aux.ij[0][2] = fScalar * matrix.ij[0][2];
	aux.ij[1][0] = fScalar * matrix.ij[1][0];
	aux.ij[1][1] = fScalar * matrix.ij[1][1];
	aux.ij[1][2] = fScalar * matrix.ij[1][2];
	aux.ij[2][0] = fScalar * matrix.ij[2][0];
	aux.ij[2][1] = fScalar * matrix.ij[2][1];
	aux.ij[2][2] = fScalar * matrix.ij[2][2];
	aux.ij[3][0] = fScalar * matrix.ij[3][0];
	aux.ij[3][1] = fScalar * matrix.ij[3][1];
	aux.ij[3][2] = fScalar * matrix.ij[3][2];

	return aux;
}

QMatrix4x3 QMatrix4x3::operator*(const QBaseMatrix3x3& matrix) const
{
	QMatrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

	return aux;
}

QBaseMatrix4x4 QMatrix4x3::operator*(const QBaseMatrix3x4& matrix) const
{
	QBaseMatrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];
    aux.ij[0][3] = this->ij[0][0] * matrix.ij[0][3] + this->ij[0][1] * matrix.ij[1][3] + this->ij[0][2] * matrix.ij[2][3];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];
    aux.ij[1][3] = this->ij[1][0] * matrix.ij[0][3] + this->ij[1][1] * matrix.ij[1][3] + this->ij[1][2] * matrix.ij[2][3];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];
    aux.ij[2][3] = this->ij[2][0] * matrix.ij[0][3] + this->ij[2][1] * matrix.ij[1][3] + this->ij[2][2] * matrix.ij[2][3];

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];
    aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3];

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

QMatrix4x3& QMatrix4x3::operator*=(const QBaseMatrix3x3& matrix)
{
	QMatrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

	*this = aux;

	return *this;
}

QMatrix4x3 QMatrix4x3::operator/(const float_q &fScalar) const
{
	QE_ASSERT(fScalar)

	const float_q &fDivisor = SQFloat::_1/fScalar;

	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] * fDivisor;
	aux.ij[0][1] = this->ij[0][1] * fDivisor;
	aux.ij[0][2] = this->ij[0][2] * fDivisor;
	aux.ij[1][0] = this->ij[1][0] * fDivisor;
	aux.ij[1][1] = this->ij[1][1] * fDivisor;
	aux.ij[1][2] = this->ij[1][2] * fDivisor;
	aux.ij[2][0] = this->ij[2][0] * fDivisor;
	aux.ij[2][1] = this->ij[2][1] * fDivisor;
	aux.ij[2][2] = this->ij[2][2] * fDivisor;
	aux.ij[3][0] = this->ij[3][0] * fDivisor;
	aux.ij[3][1] = this->ij[3][1] * fDivisor;
	aux.ij[3][2] = this->ij[3][2] * fDivisor;

	return aux;
}

QMatrix4x3 QMatrix4x3::operator+(const QBaseMatrix4x3 &matrix) const
{
	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] + matrix.ij[0][2];
	aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] + matrix.ij[1][2];
	aux.ij[2][0] = this->ij[2][0] + matrix.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] + matrix.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] + matrix.ij[2][2];
	aux.ij[3][0] = this->ij[3][0] + matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] + matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] + matrix.ij[3][2];

	return aux;
}

QMatrix4x3 QMatrix4x3::operator-(const QBaseMatrix4x3 &matrix) const
{
	QMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] - matrix.ij[0][2];
	aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] - matrix.ij[1][2];
	aux.ij[2][0] = this->ij[2][0] - matrix.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] - matrix.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] - matrix.ij[2][2];
	aux.ij[3][0] = this->ij[3][0] - matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] - matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] - matrix.ij[3][2];

	return aux;
}

string_q QMatrix4x3::ToString() const
{
    return QE_L("M4x3(") + SQFloat::ToString(this->ij[0][0]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[0][1]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[0][2]) + QE_L(")(") +
                           SQFloat::ToString(this->ij[1][0]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[1][1]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[1][2]) + QE_L(")(") +
                           SQFloat::ToString(this->ij[2][0]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[2][1]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[2][2]) + QE_L(")(") +
                           SQFloat::ToString(this->ij[3][0]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[3][1]) + QE_L(",")  +
                           SQFloat::ToString(this->ij[3][2]) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

