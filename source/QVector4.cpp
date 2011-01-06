// [TERMS&CONDITIONS]

#include "QVector4.h"

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

QVector4 QVector4::operator - (const QBaseVector4 &v) const 
{ 
    return QVector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w); 
}

QVector4 QVector4::operator * (const float_q &fValue) const 
{ 
    return QVector4(this->x*fValue, this->y*fValue, this->z*fValue, this->w*fValue); 
} 

QVector4 QVector4::operator * (const QBaseVector4 &v) const 
{ 
    return QVector4(this->x*v.x, this->y*v.y, this->z*v.z, this->w*v.w); 
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


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
