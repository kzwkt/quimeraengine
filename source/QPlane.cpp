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

#include "QPlane.h"

#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix3x4.h"
#include "QMatrix4x3.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"
#include "SQAngle.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################
    
QPlane::QPlane()
{
}

QPlane::QPlane(const QPlane &plane) : QBasePlane(plane)
{
}

QPlane::QPlane(const QBasePlane &plane) : QBasePlane(plane)
{
}

QPlane::QPlane(const float_q fA, const float_q fB, const float_q fC, const float_q fD) :
                QBasePlane(fA, fB, fC, fD)
{
}

QPlane::QPlane(const float_q fValueAll) : QBasePlane(fValueAll)
{
}

QPlane::QPlane(float_q* arValues) : QBasePlane(arValues)
{
}

QPlane::QPlane(const vf32_q value) : QBasePlane(value)
{
}

QPlane::QPlane(const QVector3 &vPoint1, const QVector3 &vPoint2, const QVector3 &vPoint3)
{
    this->QPlaneImp(vPoint1, vPoint2, vPoint3);
}

QPlane::QPlane(const QVector4 &vPoint1, const QVector4 &vPoint2, const QVector4 &vPoint3)
{
    this->QPlaneImp(vPoint1, vPoint2, vPoint3);
}

template <class VectorType>
void QPlane::QPlaneImp(const VectorType &vPoint1, const VectorType &vPoint2, const VectorType &vPoint3)
{
    // If points coincide, the plane can't be determined
    QE_ASSERT_WARNING( vPoint1 != vPoint2 && vPoint2 != vPoint3 && vPoint3 != vPoint1, "Input points must not coincide");

    // Creates two vectors, to obtain the direction vector of the plane via cross product
    VectorType vAux1 = ( vPoint1 - vPoint2 ).CrossProduct( vPoint1 - vPoint3 );;

    // Checkout to avoid the possibility of tree colinear points.
    QE_ASSERT_WARNING(!vAux1.IsZero(), "Input points must not be colinear");

    // Plane equation
    *this = QPlane( vAux1.x, vAux1.y, vAux1.z, -vAux1.DotProduct(vPoint1) ).Normalize();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QPlane QPlane::operator*(const float_q fScalar) const
{
    return QPlane(this->a * fScalar, this->b * fScalar, this->c * fScalar, this->d * fScalar);
}

// Left float product
QPlane operator*(const float_q fScalar, const QPlane &plane)
{
    return QPlane(plane.a * fScalar, plane.b * fScalar, plane.c * fScalar, plane.d * fScalar);
}

QPlane QPlane::operator/(const float_q fScalar) const
{
    QE_ASSERT_WARNING(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    return QPlane(this->a * DIVISOR, this->b * DIVISOR, this->c * DIVISOR, this->d * DIVISOR);
}

QPlane& QPlane::operator*=(const float_q fScalar)
{
    this->a *= fScalar;
    this->b *= fScalar;
    this->c *= fScalar;
    this->d *= fScalar;

    return *this;
}

QPlane& QPlane::operator/=(const float_q fScalar)
{
    // Checkout to avoid division by 0
    QE_ASSERT_WARNING(fScalar != SQFloat::_0, "Input value must not equal zero");

    const float_q &DIVISOR = SQFloat::_1/fScalar;

    this->a *= DIVISOR;
    this->b *= DIVISOR;
    this->c *= DIVISOR;
    this->d *= DIVISOR;

    return *this;
}

QPlane QPlane::operator-() const
{
    return QPlane(-this->a, -this->b, -this->c, this->d);
}

QPlane& QPlane::operator=(const QBasePlane &plane)
{
    QBasePlane::operator=(plane);
    return *this;
}

QPlane QPlane::Normalize() const
{
    // Checkout to avoid division by zero.
    QE_ASSERT_WARNING(this->GetLength() != SQFloat::_0, "A plane whose length equals zero cannot be normalized, this will produce a division by zero");

    float_q fInvDivisor = SQFloat::_1 / this->GetLength();

    return QPlane(this->a * fInvDivisor, this->b * fInvDivisor, this->c * fInvDivisor, this->d * fInvDivisor);
}

float_q QPlane::DotProduct(const QVector3 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_q QPlane::DotProduct(const QVector4 &vVector) const
{
    return this->DotProductImp(vVector);
}

float_q QPlane::DotProduct(const QBasePlane &plane) const
{
    return plane.a * this->a + plane.b * this->b + plane.c * this->c;
}

float_q QPlane::AngleBetween(const QVector3 &vVector) const
{
    return this->AngleBetweenImp(vVector);
}

float_q QPlane::AngleBetween(const QVector4 &vVector) const
{
    return this->AngleBetweenImp(vVector);
}

float_q QPlane::AngleBetween(const QBasePlane &plane) const
{
    // When the length of a plane equals zero, the calculated angle is not correct
    QE_ASSERT_WARNING( SQFloat::IsNotZero(this->GetSquaredLength()) && !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)), 
               "When the length of a plane equals zero, the calculated angle is not correct" );

    float_q DOT = this->DotProduct(plane);

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT > SQFloat::_1)
        DOT = SQFloat::_1;
    else if(DOT < -SQFloat::_1)
        DOT = -SQFloat::_1;

    float_q fAngle = acos_q(DOT);

    QE_ASSERT_WARNING( !SQFloat::IsNaN(fAngle), "The resultant angle is NAN" );
    
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

QBaseVector3 QPlane::PointProjection(const QBaseVector3 &vPoint) const
{
    return this->PointProjectionImp(vPoint);
}

QBaseVector4 QPlane::PointProjection(const QBaseVector4 &vPoint) const
{
    QBaseVector4 vAux = this->PointProjectionImp(vPoint);
    vAux.w = vPoint.w;
    return vAux;
}

bool QPlane::Contains(const QBaseVector3 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

bool QPlane::Contains(const QBaseVector4 &vPoint) const
{
    return this->ContainsImp(vPoint);
}

float_q QPlane::GetLength() const
{
    return sqrt_q(this->a * this->a + this->b * this->b + this->c * this->c);
}

float_q QPlane::GetSquaredLength() const
{
    return this->a * this->a + this->b * this->b + this->c * this->c;
}

QVector3 QPlane::GetNormal() const
{
    return QVector3(this->a, this->b, this->c);
}

float_q QPlane::PointDistance(const QBaseVector3 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

float_q QPlane::PointDistance(const QBaseVector4 &vPoint) const
{
    return PointDistanceImp(vPoint);
}

EQIntersections QPlane::IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector3 &vIntersection) const
{
    return IntersectionPointImp(plane1, plane2, vIntersection);
}

EQIntersections QPlane::IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector4 &vIntersection) const
{
    EQIntersections eNumIntersections = IntersectionPointImp(plane1, plane2, vIntersection);
    return eNumIntersections;
}

EQSpaceRelation QPlane::SpaceRelation(const QBasePlane &plane) const
{
    // It's impossible to calculate the spacial relation for a null plane
    QE_ASSERT_WARNING( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)), "It's impossible to calculate the spacial relation for a null plane" );
    QE_ASSERT_WARNING( !(SQFloat::IsZero(plane.a) && SQFloat::IsZero(plane.b) && SQFloat::IsZero(plane.c)), "It's impossible to calculate the spacial relation for a null plane" );

    // Cross product: checks if planes are parallel or coincident
    if (SQFloat::IsZero(plane.b * this->c - plane.c * this->b) &&
        SQFloat::IsZero(plane.c * this->a - plane.a * this->c) &&
        SQFloat::IsZero(plane.a * this->b - plane.b * this->a))
    {
        if (plane == *this) // They are the same plane.
            return EQSpaceRelation::E_Contained;
        else if (SQFloat::IsNegative(plane.d - this->d))
            return EQSpaceRelation::E_NegativeSide;
        else
            return EQSpaceRelation::E_PositiveSide;
    }
    else // Are not parallel
        return EQSpaceRelation::E_BothSides;
}

