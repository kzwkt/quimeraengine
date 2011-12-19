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

QQuaternion::QQuaternion(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ)
{
    // Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleXRad = SQAngle::DegreesToRadians(fAngleX, fHalfAngleXRad) * SQFloat::_0_5;
        float_q fHalfAngleYRad = SQAngle::DegreesToRadians(fAngleY, fHalfAngleYRad) * SQFloat::_0_5;
        float_q fHalfAngleZRad = SQAngle::DegreesToRadians(fAngleZ, fHalfAngleZRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleXRad = fAngleX * SQFloat::_0_5;
        const float_q& fHalfAngleYRad = fAngleY * SQFloat::_0_5;
        const float_q& fHalfAngleZRad = fAngleZ * SQFloat::_0_5;
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

QQuaternion::QQuaternion(const QBaseVector3 &vAxis, const float_q &fAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = SQAngle::DegreesToRadians(fAngle, fHalfAngleRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(fHalfAngleRad);

	// Please note the axis has to be normalized...

	this->x = vAxis.x * fSin;
	this->y = vAxis.y * fSin;
	this->z = vAxis.z * fSin;

	this->w = cos_q(fHalfAngleRad);
}

QQuaternion::QQuaternion(const QBaseVector4 &vAxis, const float_q &fAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = SQAngle::DegreesToRadians(fAngle, fHalfAngleRad) * SQFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fAngle * SQFloat::_0_5;
    #endif

	const float_q &fSin = sin_q(fHalfAngleRad);

	// Please note the axis has to be normalized...

	this->x = vAxis.x * fSin;
	this->y = vAxis.y * fSin;
	this->z = vAxis.z * fSin;

	this->w = cos_q(fHalfAngleRad);
}

QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x3> &m)
{
    QQuaternionImp(m);
}


QQuaternion::QQuaternion(const QTransformationMatrix<QMatrix4x4> &m)
{
    QQuaternionImp(m);
}


QQuaternion::QQuaternion(const QRotationMatrix3x3 &m)
{
    m.GetRotation(*this);
}

template <class MatrixType>
inline void QQuaternion::QQuaternionImp(const QTransformationMatrix<MatrixType> &m)
{
    m.GetRotation(*this);
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

QQuaternion QQuaternion::operator*(const QBaseVector3 &v) const
{
	QQuaternion qAux(v.x, v.y, v.z, SQFloat::_0);

    return *this * qAux;
}

QQuaternion QQuaternion::operator*(const QBaseVector4 &v) const
{
	QQuaternion qAux(v.x, v.y, v.z, v.w);

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

    return QQuaternion( this->x / fScalar,
                        this->y / fScalar,
                        this->z / fScalar,
                        this->w / fScalar);
}

QQuaternion operator*(const float_q &fScalar, const QBaseQuaternion &qQuat)
{
    return QQuaternion( qQuat.x * fScalar, qQuat.y * fScalar, qQuat.z * fScalar, qQuat.w * fScalar);
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
    reinterpret_cast<const QQuaternion&> (qQuat).Normalize(auxQuat);
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

    // [TODO] Thund: Should we fix this or leave it in an erroneous state?
    QE_ASSERT( !SQFloat::IsNaN(fAngleB) );

    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    // [TODO] Thund: Should we return a null quaternion instead of let the application crash? In other words, "show must go on"?
    QE_ASSERT( fAngleB != SQFloat::_0 && SQFloat::AreNotEquals(fAngleB, PI_Q) );

    // [TODO] jwladi: it might be better to do the following:
    // const float_q &fInvSin = SQFloat::_1/sin_q(fAngleB);

    float_q fWeight1 = sin_q((SQFloat::_1 - fProportion) * fAngleB) / sin_q(fAngleB);
    float_q fWeight2 = sin_q(fProportion * fAngleB) / sin_q(fAngleB);

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = qAuxSum.GetLength();

    QE_ASSERT(fDivisor != SQFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::ToAxisAngle(QBaseVector3 &vAxis, float_q &fAngle) const
{
   // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
	QE_ASSERT(SQFloat::Abs(this->w) <= SQFloat::_1);

	fAngle = SQFloat::_2 * acos_q(this->w);

	// Singularity 1: Angle = 0 -> we choose arbitrary axis.
	if (SQFloat::IsZero(fAngle))
	{
		vAxis.x = SQFloat::_1;
		vAxis.y = SQFloat::_0;
		vAxis.z = SQFloat::_0;
	}
	// Singularity 2: Angle = PI -> we calculate axis.
	else if ( SQFloat::AreEquals(fAngle, SQAngle::_Pi) )
	{
		vAxis.x = this->x;
		vAxis.y = this->y;
		vAxis.z = this->z;
	}
	else
	{
		const float_q &fInvSin = SQFloat::_1/sin_q(fAngle*SQFloat::_0_5);

		vAxis.x = this->x*fInvSin;
		vAxis.y = this->y*fInvSin;
		vAxis.z = this->z*fInvSin;
	}

	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        SQAngle::RadiansToDegrees(fAngle, fAngle);
    #endif
}

void QQuaternion::ToAxisAngle(QBaseVector4 &vAxis, float_q &fAngle) const
{
    QBaseVector3 vAux;

    this->ToAxisAngle(vAux, fAngle);

    vAxis.x =  vAux.x;
    vAxis.y =  vAux.y;
    vAxis.z =  vAux.z;
    vAxis.w = SQFloat::_0;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
