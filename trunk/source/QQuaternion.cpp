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
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QQuaternion QQuaternion::Identity(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1);


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QQuaternion::QQuaternion(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ)
{
    // Calculates half angle
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        float_q fHalfAngleXRad = DegreesToRadians(fAngleX, fHalfAngleXRad) * QFloat::_0_5;
        float_q fHalfAngleYRad = DegreesToRadians(fAngleY, fHalfAngleYRad) * QFloat::_0_5;
        float_q fHalfAngleZRad = DegreesToRadians(fAngleZ, fHalfAngleZRad) * QFloat::_0_5;
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
    this->Conjugate(); // [TODO] Thund: Use UnitReverse, when it exists.
}

QQuaternion QQuaternion::operator+(const QQuaternion &qQuat) const
{
    return QQuaternion(this->x + qQuat.x,
                       this->y + qQuat.y,
                       this->z + qQuat.z,
                       this->w + qQuat.w);
}

QQuaternion QQuaternion::operator-(const QQuaternion &qQuat) const
{
    return QQuaternion(this->x - qQuat.x,
                       this->y - qQuat.y,
                       this->z - qQuat.z,
                       this->w - qQuat.w);
}

QQuaternion QQuaternion::operator*(const QQuaternion &qQuat) const
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

QQuaternion QQuaternion::operator/(const QQuaternion &qQuat) const
{
    QE_ASSERT(qQuat.x && qQuat.y && qQuat.z && qQuat.w);

    return QQuaternion(this->x / qQuat.x,
                       this->y / qQuat.y,
                       this->z / qQuat.z,
                       this->w / qQuat.w);
}

QQuaternion QQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar);

    return QQuaternion( this->x / fScalar, 
                        this->y / fScalar, 
                        this->z / fScalar, 
                        this->w / fScalar);
}

QQuaternion operator*(const float_q &fScalar, const QQuaternion &qQuat)
{
    return QQuaternion( qQuat.x * fScalar, qQuat.y * fScalar, qQuat.z * fScalar, qQuat.w * fScalar);
}

void QQuaternion::Lerp(const QQuaternion &qQuat, const float_q &fProportion)
{
    // Separated from the equation to gain performance
    QQuaternion qAuxSum = (QFloat::_1 - fProportion) * (*this) + fProportion * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::Lerp(const QQuaternion &qQuat, const float_q &fProportion, QQuaternion &qOutQuat) const
{
    // Separated from the equation to gain performance
    QQuaternion qAuxSum = (QFloat::_1 - fProportion) * (*this) + fProportion * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor);

    qOutQuat = qAuxSum;
    qOutQuat /= fDivisor;
}

void QQuaternion::Slerp(const QQuaternion &qQuat, const float_q &fProportion)
{
    // Assures that all quaternions are unit length
    QQuaternion auxQuat = qQuat;
    auxQuat.Normalize();
    this->Normalize();

    float_q fAngleB = acos(this->DotProduct(auxQuat));

    // [TODO] Thund: Should we fix this or leave it in an erroneous state?
    QE_ASSERT( !QFloat::IsNaN(fAngleB) );
        
    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    // [TODO] Thund: Should we return a null quaternion instead of let the application crash? In other words, "show must go on"?
    QE_ASSERT( QFloat::IsNotZero(fAngleB) && QFloat::AreNotEquals(fAngleB, PI_Q) );

    float_q fWeight1 = sin((QFloat::_1 - fProportion) * fAngleB) / sin(fAngleB);
    float_q fWeight2 = sin(fProportion * fAngleB) / sin(fAngleB);

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * (*this) + fWeight2 * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor);

    *this = qAuxSum;
    *this /= fDivisor;
}

void QQuaternion::Slerp(const QQuaternion &qQuat, const float_q &fProportion, QQuaternion &qOutQuat) const
{
    // Assures that all quaternions are unit length
    QQuaternion auxQuat = qQuat;
    auxQuat.Normalize();
    this->Normalize(qOutQuat);

    float_q fAngleB = acos(qOutQuat.DotProduct(auxQuat));

    // [TODO] Thund: Should we fix this or leave it in an erroneous state?
    QE_ASSERT( !QFloat::IsNaN(fAngleB) );
        
    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    // [TODO] Thund: Should we return a null quaternion instead of let the application crash? In other words, "show must go on"?
    QE_ASSERT( QFloat::IsNotZero(fAngleB) && QFloat::AreNotEquals(fAngleB, PI_Q) );

    float_q fWeight1 = sin((QFloat::_1 - fProportion) * fAngleB) / sin(fAngleB);
    float_q fWeight2 = sin(fProportion * fAngleB) / sin(fAngleB);

    // Separated from the equation to gain performance
    QQuaternion qAuxSum = fWeight1 * qOutQuat + fWeight2 * qQuat;

    // Separated from the equation to check for "division by zero"
    float_q fDivisor = ( qAuxSum ).GetLength();

    QE_ASSERT(fDivisor);

    qOutQuat = qAuxSum;
    qOutQuat /= fDivisor;
}

string_q QQuaternion::ToString() const
{
    return QE_L("Q(") + QFloat::ToString(this->x) + QE_L(", ") + QFloat::ToString(this->y) + QE_L(", ") + QFloat::ToString(this->z) + QE_L(", ") + QFloat::ToString(this->w) + QE_L(")");
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