QPlane QPlane::Rotate(const QRotationMatrix3x3 &rotation) const
{
    QVector3 vAux = this->GetNormal().Transform(rotation);

    return QPlane(vAux.x, vAux.y, vAux.z, this->d);
}

QPlane QPlane::Rotate(const QQuaternion &qRotation) const
{
    QVector3 vAux = this->GetNormal().Transform(qRotation);

    return QPlane(vAux.x, vAux.y, vAux.z, this->d);
}

QPlane QPlane::Scale(const QScalingMatrix3x3 &scale) const
{
    // None of the scale values should equal zero
    QE_ASSERT_WARNING( scale.ij[0][0] != SQFloat::_0 && scale.ij[1][1] != SQFloat::_0 && scale.ij[2][2] != SQFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return QPlane(this->a / scale.ij[0][0], this->b / scale.ij[1][1], this->c / scale.ij[2][2], this->d)
            .Normalize();
}

QPlane QPlane::Scale(const QBaseVector3 &vScale) const
{
    // None of the scale values should equal zero
    QE_ASSERT_WARNING( vScale.x != SQFloat::_0 && vScale.y != SQFloat::_0 && vScale.z != SQFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return QPlane(this->a / vScale.x, this->b / vScale.y, this->c / vScale.z, this->d)
            .Normalize();
}

QPlane QPlane::Scale(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ) const
{
    // None of the scale values should equal zero
    QE_ASSERT_WARNING( fScaleX != SQFloat::_0 && fScaleY != SQFloat::_0 && fScaleZ != SQFloat::_0, "None of the scale values should equal zero, this will cause a division by zero" );

    return QPlane(this->a / fScaleX, this->b / fScaleY, this->c / fScaleZ, this->d)
            .Normalize();
}

QPlane QPlane::Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
{
    return QPlane(this->a,
                  this->b,
                  this->c,
                  this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
}

QPlane QPlane::Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
{
    return QPlane(this->a,
                  this->b,
                  this->c,
                  this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
}

QPlane QPlane::Translate(const QBaseVector3 &vTranslation) const
{
    return QPlane(this->a,
                  this->b,
                  this->c,
                  this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
}

QPlane QPlane::Translate(const QBaseVector4 &vTranslation) const
{
    return QPlane(this->a,
                  this->b,
                  this->c,
                  this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
}

QPlane QPlane::Translate(const float_q fTranslationX, const float_q fTranslationY, const float_q fTranslationZ) const
{
    return QPlane(this->a,
                  this->b,
                  this->c,
                  this->d - (this->a * fTranslationX + this->b * fTranslationY + this->c * fTranslationZ));
}

QPlane QPlane::Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
{
    // Explanation:
    //
    // Let it be P a plane and A a point of the plane so the cartesian equation of the plane would be: PxAx + PyAy + PzAz + PwAw = 0.
    //
    // We can write it as vectors: P * A = 0
    // Or as matrices: P * At = 0 (note that the matrix A must be transposed to be multiplied by the matrix P, so they are 1x4 * 4x1)
    //
    //                  [Ax]
    //  [Px Py Pz Pw] * [Ay] = 0
    //                  [Az]
    //                  [Aw]
    //
    // Note: If you change the order of the operands and transpose P instead of A, it doesn't affect the result because, in the end,
    //       the only change is that the transformation matrix is inverted and transposed in the opposite order, which doesn't affect
    //       invertible matrices (as affine transformation matrices are).
    //
    // Now we want to find a plane P', which results of transforming P by a transformation matrix M, for which every point A transformed
    // by M fulfils the equation:
    //
    // P' * (A * M)t = 0
    //
    // So using both equations:
    //
    // P' * (A * M)t == 0 == P * At     -->    P' * (A * M)t == P * At
    //
    // And expanding the transposition (note that transposing a product of matrices inverts the operands' order):
    //
    // P' * Mt * At == P * At    -->    P' * Mt == P    -->    P' == P * Mt^-1
    //
    // Finally we have that P' equals P multiplied by the inverse of the transpose of the original transformation matrix
    // See also: http://www.opengl.org/discussion_boards/showthread.php/159564-Clever-way-to-transform-plane-by-matrix

    QMatrix4x3 inverse = transformation.Invert();

    // The product is implemented using the transpose of the inverted transformation
    return QPlane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2],
                  this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2],
                  this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2],
                  this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d)
                  .Normalize();
}

QPlane QPlane::Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
{
    // Explanation:
    //
    // Let it be P a plane and A a point of the plane so the cartesian equation of the plane would be: PxAx + PyAy + PzAz + PwAw = 0.
    //
    // We can write it as vectors: P * A = 0
    // Or as matrices: P * At = 0 (note that the matrix A must be transposed to be multiplied by the matrix P, so they are 1x4 * 4x1)
    //
    //                  [Ax]
    //  [Px Py Pz Pw] * [Ay] = 0
    //                  [Az]
    //                  [Aw]
    //
    // Note: If you change the order of the operands and transpose P instead of A, it doesn't affect the result because, in the end,
    //       the only change is that the transformation matrix is inverted and transposed in the opposite order, which doesn't affect
    //       invertible matrices (as affine transformation matrices are).
    //
    // Now we want to find a plane P', which results of transforming P by a transformation matrix M, for which every point A transformed
    // by M fulfils the equation:
    //
    // P' * (A * M)t = 0
    //
    // So using both equations:
    //
    // P' * (A * M)t == 0 == P * At     -->    P' * (A * M)t == P * At
    //
    // And expanding the transposition (note that transposing a product of matrices inverts the operands' order):
    //
    // P' * Mt * At == P * At    -->    P' * Mt == P    -->    P' == P * Mt^-1
    //
    // Finally we have that P' equals P multiplied by the inverse of the transpose of the original transformation matrix
    // See also: http://www.opengl.org/discussion_boards/showthread.php/159564-Clever-way-to-transform-plane-by-matrix

    QMatrix4x4 inverse = transformation.Invert();

    // The product is implemented using the transpose of the inverted transformation
    return QPlane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2],
                  this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2],
                  this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2],
                  this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d)
                  .Normalize();
}

