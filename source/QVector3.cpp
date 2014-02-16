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

#include "QVector3.h"

#include "Assertions.h"
#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QSpaceConversionMatrix.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QBaseVector4.h"
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

QVector3::QVector3()
{
}

QVector3::QVector3(const QVector3 &vVector) : QBaseVector3(vVector)
{
}

QVector3::QVector3(const QBaseVector3 &vVector) : QBaseVector3(vVector)
{
}

QVector3::QVector3(const QBaseVector4 &vVector) : QBaseVector3(vVector.x, vVector.y, vVector.z)
{
}

QVector3::QVector3(const float_q &fValueX, const float_q &fValueY, const float_q &fValueZ) : QBaseVector3(fValueX, fValueY, fValueZ)
{
}

QVector3::QVector3(const float_q &fValueAll) : QBaseVector3(fValueAll)
{
}

QVector3::QVector3(const float_q* arValues) : QBaseVector3(arValues)
{
}

QVector3::QVector3(const vf32_q value) : QBaseVector3(value)
{
}

QVector3::QVector3(const QTranslationMatrix<QMatrix4x3> &translation) :
                       QBaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
{
}

QVector3::QVector3(const QTranslationMatrix<QMatrix4x4> &translation) :
                       QBaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
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

QVector3 QVector3::operator+(const QBaseVector3 &vVector) const
{
    return QVector3(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z);
}

QVector3 QVector3::operator-(const QBaseVector3 &vVector) const
{
    return QVector3(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z);
}

QVector3 QVector3::operator*(const float_q &fScalar) const
{
    return QVector3(this->x * fScalar, this->y * fScalar, this->z * fScalar);
}

QVector3 QVector3::operator*(const QBaseVector3 &vVector) const
{
    return QVector3(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z);
}

QVector3 QVector3::operator*(const QBaseMatrix3x3 &matrix) const
{
    return QVector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                    this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

}

QBaseVector4 QVector3::operator*(const QBaseMatrix3x4 &matrix) const
{
    return QBaseVector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                        this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                        this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2],
                        this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3]);

}

QVector3 QVector3::operator/(const float_q &fScalar) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fScalar != SQFloat::_0, "Input value must not equal zero")

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QVector3(this->x * DIVISOR, this->y * DIVISOR, this->z * DIVISOR);
}

QVector3 QVector3::operator/(const QBaseVector3 &vVector) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 && vVector.z != SQFloat::_0, "Input vector must not be null")

    return QVector3(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z);
}

QVector3& QVector3::operator+=(const QBaseVector3 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;

    return *this;
}

QVector3& QVector3::operator-=(const QBaseVector3 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;

    return *this;
}

QVector3& QVector3::operator*=(const float_q fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;
    this->z *= fScalar;

    return *this;
}

QVector3& QVector3::operator*=(const QBaseVector3 &vVector)
{
    this->x *= vVector.x;
    this->y *= vVector.y;
    this->z *= vVector.z;

    return *this;
}

QVector3& QVector3::operator*=(const QBaseMatrix3x3 &matrix)
{
    QVector3 vAux( this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                   this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                   this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

    this->x = vAux.x;
    this->y = vAux.y;
    this->z = vAux.z;

    return *this;
}

QVector3 operator*(const float_q &fScalar, const QVector3 &vVector)
{
    return QVector3(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar);
}

QVector3& QVector3::operator/=(const float_q &fScalar)
{
    // Checkout to avoid division by 0
    QE_ASSERT(fScalar != SQFloat::_0, "Input value must not equal zero")

    const float_q &DIVISOR = SQFloat::_1 / fScalar;

    this->x *= DIVISOR;
    this->y *= DIVISOR;
    this->z *= DIVISOR;

    return *this;
}

QVector3& QVector3::operator/=(const QBaseVector3 &vVector)
{
    // Checkout to avoid division by 0
    QE_ASSERT(vVector.x != SQFloat::_0 && vVector.y != SQFloat::_0 && vVector.z != SQFloat::_0, "Input vector must not be null")

    this->x /= vVector.x;
    this->y /= vVector.y;
    this->z /= vVector.z;

    return *this;
}

QVector3& QVector3::operator=(const QBaseVector3 &vVector)
{
    QBaseVector3::operator=(vVector);
    return *this;
}

QVector3 QVector3::operator-() const
{
    return QVector3(-this->x, -this->y, -this->z);
}

float_q QVector3::GetLength() const
{
    return sqrt_q(this->x * this->x + this->y * this->y + this->z * this->z);
}

float_q QVector3::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z;
}

