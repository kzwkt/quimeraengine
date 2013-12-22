//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "QTriangle2D.h"

#include "Assertions.h"
#include "QTransformationMatrix3x3.h"
#include "SQPoint.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;


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
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QTriangle2D::QTriangle2D()
{
}

QTriangle2D::QTriangle2D(const QTriangle2D &triangle) : QTriangle<QVector2>(triangle)
{
}

QTriangle2D::QTriangle2D(const QBaseTriangle<QVector2> &triangle) : QTriangle<QVector2>(triangle)
{
}

QTriangle2D::QTriangle2D(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC) : QTriangle<QVector2>(vA, vB, vC)
{
}

QTriangle2D::QTriangle2D(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) :
                        QTriangle<QVector2>(arValuesA, arValuesB, arValuesC)
{
}

QTriangle2D::QTriangle2D(const vf32_q &valueA, const vf32_q &valueB, const vf32_q &valueC) : QTriangle<QVector2>(valueA, valueB, valueC)
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

QTriangle2D& QTriangle2D::operator=(const QBaseTriangle<QVector2> &triangle)
{
    QBaseTriangle<QVector2>::operator=(triangle);
	return *this;
}

QTriangle2D QTriangle2D::Transform(const QTransformationMatrix3x3 &transformation) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Transform(transformation, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QVector2 QTriangle2D::GetCircumcenter() const
{
    // All the vertices shouldn't coincide
    QE_ASSERT( !(this->A == this->B && this->B == this->C) );

	//STEP 1: Obtain the gradient of height A.
	//
	// We can obtain the gradient of a line using this formula:
	// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
	const float_q gradientBC = (C.y - B.y) / (C.x - B.x);
	const float_q gradientHA = - SQFloat::_1 / gradientBC;

	//STEP 1.1: Obtain middle point of side BC
	const QVector2 middlePointBC = (C + B) * SQFloat::_0_5;

	//STEP 2: Obtain the gradient of height B.
	const float_q gradientAC = (C.y - A.y) / (C.x - A.x);
	const float_q gradientHB = - SQFloat::_1 / gradientAC;

	//STEP 2.1: Obtain middle point of side AC
	const QVector2 middlePointAC = (C + A) * SQFloat::_0_5;

	//STEP 3: Calculate the intersection of the perpendicular bisectors
	//
	// The gradient equations of the perpendicular bisectors are like this:
	// hA (identical) y - middlePointBC.y = m * (x - middlePointBC.x) -> y = m * x - m * middlePointBC.x + middlePointBC.y
	// hB (identical) y - middlePointAC.y = n * (x - middlePointAC.x) -> y = n * x - n * middlePointAC.x + middlePointAC.y
	//
	// The intersection point is that point where both formulas are equal.

	// Here we got x:
	// m * x - m * middlePointBC.x + middlePointBC.y = n * x - n * middlePointAC.x + middlePointAC.y
	// m * x - n * x = m * middlePointBC.x - middlePointBC.y - n * middlePointAC.x + middlePointAC.y
	// x = (m * middlePointBC.x - middlePointBC.y - n * middlePointAC.x + middlePointAC.y) / (m - n)
	QVector2 vCircumcenter;
    vCircumcenter.x = (gradientHA * middlePointBC.x - middlePointBC.y - gradientHB * middlePointAC.x + middlePointAC.y) / (gradientHA - gradientHB);

	// With x calculated we can now obtain y appliying the x to one of the equations explained before.
	vCircumcenter.y = gradientHA * vCircumcenter.x - gradientHA * middlePointBC.x + middlePointBC.y;

    return vCircumcenter;
}

QVector2 QTriangle2D::GetOrthocenter() const
{
    // All the vertices shouldn't coincide
    QE_ASSERT( !(this->A == this->B && this->B == this->C) );

	//STEP 1: Obtain the gradient of height A.
	//
	// We can obtain the gradient of a line using this formula:
	// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
	float_q gradientBC = (C.y - B.y) / (C.x - B.x);
	float_q gradientHA = - SQFloat::_1 / gradientBC;

	//STEP 2: Obtain the gradient of height B.
	float_q gradientAC = (C.y - A.y) / (C.x - A.x);
	float_q gradientHB = - SQFloat::_1 / gradientAC;

	//STEP 3: Calculate the intersection of the heights
	//
	// The gradient equations of the heights are like this:
	// hA (identical) y - A.y = m * (x - A.x) -> y = m * x - m * A.x + A.y
	// hB (identical) y - B.y = n * (x - B.x) -> y = n * x - n * B.x + B.y
	//
	// The intersection point is that point where both formulas are equal.

	// Here we got x:
	// m * x - m * A.x + A.y = n * x - n * B.x + B.y
	// m * x - n * x = m * A.x - A.y - n * B.x + B.y
	// x = (m * A.x - A.y - n * B.x + B.y) / (m - n)
    QVector2 vOrthocenter;
	vOrthocenter.x = (gradientHA * A.x - A.y - gradientHB * B.x + B.y) / (gradientHA - gradientHB);

	// With x calculated we can now obtain y appliying the x to one of the equations explained before.
	vOrthocenter.y = gradientHA * vOrthocenter.x - gradientHA * A.x + A.y;

    return vOrthocenter;
}

QTriangle2D QTriangle2D::Translate(const QBaseVector2 &vTranslation) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Translate(vTranslation, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Translate(fTranslationX, fTranslationY, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::Rotate(const float_q &fRotationAngle) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Rotate(fRotationAngle, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::Scale(const QBaseVector2 &vScale) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Scale(vScale, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::Scale(const float_q &fScaleX, const float_q &fScaleY) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::Scale(fScaleX, fScaleY, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::ScaleWithPivot(vScale, vPivot, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}

QTriangle2D QTriangle2D::ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const
{
    QTriangle2D auxTriangle = *this;
	SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_q(&auxTriangle, QVector2*), 3);
    return auxTriangle;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis