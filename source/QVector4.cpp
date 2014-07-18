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

#include "QVector4.h"

#include "Assertions.h"
#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"
#include "QBaseVector3.h"
#include "SQAngle.h"

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

QVector4::QVector4()
{
}

QVector4::QVector4(const QVector4 &vVector) : QBaseVector4(vVector)
{
}

QVector4::QVector4(const QBaseVector4 &vVector) : QBaseVector4(vVector)
{
}

QVector4::QVector4(const QBaseVector3 &vVector) : QBaseVector4(vVector.x, vVector.y, vVector.z, SQFloat::_0)
{
}

QVector4::QVector4(const QBaseVector3 &vVector, const float &fValue) : QBaseVector4(vVector.x, vVector.y, vVector.z, fValue)
{
}

QVector4::QVector4(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ, const float_q &fValueW) :
                    QBaseVector4(fValueX, fValueY, fValueZ, fValueW)
{
}

QVector4::QVector4(const float_q &fValueAll) : QBaseVector4(fValueAll)
{
}

QVector4::QVector4(const float_q* arValues) : QBaseVector4(arValues)
{
}

QVector4::QVector4(const vf32_q value) : QBaseVector4(value)
{
}

QVector4::QVector4(const QTranslationMatrix<QMatrix4x3> &translation) :
                       QBaseVector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SQFloat::_1)
{
}

QVector4::QVector4(const QTranslationMatrix<QMatrix4x4> &translation) :
                       QBaseVector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SQFloat::_1)
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

QVector4 QVector4::operator+(const QBaseVector4 &vVector) const
{
    return QVector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w + vVector.w);
}

QVector4 QVector4::operator+(const QBaseVector3 &vVector) const
{
    return QVector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w);
}

QVector4 QVector4::operator-(const QBaseVector4 &vVector) const
{
    return QVector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w - vVector.w);
}

QVector4 QVector4::operator-(const QBaseVector3 &vVector) const
{
    return QVector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w);
}

QVector4 QVector4::operator*(const float_q &fScalar) const
{
    return QVector4(this->x * fScalar, this->y * fScalar, this->z * fScalar, this->w * fScalar);
}

QVector4 QVector4::operator*(const QBaseVector4 &vVector) const
{
    return QVector4(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z, this->w * vVector.w);
}

QVector4 QVector4::operator*(const QBaseMatrix4x4 &matrix) const
{
    return QVector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                    this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2],
                    this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3] + this->w * matrix.ij[3][3]);
}

QBaseVector3 QVector4::operator*(const QBaseMatrix4x3 &matrix) const
{
    return QBaseVector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                        this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                        this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2]);

}

QVector4 QVector4::operator/(const float_q &fScalar) const
{
    // Checkout to avoid division by 0
    QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1 / fScalar;

    return QVector4(this->x * DIVISOR, this->y * DIVISOR, this->z * DIVISOR, this->w * DIVISOR);
}

QVector4 QVector4::operator/(const QBaseVector4 &vVector) const
{
    // Checkout to avoid division by 0
    QE_ASSERT(vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 &&
              vVector.z != SQFloat::_0 && vVector.w != SQFloat::_0, "Input vector must not be null")

    return QVector4(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z, this->w / vVector.w);
}

QVector4& QVector4::operator+=(const QBaseVector4 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;
    this->w += vVector.w;

    return *this;
}

QVector4& QVector4::operator+=(const QBaseVector3 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;

    return *this;
}

QVector4& QVector4::operator-=(const QBaseVector4 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;
    this->w -= vVector.w;

    return *this;
}

QVector4& QVector4::operator-=(const QBaseVector3 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;

    return *this;
}

QVector4& QVector4::operator*=(const float_q fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;
    this->z *= fScalar;
    this->w *= fScalar;

    return *this;
}

