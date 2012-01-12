// [TERMS&CONDITIONS]

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
        float_q fHalfAngleXRad = SQAngle::DegreesToRadians(fRotationAngleX, fHalfAngleXRad) * SQFloat::_0_5;
        float_q fHalfAngleYRad = SQAngle::DegreesToRadians(fRotationAngleY, fHalfAngleYRad) * SQFloat::_0_5;
        float_q fHalfAngleZRad = SQAngle::DegreesToRadians(fRotationAngleZ, fHalfAngleZRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleXRad = fRotationAngleX * SQFloat::_0_5;
        const float_q& fHalfAngleYRad = fRotationAngleY * SQFloat::_0_5;
        const float_q& fHalfAngleZRad = fRotationAngleZ * SQFloat::_0_5;
    #endif

    float_q cx = cos_q(fHalfAngleXRad);
    float_q cy = cos_q(fHalfAngleYRad);
    float_q cz = cos_q(fHalfAngleZRad);
    float_q sx = sin_q(fHalfAngleXRad);
    float_q sy = sin_q(fHalfAngleYRad);
    float_q sz = sin_q(fHalfAngleZRad);

	// These are the computing formulas once the following decisions have been taken for Quimera Engine:
	//
	// -Coordinate system axis: LEFT-Handed.
	//       -Positive rotation: CLOCKWISE.
	//			-Please note from user's perspective (-Z axis) rotation about Z axis may be seen
	//			 as COUNTER-CLOCKWISE.
	//		 -Matrices as ROW vectors.
	//			-Transforming vectors: Vector * TransformationMatrix = TransformedVector
	// -Convention: ZXY (roll, pitch, yaw).
	//		 -Quaternion combination: from RIGHT to LEFT --> yaw * (pitch * roll)

	this->w = cy * cx * cz - sy * sz * sx;

	this->x = cy * cz * sx + sy * cx * sz;
	this->y = cy * sz * sx + cx * cz * sy;
	this->z = cy * cx * sz - sy * cz * sx;
}

QQuaternion::QQuaternion(const QBaseVector3 &vRotationAxis, const float_q &fRotationAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = SQAngle::DegreesToRadians(fRotationAngle, fHalfAngleRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fRotationAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(fHalfAngleRad);

	// Please note the axis has to be normalized...

	this->x = vRotationAxis.x * fSin;
	this->y = vRotationAxis.y * fSin;
	this->z = vRotationAxis.z * fSin;

	this->w = cos_q(fHalfAngleRad);
}

QQuaternion::QQuaternion(const QBaseVector4 &vRotationAxis, const float_q &fRotationAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = SQAngle::DegreesToRadians(fRotationAngle, fHalfAngleRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fRotationAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(fHalfAngleRad);

	// Please note the axis has to be normalized...

	this->x = vRotationAxis.x * fSin;
	this->y = vRotationAxis.y * fSin;
	this->z = vRotationAxis.z * fSin;

	this->w = cos_q(fHalfAngleRad);
}

QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x3> &transformation)
{
    QQuaternionImp(transformation);
}


QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x4> &transformation)
{
    QQuaternionImp(transformation);
}


QQuaternion::QQuaternion(const QRotationMatrix3x3 &rotation)
{
    rotation.GetRotation(*this);
}

template <class MatrixType>
inline void QQuaternion::QQuaternionImp(const QTransformationMatrix<MatrixType> &transformation)
{
    transformation.GetRotation(*this);
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

    return QQuaternion( this->w * qQuat.x + qQuat.w * this->x + (this->y * qQuat.z - this->z * qQuat.y),	   // Vx
                        this->w * qQuat.y + this->y * qQuat.w + (this->z * qQuat.x - this->x * qQuat.z),	   // Vy
                        this->w * qQuat.z + this->z * qQuat.w + (this->x * qQuat.y - this->y * qQuat.x),	   // Vz
                        this->w * qQuat.w - (this->x * qQuat.x + this->y * qQuat.y + this->z * qQuat.z) );	   // W
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
	QQuaternion qAux(vVector.x, vVector.y, vVector.z, SQFloat::_0);

    return *this * qAux;
}

