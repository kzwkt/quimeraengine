// [TERMS&CONDITIONS]

#include "QVector4.h"

#include "QQuaternion.h"
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
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QVector4 QVector4::ZeroVector    ( QFloat::_0,  QFloat::_0,  QFloat::_0,  QFloat::_0);
const QVector4 QVector4::ZeroPoint     ( QFloat::_0,  QFloat::_0,  QFloat::_0,  QFloat::_1);
const QVector4 QVector4::VectorOfOnes  ( QFloat::_1,  QFloat::_1,  QFloat::_1,  QFloat::_1);
const QVector4 QVector4::UnitVectorX   ( QFloat::_1,  QFloat::_0,  QFloat::_0,  QFloat::_0);
const QVector4 QVector4::UnitVectorY   ( QFloat::_0,  QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector4 QVector4::UnitVectorZ   ( QFloat::_0,  QFloat::_0,  QFloat::_1,  QFloat::_0);
const QVector4 QVector4::UnitVectorInvX(-QFloat::_1,  QFloat::_0,  QFloat::_0,  QFloat::_0);
const QVector4 QVector4::UnitVectorInvY( QFloat::_0, -QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector4 QVector4::UnitVectorInvZ( QFloat::_0,  QFloat::_0, -QFloat::_1,  QFloat::_0);

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QVector4 QVector4::operator + (const QBaseVector4 &v) const 
{ 
    return QVector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w); 
}

QVector4 QVector4::operator + (const QBaseVector3 &v) const 
{ 
    return QVector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w); 
}

QVector4 QVector4::operator - (const QBaseVector4 &v) const 
{ 
    return QVector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w); 
}

QVector4 QVector4::operator - (const QBaseVector3 &v) const 
{ 
    return QVector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w); 
}

QVector4 QVector4::operator * (const float_q &fValue) const 
{ 
    return QVector4(this->x*fValue, this->y*fValue, this->z*fValue, this->w*fValue); 
} 

QVector4 QVector4::operator * (const QBaseVector4 &v) const 
{ 
    return QVector4(this->x*v.x, this->y*v.y, this->z*v.z, this->w*v.w); 
}

QVector4 QVector4::operator * (const QBaseMatrix4x4 &m) const 
{ 
    return QVector4(this->x*m.ij[0][0] + this->y*m.ij[1][0] + this->z*m.ij[2][0] + this->w*m.ij[3][0],
                    this->x*m.ij[0][1] + this->y*m.ij[1][1] + this->z*m.ij[2][1] + this->w*m.ij[3][1],
                    this->x*m.ij[0][2] + this->y*m.ij[1][2] + this->z*m.ij[2][2] + this->w*m.ij[3][2],
                    this->x*m.ij[0][3] + this->y*m.ij[1][3] + this->z*m.ij[2][3] + this->w*m.ij[3][3]); 
}

QBaseVector3 QVector4::operator * (const QBaseMatrix4x3 &m) const
{
    return QBaseVector3(this->x * m.ij[0][0] + this->y * m.ij[1][0] + this->z * m.ij[2][0] + this->w * m.ij[3][0],
                        this->x * m.ij[0][1] + this->y * m.ij[1][1] + this->z * m.ij[2][1] + this->w * m.ij[3][1],
                        this->x * m.ij[0][2] + this->y * m.ij[1][2] + this->z * m.ij[2][2] + this->w * m.ij[3][2]);

}

QVector4 QVector4::operator / (const float_q &fValue) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (fValue != QFloat::_0);

    return QVector4(this->x/fValue, this->y/fValue, this->z/fValue, this->w/fValue);
}
    
QVector4 QVector4::operator / (const QBaseVector4 &v) const
{
    // Checkout to avoid division by 0
    QE_ASSERT (v.x != QFloat::_0 && v.y != QFloat::_0 &&
        v.z != QFloat::_0 && v.w != QFloat::_0);

    return QVector4(this->x/v.x, this->y/v.y, this->z/v.z, this->w/v.w);
}

// Asignment operators

QVector4& QVector4::operator *= (const QBaseMatrix4x4 &m) 
{ 
    QVector4 vAux(*this);

    this->x = vAux.x*m.ij[0][0] + vAux.y*m.ij[1][0] + vAux.z*m.ij[2][0] + vAux.w*m.ij[3][0];
    this->y = vAux.x*m.ij[0][1] + vAux.y*m.ij[1][1] + vAux.z*m.ij[2][1] + vAux.w*m.ij[3][1];
    this->z = vAux.x*m.ij[0][2] + vAux.y*m.ij[1][2] + vAux.z*m.ij[2][2] + vAux.w*m.ij[3][2];
    this->w = vAux.x*m.ij[0][3] + vAux.y*m.ij[1][3] + vAux.z*m.ij[2][3] + vAux.w*m.ij[3][3];

    return *this; 
}

//Unary operators

QVector4 QVector4::operator- () const
{
    return QVector4(-this->x, -this->y, -this->z, -this->w);
}

// Left float product 
QVector4 operator * (const float_q &fValue, const QBaseVector4 &v)
{
    return QVector4(v.x*fValue, v.y*fValue, v.z*fValue, v.w*fValue);
}

void QVector4::CrossProduct(const QBaseVector4 &v) 
{ 
    QVector4 aux(*this);

    this->x = v.y*aux.z - v.z*aux.y;
    this->y = v.z*aux.x - v.x*aux.z;
    this->z = v.x*aux.y - v.y*aux.x; 
}

void QVector4::Transform(const QQuaternion &qR)
{
    QQuaternion qAux(this->x, this->y, this->z, QFloat::_0);
    QQuaternion qConj;

    qR.Conjugate(qConj);

    qAux = (qR * qAux) * qConj;
        
    this->x = qAux.x;
    this->y = qAux.y;
    this->z = qAux.z;
}

void QVector4::Transform(const QDualQuaternion &dqTransf)
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

void QVector4::Transform(const QRotationMatrix3x3 &mRot)
{
    QVector4 vAux;

    vAux.x = this->x * mRot.ij[0][0] + this->y * mRot.ij[1][0] + this->z * mRot.ij[2][0];
    vAux.y = this->x * mRot.ij[0][1] + this->y * mRot.ij[1][1] + this->z * mRot.ij[2][1];
    vAux.z = this->x * mRot.ij[0][2] + this->y * mRot.ij[1][2] + this->z * mRot.ij[2][2];
    vAux.w = this->w;
        
    *this = vAux;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
