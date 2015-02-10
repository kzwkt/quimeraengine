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

#include "QMatrix4x4.h"

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

QMatrix4x4::QMatrix4x4()
{
}

QMatrix4x4::QMatrix4x4(const QMatrix4x4 &matrix) : QBaseMatrix4x4(matrix)
{
}

QMatrix4x4::QMatrix4x4(const QBaseMatrix4x4 &matrix) : QBaseMatrix4x4(matrix)
{
}

QMatrix4x4::QMatrix4x4(const float_q fValueAll) : QBaseMatrix4x4(fValueAll)
{
}

QMatrix4x4::QMatrix4x4(const float_q f00, const float_q f01, const float_q f02, const float_q f03,
                       const float_q f10, const float_q f11, const float_q f12, const float_q f13,
                       const float_q f20, const float_q f21, const float_q f22, const float_q f23,
                       const float_q f30, const float_q f31, const float_q f32, const float_q f33) :
                            QBaseMatrix4x4(f00, f01, f02, f03, f10, f11, f12, f13,
                                           f20, f21, f22, f23, f30, f31, f32, f33)
{
}

QMatrix4x4::QMatrix4x4(const float_q* arValues) : QBaseMatrix4x4(arValues)
{
}

QMatrix4x4::QMatrix4x4(const vf32_q row0, const vf32_q row1, const vf32_q row2, const vf32_q &row3) :
                            QBaseMatrix4x4(row0, row1, row2, row3)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QMatrix4x4 QMatrix4x4::operator*(const float_q fScalar) const
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

QMatrix4x4 operator*(const float_q fScalar, const QMatrix4x4 &matrix)
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

QMatrix4x4 QMatrix4x4::operator/(const float_q fScalar) const
{

    QE_ASSERT_WARNING(fScalar != SQFloat::_0, "Input value must not equal zero");

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

QMatrix4x4& QMatrix4x4::operator*=(const float_q fScalar)
{
    *this = fScalar * *this;
    return *this;
}

QMatrix4x4& QMatrix4x4::operator/=(const float_q fScalar)
{
    QE_ASSERT_WARNING(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &fDivisor = SQFloat::_1/fScalar;

    this->ij[0][0] *= fDivisor;
    this->ij[0][1] *= fDivisor;
    this->ij[0][2] *= fDivisor;
    this->ij[0][3] *= fDivisor;
    this->ij[1][0] *= fDivisor;
    this->ij[1][1] *= fDivisor;
    this->ij[1][2] *= fDivisor;
    this->ij[1][3] *= fDivisor;
    this->ij[2][0] *= fDivisor;
    this->ij[2][1] *= fDivisor;
    this->ij[2][2] *= fDivisor;
    this->ij[2][3] *= fDivisor;
    this->ij[3][0] *= fDivisor;
    this->ij[3][1] *= fDivisor;
    this->ij[3][2] *= fDivisor;
    this->ij[3][3] *= fDivisor;

    return *this;
}

QMatrix4x4& QMatrix4x4::operator+=(const QBaseMatrix4x4 &matrix)
{
    this->ij[0][0] += matrix.ij[0][0];
    this->ij[0][1] += matrix.ij[0][1];
    this->ij[0][2] += matrix.ij[0][2];
    this->ij[0][3] += matrix.ij[0][3];
    this->ij[1][0] += matrix.ij[1][0];
    this->ij[1][1] += matrix.ij[1][1];
    this->ij[1][2] += matrix.ij[1][2];
    this->ij[1][3] += matrix.ij[1][3];
    this->ij[2][0] += matrix.ij[2][0];
    this->ij[2][1] += matrix.ij[2][1];
    this->ij[2][2] += matrix.ij[2][2];
    this->ij[2][3] += matrix.ij[2][3];
    this->ij[3][0] += matrix.ij[3][0];
    this->ij[3][1] += matrix.ij[3][1];
    this->ij[3][2] += matrix.ij[3][2];
    this->ij[3][3] += matrix.ij[3][3];

    return *this;
}

QMatrix4x4& QMatrix4x4::operator-=(const QBaseMatrix4x4 &matrix)
{
    this->ij[0][0] -= matrix.ij[0][0];
    this->ij[0][1] -= matrix.ij[0][1];
    this->ij[0][2] -= matrix.ij[0][2];
    this->ij[0][3] -= matrix.ij[0][3];
    this->ij[1][0] -= matrix.ij[1][0];
    this->ij[1][1] -= matrix.ij[1][1];
    this->ij[1][2] -= matrix.ij[1][2];
    this->ij[1][3] -= matrix.ij[1][3];
    this->ij[2][0] -= matrix.ij[2][0];
    this->ij[2][1] -= matrix.ij[2][1];
    this->ij[2][2] -= matrix.ij[2][2];
    this->ij[2][3] -= matrix.ij[2][3];
    this->ij[3][0] -= matrix.ij[3][0];
    this->ij[3][1] -= matrix.ij[3][1];
    this->ij[3][2] -= matrix.ij[3][2];
    this->ij[3][3] -= matrix.ij[3][3];

    return *this;
}

QMatrix4x4& QMatrix4x4::operator=(const QBaseMatrix4x4 &matrix)
{
    QBaseMatrix4x4::operator=(matrix);
    return *this;
}

void QMatrix4x4::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = this->ij[2][3] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = this->ij[3][3] = SQFloat::_0;
}

void QMatrix4x4::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = this->ij[3][3] = SQFloat::_1;

    this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][3] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SQFloat::_0;
}