QPlane QPlane::Transform(const QSpaceConversionMatrix &spaceConversion) const
{
    QMatrix4x4 inverse = spaceConversion.Invert();

    // The product is implemented using the transpose of m
    return QPlane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2] + this->d * inverse.ij[0][3],
                  this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2] + this->d * inverse.ij[1][3],
                  this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2] + this->d * inverse.ij[2][3],
                  this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d * inverse.ij[3][3])
                  .Normalize();
}

QPlane QPlane::RotateWithPivot(const QQuaternion &qRotation, const QVector3 &vPivot) const
{
    return this->RotateWithPivotImp(qRotation, vPivot);
}

QPlane QPlane::RotateWithPivot(const QQuaternion &qRotation, const QVector4 &vPivot) const
{
    return this->RotateWithPivotImp(qRotation, vPivot);
}

QPlane QPlane::RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector3 &vPivot) const
{
    return this->RotateWithPivotImp(rotation, vPivot);
}

QPlane QPlane::RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector4 &vPivot) const
{
    return this->RotateWithPivotImp(rotation, vPivot);
}

QPlane QPlane::ScaleWithPivot(const QBaseVector3 &vScale, const QVector3 &vPivot) const
{
    return this->ScaleWithPivotImp(vScale, vPivot);
}

