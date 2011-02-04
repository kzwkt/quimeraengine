// [TERMS&CONDITIONS]

#include "QVector2.h"

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

const QVector2 QVector2::ZeroVector    ( QFloat::_0,  QFloat::_0);
const QVector2 QVector2::VectorOfOnes  ( QFloat::_1,  QFloat::_1);
const QVector2 QVector2::UnitVectorX   ( QFloat::_1,  QFloat::_0);
const QVector2 QVector2::UnitVectorY   ( QFloat::_0,  QFloat::_1);
const QVector2 QVector2::UnitVectorInvX(-QFloat::_1,  QFloat::_0);
const QVector2 QVector2::UnitVectorInvY( QFloat::_0, -QFloat::_1);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QVector2 QVector2::operator - () const 
{ 
	return QVector2(-this->x, -this->y); 
}

QVector2 QVector2::operator + (const QVector2 &v) const 
{ 
	return QVector2(this->x + v.x, this->y + v.y); 
}

QVector2 QVector2::operator - (const QVector2 &v) const 
{ 
	return QVector2(this->x - v.x, this->y - v.y); 
}

QVector2 QVector2::operator * (const float_q &fValue) const 
{ 
	return QVector2(this->x*fValue, this->y*fValue); 
} 

QVector2 QVector2::operator * (const QBaseVector2 &v) const 
{ 
	return QVector2(this->x*v.x, this->y*v.y); 
}

QVector2 QVector2::operator * (const QBaseMatrix2x2 &m) const
{
	return QVector2(this->x * m.ij[0][0] + this->y * m.ij[1][0],
                    this->x * m.ij[0][1] + this->y * m.ij[1][1]);
}

QVector2 QVector2::operator / (const float_q &fValue) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (fValue);

	return QVector2(this->x/fValue, this->y/fValue);
}
	
QVector2 QVector2::operator / (const QBaseVector2 &v) const
{
	// Checkout to avoid division by 0
	QE_ASSERT (v.x && v.y);

	return QVector2(this->x/v.x, this->y/v.y);
}

// Left float product 
QVector2 operator * (const float_q &fValue, const QVector2 &v)
{
	return QVector2(v.x*fValue, v.y*fValue);
}

QVector2 QVector2::GetPerpendicular() const 
{ 
	return QVector2(this->y, -this->x); 
}

string_q QVector2::ToString() 
{
	return QE_L("V2(") + QFloat::ToString(this->x) + 
		   QE_L(", ")  + QFloat::ToString(this->y) + 
		   QE_L(")");
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
