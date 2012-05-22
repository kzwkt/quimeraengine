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
/// Class which represents a triangle in 3D.<br>
/// Methods in this class are related to transformations in 3D.
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
	/// Copy constructor.
	/// </summary>
	/// <param name="triangle">[IN] The 3D triangle in which we want resident triangle to be based.</param>
	inline QTriangle3D(const QTriangle3D<VectorType> &triangle) : QTriangle<VectorType>(triangle)
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
	/// Constructor from three pointer-to-float type, one for each vertex.<br>
	/// Each pointer references to an array which has at least three or four elements.
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
	/// Assign operator.<br>
	/// Assigns the provided triangle to the resident triangle.
	/// </summary>
	/// <param name="triangle">[IN] 3D triangle that is assigned to current triangle.</param>
    /// <returns>
    /// A reference to the triangle.
    /// </returns>
	inline QTriangle3D<VectorType>& operator=(const QBaseTriangle<VectorType> &triangle)
	{
        QBaseTriangle<VectorType>::operator=(triangle);
		return *this;
	}

	/// <summary>
	/// Calculates triangle's normal vector.<br>
	/// Follows left-handed rule..
	/// </summary>
    /// <returns>
    /// The normal vector.
    /// </returns>
	inline QVector3 GetNormal() const
	{
		return QVector3(this->GetNormalImp());
	}

	/// <summary>
	/// Calculates triangle's circumcenter.
	/// </summary>
	/// <returns>
    /// The triangle's circumcenter.
    /// </returns>
	VectorType GetCircumcenter() const
	{
        // More information: https://www.box.net/shared/9736bjiyq1

		//STEP 1: Calculate all previous stuff
		const VectorType vA(this->B - this->A);
		const VectorType vB(this->C - this->B);
		const VectorType vC(this->A - this->C);

		//fSp: Triangle´s semiperimeter
		const float_q fSp = (vA.GetLength() + vB.GetLength() + vC.GetLength()) * SQFloat::_0_5;
		//fK: Triangle´s area
		const float_q fK = sqrt_q(fSp * (fSp - vA.GetLength()) * (fSp - vB.GetLength()) * (fSp - vC.GetLength()));

		const VectorType vCrossvAvB = vA.CrossProduct(vB);
		const VectorType vCrossvCvAvB = vC.CrossProduct(vCrossvAvB);

		//STEP 2: Calculate circumcenter
		return ((this->A + this->C) * SQFloat::_0_5) + (vA.DotProduct(vB) / (SQFloat::_8 * fK * fK)) * vCrossvCvAvB;
	}

    /// <summary>
	/// This method performs a translation of the resident triangle given by the provided vector.
	/// </summary>
	/// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    inline QTriangle3D<VectorType> Translate(const QBaseVector3 &vTranslation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Translate(vTranslation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method performs a translation of the resident triangle given by the provided amounts for every axis.
	/// </summary>
	/// <param name="fTranslationX">[IN] Scalar value that contains the translation on X axis.</param>
	/// <param name="fTranslationY">[IN] Scalar value that contains the translation on Y axis.</param>
	/// <param name="fTranslationZ">[IN] Scalar value that contains the translation on Z axis.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// Translates the triangle applying a [4x3] translation matrix.
	/// </summary>
	/// <param name="translation">[IN] The [4x3] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Translate(translation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// Translates the triangle applying a [4x4] translation matrix.
	/// </summary>
	/// <param name="translation">[IN] The [4x4] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
	{
	    QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Translate(translation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Rotate(const QQuaternion &qRotation) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Rotate(qRotation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Rotates the triangle applying the provided rotation matrix.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix to be applied.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Rotate(const QRotationMatrix3x3 &rotation) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Rotate(rotation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method applies to the resident triangle the rotation defined by the provided quaternion
	/// around a point which acts as pivot of rotation.
	/// </summary>
	/// <param name="qRotation">[IN] Quaternion which contais the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::RotateWithPivot(qRotation, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Scale(const QBaseVector3 &vScale) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Scale(vScale, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Scale(fScaleX, fScaleY, fScaleZ, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Scales the triangle applying a scale matrix.
	/// </summary>
	/// <param name="scale">[IN] Scale matrix to be applied.</param>
    /// <returns>
    ///The scaled triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Scale(const QScalingMatrix3x3 &scale) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Scale(scale, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the scale contained in the provided vector using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle3D<VectorType> ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::ScaleWithPivot(vScale, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// This method scales the resident triangle by the provided amounts for every axis using the
	/// provided point as pivot of scale.
	/// </summary>
	/// <param name="fScaleX">[IN] Scalar value that contains the scale on X axis.</param>
	/// <param name="fScaleY">[IN] Scalar value that contains the scale on Y axis.</param>
	/// <param name="fScaleZ">[IN] Scalar value that contains the scale on Z axis.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
	inline QTriangle3D<VectorType> ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x3] transformation matrix provided.
	/// </summary>
	/// <param name="transformation">[IN] A [4x3] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Transform(transformation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Transforms the resident triangle applying the [4x4] transformation matrix provided.
	/// </summary>
	/// <param name="transformation">[IN] A [4x4] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::Transform(transformation, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method transforms the resident triangle by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
	inline QTriangle3D<VectorType> RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::RotateWithPivot(rotation, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method scales the resident triangle by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scalde triangle.
    /// </returns>
	inline QTriangle3D<VectorType> ScaleWithPivot(const QScalingMatrix3x3 &scale, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::ScaleWithPivot(scale, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::TransformWithPivot(transformation, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

    /// <summary>
	/// This method transforms the resident triangle applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
	inline QTriangle3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot) const
	{
        QTriangle3D<VectorType> auxTriangle = *this;
		SQPoint::TransformWithPivot(transformation, vPivot, auxTriangle.template AsPtr<VectorType>(), 3);
        return auxTriangle;
	}

	/// <summary>
	/// Checks the space relation between current triangle and a plane recieved as parameter.<br>
	/// Space Relation means that
	/// the triangle is in the positive side of the space divided by the plane, in the negative side, in both sides (intersection)
	/// or even the triangle is contained in the plane.
	/// </summary>
	/// <param name="plane">[IN] The plane we want check the relation with current triangle.</param>
    /// <returns>
    /// An enumerated value like follows:<br>
    /// - Contained in the plane
    /// - Positive Side
    /// - Negative Side
    /// - Both Sides (intersects the plane).
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
        else if ( SQFloat::IsLessOrEquals(fdistA, SQFloat::_0) && SQFloat::IsLessOrEquals(fdistB, SQFloat::_0) &&
                  SQFloat::IsLessOrEquals(fdistC, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
	}

	/// <summary>
	/// Moves the triangle along its normal vector the units indicated by a scalar value .
	/// </summary>
	/// <param name="fAmount">[IN] Float type that contains the amount of the movement.</param>
    /// <returns>
    /// The extruded triangle.
    /// </returns>
	inline QTriangle3D<VectorType> Extrude(const float_q &fAmount) const
	{
		VectorType vLangthenedNormalVector = this->GetNormal() * fAmount;

        return QTriangle3D<VectorType>(this->A + vLangthenedNormalVector,
                                       this->B + vLangthenedNormalVector,
                                       this->C + vLangthenedNormalVector);
	}

    /// <summary>
	/// Calculates triangle's orthocenter.
	/// </summary>
	/// <returns>
    /// The orthocenter.
    /// </returns>
	inline VectorType GetOrthocenter() const
	{
	    // Method from here: http://descartes.cnice.mec.es/materiales_didacticos/OrtoCircun/Ortocentro.htm

	    const VectorType &AB = this->B - this->A;
	    const VectorType &BC = this->C - this->B;
	    const VectorType &CA = this->A - this->C;

	    // Normal to BC in ABC plane
	    const VectorType &NORMAL_TO_BC = ( BC.CrossProduct(AB) ).CrossProduct(BC);

        // NORMAL_TO_BC and AB can't be perpendicular, but we ensure it:
        const float_q &DOT = NORMAL_TO_BC.DotProduct(AB);

        QE_ASSERT(DOT != SQFloat::_0)

	    return this->A - ( CA.DotProduct(AB) / DOT) * NORMAL_TO_BC;
	}

	/// <summary>
	/// Projects resident triangle over a given plane, storing the resultant triangle in the provided one.
	/// </summary>
    /// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
	/// <param name="plane">[IN] Plane where to project resident triangle.</param>
	/// <returns>
	/// The projected triangle.
	/// </returns>
	inline QTriangle3D<VectorType> ProjectToPlane(const QPlane &plane) const
	{
        return QTriangle3D<VectorType>(plane.PointProjection(this->A),
	                                   plane.PointProjection(this->B),
	                                   plane.PointProjection(this->C));
	}

protected:

	// <summary>
	// Template method that calculates triangle's normal vector.<br>
	// Follows left-handed rule, as Quimera requires.
	// </summary>
	// <param name="vNormal">[OUT] Vector type which will store the normal vector.</param>
    // <returns>
    // The normal.
    // </returns>
	template <class OtherVectorType>
	inline OtherVectorType GetNormalImp() const
	{
		OtherVectorType vAB = this->B - this->A;
		OtherVectorType vBC = this->C - this->B;

		return vAB.CrossProduct(vBC).Normalize();
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE3D__