QVector3 QVector3::Normalize() const
{
    // Gets vector length
    float_q fLength = this->GetLength();

    // Checkout to avoid division by 0
    QE_ASSERT(fLength != SQFloat::_0, "The vector is null so it cannot be normalized, this will cause a division by zero")

    //Normalize
    return QVector3(this->x / fLength, this->y / fLength, this->z / fLength);
}

void QVector3::ResetToOne()
{
    this->x = SQFloat::_1;
    this->y = SQFloat::_1;
    this->z = SQFloat::_1;
}

void QVector3::ResetToZero()
{
    this->x = SQFloat::_0;
    this->y = SQFloat::_0;
    this->z = SQFloat::_0;
}

bool QVector3::IsZero() const
{
    return SQFloat::IsZero(this->x) && SQFloat::IsZero(this->y) && SQFloat::IsZero(this->z);
}

bool QVector3::IsVectorOfOnes() const
{
    return SQFloat::AreEqual(this->x, SQFloat::_1) && SQFloat::AreEqual(this->y, SQFloat::_1) && SQFloat::AreEqual(this->z, SQFloat::_1);
}

float_q QVector3::DotProduct(const QBaseVector3 &vVector) const
{
    return(this->x * vVector.x + this->y * vVector.y + this->z * vVector.z);
}

float_q QVector3::AngleBetween(const QVector3 &vVector) const
{
    // Note: Square root is performed outside to avoid loss of precision and gain performance
    float_q fLength = sqrt_q(this->GetSquaredLength() * vVector.GetSquaredLength());

    // Checkout to avoid division by zero.
    QE_ASSERT(fLength != SQFloat::_0, "Vectors must not be null, this will cause a division by zero")

    float_q fDot = this->DotProduct(vVector)/fLength;

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

QVector3 QVector3::CrossProduct(const QBaseVector3 &vVector) const
{
    return QVector3(this->y * vVector.z - this->z * vVector.y,
                    this->z * vVector.x - this->x * vVector.z,
                    this->x * vVector.y - this->y * vVector.x);
}

QVector3 QVector3::Lerp(const float_q &fProportion, const QVector3 &vVector) const
{
    return QVector3(this->x * (SQFloat::_1 - fProportion) + vVector.x * fProportion,
                    this->y * (SQFloat::_1 - fProportion) + vVector.y * fProportion,
                    this->z * (SQFloat::_1 - fProportion) + vVector.z * fProportion);
}

float_q QVector3::Distance(const QBaseVector3 &vVector) const
{
    return (*this - vVector).GetLength();
}

QVector3 QVector3::Transform(const QQuaternion &qRotation) const
{
    QQuaternion qAux(this->x, this->y, this->z, SQFloat::_0);
    QQuaternion qConj = qRotation.Conjugate();

    qAux = (qRotation * qAux) * qConj;

    return QVector3(qAux.x, qAux.y, qAux.z);
}

QVector3 QVector3::Transform(const QDualQuaternion &transformation) const
{
    QDualQuaternion dqAux(QBaseQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1),
                          QBaseQuaternion(this->x, this->y, this->z, SQFloat::_0));
    QDualQuaternion dqConj = transformation.DoubleConjugate();

    dqAux = (transformation * dqAux ) * dqConj;

    return QVector3(dqAux.d.x, dqAux.d.y, dqAux.d.z);
}