QQuaternion QQuaternion::operator*(const QBaseVector4 &vVector) const
{
	QQuaternion qAux(vVector.x, vVector.y, vVector.z, vVector.w);

    return *this * qAux;
}
QQuaternion QQuaternion::operator/(const QBaseQuaternion &qQuat) const
{
    QE_ASSERT(qQuat.x != SQFloat::_0 && qQuat.y != SQFloat::_0 && qQuat.z != SQFloat::_0 && qQuat.w != SQFloat::_0);

    return QQuaternion(this->x / qQuat.x,
                       this->y / qQuat.y,
                       this->z / qQuat.z,
                       this->w / qQuat.w);
}

QQuaternion QQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != SQFloat::_0);

    const float_q &fDivisor = SQFloat::_1/fScalar;

    return QQuaternion( this->x * fDivisor,
                        this->y * fDivisor,
                        this->z * fDivisor,
                        this->w * fDivisor);
}

QQuaternion operator*(const float_q &fScalar, const QBaseQuaternion &qQuat)
{
    return QQuaternion( qQuat.x * fScalar, qQuat.y * fScalar, qQuat.z * fScalar, qQuat.w * fScalar);
}

float_q QQuaternion::DotProduct(const QBaseQuaternion &qQuat) const
{
    return this->x * qQuat.x + this->y * qQuat.y + this->z * qQuat.z + this->w * qQuat.w;
}

float_q QQuaternion::DotProductAngle(const QBaseQuaternion &qQuat) const
{
    float_q fLength = sqrt_q( (this->x*this->x + this->y*this->y + this->z*this->z) *
                            (qQuat.x*qQuat.x + qQuat.y*qQuat.y + qQuat.z*qQuat.z) );

    // Checkout to avoid division by zero.
    QE_ASSERT(fLength != SQFloat::_0);

    float_q fDot = (this->x*qQuat.x + this->y*qQuat.y + this->z*qQuat.z)/fLength;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

    float_q fAngle = acos(fDot);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        SQAngle::RadiansToDegrees(fAngle, fAngle);
    #endif

    return fAngle;
}

