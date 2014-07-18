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

#include "QDualQuaternion.h"

#include "Assertions.h"
#include "QBaseVector3.h"
#include "QBaseVector4.h"


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

QDualQuaternion::QDualQuaternion()
{
}

QDualQuaternion::QDualQuaternion(const QDualQuaternion &dualQuat) : QBaseDualQuaternion(dualQuat)
{
}

QDualQuaternion::QDualQuaternion(const QBaseDualQuaternion &dualQuat) : QBaseDualQuaternion(dualQuat)
{
}

QDualQuaternion::QDualQuaternion(const QBaseQuaternion &qReal, const QBaseQuaternion &qDual) : QBaseDualQuaternion(qReal, qDual)
{
}

QDualQuaternion::QDualQuaternion(const QBaseQuaternion &qRotation, const QBaseVector3 &vTranslation)
{
    QDualQuaternionImp(qRotation, vTranslation);
}

QDualQuaternion::QDualQuaternion(const QBaseQuaternion &qRotation, const QBaseVector4 &vTranslation)
{
    QDualQuaternionImp(qRotation, vTranslation);
}

QDualQuaternion::QDualQuaternion(const QBaseVector3 &vTranslation, const QBaseQuaternion &qRotation)
{
    QDualQuaternionImp(vTranslation, qRotation);
}

QDualQuaternion::QDualQuaternion(const QBaseVector4 &vTranslation, const QBaseQuaternion &qRotation)
{
    QDualQuaternionImp(vTranslation, qRotation);
}

QDualQuaternion::QDualQuaternion(const float_q *arValuesReal, const float_q *arValuesDual)
{
    QE_ASSERT(arValuesReal != null_q && arValuesDual != null_q, "Input arrays must not be null");

    this->r = QQuaternion(arValuesReal[0], arValuesReal[1], arValuesReal[2], arValuesReal[3]);
    this->d = QQuaternion(arValuesDual[0], arValuesDual[1], arValuesDual[2], arValuesDual[3]);
}

template <class VectorType>
void QDualQuaternion::QDualQuaternionImp(const QBaseQuaternion &qRotation, const VectorType &vTranslation)
{
    QDualQuaternion rotation(qRotation, QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));
    QDualQuaternion translation(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                QBaseQuaternion(vTranslation.x * SQFloat::_0_5, vTranslation.y * SQFloat::_0_5, vTranslation.z * SQFloat::_0_5, SQFloat::_0));

    *this = translation * rotation;
}

template <class VectorType>
void QDualQuaternion::QDualQuaternionImp(const VectorType &vTranslation, const QBaseQuaternion &qRotation)
{
    QDualQuaternion rotation(qRotation, QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));
    QDualQuaternion translation(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                QBaseQuaternion(vTranslation.x * SQFloat::_0_5, vTranslation.y * SQFloat::_0_5, vTranslation.z * SQFloat::_0_5, SQFloat::_0));

    *this = rotation * translation;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QDualQuaternion QDualQuaternion::operator+(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r + dualQuat.r), QBaseQuaternion(this->d + dualQuat.d));
}

QDualQuaternion QDualQuaternion::operator-(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r - dualQuat.r), QBaseQuaternion(this->d - dualQuat.d));
}

QDualQuaternion QDualQuaternion::operator*(const QBaseDualQuaternion &dualQuat) const
{
    return QDualQuaternion(QBaseQuaternion(this->r * dualQuat.r), QBaseQuaternion(this->r * dualQuat.d + this->d * dualQuat.r));
}

QDualQuaternion QDualQuaternion::operator*(const float_q &fScalar) const
{
    return QDualQuaternion(QBaseQuaternion(this->r * fScalar), QBaseQuaternion(this->d * fScalar));
}

QDualQuaternion operator*(const float_q &fScalar, const QDualQuaternion &dualQuat)
{
    return QDualQuaternion(QBaseQuaternion(dualQuat.r * fScalar), QBaseQuaternion(dualQuat.d * fScalar));
}

