// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE2D__
#define __QTRIANGLE2D__

#include "QTriangle.h"
#include "QVector2.h"
#include "QTransformationMatrix3x3.h"

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
/// Class which represents a triangle in 2D. Methods in this class are related to transformations in 2D.
/// </summary>
class QDllExport QTriangle2D : public QTriangle<QVector2>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QTriangle2D() { }

	/// <summary>
	/// Constructor from three 2D vectors, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] 2D Vector which defines vertex A.</param>
	/// <param name="vB">[IN] 2D Vector which defines vertex B.</param>
	/// <param name="vC">[IN] 2D Vector which defines vertex C.</param>
	inline QTriangle2D(const QVector2& vA, const QVector2& vB, const QVector2& vC) : QTriangle<QVector2>(vA, vB, vC) { }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex. Each pointer references to an array which has at least two elements.
	/// </summary>
	/// <param name="pValueA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="pValueB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="pValueC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle2D(const float_q* pValueA, const float_q* pValueB, const float_q* pValueC) : QTriangle<QVector2>(pValueA, pValueB, pValueC) { }

	/// <summary>
	/// Constructor from three V4x32-FLOAT, one for each vertex.
	/// </summary>
	/// <param name="vfValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="vfValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="vfValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle2D(const vf32_q& vfValueA, const vf32_q& vfValueB, const vf32_q& vfValueC) : QTriangle<QVector2>(vfValueA, vfValueB, vfValueC) { }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="tValue">[IN] 2D triangle that is assigned to current triangle.</param>
	QTriangle2D& operator=(const QBaseTriangle<QVector2>& tValue)
	{
        QBaseTriangle2::operator=(tValue);
		return *this;
	}

	/// <summary>
	/// Receives a transformation matrix and applies its transformations to the resident
	/// triangle. The origin of transformations is the coordinate axis origin.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	inline void Transform(const QTransformationMatrix3x3& matrix)
	{
		A.Transform(matrix);
		B.Transform(matrix);
		C.Transform(matrix);
	}

	/// <summary>
	/// Receives a transformation matrix and an output 2D triangle and applies the transformations 
	/// to the resident triangle, storing the results in the output triangle. The origin of transformations is the 
	/// coordinate axis origin.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="tOutputTriangle">[OUT] 2D Triangle that stores the result of the transformation.</param>
	inline void Transform(const QTransformationMatrix3x3& matrix, QBaseTriangle<QVector2>& tOutputTriangle) const
	{
		tOutputTriangle.A = A;
		tOutputTriangle.B = B;
		tOutputTriangle.C = C;

		tOutputTriangle.A.Transform(matrix);
		tOutputTriangle.B.Transform(matrix);
		tOutputTriangle.C.Transform(matrix);
	}

	/// <summary>
	/// Receives a transformation matrix and a 2D vector (transformation pivot) and applies the transformations 
	/// to the resident triangle. The origin of transformations is the vector type point received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="v2Pivot">[IN] 2D Vector Pivot used for the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix3x3& matrix, const QBaseVector2& v2Pivot)
	{
		//STEP 1: Translate current triangle's vertices.
		A = A - v2Pivot;
		B = B - v2Pivot;
		C = C - v2Pivot;

		//STEP 2: Tranformation of each vertex.
		A.Transform(matrix);
		B.Transform(matrix);
		C.Transform(matrix);

		//STEP 3: Return the transformated vertices to the original position.
		A = A + v2Pivot;
		B = B + v2Pivot;
		C = C + v2Pivot;
	}

	/// <summary>
	/// Receives a transformation matrix, a 2D vector (transformation pivot) and an output 2D triangle,
	/// and applies the transformations to the resident triangle storing the result in the output triangle. The origin of transformations is the 
	/// vector type point received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="v2Pivot">[IN] 2D Vector Pivot used for the transformation.</param>
	/// <param name="tOutputTriangle">[OUT] 2D Triangle that stores the result of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix3x3& matrix, const QBaseVector2& v2Pivot, QBaseTriangle<QVector2>& tOutputTriangle) const
	{
		//STEP 1: Translate current triangle's vertices.
		tOutputTriangle.A = A - v2Pivot;
		tOutputTriangle.B = B - v2Pivot;
		tOutputTriangle.C = C - v2Pivot;

		//STEP 2: Tranformation of each vertex.
		tOutputTriangle.A.Transform(matrix);
		tOutputTriangle.B.Transform(matrix);
		tOutputTriangle.C.Transform(matrix);

		//STEP 3: Return the transformated vertices to the original position.
		tOutputTriangle.A = tOutputTriangle.A + v2Pivot;
		tOutputTriangle.B = tOutputTriangle.B + v2Pivot;
		tOutputTriangle.C = tOutputTriangle.C + v2Pivot;
	}

	/// <summary>
	/// Calculates the circumcenter of the triangle.
	/// </summary>
	/// <param name="vCircumcenter">[OUT] Vector type param used to store the circumcenter as a return value.</param>
	inline void GetCircumcenter(QVector2& vCircumcenter) const
	{
		//STEP 1: Obtain the gradient of height A.
		//
		// We can obtain the gradient of a line using this formula:
		// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
		float_q gradientBC = (C.y - B.y) / (C.x - B.x);
		float_q gradientHA = - QFloat::_1 / gradientBC;

		//STEP 1.1: Obtain middle point of side BC
		QVector2 middlePointBC((C + B) * QFloat::_0_5);

		//STEP 2: Obtain the gradient of height B.
		float_q gradientAC = (C.y - A.y) / (C.x - A.x);
		float_q gradientHB = - QFloat::_1 / gradientAC;

		//STEP 2.1: Obtain middle point of side AC
		QVector2 middlePointAC((C + A) * QFloat::_0_5);		

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

		vCircumcenter.x = (gradientHA * middlePointBC.x - middlePointBC.y - gradientHB * middlePointAC.x + middlePointAC.y) / (gradientHA - gradientHB);

		// With x calculated we can now obtain y appliying the x to one of the equations explained before.

		vCircumcenter.y = gradientHA * vCircumcenter.x - gradientHA * middlePointBC.x + middlePointBC.y;

	}

	/// <summary>
	/// Calculates the orthocenter of the triangle.
	/// </summary>
	/// <param name="vOrthocenter">[OUT] Vector type param used to store the orthocenter as a return value.</param>
	inline void GetOrthocenter(QVector2& vOrthocenter) const
	{
		//STEP 1: Obtain the gradient of height A.
		//
		// We can obtain the gradient of a line using this formula:
		// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
		float_q gradientBC = (C.y - B.y) / (C.x - B.x);
		float_q gradientHA = - QFloat::_1 / gradientBC;

		//STEP 2: Obtain the gradient of height B.
		float_q gradientAC = (C.y - A.y) / (C.x - A.x);
		float_q gradientHB = - QFloat::_1 / gradientAC;

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

		vOrthocenter.x = (gradientHA * A.x - A.y - gradientHB * B.x + B.y) / (gradientHA - gradientHB);

		// With x calculated we can now obtain y appliying the x to one of the equations explained before.

		vOrthocenter.y = gradientHA * vOrthocenter.x - gradientHA * A.x + A.y;
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE2D__
