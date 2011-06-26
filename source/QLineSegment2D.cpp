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
	// Matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	// axis, and then displaced an amount across X and Y (for expressing the point finally in
	// world coordinates) indicated by A, as being the pivot point.
	QTransformationMatrix3x3 m(QBaseVector2(A), fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 1) Substracting A from B we're expressing B in LOCAL coordinates.
	//         (** by the same way, if we substract A from A we'll have A in 
	//		       the center of coordinates axis, as being A to become the
	//			   pivot point **)
	QBaseVector2 vBLocal(B.x - A.x, B.y - A.y);

	// STEP 2) Now we transform B; please note due to A is the pivot point, 
	//         transforming B is only needed.
	B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// After STEP 2) we have the segment rotated around A and expressed again in
	// WORLD coordinates.
}

void QLineSegment2D::Transform (const float_q& fRotationAngle, QBaseLineSegment<QVector2>& segmt) const
{
	// Matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	// axis, and then displaced an amount across X and Y (for expressing the point finally in
	// world coordinates) indicated by A, as being the pivot point.
	QTransformationMatrix3x3 m(QBaseVector2(A), fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 1) Substracting A from B we're expressing B in LOCAL coordinates.
	//         (** by the same way, if we substract A from A we'll have A in 
	//		       the center of coordinates axis, as being A to become the
	//			   pivot point **)
	QBaseVector2 vBLocal(B.x - A.x, B.y - A.y);

	// STEP 2) A is the pivot point, so copying A is just needed.
	segmt.A = A;

	// STEP 3) Now we transform and copy B; please note due to A is the pivot point, 
	//         transforming B is only needed.
	segmt.B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	segmt.B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// So after STEP 3) we have in the output parameter the segment rotated around A
	//	and expressed again in WORLD coordinates.
}

void QLineSegment2D::TransformFromCenter (const float_q& fRotationAngle)
{
	// STEP 1.1) First of all we get the segment's centre.
	QVector2 vCenter;
	this->GetCenter(vCenter); 
							  
	// STEP 1.2) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//           axis, and then displaced an amount across X and Y (for expressing the point finally in
	//           world coordinates) indicated by the segment's centre, as being the pivot point.
	QTransformationMatrix3x3 m(vCenter, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Substracting the segment's centre from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the centre from itself we'll
	//			   have the centre in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)
	QBaseVector2 vALocal(A.x - vCenter.x, A.y - vCenter.y);
	QBaseVector2 vBLocal(B.x - vCenter.x, B.y - vCenter.y);

	// STEP 3) Now we transform A and B.
	A.x = vALocal.x * m.ij[0][0] + vALocal.y * m.ij[1][0] +  m.ij[2][0];
	A.y = vALocal.x * m.ij[0][1] + vALocal.y * m.ij[1][1] +  m.ij[2][1];
	B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// After STEP 3) we have the segment rotated around the center and expressed
	// again in WORLD coordinates.
}

void QLineSegment2D::TransformFromCenter (const float_q& fRotationAngle, QBaseLineSegment<QVector2>& segmt) const
{
	// STEP 1.1) First of all we get the segment's centre.
	QVector2 vCenter;
	this->GetCenter(vCenter);

	// STEP 1.2) Creating a matrix for rotating a 2D point (expressed in local coordinates) around the coordinate
	//           axis, and then displaced an amount across X and Y (for expressing the point finally in
	//           world coordinates) indicated by the segment's centre, as being the pivot point.
	QTransformationMatrix3x3 m(vCenter, fRotationAngle, QBaseVector2(QFloat::_1));

	// STEP 2) Substracting the segment's centre from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the centre from itself we'll
	//			   have the centre in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)
	QBaseVector2 vALocal(A.x - vCenter.x, A.y - vCenter.y);
	QBaseVector2 vBLocal(B.x - vCenter.x, B.y - vCenter.y);

	// STEP 3) Now we transform A and B.
	segmt.A.x = vALocal.x * m.ij[0][0] + vALocal.y * m.ij[1][0] +  m.ij[2][0];
	segmt.A.y = vALocal.x * m.ij[0][1] + vALocal.y * m.ij[1][1] +  m.ij[2][1];
	segmt.B.x = vBLocal.x * m.ij[0][0] + vBLocal.y * m.ij[1][0] +  m.ij[2][0];
	segmt.B.y = vBLocal.x * m.ij[0][1] + vBLocal.y * m.ij[1][1] +  m.ij[2][1];

	// After STEP 3) we have the segment rotated around the center and expressed
	// again in WORLD coordinates.
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

void QLineSegment2D::TransformFromPivot (const QTransformationMatrix3x3 & matrix, const QBaseVector2 & v2Pivot)
{
	// STEP 1) Substracting the pivot from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot from itself we'll
	//			   have the pivot in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)
	QVector2 vALocal;
	QVector2 vBLocal;
	QVector2 vPivot(v2Pivot);

	vALocal = A - vPivot;
	vBLocal = B - vPivot;

	// STEP 2) Transform A and B
	vALocal.Transform(matrix, A);
	vBLocal.Transform(matrix, B);
}

void QLineSegment2D::TransformFromPivot (const QTransformationMatrix3x3 & matrix, const QBaseVector2 & v2Pivot, QBaseLineSegment<QVector2> & lsOutputLineSegment) const
{
	// STEP 1) Substracting the pivot from B (A) we're expressing
	//		   B (A) in LOCAL coordinates.
	//         (** by the same way, if we substract the pivot from itself we'll
	//			   have the pivot in the center of coordinates axis, as being
	//			   the centre to become the pivot point **)

	QVector2 vALocal(A);
	QVector2 vBLocal(B);
	QVector2 vPivot(v2Pivot);

	vALocal = vALocal - vPivot;
	vBLocal = vBLocal - vPivot;

	// STEP 2) Transform A and B, storing them in the output line segment. Current line segment IS NOT transformated.
	vALocal.Transform(matrix, lsOutputLineSegment.A);
	vBLocal.Transform(matrix, lsOutputLineSegment.B);
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
