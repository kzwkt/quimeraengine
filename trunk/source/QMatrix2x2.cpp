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

#include "QMatrix2x2.h"

#include "Assertions.h"
#include "SQAngle.h"
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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QMatrix2x2::QMatrix2x2()
{
}

QMatrix2x2::QMatrix2x2(const QMatrix2x2 &matrix) : QBaseMatrix2x2(matrix)
{
}

QMatrix2x2::QMatrix2x2(const QBaseMatrix2x2 &matrix) : QBaseMatrix2x2(matrix)
{
}

QMatrix2x2::QMatrix2x2(const float_q &fValueAll) : QBaseMatrix2x2(fValueAll)
{
}

QMatrix2x2::QMatrix2x2(const float_q &f00, const float_q &f01, const float_q &f10, const float_q &f11) :
                        QBaseMatrix2x2(f00, f01, f10, f11)
{
}

QMatrix2x2::QMatrix2x2(const float_q* arValues) : QBaseMatrix2x2(arValues)
{
}

QMatrix2x2::QMatrix2x2(const vf32_q &value) : QBaseMatrix2x2(value)
{
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

QMatrix2x2 operator*(const float_q &fScalar, const QMatrix2x2 &matrix)
{
    QMatrix2x2 aux;

    aux.ij[0][0] = fScalar * matrix.ij[0][0];
    aux.ij[0][1] = fScalar * matrix.ij[0][1];
    aux.ij[1][0] = fScalar * matrix.ij[1][0];
    aux.ij[1][1] = fScalar * matrix.ij[1][1];

    return aux;
}

QMatrix2x2 QMatrix2x2::operator*(const QBaseMatrix2x2 &matrix) const
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1];
    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1];

    return aux;
}

QMatrix2x2 QMatrix2x2::operator/(const float_q &fScalar) const
{

    QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * DIVISOR;
    aux.ij[0][1] = this->ij[0][1] * DIVISOR;
    aux.ij[1][0] = this->ij[1][0] * DIVISOR;
    aux.ij[1][1] = this->ij[1][1] * DIVISOR;

    return aux;
}

QMatrix2x2 QMatrix2x2::operator+(const QBaseMatrix2x2 &matrix) const
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];

    return aux;
}

QMatrix2x2 QMatrix2x2::operator-(const QBaseMatrix2x2 &matrix) const
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];

    return aux;
}

QMatrix2x2& QMatrix2x2::operator*=(const float_q fScalar)
{
    this->ij[0][0] *= fScalar;
    this->ij[0][1] *= fScalar;
    this->ij[1][0] *= fScalar;
    this->ij[1][1] *= fScalar;

    return *this;
}

QMatrix2x2& QMatrix2x2::operator*=(const QBaseMatrix2x2 &matrix)
{
    QMatrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1];
    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1];

    *this = aux;

    return *this;
}

QMatrix2x2& QMatrix2x2::operator/=(const float_q &fScalar)
{
    QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    this->ij[0][0] *= DIVISOR;
    this->ij[0][1] *= DIVISOR;
    this->ij[1][0] *= DIVISOR;
    this->ij[1][1] *= DIVISOR;

    return *this;
}

QMatrix2x2& QMatrix2x2::operator+=(const QBaseMatrix2x2 &matrix)
{
    this->ij[0][0] += matrix.ij[0][0];
    this->ij[0][1] += matrix.ij[0][1];
    this->ij[1][0] += matrix.ij[1][0];
    this->ij[1][1] += matrix.ij[1][1];

    return *this;
}

QMatrix2x2& QMatrix2x2::operator-=(const QBaseMatrix2x2 &matrix)
{
    this->ij[0][0] -= matrix.ij[0][0];
    this->ij[0][1] -= matrix.ij[0][1];
    this->ij[1][0] -= matrix.ij[1][0];
    this->ij[1][1] -= matrix.ij[1][1];

    return *this;
}

QMatrix2x2& QMatrix2x2::operator=(const QBaseMatrix2x2 &matrix)
{
    QBaseMatrix2x2::operator=(matrix);
    return *this;
}

void QMatrix2x2::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] =
    this->ij[1][0] = this->ij[1][1] = SQFloat::_0;
}

void QMatrix2x2::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = SQFloat::_1;
    this->ij[0][1] = this->ij[1][0] = SQFloat::_0;
}

QMatrix2x2 QMatrix2x2::Transpose() const
{
    return QMatrix2x2(this->ij[0][0], this->ij[1][0], this->ij[0][1], this->ij[1][1]);
}

bool QMatrix2x2::IsZero() const
{
    return  SQFloat::IsZero(this->ij[0][0]) &&
            SQFloat::IsZero(this->ij[0][1]) &&
            SQFloat::IsZero(this->ij[1][0]) &&
            SQFloat::IsZero(this->ij[1][1]);
}

bool QMatrix2x2::IsIdentity() const
{
    return  SQFloat::AreEqual(this->ij[0][0], SQFloat::_1) &&
            SQFloat::IsZero(this->ij[0][1]) &&
            SQFloat::IsZero(this->ij[1][0]) &&
            SQFloat::AreEqual(this->ij[1][1], SQFloat::_1);
}

float_q QMatrix2x2::GetDeterminant() const
{
    return this->ij[0][0] * this->ij[1][1] - this->ij[0][1] * this->ij[1][0];
}

QMatrix2x2 QMatrix2x2::Invert() const
{
    // We need inverse of determinant in calculus.
    const float_q INV_DET = SQFloat::_1 / this->GetDeterminant();

    return QMatrix2x2( INV_DET * this->ij[1][1],
                      -INV_DET * this->ij[0][1],
                      -INV_DET * this->ij[1][0],
                       INV_DET * this->ij[0][0] ); 
}

bool QMatrix2x2::HasInverse() const
{
    // If Determinant is 0, this matrix has not inverse.
    return SQFloat::IsNotZero(this->GetDeterminant());
}

string_q QMatrix2x2::ToString() const
{
    return string_q("M2x2(") + SQFloat::ToString(this->ij[0][0]) + QE_L(",") +
                               SQFloat::ToString(this->ij[0][1]) + QE_L(",") +
                               SQFloat::ToString(this->ij[1][0]) + QE_L(",") +
                               SQFloat::ToString(this->ij[1][1]) + QE_L(")");
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QMatrix2x2& QMatrix2x2::GetNullMatrix()
{
    static const QMatrix2x2 NULLMATRIX(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    return NULLMATRIX;
}

const QMatrix2x2& QMatrix2x2::GetIdentity()
{
    static const QMatrix2x2 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    return IDENTITY;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

