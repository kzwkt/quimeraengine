//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "QMatrix4x3.h"

#include "Assertions.h"
#include "QMatrix3x3.h"
#include "SQFloat.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;


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
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QMatrix4x3::QMatrix4x3()
{
}

QMatrix4x3::QMatrix4x3(const QMatrix4x3 &matrix) : QBaseMatrix4x3(matrix)
{
}

QMatrix4x3::QMatrix4x3(const QBaseMatrix4x3 &matrix) : QBaseMatrix4x3(matrix)
{
}

QMatrix4x3::QMatrix4x3(const float_q &fValueAll) : QBaseMatrix4x3(fValueAll)
{
}

QMatrix4x3::QMatrix4x3(const float_q &f00, const float_q &f01, const float_q &f02,
                       const float_q &f10, const float_q &f11, const float_q &f12,
                       const float_q &f20, const float_q &f21, const float_q &f22,
                       const float_q &f30, const float_q &f31, const float_q &f32) :
                            QBaseMatrix4x3(f00, f01, f02, f10, f11, f12, f20, f21, f22, f30, f31, f32)
{
}

QMatrix4x3::QMatrix4x3(const float_q* arValues) : QBaseMatrix4x3(arValues)
{
}

QMatrix4x3::QMatrix4x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) :
		                    QBaseMatrix4x3(row0, row1, row2, row3)
{
}


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

QMatrix4x3 operator*(const float_q &fScalar, const QMatrix4x3 &matrix)
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

QMatrix4x3& QMatrix4x3::operator*=(const float_q fScalar)
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
	QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero")

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

QMatrix4x3& QMatrix4x3::operator/=(const float_q &fScalar)
{
	QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero")

	const float_q &fDivisor = SQFloat::_1/fScalar;

	this->ij[0][0] *= fDivisor;
	this->ij[0][1] *= fDivisor;
	this->ij[0][2] *= fDivisor;
	this->ij[1][0] *= fDivisor;
	this->ij[1][1] *= fDivisor;
	this->ij[1][2] *= fDivisor;
	this->ij[2][0] *= fDivisor;
	this->ij[2][1] *= fDivisor;
	this->ij[2][2] *= fDivisor;
	this->ij[3][0] *= fDivisor;
	this->ij[3][1] *= fDivisor;
	this->ij[3][2] *= fDivisor;

	return *this;
}

QMatrix4x3& QMatrix4x3::operator+=(const QBaseMatrix4x3 &matrix)
{
	this->ij[0][0] += matrix.ij[0][0];
	this->ij[0][1] += matrix.ij[0][1];
	this->ij[0][2] += matrix.ij[0][2];
	this->ij[1][0] += matrix.ij[1][0];
	this->ij[1][1] += matrix.ij[1][1];
	this->ij[1][2] += matrix.ij[1][2];
	this->ij[2][0] += matrix.ij[2][0];
	this->ij[2][1] += matrix.ij[2][1];
	this->ij[2][2] += matrix.ij[2][2];
	this->ij[3][0] += matrix.ij[3][0];
	this->ij[3][1] += matrix.ij[3][1];
	this->ij[3][2] += matrix.ij[3][2];

	return *this;
}

QMatrix4x3& QMatrix4x3::operator-=(const QBaseMatrix4x3 &matrix)
{
	this->ij[0][0] -= matrix.ij[0][0];
	this->ij[0][1] -= matrix.ij[0][1];
	this->ij[0][2] -= matrix.ij[0][2];
	this->ij[1][0] -= matrix.ij[1][0];
	this->ij[1][1] -= matrix.ij[1][1];
	this->ij[1][2] -= matrix.ij[1][2];
	this->ij[2][0] -= matrix.ij[2][0];
	this->ij[2][1] -= matrix.ij[2][1];
	this->ij[2][2] -= matrix.ij[2][2];
	this->ij[3][0] -= matrix.ij[3][0];
	this->ij[3][1] -= matrix.ij[3][1];
	this->ij[3][2] -= matrix.ij[3][2];

	return *this;
}

QMatrix4x3& QMatrix4x3::operator=(const QBaseMatrix4x3 &matrix)
{
    QBaseMatrix4x3::operator=(matrix);
    return *this;
}

void QMatrix4x3::ResetToZero()
{
	this->ij[0][0] = this->ij[0][1] = this->ij[0][2] =
	this->ij[1][0] = this->ij[1][1] = this->ij[1][2] =
	this->ij[2][0] = this->ij[2][1] = this->ij[2][2] =
	this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SQFloat::_0;
}

void QMatrix4x3::ResetToIdentity()
{
	this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = SQFloat::_1;
    this->ij[0][1] = this->ij[0][2] =
	this->ij[1][0] = this->ij[1][2] =
	this->ij[2][0] = this->ij[2][1] =
	this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SQFloat::_0;
}

QBaseMatrix3x4 QMatrix4x3::Transpose() const
{
    return QBaseMatrix3x4(this->ij[0][0], this->ij[1][0], this->ij[2][0], this->ij[3][0],
                            this->ij[0][1], this->ij[1][1], this->ij[2][1], this->ij[3][1],
                            this->ij[0][2], this->ij[1][2], this->ij[2][2], this->ij[3][2]);
}

bool QMatrix4x3::IsZero() const
{
	return	SQFloat::IsZero(this->ij[0][0]) &&
			SQFloat::IsZero(this->ij[0][1]) &&
			SQFloat::IsZero(this->ij[0][2]) &&
			SQFloat::IsZero(this->ij[1][0]) &&
			SQFloat::IsZero(this->ij[1][1]) &&
			SQFloat::IsZero(this->ij[1][2]) &&
			SQFloat::IsZero(this->ij[2][0]) &&
			SQFloat::IsZero(this->ij[2][1]) &&
			SQFloat::IsZero(this->ij[2][2]) &&
			SQFloat::IsZero(this->ij[3][0]) &&
			SQFloat::IsZero(this->ij[3][1]) &&
			SQFloat::IsZero(this->ij[3][2]);
}

string_q QMatrix4x3::ToString() const
{
    return QE_L("M4x3(") + SQFloat::ToString(this->ij[0][0]) + QE_L(",") +
                           SQFloat::ToString(this->ij[0][1]) + QE_L(",") +
                           SQFloat::ToString(this->ij[0][2]) + QE_L(",") +
                           SQFloat::ToString(this->ij[1][0]) + QE_L(",") +
                           SQFloat::ToString(this->ij[1][1]) + QE_L(",") +
                           SQFloat::ToString(this->ij[1][2]) + QE_L(",") +
                           SQFloat::ToString(this->ij[2][0]) + QE_L(",") +
                           SQFloat::ToString(this->ij[2][1]) + QE_L(",") +
                           SQFloat::ToString(this->ij[2][2]) + QE_L(",") +
                           SQFloat::ToString(this->ij[3][0]) + QE_L(",") +
                           SQFloat::ToString(this->ij[3][1]) + QE_L(",") +
                           SQFloat::ToString(this->ij[3][2]) + QE_L(")");
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QMatrix4x3& QMatrix4x3::GetNullMatrix()
{
    static const QMatrix4x3 NULLMATRIX(SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0);
    return NULLMATRIX;
}

const QMatrix4x3& QMatrix4x3::GetIdentity()
{
    static const QMatrix4x3 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_1,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0);
    return IDENTITY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

