// [TERMS&CONDITIONS]

#ifndef __QTRIANGLE3D__
#define __QTRIANGLE3D__

#include "EQSpaceRelation.h"
#include "QTriangle.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QBasePlane.h"
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
	inline QTriangle3D() { }

	/// <summary>
	/// Constructor from three vector types, one for each vertex.
	/// </summary>
	/// <param name="vA">[IN] Vector types which defines vertex A.</param>
	/// <param name="vB">[IN] Vector types which defines vertex B.</param>
	/// <param name="vC">[IN] Vector types which defines vertex C.</param>
	inline QTriangle3D(const VectorType& vA, const VectorType& vB, const VectorType& vC) : QTriangle<VectorType>(vA, vB, vC) { }

	/// <summary>
	/// Constructor from three pointer-to-float type, one for each vertex. Each pointer references to an array which has at least three or four elements.
	/// </summary>
	/// <param name="pValueA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="pValueB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="pValueC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QTriangle3D(const float_q* pValueA, const float_q* pValueB, const float_q* pValueC) : QTriangle<VectorType>(pValueA, pValueB, pValueC) { }

	/// <summary>
	/// Constructor from three V4x32-FLOAT, one for each vertex.
	/// </summary>
	/// <param name="vfValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="vfValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="vfValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QTriangle3D(const vf32_q& vfValueA, const vf32_q& vfValueB, const vf32_q& vfValueC) : QTriangle<VectorType>(vfValueA, vfValueB, vfValueC) { }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator. Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="tValue">[IN] 3D triangle that is assigned to current triangle.</param>
	inline QTriangle3D& operator=(const QBaseTriangle<VectorType>& tValue)
	{
        QBaseTriangle<VectorType>::operator=(tValue);
		return *this;
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormalVector">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector3& vNormalVector) const
	{
		this->GetNormalImp(reinterpret_cast<QVector3&> (vNormalVector));
	}

	/// <summary>
	/// Calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormalVector">[OUT] Vector that will contain the normal vector.</param>
	inline void GetNormal(QBaseVector4& vNormalVector) const
	{
		this->GetNormalImp(reinterpret_cast<QVector4&> (vNormalVector));
	}

	/// <summary>
	/// Calculates triangle's circumcenter.
	/// </summary>
	/// <param name="vCircumcenter">[OUT] Vector type that will contain the triangle큦 circumcenter.</param>
	/// More information: https://www.box.net/shared/9736bjiyq1
	void GetCircumcenter(VectorType& vCircumcenter) const
	{
		//STEP 1: Calculate all previous stuff
		VectorType vA(this->B - this->A);
		VectorType vB(this->C - this->B);
		VectorType vC(this->A - this->C);

		//fSp: Triangle큦 semiperimeter
		float_q fSp = (vA.GetLength() + vB.GetLength() + vC.GetLength()) * QFloat::_0_5;
		//fK: Triangle큦 area
		float_q fK = sqrt(fSp * (fSp - vA.GetLength()) * (fSp - vB.GetLength()) * (fSp - vC.GetLength()));

		VectorType vCrossvAvB;
		VectorType vCrossvCvAvB;

		vA.CrossProduct(vB, vCrossvAvB);
		vC.CrossProduct(vCrossvAvB, vCrossvCvAvB);

		//STEP 2: Calculate circumcenter
		vCircumcenter = ((this->A + this->C) * QFloat::_0_5) + (vA.DotProduct(vB) / (QFloat::_8 * fK * fK)) * vCrossvCvAvB;
	}

    /// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTrans">[IN] Vector which contains the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTrans)
	{
		QPoint::Translate(vTrans, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector,
	/// storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vTrans">[IN] Vector that represents the translation.</param>
	/// <param name="tOut">[OUT] Triangle which stores the translated one.</param>
	inline void Translate(const QBaseVector3 &vTrans, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
		QPoint::Translate(vTrans, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslateX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslateY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslateZ">[IN] Scalar value that contains the translation on Z axis.</param>
	inline void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ)
	{
		QPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis,
	/// storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fTranslateX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslateY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslateZ">[IN] Scalar value that contains the translation on Z axis.</param>
	/// <param name="tOut">[OUT] Triangle which stores the translated one.</param>
	inline void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
		QPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, reinterpret_cast<VectorType*> (&tOut), 3);	}

    /// <summary>
	/// Translates the triangle applying a [4x3] translation matrix.
	/// </summary>
	/// <param name="mTrans">[IN] The [4x3] translation matrix to be applied.</param>
	inline void Translate(const QTranslationMatrix4x3 &mTrans)
	{
	    QPoint::Translate(mTrans, reinterpret_cast<VectorType*> (this), 3);
	}

    /// <summary>
	/// Translates the triangle applying a [4x4] translation matrix.
	/// </summary>
	/// <param name="mTrans">[IN] The [4x4] translation matrix to be applied.</param>
	inline void Translate(const QTranslationMatrix4x4 &mTrans)
	{
	    QPoint::Translate(mTrans, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// Translates the triangle applying a [4x3] translation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="mTrans">[IN] The [4x3] translation matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the translated one.</param>
	inline void Translate(const QTranslationMatrix4x3 &mTrans, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Translate(mTrans, reinterpret_cast<VectorType*> (&tOut), 3);
	}

    /// <summary>
	/// Translates the triangle applying a [4x4] translation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="mTrans">[IN] The [4x4] translation matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the translated one.</param>
	inline void Translate(const QTranslationMatrix4x4 &mTrans, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Translate(mTrans, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	inline void Rotate(const QQuaternion &qRot)
	{
	    QPoint::Rotate(qRot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around the coordinate axis centre, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the rotated one.</param>
	inline void Rotate(const QQuaternion& qRot, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
	    QPoint::Rotate(qRot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// Rotates the triangle applying the provided rotation matrix.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix to be applied.</param>
	inline void Rotate(const QRotationMatrix3x3 &mRot)
	{
	    QPoint::Rotate(mRot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// Rotates the triangle applying the provided rotation matrix, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the rotated triangle.</param>
	inline void Rotate(const QRotationMatrix3x3 &mRot, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Rotate(mRot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around a point which acts as pivot of rotation.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateFromPivot(const QQuaternion& qRot, const VectorType& vPivot)
	{
		QPoint::RotateFromPivot(qRot, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around a point which acts as pivot of rotation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="qRot">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="tOut">[OUT] Triangle where to store the rotated triangle.</param>
	inline void RotateFromPivot(const QQuaternion& qRot, const VectorType& vPivot, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
	    QPoint::RotateFromPivot(qRot, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	inline void Scale(const QBaseVector3 &vScale)
	{
	    QPoint::Scale(vScale, reinterpret_cast<VectorType*> (this), 3);
	}


	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector, storing
	/// the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="tOut">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const QBaseVector3 &vScale, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
		QPoint::Scale(vScale, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	inline void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ)
	{
		QPoint::Scale(fScaleX, fScaleY, fScaleZ, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis, storing
	/// the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="tOut">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, QBaseTriangle<VectorType>& tOut) const
	{
		tOut = *this;
		QPoint::Scale(fScaleX, fScaleY, fScaleZ, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// Scales the triangle applying a scale matrix.
	/// </summary>
	/// <param name="mScale">[IN] Scale matrix to be applied.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale)
	{
	    QPoint::Scale(mScale, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// Scales the triangle applying a scale matrix, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="mScale">[IN] Scale matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the scaled triangle.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Scale(mScale, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const QBaseVector3 &vScale, const VectorType& vPivot)
	{
		 QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector using the
	/// provided point as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="tOut">[OUT] Triangle where to store the scaled triangle.</param>
	inline void ScaleFromPivot(const QBaseVector3 &vScale, const VectorType& vPivot, QBaseTriangle<VectorType> & tOut) const
	{
		tOut = *this;
		QPoint::ScaleFromPivot(vScale, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot)
	{
		QPoint::ScaleFromPivot(fScaleX, fScaleY, fScaleZ, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by provided amounts for every axis using the
	/// provided point as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="tOut">[OUT] Triangle where to store the scaled triangle.</param>
	inline void ScaleFromPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot,
                                QBaseTriangle<VectorType> &tOut) const
	{
		tOut = *this;
		QPoint::ScaleFromPivot(fScaleX, fScaleY, fScaleZ, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x3] transformation matrix provided.
	/// </summary>
	/// <param name="mTransf">[IN] A [4x3] transformation matrix to be applied.</param>
	inline void Transform(const QTransformationMatrix4x3 &mTransf)
	{
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x4] transformation matrix provided.
	/// </summary>
	/// <param name="mTransf">[IN] A [4x4] transformation matrix to be applied.</param>
	inline void Transform(const QTransformationMatrix4x4 &mTransf)
	{
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x3] transformation matrix provided, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] A [4x3] transformation matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the transformed triangle.</param>
	inline void Transform(const QTransformationMatrix4x3 &mTransf, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x4] transformation matrix provided, storing the resultant
	/// triangle in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] A [4x4] transformation matrix to be applied.</param>
	/// <param name="tOut">[OUT] Triangle where to store the transformed triangle.</param>
	inline void Transform(const QTransformationMatrix4x4 &mTransf, QBaseTriangle<VectorType> tOut) const
	{
	    tOut = *this;
	    QPoint::Transform(mTransf, reinterpret_cast<VectorType*> (&tOut), 3);
	}

    /// <summary>
	/// This method transforms the resident triangle by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateFromPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot)
	{
	    QPoint::RotateFromPivot(mRot, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="tOut">[OUT] The rotated triangle.</param>
	/// <remarks>
	/// The resident triangle is NOT modified, remains unchanged.
	/// </remarks>
	inline void RotateFromPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot, QBaseTriangle<VectorType> &tOut) const
	{
	    tOut = *this;
	    QPoint::RotateFromPivot(mRot, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleFromPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot)
	{
	    QPoint::ScaleFromPivot(mScale, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="tOut">[OUT] The scaled triangle.</param>
	inline void ScaleFromPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot, QBaseTriangle<VectorType> &tOut) const
	{
	    tOut = *this;
	    QPoint::ScaleFromPivot(mScale, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x3 &mTransf, const VectorType &vPivot)
	{
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="tOut">[OUT] The transformed triangle.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x3 &mTransf, const VectorType &vPivot, QBaseTriangle<VectorType> &tOut) const
	{
	    tOut = *this;
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
	}

    /// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x4 &mTransf, const VectorType &vPivot)
	{
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (this), 3);
	}

	/// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant triangle in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="tOut">[OUT] The transformed triangle.</param>
	inline void TransformFromPivot(const QTransformationMatrix4x4 &mTransf, const VectorType &vPivot, QBaseTriangle<VectorType> &tOut) const
	{
	    tOut = *this;
	    QPoint::TransformFromPivot(mTransf, vPivot, reinterpret_cast<VectorType*> (&tOut), 3);
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
	inline EQSpaceRelation SpaceRelation(const QBasePlane& plane) const
	{
		const float_q &fdistA = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
		const float_q &fdistB = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
		const float_q &fdistC = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;

		if ( QFloat::IsZero(fdistA) && QFloat::IsZero(fdistB) && QFloat::IsZero(fdistC) )
            return EQSpaceRelation::E_Contained;
        else if ( QFloat::IsPositive(fdistA) && QFloat::IsPositive(fdistB) && QFloat::IsPositive(fdistC) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( QFloat::IsLowerOrEquals(fdistA, QFloat::_0) && QFloat::IsLowerOrEquals(fdistB, QFloat::_0) &&
                  QFloat::IsLowerOrEquals(fdistC, QFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
	inline void Extrude(const float_q& fAmount)
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
	/// <param name="outputTriangle">[OUT] Triangle which stores the transformation.</param>
	inline void Extrude(const float_q& fAmount, QBaseTriangle<VectorType>& outputTriangle) const
	{
		outputTriangle = *this;
		reinterpret_cast<QTriangle3D&> (outputTriangle).Extrude(fAmount);
	}

    /// <summary>
	/// Calculates triangle's orthocenter.
	/// </summary>
	/// <param name="vOrthocenter">[OUT] Vector that will contain the triangle큦 orthocenter.</param>
	/// <remarks>
	/// Method from here: http://descartes.cnice.mec.es/materiales_didacticos/OrtoCircun/Ortocentro.htm
	/// </remarks>
	inline void GetOrthocenter(VectorType &vOrthocenter)
	{
	    const VectorType &vAB = this->B - this->A;
	    const VectorType &vBC = this->C - this->B;
	    const VectorType &vCA = this->A - this->C;

	    // Normal to BC in ABC plane
	    const VectorType &vNormBC = ( vBC.CrossProduct(vAB) ).CrossProduct(vBC);

        // vNormBC and AB can't be perpendicular, but we ensure it:
        const float_q &fDot = vNormBC.DotProduct(vAB);
        QE_ASSERT(fDot != QFloat::_0);

	    vOrthocenter = this->A - ( vCA.DotProduct(vAB)/fDot) * vNormBC;
	}

protected:

	/// <summary>
	/// Template method that calculates triangle's normal vector.
	/// Follows left-handed rule, as Quimera requires.
	/// </summary>
	/// <param name="vNormal">[OUT] Vector type which will store the normal vector.</param>
	template <class OtherVectorType>
	inline void GetNormalImp(OtherVectorType& vNormal) const
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