QVector4& QVector4::operator*=(const QBaseVector4 &vVector)
{
    this->x *= vVector.x;
    this->y *= vVector.y;
    this->z *= vVector.z;
    this->w *= vVector.w;

    return *this;
}

QVector4& QVector4::operator*=(const QBaseMatrix4x4 &matrix)
{
    QVector4 vAux(*this);

    this->x = vAux.x * matrix.ij[0][0] + vAux.y * matrix.ij[1][0] + vAux.z * matrix.ij[2][0] + vAux.w * matrix.ij[3][0];
    this->y = vAux.x * matrix.ij[0][1] + vAux.y * matrix.ij[1][1] + vAux.z * matrix.ij[2][1] + vAux.w * matrix.ij[3][1];
    this->z = vAux.x * matrix.ij[0][2] + vAux.y * matrix.ij[1][2] + vAux.z * matrix.ij[2][2] + vAux.w * matrix.ij[3][2];
    this->w = vAux.x * matrix.ij[0][3] + vAux.y * matrix.ij[1][3] + vAux.z * matrix.ij[2][3] + vAux.w * matrix.ij[3][3];

    return *this;
}

QVector4& QVector4::operator/=(const float_q &fScalar)
{
    // Checkout to avoid division by 0
    QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1 / fScalar;

    this->x *= DIVISOR;
    this->y *= DIVISOR;
    this->z *= DIVISOR;
    this->w *= DIVISOR;

    return *this;
}

QVector4& QVector4::operator/=(const QBaseVector4 &vVector)
{
    // Checkout to avoid division by 0
    QE_ASSERT (vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 && vVector.z != SQFloat::_0 && vVector.w != SQFloat::_0, 
               "Input vector must not be null")

    this->x /= vVector.x;
    this->y /= vVector.y;
    this->z /= vVector.z;
    this->w /= vVector.w;

    return *this;
}

QVector4& QVector4::operator=(const QBaseVector4 &vVector)
{
    QBaseVector4::operator=(vVector);
    return *this;
}

QVector4 QVector4::operator-() const
{
    return QVector4(-this->x, -this->y, -this->z, -this->w);
}

// Left float product
QVector4 operator*(const float_q &fScalar, const QVector4 &vVector)
{
    return QVector4(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar, vVector.w * fScalar);
}

float_q QVector4::GetLength() const
{
    return sqrt_q(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

float_q QVector4::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
}

QVector4 QVector4::Normalize() const
{
    // Checkout to avoid division by 0
    QE_ASSERT(this->GetLength() != SQFloat::_0, "The vector is null so it cannot be normalized, this will cause a division by zero");

    // Gets inverse of the vector length
    float_q fInvLength = SQFloat::_1 / this->GetLength();

    //Normalize
    return QVector4(this->x * fInvLength, this->y * fInvLength, this->z * fInvLength, this->w * fInvLength);
}

void QVector4::ResetToOne()
{
    this->x = SQFloat::_1;
    this->y = SQFloat::_1;
    this->z = SQFloat::_1;
    this->w = SQFloat::_1;
}

void QVector4::ResetToZeroPoint()
{
    this->x = SQFloat::_0;
    this->y = SQFloat::_0;
    this->z = SQFloat::_0;
    this->w = SQFloat::_1;
}

void QVector4::ResetToZeroVector()
{
    this->x = SQFloat::_0;
    this->y = SQFloat::_0;
    this->z = SQFloat::_0;
    this->w = SQFloat::_0;
}
    
bool QVector4::IsZero() const
{
    return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) &&
            SQFloat::IsZero(this->z) && SQFloat::IsZero(this->w);
}

bool QVector4::IsVectorOfOnes() const
{
    return SQFloat::AreEqual(this->x, SQFloat::_1) && SQFloat::AreEqual(this->y, SQFloat::_1) &&
            SQFloat::AreEqual(this->z, SQFloat::_1) && SQFloat::AreEqual(this->w, SQFloat::_1);
}

