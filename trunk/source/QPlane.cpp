// [TERMS&CONDITIONS]

#include "QPlane.h"

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

const QPlane QPlane::ZeroPlane ( QFloat::_0,  QFloat::_0,  QFloat::_0,  QFloat::_0);
const QPlane QPlane::PlaneZX   ( QFloat::_0,  QFloat::_1,  QFloat::_0,  QFloat::_0);
const QPlane QPlane::PlaneXY   ( QFloat::_0,  QFloat::_0,  QFloat::_1,  QFloat::_0);
const QPlane QPlane::PlaneYZ   ( QFloat::_1,  QFloat::_0,  QFloat::_0,  QFloat::_0);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QPlane QPlane::operator * (const float_q &fValue) const
{
    return QPlane(this->a * fValue, this->b * fValue, this->c * fValue, this->d * fValue);
}

// Left float product 
QPlane operator * (const float_q &fValue, const QBasePlane &p)
{
    return QPlane(p.a * fValue, p.b * fValue, p.c * fValue, p.d * fValue);
}

QPlane QPlane::operator / (const float_q &fValue) const
{
    QE_ASSERT(fValue);

    return QPlane(this->a / fValue, this->b / fValue, this->c / fValue, this->d / fValue);
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