QMatrix4x4 QMatrix4x4::Transpose() const
{
    return QMatrix4x4(this->ij[0][0], this->ij[1][0], this->ij[2][0], this->ij[3][0],
                      this->ij[0][1], this->ij[1][1], this->ij[2][1], this->ij[3][1],
                      this->ij[0][2], this->ij[1][2], this->ij[2][2], this->ij[3][2],
                      this->ij[0][3], this->ij[1][3], this->ij[2][3], this->ij[3][3]);
}

bool QMatrix4x4::IsZero() const
{
    return    SQFloat::IsZero(this->ij[0][0]) &&
            SQFloat::IsZero(this->ij[0][1]) &&
            SQFloat::IsZero(this->ij[0][2]) &&
            SQFloat::IsZero(this->ij[0][3]) &&
            SQFloat::IsZero(this->ij[1][0]) &&
            SQFloat::IsZero(this->ij[1][1]) &&
            SQFloat::IsZero(this->ij[1][2]) &&
            SQFloat::IsZero(this->ij[1][3]) &&
            SQFloat::IsZero(this->ij[2][0]) &&
            SQFloat::IsZero(this->ij[2][1]) &&
            SQFloat::IsZero(this->ij[2][2]) &&
            SQFloat::IsZero(this->ij[2][3]) &&
            SQFloat::IsZero(this->ij[3][0]) &&
            SQFloat::IsZero(this->ij[3][1]) &&
            SQFloat::IsZero(this->ij[3][2]) &&
            SQFloat::IsZero(this->ij[3][3]);
}

