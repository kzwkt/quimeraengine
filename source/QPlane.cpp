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
//##################		    |  CONSTANTS INITIALIZATION  |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QPlane QPlane::ZeroPlane ( SQFloat::_0,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
const QPlane QPlane::PlaneZX   ( SQFloat::_0,  SQFloat::_1,  SQFloat::_0,  SQFloat::_0);
const QPlane QPlane::PlaneXY   ( SQFloat::_0,  SQFloat::_0,  SQFloat::_1,  SQFloat::_0);
const QPlane QPlane::PlaneYZ   ( SQFloat::_1,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);

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
    QE_ASSERT(fValue != SQFloat::_0);

    return QPlane(this->a / fValue, this->b / fValue, this->c / fValue, this->d / fValue);
}

EQSpaceRelation QPlane::SpaceRelation(const QBasePlane &p) const
{
    // Cross product.
    if (SQFloat::IsZero(p.b*this->c - p.c*this->b) && 
        SQFloat::IsZero(p.c*this->a - p.a*this->c) && 
        SQFloat::IsZero(p.a*this->b - p.b*this->a))
    {

        QPlane plAux1(p), plAux2(*this);

        plAux1.Normalize();
        plAux2.Normalize();

        // They are the same plane.
        if (plAux1 == plAux2)
            return EQSpaceRelation::E_Contained;
        // They are parallel planes.
        else if (SQFloat::IsNegative(plAux1.d - plAux2.d))
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_PositiveSide;
    }
    else
        return EQSpaceRelation::E_BothSides; 
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