QVector3 QVector3::Transform(const QSpaceConversionMatrix &conversion) const
{
    return QVector3(this->x * conversion.ij[0][0] + this->y * conversion.ij[1][0] + this->z * conversion.ij[2][0] + conversion.ij[3][0],
                    this->x * conversion.ij[0][1] + this->y * conversion.ij[1][1] + this->z * conversion.ij[2][1] + conversion.ij[3][1],
                    this->x * conversion.ij[0][2] + this->y * conversion.ij[1][2] + this->z * conversion.ij[2][2] + conversion.ij[3][2]);
}

QVector3 QVector3::Transform(const QRotationMatrix3x3 &rotation) const
{
    return *this * rotation;
}

QVector3 QVector3::Transform(const QScalingMatrix3x3 &scale) const
{
    return QVector3(this->x * scale.ij[0][0], this->y * scale.ij[1][1], this->z * scale.ij[2][2]);
}

QVector3 QVector3::Transform(const QTranslationMatrix<QMatrix4x3> &translation) const
{
    return TransformImp(translation);
}

QVector3 QVector3::Transform(const QTranslationMatrix<QMatrix4x4> &translation) const
{
    return TransformImp(translation);
}

QVector3 QVector3::Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
{
    return TransformImp(transformation);
}

QVector3 QVector3::Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
{
    return TransformImp(transformation);
}

string_q QVector3::ToString() const
{
    return QE_L("V3(") + SQFloat::ToString(this->x) +
           QE_L(",")  + SQFloat::ToString(this->y) +
           QE_L(",")  + SQFloat::ToString(this->z) + QE_L(")");
}

template <class MatrixType>
QVector3 QVector3::TransformImp(const QTranslationMatrix<MatrixType> &translation) const
{
    return QVector3(this->x + translation.ij[3][0], this->y + translation.ij[3][1], this->z + translation.ij[3][2]);
}

template <class MatrixType>
QVector3 QVector3::TransformImp(const QTransformationMatrix<MatrixType> &transformation) const
{
    return QVector3(this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + transformation.ij[3][0],
                    this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + transformation.ij[3][1],
                    this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + transformation.ij[3][2]);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QVector3& QVector3::GetNullVector()
{
    static const QVector3 NULLVECTOR(SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
    return NULLVECTOR;
}

const QVector3& QVector3::GetVectorOfOnes()
{
    static const QVector3 VECTOROFONES(SQFloat::_1,  SQFloat::_1,  SQFloat::_1);
    return VECTOROFONES;
}

const QVector3& QVector3::GetUnitVectorX()
{
    static const QVector3 UNITVECTORX(SQFloat::_1,  SQFloat::_0,  SQFloat::_0);
    return UNITVECTORX;
}

const QVector3& QVector3::GetUnitVectorY()
{
    static const QVector3 UNITVECTORY(SQFloat::_0,  SQFloat::_1,  SQFloat::_0);
    return UNITVECTORY;
}

const QVector3& QVector3::GetUnitVectorZ()
{
    static const QVector3 UNITVECTORZ(SQFloat::_0,  SQFloat::_0,  SQFloat::_1);
    return UNITVECTORZ;
}

const QVector3& QVector3::GetUnitVectorInvX()
{
    static const QVector3 UNITVECTORINVX(-SQFloat::_1,  SQFloat::_0,  SQFloat::_0);
    return UNITVECTORINVX;
}

const QVector3& QVector3::GetUnitVectorInvY()
{
    static const QVector3 UNITVECTORINVY(SQFloat::_0,  -SQFloat::_1,  SQFloat::_0);
    return UNITVECTORINVY;
}

const QVector3& QVector3::GetUnitVectorInvZ()
{
    static const QVector3 UNITVECTORINVZ(SQFloat::_0,  SQFloat::_0,  -SQFloat::_1);
    return UNITVECTORINVZ;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
