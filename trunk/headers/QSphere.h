// [TERMS&CONDITIONS]

#ifndef __QSPHERE__
#define __QSPHERE__

#include "QOrb.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "SQPoint.h"
#include "EQIntersections.h"
#include "EQSpaceRelation.h"
#include "QPlane.h"

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
/// Class which represents a sphere in space. A sphere is the collection of all points that are equidistant from other point known as "Center".
/// </summary>
template <class VectorType>
class QDllExport QSphere : public QOrb<VectorType>
{

    // BASE CLASS USINGS
    // -------------------
public:

    using QOrb<VectorType>::Center;
    using QOrb<VectorType>::Radius;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QSphere() { }

    /// <summary>
    /// Constructor from a point as center of the sphere and its radius.
    /// </summary>
    /// <param name="vCenter">[IN] Vector that defines the center of the sphere.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QSphere (const VectorType& vCenter, const float_q& fRadius) : QOrb<VectorType>(vCenter, fRadius) { }


    // PROPERTIES
    // ---------------
public:

	/// <summary>
    /// Gets a "unit sphere" placed in the center of coordinates and whose radius equals to 1.
	/// </summary>
	/// <returns>
	/// A "unit sphere".
	/// </returns>
    inline static const QSphere<VectorType>& GetUnitSphere()
    {
        static const QSphere<VectorType> UNITSPHERE(QVector3::GetZeroVector(), SQFloat::_1);
        return UNITSPHERE;
    }


	// METHODS
	// ---------------
public:

	/// <summary>
	/// Assign operator.
	/// </summary>
    /// <param name="orb">[IN] The orb to be copied from.</param>
    /// <returns>
	/// A reference to the modified orb.
	/// </returns>
    inline QSphere& operator=(const QBaseOrb<VectorType>& orb)
    {
        QBaseOrb<VectorType>::operator=(orb);
        return *this;
    }

	/// <summary>
	/// Translates the sphere.
	/// </summary>
    /// <param name="vTranslate">[IN] Vector that contains the translation to be applied.</param>
    inline void Translate (const VectorType& vTranslate)
    {
        SQPoint::Translate(vTranslate, &this->Center, 1);
    }

	/// <summary>
	/// Translates the sphere. Translated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="vTranslate">[IN] Vector that contains the translation to be applied.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the translated sphere.</param>
    inline void Translate (const VectorType& vTranslate, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).Translate(vTranslate);
    }

	/// <summary>
	/// Translates the sphere.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslateY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslateZ">[IN] Scalar that contains the translation on Z axis.</param>
    inline void Translate (const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ)
    {
        SQPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, &this->Center, 1);
    }

	/// <summary>
	/// Translates the sphere. Translated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslateY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslateZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the translated sphere.</param>
    inline void Translate (const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).Translate(fTranslateX, fTranslateY, fTranslateZ);
    }

	/// <summary>
	/// Rotates the sphere.
	/// </summary>
    /// <param name="q">[IN] Quaternion that represents the rotation.</param>
    inline void Rotate (const QQuaternion& q)
    {
        SQPoint::Rotate(q, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the sphere. Rotated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="q">[IN] Quaternion that represents the rotation.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the rotated sphere.</param>
    inline void Rotate (const QQuaternion& q, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).Rotate(q);
    }

	/// <summary>
	/// Rotates the sphere using a pivot.
	/// </summary>
    /// <param name="q">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void RotateWithPivot (const QQuaternion& q, const VectorType& vPivot)
    {
        SQPoint::RotateWithPivot(q, vPivot, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the sphere using a pivot. Rotated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="q">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the rotated sphere.</param>
    inline void RotateWithPivot (const QQuaternion& q, const VectorType& vPivot, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).RotateWithPivot(q, vPivot);
    }

 	/// <summary>
	/// Scales the sphere.
	/// Only the center of the sphere is affected by the scale.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    inline void Scale (const VectorType& vScale)
    {
        SQPoint::Scale(vScale, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //Radius *= reinterpret_cast<const VectorType&> (vScale).GetLength();
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void Scale (const VectorType& vScale, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).Scale(vScale);
    }

 	/// <summary>
	/// Scales the sphere.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    inline void Scale (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ)
    {
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, &this->Center, 1);
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void Scale (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).Scale(fScaleX, fScaleY, fScaleZ);
    }

 	/// <summary>
	/// Scales the sphere using a pivot.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const VectorType& vScale, const VectorType& vPivot)
    {
        SQPoint::ScaleWithPivot(vScale, vPivot, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //Radius *= reinterpret_cast<const VectorType&> (vScale).GetLength();
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void ScaleWithPivot (const VectorType& vScale, const VectorType& vPivot, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).ScaleWithPivot(vScale, vPivot);
    }

 	/// <summary>
	/// Scales the sphere using a pivot.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot)
    {
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //QVector3 vScale(fScaleX, fScaleY, fScaleZ);
        //Radius *= vScale.GetLength();
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outputSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void ScaleWithPivot (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot, QBaseOrb<VectorType>& outputSphere) const
    {
        outputSphere = *this;
        reinterpret_cast<QSphere<VectorType>&> (outputSphere).ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot);
    }

    /// <summary>
	/// This method applies to the resident sphere the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contais the rotation to be applied.</param>
	inline void Rotate (const QRotationMatrix3x3 &mRot)
	{
        SQPoint::Rotate(mRot, reinterpret_cast<VectorType*> (&this->Center), 1);
	}

	/// <summary>
	/// This method applies to the resident sphere the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre, and stores the resulting sphere in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contais the rotation to be applied.</param>
	/// <param name="outSphere">[OUT] The resultant rotated sphere.</param>
	inline void Rotate (const QRotationMatrix3x3 &mRot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Rotate(mRot, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot)
	{
	    SQPoint::RotateWithPivot(mRot, vPivot, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
	/// <param name="mRot">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outSphere">[OUT] The rotated sphere.</param>
	inline void RotateWithPivot (const QRotationMatrix3x3 &mRot, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::RotateWithPivot(mRot, vPivot, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &mTranslation)
	{
	    SQPoint::Translate(mTranslation, &this->Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix,
	/// storing the resultant sphere in the provided one.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outSphere">[OUT] The translated sphere.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x3> &mTranslation, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Translate(mTranslation, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &mTranslation)
	{
	    SQPoint::Translate(mTranslation, &this->Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix,
	/// storing the resultant sphere in the provided one.
	/// </summary>
	/// <param name="mTranslation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outSphere">[OUT] The translated sphere.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x4> &mTranslation, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Translate(mTranslation, &outSphere.Center, 1);
	}

    /// <summary>
	/// This method scales the resident sphere by the scale contained in the provided scale matrix.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale)
	{
	    SQPoint::Scale(mScale, &this->Center, 1);
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided scale matrix, storing the
	/// resultant sphere in the output parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="outSphere">[OUT] The scaled sphere.</param>
	inline void Scale(const QScaleMatrix3x3 &mScale, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Scale(mScale, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot)
	{
	    SQPoint::ScaleWithPivot(mScale, vPivot, &this->Center, 1);
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant sphere in the output parameter.
	/// Only the center of sphere is affected by the scale.
	/// </summary>
	/// <param name="mScale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outSphere">[OUT] The scaled sphere.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &mScale, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::ScaleWithPivot(mScale, vPivot, &outSphere.Center, 1);
	}

    /// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf)
	{
	    SQPoint::Transform(mTransf, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &mTransf, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(mTransf, &outSphere.Center, 1);
	}

    /// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf)
	{
	    SQPoint::Transform(mTransf, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &mTransf, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(mTransf, &outSphere.Center, 1);
	}


    /// <summary>
	/// This method transforms the resident sphere applying the provided space conversion matrix.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	inline void Transform(const QSpaceConversionMatrix &mTransf)
	{
	    SQPoint::Transform(mTransf, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided space conversion matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QSpaceConversionMatrix &mTransf, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(mTransf, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &mTransf, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(mTransf, vPivot, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant sphere in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &mTransf, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::TransformWithPivot(mTransf, vPivot, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &mTransf, const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(mTransf, vPivot, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant sphere in the output parameter.
	/// </summary>
	/// <param name="mTransf">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &mTransf, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::TransformWithPivot(mTransf, vPivot, &outSphere.Center, 1);
	}

	/// <summary>
	/// Checks the space relation between current sphere and a plane received as parameter. Space relation means that
	/// the sphere is in the positive side of the space divided by the plane (subspace pointed by plane´s normal),
	/// in the negative side or in both sides (intersection).
	/// </summary>
	/// <param name="plane">[IN] The plane we want check the relation with current sphere.</param>
	/// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
    /// <returns>
    /// An enumerated value like follows: Positive Side, Negative Side or Both Sides (intersects the plane).
    /// </returns>
	inline EQSpaceRelation SpaceRelation(const QBasePlane& plane) const
	{
        const float_q &fDistP = plane.a * this->Center.x + plane.b * this->Center.y + plane.c * this->Center.z + plane.d;

		if (SQFloat::IsZero(fDistP))
		{
		    return EQSpaceRelation::E_BothSides;
		}
		else
        {
            const float_q &fAbsDistP = SQFloat::Abs(fDistP);

            if (SQFloat::IsLessThan(fAbsDistP, Radius))
                return EQSpaceRelation::E_BothSides;
            else if (SQFloat::IsNegative(fDistP))
                return EQSpaceRelation::E_NegativeSide;
            else
                return EQSpaceRelation::E_PositiveSide;
        }
	}

	/// <summary>
	/// Projects the sphere to a plane perpendicularly. Only the center point of the sphere is projected. Radius keeps its original value.
	/// </summary>
	/// <param name="plane">[IN] Plane where current sphere will be projected.</param>
    /// <param name="outputOrb">[OUT] Projected orb on the plane.</param>
    /// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
	inline void ProjectToPlane(const QPlane& plane, QBaseOrb<VectorType>& outputOrb) const
	{
	    plane.PointProjection(this->Center, outputOrb.Center);
        outputOrb.Radius = this->Radius;
	}
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPHERE__