QPlane QPlane::ScaleWithPivot(const QBaseVector3 &vScale, const QVector4 &vPivot) const
{
    return this->ScaleWithPivotImp(vScale, vPivot);
}

QPlane QPlane::ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const QVector3 &vPivot) const
{
    return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
}

QPlane QPlane::ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const QVector4 &vPivot) const
{
    return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
}

QPlane QPlane::ScaleWithPivot(const QScalingMatrix3x3 &scale, const QVector3 &vPivot) const
{
    return this->ScaleWithPivotImp(scale, vPivot);
}

QPlane QPlane::ScaleWithPivot(const QScalingMatrix3x3 &scale, const QVector4 &vPivot) const
{
    return this->ScaleWithPivotImp(scale, vPivot);
}

QPlane QPlane::TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector3 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

QPlane QPlane::TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector4 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

QPlane QPlane::TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector3 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

QPlane QPlane::TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector4 &vPivot) const
{
    return this->TransformWithPivotImp(transformation, vPivot);
}

string_q QPlane::ToString() const
{
    return string_q("PL(") + SQFloat::ToString(this->a) + QE_L(",") + SQFloat::ToString(this->b) +
               QE_L(",")   + SQFloat::ToString(this->c) + QE_L(",") + SQFloat::ToString(this->d) + QE_L(")");
}