float_q QVector4::DotProduct(const QBaseVector4 &vVector) const
{
    return this->x * vVector.x + this->y * vVector.y + this->z * vVector.z;
}

float_q QVector4::AngleBetween(const QBaseVector4 &vVector) const
{
    float_q fLength = sqrt_q( (this->x*this->x + this->y*this->y + this->z*this->z) * (vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z) );

    // Checkout to avoid division by zero.
    QE_ASSERT(fLength != SQFloat::_0, "Vectors must not be null, this will cause a division by zero");

    float_q fDot = (this->x*vVector.x + this->y*vVector.y + this->z*vVector.z) / fLength;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(fDot > SQFloat::_1)
        fDot = SQFloat::_1;
    else if(fDot < -SQFloat::_1)
        fDot = -SQFloat::_1;

    float_q fAngle = acos_q(fDot);

    QE_ASSERT( !SQFloat::IsNaN(fAngle), "The resultant angle is NAN" );

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

QVector4 QVector4::CrossProduct(const QBaseVector4 &vVector) const
{
    return QVector4(this->y * vVector.z - this->z * vVector.y,
                    this->z * vVector.x - this->x * vVector.z,
                    this->x * vVector.y - this->y * vVector.x,
                    this->w);
}

QVector4 QVector4::Lerp(const float_q &fProportion, const QBaseVector4 &vVector) const
{
    return QVector4(this->x * (SQFloat::_1 - fProportion) + vVector.x * fProportion,
                    this->y * (SQFloat::_1 - fProportion) + vVector.y * fProportion,
                    this->z * (SQFloat::_1 - fProportion) + vVector.z * fProportion,
                    this->w * (SQFloat::_1 - fProportion) + vVector.w * fProportion);
}

float_q QVector4::Distance(const QBaseVector4 &vVector) const
{
    return sqrt_q( (this->x - vVector.x)*(this->x - vVector.x) + (this->y - vVector.y)*(this->y - vVector.y) +
                    (this->z - vVector.z)*(this->z - vVector.z) );
}

QVector4 QVector4::Homogenize() const
{
    QVector4 homogenizedVector;

    if(this->w != SQFloat::_0) // Exactly zero
    {
        float_q fInvW = SQFloat::_1 / this->w;
        homogenizedVector = QVector4(this->x * fInvW, this->y * fInvW, this->z * fInvW, SQFloat::_1);
    }
    else
    {
        homogenizedVector = *this;
    }

    return homogenizedVector;
}

QVector4 QVector4::Transform(const QQuaternion &qRotation) const
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj = qRotation.Conjugate();

    qAux = (qRotation * qAux) * qConj;

    return QVector4(qAux.x, qAux.y, qAux.z, this->w);
}

QVector4 QVector4::Transform(const QDualQuaternion &transformation) const
{
    QDualQuaternion dqAux(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                          QBaseQuaternion(this->x, this->y, this->z, SQFloat::_0));
    QDualQuaternion dqConj = transformation.DoubleConjugate();

    dqAux = (transformation * dqAux ) * dqConj;

    return QVector4(dqAux.d.x, dqAux.d.y, dqAux.d.z, this->w);
}

QVector4 QVector4::Transform(const QRotationMatrix3x3 &rotation) const
{
    return QVector4(this->x * rotation.ij[0][0] + this->y * rotation.ij[1][0] + this->z * rotation.ij[2][0],
                    this->x * rotation.ij[0][1] + this->y * rotation.ij[1][1] + this->z * rotation.ij[2][1],
                    this->x * rotation.ij[0][2] + this->y * rotation.ij[1][2] + this->z * rotation.ij[2][2],
                    this->w);
}

QVector4 QVector4::Transform(const QScalingMatrix3x3 &scale) const
{
    return QVector4(this->x * scale.ij[0][0], this->y * scale.ij[1][1], this->z * scale.ij[2][2], this->w);
}

