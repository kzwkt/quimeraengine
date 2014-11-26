//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

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

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a sphere in space.
/// </summary>
/// <remarks>
/// A sphere is the collection of all points that are equidistant from other point known as "Center".
/// </remarks>
/// <typeparam name="VectorType">Allowed types: QVector2, QVector3, QVector4.</typeparam>
template <class VectorType>
class QSphere : public QOrb<VectorType>
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
    QSphere()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="sphere">[IN] The sphere from which we want to create a copy in the resident sphere.</param>
    QSphere(const QSphere<VectorType> &sphere) : QOrb<VectorType>(sphere)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="orb">[IN] The sphere in which we want resident sphere to be based.</param>
    QSphere(const QBaseOrb<VectorType> &orb) : QOrb<VectorType>(orb)
    {
    }

    /// <summary>
    /// Constructor from a point as center of the sphere and its radius.
    /// </summary>
    /// <param name="vCenter">[IN] Vector that defines the center of the sphere.</param>
    /// <param name="fRadius">[IN] A floating point value to define the radius.</param>
    QSphere(const VectorType &vCenter, const float_q fRadius) : QOrb<VectorType>(vCenter, fRadius)
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
    static const QSphere<VectorType>& GetUnitSphere()
    {
        static const QSphere<VectorType> UNITSPHERE(VectorType::GetNullVector(), SQFloat::_1);
        return UNITSPHERE;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator.
    /// </summary>
    /// <param name="sphere">[IN] The orb to be copied from.</param>
    /// <returns>
    /// A reference to the modified orb.
    /// </returns>
    QSphere<VectorType>& operator=(const QBaseOrb<VectorType> &sphere)
    {
        QBaseOrb<VectorType>::operator=(sphere);
        return *this;
    }

    /// <summary>
    /// Translates the sphere.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector that contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    QSphere<VectorType> Translate(const QVector3 &vTranslation) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Translate(vTranslation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Translates the sphere.
    /// </summary>
    /// <param name="fTranslationX">[IN] Scalar that contains the translation on X axis.</param>
    /// <param name="fTranslationY">[IN] Scalar that contains the translation on Y axis.</param>
    /// <param name="fTranslationZ">[IN] Scalar that contains the translation on Z axis.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    QSphere<VectorType> Translate(const float_q fTranslationX, const float_q fTranslationY, const float_q fTranslationZ) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Rotates the sphere.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    QSphere<VectorType> Rotate(const QQuaternion &qRotation) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Rotate(qRotation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// Rotates the sphere using a pivot.
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion that represents the rotation.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the rotation.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    QSphere<VectorType> RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::RotateWithPivot(qRotation, vPivot, &auxSphere.Center, 1);
        return auxSphere;
    }

     /// <summary>
    /// Scales the sphere.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> Scale(const QVector3 &vScale, const float_q fRadiusScale) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Scale(vScale, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> Scale(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const float_q fRadiusScale) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere using a pivot.
    /// </summary>
    /// <param name="vScale">[IN] Vector that contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> ScaleWithPivot(const QVector3 &vScale, const float_q fRadiusScale, const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

     /// <summary>
    /// Scales the sphere using a pivot.
    /// </summary>
    /// <param name="fScaleX">[IN] Scalar that contains the scale on X axis.</param>
    /// <param name="fScaleY">[IN] Scalar that contains the scale on Y axis.</param>
    /// <param name="fScaleZ">[IN] Scalar that contains the scale on Z axis.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] Vector used as pivot for the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const float_q fRadiusScale,
                               const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method applies to the resident sphere the rotation defined by the provided rotation matrix
    /// around the coordinate axis centre.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contais the rotation to be applied.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    QSphere<VectorType> Rotate(const QRotationMatrix3x3 &rotation) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Rotate(rotation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method transforms the resident sphere by applying the rotation contained in the
    /// provided rotation matrix around a pivot point (which acts as center of rotation).
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix which contains the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The pivot point which the rotation will be accomplished around.</param>
    /// <returns>
    /// The rotated sphere.
    /// </returns>
    QSphere<VectorType> RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::RotateWithPivot(rotation, vPivot, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method performs a translation of the resident sphere given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    QSphere<VectorType> Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Translate(translation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method performs a translation of the resident sphere given by the provided translation matrix.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation to be applied.</param>
    /// <returns>
    /// The translated sphere.
    /// </returns>
    QSphere<VectorType> Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Translate(translation, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method scales the resident sphere by the scale contained in the provided scale matrix.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> Scale(const QScalingMatrix3x3 &scale, const float_q fRadiusScale) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Scale(scale, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method scales the resident sphere by the scale contained in the provided matrix,
    /// acting the provided vector as pivot of scale.
    /// </summary>
    /// <param name="scale">[IN] Matrix which contains the scale to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the scale.</param>
    /// <returns>
    /// The scaled sphere.
    /// </returns>
    QSphere<VectorType> ScaleWithPivot(const QScalingMatrix3x3 &scale, const float_q fRadiusScale, const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::ScaleWithPivot(scale, vPivot, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    QSphere<VectorType> Transform(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q fRadiusScale) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Transform(transformation, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix.
    /// </summary>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    QSphere<VectorType> Transform(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q fRadiusScale) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Transform(transformation, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided space conversion matrix.
    /// </summary>
    /// <remarks>
    /// Only the center of sphere is affected by this transformation.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    QSphere<VectorType> Transform(const QSpaceConversionMatrix &spaceConversion) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::Transform(spaceConversion, &auxSphere.Center, 1);
        return auxSphere;
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    QSphere<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const float_q fRadiusScale,
                                   const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// This method transforms the resident sphere applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="fRadiusScale">[IN] Multiplying factor to scale the sphere's radius.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed sphere.
    /// </returns>
    QSphere<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const float_q fRadiusScale,
                                   const VectorType &vPivot) const
    {
        QSphere<VectorType> auxSphere = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, &auxSphere.Center, 1);
        return QSphere<VectorType>(auxSphere.Center, auxSphere.Radius * fRadiusScale);
    }

    /// <summary>
    /// Checks the space relation between current sphere and a plane received as parameter.
    /// </summary>
    /// <remarks>
    /// Space relation means that the sphere is in the positive side of the space divided by the plane (subspace pointed by plane´s normal),
    /// in the negative side or in both sides (intersection).
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with current sphere. It must be normalized to obtain correct result. 
    /// If it is null, the result is undefined.</param>
    /// <returns>
    /// An enumerated value like follows:
    /// - Positive Side
    /// - Negative Side
    /// - Both Sides (intersects with the plane).
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
    {
        // The plane should not be null
        QE_ASSERT_WARNING( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)), "The plane should not be null" );

        // The radius should not equal zero
        QE_ASSERT_WARNING( SQFloat::IsNotZero(this->Radius), "The radius should not equal zero" );

        const float_q &DIST_P = plane.a * this->Center.x + plane.b * this->Center.y + plane.c * this->Center.z + plane.d;

        if (SQFloat::IsZero(DIST_P))
        {
            return EQSpaceRelation::E_BothSides;
        }
        else
        {
            const float_q &ABS_DIST_P = SQFloat::Abs(DIST_P);

            if (SQFloat::IsLessThan(ABS_DIST_P, Radius))
                return EQSpaceRelation::E_BothSides;
            else if (SQFloat::IsNegative(DIST_P))
                return EQSpaceRelation::E_NegativeSide;
            else
                return EQSpaceRelation::E_PositiveSide;
        }
    }

    /// <summary>
    /// Projects the sphere to a plane perpendicularly.
    /// </summary>
    /// <remarks>
    /// Only the center point of the sphere is projected. Radius keeps its original value. 
    /// </remarks>
    /// <param name="plane">[IN] Plane where current sphere will be projected. It must be normalized to obtain correct result. 
    /// If it is null, the result is undefined.</param>
    /// <returns>
    /// The projected sphere.
    /// </returns>
    QSphere<VectorType> ProjectToPlane(const QPlane &plane) const
    {
        // The plane should not be null
        QE_ASSERT_WARNING( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)), "The input plane should not be null" );

        return QSphere<VectorType>(plane.PointProjection(this->Center), this->Radius);
    }
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QSphere<Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QSphere<Kinesis::QuimeraEngine::Tools::Math::QVector4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPHERE__
