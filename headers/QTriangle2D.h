// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE2D__
#define __QTRIANGLE2D__

#include "QTriangle.h"
#include "QVector2.h"
#include "QTransformationMatrix3x3.h"
#include "QPoint.h"

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
		QPoint::Transform(matrix, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// Receives a transformation matrix and an output 2D triangle and applies the transformations
	/// to the resident triangle, storing the results in the output triangle. The origin of transformations is the
	/// coordinate axis origin.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="tOutputTriangle">[OUT] 2D Triangle that stores the result of the transformation.</param>
	inline void Transform(const QTransformationMatrix3x3& matrix, QBaseTriangle2 &tOutputTriangle) const
	{
		tOutputTriangle= *this;
		QPoint::Transform(matrix, reinterpret_cast<QVector2*> (&tOutputTriangle), 3);
	}

	/// <summary>
	/// Receives a transformation matrix and a 2D vector (transformation pivot) and applies the transformations
	/// to the resident triangle. The origin of transformations is the vector type point received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="v2Pivot">[IN] 2D Vector Pivot used for the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix3x3& matrix, const QBaseVector2& v2Pivot)
	{
		QPoint::TransformFromPivot(matrix, v2Pivot, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// Receives a transformation matrix, a 2D vector (transformation pivot) and an output 2D triangle,
	/// and applies the transformations to the resident triangle storing the result in the output triangle. The origin of transformations is the
	/// vector type point received as parameter.
	/// </summary>
	/// <param name="matrix">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="v2Pivot">[IN] 2D Vector Pivot used for the transformation.</param>
	/// <param name="tOutputTriangle">[OUT] 2D Triangle that stores the result of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix3x3& matrix, const QBaseVector2& v2Pivot, QBaseTriangle2 &tOutputTriangle) const
	{
		tOutputTriangle= *this;
		QPoint::TransformFromPivot(matrix, v2Pivot, reinterpret_cast<QVector2*> (&tOutputTriangle), 3);
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

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector2 &vTranslation)
	{
	    QPoint::Translate(vTranslation, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector, storing the
	/// resultant triangle in the provided one.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
	/// <param name="tOut">[OUT] The translated triangle.</param>
	inline void Translate(const QBaseVector2 &vTranslation, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::Translate(vTranslation, reinterpret_cast<QVector2*> (&tOut), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY)
	{
	    QPoint::Translate(fTranslationX, fTranslationY, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis,
	/// storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
	/// <param name="tOut">[OUT] The translated triangle.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::Translate(fTranslationX, fTranslationY, reinterpret_cast<QVector2*> (&tOut), 3);
	}

    /// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	inline void Rotate (const float_q &fRotationAngle)
	{
        QPoint::Rotate(fRotationAngle, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided angle
	/// around the coordinate axis centre, and stores the resulting triangle in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="tOut">[OUT] It receives the resulting triangle.</param>
	inline void Rotate (const float_q &fRotationAngle, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::Rotate(fRotationAngle, reinterpret_cast<QVector2*> (&tOut), 3);
	}

    /// <summary>
	/// This method transforms the resident triangle by rotating it an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateFromPivot (const float_q &fRotationAngle, const QBaseVector2 &vPivot)
	{
	    QPoint::RotateFromPivot(fRotationAngle, vPivot, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method performs a rotation of the resident triangle by rotating it an amount defined by a rotation angle
	/// around a pivot point (as center of rotation), and then storing the resulting triangle in the output parameter.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="tOut">[OUT] It receives the resulting triangle.</param>
	inline void RotateFromPivot (const float_q &fRotationAngle, const QBaseVector2 &vPivot, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::RotateFromPivot(fRotationAngle, vPivot, reinterpret_cast<QVector2*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector2 &vScale)
	{
	    QPoint::Scale(vScale, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY)
	{
	     QPoint::Scale(fScaleX, fScaleY, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector, storing the
	/// resultant triangle in the provided one.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="tOut">[OUT] The scaled triangle.</param>
	inline void Scale(const QBaseVector2 &vScale, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::Scale(vScale, reinterpret_cast<QVector2*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis, storing the
	/// resultant triangle in the provided one.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="tOut">[OUT] The scaled triangle.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::Scale(fScaleX, fScaleY, reinterpret_cast<QVector2*> (&tOut), 3);
	}

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot)
	{
	    QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot)
	{
	     QPoint::ScaleFromPivot(fScaleX, fScaleY, vPivot, reinterpret_cast<QVector2*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector,
	/// acting the other provided vector as pivot of scale, and storing the resultant triangle in the provided one.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="tOut">[OUT] The scaled triangle.</param>
	inline void ScaleFromPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<QVector2*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale, storing the resultant triangle in the provided one.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="tOut">[OUT] The scaled triangle.</param>
	inline void ScaleFromPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot, QBaseTriangle2 &tOut) const
	{
	    tOut = *this;
	    QPoint::ScaleFromPivot(fScaleX, fScaleY, vPivot, reinterpret_cast<QVector2*> (&tOut), 3);
	}

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE2D__
