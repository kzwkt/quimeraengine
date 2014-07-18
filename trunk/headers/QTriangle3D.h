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

#ifndef __QTRIANGLE3D__
#define __QTRIANGLE3D__

#include "EQSpaceRelation.h"
#include "QTriangle.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QQuaternion.h"
#include "QPlane.h"
#include "SQPoint.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::vf32_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a triangle in 3D.
/// </summary>
/// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
template <class VectorType>
class QTriangle3D : public QTriangle<VectorType>
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QTriangle3D()
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="triangle">[IN] The 3D triangle from which we want to create a copy in the resident 3D triangle.</param>
    QTriangle3D(const QTriangle3D<VectorType> &triangle) : QTriangle<VectorType>(triangle)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="triangle">[IN] The 3D triangle in which we want resident 3D triangle to be based.</param>
    QTriangle3D(const QBaseTriangle<VectorType> &triangle) : QTriangle<VectorType>(triangle)
    {
    }

    /// <summary>
    /// Constructor from three vector types, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector types which defines vertex A.</param>
    /// <param name="vB">[IN] Vector types which defines vertex B.</param>
    /// <param name="vC">[IN] Vector types which defines vertex C.</param>
    QTriangle3D(const VectorType &vA, const VectorType &vB, const VectorType &vC) : QTriangle<VectorType>(vA, vB, vC)
    {
    }

    /// <summary>
    /// Constructor from three pointer-to-float type, one for each vertex.
    /// </summary>
    /// <remarks>
    /// Each pointer references to an array which has at least three or four elements.
    /// </remarks>
    /// <param name="arValuesA">[IN] Array of components of the vertex A. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesB">[IN] Array of components of the vertex B. If it is null, the behavior is undefined.</param>
    /// <param name="arValuesC">[IN] Array of components of the vertex C. If it is null, the behavior is undefined.</param>
    QTriangle3D(const float_q* arValuesA, const float_q* arValuesB, const float_q* arValuesC) :
                           QTriangle<VectorType>(arValuesA, arValuesB, arValuesC)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 packed floating point values, one for each vertex.
    /// </summary>
    /// <param name="valueA">[IN] 4x32 packed value which defines vertex A.</param>
    /// <param name="valueB">[IN] 4x32 packed value which defines vertex B.</param>
    /// <param name="valueC">[IN] 4x32 packed value which defines vertex C.</param>
    QTriangle3D(const vf32_q& valueA, const vf32_q& valueB, const vf32_q& valueC) :
                           QTriangle<VectorType>(valueA, valueB, valueC)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided triangle to the resident triangle.
    /// </summary>
    /// <param name="triangle">[IN] 3D triangle that is assigned to current triangle.</param>
    /// <returns>
    /// A reference to the triangle.
    /// </returns>
    QTriangle3D<VectorType>& operator=(const QBaseTriangle<VectorType> &triangle)
    {
        QBaseTriangle<VectorType>::operator=(triangle);
        return *this;
    }

    /// <summary>
    /// Calculates the triangle's normal vector.
    /// </summary>
    /// <remarks>
    /// The resultant vector can be deduced by imagining that the triangle is facing the screen; if the vertices are traversed in alphabetical order (A, B, C then A again),
    /// clockwise, the vector points toward the outside of the screen. If the turn direction is counter-clockwise, the vector points toward the interior of the screen.<br/>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The normal vector.
    /// </returns>
    QVector3 GetNormal() const
    {
        const QVector3 A_TO_B = QVector3(this->B - this->A);
        const QVector3 B_TO_C = QVector3(this->C - this->B);

        return A_TO_B.CrossProduct(B_TO_C).Normalize();
    }

    /// <summary>
    /// Calculates triangle's circumcenter.
    /// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The triangle's circumcenter.
    /// </returns>
    VectorType GetCircumcenter() const
    {
        // Vertices shouldn't coincide
        QE_ASSERT( this->A != this->B && this->B != this->C && this->C != this->A, "Vertices shouldn't coincide, this may cause a division by zero" );

        // More information: https://www.box.net/shared/9736bjiyq1

        //STEP 1: Calculate all previous stuff
        const VectorType A_TO_B(this->B - this->A);
        const VectorType B_TO_C(this->C - this->B);
        const VectorType C_TO_A(this->A - this->C);

        // Triangle´s semiperimeter
        const float_q SEMIPERIMETER = (A_TO_B.GetLength() + B_TO_C.GetLength() + C_TO_A.GetLength()) * SQFloat::_0_5;
        // Triangle´s area
        const float_q AREA = sqrt_q(SEMIPERIMETER * (SEMIPERIMETER - A_TO_B.GetLength()) * (SEMIPERIMETER - B_TO_C.GetLength()) * (SEMIPERIMETER - C_TO_A.GetLength()));

        const VectorType CROSS_PRODUCT_AB_BC = A_TO_B.CrossProduct(B_TO_C);
        const VectorType CROSS_PRODUCT_CA_AB_BC = C_TO_A.CrossProduct(CROSS_PRODUCT_AB_BC);

        //STEP 2: Calculate circumcenter
        return ((this->A + this->C) * SQFloat::_0_5) + (A_TO_B.DotProduct(B_TO_C) / (SQFloat::_8 * AREA * AREA)) * CROSS_PRODUCT_CA_AB_BC;
    }

    /// <summary>
    /// This method performs a translation of the resident triangle given by the provided vector.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    QTriangle3D<VectorType> Translate(const QBaseVector3 &vTranslation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Translate(vTranslation, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Translates the triangle applying a [4x3] translation matrix.
    /// </summary>
    /// <param name="translation">[IN] The [4x3] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    QTriangle3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Translate(translation, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Translates the triangle applying a [4x4] translation matrix.
    /// </summary>
    /// <param name="translation">[IN] The [4x4] translation matrix to be applied.</param>
    /// <returns>
    /// The translated triangle.
    /// </returns>
    QTriangle3D<VectorType> Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Translate(translation, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> Rotate(const QQuaternion &qRotation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Rotate(qRotation, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Rotates the triangle applying the provided rotation matrix.
    /// </summary>
    /// <param name="rotation">[IN] Rotation matrix to be applied.</param>
    /// <returns>
    /// The rotated triangle.
    /// </returns>
    QTriangle3D<VectorType> Rotate(const QRotationMatrix3x3 &rotation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Rotate(rotation, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> RotateWithPivot(const QQuaternion &qRotation, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::RotateWithPivot(qRotation, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method scales the resident triangle by the scale contained in the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] Vector which contains the scale to be applied in every axis.</param>
    /// <returns>
    /// The scaled triangle.
    /// </returns>
    QTriangle3D<VectorType> Scale(const QBaseVector3 &vScale) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Scale(vScale, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Scales the triangle applying a scale matrix.
    /// </summary>
    /// <param name="scale">[IN] Scale matrix to be applied.</param>
    /// <returns>
    ///The scaled triangle.
    /// </returns>
    QTriangle3D<VectorType> Scale(const QScalingMatrix3x3 &scale) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Scale(scale, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> ScaleWithPivot(const QBaseVector3 &vScale, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::ScaleWithPivot(vScale, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const VectorType& vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Transforms the resident triangle applying the [4x3] transformation matrix provided.
    /// </summary>
    /// <param name="transformation">[IN] A [4x3] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    QTriangle3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Transform(transformation, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Transforms the resident triangle applying the [4x4] transformation matrix provided.
    /// </summary>
    /// <param name="transformation">[IN] A [4x4] transformation matrix to be applied.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    QTriangle3D<VectorType> Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::Transform(transformation, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> RotateWithPivot(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::RotateWithPivot(rotation, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
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
    QTriangle3D<VectorType> ScaleWithPivot(const QScalingMatrix3x3 &scale, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::ScaleWithPivot(scale, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method transforms the resident triangle applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    QTriangle3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// This method transforms the resident triangle applying the provided transformation matrix,
    /// acting the provided vector as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Matrix which contains the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point which acts as pivot of the transformation.</param>
    /// <returns>
    /// The transformed triangle.
    /// </returns>
    QTriangle3D<VectorType> TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const VectorType &vPivot) const
    {
        QTriangle3D<VectorType> auxTriangle = *this;
        SQPoint::TransformWithPivot(transformation, vPivot, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }
    
    /// <summary>
    /// This method transforms the resident triangle applying the provided space conversion matrix.
    /// </summary>
    /// <param name="spaceConversion">[IN] Matrix which contains the space conversion transformation to be applied.</param>
    /// <returns>
    /// The converted triangle.
    /// </returns>
    QTriangle<VectorType> Transform(const QSpaceConversionMatrix &spaceConversion) const
    {
        QTriangle<VectorType> auxTriangle = *this;
        SQPoint::Transform(spaceConversion, rcast_q(&auxTriangle, VectorType*), 3);
        return auxTriangle;
    }

    /// <summary>
    /// Checks the space relation between the triangle and a plane received as parameter.
    /// </summary>
    /// <remarks>
    /// Space relation means that the triangle is in the positive side of the space divided by the plane, 
    /// in the negative side, in both sides (intersection) or even the triangle is contained in the plane.<br/>
    /// If one or two vertices belong to the plane, the third vertex will determine whether the triangle
    /// is in the positive or negative side.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with current triangle. If it is null, the result is undefined.</param>
    /// <returns>
    /// An enumerated value like follows:<br/>
    /// - Contained in the plane
    /// - Positive Side
    /// - Negative Side
    /// - Both Sides (intersects the plane).
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const
    {
        // The plane should not be null
        QE_ASSERT( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)), "Input plane should not be null" );

        const float_q &DIST_TO_A = plane.a * this->A.x + plane.b * this->A.y + plane.c * this->A.z + plane.d;
        const float_q &DIST_TO_B = plane.a * this->B.x + plane.b * this->B.y + plane.c * this->B.z + plane.d;
        const float_q &DIST_TO_C = plane.a * this->C.x + plane.b * this->C.y + plane.c * this->C.z + plane.d;

        if ( SQFloat::IsZero(DIST_TO_A) && SQFloat::IsZero(DIST_TO_B) && SQFloat::IsZero(DIST_TO_C) )
            return EQSpaceRelation::E_Contained;
        else if ( SQFloat::IsGreaterOrEquals(DIST_TO_A, SQFloat::_0) && SQFloat::IsGreaterOrEquals(DIST_TO_B, SQFloat::_0) && SQFloat::IsGreaterOrEquals(DIST_TO_C, SQFloat::_0) )
            return EQSpaceRelation::E_PositiveSide;
        else if ( SQFloat::IsLessOrEquals(DIST_TO_A, SQFloat::_0) && SQFloat::IsLessOrEquals(DIST_TO_B, SQFloat::_0) &&
                  SQFloat::IsLessOrEquals(DIST_TO_C, SQFloat::_0) )
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_BothSides;
    }

    /// <summary>
    /// Moves the triangle along its normal vector the units indicated by a scalar value.
    /// </summary>
    /// <remarks>
    /// If any of the vertices of the triangle coincide or if they are colinear, the result is undefined.
    /// </remarks>
    /// <param name="fAmount">[IN] The amount of movement.</param>
    /// <returns>
    /// The extruded triangle.
    /// </returns>
    QTriangle3D<VectorType> Extrude(const float_q &fAmount) const
    {
        VectorType vLangthenedNormalVector = VectorType(this->GetNormal() * fAmount);

        return QTriangle3D<VectorType>(this->A + vLangthenedNormalVector,
                                       this->B + vLangthenedNormalVector,
                                       this->C + vLangthenedNormalVector);
    }

    /// <summary>
    /// Calculates triangle's orthocenter.
    /// </summary>
    /// <remarks>
    /// When using 4D vectors, the W component of the resultant point will depend on the W component of the
    /// vertices of the triangle.<br/>
    /// If any of the vertices of the triangle coincide, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The orthocenter.
    /// </returns>
    VectorType GetOrthocenter() const
    {
        // Method from here: http://descartes.cnice.mec.es/materiales_didacticos/OrtoCircun/Ortocentro.htm

        const VectorType &AB = this->B - this->A;
        const VectorType &BC = this->C - this->B;
        const VectorType &CA = this->A - this->C;

        // Normal to BC in ABC plane
        const VectorType &NORMAL_TO_BC = ( BC.CrossProduct(AB) ).CrossProduct(BC);

        // NORMAL_TO_BC and AB can't be perpendicular, but we ensure it:
        const float_q &DOT = NORMAL_TO_BC.DotProduct(AB);

        QE_ASSERT(DOT != SQFloat::_0, "\"NORMAL_TO_BC\" and \"AB\" can't be perpendicular");

        return this->A - ( CA.DotProduct(AB) / DOT ) * NORMAL_TO_BC;
    }

    /// <summary>
    /// Projects resident triangle over a given plane, storing the resultant triangle in the provided one.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain correct result.
    /// </remarks>
    /// <param name="plane">[IN] Plane where to project the resident triangle. If it is null, the result is undefined.</param>
    /// <returns>
    /// The projected triangle.
    /// </returns>
    QTriangle3D<VectorType> ProjectToPlane(const QPlane &plane) const
    {
        return QTriangle3D<VectorType>(plane.PointProjection(this->A),
                                       plane.PointProjection(this->B),
                                       plane.PointProjection(this->C));
    }

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QTriangle3D<Kinesis::QuimeraEngine::Tools::Math::QVector3>;
template class QE_LAYER_TOOLS_SYMBOLS QTriangle3D<Kinesis::QuimeraEngine::Tools::Math::QVector4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRIANGLE3D__
