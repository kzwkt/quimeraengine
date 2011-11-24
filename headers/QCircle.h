// [TERMS&CONDITIONS]

#ifndef __QCIRCLE__
#define __QCIRCLE__

#include "QOrb.h"
#include "QVector2.h"
#include "QPoint.h"
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
/// Class which represents a circle in bidimensional space. A circle is the collection of all points that are equidistant from other point known as "Center".
/// </summary>
class QDllExport QCircle : public QOrb<QVector2>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QOrb<QVector2>::Center;
    using QOrb<QVector2>::Radius;


    // CONSTANTS
    // ---------------
public:

	/// <summary>
    /// Unit circle placed in the center of coordinates and whose radius equals to 1.
	/// </summary>
    static const QCircle UnitCircle;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QCircle() { }

    /// <summary>
    /// Constructor from a vector which defines the center point and a floating point value which
    /// defines the radius for the circle.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the cirle.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QCircle (const QVector2& vCenter, const float_q& fRadius) : QOrb<QVector2>(vCenter, fRadius) { }


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
    inline QCircle& operator=(const QBaseOrb<QVector2>& orb)
    {
        QBaseOrb<QVector2>::operator=(orb);
        return *this;
    }

	/// <summary>
	/// Translates the circle.
	/// </summary>
    /// <param name="vTranslate">[IN] 2D vector that contains the translation to be applied.</param>
    inline void Translate (const QBaseVector2& vTranslate)
    {
        QPoint::Translate(vTranslate, &this->Center, 1);
    }

	/// <summary>
	/// Translates the circle. Translated circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="vTranslate">[IN] 2D vector that contains the translation to be applied.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the translated circle.</param>
    inline void Translate (const QBaseVector2& vTranslate, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Translate(vTranslate);
    }

	/// <summary>
	/// Translates the circle.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslateY">[IN] Scalar that contains the translation on Y axis.</param>
    inline void Translate (const float_q& fTranslateX, const float_q& fTranslateY)
    {
        QPoint::Translate(fTranslateX, fTranslateY, &this->Center, 1);
    }

	/// <summary>
	/// Translates the circle. Translated circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslateY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the translated circle.</param>
    inline void Translate (const float_q& fTranslateX, const float_q& fTranslateY, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Translate(fTranslateX, fTranslateY);
    }

	/// <summary>
	/// Rotates the circle.
	/// </summary>
    /// <param name="fAngle">[IN] Scalar that contains the angle of rotation.</param>
    inline void Rotate (const float_q& fAngle)
    {
        QPoint::Rotate(fAngle, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the circle. Rotated circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="fAngle">[IN] Scalar that contains the angle of rotation.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the rotated circle.</param>
    inline void Rotate (const float_q& fAngle, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Rotate(fAngle);
    }

	/// <summary>
	/// Rotates the circle using a pivot.
	/// </summary>
    /// <param name="fAngle">[IN] Scalar that contains the angle of rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void RotateWithPivot (const float_q& fAngle, const QBaseVector2& vPivot)
    {
        QPoint::RotateWithPivot(fAngle, vPivot, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the circle using a pivot. Rotated circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="fAngle">[IN] Scalar that contains the angle of rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the rotated circle.</param>
    inline void RotateWithPivot (const float_q& fAngle, const QBaseVector2& vPivot, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).RotateWithPivot(fAngle, vPivot);
    }

 	/// <summary>
	/// Scales the circle.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    inline void Scale (const QBaseVector2& vScale)
    {
        QPoint::Scale(vScale, &this->Center, 1);
    }

 	/// <summary>
	/// Scales the circle. Scaled circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the scaled circle.</param>
    inline void Scale (const QBaseVector2& vScale, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Scale(vScale);
    }

 	/// <summary>
	/// Scales the circle.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    inline void Scale (const float_q& fScaleX, const float_q& fScaleY)
    {
        QPoint::Scale(fScaleX, fScaleY, &this->Center, 1);
    }

 	/// <summary>
	/// Scales the circle. Scaled circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the scaled circle.</param>
    inline void Scale (const float_q& fScaleX, const float_q& fScaleY, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Scale(fScaleX, fScaleY);
    }

 	/// <summary>
	/// Scales the circle using a pivot.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const QBaseVector2& vScale, const QBaseVector2& vPivot)
    {
        QPoint::ScaleWithPivot(vScale, vPivot, &this->Center, 1);
    }

 	/// <summary>
	/// Scales the circle using a pivot. Scaled circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] 2D vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the scaled circle.</param>
    inline void ScaleWithPivot (const QBaseVector2& vScale, const QBaseVector2& vPivot, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).ScaleWithPivot(vScale, vPivot);
    }

 	/// <summary>
	/// Scales the circle using a pivot.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const float_q& fScaleX, const float_q& fScaleY, const QBaseVector2& vPivot)
    {
        QPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, &this->Center, 1);
    }

 	/// <summary>
	/// Scales the circle using a pivot. Scaled circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the scaled circle.</param>
    inline void ScaleWithPivot (const float_q& fScaleX, const float_q& fScaleY, const QBaseVector2& vPivot, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).ScaleWithPivot(fScaleX, fScaleY, vPivot);
    }

 	/// <summary>
	/// Transforms the circle.
	/// </summary>
    /// <param name="matrix">[IN] Matrix that contains the transformations to apply.</param>
    inline void Transform (const QTransformationMatrix3x3& matrix)
    {
        QPoint::Transform(matrix, &this->Center, 1);
    }

 	/// <summary>
	/// Transforms the circle. Transformed circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="matrix">[IN] Matrix that contains the transformations to apply.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the transformed circle.</param>
    inline void Transform (const QTransformationMatrix3x3& matrix, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).Transform(matrix);
    }

 	/// <summary>
	/// Transforms the circle using a pivot.
	/// </summary>
    /// <param name="matrix">[IN] Matrix that contains the transformations to apply.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the transformation.</param>
    inline void TransformWithPivot (const QTransformationMatrix3x3& matrix, const QBaseVector2& vPivot)
    {
        QPoint::TransformWithPivot(matrix, vPivot, &this->Center, 1);
    }

 	/// <summary>
	/// Transforms the circle using a pivot. Transformed circle will be stored in the circle received as parameter.
	/// </summary>
    /// <param name="matrix">[IN] Matrix that contains the transformations to apply.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the transformation.</param>
    /// <param name="outputCircle">[OUT] Circle that will store the transformed circle.</param>
    inline void TransformWithPivot (const QTransformationMatrix3x3& matrix, const QBaseVector2& vPivot, QBaseOrb<QVector2>& outputCircle) const
    {
        outputCircle = *this;
        reinterpret_cast<QCircle&> (outputCircle).TransformWithPivot(matrix, vPivot);
    }

 	/// <summary>
	/// Calculates possible intersections between resident circle and a circle received as parameter.
	/// When no intersections are detected, output parameters are not modified.
	/// </summary>
    /// <param name="otherCircle">[IN] A circle that is supposed to intersect with resident one.</param>
    /// <param name="vFirstIntersection">[OUT] First intersection point.</param>
    /// <param name="vSecondIntersection">[OUT] Second intersection point.</param>
    /// <returns>
    /// An enumerated value that shows if there have been one intersection, two intersections, one circle is contained into the other or the circles don´t intersect.
    /// </returns>
    /// More information: http://mathforum.org/library/drmath/view/51710.html
    inline EQIntersections IntersectionPoint(const QBaseOrb<QVector2>& otherCircle, QBaseVector2& vFirstIntersection, QBaseVector2& vSecondIntersection) const
    {
        QVector2 vFirstI(vFirstIntersection);
        QVector2 vSecondI(vSecondIntersection);

        //STEP 1: Obtain V1, a unit vector that points from the first circle's center to second circle's center, and the distance between both centers.
        QVector2 vV1 = otherCircle.Center - this->Center;
        float_q fDistance = vV1.GetLength();

        if (QFloat::IsNotZero(fDistance))
        {
            vV1.Normalize();

            //STEP 2: Obtain V2, a normal vector to V1.
            QVector2 vV2(vV1.y, -vV1.x);

            //STEP 3: Obtain the angle between V1 and V3. V3 is a vector that points from first circle's center to one of the intersection points.
            float_q fAngle = acos((this->Radius * this->Radius + fDistance * fDistance - otherCircle.Radius * otherCircle.Radius) / (QFloat::_2 * this->Radius * fDistance));

            //STEP 4: If the equation above gives a value different of NaN, then circles intersect. Intersection points are calculated.
            if (!QFloat::IsNaN(fAngle))
            {
                vFirstI = this->Center + vV1 * (this->Radius * cos(fAngle)) + vV2 * (this->Radius * sin(fAngle));
                vSecondI = this->Center + vV1 * (this->Radius * cos(fAngle)) - vV2 * (this->Radius * sin(fAngle));

                if (QFloat::AreEquals(vFirstI.x, vSecondI.x) && QFloat::AreEquals(vFirstI.y, vSecondI.y))
                {
                    float_q fRadiusAddition = this->Radius + otherCircle.Radius;

                    if (fRadiusAddition > fDistance)
                    {
                        //One circle is contained into another.
                        return EQIntersections::E_Infinite;
                    }
                    else
                    {
                        vFirstIntersection = vFirstI;

                        //Circles intersect in one point.
                        return EQIntersections::E_One;
                    }

                }
                else
                {
                    vFirstIntersection = vFirstI;
                    vSecondIntersection = vSecondI;

                    //Circles intersect in two points.
                    return EQIntersections::E_Two;
                }
            }
        }

        //STEP 5: Checks if one circle is contained or not into the other (circles may even have the same center point). Otherwise, circles don't intersect.
        if (Intersection(otherCircle))
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
