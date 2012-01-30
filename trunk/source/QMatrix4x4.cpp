// [TERMS&CONDITIONS]

#include "SQAngle.h"
#include "QMatrix4x4.h"

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

QMatrix4x4 QMatrix4x4::operator*(const float_q &fScalar) const
{
	QMatrix4x4 aux;

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
	aux.ij[3][0] = fScalar * this->ij[3][0];
	aux.ij[3][1] = fScalar * this->ij[3][1];
	aux.ij[3][2] = fScalar * this->ij[3][2];
	aux.ij[3][3] = fScalar * this->ij[3][3];

	return aux;
}

QMatrix4x4 operator*(const float_q &fScalar, const QBaseMatrix4x4 &matrix)
{
	QMatrix4x4 aux;

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
	aux.ij[3][0] = fScalar * matrix.ij[3][0];
	aux.ij[3][1] = fScalar * matrix.ij[3][1];
	aux.ij[3][2] = fScalar * matrix.ij[3][2];
	aux.ij[3][3] = fScalar * matrix.ij[3][3];

	return aux;
}

QMatrix4x4 QMatrix4x4::operator*(const QBaseMatrix4x4 &matrix) const
{
	QMatrix4x4 aux;

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

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];
	aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3] + this->ij[3][3] * matrix.ij[3][3];

	return aux;
}

QBaseMatrix4x3 QMatrix4x4::operator*(const QBaseMatrix4x3 &matrix) const
{
    QBaseMatrix4x3 aux;

	aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
	aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
	aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];

	aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
	aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
	aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];

	aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
	aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
	aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];

	return aux;
}

QMatrix4x4 QMatrix4x4::operator/(const float_q &fScalar) const
{

	QE_ASSERT(fScalar != SQFloat::_0)

	const float_q &fDivisor = SQFloat::_1/fScalar;

	QMatrix4x4 aux;

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
	aux.ij[3][0] = this->ij[3][0] * fDivisor;
	aux.ij[3][1] = this->ij[3][1] * fDivisor;
	aux.ij[3][2] = this->ij[3][2] * fDivisor;
	aux.ij[3][3] = this->ij[3][3] * fDivisor;

	return aux;
}

QMatrix4x4 QMatrix4x4::operator+(const QBaseMatrix4x4 &matrix) const
{
	QMatrix4x4 aux;

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
	aux.ij[3][0] = this->ij[3][0] + matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] + matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] + matrix.ij[3][2];
	aux.ij[3][3] = this->ij[3][3] + matrix.ij[3][3];

	return aux;
}

QMatrix4x4 QMatrix4x4::operator-(const QBaseMatrix4x4 &matrix) const
{
	QMatrix4x4 aux;

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
	aux.ij[3][0] = this->ij[3][0] - matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][1] - matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][2] - matrix.ij[3][2];
	aux.ij[3][3] = this->ij[3][3] - matrix.ij[3][3];

	return aux;
}

QMatrix4x4& QMatrix4x4::operator*=(const QBaseMatrix4x4 &matrix)
{
	QMatrix4x4 aux;

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

	aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
	aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
	aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];
	aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3] + this->ij[3][3] * matrix.ij[3][3];

	*this = aux;

	return *this;
}

void QMatrix4x4::Transpose()
{
	QMatrix4x4 aux;

	aux.ij[0][0] = this->ij[0][0];
	aux.ij[0][1] = this->ij[1][0];
	aux.ij[0][2] = this->ij[2][0];
	aux.ij[0][3] = this->ij[3][0];
	aux.ij[1][0] = this->ij[0][1];
	aux.ij[1][1] = this->ij[1][1];
	aux.ij[1][2] = this->ij[2][1];
	aux.ij[1][3] = this->ij[3][1];
	aux.ij[2][0] = this->ij[0][2];
	aux.ij[2][1] = this->ij[1][2];
	aux.ij[2][2] = this->ij[2][2];
	aux.ij[2][3] = this->ij[3][2];
	aux.ij[3][0] = this->ij[0][3];
	aux.ij[3][1] = this->ij[1][3];
	aux.ij[3][2] = this->ij[2][3];
	aux.ij[3][3] = this->ij[3][3];

	*this = aux;
}

