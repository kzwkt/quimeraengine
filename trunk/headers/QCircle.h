// [TERMS&CONDITIONS]

#ifndef __QCIRCLE__
#define __QCIRCLE__

#include "QOrb.h"
#include "QVector2.h"
#include "SQPoint.h"
#include "EQIntersections.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a circle in bidimensional space.<br>
/// A circle is the collection of all points that are equidistant from other point known as "Center".
/// </summary>
class QDllExport QCircle : public QOrb<QVector2>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QOrb<QVector2>::Center;
    using QOrb<QVector2>::Radius;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QCircle()
    {
    }
    
	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="orb">[IN] The orb in which we want resident orb to be based.</param>
	inline QCircle(const QOrb<QVector2> &orb) : QOrb<QVector2>(orb)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines the center point and a floating point value which
    /// defines the radius for the circle.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the cirle.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QCircle(const QVector2 &vCenter, const float_q &fRadius) : QOrb<QVector2>(vCenter, fRadius)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a "unit circle" placed in the center of coordinates and whose radius equals 1.
	/// </summary>
	/// <returns>
	/// A unit circle.
	/// </returns>
    inline static const QCircle& GetUnitCircle()
    {
        static const QCircle UNITCIRCLE(QVector2::GetZeroVector(), SQFloat::_1);
        return UNITCIRCLE;
    }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator.
	/// </summary>
    /// <param name="orb">[IN] The orb to be copied from.</param>
    /// <returns>
	/// A reference to the modified orb.
	/// </returns>
    inline QCircle& operator=(const QBaseOrb<QVector2> &orb)
    {
        QBaseOrb<QVector2>::operator=(orb);
        return *this;
    }

	/// <summary>
	/// Translates the circle.
	/// </summary>
    /// <param name="vTranslation">[IN] 2D vector that contains the translation to be applied.</param>
    /// <returns>
	/// The translated circle.
	/// </returns>
    inline QCircle Translate(const QBaseVector2 &vTranslation) const
    {
        QCircle auxCircle = *this;
        SQPoint::Translate(vTranslation, &auxCircle.Center, 1);
        return auxCircle;
    }

	/// <summary>
	/// Translates the circle.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <returns>
	/// The translated circle.
	/// </returns>
    inline QCircle Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
    {
        QCircle auxCircle = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, &auxCircle.Center, 1);
        return auxCircle;
    }
    
	/// <summary>
	/// Rotates the circle.
	/// </summary>
    /// <param name="fRotationAngle">[IN] Scalar that contains the angle of rotation.</param>
    /// <returns>
	/// The rotated circle.
	/// </returns>
    inline QCircle Rotate(const float_q &fRotationAngle) const
    {
        QCircle auxCircle = *this;
        SQPoint::Rotate(fRotationAngle, &auxCircle.Center, 1);
        return auxCircle;
    }

	/// <summary>
	/// Rotates the circle using a pivot.
	/// </summary>
    /// <param name="fRotationAngle">[IN] Scalar that contains the angle of rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
	/// The rotated circle.
	/// </returns>
    inline QCircle RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
    {
        QCircle auxCircle = *this;
        SQPoint::RotateWithPivot(fRotationAngle, vPivot, &auxCircle.Center, 1);
        return auxCircle;
    }

 	/// <summary>
	/// Scales the circle.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <returns>
	/// The scaled circle.
	/// </returns>
    inline QCircle Scale(const QBaseVector2 &vScale, const float_q &fRadiusScale) const
    {
        QCircle auxCircle = *this;
        SQPoint::Scale(vScale, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Scales the circle.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <returns>
	/// The scaled circle.
	/// </returns>
    inline QCircle Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fRadiusScale) const
    {
        QCircle auxCircle = *this;
        SQPoint::Scale(fScaleX, fScaleY, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Scales the circle using a pivot.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
	/// The scaled circle.
	/// </returns>
    inline QCircle ScaleWithPivot(const QBaseVector2 &vScale, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
    {
        QCircle auxCircle = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Scales the circle using a pivot.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
	/// The scaled circle.
	/// </returns>
    inline QCircle ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
    {
        QCircle auxCircle = *this;
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Transforms the circle.
	/// </summary>
    /// <param name="transformation">[IN] Matrix that contains the transformations to apply.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <returns>
	/// The transformed circle.
	/// </returns>
    inline QCircle Transform(const QTransformationMatrix3x3 &transformation, const float_q &fRadiusScale) const
    {
        QCircle auxCircle = *this;
        SQPoint::Transform(transformation, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Transforms the circle using a pivot.
	/// </summary>
    /// <param name="transformation">[IN] Matrix that contains the transformations to apply.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the circle's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the transformation.</param>
    /// <returns>
	/// The transformed circle.
	/// </returns>
    inline QCircle TransformWithPivot(const QTransformationMatrix3x3 &transformation, const float_q &fRadiusScale, const QBaseVector2 &vPivot) const
    {
        QCircle auxCircle = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, &auxCircle.Center, 1);
        auxCircle.Radius *= fRadiusScale;
        return auxCircle;
    }

 	/// <summary>
	/// Calculates possible intersections between resident circle and a circle received as parameter.<br>
	/// When no intersections are detected, output parameters are not modified.
	/// </summary>
    /// <param name="circle">[IN] A circle that is supposed to intersect with resident one.</param>
    /// <param name="vIntersection1">[OUT] An intersection point.</param>
    /// <param name="vIntersection2">[OUT] An intersection point.</param>
    /// <returns>
    /// An enumerated value that shows if there have been one intersection, two intersections, one circle is contained into the other or the circles don't intersect.
    /// </returns>
    inline EQIntersections IntersectionPoint(const QBaseOrb<QVector2> &circle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
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

                if (SQFloat::AreEquals(vFirstI.x, vSecondI.x) && SQFloat::AreEquals(vFirstI.y, vSecondI.y))
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
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QCIRCLE__
