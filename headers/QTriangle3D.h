// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE3D__
#define __QTRIANGLE3D__

#include "EQSpaceRelation.h"
#include "QTriangle.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QPlane.h"
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
/// Class which represents a triangle in 3D. Methods in this class are related to transformations in 3D.
/// </summary>
template <class VectorType>
class QDllExport QTriangle3D : public QTriangle<VectorType>
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QTriangle3D()
    {
    }

	/// <summary>
	/// Constructor from three vector types, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] Vector types which defines vertex A.</param>
	/// <param name="vB">[IN] Vector types which defines vertex B.</param>
	/// <param name="vC">[IN] Vector types which defines vertex C.</param>
	inline QTriangle3D(const VectorType &vA, const VectorType &vB, const VectorType &vC) : QTriangle<VectorType>(vA, vB, vC)
    {
    }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex. Each pointer references to an array which has at least three or four elements.
	/// </summary>
	/// <param name="arValuesA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="arValuesB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="arValuesC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle3D(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) : 
                           QTriangle<VectorType>(arValuesA, arValuesB, arValuesC)
    {
    }

	/// <summary>
	/// Constructor from three 4x32 packed floating point values, one for each vertex.
	/// </summary>
	/// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle3D(const vf32_q& valueA, const vf32_q& valueB, const vf32_q& valueC) : 
                           QTriangle<VectorType>(valueA, valueB, valueC)
    {
    }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="triangle">[IN] 3D triangle that is assigned to current triangle.</param>
	inline QTriangle3D& operator=(const QBaseTriangle<VectorType> &triangle)
	{
        QBaseTriangle<VectorType>::operator=(triangle);
		return *this;
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormal">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector3 &vNormal) const
	{
		this->GetNormalImp(vNormal.As<QVector3>());
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormal">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector4 &vNormal) const
	{
		this->GetNormalImp(vNormal.As<QVector4>());
	}

	/// <summary>
	/// Calculates triangle's circumcenter.
	/// </summary>
	/// <param name="vCircumcenter">[OUT] Vector type that will contain the triangle큦 circumcenter.</param>
	void GetCircumcenter(VectorType &vCircumcenter) const
	{
        /// More information: https://www.box.net/shared/9736bjiyq1

		//STEP 1: Calculate all previous stuff
		VectorType vA(this->B - this->A);
		VectorType vB(this->C - this->B);
		VectorType vC(this->A - this->C);

		//fSp: Triangle큦 semiperimeter
		float_q fSp = (vA.GetLength() + vB.GetLength() + vC.GetLength()) * SQFloat::_0_5;
		//fK: Triangle큦 area
		float_q fK = sqrt_q(fSp * (fSp - vA.GetLength()) * (fSp - vB.GetLength()) * (fSp - vC.GetLength()));

		VectorType vCrossvAvB;
		VectorType vCrossvCvAvB;

		vA.CrossProduct(vB, vCrossvAvB);
		vC.CrossProduct(vCrossvAvB, vCrossvCvAvB);

		//STEP 2: Calculate circumcenter
		vCircumcenter = ((this->A + this->C) * SQFloat::_0_5) + (vA.DotProduct(vB) / (SQFloat::_8 * fK * fK)) * vCrossvCvAvB;
	}

    /// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTranslation)
	{
		SQPoint::Translate(vTranslation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector,
	/// storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector that represents the translation.</param>
	/// <param name="outTriangle">[OUT] Triangle which stores the translated one.</param>
	inline void Translate(const QBaseVector3 &vTranslation, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		SQPoint::Translate(vTranslation, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslationY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslationZ">[IN] Scalar value that contains the translation on Z axis.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
	{
		SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis,
	/// storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fTranslationX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslationY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslationZ">[IN] Scalar value that contains the translation on Z axis.</param>
	/// <param name="outTriangle">[OUT] Triangle which stores the translated one.</param>
	inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, 
                          QBaseTriangle<VectorType>& outTriangle) const
	{
		outTriangle = *this;
		SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, outTriangle.template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// Translates the triangle applying a [4x3] translation matrix.
	/// </summary>
	/// <param name="translation">[IN] The [4x3] translation matrix to be applied.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation)
	{
	    SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// Translates the triangle applying a [4x4] translation matrix.
	/// </summary>
	/// <param name="translation">[IN] The [4x4] translation matrix to be applied.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation)
	{
	    SQPoint::Translate(translation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Translates the triangle applying a [4x3] translation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="translation">[IN] The [4x3] translation matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the translated one.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QBaseTriangle<VectorType> outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Translate(translation, outTriangle.template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// Translates the triangle applying a [4x4] translation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="translation">[IN] The [4x4] translation matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the translated one.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QBaseTriangle<VectorType> outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Translate(translation, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	inline void Rotate(const QQuaternion &qRotation)
	{
	    SQPoint::Rotate(qRotation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around the coordinate axis centre, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the rotated one.</param>
	inline void Rotate(const QQuaternion &qRotation, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
	    SQPoint::Rotate(qRotation, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Rotates the triangle applying the provided rotation matrix.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix to be applied.</param>
	inline void Rotate(const QRotationMatrix3x3 &rotation)
	{
	    SQPoint::Rotate(rotation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Rotates the triangle applying the provided rotation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the rotated triangle.</param>
	inline void Rotate(const QRotationMatrix3x3 &rotation, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Rotate(rotation, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around a point which acts as pivot of rotation.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot)
	{
		SQPoint::RotateWithPivot(qRotation, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around a point which acts as pivot of rotation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the rotated triangle.</param>
	inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
	    SQPoint::RotateWithPivot(qRotation, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector3 &vScale)
	{
	    SQPoint::Scale(vScale, this->template AsPtr<VectorType>(), 3);
	}


	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector, storing
	/// the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const QBaseVector3 &vScale, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		SQPoint::Scale(vScale, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
	{
		SQPoint::Scale(fScaleX, fScaleY, fScaleZ, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis, storing
	/// the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		SQPoint::Scale(fScaleX, fScaleY, fScaleZ, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Scales the triangle applying a scale matrix.
	/// </summary>
	/// <param name="scale">[IN] Scale matrix to be applied.</param>
	inline void Scale(const QScaleMatrix3x3 &scale)
	{
	    SQPoint::Scale(scale, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Scales the triangle applying a scale matrix, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Scale matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const QScaleMatrix3x3 &scale, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Scale(scale, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot)
	{
		 SQPoint::ScaleWithPivot(vScale, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector using the
	/// provided point as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the scaled triangle.</param>
	inline void ScaleWithPivot(const QBaseVector3 &vScale, const VectorType& vPivot, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		SQPoint::ScaleWithPivot(vScale, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot)
	{
		SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by provided amounts for every axis using the
	/// provided point as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the scaled triangle.</param>
	inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot,
                                   QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x3] transformation matrix provided.
	/// </summary>
	/// <param name="transformation">[IN] A [4x3] transformation matrix to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
	{
	    SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x4] transformation matrix provided.
	/// </summary>
	/// <param name="transformation">[IN] A [4x4] transformation matrix to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
	{
	    SQPoint::Transform(transformation, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x3] transformation matrix provided, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] A [4x3] transformation matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the transformed triangle.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Transform(transformation, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x4] transformation matrix provided, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] A [4x4] transformation matrix to be applied.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the transformed triangle.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::Transform(transformation, outTriangle.template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// This method transforms the resident triangle by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot)
	{
	    SQPoint::RotateWithPivot(rotation, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
    /// <remarks>
	/// The resident triangle is NOT modified, remains unchanged.
	/// </remarks>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outTriangle">[OUT] The rotated triangle.</param>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::RotateWithPivot(rotation, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const VectorType &vPivot)
	{
	    SQPoint::ScaleWithPivot(scale, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outTriangle">[OUT] The scaled triangle.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const VectorType &vPivot, QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::ScaleWithPivot(scale, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outTriangle">[OUT] The transformed triangle.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot, 
                                   QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

    /// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, this->template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outTriangle">[OUT] The transformed triangle.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot, 
                                   QBaseTriangle<VectorType> &outTriangle) const
	{
	    outTriangle = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, outTriangle.template AsPtr<VectorType>(), 3);
	}

	/// <summary>
	/// Checks the space relation between current triangle and a plane recieved as parameter. Space Relation means that
	/// the triangle is in the positive side of the space divided by the plane, in the negative side, in both sides (intersection)
	/// or even the triangle is contained in the plane.
	/// </summary>
	/// <param name="plane">[IN] The plane we want check the relation with current triangle.</param>
    /// <returns>
    /// An enumerated value like follows: Contained in the plane, Positive Side, Negative Side or Both Sides (intersects the plane).
    /// </returns>
	EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
	{
		const float_q &fdistA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
		const float_q &fdistB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
		const float_q &fdistC = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;

		if ( SQFloat::IsZero(fdistA) && SQFloat::IsZero(fdistB) && SQFloat::IsZero(fdistC) )
            return EQSpaceRelation::E_Contained;
        else if ( SQFloat::IsPositive(fdistA) && SQFloat::IsPositive(fdistB) && SQFloat::IsPositive(fdistC) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( SQFloat::IsLowerOrEquals(fdistA, SQFloat::_0) && SQFloat::IsLowerOrEquals(fdistB, SQFloat::_0) &&
                  SQFloat::IsLowerOrEquals(fdistC, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
	inline void Extrude(const float_q &fAmount)
	{
		VectorType vNormalVector;

		GetNormal(vNormalVector);

		vNormalVector = vNormalVector * fAmount;

		this->A += vNormalVector;
		this->B += vNormalVector;
		this->C += vNormalVector;
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
	/// <param name="outTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Extrude(const float_q &fAmount, QBaseTriangle<VectorType> &outTriangle) const
	{
		outTriangle = *this;
		outTriangle.template As<QTriangle3D<VectorType> >().Extrude(fAmount);
	}

    /// <summary>
	/// Calculates triangle's orthocenter.
	/// </summary>
	/// <param name="vOrthocenter">[OUT] Vector to store the triangle큦 orthocenter.</param>
	inline void GetOrthocenter(VectorType &vOrthocenter)
	{
	    /// Method from here: http://descartes.cnice.mec.es/materiales_didacticos/OrtoCircun/Ortocentro.htm

	    const VectorType &vAB = this->B - this->A;
	    const VectorType &vBC = this->C - this->B;
	    const VectorType &vCA = this->A - this->C;

	    // Normal to BC in ABC plane
	    const VectorType &vNormBC = ( vBC.CrossProduct(vAB) ).CrossProduct(vBC);

        // vNormBC and AB can't be perpendicular, but we ensure it:
        const float_q &fDot = vNormBC.DotProduct(vAB);
        QE_ASSERT(fDot != SQFloat::_0)

	    vOrthocenter = this->A - ( vCA.DotProduct(vAB)/fDot) * vNormBC;
	}

	/// <summary>
	/// Projects resident triangle over a given plane, storing the resultant triangle in the provided one.
	/// </summary>
    /// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
	/// <param name="plane">[IN] Plane where to project resident triangle.</param>
	/// <param name="outTriangle">[OUT] Triangle where to store the projected one.</param>
	inline void ProjectToPlane(const QPlane &plane, QBaseTriangle<VectorType> &outTriangle)
	{
	    plane.PointProjection(this->A, outTriangle.A);
	    plane.PointProjection(this->B, outTriangle.B);
	    plane.PointProjection(this->C, outTriangle.C);
	}

protected:

	/// <summary>
	/// Template method that calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormal">[OUT] Vector type which will store the normal vector.</param>
	template <class OtherVectorType>
	inline void GetNormalImp(OtherVectorType &vNormal) const
	{
		OtherVectorType vAB = this->B - this->A;
		OtherVectorType vBC = this->C - this->B;

		vAB.CrossProduct(vBC, vNormal);

		vNormal.Normalize();
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE3D__
