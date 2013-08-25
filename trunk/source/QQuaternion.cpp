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

#include "QQuaternion.h"
#include "MathDefinitions.h"

#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QRotationMatrix3x3.h"
#include "QTransformationMatrix.h"

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

QQuaternion::QQuaternion(const float_q &fRotationAngleX, const float_q &fRotationAngleY, const float_q &fRotationAngleZ)
{
    // Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q& HALF_ANGLE_X_RAD = SQAngle::DegreesToRadians(fRotationAngleX) * SQFloat::_0_5;
        const float_q& HALF_ANGLE_Y_RAD = SQAngle::DegreesToRadians(fRotationAngleY) * SQFloat::_0_5;
        const float_q& HALF_ANGLE_Z_RAD = SQAngle::DegreesToRadians(fRotationAngleZ) * SQFloat::_0_5;
    #else
        const float_q& HALF_ANGLE_X_RAD = fRotationAngleX * SQFloat::_0_5;
        const float_q& HALF_ANGLE_Y_RAD = fRotationAngleY * SQFloat::_0_5;
        const float_q& HALF_ANGLE_Z_RAD = fRotationAngleZ * SQFloat::_0_5;
    #endif

    const float_q cx = cos_q(HALF_ANGLE_X_RAD);
    const float_q cy = cos_q(HALF_ANGLE_Y_RAD);
    const float_q cz = cos_q(HALF_ANGLE_Z_RAD);
    const float_q sx = sin_q(HALF_ANGLE_X_RAD);
    const float_q sy = sin_q(HALF_ANGLE_Y_RAD);
    const float_q sz = sin_q(HALF_ANGLE_Z_RAD);

	this->w =  cy * cx * cz + sy * sx * sz;
	this->x =  cy * sx * cz + sy * cx * sz;
	this->y = -cy * sx * sz + sy * cx * cz;
	this->z = -sy * sx * cz + cy * cx * sz;
}

QQuaternion::QQuaternion(const QBaseVector3 &vRotationAxis, const float_q &fRotationAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q& HALF_ANGLE_RAD = SQAngle::DegreesToRadians(fRotationAngle) * SQFloat::_0_5;
    #else
        const float_q& HALF_ANGLE_RAD = fRotationAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(HALF_ANGLE_RAD);

	// Please note the axis has to be normalized...

	this->x = vRotationAxis.x * fSin;
	this->y = vRotationAxis.y * fSin;
	this->z = vRotationAxis.z * fSin;

	this->w = cos_q(HALF_ANGLE_RAD);
}

QQuaternion::QQuaternion(const QBaseVector4 &vRotationAxis, const float_q &fRotationAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_q& HALF_ANGLE_RAD = SQAngle::DegreesToRadians(fRotationAngle) * SQFloat::_0_5;
    #else
        const float_q& HALF_ANGLE_RAD = fRotationAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(HALF_ANGLE_RAD);

	// Please note the axis has to be normalized...

	this->x = vRotationAxis.x * fSin;
	this->y = vRotationAxis.y * fSin;
	this->z = vRotationAxis.z * fSin;

	this->w = cos_q(HALF_ANGLE_RAD);
}

QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x3> &transformation)
{
    this->QQuaternionImp(transformation);
}


QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x4> &transformation)
{
    this->QQuaternionImp(transformation);
}


QQuaternion::QQuaternion(const QRotationMatrix3x3 &rotation)
{
    rotation.GetRotation(*this);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QQuaternion QQuaternion::operator+(const QBaseQuaternion &qQuat) const
{
    return QQuaternion(this->x + qQuat.x,
                       this->y + qQuat.y,
                       this->z + qQuat.z,
                       this->w + qQuat.w);
}

QQuaternion QQuaternion::operator-(const QBaseQuaternion &qQuat) const
{
    return QQuaternion(this->x - qQuat.x,
                       this->y - qQuat.y,
                       this->z - qQuat.z,
                       this->w - qQuat.w);
}

QQuaternion QQuaternion::operator*(const QBaseQuaternion &qQuat) const
{
    return QQuaternion( qQuat.w * this->x + qQuat.x * this->w + qQuat.y * this->z - qQuat.z * this->y,	   // Vx
                        qQuat.w * this->y + qQuat.y * this->w + qQuat.z * this->x - qQuat.x * this->z,	   // Vy
                        qQuat.w * this->z + qQuat.z * this->w + qQuat.x * this->y - qQuat.y * this->x,	   // Vz
                        qQuat.w * this->w - qQuat.x * this->x - qQuat.y * this->y - qQuat.z * this->z );	   // W
}

QQuaternion QQuaternion::operator*(const float_q &fScalar) const
{
    return QQuaternion( this->x * fScalar,
                        this->y * fScalar,
                        this->z * fScalar,
                        this->w * fScalar);
}

QQuaternion QQuaternion::operator*(const QBaseVector3 &vVector) const
{
    return *this * QQuaternion(vVector.x, vVector.y, vVector.z, SQFloat::_0);
}

QQuaternion QQuaternion::operator*(const QBaseVector4 &vVector) const
{
    return *this * QQuaternion(vVector.x, vVector.y, vVector.z, vVector.w);
}

QQuaternion QQuaternion::operator/(const QBaseQuaternion &qQuat) const
{
    return *this * rcast_q(qQuat, const QQuaternion&).Invert();
}

QQuaternion QQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QQuaternion( this->x * DIVISOR,
                        this->y * DIVISOR,
                        this->z * DIVISOR,
                        this->w * DIVISOR);
}

