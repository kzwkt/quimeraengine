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
	inline QSphere()
    {
    }

    /// <summary>
    /// Constructor from a point as center of the sphere and its radius.
    /// </summary>
    /// <param name="vCenter">[IN] Vector that defines the center of the sphere.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    inline QSphere(const VectorType &vCenter, const float_q &fRadius) : QOrb<VectorType>(vCenter, fRadius)
    {
    }


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
    /// <param name="sphere">[IN] The orb to be copied from.</param>
    /// <returns>
	/// A reference to the modified orb.
	/// </returns>
    inline QSphere& operator=(const QBaseOrb<VectorType> &sphere)
    {
        QBaseOrb<VectorType>::operator=(sphere);
        return *this;
    }

	/// <summary>
	/// Translates the sphere.
	/// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    inline void Translate(const VectorType &vTranslation)
    {
        SQPoint::Translate(vTranslation, &this->Center, 1);
    }

	/// <summary>
	/// Translates the sphere. Translated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the translated sphere.</param>
    inline void Translate(const VectorType &vTranslation, QBaseOrb<VectorType>& outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().Translate(vTranslation);
    }

	/// <summary>
	/// Translates the sphere.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
    {
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, &this->Center, 1);
    }

	/// <summary>
	/// Translates the sphere. Translated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the translated sphere.</param>
    inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().Translate(fTranslationX, fTranslationY, fTranslationZ);
    }

	/// <summary>
	/// Rotates the sphere.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    inline void Rotate(const QQuaternion &qRotation)
    {
        SQPoint::Rotate(qRotation, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the sphere. Rotated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the rotated sphere.</param>
    inline void Rotate(const QQuaternion &qRotation, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().Rotate(qRotation);
    }

	/// <summary>
	/// Rotates the sphere using a pivot.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot)
    {
        SQPoint::RotateWithPivot(qRotation, vPivot, &this->Center, 1);
    }

	/// <summary>
	/// Rotates the sphere using a pivot. Rotated sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the rotated sphere.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().RotateWithPivot(qRotation, vPivot);
    }

 	/// <summary>
	/// Scales the sphere.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    inline void Scale(const VectorType &vScale, const float_q &fRadiusScale)
    {
        SQPoint::Scale(vScale, &this->Center, 1);
        this->Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void Scale(const VectorType &vScale, const float_q &fRadiusScale, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().Scale(vScale, fRadiusScale);
        outSphere.Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const float_q &fRadiusScale)
    {
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, &this->Center, 1);
        this->Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const float_q &fRadiusScale,
                      QBaseOrb<VectorType>& outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().Scale(fScaleX, fScaleY, fScaleZ, fRadiusScale);
        outSphere.Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere using a pivot.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot(const VectorType &vScale, const float_q &fRadiusScale, const VectorType &vPivot)
    {
        SQPoint::ScaleWithPivot(vScale, vPivot, &this->Center, 1);
        this->Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void ScaleWithPivot(const VectorType &vScale, const float_q &fRadiusScale, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As<QSphere<VectorType> >().ScaleWithPivot(vScale, fRadiusScale, vPivot);
        outSphere.Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere using a pivot.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const float_q &fRadiusScale,
                               const VectorType &vPivot)
    {
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &this->Center, 1);
        this->Radius *= fRadiusScale;
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <param name="outSphere">[OUT] Sphere that will store the scaled sphere.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const float_q &fRadiusScale,
                               const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
    {
        outSphere = *this;
        outSphere.template As< QSphere<VectorType> >().ScaleWithPivot(fScaleX, fScaleY, fScaleZ, fRadiusScale, vPivot);
        outSphere.Radius *= fRadiusScale;
    }

    /// <summary>
	/// This method applies to the resident sphere the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
	inline void Rotate(const QRotationMatrix3x3 &rotation)
	{
        SQPoint::Rotate(rotation, &this->Center, 1);
	}

	/// <summary>
	/// This method applies to the resident sphere the rotation defined by the provided rotation matrix
	/// around the coordinate axis centre, and stores the resulting sphere in the output parameter.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
	/// <param name="outSphere">[OUT] The resultant rotated sphere.</param>
	inline void Rotate(const QRotationMatrix3x3 &rotation, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Rotate(rotation, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation).
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot)
	{
	    SQPoint::RotateWithPivot(rotation, vPivot, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere by applying the rotation contained in the
	/// provided rotation matrix around a pivot point (which acts as center of rotation),
	/// and then storing it in the output parameter.
	/// </summary>
	/// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
	/// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
	/// <param name="outSphere">[OUT] The rotated sphere.</param>
	inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::RotateWithPivot(rotation, vPivot, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation)
	{
	    SQPoint::Translate(translation, &this->Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix,
	/// storing the resultant sphere in the provided one.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outSphere">[OUT] The translated sphere.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Translate(translation, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation)
	{
	    SQPoint::Translate(translation, &this->Center, 1);
	}

	/// <summary>
	/// This method performs a translation of the resident sphere given by the provided translation matrix,
	/// storing the resultant sphere in the provided one.
	/// </summary>
	/// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
	/// <param name="outSphere">[OUT] The translated sphere.</param>
	inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Translate(translation, &outSphere.Center, 1);
	}

    /// <summary>
	/// This method scales the resident sphere by the scale contained in the provided scale matrix.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	inline void Scale(const QScaleMatrix3x3 &scale, const float_q &fRadiusScale)
	{
	    SQPoint::Scale(scale, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided scale matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="outSphere">[OUT] The scaled sphere.</param>
	inline void Scale(const QScaleMatrix3x3 &scale, const float_q &fRadiusScale, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Scale(scale, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const float_q &fRadiusScale, const VectorType &vPivot)
	{
	    SQPoint::ScaleWithPivot(scale, vPivot, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method scales the resident sphere by the scale contained in the provided matrix,
	/// acting the provided vector as pivot of scale, storing the resultant sphere in the output parameter.
	/// </summary>
	/// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
	/// <param name="outSphere">[OUT] The scaled sphere.</param>
	inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const float_q &fRadiusScale, const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::ScaleWithPivot(scale, vPivot, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}

    /// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q &fRadiusScale)
	{
	    SQPoint::Transform(transformation, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q &fRadiusScale,
                          QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(transformation, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}

    /// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q &fRadiusScale)
	{
	    SQPoint::Transform(transformation, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix, storing the
	/// resultant sphere in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q &fRadiusScale,
                          QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(transformation, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}


    /// <summary>
	/// This method transforms the resident sphere applying the provided space conversion matrix.
    /// Only the center of sphere is affected by this transformation.
	/// </summary>
	/// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	inline void Transform(const QSpaceConversionMatrix &spaceConversion)
	{
	    SQPoint::Transform(spaceConversion, &this->Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided space conversion matrix, storing the
	/// resultant sphere in the output parameter.
	/// Only the center of sphere is affected by this transformation.
	/// </summary>
	/// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void Transform(const QSpaceConversionMatrix &spaceConversion, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::Transform(spaceConversion, &outSphere.Center, 1);
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q &fRadiusScale,
                                   const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant sphere in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q &fRadiusScale,
                                   const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q &fRadiusScale,
                                   const VectorType &vPivot)
	{
	    SQPoint::TransformWithPivot(transformation, vPivot, &this->Center, 1);
	    this->Radius *= fRadiusScale;
	}

	/// <summary>
	/// This method transforms the resident sphere applying the provided transformation matrix,
	/// acting the provided vector as pivot of transformation, storing the resultant sphere in the output parameter.
	/// </summary>
	/// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
	/// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
	/// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
	/// <param name="outSphere">[OUT] The transformed sphere.</param>
	inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q &fRadiusScale,
                                   const VectorType &vPivot, QBaseOrb<VectorType> &outSphere) const
	{
	    outSphere = *this;
	    SQPoint::TransformWithPivot(transformation, vPivot, &outSphere.Center, 1);
	    outSphere.Radius *= fRadiusScale;
	}

	/// <summary>
	/// Checks the space relation between current sphere and a plane received as parameter. Space relation means that
	/// the sphere is in the positive side of the space divided by the plane (subspace pointed by plane´s normal),
	/// in the negative side or in both sides (intersection).
	/// </summary>
    /// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
	/// <param name="plane">[IN] The plane we want check the relation with current sphere.</param>
    /// <returns>
    /// An enumerated value like follows: Positive Side, Negative Side or Both Sides (intersects the plane).
    /// </returns>
	inline EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
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
    /// <remarks>
	/// The plane must be normalized to obtain correct result.
	/// </remarks>
	/// <param name="plane">[IN] Plane where current sphere will be projected.</param>
    /// <param name="outSphere">[OUT] Projected orb on the plane.</param>
	inline void ProjectToPlane(const QPlane &plane, QBaseOrb<VectorType> &outSphere) const
	{
	    plane.PointProjection(this->Center, outSphere.Center);
        outSphere.Radius = this->Radius;
	}
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPHERE__