bool QMatrix4x4::IsIdentity() const
{
    return    SQFloat::AreEqual(this->ij[0][0], SQFloat::_1) &&
            SQFloat::IsZero(this->ij[0][1]) &&
            SQFloat::IsZero(this->ij[0][2]) &&
            SQFloat::IsZero(this->ij[0][3]) &&
            SQFloat::IsZero(this->ij[1][0]) &&
            SQFloat::AreEqual(this->ij[1][1], SQFloat::_1) &&
            SQFloat::IsZero(this->ij[1][2]) &&
            SQFloat::IsZero(this->ij[1][3]) &&
            SQFloat::IsZero(this->ij[2][0]) &&
            SQFloat::IsZero(this->ij[2][1]) &&
            SQFloat::AreEqual(this->ij[2][2], SQFloat::_1) &&
            SQFloat::IsZero(this->ij[2][3]) &&
            SQFloat::IsZero(this->ij[3][0]) &&
            SQFloat::IsZero(this->ij[3][1]) &&
            SQFloat::IsZero(this->ij[3][2]) &&
            SQFloat::AreEqual(this->ij[3][3], SQFloat::_1);
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

    return this->ij[0][0] * (    A * this->ij[3][3] + B * this->ij[3][1] + C * this->ij[3][2] -
                                D * this->ij[3][1] - E * this->ij[3][2] - F * this->ij[3][3] ) -
            this->ij[0][1] * (    G * this->ij[3][3] + B * this->ij[3][0] + H * this->ij[3][2] -
                                D * this->ij[3][0] - I * this->ij[3][2] - J * this->ij[3][3] ) +
            this->ij[0][2] * (    K * this->ij[3][3] + E * this->ij[3][0] + H * this->ij[3][1] -
                                C * this->ij[3][0] - I * this->ij[3][1] - L * this->ij[3][3] ) -
            this->ij[0][3] * (    K * this->ij[3][2] + A * this->ij[3][0] + J * this->ij[3][1] -
                                F * this->ij[3][0] - G * this->ij[3][1] - L * this->ij[3][2] );
}