QQuaternion operator*(const float_q &fScalar, const QQuaternion &qQuat)
{
    return QQuaternion( qQuat.x * fScalar, qQuat.y * fScalar, qQuat.z * fScalar, qQuat.w * fScalar);
}

float_q QQuaternion::DotProduct(const QBaseQuaternion &qQuat) const
{
    return this->x * qQuat.x + this->y * qQuat.y + this->z * qQuat.z + this->w * qQuat.w;
}

float_q QQuaternion::DotProductAngle(const QBaseQuaternion &qQuat) const
{
    float_q fLengths = this->GetLength() * rcast_q(qQuat, const QQuaternion&).GetLength();

    // Checkout to avoid division by zero.
    QE_ASSERT(fLengths != SQFloat::_0)

    float_q fDot = (this->x*qQuat.x + this->y*qQuat.y + this->z*qQuat.z + this->w*qQuat.w)/fLengths;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1)

    float_q fAngle = acos(fDot) * SQFloat::_2;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

QQuaternion QQuaternion::Lerp(const float_q &fProportion, const QQuaternion &qQuat) const
{
    // Separated from the equation to gain performance
    QQuaternion qAuxSum(this->x * (SQFloat::_1 - fProportion) + qQuat.x * fProportion,
                        this->y * (SQFloat::_1 - fProportion) + qQuat.y * fProportion,
                        this->z * (SQFloat::_1 - fProportion) + qQuat.z * fProportion,
                        this->w * (SQFloat::_1 - fProportion) + qQuat.w * fProportion);

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor != SQFloat::_0)

    return qAuxSum / fDivisor;
}

QQuaternion QQuaternion::Slerp(const float_q &fProportion, const QQuaternion &qQuat) const
{
    QQuaternion qReturnValue;

    // Assures that all quaternions are unit length
    QQuaternion qNormalizedInputQuat = rcast_q(qQuat, const QQuaternion&).Normalize();
    QQuaternion qNormalizedThisQuat = this->Normalize();

    const float_q ANGLE_B = acos_q(qNormalizedThisQuat.DotProduct(qNormalizedInputQuat));

    QE_ASSERT( !SQFloat::IsNaN(ANGLE_B) )

    if( ANGLE_B != SQFloat::_0 && SQFloat::AreNotEqual(ANGLE_B, PI_Q) )
    {
        const float_q INV_SIN = SQFloat::_1/sin_q(ANGLE_B);

        const float_q WEIGHT1 = sin_q((SQFloat::_1 - fProportion) * ANGLE_B) * INV_SIN;
        const float_q WEIGHT2 = sin_q(fProportion * ANGLE_B) * INV_SIN;

        // Separated from the equation to gain performance
        const QQuaternion AUX_SUM = WEIGHT1 * qNormalizedThisQuat + WEIGHT2 * qNormalizedInputQuat;

        // Separated from the equation to check for "division by zero"
        const float_q DIVISOR = AUX_SUM.GetLength();

        QE_ASSERT(DIVISOR != SQFloat::_0)

        qReturnValue = AUX_SUM / DIVISOR;
    }
    else
        qReturnValue = *this;

    return qReturnValue;
}