float_q QMatrix4x4::GetDeterminant() const
{
	// Binary products are stored in vars to avoid unnecesary repetitions
	// (each binary product appears 2 times in determinant expresion)
	const float_q& A = this->ij[1][1] * this->ij[2][2];
	const float_q& B = this->ij[1][2] * this->ij[2][3];
	const float_q& C = this->ij[1][3] * this->ij[2][1];
	const float_q& D = this->ij[1][3] * this->ij[2][2];
	const float_q& E = this->ij[1][1] * this->ij[2][3];
	const float_q& F = this->ij[1][2] * this->ij[2][1];
	const float_q& G = this->ij[1][0] * this->ij[2][2];
	const float_q& H = this->ij[1][3] * this->ij[2][0];
	const float_q& I = this->ij[1][0] * this->ij[2][3];
	const float_q& J = this->ij[1][2] * this->ij[2][0];
	const float_q& K = this->ij[1][0] * this->ij[2][1];
	const float_q& L = this->ij[1][1] * this->ij[2][0];

	return this->ij[0][0] * (	A * this->ij[3][3] + B * this->ij[3][1] + C * this->ij[3][2] -
								D * this->ij[3][1] - E * this->ij[3][2] - F * this->ij[3][3] ) -
			this->ij[0][1] * (	G * this->ij[3][3] + B * this->ij[3][0] + H * this->ij[3][2] -
								D * this->ij[3][0] - I * this->ij[3][2] - J * this->ij[3][3] ) +
			this->ij[0][2] * (	K * this->ij[3][3] + E * this->ij[3][0] + H * this->ij[3][1] -
								C * this->ij[3][0] - I * this->ij[3][1] - L * this->ij[3][3] ) -
			this->ij[0][3] * (	K * this->ij[3][2] + A * this->ij[3][0] + J * this->ij[3][1] -
								F * this->ij[3][0] - G * this->ij[3][1] - L * this->ij[3][2] );
}