template <class VectorType>
float_q QPlane::DotProductImp(const VectorType &vVector) const
{
    return vVector.x * this->a + vVector.y * this->b + vVector.z * this->c;
}

template <class VectorType>
float_q QPlane::AngleBetweenImp(const VectorType &vVector) const
{
    // When the length of either the plane or the vector equals zero, the calculated angle is not correct
    QE_ASSERT_WARNING( SQFloat::IsNotZero(this->GetSquaredLength()) && !(SQFloat::IsZero(vVector.x) && SQFloat::IsZero(vVector.y) && SQFloat::IsZero(vVector.z)), 
               "When the length of either the plane or the vector equals zero, the calculated angle is not correct" );

    // Length of plane equals one due to plane is supposed to be normalized.
    const float_q &DOT_LENGTH = sqrt_q(vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z);

    // Checkout to avoid division by zero.
    QE_ASSERT_WARNING(DOT_LENGTH != SQFloat::_0, "Input vector must not be null, this will produce a division by zero");

    float_q DOT = this->DotProduct(vVector)/DOT_LENGTH;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT > SQFloat::_1)
        DOT = SQFloat::_1;
    else if(DOT < -SQFloat::_1)
        DOT = -SQFloat::_1;

    float_q fAngle = acos_q(DOT);

    QE_ASSERT_WARNING( !SQFloat::IsNaN(fAngle), "The resultant angle is NAN" );

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SQAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

template <class VectorType>
QPlane QPlane::RotateWithPivotImp(const QQuaternion &qRotation, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Rotate(qRotation)
                .Translate(vPivot);
}

template <class VectorType>
QPlane QPlane::RotateWithPivotImp(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Rotate(rotation)
                .Translate(vPivot);
}

template <class VectorType>
QPlane QPlane::ScaleWithPivotImp(const QBaseVector3 &vScale, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(vScale)
                .Translate(vPivot);
}

template <class VectorType>
QPlane QPlane::ScaleWithPivotImp(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(fScaleX, fScaleY, fScaleZ)
                .Translate(vPivot);
}

template <class VectorType>
QPlane QPlane::ScaleWithPivotImp(const QScalingMatrix3x3 &scale, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Scale(scale)
                .Translate(vPivot);
}

template <class MatrixType, class VectorType>
QPlane QPlane::TransformWithPivotImp(const MatrixType &transformation, const VectorType &vPivot) const
{
    return this->Translate(-vPivot)
                .Transform(transformation)
                .Translate(vPivot);
}

template <class VectorType>
VectorType QPlane::PointProjectionImp(const VectorType &vPoint) const
{
    // The plane shouldn't be null
    QE_ASSERT_WARNING( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );
        
    // [SMELL] Thund: Can this line be replaced with a dot product + d?
    const float_q &PROJ = -(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);

    // [SMELL] Thund: Can this line contain all the operations so no 2 constructor calls are performed?
    VectorType vProjection;
    vProjection.x = PROJ * this->a  + vPoint.x;
    vProjection.y = PROJ * this->b  + vPoint.y;
    vProjection.z = PROJ * this->c  + vPoint.z;

    return vProjection;
}

