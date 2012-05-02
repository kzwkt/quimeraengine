// [TERMS&CONDITIONS]

#include "SQAngle.h"
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

QMatrix2x2 operator*(const float_q &fScalar, const QBaseMatrix2x2 &matrix)
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

    QE_ASSERT(fScalar != SQFloat::_0)

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

string_q QMatrix2x2::ToString() const
{
    return QE_L("M2x2((") + SQFloat::ToString(this->ij[0][0]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[0][1]) + QE_L(")(") +
                            SQFloat::ToString(this->ij[1][0]) + QE_L(",")  +
                            SQFloat::ToString(this->ij[1][1]) + QE_L("))");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

