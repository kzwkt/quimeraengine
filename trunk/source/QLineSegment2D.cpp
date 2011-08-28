// [TERMS&CONDITIONS]

#include "QBaseTriangle.h"
#include "QBaseQuadrilateral.h"
#include "QTransformationMatrix3x3.h"

#include "QLineSegment2D.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
const QLineSegment2D QLineSegment2D::UnitLine(QVector2::ZeroVector, QVector2::UnitVectorX);
const QLineSegment2D QLineSegment2D::LineZero(QVector2::ZeroVector, QVector2::ZeroVector);


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool QLineSegment2D::Intersection (const QBaseTriangle2& triangl) const
{
	// Just checking if the segment instersects with any edge of the triangle.

	QLineSegment<QVector2> lsAB(triangl.A, triangl.B);
	QLineSegment<QVector2> lsBC(triangl.B, triangl.C);
	QLineSegment<QVector2> lsCA(triangl.C, triangl.A);

	return     ( QLineSegment<QVector2>::Intersection(lsAB) )
			|| ( QLineSegment<QVector2>::Intersection(lsBC) )
			|| ( QLineSegment<QVector2>::Intersection(lsCA) );

}

bool QLineSegment2D::Intersection (const QBaseQuadrilateral& quadrl) const
{
	// Just checking if the segment instersects with any edge of the quadrilateral.

	QLineSegment<QVector2> lsAB(quadrl.A, quadrl.B);
	QLineSegment<QVector2> lsBC(quadrl.B, quadrl.C);
	QLineSegment<QVector2> lsCD(quadrl.C, quadrl.D);
	QLineSegment<QVector2> lsDA(quadrl.D, quadrl.A);

	return     ( QLineSegment<QVector2>::Intersection(lsAB) )
			|| ( QLineSegment<QVector2>::Intersection(lsBC) )
			|| ( QLineSegment<QVector2>::Intersection(lsCD) )
			|| ( QLineSegment<QVector2>::Intersection(lsDA) );
}

void QLineSegment2D::Transform (const float_q& fRotationAngle)
{
	// We assume the segment endpoints are expressed in WORLD coordinates.

	// STEP 1) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//         axis, and then displaced an amount across X and Y (for expressing the point finally in
	//         world coordinates) indicated by the pivot point.
	QTransformationMatrix3x3 m(QVector2::ZeroVector, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Express the segment endpoints in LOCAL coordinates (from the pivot point)
	//         and transform the segment; please note this time the pivot point is the coordinate
	//		   centre itself.
	this->TransformFromPivot(m, QVector2::ZeroVector);

	// After the former step, we have the segment rotated around the coordinate axis centre
	// and expressed again in WORLD coordinates.
}

void QLineSegment2D::Transform (const float_q& fRotationAngle, QBaseLineSegment<QVector2>& segmt) const
{
	// We assume the segment endpoints are expressed in WORLD coordinates.

	// STEP 1) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//         axis, and then displaced an amount across X and Y (for expressing the point finally in
	//         world coordinates) indicated by the pivot point.
	QTransformationMatrix3x3 m(QVector2::ZeroVector, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Express the segment endpoints in LOCAL coordinates (from the pivot point) 
	//         and transform the segment; please note this time the pivot point is the coordinate
	//		   centre itself.
	this->TransformFromPivot(m, QVector2::ZeroVector, segmt);

	// After the former step, we have the segment rotated around the coordinate axis 
	// and expressed in WORLD coordinates.
}

void QLineSegment2D::Transform (const QTransformationMatrix3x3 & matrix)
{
	// STEP 1) Transform A and B.
	A.Transform(matrix);
	B.Transform(matrix);	
}

void QLineSegment2D::Transform (const QTransformationMatrix3x3 & matrix, QBaseLineSegment<QVector2> & lsOutputLineSegment) const
{
	// STEP 1) Transform A and B, storing them in the output line segment. Current line segment IS NOT transformated.
	QVector2 vALocal(A);
	QVector2 vBLocal(B);

	vALocal.Transform(matrix, lsOutputLineSegment.A);
	vBLocal.Transform(matrix, lsOutputLineSegment.B);
}

void QLineSegment2D::TransformFromPivot (const float_q& fRotationAngle, const QVector2& vPivot)
{
 							  
	// STEP 1) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//         axis, and then displaced an amount across X and Y (for expressing the point finally in
	//         world coordinates) indicated by the pivot point.
	QTransformationMatrix3x3 m(vPivot, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Substracting the pivot point from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot point from itself we'll
	//			   have the pivot in the center of coordinates axis, fot it's the
	//			   centre of rotation **)
	QVector2 vALocal(A - vPivot);
	QVector2 vBLocal(B - vPivot);

	// STEP 3) Now we transform A and B.
	A.x = vALocal.x * m.ij[0][0] + vALocal.y * m.ij[1][0] +  m.ij[2][0];
	A.y = vALocal.x * m.ij[0][1] + vALocal.y * m.ij[1][1] +  m.ij[2][1];
	B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// After STEP 3) we have the segment rotated around the pivot and expressed
	// again in WORLD coordinates.
}

void QLineSegment2D::TransformFromPivot (const float_q& fRotationAngle, const QVector2& vPivot,  QBaseLineSegment2& segmt) const
{

	// STEP 1) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//         axis, and then displaced an amount across X and Y (for expressing the point finally in
	//         world coordinates) indicated by the pivot point.
	QTransformationMatrix3x3 m(vPivot, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Substracting the pivot point from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot point from itself we'll
	//			   have the pivot in the center of coordinates axis, fot it's the
	//			   centre of rotation **)
	QVector2 vALocal(A - vPivot);
	QVector2 vBLocal(B - vPivot);

	// STEP 3) Now we transform A and B.
	segmt.A.x = vALocal.x * m.ij[0][0] + vALocal.y * m.ij[1][0] +  m.ij[2][0];
	segmt.A.y = vALocal.x * m.ij[0][1] + vALocal.y * m.ij[1][1] +  m.ij[2][1];
	segmt.B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	segmt.B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// After STEP 3) we have the segment rotated around the pivot and expressed
	// again in WORLD coordinates.
}

void QLineSegment2D::TransformFromPivot (const QTransformationMatrix3x3 & matrix, const QBaseVector2 & v2Pivot)
{
	// STEP 1) Substracting the pivot from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot from itself we'll
	//			   have the pivot in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)
	A = A - v2Pivot;
	B = B - v2Pivot;

	// STEP 2) Transform A and B
	A.Transform(matrix);
	B.Transform(matrix);

	A = A + v2Pivot;
	B = B + v2Pivot;
}

void QLineSegment2D::TransformFromPivot (const QTransformationMatrix3x3 & matrix, const QBaseVector2 & v2Pivot, QBaseLineSegment<QVector2> & lsOutputLineSegment) const
{
	// STEP 1) Substracting the pivot from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot from itself we'll
	//			   have the pivot in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)
	lsOutputLineSegment.A = A - v2Pivot;
	lsOutputLineSegment.B = B - v2Pivot;

	// STEP 2) Transform A and B, storing them in the output line segment. Current line segment IS NOT transformated.
	lsOutputLineSegment.A.Transform(matrix);
	lsOutputLineSegment.B.Transform(matrix);

	lsOutputLineSegment.A = lsOutputLineSegment.A + v2Pivot;
	lsOutputLineSegment.B = lsOutputLineSegment.B + v2Pivot;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
