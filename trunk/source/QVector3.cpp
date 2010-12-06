// [TERMS&CONDITIONS]

#include "QVector3.h"

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

const QVector3 QVector3::ZeroVector    ( QFloat::_0,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::VectorOfOnes  ( QFloat::_1,  QFloat::_1,  QFloat::_1);
const QVector3 QVector3::UnitVectorX   ( QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::UnitVectorY   ( QFloat::_0,  QFloat::_1,  QFloat::_0);
const QVector3 QVector3::UnitVectorZ   ( QFloat::_0,  QFloat::_0,  QFloat::_1);
const QVector3 QVector3::UnitVectorInvX(-QFloat::_1,  QFloat::_0,  QFloat::_0);
const QVector3 QVector3::UnitVectorInvY( QFloat::_0, -QFloat::_1,  QFloat::_0);
const QVector3 QVector3::UnitVectorInvZ( QFloat::_0,  QFloat::_0, -QFloat::_1);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QVector3 QVector3::operator + (const QVector3 &v) const 
{ 
	return QVector3(this->x + v.x, this->y + v.y, this->z + v.z); 
}

QVector3 QVector3::operator - (const QVector3 &v) const 
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

QVector3 QVector3::operator / (const float_q &fValue) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (fValue);

	return QVector3(this->x/fValue, this->y/fValue, this->z/fValue);
}
	
QVector3 QVector3::operator / (const QBaseVector3 &v) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (v.x && v.y && v.z);

	return QVector3(this->x/v.x, this->y/v.y, this->z/v.z);
}

// Left float product 
QVector3 operator * (const float_q &fValue, const QVector3 &v)
{
	return QVector3(v.x*fValue, v.y*fValue, v.z*fValue);
}

std::string QVector3::ToString() 
{
	return "V3(" + QFloat::ToString(this->x) + ", " + QFloat::ToString(this->y) + ", " + QFloat::ToString(this->z) + ")";
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
