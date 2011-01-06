// [TERMS&CONDITIONS]

#include "QDualQuaternion.h"

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
//##################		    |		  CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorType> 
QDualQuaternion::QDualQuaternion(const QBaseQuaternion &qR, const VectorType &vD)
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                         QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    *this = Desp * Rot;
}

template <class VectorType>
QDualQuaternion::QDualQuaternion(const VectorType &vD, const QBaseQuaternion &qR) 
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    *this = Rot * Desp;
}

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
    return QDualQuaternion (QBaseQuaternion(this->r * dqQuat.r), QBaseQuaternion(this->r * dqQuat.d + dqQuat.r * this->d));
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
    *this = ( static_cast<QDualQuaternion>(dqTransf) * (*this) ) * dqConj;
}

void QDualQuaternion::Transform(const QBaseDualQuaternion &dqTransf, QBaseDualQuaternion &dqOut) const
{
    QDualQuaternion dqConj(dqTransf);

    dqConj.DoubleConjugate();
    dqOut = ( static_cast<QDualQuaternion>(dqTransf) * (*this) ) * dqConj;
}

template <class VectorType>
void QDualQuaternion::TransformRotationFirst(const QBaseQuaternion &qR, const VectorType &vD) 
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    QDualQuaternion dqTransf = Desp * Rot;

    this->Transform(dqTransf);
}

template <class VectorType>
void QDualQuaternion::TransformTranslationFirst(const VectorType &vD, const QBaseQuaternion &qR) 
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    QDualQuaternion dqTransf = Rot * Desp;

    this->Transform(dqTransf);
}

template <class VectorType>
void QDualQuaternion::TransformRotationFirst(const QBaseQuaternion &qR, const VectorType &vD, const QBaseDualQuaternion &dqOut) 
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    QDualQuaternion dqTransf = Desp * Rot;

    this->Transform(dqTransf, &dqOut);
}

template <class VectorType>
void QDualQuaternion::TransformTranslationFirst(const VectorType &vD, const QBaseQuaternion &qR, const QBaseDualQuaternion &dqOut) 
{ 
    QDualQuaternion Rot(qR, QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0));
    QDualQuaternion Desp(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                                QBaseQuaternion(vD.x, vD.y, vD.z, QFloat::_0)); 

    QDualQuaternion dqTransf = Rot * Desp;

    this->Transform(dqTransf, &dqOut);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
