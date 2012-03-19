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
    QE_ASSERT(fScalar != SQFloat::_0)

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QDualQuaternion(QBaseQuaternion(this->r * DIVISOR), QBaseQuaternion(this->d * DIVISOR));
}

QDualQuaternion QDualQuaternion::Transform(const QBaseDualQuaternion &transformation) const
{
    return QDualQuaternion(transformation.As<const QDualQuaternion>() * (*this) * transformation.As<const QDualQuaternion>().DoubleConjugate());
}

string_q QDualQuaternion::ToString() const
{
    return QE_L("DQ(r(") + r.ToString() +
           QE_L("),d(")  + d.ToString() + QE_L("))");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
