// [TERMS&CONDITIONS]

#include "QDualQuaternion.h"

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
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
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
    return QDualQuaternion(QBaseQuaternion(this->r * fScalar), QBaseQuaternion(this->r * fScalar));
}

QDualQuaternion operator*(const float_q &fScalar, const QBaseDualQuaternion &dualQuat)
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
    QE_ASSERT(fScalar != SQFloat::_0);

    const float_q &fDivisor = SQFloat::_1/fScalar;

    return QDualQuaternion(QBaseQuaternion(this->r * fDivisor), QBaseQuaternion(this->d * fDivisor));
}

void QDualQuaternion::Transform(const QBaseDualQuaternion &transformation)
{
    QDualQuaternion dqConj(transformation);

    dqConj.DoubleConjugate();
    *this = ( transformation.As<const QDualQuaternion>() * (*this) ) * dqConj;


}

string_q QDualQuaternion::ToString() const
{
    return QE_L("DQ(") + SQFloat::ToString(this->r.x) +
           QE_L(", ")  + SQFloat::ToString(this->r.y) +
           QE_L(", ")  + SQFloat::ToString(this->r.z) +
           QE_L(", ")  + SQFloat::ToString(this->r.w) + QE_L(")") +
           QE_L("(")   + SQFloat::ToString(this->d.x) +
           QE_L(", ")  + SQFloat::ToString(this->d.y) +
           QE_L(", ")  + SQFloat::ToString(this->d.z) +
           QE_L(", ")  + SQFloat::ToString(this->d.w) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