void QQuaternion::Lerp(const QBaseQuaternion &qQuat, const float_q &fProportion)
{
    // Separated from the equation to gain performance
    QQuaternion qAuxSum = (SQFloat::_1 - fProportion) * (*this) + fProportion * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor != SQFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::Slerp(const QBaseQuaternion &qQuat, const float_q &fProportion)
{
    // Assures that all quaternions are unit length
    QBaseQuaternion auxQuat;
    qQuat.As<const QQuaternion>().Normalize(auxQuat);
    this->Normalize();

    float_q fAngleB = acos_q(this->DotProduct(auxQuat));

    QE_ASSERT( !SQFloat::IsNaN(fAngleB) );

    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    QE_ASSERT( fAngleB != SQFloat::_0 && SQFloat::AreNotEquals(fAngleB, PI_Q) );

    const float_q &fInvSin = SQFloat::_1/sin_q(fAngleB);

    float_q fWeight1 = sin_q((SQFloat::_1 - fProportion) * fAngleB) * fInvSin;
    float_q fWeight2 = sin_q(fProportion * fAngleB) * fInvSin;

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * auxQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor != SQFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::UnitSlerp(const QBaseQuaternion &qQuat, const float_q &fProportion)
{
    float_q fAngleB = acos_q(this->DotProduct(qQuat));

    QE_ASSERT( !SQFloat::IsNaN(fAngleB) );

    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    QE_ASSERT( fAngleB != SQFloat::_0 && SQFloat::AreNotEquals(fAngleB, PI_Q) );

    const float_q &fInvSin = SQFloat::_1/sin_q(fAngleB);

    float_q fWeight1 = sin_q((SQFloat::_1 - fProportion) * fAngleB) * fInvSin;
    float_q fWeight2 = sin_q(fProportion * fAngleB) * fInvSin;

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = qAuxSum.GetLength();

    QE_ASSERT(fDivisor != SQFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::ToEulerAngles(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const
{
    // [TODO] Thund: Check whether this implementation corresponds to YawPitchRoll.
    const float_q fNorthAndSouthPoleCheckValue = this->x * this->y + this->z * this->w;

    // X (pitch or heading) and Z (roll or bank) checking
    if(SQFloat::AreEquals(fNorthAndSouthPoleCheckValue, SQFloat::_0_5)) // North pole
    {
        // The atan2 result is undefined when both parameters are equal to zero
        QE_ASSERT(this->x != SQFloat::_0 || this->w != SQFloat::_0);

        fRotationAngleX = SQFloat::_2 * atan2_q(this->x, this->w);
        fRotationAngleZ = SQFloat::_0;
    }
    else if(SQFloat::AreEquals(fNorthAndSouthPoleCheckValue, -SQFloat::_0_5)) // South pole
    {
        // The atan2 result is undefined when both parameters are equal to zero
        QE_ASSERT(this->x != SQFloat::_0 || this->w != SQFloat::_0);

        fRotationAngleX = -SQFloat::_2 * atan2_q(this->x, this->w);
        fRotationAngleZ = SQFloat::_0;
    }
    else
    {
        float_q fFirstParameter  = SQFloat::_2 * this->x * this->w - SQFloat::_2 * this->x * this->z;
        float_q fSecondParameter = SQFloat::_1 - SQFloat::_2 * this->y * this->y - SQFloat::_2 * this->z * this->z;

        // The atan2 result is undefined when both parameters are equal to zero
        QE_ASSERT(fFirstParameter != SQFloat::_0 || fSecondParameter != SQFloat::_0);

        fRotationAngleX = atan2_q(fFirstParameter, fSecondParameter);

        fFirstParameter = SQFloat::_2 * this->x * this->w - SQFloat::_2 * this->y * this->z;
        fSecondParameter = SQFloat::_1 - SQFloat::_2 * this->x * this->x - SQFloat::_2 * this->z * this->z;

        // The atan2 result is undefined when both parameters are equal to zero
        QE_ASSERT(fFirstParameter != SQFloat::_0 || fSecondParameter != SQFloat::_0);

        fRotationAngleZ = atan2_q(fFirstParameter, fSecondParameter);
    }

    fRotationAngleY = asin_q( SQFloat::_2 * this->x * this->y + SQFloat::_2 * this->z * this->w );

    QE_ASSERT( !SQFloat::IsNaN(fRotationAngleX) );
    QE_ASSERT( !SQFloat::IsNaN(fRotationAngleY) );
    QE_ASSERT( !SQFloat::IsNaN(fRotationAngleZ) );

}

void QQuaternion::ToAxisAngle(QBaseVector3 &vRotationAxis, float_q &fRotationAngle) const
{
   // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
	QE_ASSERT(SQFloat::Abs(this->w) <= SQFloat::_1);

	fRotationAngle = SQFloat::_2 * acos_q(this->w);

	// Singularity 1: Angle = 0 -> we choose arbitrary axis.
	if (SQFloat::IsZero(fRotationAngle))
	{
		vRotationAxis.x = SQFloat::_1;
		vRotationAxis.y = SQFloat::_0;
		vRotationAxis.z = SQFloat::_0;
	}
	// Singularity 2: Angle = PI -> we calculate axis.
	else if ( SQFloat::AreEquals(fRotationAngle, SQAngle::_Pi) )
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
        SQAngle::RadiansToDegrees(fRotationAngle, fRotationAngle);
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
           QE_L(", ") + SQFloat::ToString(this->y) +
           QE_L(", ") + SQFloat::ToString(this->z) +
           QE_L(", ") + SQFloat::ToString(this->w) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
