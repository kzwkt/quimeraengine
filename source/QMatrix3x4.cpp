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

QMatrix3x4 operator*(const float_q &fScalar, const QBaseMatrix3x4 &matrix)
{
	QMatrix3x4 aux;

	aux.ij[0][0] = fScalar * matrix.ij[0][0];
	aux.ij[0][1] = fScalar * matrix.ij[0][1];
	aux.ij[0][2] = fScalar * matrix.ij[0][2];
	aux.ij[0][3] = fScalar * matrix.ij[0][3];
	aux.ij[1][0] = fScalar * matrix.ij[1][0];
	aux.ij[1][1] = fScalar * matrix.ij[1][1];
	aux.ij[1][2] = fScalar * matrix.ij[1][2];
	aux.ij[1][3] = fScalar * matrix.ij[1][3];
	aux.ij[2][0] = fScalar * matrix.ij[2][0];
	aux.ij[2][1] = fScalar * matrix.ij[2][1];
	aux.ij[2][2] = fScalar * matrix.ij[2][2];
	aux.ij[2][3] = fScalar * matrix.ij[2][3];

	return aux;
}

QMatrix3x4 QMatrix3x4::operator/(const float_q &fScalar) const
{

	QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &fDivisor = SQFloat::_1/fScalar;

	QMatrix3x4 aux;

	aux.ij[0][0] = this->ij[0][0] * fDivisor;
	aux.ij[0][1] = this->ij[0][1] * fDivisor;
	aux.ij[0][2] = this->ij[0][2] * fDivisor;
	aux.ij[0][3] = this->ij[0][3] * fDivisor;
	aux.ij[1][0] = this->ij[1][0] * fDivisor;
	aux.ij[1][1] = this->ij[1][1] * fDivisor;
	aux.ij[1][2] = this->ij[1][2] * fDivisor;
	aux.ij[1][3] = this->ij[1][3] * fDivisor;
	aux.ij[2][0] = this->ij[2][0] * fDivisor;
	aux.ij[2][1] = this->ij[2][1] * fDivisor;
	aux.ij[2][2] = this->ij[2][2] * fDivisor;
	aux.ij[2][3] = this->ij[2][3] * fDivisor;

	return aux;
}

QMatrix3x4 QMatrix3x4::operator+(const QBaseMatrix3x4 &matrix) const
{
	QMatrix3x4 aux;

	aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] + matrix.ij[0][2];
	aux.ij[0][3] = this->ij[0][3] + matrix.ij[0][3];
	aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] + matrix.ij[1][2];
	aux.ij[1][3] = this->ij[1][3] + matrix.ij[1][3];
	aux.ij[2][0] = this->ij[2][0] + matrix.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] + matrix.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] + matrix.ij[2][2];
	aux.ij[2][3] = this->ij[2][3] + matrix.ij[2][3];

	return aux;
}

QMatrix3x4 QMatrix3x4::operator-(const QBaseMatrix3x4 &matrix) const
{
	QMatrix3x4 aux;

	aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
	aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
	aux.ij[0][2] = this->ij[0][2] - matrix.ij[0][2];
	aux.ij[0][3] = this->ij[0][3] - matrix.ij[0][3];
	aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
	aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];
	aux.ij[1][2] = this->ij[1][2] - matrix.ij[1][2];
	aux.ij[1][3] = this->ij[1][3] - matrix.ij[1][3];
	aux.ij[2][0] = this->ij[2][0] - matrix.ij[2][0];
	aux.ij[2][1] = this->ij[2][1] - matrix.ij[2][1];
	aux.ij[2][2] = this->ij[2][2] - matrix.ij[2][2];
	aux.ij[2][3] = this->ij[2][3] - matrix.ij[2][3];

	return aux;
}

QBaseMatrix3x3 QMatrix3x4::operator*(const QBaseMatrix4x3 &matrix) const
{
	QBaseMatrix3x3 aux;

	aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
	aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
	aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];

	aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
	aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
	aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];

	aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
	aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
	aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];

	return aux;
}

QBaseMatrix3x4 QMatrix3x4::operator*(const QBaseMatrix4x4 &matrix) const
{
	QBaseMatrix3x4 aux;

	aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
	aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
	aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];
	aux.ij[0][3] = this->ij[0][0] * matrix.ij[0][3] + this->ij[0][1] * matrix.ij[1][3] + this->ij[0][2] * matrix.ij[2][3] + this->ij[0][3] * matrix.ij[3][3];

	aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
	aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
	aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];
	aux.ij[1][3] = this->ij[1][0] * matrix.ij[0][3] + this->ij[1][1] * matrix.ij[1][3] + this->ij[1][2] * matrix.ij[2][3] + this->ij[1][3] * matrix.ij[3][3];

	aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
	aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
	aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];
	aux.ij[2][3] = this->ij[2][0] * matrix.ij[0][3] + this->ij[2][1] * matrix.ij[1][3] + this->ij[2][2] * matrix.ij[2][3] + this->ij[2][3] * matrix.ij[3][3];

	return aux;
}

string_q QMatrix3x4::ToString() const
{
    return QE_L("M3x4((") + SQFloat::ToString(this->ij[0][0]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[0][1]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[0][2]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[0][3]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[1][0]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[1][1]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[1][2]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[1][3]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[2][0]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[2][1]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[2][2]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[2][3]) + QE_L("))");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

