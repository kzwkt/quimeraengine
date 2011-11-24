// [TERMS&CONDITIONS]

#ifndef __QSPHERE__
#define __QSPHERE__

#include "QOrb.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QPoint.h"
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


    // CONSTANTS
    // ---------------
public:

	/// <summary>
    /// Unit sphere placed in the center of coordinates and whose radius equals to 1.
	/// </summary>
    static const QSphere<VectorType> UnitSphere;


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
        QPoint::Translate(vTranslate, &this->Center, 1);
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
        QPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, &this->Center, 1);
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
        QPoint::Rotate(q, &this->Center, 1);
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
        QPoint::RotateWithPivot(q, vPivot, &this->Center, 1);
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
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    inline void Scale (const VectorType& vScale)
    {
        QPoint::Scale(vScale, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //Radius *= reinterpret_cast<const VectorType&> (vScale).GetLength();
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
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
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    inline void Scale (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ)
    {
        QVector3 vScale(fScaleX, fScaleY, fScaleZ);

        this->Scale(vScale);
    }

 	/// <summary>
	/// Scales the sphere. Scaled sphere will be stored in the sphere received as parameter.
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
	/// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const VectorType& vScale, const VectorType& vPivot)
    {
        QPoint::ScaleWithPivot(vScale, vPivot, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //Radius *= reinterpret_cast<const VectorType&> (vScale).GetLength();
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
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
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    inline void ScaleWithPivot (const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot)
    {
        QPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &this->Center, 1);

        //Txaneto: Scaling only transforms the center point
        //QVector3 vScale(fScaleX, fScaleY, fScaleZ);
        //Radius *= vScale.GetLength();
    }

 	/// <summary>
	/// Scales the sphere using a pivot. Scaled sphere will be stored in the sphere received as parameter.
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
	/// Checks the space relation between current sphere and a plane received as parameter. Space relation means that
	/// the sphere is in the positive side of the space divided by the plane (subspace pointed by plane´s normal),
	/// in the negative side or in both sides (intersection).
	/// </summary>
	/// <param name="plane">[IN] The plane we want check the relation with current sphere.</param>
    /// <returns>
    /// An enumerated value like follows: Positive Side, Negative Side or Both Sides (intersects the plane).
    /// </returns>
	inline EQSpaceRelation SpaceRelation(const QBasePlane& plane) const
	{
        const float_q &fDistP = plane.a * this->Center.x + plane.b * this->Center.y + plane.c * this->Center.z + plane.d;

		if (QFloat::IsZero(fDistP))
		{
		    return EQSpaceRelation::E_BothSides;
		}
		else
        {
            const float_q &fAbsDistP = QFloat::Abs(fDistP)/( reinterpret_cast<QPlane &> (plane).GetLength() );

            if (QFloat::IsLessThan(fAbsDistP, Radius))
                return EQSpaceRelation::E_BothSides;
            else if (QFloat::IsNegative(fDistP))
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
	inline void ProjectToPlane(const QPlane& plane, QBaseOrb<VectorType>& outputOrb) const
	{
	    plane.PointProjection<VectorType>(this->Center, outputOrb.Center);
        outputOrb.Radius = this->Radius;
	}
};

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |    CONSTANTS DEFINITIONS	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorType>
const QSphere<VectorType> QSphere<VectorType>::UnitSphere(QVector3::ZeroVector, QFloat::_1);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPHERE__
