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
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QDualQuaternion QDualQuaternion::Identity(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1),
                                                QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QDualQuaternion QDualQuaternion::operator + (const QBaseDualQuaternion &dqQuat) const
{
    return QDualQuaternion (QBaseQuaternion(this->r + dqQuat.r), QBaseQuaternion(this->d + dqQuat.d));
}

QDualQuaternion QDualQuaternion::operator - (const QBaseDualQuaternion &dqQuat) const
{
    return QDualQuaternion (QBaseQuaternion(this->r - dqQuat.r), QBaseQuaternion(this->d - dqQuat.d));
}

QDualQuaternion QDualQuaternion::operator * (const QBaseDualQuaternion &dqQuat) const
{
    return QDualQuaternion (QBaseQuaternion(this->r * dqQuat.r), QBaseQuaternion(this->r * dqQuat.d + this->d * dqQuat.r));
}

QDualQuaternion QDualQuaternion::operator*(const float_q &fScalar) const
{
    return QDualQuaternion(QBaseQuaternion(this->r * fScalar), QBaseQuaternion(this->r * fScalar));
}

QDualQuaternion operator*(const float_q &fScalar, const QBaseDualQuaternion &dqQuat)
{
    return QDualQuaternion(QBaseQuaternion(dqQuat.r * fScalar), QBaseQuaternion(dqQuat.d * fScalar));
}

QDualQuaternion QDualQuaternion::operator * (const QBaseVector3 &v) const
{
    // Vector3 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                       QBaseQuaternion(v.x, v.y, v.z, QFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator * (const QBaseVector4 &v) const
{
    // Vector4 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    QDualQuaternion auxQ(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                         QBaseQuaternion(v.x, v.y, v.z, QFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

QDualQuaternion QDualQuaternion::operator/(const float_q &fScalar) const
{
    QE_ASSERT(fScalar != QFloat::_0);

    return QDualQuaternion(QBaseQuaternion(this->r / fScalar), QBaseQuaternion(this->d / fScalar));
}

void QDualQuaternion::Transform(const QBaseDualQuaternion &dqTransf)
{
    QDualQuaternion dqConj(dqTransf);

    dqConj.DoubleConjugate();
    *this = ( reinterpret_cast<const QDualQuaternion&>(dqTransf) * (*this) ) * dqConj;
}

string_q QDualQuaternion::ToString() const
{
    return QE_L("DQ(") + QFloat::ToString(this->r.x) + 
            QE_L(", ")  + QFloat::ToString(this->r.y) + 
            QE_L(", ")  + QFloat::ToString(this->r.z) +
            QE_L(", ")  + QFloat::ToString(this->r.w) + QE_L(")") +
            QE_L("(")   + QFloat::ToString(this->d.x) + 
            QE_L(", ")  + QFloat::ToString(this->d.y) + 
            QE_L(", ")  + QFloat::ToString(this->d.z) +
            QE_L(", ")  + QFloat::ToString(this->d.w) + QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
