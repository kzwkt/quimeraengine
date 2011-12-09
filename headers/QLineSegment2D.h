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

// Forward Declarations
//-----------------------

typedef QBaseTriangle<QVector2> QBaseTriangle2;


/// <summary>
/// This class represents a chunk (segment) of straight line into 2D space, defined by two
/// endpoints, A and B.
/// These points will always be expressed as 2D points or vectors.
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
	inline QLineSegment2D() { };

	/// <summary>
    /// Constructor from two vectors.
    /// </summary>
    /// <param name="vA">[IN] 2D vector to define endpoint A.</param>
    /// <param name="vB">[IN] 2D vector to define endpoint B.</param>
	inline QLineSegment2D (const QVector2& vA, const QVector2& vB) : QLineSegment<QVector2>(vA,vB) { }

	/// <summary>
    /// Constructor from a 2D line segment.
    /// </summary>
    /// <param name="segmt">[IN] 2D line segment containing the two endpoints.</param>
	inline explicit QLineSegment2D (const QLineSegment<QVector2>& segmt) : QLineSegment<QVector2>(segmt.A, segmt.B)  { }


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
	/// <param name="segmt">[IN] The 2D segment to be copied from.</param>
	/// <returns>
	/// A reference to the modified line segment.
	/// </returns>
    inline QLineSegment2D& operator=(const QBaseLineSegment2& segmt)
    {
        QBaseLineSegment2::operator=(segmt);
        return *this;
    }

    /// <summary>
    /// This method receives a orb, and computes if it intersects the resident segment or not.
    /// </summary>
    /// <param name="orb">[IN] The orb to be compared to.</param>
    /// <returns>
    /// True if the segment intersects the orb (or if they were either tangent or coincident). Otherwise returns false.
    /// </returns>
    inline bool Intersection (const QBaseOrb<QVector2>& orb) const
    {
         return QLineSegment<QVector2>::Intersection(orb);
    };

	// This method receives a 2D triangle, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="triangl">[IN] The 2D triangle to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the triangle (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection (const QBaseTriangle2& triangl) const;

	/// <summary>
	/// This method receives a 2D quadrilateral, and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="quadrl">[IN] The 2D quadrilateral to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the quadrilateral (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection (const QBaseQuadrilateral& quadrl) const;

	/// <summary>
	/// This method receives another line segment and computes whether they intersect each other or not.
	/// </summary>
	/// <param name="segmt">[IN] The segment to be compared to.</param>
	/// <returns>
	/// True if they intersect each other (or if they were coincident), false if they don't.
	/// </returns>
	inline bool Intersection (const QBaseLineSegment<QVector2>& segmt) const
	{
		return QLineSegment<QVector2>::Intersection(segmt);
	}

	/// <summary>
	/// This method applies to the resident line segment the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	inline void Rotate (const float_q &fRotationAngle)
	{
        SQPoint::Rotate(fRotationAngle, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method applies to the resident line segment the rotation defined by the provided angle
	/// around the coordinate axis centre, and stores the resulting segment in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="lsOut">[OUT] It receives the resulting rotated 2D segment.</param>
	/// <remarks>
	/// The segment is NOT modified, it stays the same.
	/// </remarks>
	inline void Rotate (const float_q &fRotationAngle, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Rotate(fRotationAngle, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector2 &vTranslation)
	{
	    SQPoint::Translate(vTranslation, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY)
	{
	    SQPoint::Translate(fTranslationX, fTranslationY, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided vector, storing the
	/// resultant line segment in the provided one.
	/// </summary>
	/// <param name="vTranslation">[IN] The 2D vector which contains the translation to be applied.</param>
	/// <param name="lsOut">[OUT] The translated line segment.</param>
	inline void Translate(const QBaseVector2 &vTranslation, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Translate(vTranslation, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method performs a translation of the resident line segment given by the provided amounts for every axis, storing the
	/// resultant vector in the provided one.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="lsOut">[OUT] The translated line segment.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Translate(fTranslationX, fTranslationY, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector2 &vScale)
	{
	    SQPoint::Scale(vScale, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY)
	{
	     SQPoint::Scale(fScaleX, fScaleY, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector, storing the
	/// resultant line segment in the provided one.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="lsOut">[OUT] The scaled line segment.</param>
	inline void Scale(const QBaseVector2 &vScale, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Scale(vScale, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis, storing the
	/// resultant vector in the provided one.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="lsOut">[OUT] The scaled line segment.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Scale(fScaleX, fScaleY, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// Receives a transformation matrix and applies the transformations to the resident
	/// line segment. The transformation pivot is the origin of coordinates.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	inline void Transform(const QTransformationMatrix3x3 &matrix)
	{
	    SQPoint::Transform(matrix, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// Receives a transformation matrix and an output line segment and applies the transformations
	/// to a copy of the resident line segment, storing the results in the output parameter. The transformation pivot is the
	/// origin of coordinates.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="lsOut">[OUT] Line segment that stores the result of the transformation.</param>
	inline void Transform(const QTransformationMatrix3x3 &matrix, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::Transform(matrix, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method transforms the 2D segment by rotating an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot (const float_q &fRotationAngle, const QVector2 &vPivot)
	{
	    SQPoint::RotateWithPivot(fRotationAngle, vPivot, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method performs a rotation of the 2D segment by rotating an amount defined by a rotation angle
	/// around a pivot point (as center of rotation), and then storing the resulting segment in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="lsOut">[OUT] It receives the resulting rotated 2D segment.</param>
	/// <remarks>
	/// The segment is NOT modified, it stays the same.
	/// </remarks>
	inline void RotateWithPivot (const float_q &fRotationAngle, const QVector2 &vPivot, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::RotateWithPivot(fRotationAngle, vPivot, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot)
	{
	    SQPoint::ScaleWithPivot(vScale, vPivot, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot)
	{
	     SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale, and storing the resultant line segment in the provided one.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="lsOut">[OUT] The scaled line segment.</param>
	inline void ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::ScaleWithPivot(vScale, vPivot, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

	/// <summary>
	/// This method scales the resident line segment by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale, storing the resultant vector in the provided one.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="lsOut">[OUT] The scaled line segment.</param>
	inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, reinterpret_cast<QVector2*> (&lsOut), 2);
	}


	/// <summary>
	/// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
	/// to the resident line segment. The transformation pivot is the vector received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix3x3 &matrix, const QBaseVector2 &vPivot)
	{
	    SQPoint::TransformWithPivot(matrix, vPivot, reinterpret_cast<QVector2*> (this), 2);
	}

	/// <summary>
	/// Receives a transformation matrix, a vector (transformation pivot) and an output line segment,
	/// and applies the transformations to a copy of the resident line segment, storing the results in the output parameter.
	/// The transformation pivot is the vector received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] Pivot point used for the transformation.</param>
	/// <param name="lsOut">[OUT] Line segment that stores the result of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix3x3 &matrix, const QBaseVector2 &vPivot, QBaseLineSegment2 &lsOut) const
	{
	    lsOut = *this;
	    SQPoint::TransformWithPivot(matrix, vPivot, reinterpret_cast<QVector2*> (&lsOut), 2);
	}

 	/// <summary>
	/// This method receives another line segment, and computes the intersection point between them,
	/// if it exists.
	/// </summary>
	/// <param name="segmt">[IN] The segment to be compared to.</param>
	/// <param name="vIntersectionPt">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If segments are totally or parcially coincident only a single point will be stored in the output
	///  parameter, presumingly an endpoint belonging to one of the segments.
	/// </remarks>
	inline EQIntersections IntersectionPoint (const QBaseLineSegment<QVector2>& segmt, QBaseVector2& vIntersectionPt) const
	{
		return QLineSegment<QVector2>::IntersectionPoint(segmt, *reinterpret_cast<QVector2*>(&vIntersectionPt));
	}

	/// <summary>
	/// This method receives a 2D orb, computes the intersections with the resident line segment and stores the intersection point
	/// closest to A end point, if it exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersection point with resident line segment we want to check.</param>
    /// <param name="vPoint">[OUT] A vector where to store the intersection point closest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the output parameter used for storing that point won't be modified.
	/// -If there are two intersections, the output parameter stores only the closest to A end point.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseOrb<QVector2> &orb, QBaseVector2 &vPoint) const
	{
        return QLineSegment<QVector2>::IntersectionPoint(orb, reinterpret_cast<QVector2&>(vPoint));
	}

    /// <summary>
	/// This method receives a 2D orb, and computes and stores the points where the resident line segment intersects with it,
    /// if they exists.
	/// </summary>
	/// <param name="orb">[IN] The orb whose intersections with resident line segment we want to check.</param>
    /// <param name="vPoint1">[OUT] A vector where to store the intersection point closest to A end point.</param>
    /// <param name="vPoint2">[OUT] A vector where to store the intersection point farthest to A end point.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One and E_Two.
	/// </returns>
	/// <remarks>
	/// -If there's no intersection point, the two output parameters used for storing the points won't be modified.
	/// -If there is one intersection, it's stored in the first output parameter.
	/// -If there are two intersections, the first output parameter stores the closest to A end point of
    ///  line segment, and the second one stores the closest to B end point.
	/// </remarks>
	EQIntersections IntersectionPoint (const QBaseOrb<QVector2> &orb, QBaseVector2 &vPoint1, QBaseVector2 &vPoint2) const
	{
        return QLineSegment<QVector2>::IntersectionPoint(orb, reinterpret_cast<QVector2&>(vPoint1), reinterpret_cast<QVector2&>(vPoint2));
	}

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vPoint1">[OUT] The first point where they intersect.</param>
	/// <param name="vPoint2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there are no intersection points, the output parameters used for storing that points won't be modified.
	/// -If there's only one intersection point, only the first parameter will be modified.
	/// -The first point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseTriangle2& triangle, QBaseVector2& vPoint1, QBaseVector2& vPoint2) const;

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vPoint">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -If there are no intersection point, the output parameter used for storing that point won't be modified.
	/// -The point returned is the closest one to A.
	/// </remarks>
	inline EQIntersections IntersectionPoint(const QBaseTriangle2& triangle, QBaseVector2& vPoint) const
	{
		QBaseVector2 aux;
		return this->IntersectionPoint(triangle, vPoint, aux);
	}

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vPoint1">[OUT] The first point where they intersect.</param>
	/// <param name="vPoint2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.
	/// -If there are no intersection points, the output parameters used for storing that points won't be modified.
	/// -If there's only one intersection point, only the first parameter will be modified.
	/// -The first point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseQuadrilateral& quad, QBaseVector2& vPoint1, QBaseVector2& vPoint2) const;

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vPoint">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	/// <remarks>
	/// -The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.
	/// -If there are no intersection point, the output parameter used for storing that point won't be modified.
	/// -The point returned is the closest one to A.
	/// </remarks>
	EQIntersections IntersectionPoint(const QBaseQuadrilateral& quad, QBaseVector2& vPoint) const
	{
		QBaseVector2 aux;
		return this->IntersectionPoint(quad, vPoint, aux);
	}


protected:

	// Checks if a point is inside a triangle.
	// [TODO] jwladi: Replace by the QTriangle2D or QTriangle Contains method, when it exists.
	inline bool PointInsideTriangle(const QBaseTriangle2& triangle, const QVector2& vPoint) const
	{
        return ( PointsInSameSideOfLine(vPoint, triangle.A, triangle.B, triangle.C) &&
                 PointsInSameSideOfLine(vPoint, triangle.B, triangle.C, triangle.A) &&
                 PointsInSameSideOfLine(vPoint, triangle.C, triangle.A, triangle.B) );
	}

    // Check if two points are in the same side of a line.
	inline bool PointsInSameSideOfLine(const QVector2 &vP1, const QVector2 &vP2, const QVector2 &vLine1, const QVector2 &vLine2) const
	{
        const float_q &fOrientation1 = (vLine1.x - vP1.x)*(vLine2.y - vP1.y) - (vLine1.y - vP1.y)*(vLine2.x - vP1.x);
        const float_q &fOrientation2 = (vLine1.x - vP2.x)*(vLine2.y - vP2.y) - (vLine1.y - vP2.y)*(vLine2.x - vP2.x);

        if ( SQFloat::IsZero(fOrientation1) || SQFloat::IsZero(fOrientation2) )
            return true;
        else if ( SQFloat::IsNegative(fOrientation1) == SQFloat::IsNegative(fOrientation2) )
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
