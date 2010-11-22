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

const QVector3 QVector3::ZeroVector(0.0f, 0.0f, 0.0f);
const QVector3 QVector3::VectorOfOnes(1.0f, 1.0f, 1.0f);
const QVector3 QVector3::UnitVectorX(1.0f, 0.0f, 0.0f);
const QVector3 QVector3::UnitVectorY(0.0f, 1.0f, 0.0f);
const QVector3 QVector3::UnitVectorZ(0.0f, 0.0f, 1.0f);
const QVector3 QVector3::UnitVectorInvX(-1.0f, 0.0f, 0.0f);
const QVector3 QVector3::UnitVectorInvY(0.0f, -1.0f, 0.0f);
const QVector3 QVector3::UnitVectorInvZ(0.0f, 0.0f, -1.0f);

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
	return QVector3(x + v.x, y + v.y, z + v.z); 
}

QVector3 QVector3::operator - (const QVector3 &v) const 
{ 
	return QVector3(x - v.x, y - v.y, z - v.z); 
}

QVector3 QVector3::operator * (const float_q &fValue) const 
{ 
	return QVector3(x*fValue, y*fValue, z*fValue); 
} 

QVector3 QVector3::operator * (const QBaseVector3 &v) const 
{ 
	return QVector3(x*v.x, y*v.y, z*v.z); 
}

QVector3 QVector3::operator / (const float_q &fValue) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (fValue);

	return QVector3(x/fValue, y/fValue, z/fValue);
}
	
QVector3 QVector3::operator / (const QBaseVector3 &v) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (v.x && v.y && v.z);

	return QVector3(x/v.x, y/v.y, z/v.z);
}

// Left float product 
QVector3 operator * (const float_q &fValue, const QVector3 &v)
{
	return QVector3(v.x*fValue, v.y*fValue, v.z*fValue);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
