// [TERMS&CONDITIONS]

#include "QQuaternion.h"
#include "MathDefinitions.h"

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
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QQuaternion QQuaternion::Identity(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1);

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
        float_q fHalfAngleXRad = QAngle::DegreesToRadians(fAngleX, fHalfAngleXRad) * QFloat::_0_5;
        float_q fHalfAngleYRad = QAngle::DegreesToRadians(fAngleY, fHalfAngleYRad) * QFloat::_0_5;
        float_q fHalfAngleZRad = QAngle::DegreesToRadians(fAngleZ, fHalfAngleZRad) * QFloat::_0_5;
    #else
        const float_q& fHalfAngleXRad = fAngleX * QFloat::_0_5;
        const float_q& fHalfAngleYRad = fAngleY * QFloat::_0_5;
        const float_q& fHalfAngleZRad = fAngleZ * QFloat::_0_5;
    #endif

    float_q cx = cos(fHalfAngleXRad);
    float_q cy = cos(fHalfAngleYRad);
    float_q cz = cos(fHalfAngleZRad);
    float_q sx = sin(fHalfAngleXRad);
    float_q sy = sin(fHalfAngleYRad);
    float_q sz = sin(fHalfAngleZRad);

    this->x = sx * sy * cz + cx * cy * sz;
    this->y = sx * cy * cz + cx * sy * sz;
    this->z = cx * sy * cz - sx * cy * sz;
    this->w = cx * cy * cz - sx * sy * sz;

    this->Normalize();

    // Since Quimera Engine uses left-handed system, the quaternion must be reverted
    this->UnitReverse();
}

QQuaternion::QQuaternion(const QBaseVector3 &vAxis, const float_q &fAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = QAngle::DegreesToRadians(fAngle, fHalfAngleRad) * QFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fAngle * QFloat::_0_5;
    #endif

	const float_q &fSin = sin(fHalfAngleRad);

	this->x = vAxis.x * fSin;
	this->y = vAxis.y * fSin;
	this->z = vAxis.z * fSin;
	this->w = cos(fHalfAngleRad);

	this->Normalize();
}

QQuaternion::QQuaternion(const QBaseVector4 &vAxis, const float_q &fAngle)
{
	// Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleRad = QAngle::DegreesToRadians(fAngle, fHalfAngleRad) * QFloat::_0_5;
    #else
        const float_q& fHalfAngleRad = fAngle * QFloat::_0_5;
    #endif

	const float_q &fSin = sin(fHalfAngleRad);

	this->x = vAxis.x * fSin;
	this->y = vAxis.y * fSin;
	this->z = vAxis.z * fSin;
	this->w = cos(fHalfAngleRad);

	this->Normalize();
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
    return QQuaternion( this->w * qQuat.x + this->x * qQuat.w + this->y * qQuat.z - this->z * qQuat.y,
                        this->w * qQuat.y + this->y * qQuat.w + this->z * qQuat.x - this->x * qQuat.z,
                        this->w * qQuat.z + this->z * qQuat.w + this->x * qQuat.y - this->y * qQuat.x,
                        this->w * qQuat.w - this->x * qQuat.x - this->y * qQuat.y - this->z * qQuat.z);
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
	QQuaternion qAux(v.x, v.y, v.z, QFloat::_0);

    return *this * qAux;
}

QQuaternion QQuaternion::operator*(const QBaseVector4 &v) const
{
	QQuaternion qAux(v.x, v.y, v.z, v.w);

    return *this * qAux;
}
QQuaternion QQuaternion::operator/(const QBaseQuaternion &qQuat) const
{
    QE_ASSERT(qQuat.x != QFloat::_0 && qQuat.y != QFloat::_0 && 
        qQuat.z != QFloat::_0 && qQuat.w != QFloat::_0);

    return QQuaternion(this->x / qQuat.x,
                       this->y / qQuat.y,
                       this->z / qQuat.z,
                       this->w / qQuat.w);
}

QQuaternion QQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != QFloat::_0);

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
    QQuaternion qAuxSum = (QFloat::_1 - fProportion) * (*this) + fProportion * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor != QFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::Slerp(const QBaseQuaternion &qQuat, const float_q &fProportion)
{
    // Assures that all quaternions are unit length
    QBaseQuaternion auxQuat;
    reinterpret_cast<const QQuaternion&> (qQuat).Normalize(auxQuat);
    this->Normalize();

    float_q fAngleB = acos(this->DotProduct(auxQuat));

    // [TODO] Thund: Should we fix this or leave it in an erroneous state?
    QE_ASSERT( !QFloat::IsNaN(fAngleB) );
        
    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    // [TODO] Thund: Should we return a null quaternion instead of let the application crash? In other words, "show must go on"?
    QE_ASSERT( fAngleB != QFloat::_0 && QFloat::AreNotEquals(fAngleB, PI_Q) );

    // [TODO] jwladi: it might be better to do the following:
    // const float_q &fInvSin = QFloat::_1/sin(fAngleB);

    float_q fWeight1 = sin((QFloat::_1 - fProportion) * fAngleB) / sin(fAngleB);
    float_q fWeight2 = sin(fProportion * fAngleB) / sin(fAngleB);

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * auxQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor != QFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::UnitSlerp(const QBaseQuaternion &qQuat, const float_q &fProportion)
{
    float_q fAngleB = acos(this->DotProduct(qQuat));

    // [TODO] Thund: Should we fix this or leave it in an erroneous state?
    QE_ASSERT( !QFloat::IsNaN(fAngleB) );
        
    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    // [TODO] Thund: Should we return a null quaternion instead of let the application crash? In other words, "show must go on"?
    QE_ASSERT( fAngleB != QFloat::_0 && QFloat::AreNotEquals(fAngleB, PI_Q) );

    // [TODO] jwladi: it might be better to do the following:
    // const float_q &fInvSin = QFloat::_1/sin(fAngleB);

    float_q fWeight1 = sin((QFloat::_1 - fProportion) * fAngleB) / sin(fAngleB);
    float_q fWeight2 = sin(fProportion * fAngleB) / sin(fAngleB);

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = qAuxSum.GetLength();

    QE_ASSERT(fDivisor != QFloat::_0);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::ToAxisAngle(QBaseVector3 &vAxis, float_q &fAngle) const
{
   // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
	QE_ASSERT(abs(this->w) <= QFloat::_1);

	fAngle = QFloat::_2 * acos(this->w);

	// Singularity 1: Angle = 0 -> we choose arbitrary axis.
	if (QFloat::IsZero(fAngle)) 
	{
		vAxis.x = QFloat::_1;
		vAxis.y = QFloat::_0;
		vAxis.z = QFloat::_0;
	}
	// Singularity 2: Angle = PI -> we calculate axis.
	else if ( QFloat::AreEquals(fAngle, QAngle::_Pi) ) 
	{
		vAxis.x = this->x;
		vAxis.y = this->y;
		vAxis.z = this->z;		
	}
	else
	{
		const float_q &fInvSin = QFloat::_1/sin(fAngle*QFloat::_0_5);
		
		vAxis.x = this->x*fInvSin;
		vAxis.y = this->y*fInvSin;
		vAxis.z = this->z*fInvSin;		
	}

	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        QAngle::RadiansToDegrees(fAngle, fAngle);
    #endif
}

void QQuaternion::ToAxisAngle(QBaseVector4 &vAxis, float_q &fAngle) const
{
    QBaseVector3 vAux;

    this->ToAxisAngle(vAux, fAngle);

    vAxis.x =  vAux.x;
    vAxis.y =  vAux.y;
    vAxis.z =  vAux.z;
    vAxis.w = QFloat::_0;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
