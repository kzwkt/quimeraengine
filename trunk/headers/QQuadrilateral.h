// [TERMS&CONDITIONS]

#ifndef __QQUADRILATERAL__
#define __QQUADRILATERAL__

#include "QBaseQuadrilateral.h"
#include "QLineSegment2D.h"
#include "QVector2.h"
#include "SQAngle.h"

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
/// Class which represents a quadrilateral in 2D space. Methods in this class are related to transformations in 2D.<br>
/// The quadrilateral is defined by four consecutive vertices A, B, C, D, being the edges AB, BC, CD and DA segments.
/// </summary>
class QDllExport QQuadrilateral : public QBaseQuadrilateral
{

	// CONSTRUCTORS
	// ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QQuadrilateral()
    {
    }

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral from which we want to create a copy in the resident quadrilateral.</param>
	inline QQuadrilateral(const QQuadrilateral &quad) : QBaseQuadrilateral(quad)
    {
    }

	/// <summary>
	/// Base type constructor.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral in which we want resident quadrilateral to be based.</param>
	inline QQuadrilateral(const QBaseQuadrilateral &quad) : QBaseQuadrilateral(quad)
    {
    }

    /// <summary>
    /// Constructor from four 2D vectors.
    /// </summary>
    /// <remarks>
    /// Note that the four vertices must be consecutive, so that the egdes of the quadrilateral must be AB, BC, CD and DA.
    /// </remarks>
    /// <param name="vA">[IN] The 2D vector which defines A vertex.</param>
    /// <param name="vB">[IN] The 2D vector which defines B vertex.</param>
    /// <param name="vC">[IN] The 2D vector which defines C vertex.</param>
    /// <param name="vD">[IN] The 2D vector which defines D vertex.</param>
    inline QQuadrilateral(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC, const QVector2 &vD ) :
                              QBaseQuadrilateral(vA, vB, vC, vD)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a square with center in coordinate origin and 1-length edges which are parallels to axes.
    /// </summary>
    /// <returns>
    /// The "unit square".
    /// </returns>
    inline static const QQuadrilateral& GetUnitSquare()
    {
        static const QQuadrilateral UNITSQUARE(QVector2( SQFloat::_0_5,   SQFloat::_0_5),
                                               QVector2(-SQFloat::_0_5,   SQFloat::_0_5),
                                               QVector2(-SQFloat::_0_5,  -SQFloat::_0_5),
                                               QVector2( SQFloat::_0_5,  -SQFloat::_0_5));
        return UNITSQUARE;
    }


    // METHODS
    // ---------------
public:

    //Unary operators

    /// <summary>
    /// Assign operator. Assigns the provided quadrilateral to the resident quadrilateral.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral to be assigned.</param>
    /// <returns>
    /// A reference to the modified quadrilateral.
    /// </returns>
    inline QQuadrilateral& operator=(const QBaseQuadrilateral &quad)
    {
        QBaseQuadrilateral::operator=(quad);
        return *this;
    }

    //Methods

    /// <summary>
    /// Checks if a given point is inside quadrilateral or not.<br>
    /// This is made in a different way depending on the
    /// kind of quadrilateral we have (crossed, standard convex or concave).
    /// </summary>
    /// <param name="vPoint">[IN] The point we want to check.</param>
    /// <returns>
    /// True if the given point is inside quadrilateral, false otherwise.
    /// The quadrilateral perimeter is considered inside.
    /// </returns>
    bool Contains(const QBaseVector2 &vPoint) const;

    /// <summary>
    /// Checks if the resident quadrilateral intersects with the provided one.<br>
    /// To do that, it checks the intersection with the four segments of the resident quadrilateral with the provided quadrilateral.<br>
    /// Additionally, it checks if
    /// one arbitrary edge of provided quadrilateral intersects with the resident one, to check the case where the provided
    /// quadrilateral is included in the resident one.
    /// </summary>
    /// <param name="quad">[IN] The quadrilateral we want to check the intersection with resident one.</param>
    /// <returns>
    /// True if the given quadrilateral intersects with resident quadrilateral, false otherwise.
    /// </returns>
    bool Intersection(const QBaseQuadrilateral &quad) const;

    /// <summary>
    /// Checks if the resident quadrilateral is crossed.<br>
    /// To do that, it checks if A and D vertices are in the
    /// same side of BC segment AND C and D vertices are in the same side of AB segment, in which case the quadrilateral
    /// is not crossed.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is crossed, false otherwise.
    /// </returns>
    bool IsCrossed() const;

