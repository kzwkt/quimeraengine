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

#ifndef __QPLANE__
#define __QPLANE__

#include "EQIntersections.h"
#include "EQSpaceRelation.h"
#include "QBasePlane.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix3x4.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// It represents the basic form of a 3D plane, defined by the equation:
///
/// \f$ ax + by + cz + d = 0\f$.
///
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from
/// plane to the origin, when the normal is normalized.
/// </summary>
class QDllExport QPlane : public QBasePlane
{
	// FRIENDS
	// ---------------
public:

    /// <summary>
    /// Product by a scalar: all coefficients are multiplied by the floating point value provided.<br>
    /// Shortcut to multiply on the left.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <param name="plane">[IN] Plane to be multiplied.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    friend QPlane operator*(const float_q &fScalar, const QPlane &plane);


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    QPlane()
    {
    }

    /// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="plane">[IN] The plane from which we want to create a copy in the resident plane.</param>
	inline QPlane(const QPlane &plane) : QBasePlane(plane)
	{
	}

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <param name="plane">The plane on which we base the resident plane.</param>
    inline QPlane(const QBasePlane &plane) : QBasePlane(plane)
    {
    }

	/// <summary>
	/// Constructor from a floating point value for each coefficient.
	/// </summary>
	/// <param name="fA">[IN] Floating point value for a coefficient.</param>
	/// <param name="fB">[IN] Floating point value for b coefficient.</param>
	/// <param name="fC">[IN] Floating point value for c coefficient.</param>
	/// <param name="fD">[IN] Floating point value for independent term d.</param>
    inline QPlane(const float_q &fA, const float_q &fB, const float_q &fC, const float_q &fD) :
                      QBasePlane(fA, fB, fC, fD)
    {
    }

	/// <summary>
	/// Constructor from a floating point value for all coefficients.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value for all the coefficients.</param>
	inline explicit QPlane(const float_q &fValueAll) : QBasePlane(fValueAll)
    {
    }

    /// <summary>
	/// Constructor from a pointer to an array of floating point values.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    inline explicit QPlane(float_q* arValues) : QBasePlane(arValues)
    {
    }

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed float containing the four components.</param>
	/// <remarks>
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
	/// 3rd value (c coefficient), 4th value (d independent term).
	/// </remarks>
    inline explicit QPlane(const vf32_q value) : QBasePlane(value)
    {
    }

    /// <summary>
	/// Constructor from three points.
	/// </summary>
    /// <remarks>
    /// This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.<br />
    /// The three points shouldn't be collinear and shouldn't coincide.
    /// </remarks>
	/// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	/// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	/// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    inline QPlane(const QVector3 &vPoint1, const QVector3 &vPoint2, const QVector3 &vPoint3)
    {
        this->QPlaneImp(vPoint1, vPoint2, vPoint3);
    }

    /// <summary>
	/// Constructor from three points.
	/// </summary>
    /// <remarks>
    /// This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.<br />
    /// The three points shouldn't be collinear and shouldn't coincide.
    /// </remarks>
	/// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	/// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	/// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    inline QPlane(const QVector4 &vPoint1, const QVector4 &vPoint2, const QVector4 &vPoint3)
    {
        this->QPlaneImp(vPoint1, vPoint2, vPoint3);
    }

protected:

	// <summary>
	// Constructor from three points.
	// </summary>
    // <remarks>
    // This method produces a normalized plane. The normal of the plane depends on the order the points are passed as parameters.
    // </remarks>
	// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    template <class VectorType>
    inline void QPlaneImp(const VectorType &vPoint1, const VectorType &vPoint2, const VectorType &vPoint3)
    {
        // If points coincide, the plane can't be determined
        QE_ASSERT( vPoint1 != vPoint2 && vPoint2 != vPoint3 && vPoint3 != vPoint1);

        // Creates two vectors, to obtain the direction vector of the plane via cross product
        VectorType vAux1 = ( vPoint1 - vPoint2 ).CrossProduct( vPoint1 - vPoint3 );;

        // Checkout to avoid the possibility of tree colinear points.
        QE_ASSERT(!vAux1.IsZero())

        // Plane equation
        *this = QPlane( vAux1.x, vAux1.y, vAux1.z, -vAux1.DotProduct(vPoint1) ).Normalize();
    }


    // PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets a plane with all components set to 0.
    /// </summary>
    /// <returns>
    /// A plane with all components set to 0.
    /// </returns>
    inline static const QPlane& GetZeroPlane()
    {
        static const QPlane ZEROPLANE(SQFloat::_0,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
        return ZEROPLANE;
    }

    /// <summary>
    /// Gets the plane that contains the Z and X axis, and its normal is in the Y axis.
    /// </summary>
    /// <returns>
    /// The plane ZX.
    /// </returns>
    inline static const QPlane& GetPlaneZX()
    {
        static const QPlane PLANEZX(SQFloat::_0,  SQFloat::_1,  SQFloat::_0,  SQFloat::_0);
        return PLANEZX;
    }

    /// <summary>
    /// Gets the plane that contains the X and Y axis, and its normal is in the Z axis.
    /// </summary>
    /// <returns>
    /// The plane XY.
    /// </returns>
    inline static const QPlane& GetPlaneXY()
    {
        static const QPlane PLANEXY(SQFloat::_0,  SQFloat::_0,  SQFloat::_1,  SQFloat::_0);
        return PLANEXY;
    }

    /// <summary>
    /// Gets the plane that contains the Y and Z axis, and its normal is in the X axis.
    /// </summary>
    /// <returns>
    /// The plane YZ.
    /// </returns>
    inline static const QPlane& GetPlaneYZ()
    {
        static const QPlane PLANEYZ(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0);
        return PLANEYZ;
    }


    // METHODS
	// ---------------
public:

    /// <summary>
    /// Product by a scalar: all coefficients are multiplied by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    QPlane operator*(const float_q &fScalar) const;

    /// <summary>
    /// Division by a scalar: all coefficients are divided by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A plane that is the result of the division.
    /// </returns>
    QPlane operator/(const float_q &fScalar) const;

    /// <summary>
    /// Multiplies resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A reference to plane result of the product.
    /// </returns>
    inline QPlane& operator*=(const float_q fScalar)
    {
        this->a *= fScalar;
        this->b *= fScalar;
        this->c *= fScalar;
        this->d *= fScalar;

        return *this;
    }

    /// <summary>
    /// Divides resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fScalar">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A reference to plane result of the division.
    /// </returns>
    inline QPlane& operator/=(const float_q &fScalar)
    {
        // Checkout to avoid division by 0
        QE_ASSERT(fScalar != SQFloat::_0)

        const float_q &DIVISOR = SQFloat::_1/fScalar;

        this->a *= DIVISOR;
        this->b *= DIVISOR;
        this->c *= DIVISOR;
        this->d *= DIVISOR;

        return *this;
    }

    //Unary operators

    /// <summary>
    /// Opposite plane: multiplies each coefficient by -1, maintaining its distance to the origin. Note that
    /// this operation does not flips the normal of the plane but also moves the plane to the opposite place 
    /// regarding the coordinate origin.
    /// </summary>
    /// <returns>
    /// A plane that is the opposite of the resident plane.
    /// </returns>
    QPlane operator-() const;

    /// <summary>
    /// Assign operator. Assigns the provided plane to the resident plane.
    /// </summary>
    /// <param name="plane">[IN] The plane to be assigned.</param>
    /// <returns>
    /// A reference to the modified plane.
    /// </returns>
    inline QPlane& operator=(const QBasePlane &plane)
    {
        QBasePlane::operator=(plane);
        return *this;
    }

    //Methods

    /// <summary>
    /// Normalizes the resident plane.<br>
    /// This implies to divide all components of plane by the length of the normal.
    /// </summary>
    /// <returns>
    /// The normalized plane.
    /// </returns>
    inline QPlane Normalize() const
    {
        // Checkout to avoid division by zero.
        QE_ASSERT(this->GetLength() != SQFloat::_0);

        float_q fInvDivisor = SQFloat::_1 / this->GetLength();

        return QPlane(this->a * fInvDivisor, this->b * fInvDivisor, this->c * fInvDivisor, this->d * fInvDivisor);
    }

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProduct(const QVector3 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProduct(const QVector4 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vectors of the resident plane and the provided one.
    /// </summary>
    /// <param name="plane">[IN] The plane which we want to calculate the dot product with.</param>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProduct(const QBasePlane &plane) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProductAngle(const QVector3 &vVector) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProductAngle(const QVector4 &vVector) const;

    /// <summary>
    /// Calculates the angle between resident and provided planes via dot product between their direction vectors.
    /// </summary>
    /// <param name="plane">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The result of the dot product.
    /// </returns>
    float_q DotProductAngle(const QBasePlane &plane) const;

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] A 3D vector which represents the point to be projected.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero).
    /// </remarks>
    /// <returns>
    /// The projected point.
    /// </returns>
    inline QBaseVector3 PointProjection(const QBaseVector3 &vPoint) const
    {
        return PointProjectionImp(vPoint);
    }

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result and shouldn't be null (zero). The W component of the
    /// returned point equals the input point one's value.
    /// </remarks>
    /// <param name="vPoint">[IN] A 4D vector which represents the point to be projected.</param>
    /// <returns>
    /// The projected point.
    /// </returns>
    inline QBaseVector4 PointProjection(const QBaseVector4 &vPoint) const
    {
        QBaseVector4 vAux = PointProjectionImp(vPoint);
        vAux.w = vPoint.w;
        return vAux;
    }

    /// <summary>
    /// Calculates if a point is contained in the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    bool Contains(const QBaseVector3 &vPoint) const;

    /// <summary>
    /// Calculates if a point is contained in the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    bool Contains(const QBaseVector4 &vPoint) const;

    /// <summary>
    /// Calculates the length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated length.
    /// </returns>
    float_q GetLength() const;

    /// <summary>
    /// Calculates the squared length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated squared length.
    /// </returns>
    float_q GetSquaredLength() const;

    /// <summary>
    /// Calculates the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// The direction vector of the plane.
    /// </returns>
    inline QVector3 GetNormal() const
    {
        return QVector3(this->a, this->b, this->c);
    }

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    float_q PointDistance(const QBaseVector3 &vPoint) const;

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    float_q PointDistance(const QBaseVector4 &vPoint) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <remarks>
    /// All planes must be normalized to obtain a correct result. Only when the three planes coincide in one single
    /// point the intersection point is calculated and One is returned. If the planes intersect but there is
    /// no common point, Infinite is returned and the intersection point is not calculated. If one of the planes does not
    /// intersect the others (because two of them coincide and the third one is parallel), then None is returned.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: None, One and Infinite.
    /// </returns>
    EQIntersections IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector3 &vIntersection) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <remarks>
    /// All planes must be normalized to obtain a correct result. Only when the three planes coincide in one single
    /// point the intersection point is calculated and One is returned. If the planes intersect but there is
    /// no common point, Infinite is returned and the intersection point is not calculated. If one of the planes does not
    /// intersect with the others (because two of them coincide and the third one is parallel), then None is returned.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists. The W component is not
    /// changed during the process.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: None, One and Infinite.
    /// </returns>
    EQIntersections IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector4 &vIntersection) const;

    /// <summary>
    /// Checks the spacial relation between resident plane and the provided plane.
    /// </summary>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident plane.</param>
    /// <returns>
    /// The space relation of the input plane regarding the resident one.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const;

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane Rotate(const QRotationMatrix3x3 &rotation) const
    {
        QVector3 vAux = this->GetNormal().Transform(rotation);

        return QPlane(vAux.x, vAux.y, vAux.z, this->d);
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane Rotate(const QQuaternion &qRotation) const
    {
        QVector3 vAux = this->GetNormal().Transform(qRotation);

        return QPlane(vAux.x, vAux.y, vAux.z, this->d);
    }

    /// <summary>
    /// Applies a scale to the resident plane.
    /// </summary>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br />
    /// The scale should not equal zero to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane Scale(const QScalingMatrix3x3 &scale) const
    {
        // None of the scale values should equal zero
        QE_ASSERT( scale.ij[0][0] != SQFloat::_0 && scale.ij[1][1] != SQFloat::_0 && scale.ij[2][2] != SQFloat::_0 );

        return QPlane(this->a / scale.ij[0][0], this->b / scale.ij[1][1], this->c / scale.ij[2][2], this->d)
               .Normalize();
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] A vector containing the scale to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br />
    /// The scale should not equal zero to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane Scale(const QBaseVector3 &vScale) const
    {
        // None of the scale values should equal zero
        QE_ASSERT( vScale.x != SQFloat::_0 && vScale.y != SQFloat::_0 && vScale.z != SQFloat::_0 );

        return QPlane(this->a / vScale.x, this->b / vScale.y, this->c / vScale.z, this->d)
               .Normalize();
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale amount to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale amount to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale amount to be applied in Z direction.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br />
    /// The scale should not equal zero to obtain a correct result.
    /// </remarks>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ) const
    {
        // None of the scale values should equal zero
        QE_ASSERT( fScaleX != SQFloat::_0 && fScaleY != SQFloat::_0 && fScaleZ != SQFloat::_0 );

        return QPlane(this->a / fScaleX, this->b / fScaleY, this->c / fScaleZ, this->d)
               .Normalize();
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the translation applied.
    /// </summary>
    /// <param name="translation">[IN] A [4x3] matrix containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    inline QPlane Translate(const QTranslationMatrix<QMatrix4x3> &translation) const
    {
        return QPlane(this->a,
                      this->b,
                      this->c,
                      this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the translation applied.
    /// </summary>
    /// <param name="translation">[IN] A [4x4] matrix containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    inline QPlane Translate(const QTranslationMatrix<QMatrix4x4> &translation) const
    {
        return QPlane(this->a,
                      this->b,
                      this->c,
                      this->d - (this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2]));
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector.<br>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    inline QPlane Translate(const QBaseVector3 &vTranslation) const
    {
        return QPlane(this->a,
                      this->b,
                      this->c,
                      this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector.<br>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the applied translation.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    inline QPlane Translate(const QBaseVector4 &vTranslation) const
    {
        return QPlane(this->a,
                      this->b,
                      this->c,
                      this->d - (this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z));
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided amounts for every axis.<br>
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according to the applied translation.
    /// </summary>
    /// <param name="fTranslationX">[IN] Translation amount to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] Translation amount to be applied in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Translation amount to be applied in Z direction.</param>
    /// <returns>
    /// The translated plane.
    /// </returns>
    inline QPlane Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ) const
    {
        return QPlane(this->a,
                      this->b,
                      this->c,
                      this->d - (this->a * fTranslationX + this->b * fTranslationY + this->c * fTranslationZ));
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane Transform(const QTransformationMatrix<QMatrix4x3> &transformation) const
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

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane Transform(const QTransformationMatrix<QMatrix4x4> &transformation) const
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

    /// <summary>
    /// Applies the transformation contained in a space conversion matrix to the resident plane.
    /// </summary>
    /// <param name="spaceConversion">[IN] A [4x4] space conversion matrix containing the transformation to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <returns>
    /// The converted plane.
    /// </returns>
    inline QPlane Transform(const QSpaceConversionMatrix &spaceConversion) const
    {
        QMatrix4x4 inverse = spaceConversion.Invert();

        // The product is implemented using the transpose of m
        return QPlane(this->a * inverse.ij[0][0] + this->b * inverse.ij[0][1] + this->c * inverse.ij[0][2] + this->d * inverse.ij[0][3],
                      this->a * inverse.ij[1][0] + this->b * inverse.ij[1][1] + this->c * inverse.ij[1][2] + this->d * inverse.ij[1][3],
                      this->a * inverse.ij[2][0] + this->b * inverse.ij[2][1] + this->c * inverse.ij[2][2] + this->d * inverse.ij[2][3],
                      this->a * inverse.ij[3][0] + this->b * inverse.ij[3][1] + this->c * inverse.ij[3][2] + this->d * inverse.ij[3][3])
                      .Normalize();
    }

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane RotateWithPivot(const QQuaternion &qRotation, const QVector3 &vPivot) const
    {
        return this->RotateWithPivotImp(qRotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane RotateWithPivot(const QQuaternion &qRotation, const QVector4 &vPivot) const
    {
        return this->RotateWithPivotImp(qRotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector3 &vPivot) const
    {
        return this->RotateWithPivotImp(rotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <returns>
    /// The rotated plane.
    /// </returns>
    inline QPlane RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector4 &vPivot) const
    {
        return this->RotateWithPivotImp(rotation, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const QBaseVector3 &vScale, const QVector3 &vPivot) const
    {
        return this->ScaleWithPivotImp(vScale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const QBaseVector3 &vScale, const QVector4 &vPivot) const
    {
        return this->ScaleWithPivotImp(vScale, vPivot);
    }

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector3 &vPivot) const
    {
        return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
    }

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector4 &vPivot) const
    {
        return this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const QScalingMatrix3x3 &scale, const QVector3 &vPivot) const
    {
        return this->ScaleWithPivotImp(scale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <returns>
    /// The scaled plane.
    /// </returns>
    inline QPlane ScaleWithPivot(const QScalingMatrix3x3 &scale, const QVector4 &vPivot) const
    {
        return this->ScaleWithPivotImp(scale, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector3 &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br />
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector4 &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector3 &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.<br />
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <returns>
    /// The transformed plane.
    /// </returns>
    inline QPlane TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector4 &vPivot) const
    {
        return this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Converts plane into a string with the following format:<br>
    /// "PL($a,$b,$c,$d)".<br>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>
    /// The string with the format specified.
    /// </returns>
    string_q ToString() const;

protected:

    // <summary>
    // Calculates the dot product between the direction vector of the resident plane and the provided vector.
    // </summary>
    // <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    template <class VectorType>
    float_q DotProductImp(const VectorType &vVector) const
    {
        return vVector.x * this->a + vVector.y * this->b + vVector.z * this->c;
    }

    // <summary>
    // Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    // </summary>
    // <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    template <class VectorType>
    float_q DotProductAngleImp(const VectorType &vVector) const
    {
        // When the length of either the plane or the vector equals zero, the calculated angle is not correct
        QE_ASSERT( SQFloat::IsNotZero(this->GetSquaredLength()) && !(SQFloat::IsZero(vVector.x) && SQFloat::IsZero(vVector.y) && SQFloat::IsZero(vVector.z)) );

        // Length of plane equals due to plane is supposed to be normalized.
        const float_q &DOT_LENGTH = sqrt_q(vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z);

        // Checkout to avoid division by zero.
        QE_ASSERT(DOT_LENGTH != SQFloat::_0)

        const float_q &DOT = this->DotProduct(vVector)/DOT_LENGTH;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(DOT) <= SQFloat::_1)

        float_q fAngle = acos_q(DOT);
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = SQAngle::RadiansToDegrees(fAngle);
        #endif

        return fAngle;
    }

    // <summary>
    // Applies the rotation contained in the provided quaternion to the resident plane
    // around the given point, that acts as pivot of rotation.
    // </summary>
    // <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    // <returns>
    // The rotated plane.
    // </returns>
    template <class VectorType>
    inline QPlane RotateWithPivotImp(const QQuaternion &qRotation, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Rotate(qRotation)
                    .Translate(vPivot);
    }

    // <summary>
    // Applies the rotation contained in the provided matrix to the resident plane
    // around the given point, that acts as pivot of rotation.
    // </summary>
    // <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    // <returns>
    // The rotated plane.
    // </returns>
    template <class VectorType>
    inline QPlane RotateWithPivotImp(const QRotationMatrix3x3 &rotation, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Rotate(rotation)
                    .Translate(vPivot);
    }

    // <summary>
    // Applies the scale contained in the provided vector to the resident plane,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    // <returns>
    // The scaled plane.
    // </returns>
    template <class VectorType>
    inline QPlane ScaleWithPivotImp(const QBaseVector3 &vScale, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Scale(vScale)
                    .Translate(vPivot);
    }

    // <summary>
    // Scales the resident plane by the provided amounts for every axis,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    // <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    // <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    // <returns>
    // The scaled plane.
    // </returns>
    template <class VectorType>
    inline QPlane ScaleWithPivotImp(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Scale(fScaleX, fScaleY, fScaleZ)
                    .Translate(vPivot);
    }

    // <summary>
    // Applies the scale contained in the provided matrix to the resident plane,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    // <returns>
    // The scaled plane.
    // </returns>
    template <class VectorType>
    inline QPlane ScaleWithPivotImp(const QScalingMatrix3x3 &scale, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Scale(scale)
                    .Translate(vPivot);
    }

    // <summary>
    // Applies the transformation contained in the provided matrix to the resident plane
    // around the given point, that acts as pivot of transformation.
    // </summary>
    // <param name="transformation">[IN] A [4x3] or [4x4] matrix containing the transformation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    // <returns>
    // The transformed plane.
    // </returns>
    template <class MatrixType, class VectorType>
    inline QPlane TransformWithPivotImp(const MatrixType &transformation, const VectorType &vPivot) const
    {
        return this->Translate(-vPivot)
                    .Transform(transformation)
                    .Translate(vPivot);
    }


    // <summary>
    // Calculates the orthogonal projection of a given point over the resident plane.
    // </summary>
    // <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    // <param name="vProjection">[OUT] A 3D vector where to store the projected point.</param>
    // <returns>
    // The projected point.
    // </returns>
    template <class VectorType>
    inline VectorType PointProjectionImp(const VectorType &vPoint) const
    {
        // The plane shouldn't be null
        QE_ASSERT( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)) );

        // [SMELL] Thund: Can this line be replaced with a dot product?
        const float_q &PROJ = -(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);

        // [SMELL] Thund: Can this line contain all the operations so no 2 constructor calls are performed?
        VectorType vProjection;
        vProjection.x = PROJ * this->a  + vPoint.x;
        vProjection.y = PROJ * this->b  + vPoint.y;
        vProjection.z = PROJ * this->c  + vPoint.z;

        return vProjection;
    }

    // <summary>
    // Calculates if a point is contained on the resident plane.
    // </summary>
    // <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    // <returns>
    // True if the point is contained, false otherwise.
    // </returns>
    template <class VectorType>
    bool ContainsImp(const VectorType &vPoint) const
    {
        // The plane should not be null
        QE_ASSERT( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)) );

        return SQFloat::IsZero(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
    }

    // <summary>
    // Calculates the minimum distance from the given point to the resident plane, which is the length
    // of the normal to the plane which passes through the point.
    // </summary>
    // <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    // <returns>
    // A floating point value which represents the minimum distance between the plane and the point.
    // </returns>
    template <class VectorType>
    float_q PointDistanceImp(const VectorType &vPoint) const
    {
        // The plane should not be null
        QE_ASSERT( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)) );

        return SQFloat::Abs(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
    }

    // <summary>
    // Calculates the number of intersections between the resident plane and two planes provided,
    // and also calculates the intersection point if there is only one.
    // </summary>
    // <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    // <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    // <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    // <returns>
    // An enumerated value which represents the number of intersections between the three planes, and can take
    // the following values: E_None, E_One and E_Infinite.
    // </returns>
    template <class VectorType>
    EQIntersections IntersectionPointImp(const QBasePlane &plane1, const QBasePlane &plane2, VectorType &vIntersection) const
    {
        // None of the planes should be null
        QE_ASSERT( !(SQFloat::IsZero(this->a) && SQFloat::IsZero(this->b) && SQFloat::IsZero(this->c)) );
        QE_ASSERT( !(SQFloat::IsZero(plane1.a) && SQFloat::IsZero(plane1.b) && SQFloat::IsZero(plane1.c)) );
        QE_ASSERT( !(SQFloat::IsZero(plane2.a) && SQFloat::IsZero(plane2.b) && SQFloat::IsZero(plane2.c)) );

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
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPLANE__
