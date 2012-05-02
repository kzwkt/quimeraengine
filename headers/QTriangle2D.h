// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE2D__
#define __QTRIANGLE2D__

#include "QTriangle.h"
#include "QVector2.h"
#include "QTransformationMatrix3x3.h"
#include "SQPoint.h"

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
/// Class which represents a triangle in 2D.<br>
/// Methods in this class are related to transformations in 2D.
/// </summary>
class QDllExport QTriangle2D : public QTriangle<QVector2>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QTriangle2D()
    {
    }
    
	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="triangle">[IN] The 2D triangle in which we want resident triangle to be based.</param>
	inline QTriangle2D(const QTriangle2D &triangle) : QTriangle<QVector2>(triangle)
    {
    }

	/// <summary>
	/// Constructor from three 2D vectors, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] 2D Vector which defines vertex A.</param>
	/// <param name="vB">[IN] 2D Vector which defines vertex B.</param>
	/// <param name="vC">[IN] 2D Vector which defines vertex C.</param>
	inline QTriangle2D(const QVector2 &vA, const QVector2 &vB, const QVector2 &vC) : QTriangle<QVector2>(vA, vB, vC)
    {
    }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex.<br>
	/// Each pointer references to an array which has at least two elements.
	/// </summary>
	/// <param name="arValuesA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="arValuesB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="arValuesC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle2D(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) :
                           QTriangle<QVector2>(arValuesA, arValuesB, arValuesC)
    {
    }

	/// <summary>
	/// Constructor from three 4x32 packed floating point values, one for each vertex.
	/// </summary>
	/// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle2D(const vf32_q &valueA, const vf32_q &valueB, const vf32_q &valueC) : QTriangle<QVector2>(valueA, valueB, valueC)
    {
    }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator.<br>
	/// Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="triangle">[IN] Triangle that is assigned to current triangle.</param>
    /// <returns>
    /// A reference to the triangle.
    /// </returns>
	QTriangle2D& operator=(const QBaseTriangle<QVector2> &triangle)
	{
        QBaseTriangle<QVector2>::operator=(triangle);
		return *this;
	}

	/// <summary>
	/// Receives a transformation matrix and applies its transformations to the resident triangle.<br>
	/// The origin of transformations is the coordinate axis origin.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle2D Transform(const QTransformationMatrix3x3 &transformation) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Transform(transformation, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Receives a transformation matrix and a 2D vector (transformation pivot) and applies the transformations
	/// to the resident triangle.<br>
	/// The origin of transformations is the vector type point received as parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix that contains the transformation to apply.</param>
	/// <param name="vPivot">[IN] 2D Vector Pivot used for the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle2D TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::TransformWithPivot(transformation, vPivot, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Calculates the circumcenter of the triangle.
	/// </summary>
    /// <returns>
    /// The circumcenter.
    /// </returns>
	inline QVector2 GetCircumcenter() const
	{
		//STEP 1: Obtain the gradient of height A.
		//
		// We can obtain the gradient of a line using this formula:
		// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
		const float_q gradientBC = (C.y - B.y) / (C.x - B.x);
		const float_q gradientHA = - SQFloat::_1 / gradientBC;

		//STEP 1.1: Obtain middle point of side BC
		const QVector2 middlePointBC = (C + B) * SQFloat::_0_5;

		//STEP 2: Obtain the gradient of height B.
		const float_q gradientAC = (C.y - A.y) / (C.x - A.x);
		const float_q gradientHB = - SQFloat::_1 / gradientAC;

		//STEP 2.1: Obtain middle point of side AC
		const QVector2 middlePointAC = (C + A) * SQFloat::_0_5;

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
		QVector2 vCircumcenter;
        vCircumcenter.x = (gradientHA * middlePointBC.x - middlePointBC.y - gradientHB * middlePointAC.x + middlePointAC.y) / (gradientHA - gradientHB);

		// With x calculated we can now obtain y appliying the x to one of the equations explained before.
		vCircumcenter.y = gradientHA * vCircumcenter.x - gradientHA * middlePointBC.x + middlePointBC.y;

        return vCircumcenter;
	}

	/// <summary>
	/// Calculates the orthocenter of the triangle.
	/// </summary>
    /// <returns>
    /// The orthocenter.
    /// </returns>
	inline QVector2 GetOrthocenter() const
	{
		//STEP 1: Obtain the gradient of height A.
		//
		// We can obtain the gradient of a line using this formula:
		// m = (y - y1) / (x - x1), where (x1, y1) is a point contained into the line
		float_q gradientBC = (C.y - B.y) / (C.x - B.x);
		float_q gradientHA = - SQFloat::_1 / gradientBC;

		//STEP 2: Obtain the gradient of height B.
		float_q gradientAC = (C.y - A.y) / (C.x - A.x);
		float_q gradientHB = - SQFloat::_1 / gradientAC;

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
        QVector2 vOrthocenter;
		vOrthocenter.x = (gradientHA * A.x - A.y - gradientHB * B.x + B.y) / (gradientHA - gradientHB);

		// With x calculated we can now obtain y appliying the x to one of the equations explained before.
		vOrthocenter.y = gradientHA * vOrthocenter.x - gradientHA * A.x + A.y;

        return vOrthocenter;
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    inline QTriangle2D Translate(const QBaseVector2 &vTranslation) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Translate(vTranslation, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] The amount of translation to be applied in X direction.</param>
	/// <param name="fTranslationY">[IN] The amount of translation to be applied in Y direction.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
	inline QTriangle2D Translate(const float_q &fTranslationX, const float_q &fTranslationY) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Translate(fTranslationX, fTranslationY, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided angle
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle2D Rotate(const float_q &fRotationAngle) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Rotate(fRotationAngle, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method transforms the resident triangle by rotating it an amount defined by a rotation angle
	/// around a pivot point (as center of rotation).
	/// </summary>
	/// <param name="fRotationAngle">[IN] The angle of rotation.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle2D RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::RotateWithPivot(fRotationAngle, vPivot, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle2D Scale(const QBaseVector2 &vScale) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Scale(vScale, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle2D Scale(const float_q &fScaleX, const float_q &fScaleY) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::Scale(fScaleX, fScaleY, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] The 2D vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle2D ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::ScaleWithPivot(vScale, vPivot, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] The scale to be applied in X direction.</param>
	/// <param name="fScaleY">[IN] The scale to be applied in Y direction.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle2D ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot) const
	{
        QTriangle2D auxTriangle = *this;
		SQPoint::ScaleWithPivot(fScaleX, fScaleY, vPivot, auxTriangle.AsPtr<QVector2>(), 3);
        return auxTriangle;
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE2D__
