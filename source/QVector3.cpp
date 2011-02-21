// [TERMS&CONDITIONS]

#include "QVector3.h"

#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "QSpaceConversionMatrix.h"

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
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QVector3 QVector3::ZeroVector    ( QFloat::_0,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::VectorOfOnes  ( QFloat::_1,  QFloat::_1,  QFloat::_1);
const QVector3 QVector3::UnitVectorX   ( QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::UnitVectorY   ( QFloat::_0,  QFloat::_1,  QFloat::_0);
const QVector3 QVector3::UnitVectorZ   ( QFloat::_0,  QFloat::_0,  QFloat::_1);
const QVector3 QVector3::UnitVectorInvX(-QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::UnitVectorInvY( QFloat::_0, -QFloat::_1,  QFloat::_0);
const QVector3 QVector3::UnitVectorInvZ( QFloat::_0,  QFloat::_0, -QFloat::_1);

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QVector3 QVector3::operator + (const QBaseVector3 &v) const 
{ 
    return QVector3(this->x + v.x, this->y + v.y, this->z + v.z); 
}

QVector3 QVector3::operator - (const QBaseVector3 &v) const 
{ 
    return QVector3(this->x - v.x, this->y - v.y, this->z - v.z); 
}

QVector3 QVector3::operator * (const float_q &fValue) const 
{ 
    return QVector3(this->x*fValue, this->y*fValue, this->z*fValue); 
} 

QVector3 QVector3::operator * (const QBaseVector3 &v) const 
{ 
    return QVector3(this->x*v.x, this->y*v.y, this->z*v.z); 
}

QVector3 QVector3::operator * (const QBaseMatrix3x3 &m) const
{
    return QVector3(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                    this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                    this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2]);

}

QBaseVector4 QVector3::operator * (const QBaseMatrix3x4 &m) const
{
    return QBaseVector4(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                        this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                        this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2],
                        this->x * m.ij[0][3] + this->y * m.ij[1][3] + this->z * m.ij[2][3]);

}

QVector3 QVector3::operator / (const float_q &fValue) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fValue != QFloat::_0);

    return QVector3(this->x/fValue, this->y/fValue, this->z/fValue);
}
    
QVector3 QVector3::operator / (const QBaseVector3 &v) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (v.x != QFloat::_0 && v.y != QFloat::_0 && v.z != QFloat::_0);

    return QVector3(this->x/v.x, this->y/v.y, this->z/v.z);
}

// Product and assignment by a matrix 3x3
QVector3& QVector3::operator *= (const QBaseMatrix3x3 &m) 
{ 
    QVector3 aux( this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0],
                  this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1],
                  this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2]);

    this->x = aux.x;
    this->y = aux.y;
    this->z = aux.z;

    return *this; 
}

// Left float product 
QVector3 operator * (const float_q &fValue, const QBaseVector3 &v)
{
    return QVector3(v.x*fValue, v.y*fValue, v.z*fValue);
}

//Unary operators

QVector3 QVector3::operator- () const
{
    return QVector3(-this->x, -this->y, -this->z);
}

void QVector3::CrossProduct(const QBaseVector3 &v) 
{ 
    QVector3 aux(*this);

    this->x = v.y*aux.z - v.z*aux.y;
    this->y = v.z*aux.x - v.x*aux.z;
    this->z = v.x*aux.y - v.y*aux.x; 
}

void QVector3::Transform(const QQuaternion &qR)
{
    QQuaternion qAux(this->x, this->y, this->z, QFloat::_0);
    QQuaternion qConj;

    qR.Conjugate(qConj);

    qAux = (qR * qAux) * qConj;
        
    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector3::Transform(const QDualQuaternion &dqTransf)
{
    QDualQuaternion dqAux(QBaseQuaternion(QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_1), 
                        QBaseQuaternion(this->x, this->y, this->z, QFloat::_0));
    QDualQuaternion dqConj;
    
    dqTransf.DoubleConjugate(dqConj);
    
    dqAux = (dqTransf * dqAux ) * dqConj;
      
    this->x = dqAux.d.x;
    this->y = dqAux.d.y;
    this->z = dqAux.d.z;      
}

void QVector3::Transform(const QSpaceConversionMatrix &mTransf)
{
	QVector3 vAux;

    vAux.x = this->x * mTransf.ij[0][0] + this->y * mTransf.ij[1][0] + this->z * mTransf.ij[2][0] + mTransf.ij[3][0];
    vAux.y = this->x * mTransf.ij[0][1] + this->y * mTransf.ij[1][1] + this->z * mTransf.ij[2][1] + mTransf.ij[3][1];
    vAux.z = this->x * mTransf.ij[0][2] + this->y * mTransf.ij[1][2] + this->z * mTransf.ij[2][2] + mTransf.ij[3][2];
        
    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