QDualQuaternion QDualQuaternion::operator*(const QBaseVector3 &vVector) const
{
    // Vector3 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                         QBaseQuaternion(vVector.x, vVector.y, vVector.z, SQFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator*(const QBaseVector4 &vVector) const
{
    // Vector4 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                         QBaseQuaternion(vVector.x, vVector.y, vVector.z, SQFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0, "The input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QDualQuaternion(QBaseQuaternion(this->r * DIVISOR), QBaseQuaternion(this->d * DIVISOR));
}

QDualQuaternion& QDualQuaternion::operator+=(const QBaseDualQuaternion &dualQuat)
{
    this->r += dualQuat.r;
    this->d += dualQuat.d;

    return *this;
}

QDualQuaternion& QDualQuaternion::operator-=(const QBaseDualQuaternion &dualQuat)
{
    this->r -= dualQuat.r;
    this->d -= dualQuat.d;

    return *this;
}

QDualQuaternion& QDualQuaternion::operator*=(const QBaseDualQuaternion &dualQuat)
{
    QDualQuaternion aux(*this);

    this->r = aux.r * dualQuat.r;
    this->d = aux.r * dualQuat.d + aux.d * dualQuat.r;

    return *this;
}

QDualQuaternion& QDualQuaternion::operator*=(const float_q fScalar)
{
    this->r *= fScalar;
    this->d *= fScalar;

    return *this;
}

QDualQuaternion& QDualQuaternion::operator/=(const float_q &fScalar)
{
    // Checkout to avoid division by zero.
    QE_ASSERT(fScalar != SQFloat::_0, "The input array must not be null");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    this->r *= DIVISOR;
    this->d *= DIVISOR;

    return *this;
}

QDualQuaternion& QDualQuaternion::operator=(const QBaseDualQuaternion &dualQuat)
{
    QBaseDualQuaternion::operator=(dualQuat);
    return *this;
}

void QDualQuaternion::ResetToZero()
{
    this->r.ResetToZero();
    this->d.ResetToZero();
}

void QDualQuaternion::ResetToIdentity()
{
    this->r.ResetToIdentity();
    this->d.ResetToZero();
}

QDualQuaternion QDualQuaternion::Conjugate() const
{
    return QDualQuaternion(r.Conjugate(), d.Conjugate());
}

QDualQuaternion QDualQuaternion::DoubleConjugate() const
{
    return QDualQuaternion(r.Conjugate(), d.Conjugate() * -SQFloat::_1);
}

float_q QDualQuaternion::GetNonDualLength() const
{
    return this->r.GetLength();
}

QDualQuaternion QDualQuaternion::Transform(const QDualQuaternion &transformation) const
{
    return QDualQuaternion(transformation * (*this) * transformation.DoubleConjugate());
}

QDualQuaternion QDualQuaternion::TransformRotationFirst(const QBaseQuaternion &qRotation, const QBaseVector3 &vTranslation) const
{
    return this->TransformRotationFirstImp(qRotation, vTranslation);
}

QDualQuaternion QDualQuaternion::TransformRotationFirst(const QBaseQuaternion &qRotation, const QBaseVector4 &vTranslation) const
{
    return this->TransformRotationFirstImp(qRotation, vTranslation);
}

QDualQuaternion QDualQuaternion::TransformTranslationFirst(const QBaseVector3 &vTranslation, const QBaseQuaternion &qRotation) const
{
    return this->TransformTranslationFirstImp(vTranslation, qRotation);
}

QDualQuaternion QDualQuaternion::TransformTranslationFirst(const QBaseVector4 &vTranslation, const QBaseQuaternion &qRotation) const
{
    return this->TransformTranslationFirstImp(vTranslation, qRotation);
}

QDualQuaternion QDualQuaternion::Lerp(const float_q &fProportion, const QDualQuaternion &dualQuat) const
{
    QDualQuaternion auxDualQuat = (SQFloat::_1 - fProportion) * (*this) + fProportion * dualQuat;
    float_q fLength = auxDualQuat.GetNonDualLength();

    QE_ASSERT(fLength != SQFloat::_0, "A zero length will produce a division by zero");

    return auxDualQuat / fLength;
}

string_q QDualQuaternion::ToString() const
{
    return string_q("DQ(r(") + r.ToString() +
               QE_L("),d(")  + d.ToString() + QE_L("))");
}

template <class VectorType>
QDualQuaternion QDualQuaternion::TransformRotationFirstImp(const QBaseQuaternion &qRotation, const VectorType &vTranslation) const
{
    QDualQuaternion rotation(qRotation, QBaseQuaternion());
    QDualQuaternion translation(QQuaternion::GetIdentity(),
                                QBaseQuaternion(vTranslation.x * SQFloat::_0_5, vTranslation.y * SQFloat::_0_5, vTranslation.z * SQFloat::_0_5, SQFloat::_0));

    return this->Transform(translation * rotation);
}

template <class VectorType>
QDualQuaternion QDualQuaternion::TransformTranslationFirstImp(const VectorType &vTranslation, const QBaseQuaternion &qRotation) const
{
    QDualQuaternion rotation(qRotation, QBaseQuaternion());
    QDualQuaternion translation(QQuaternion::GetIdentity(),
                                QBaseQuaternion(vTranslation.x * SQFloat::_0_5, vTranslation.y * SQFloat::_0_5, vTranslation.z * SQFloat::_0_5, SQFloat::_0));

    return this->Transform(rotation * translation);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QDualQuaternion& QDualQuaternion::GetIdentity()
{
    static const QDualQuaternion IDENTITY(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                            QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));
    return IDENTITY;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
