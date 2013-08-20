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

#ifndef __QLINESEGMENT2D__
#define __QLINESEGMENT2D__

#include "QLineSegment.h"
#include "QVector2.h"
#include "SQPoint.h"

#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;


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
/// endpoints, A and B.<br/>
/// These points will always be expressed as 2D points or vectors.<br/>
/// Please note there's really no "source" and "end" points implicit, that is, it's not an oriented segment
/// except for the unit line (see below). However, some transforming methods will rotate the segment using A
/// by default as the pivot point.
/// </summary>
class QDllExport QLineSegment2D : public QLineSegment<QVector2>
{
    // BASE CLASS USINGS
    // ------------------
public:

    using QLineSegment<QVector2>::Intersection;
    using QLineSegment<QVector2>::IntersectionPoint;


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
    /// <param name="segment">[IN] 2D line segment containing the two endpoints from which we want to create a copy in the resident segment.</param>
	inline QLineSegment2D(const QLineSegment2D &segment) : QLineSegment<QVector2>(segment.A, segment.B)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="segment">[IN] The 2D line segment containing the two endpoints in which we want resident segment to be based.</param>
	inline QLineSegment2D(const QBaseLineSegment<QVector2> &segment) : QLineSegment<QVector2>(segment.A, segment.B)
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
    /// <remarks>
    /// If the quadrilateral is complex or concave, the result is undefined.
    /// </remarks>
	/// <param name="quad">[IN] The 2D quadrilateral to be compared to.</param>
	/// <returns>
	/// True if the segment intersects the quadrilateral (or if they were either tangent or coincident). Otherwise returns false.
	/// </returns>
	bool Intersection(const QBaseQuadrilateral& quad) const;

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
        SQPoint::Rotate(fRotationAngle, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::Translate(vTranslation, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::Translate(fTranslationX, fTranslationY, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::Scale(vScale, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::Scale(fScaleX, fScaleY, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::Transform(transformation, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::RotateWithPivot(fRotationAngle, vPivot, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::ScaleWithPivot(vScale, vPivot, rcast_q(&auxLineSegment, QVector2*), 2);
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
	    SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, rcast_q(&auxLineSegment, QVector2*), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// Receives a transformation matrix and a vector (transformation pivot) and applies the transformations
	/// to the resident line segment.<br/>
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
	    SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxLineSegment, QVector2*), 2);
        return auxLineSegment;
	}

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
    /// <remarks>
	/// If there are no intersection points, the output parameters used for storing that points won't be modified.<br/>
	/// If there's only one intersection point, only the first parameter will be modified.<br/>
	/// The first point returned is the closest one to A.
	/// </remarks>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vIntersection1">[OUT] The first point where they intersect.</param>
	/// <param name="vIntersection2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

	/// <summary>
	/// This method receives a 2D triangle, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
    /// <remarks>
	/// If there are no intersection point, the output parameter used for storing that point won't be modified.<br/>
	/// The point returned is the closest one to A.
	/// </remarks>
	/// <param name="triangle">[IN] The triangle to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	inline EQIntersections IntersectionPoint(const QBaseTriangle<QVector2> &triangle, QBaseVector2 &vIntersection) const
	{
		QBaseVector2 vAux;
		return this->IntersectionPoint(triangle, vIntersection, vAux);
	}

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection points between it and the segment,
	/// if they exist.
	/// </summary>
    /// <remarks>
	/// The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.<br/>
	/// If there are no intersection points, the output parameters used for storing that points won't be modified.<br/>
	/// If there's only one intersection point, only the first parameter will be modified.<br/>
	/// The first point returned is the closest one to A.
	/// </remarks>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vIntersection1">[OUT] The first point where they intersect.</param>
	/// <param name="vIntersection2">[OUT] The second point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
	EQIntersections IntersectionPoint(const QBaseQuadrilateral &quad, QBaseVector2 &vIntersection1, QBaseVector2 &vIntersection2) const;

	/// <summary>
	/// This method receives a quadrilateral, and computes the intersection point between it and the segment,
	/// if it exists.
	/// </summary>
    /// <remarks>
	/// The provided quadrilateral MUST be convex. Otherwise, the results obtained by the method will be incorrect.<br/>
	/// If there are no intersection point, the output parameter used for storing that point won't be modified.<br/>
	/// The point returned is the closest one to A.
	/// </remarks>
	/// <param name="quad">[IN] The quadrilateral to be compared to.</param>
	/// <param name="vIntersection">[OUT] The point where they intersect.</param>
	/// <returns>
    /// An enumerated value which represents the number of intersections between the line segment and the orb, and can take
    /// the following values: E_None, E_One, E_Two and E_Infinite.
	/// </returns>
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