    /// <summary>
    /// Checks if the resident quadrilateral is convex.<br>
    /// To do that, it checks if the quadrilateral diagonals intersects.
    /// </summary>
    /// <remarks>
    /// Crossed quadrilaterals are considered as convex.<br>
    /// Quadrilaterals with a \f$ 180^0\f$ angle are considered convex too.
    /// </remarks>
    /// <returns>
    /// True if the resident quadrilateral is convex, false otherwise.
    /// </returns>
    bool IsConvex() const;

    /// <summary>
    /// Checks if the resident quadrilateral is concave.
    /// </summary>
    /// <returns>
    /// True if the resident quadrilateral is concave, false otherwise.
    /// </returns>
    bool IsConcave() const;

    /// <summary>
    /// Computes the interior angle between AB and AD edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_q GetAngleA() const;

    /// <summary>
    /// Computes the interior angle between BC and BA edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_q GetAngleB() const;

    /// <summary>
    /// Computes the angle between CD and CB edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_q GetAngleC() const;

    /// <summary>
    /// Computes the angle between DA and DC edges of resident quadrilateral.
    /// </summary>
    /// <returns>
    /// A floating point value which is the angle computed.
    /// </returns>
    float_q GetAngleD() const;

	/// <summary>
	/// This method applies to the resident quadrilateral the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
    /// The rotated quadrilateral.
    /// </returns>
	inline QQuadrilateral Rotate(const float_q &fRotationAngle) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Rotate(fRotationAngle, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method performs a translation of the resident quadrilateral given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated quadrilateral.
    /// </returns>
    inline QQuadrilateral Translate(const QBaseVector2 &vTranslation) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Translate(vTranslation, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method performs a translation of the resident quadrilateral given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <returns>
    /// The translated quadrilateral.
    /// </returns>
	inline QQuadrilateral Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method scales the resident quadrilateral by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
	inline QQuadrilateral Scale(const QBaseVector2 &vScale) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Scale(vScale, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method scales the resident quadrilateral by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
	inline QQuadrilateral Scale(const float_q &fScaleX, const float_q &fScaleY) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Scale(fScaleX, fScaleY, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// Receives a transformation matrix and applies the transformations to the resident quadrilateral.<br>
	/// The transformation pivot is the origin of coordinates.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
    /// The transformed quadrilateral.
    /// </returns>
	inline QQuadrilateral Transform(const QTransformationMatrix3x3 &transformation) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::Transform(transformation, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method transforms the 2D quadrilateral by rotating an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated quadrilateral.
    /// </returns>
	inline QQuadrilateral RotateWithPivot(const float_q &fRotationAngle, const QVector2 &vPivot) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::RotateWithPivot(fRotationAngle, vPivot, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method scales the resident quadrilateral by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
	inline QQuadrilateral ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// This method scales the resident quadrilateral by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled quadrilateral.
    /// </returns>
	inline QQuadrilateral ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

	/// <summary>
	/// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
	/// to the resident quadrilateral.<br>
	/// The transformation pivot is the vector received as parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
    /// <returns>
    /// The transformed quadrilateral.
    /// </returns>
	inline QQuadrilateral TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
	{
        QQuadrilateral auxQuadrilateral = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, auxQuadrilateral.AsPtr<QVector2>(), 4);
        return auxQuadrilateral;
	}

    /// <summary>
    /// Converts quadrilateral into a string with the following format:<br>
    /// "QL(a($A),b($B),c($C),d($D))".<br>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string with the specified format.
    /// </returns>
    string_q ToString() const;

protected:

    // Calculates if two points are in the same side of a line segment. Used to know if
    // a quadrilateral is crossed, and to check if a point is inside a triangle.
    // In 2D case, I think is more efficient than the baricentric method.
    // It is bassed on the orientation of the two tringles compossed by
    // each point of the two we want to check and the end points of the line. If both triangles have
    // the same orientation, both points are in the same side of the line.
    bool PointsInSameSideOfLine(const QBaseVector2 &vPoint1, const QBaseVector2 &vPoint2,
                                const QBaseVector2 &vLine1, const QBaseVector2 &vLine2) const;

    // Checks if exists concavity in the "AngleVertex" vertex.
    // AngleEndVertex1 and 2 are the two vertices in the end of the segments which defines the angle (adjacent vertices)
    bool IsConcaveHere(const QVector2 &vAngleVertex, const QVector2 &vAngleEndVertex1,
                       const QVector2 &vAngleEndVertex2, const QVector2 &vOppositeVertex) const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QQUADRILATERAL__