template <class VectorType>
bool QPlane::ContainsImp(const VectorType &vPoint) const
{
    // The plane should not be null
    QE_ASSERT_WARNING( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );

    return SQFloat::IsZero(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
}

template <class VectorType>
float_q QPlane::PointDistanceImp(const VectorType &vPoint) const
{
    // The plane should not be null
    QE_ASSERT_WARNING( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );

    return SQFloat::Abs(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
}

template <class VectorType>
EQIntersections QPlane::IntersectionPointImp(const QBasePlane &plane1, const QBasePlane &plane2, VectorType &vIntersection) const
{
    // None of the planes should be null
    QE_ASSERT_WARNING( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)), "The plane should not be null, the result will be incorrect" );
    QE_ASSERT_WARNING( !(SQFloat::IsZero(plane1.a) && SQFloat::IsZero(plane1.b) && SQFloat::IsZero(plane1.c)), "Input planes should not be null, the result will be incorrect" );
    QE_ASSERT_WARNING( !(SQFloat::IsZero(plane2.a) && SQFloat::IsZero(plane2.b) && SQFloat::IsZero(plane2.c)), "Input planes should not be null, the result will be incorrect" );

    // Solved by Cramer method.
    const float_q &DET_C = this->a * plane1.b * plane2.c + this->b * plane1.c * plane2.a + this->c * plane1.a * plane2.b -
                            (this->c * plane1.b * plane2.a + this->a * plane1.c * plane2.b + this->b * plane1.a * plane2.c);
    const float_q &DET_X = this->c * plane1.b * plane2.d + this->d * plane1.c * plane2.b + this->b * plane1.d * plane2.c -
                            (this->d * plane1.b * plane2.c + this->b * plane1.c * plane2.d + this->c * plane1.d * plane2.b);
    const float_q &DET_Y = this->c * plane1.d * plane2.a + this->a * plane1.c * plane2.d + this->d * plane1.a * plane2.c -
                            (this->a * plane1.d * plane2.c + this->d * plane1.c * plane2.a + this->c * plane1.a * plane2.d);
    const float_q &DET_Z = this->d * plane1.b * plane2.a + this->a * plane1.d * plane2.b + this->b * plane1.a * plane2.d -
                            (this->a * plane1.b * plane2.d + this->b * plane1.d * plane2.a + this->d * plane1.a * plane2.b);

    if (!SQFloat::IsZero(DET_C)) // A range = 3, A* range = 3: Compatible system
    {
        const float_q &INV_DET_C = SQFloat::_1/DET_C;

        vIntersection.x = DET_X * INV_DET_C;
        vIntersection.y = DET_Y * INV_DET_C;
        vIntersection.z = DET_Z * INV_DET_C;

        return EQIntersections::E_One;
    }
    else if (SQFloat::IsZero(DET_X) && SQFloat::IsZero(DET_Y) && SQFloat::IsZero(DET_Z)) // A range < 3, A* range < 3
    {
        // A range = 2, A* range < 3: Undetermined compatible system
        if (SQFloat::IsNotZero(this->a  * plane1.b - this->b  * plane1.a) ||
            SQFloat::IsNotZero(this->a  * plane1.c - this->c  * plane1.a) ||
            SQFloat::IsNotZero(this->a  * plane2.b - this->b  * plane2.a) ||
            SQFloat::IsNotZero(this->a  * plane2.c - this->c  * plane2.a) ||
            SQFloat::IsNotZero(this->b  * plane1.c - this->c  * plane1.b) ||
            SQFloat::IsNotZero(this->b  * plane2.c - this->c  * plane2.b) ||
            SQFloat::IsNotZero(plane1.a * plane2.b - plane1.b * plane2.a) ||
            SQFloat::IsNotZero(plane1.a * plane2.c - plane1.c * plane2.a) ||
            SQFloat::IsNotZero(plane1.b * plane2.c - plane1.c * plane2.b))

            return EQIntersections::E_Infinite;
        else //// A range = 1, A* range < 3
        {
            if (*this == plane1 && *this == plane2) // Coincident planes (A* range = 1)
                return EQIntersections::E_Infinite;
            else // Incompatible system (A* range = 2)
                return EQIntersections::E_None;
        }
    }
    else // A range < 3, A* range = 3: Incompatible system
        return EQIntersections::E_None;
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const QPlane& QPlane::GetNullPlane()
{
    static const QPlane NULLPLANE(SQFloat::_0,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
    return NULLPLANE;
}

const QPlane& QPlane::GetPlaneZX()
{
    static const QPlane PLANEZX(SQFloat::_0,  SQFloat::_1,  SQFloat::_0,  SQFloat::_0);
    return PLANEZX;
}

const QPlane& QPlane::GetPlaneXY()
{
    static const QPlane PLANEXY(SQFloat::_0,  SQFloat::_0,  SQFloat::_1,  SQFloat::_0);
    return PLANEXY;
}

const QPlane& QPlane::GetPlaneYZ()
{
    static const QPlane PLANEYZ(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
    return PLANEYZ;
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