QVector4 QVector4::Transform(const QTranslationMatrix<QMatrix4x3> &translation) const
{
    return TransformImp(translation);
}


QVector4 QVector4::Transform(const QTranslationMatrix<QMatrix4x4> &translation) const
{
    return TransformImp(translation);
}

QVector4 QVector4::Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
{
    return TransformImp(transformation);
}


QVector4 QVector4::Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
{
    return TransformImp(transformation);
}

QVector4 QVector4::Transform(const QSpaceConversionMatrix &conversion) const
{
    return *this * conversion;
}

string_q QVector4::ToString() const
{
    return string_q("V4(") + SQFloat::ToString(this->x) +
               QE_L(",")   + SQFloat::ToString(this->y) +
               QE_L(",")   + SQFloat::ToString(this->z) +
               QE_L(",")   + SQFloat::ToString(this->w) + QE_L(")");
}

template <class MatrixType>
QVector4 QVector4::TransformImp(const QTranslationMatrix<MatrixType> &translation) const
{
    return QVector4(this->x + this->w * translation.ij[3][0],
                    this->y + this->w * translation.ij[3][1],
                    this->z + this->w * translation.ij[3][2],
                    this->w);
}

/// <summary>
/// Applies a translation to resident vector, multiplying the vector by a translation matrix
/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
/// since a 3D vector cannot be displaced.
/// </summary>
/// <typeparam name="MatrixType">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
/// <param name="translation">[IN] The translation matrix. It must be a 4x3 or a 4x4 translation matrix.</param>
/// <returns>
/// The transformed vector.
/// </returns>
template <class MatrixType>
QVector4 QVector4::TransformImp(const QTransformationMatrix<MatrixType> &transformation) const
{
    return QVector4(this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + this->w * transformation.ij[3][0],
                    this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + this->w * transformation.ij[3][1],
                    this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + this->w * transformation.ij[3][2],
                    this->w);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QVector4& QVector4::GetZeroPoint()
{
    static const QVector4 ZEROPOINT(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    return ZEROPOINT;
}

const QVector4& QVector4::GetNullVector()
{
    static const QVector4 NULLVECTOR(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    return NULLVECTOR;
}

const QVector4& QVector4::GetVectorOfOnes()
{
    static const QVector4 VECTOROFONES(SQFloat::_1,  SQFloat::_1,  SQFloat::_1, SQFloat::_1);
    return VECTOROFONES;
}

const QVector4& QVector4::GetUnitVectorX()
{
    static const QVector4 UNITVECTORX(SQFloat::_1,  SQFloat::_0,  SQFloat::_0, SQFloat::_0);
    return UNITVECTORX;
}

const QVector4& QVector4::GetUnitVectorY()
{
    static const QVector4 UNITVECTORY(SQFloat::_0,  SQFloat::_1,  SQFloat::_0, SQFloat::_0);
    return UNITVECTORY;
}

const QVector4& QVector4::GetUnitVectorZ()
{
    static const QVector4 UNITVECTORZ(SQFloat::_0,  SQFloat::_0,  SQFloat::_1, SQFloat::_0);
    return UNITVECTORZ;
}

const QVector4& QVector4::GetUnitVectorInvX()
{
    static const QVector4 UNITVECTORINVX(-SQFloat::_1,  SQFloat::_0,  SQFloat::_0, SQFloat::_0);
    return UNITVECTORINVX;
}

const QVector4& QVector4::GetUnitVectorInvY()
{
    static const QVector4 UNITVECTORINVY(SQFloat::_0,  -SQFloat::_1,  SQFloat::_0, SQFloat::_0);
    return UNITVECTORINVY;
}

const QVector4& QVector4::GetUnitVectorInvZ()
{
    static const QVector4 UNITVECTORINVZ(SQFloat::_0,  SQFloat::_0,  -SQFloat::_1, SQFloat::_0);
    return UNITVECTORINVZ;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
