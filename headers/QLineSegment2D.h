// [TERMS&CONDITIONS]

#ifndef __QLINESEGMENT2D__
#define __QLINESEGMENT2D__

#include "QLineSegment.h"
#include "QVector2.h"
#include "SQPoint.h"

#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"

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
/// This class represents a chunk (segment) of straight line into 2D space, defined by two
/// endpoints, A and B.<br>
/// These points will always be expressed as 2D points or vectors.<br>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below). However, some transforming methods will rotate the segment using A
/// by default as the pivot point.
/// </summary>
class QDllExport QLineSegment2D : public QLineSegment<QVector2>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QLineSegment2D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="segment">[IN] 2D line segment containing the two endpoints.</param>
	inline QLineSegment2D(const QLineSegment<QVector2>& segment) : QLineSegment<QVector2>(segment.A, segment.B)
    {
    }

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] 2D vector to define endpoint A.</param>
    /// <param name="vB">[IN] 2D vector to define endpoint B.</param>
	inline QLineSegment2D(const QVector2& vA, const QVector2& vB) : QLineSegment<QVector2>(vA,vB)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Unit segment lying on positive X axis (it's length equals 1).
    /// </summary>
    /// <returns>
	/// A 1-length line segment.
	/// </returns>
	inline static const QLineSegment2D& GetUnitLine()
	{
	    static const QLineSegment2D UNITLINE(QVector2::GetZeroVector(), QVector2::GetUnitVectorX());
	    return UNITLINE;
    }

    /// <summary>
    /// Zero segment lying in the coordinates center whose endpoints
	/// both equals (0, 0) and it's length equals 0.
    /// </summary>
    /// <returns>
	/// A 0-length line segment.
	/// </returns>
	inline static const QLineSegment2D& GetLineZero()
	{
	    static const QLineSegment2D LINEZERO(QVector2::GetZeroVector(), QVector2::GetZeroVector());
	    return LINEZERO;
	}


	// METHODS
	// ---------------
public:
	/// <summary>
	/// Assigning operator.
	/// </summary>
	/// <param name="segment">[IN] The 2D segment to be copied from.</param>
	/// <returns>
	/// A reference to the modified line segment.
	/// </returns>
    inline QLineSegment2D& operator=(const QBaseLineSegment<QVector2> &segment)
    {
        QBaseLineSegment<QVector2>::operator=(segment);
        return *this;
    }

    /// <summary>
    /// This method receives a orb, and computes if it intersects the resident segment or not.
    /// </summary>
    /// <param name="orb">[IN] The orb to be compared to.</param>
    /// <returns>
    /// True if the segment intersects the orb (or if they were either tangent or coincident). Otherwise returns false.
    /// </returns>
    inline bool Intersection(const QBaseOrb<QVector2> &orb) const
    {
         return QLineSegment<QVector2>::Intersection(orb);
    };

    /// <summary>
	/// This method receives a 2D triangle, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="triangle">[IN] The 2D triangle to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the triangle (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection(const QBaseTriangle<QVector2>& triangle) const;

	/// <summary>
	/// This method receives a 2D quadrilateral, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="quad">[IN] The 2D quadrilateral to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the quadrilateral (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection(const QBaseQuadrilateral& quad) const;

	/// <summary>
	/// This method receives another line segment and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="segment">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection(const QBaseLineSegment<QVector2> &segment) const
	{
		return QLineSegment<QVector2>::Intersection(segment);
	}

	/// <summary>
	/// This method applies to the resident line segment the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
	inline QLineSegment2D Rotate(const float_q &fRotationAngle) const
	{
        QLineSegment2D auxLineSegment = *this;
        SQPoint::Rotate(fRotationAngle, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
    /// <returns>
	/// The translated segment.
	/// </returns>
    inline QLineSegment2D Translate(const QBaseVector2 &vTranslation) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::Translate(vTranslation, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <returns>
	/// The translated segment.
	/// </returns>
    inline QLineSegment2D Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::Translate(fTranslationX, fTranslationY, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <returns>
	/// The scaled segment.
	/// </returns>
    inline QLineSegment2D Scale(const QBaseVector2 &vScale) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::Scale(vScale, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <returns>
	/// The scaled segment.
	/// </returns>
    inline QLineSegment2D Scale(const float_q &fScaleX, const float_q &fScaleY) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::Scale(fScaleX, fScaleY, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// Receives a transformation matrix and applies the transformations to the resident
	/// line segment. The transformation pivot is the origin of coordinates.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
	inline QLineSegment2D Transform(const QTransformationMatrix3x3 &transformation) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::Transform(transformation, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method transforms the 2D segment by rotating an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
	/// The rotated segment.
	/// </returns>
	inline QLineSegment2D RotateWithPivot(const float_q &fRotationAngle, const QVector2 &vPivot) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::RotateWithPivot(fRotationAngle, vPivot, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
	inline QLineSegment2D ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::ScaleWithPivot(vScale, vPivot, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
	/// The scaled segment.
	/// </returns>
	inline QLineSegment2D ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const 
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
	/// to the resident line segment.<br>
	/// The transformation pivot is the vector received as parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
    /// <returns>
	/// The transformed segment.
	/// </returns>
	inline QLineSegment2D TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
	{
        QLineSegment2D auxLineSegment = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, auxLineSegment.AsPtr<QVector2>(), 2);
        return auxLineSegment;
	}
    
 	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="segment">[IN] The segment to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameter used for storing that point won't be modified.<br>
	/// If segments are totally or parcially coincident only a single point will be stored in the output
	///  parameter, presumingly an endpoint belonging to one of the segments.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseLineSegment<QVector2>& segment, QBaseVector2& vIntersection) const
	{
		return QLineSegment<QVector2>::IntersectionPoint(segment, vIntersection.As<QVector2>());
	}

	/// <summary>
	/// This method receives a 2D orb, computes the intersections with the resident line segment and stores the intersection point
	/// closest to A end point, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection point with resident line segment we want to check.</param>
    /// <param name="vIntersection">[OUT] A vector where to store the intersection point closest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the output parameter used for storing that point won't be modified.<br>
	/// If there are two intersections, the output parameter stores only the closest to A end point.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseOrb<QVector2> &orb, QBaseVector2 &vIntersection) const
	{
        return QLineSegment<QVector2>::IntersectionPoint(orb, vIntersection.As<QVector2>());
	}

    /// <summary>
	/// This method receives a 2D orb, and computes and stores the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vIntersection1">[OUT] A vector where to store the intersection point closest to A end point.</param>
    /// <param name="vIntersection2">[OUT] A vector where to store the intersection point farthest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// If there's no intersection point, the two output parameters used for storing the points won't be modified.<br>
	/// If there is one intersection, it's stored in the first output parameter.<br>
	/// If there are two intersections, the first output parameter stores the closest to A end point of
    ///  line segment, and the second one stores the closest to B end point.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseOrb<QVector2> &orb, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const
	{
        return QLineSegment<QVector2>::IntersectionPoint(orb, vIntersection1.As<QVector2>(), vIntersection2.As<QVector2>());
	}

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vIntersection1">[OUT] The first point where they intersect.</param>
	/// <param name="vIntersection2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// If there are no intersection points, the output parameters used for storing that points won't be modified.<br>
	/// If there's only one intersection point, only the first parameter will be modified.<br>
	/// The first point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// If there are no intersection point, the output parameter used for storing that point won't be modified.<br>
	/// The point returned is the closest one to A.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection) const
	{
		QBaseVector2 vAux;
		return this->IntersectionPoint(triangle, vIntersection, vAux);
	}

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vIntersection1">[OUT] The first point where they intersect.</param>
	/// <param name="vIntersection2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.<br>
	/// If there are no intersection points, the output parameters used for storing that points won't be modified.<br>
	/// If there's only one intersection point, only the first parameter will be modified.<br>
	/// The first point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.<br>
	/// If there are no intersection point, the output parameter used for storing that point won't be modified.<br>
	/// The point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection) const
	{
		QBaseVector2 vAux;
		return this->IntersectionPoint(quad, vIntersection, vAux);
	}


protected:

	// Checks if a point is inside a triangle.
	// [TODO] jwladi: Replace by the QTriangle2D or QTriangle Contains method, when it exists.
	inline bool PointInsideTriangle(const QBaseTriangle<QVector2>& triangle, const QVector2& vPoint) const
	{
        return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                 PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                 PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
	}

    // Check if two points are in the same side of a line.
	inline bool PointsInSameSideOfLine(const QVector2 &vP1, const QVector2 &vP2, const QVector2 &vLine1, const QVector2 &vLine2) const
	{
        const float_q &ORIENTATION1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
        const float_q &ORIENTATION2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

        if ( SQFloat::IsZero(ORIENTATION1) || SQFloat::IsZero(ORIENTATION2) )
            return true;
        else if ( SQFloat::IsNegative(ORIENTATION1) == SQFloat::IsNegative(ORIENTATION2) )
            return true;
        else
            return false;
	}

	// Checks if a point is inside a quadrilateral.
	// [TODO] jwladi: Replace by the QQuadrilateral Contains method, when it exists.
	inline bool PointInsideQuadrilateral(const QBaseQuadrilateral& quad, const QVector2& vPoint) const
	{
	    return ( PointsInSameSideOfLine(vPoint, quad.C, quad.A, quad.B) &&
                 PointsInSameSideOfLine(vPoint, quad.A, quad.B, quad.C) &&
                 PointsInSameSideOfLine(vPoint, quad.A, quad.C, quad.D) &&
                 PointsInSameSideOfLine(vPoint, quad.C, quad.D, quad.A) );
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QLINESEGMENT2D__