QMatrix4x4 QMatrix4x4::Invert() const
{
    // Based on http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

    // The results will be wrong when the determinant equals zero
    QE_ASSERT_WARNING( this->GetDeterminant() != SQFloat::_0, "Matrices whose determinant equals zero do not have inverse" );

    // Gets the inverse of the Determinant.
    const float_q fInvDet = SQFloat::_1 / this->GetDeterminant();

    // Binary products are stored in vars to avoid unnecesary repetitions
    // (each binary product appears 4 times in inverse expresion)
    const float_q& fA = this->ij[0][0] * this->ij[1][1];
    const float_q& fB = this->ij[2][2] * this->ij[3][3];
    const float_q& fC = this->ij[0][3] * this->ij[1][2];
    const float_q& fD = this->ij[2][1] * this->ij[3][0];
    const float_q& fE = this->ij[0][1] * this->ij[1][0];
    const float_q& fF = this->ij[0][2] * this->ij[1][3];
    const float_q& fG = this->ij[2][3] * this->ij[3][2];
    const float_q& fH = this->ij[2][0] * this->ij[3][1];
    const float_q& fI = this->ij[2][3] * this->ij[3][1];
    const float_q& fJ = this->ij[2][1] * this->ij[3][2];
    const float_q& fK = this->ij[2][2] * this->ij[3][1];
    const float_q& fL = this->ij[2][1] * this->ij[3][3];
    const float_q& fM = this->ij[2][3] * this->ij[3][0];
    const float_q& fN = this->ij[2][0] * this->ij[3][2];
    const float_q& fO = this->ij[2][2] * this->ij[3][0];
    const float_q& fP = this->ij[2][0] * this->ij[3][3];
    const float_q& fQ = this->ij[0][1] * this->ij[1][2];
    const float_q& fR = this->ij[0][3] * this->ij[1][1];
    const float_q& fS = this->ij[0][1] * this->ij[1][3];
    const float_q& fT = this->ij[0][2] * this->ij[1][1];
    const float_q& fU = this->ij[0][0] * this->ij[1][2];
    const float_q& fV = this->ij[0][3] * this->ij[1][0];
    const float_q& fW = this->ij[0][0] * this->ij[1][3];
    const float_q& fX = this->ij[0][2] * this->ij[1][0];

    return QMatrix4x4( fInvDet * (this->ij[1][1] * fB + this->ij[1][2] * fI + this->ij[1][3] * fJ -
                                  this->ij[1][1] * fG - this->ij[1][2] * fL - this->ij[1][3] * fK ),
                       fInvDet * (this->ij[0][1] * fG + this->ij[0][2] * fL + this->ij[0][3] * fK -
                                  this->ij[0][1] * fB - this->ij[0][2] * fI - this->ij[0][3] * fJ ),
                       fInvDet * (fQ * this->ij[3][3] + fF * this->ij[3][1] + fR * this->ij[3][2] -
                                  fS * this->ij[3][2] - fT * this->ij[3][3] - fC * this->ij[3][1] ),
                       fInvDet * (fS * this->ij[2][2] + fT * this->ij[2][3] + fC * this->ij[2][1] -
                                  fQ * this->ij[2][3] - fF * this->ij[2][1] - fR * this->ij[2][2] ),
                       fInvDet * (this->ij[1][0] * fG + this->ij[1][2] * fP + this->ij[1][3] * fO -
                                  this->ij[1][0] * fB - this->ij[1][2] * fM - this->ij[1][3] * fN ),
                       fInvDet * (this->ij[0][0] * fB + this->ij[0][2] * fM + this->ij[0][3] * fN -
                                  this->ij[0][0] * fG - this->ij[0][2] * fP - this->ij[0][3] * fO ),
                       fInvDet * (fW * this->ij[3][2] + fX * this->ij[3][3] + fC * this->ij[3][0] -
                                  fU * this->ij[3][3] - fF * this->ij[3][0] - fV * this->ij[3][2] ),
                       fInvDet * (fU * this->ij[2][3] + fF * this->ij[2][0] + fV * this->ij[2][2] -
                                  fW * this->ij[2][2] - fX * this->ij[2][3] - fC * this->ij[2][0] ),
                       fInvDet * (this->ij[1][0] * fL + this->ij[1][1] * fM + this->ij[1][3] * fH -
                                  this->ij[1][0] * fI - this->ij[1][1] * fP - this->ij[1][3] * fD ),
                       fInvDet * (this->ij[0][0] * fI + this->ij[0][1] * fP + this->ij[0][3] * fD -
                                  this->ij[0][0] * fL - this->ij[0][1] * fM - this->ij[0][3] * fH ),
                       fInvDet * (fA * this->ij[3][3] + fS * this->ij[3][0] + fV * this->ij[3][1] -
                                  fW * this->ij[3][1] - fE * this->ij[3][3] - fR * this->ij[3][0] ),
                       fInvDet * (fW * this->ij[2][1] + fE * this->ij[2][3] + fR * this->ij[2][0] -
                                  fA * this->ij[2][3] - fS * this->ij[2][0] - fV * this->ij[2][1] ),
                       fInvDet * (this->ij[1][0] * fK + this->ij[1][1] * fN + this->ij[1][2] * fD -
                                  this->ij[1][0] * fJ - this->ij[1][1] * fO - this->ij[1][2] * fH ),
                       fInvDet * (this->ij[0][0] * fJ + this->ij[0][1] * fO + this->ij[0][2] * fH -
                                  this->ij[0][0] * fK - this->ij[0][1] * fN - this->ij[0][2] * fD ),
                       fInvDet * (fU * this->ij[3][1] + fE * this->ij[3][2] + fT * this->ij[3][0] -
                                  fA * this->ij[3][2] - fQ * this->ij[3][0] - fX * this->ij[3][1] ),
                       fInvDet * (fA * this->ij[2][2] + fQ * this->ij[2][0] + fX * this->ij[2][1] -
                                  fU * this->ij[2][1] - fE * this->ij[2][2] - fT * this->ij[2][0] ));
}

bool QMatrix4x4::HasInverse() const
{
    // If Determinant is 0, this matrix has not inverse.
    return SQFloat::IsNotZero(this->GetDeterminant());
}

string_q QMatrix4x4::ToString() const
{
    static const string_q STRING_PREFIX("M4x4(");
    static const string_q STRING_COMMA(",");
    static const string_q STRING_END(")");

    string_q strOutput = STRING_PREFIX;
    strOutput.Append(this->ij[0][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][3]);
    strOutput.Append(STRING_END);

    return strOutput;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QMatrix4x4& QMatrix4x4::GetNullMatrix()
{
    static const QMatrix4x4 NULLMATRIX(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                       SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                       SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                       SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    return NULLMATRIX;
}

const QMatrix4x4& QMatrix4x4::GetIdentity()
{
    static const QMatrix4x4 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                     SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                     SQFloat::_0, SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                     SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    return IDENTITY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

