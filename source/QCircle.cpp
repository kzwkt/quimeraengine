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

#include "QCircle.h"

#include "SQPoint.h"
#include "MathDefinitions.h"

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

QCircle::QCircle()
{
}

QCircle::QCircle(const QCircle &circle) : QOrb<QVector2>(circle)
{
}

QCircle::QCircle(const QBaseOrb<QVector2> &orb) : QOrb<QVector2>(orb)
{
}

QCircle::QCircle(const QVector2 &vCenter, const float_q &fRadius) : QOrb<QVector2>(vCenter, fRadius)
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

QCircle& QCircle::operator=(const QBaseOrb<QVector2> &orb)
{
    QBaseOrb<QVector2>::operator=(orb);
    return *this;
}

QCircle QCircle::Translate(const QBaseVector2 &vTranslation) const
{
    QCircle auxCircle = *this;
    SQPoint::Translate(vTranslation, &auxCircle.Center, 1);
    return auxCircle;
}

QCircle QCircle::Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
{
    QCircle auxCircle = *this;
    SQPoint::Translate(fTranslationX, fTranslationY, &auxCircle.Center, 1);
    return auxCircle;
}

QCircle QCircle::Rotate(const float_q &fRotationAngle) const
{
    QCircle auxCircle = *this;
    SQPoint::Rotate(fRotationAngle, &auxCircle.Center, 1);
    return auxCircle;
}

QCircle QCircle::RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
{
    QCircle auxCircle = *this;
    SQPoint::RotateWithPivot(fRotationAngle, vPivot, &auxCircle.Center, 1);
    return auxCircle;
}

QCircle QCircle::Scale(const QBaseVector2 &vScale, const float_q &fRadiusScale) const
{
    QCircle auxCircle = *this;
    SQPoint::Scale(vScale, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

QCircle QCircle::Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fRadiusScale) const
{
    QCircle auxCircle = *this;
    SQPoint::Scale(fScaleX, fScaleY, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

QCircle QCircle::ScaleWithPivot(const QBaseVector2 &vScale, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
{
    QCircle auxCircle = *this;
    SQPoint::ScaleWithPivot(vScale, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

QCircle QCircle::ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
{
    QCircle auxCircle = *this;
    SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

QCircle QCircle::Transform(const QTransformationMatrix3x3 &transformation, const float_q &fRadiusScale) const
{
    QCircle auxCircle = *this;
    SQPoint::Transform(transformation, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

QCircle QCircle::TransformWithPivot(const QTransformationMatrix3x3 &transformation, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
{
    QCircle auxCircle = *this;
    SQPoint::TransformWithPivot(transformation, vPivot, &auxCircle.Center, 1);
    auxCircle.Radius *= fRadiusScale;
    return auxCircle;
}

EQIntersections QCircle::IntersectionPoint(const QBaseOrb<QVector2> &circle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
{
    // More information: http://mathforum.org/library/drmath/view/51710.html

    QVector2 vFirstI(vIntersection1);
    QVector2 vSecondI(vIntersection2);

    //STEP 1: Obtain V1, a unit vector that points from the first circle's center to second circle's center, and the distance between both centers.
    QVector2 vV1 = circle.Center - this->Center;
    float_q fDistance = vV1.GetLength();

    if (SQFloat::IsNotZero(fDistance))
    {
        vV1 = vV1.Normalize();

        //STEP 2: Obtain V2, a normal vector to V1.
        QVector2 vV2(vV1.y, -vV1.x);

        //STEP 3: Obtain the angle between V1 and V3. V3 is a vector that points from first circle's center to one of the intersection points.
        float_q fAngle = acos_q((this->Radius * this->Radius + fDistance * fDistance - circle.Radius * circle.Radius) / (SQFloat::_2 * this->Radius * fDistance));

        //STEP 4: If the equation above gives a value different of NaN, then circles intersect. Intersection points are calculated.
        if (!SQFloat::IsNaN(fAngle))
        {
            vFirstI = this->Center + vV1 * (this->Radius * cos_q(fAngle)) + vV2 * (this->Radius * sin_q(fAngle));
            vSecondI = this->Center + vV1 * (this->Radius * cos_q(fAngle)) - vV2 * (this->Radius * sin_q(fAngle));

            if (SQFloat::AreEqual(vFirstI.x, vSecondI.x) && SQFloat::AreEqual(vFirstI.y, vSecondI.y))
            {
                float_q fRadiusAddition = this->Radius + circle.Radius;

                if (fRadiusAddition > fDistance)
                {
                    //One circle is contained into another.
                    return EQIntersections::E_Infinite;
                }
                else
                {
                    vIntersection1 = vFirstI;

                    //Circles intersect in one point.
                    return EQIntersections::E_One;
                }

            }
            else
            {
                vIntersection1 = vFirstI;
                vIntersection2 = vSecondI;

                //Circles intersect in two points.
                return EQIntersections::E_Two;
            }
        }
    }

    //STEP 5: Checks if one circle is contained or not into the other (circles may even have the same center point). Otherwise, circles don't intersect.
    if (Intersection(circle))
    {
        //One of the circles is contained into the other.
        return EQIntersections::E_Infinite;
    }

    //Circles don't intersect.
    return EQIntersections::E_None;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const QCircle& QCircle::GetUnitCircle()
{
    static const QCircle UNITCIRCLE(QVector2::GetZeroVector(), SQFloat::_1);
    return UNITCIRCLE;
}


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