bool QMatrix4x4::Reverse()
{
	// Special case where matrix is identity. Then inverse of the matrix is itself.
	if (this->IsIdentity())
	{
		return true;
	}

	// Gets Determinant.
	float_q fDet = this->GetDeterminant();

	// If Determinant is 0, this matrix has not inverse.
	if (SQFloat::IsZero(fDet))
		return false;

	// We need inverse of determinant in calculus.
	fDet = SQFloat::_1/fDet;

	// Binary products are stored in vars to avoid unnecesary repetitions
	// (each binary product appears 4 times in inverse expresion)
	const float_q& A = this->ij[0][0] * this->ij[1][1];
	const float_q& B = this->ij[2][2] * this->ij[3][3];
	const float_q& C = this->ij[0][3] * this->ij[1][2];
	const float_q& D = this->ij[2][1] * this->ij[3][0];
	const float_q& E = this->ij[0][1] * this->ij[1][0];
	const float_q& F = this->ij[0][2] * this->ij[1][3];
	const float_q& G = this->ij[2][3] * this->ij[3][2];
	const float_q& H = this->ij[2][0] * this->ij[3][1];
	const float_q& I = this->ij[2][3] * this->ij[3][1];
	const float_q& J = this->ij[2][1] * this->ij[3][2];
	const float_q& K = this->ij[2][2] * this->ij[3][1];
	const float_q& L = this->ij[2][1] * this->ij[3][3];
	const float_q& M = this->ij[2][3] * this->ij[3][0];
	const float_q& N = this->ij[2][0] * this->ij[3][2];
	const float_q& O = this->ij[2][2] * this->ij[3][0];
	const float_q& P = this->ij[2][0] * this->ij[3][3];
	const float_q& Q = this->ij[0][1] * this->ij[1][2];
	const float_q& R = this->ij[0][3] * this->ij[1][1];
	const float_q& S = this->ij[0][1] * this->ij[1][3];
	const float_q& T = this->ij[0][2] * this->ij[1][1];
	const float_q& U = this->ij[0][0] * this->ij[1][2];
	const float_q& V = this->ij[0][3] * this->ij[1][0];
	const float_q& W = this->ij[0][0] * this->ij[1][3];
	const float_q& X = this->ij[0][2] * this->ij[1][0];

	QMatrix4x4 aux;

	// 1st column of inverse

	aux.ij[0][0] =  fDet * (this->ij[1][1] * B + this->ij[1][2] * I + this->ij[1][3] * J -
							this->ij[1][3] * K - this->ij[1][1] * G - this->ij[1][2] * L );

	aux.ij[1][0] = -fDet * (this->ij[1][0] * B + this->ij[1][2] * M + this->ij[1][3] * N -
							this->ij[1][3] * O - this->ij[1][0] * G - this->ij[1][2] * P );

	aux.ij[2][0] =  fDet * (this->ij[1][0] * L + this->ij[1][1] * M + this->ij[1][3] * H -
							this->ij[1][3] * D - this->ij[1][0] * I - this->ij[1][1] * P );

	aux.ij[3][0] = -fDet * (this->ij[1][0] * J + this->ij[1][1] * O + this->ij[1][2] * H -
							this->ij[1][2] * D - this->ij[1][0] * K - this->ij[1][1] * N );

	// 2nd column of inverse

	aux.ij[0][1] = -fDet * (this->ij[0][1] * B + this->ij[0][2] * I + this->ij[0][3] * J -
							this->ij[0][3] * K - this->ij[0][1] * G - this->ij[0][2] * L );

	aux.ij[1][1] =  fDet * (this->ij[0][0] * B + this->ij[0][2] * M + this->ij[0][3] * N -
							this->ij[0][3] * O - this->ij[0][0] * G - this->ij[0][2] * P );

	aux.ij[2][1] = -fDet * (this->ij[0][0] * L + this->ij[0][1] * M + this->ij[0][3] * H -
							this->ij[0][3] * D - this->ij[0][0] * I - this->ij[0][1] * P );

	aux.ij[3][1] =  fDet * (this->ij[0][0] * J + this->ij[0][1] * O + this->ij[0][2] * H -
							this->ij[0][2] * D - this->ij[0][0] * K - this->ij[0][1] * N );

	// 3rd column of inverse

	aux.ij[0][2] =  fDet * (Q * this->ij[3][3] + F * this->ij[3][1] + R * this->ij[3][2] -
							C * this->ij[3][1] - S * this->ij[3][2] - T * this->ij[3][3] );

	aux.ij[1][2] = -fDet * (U * this->ij[3][3] + F * this->ij[3][0] + V * this->ij[3][2] -
							C * this->ij[3][0] - W * this->ij[3][2] - X * this->ij[3][3] );

	aux.ij[2][2] =  fDet * (A * this->ij[3][3] + S * this->ij[3][0] + V * this->ij[3][1] -
							R * this->ij[3][0] - W * this->ij[3][1] - E * this->ij[3][3] );

	aux.ij[3][2] = -fDet * (A * this->ij[3][2] + Q * this->ij[3][0] + X * this->ij[3][1] -
							T * this->ij[3][0] - U * this->ij[3][1] - E * this->ij[3][2] );

	// 4rd column of inverse

	aux.ij[0][3] = -fDet * (Q * this->ij[2][3] + F * this->ij[2][1] + R * this->ij[2][2] -
							C * this->ij[2][1] - S * this->ij[2][2] - T * this->ij[2][3] );

	aux.ij[1][3] =  fDet * (U * this->ij[2][3] + F * this->ij[2][0] + V * this->ij[2][2] -
							C * this->ij[2][0] - W * this->ij[2][2] - X * this->ij[2][3] );

	aux.ij[2][3] = -fDet * (A * this->ij[2][3] + S * this->ij[2][0] + V * this->ij[2][1] -
							R * this->ij[2][0] - W * this->ij[2][1] - E * this->ij[2][3] );

	aux.ij[3][3] =  fDet * (A * this->ij[2][2] + Q * this->ij[2][0] + X * this->ij[2][1] -
							T * this->ij[2][0] - U * this->ij[2][1] - E * this->ij[2][2] );

	*this = aux;

	return true;

}

string_q QMatrix4x4::ToString() const
{
	return QE_L("M4x4((") + SQFloat::ToString(this->ij[0][0]) + QE_L(",") +
                            SQFloat::ToString(this->ij[0][1]) + QE_L(",") +
                            SQFloat::ToString(this->ij[0][2]) + QE_L(",") +
                            SQFloat::ToString(this->ij[0][3]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[1][0]) + QE_L(",") +
                            SQFloat::ToString(this->ij[1][1]) + QE_L(",") +
                            SQFloat::ToString(this->ij[1][2]) + QE_L(",") +
                            SQFloat::ToString(this->ij[1][3]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[2][0]) + QE_L(",") +
                            SQFloat::ToString(this->ij[2][1]) + QE_L(",") +
                            SQFloat::ToString(this->ij[2][2]) + QE_L(",") +
                            SQFloat::ToString(this->ij[2][3]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[3][0]) + QE_L(",") +
                            SQFloat::ToString(this->ij[3][1]) + QE_L(",") +
                            SQFloat::ToString(this->ij[3][2]) + QE_L(",") +
                            SQFloat::ToString(this->ij[3][3]) + QE_L("))");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