QQuaternion QQuaternion::UnitSlerp(const float_q &fProportion, const QQuaternion &qQuat) const
{
    QQuaternion qReturnValue;

    const float_q& ANGLE_B = acos_q(this->DotProduct(qQuat));

    QE_ASSERT( !SQFloat::IsNaN(ANGLE_B) )

    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    if(ANGLE_B != SQFloat::_0 && SQFloat::AreNotEqual(ANGLE_B, PI_Q))
    {
        const float_q INV_SIN = SQFloat::_1/sin_q(ANGLE_B);

        const float_q WEIGHT1 = sin_q((SQFloat::_1 - fProportion) * ANGLE_B) * INV_SIN;
        const float_q WEIGHT2 = sin_q(fProportion * ANGLE_B) * INV_SIN;

        // Separated from the equation to gain performance
        const QQuaternion AUX_SUM = WEIGHT1 * (*this) + WEIGHT2 * qQuat;

        // Separated from the equation to check for "division by zero"
        const float_q DIVISOR = AUX_SUM.GetLength();

        QE_ASSERT(DIVISOR != SQFloat::_0)

        qReturnValue = AUX_SUM / DIVISOR;
    }
    else
        qReturnValue = *this;

    return qReturnValue;
}

void QQuaternion::ToEulerAngles(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const
{
    // Source: Based on Amy de Buitléir's document about quaternions

    fRotationAngleX = asin_q(SQFloat::_2 * (this->w * this->x - this->z * this->y));


    // Checks for +-90º singularity
    if(SQFloat::AreEqual(fRotationAngleX, SQFloat::Abs(SQAngle::_HalfPi)))

    {
        fRotationAngleZ = atan2_q(this->z, this->w);
        fRotationAngleY = SQFloat::_0;
    }
    else
    {
        fRotationAngleZ = atan2_q(SQFloat::_2 * (this->w * this->z + this->x * this->y),
                                  (SQFloat::_1 - SQFloat::_2 * (this->z * this->z + this->x * this->x)) );
        fRotationAngleY = atan2_q(SQFloat::_2 * (this->w * this->y + this->z * this->x),
                                  (SQFloat::_1 - SQFloat::_2 * (this->x * this->x + this->y * this->y)) );
    }
}

void QQuaternion::ToAxisAngle(QBaseVector3 &vRotationAxis, float_q &fRotationAngle) const
{
   // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
	QE_ASSERT(SQFloat::Abs(this->w) <= SQFloat::_1)

	fRotationAngle = SQFloat::_2 * acos_q(this->w);

	// Singularity 1: Angle = 0 -> we choose arbitrary axis.
	if (SQFloat::IsZero(fRotationAngle))
	{
		vRotationAxis.x = SQFloat::_1;
		vRotationAxis.y = SQFloat::_0;
		vRotationAxis.z = SQFloat::_0;
	}
	// Singularity 2: Angle = PI -> we calculate axis.
	else if ( SQFloat::AreEqual(fRotationAngle, SQAngle::_Pi) )
	{
		vRotationAxis.x = this->x;
		vRotationAxis.y = this->y;
		vRotationAxis.z = this->z;
	}
	else
	{
		const float_q &fInvSin = SQFloat::_1 / sin_q(fRotationAngle * SQFloat::_0_5);

		vRotationAxis.x = this->x*fInvSin;
		vRotationAxis.y = this->y*fInvSin;
		vRotationAxis.z = this->z*fInvSin;
	}

	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        fRotationAngle = SQAngle::RadiansToDegrees(fRotationAngle);
    #endif
}

void QQuaternion::ToAxisAngle(QBaseVector4 &vRotationAxis, float_q &fRotationAngle) const
{
    QBaseVector3 vAux;

    this->ToAxisAngle(vAux, fRotationAngle);

    vRotationAxis.x =  vAux.x;
    vRotationAxis.y =  vAux.y;
    vRotationAxis.z =  vAux.z;
    vRotationAxis.w = SQFloat::_0;
}

float_q QQuaternion::GetLength() const
{
    //           _______________________
    // length = V x^2 + y^2 + z^2 + w^2
    //
    return sqrt_q( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

float_q QQuaternion::GetSquaredLength() const
{
    //                    ______________________
    // squared length = (V x^2 + y^2 + z^2 + w^2)^2
    //
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
}

string_q QQuaternion::ToString() const
{
    return QE_L("Q(") + SQFloat::ToString(this->x) +
           QE_L(",")  + SQFloat::ToString(this->y) +
           QE_L(",")  + SQFloat::ToString(this->z) +
           QE_L(",")  + SQFloat::ToString(this->w) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
