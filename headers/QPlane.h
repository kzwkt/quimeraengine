// [TERMS&CONDITIONS]

#ifndef __QPLANE__
#define __QPLANE__

#include "EQIntersections.h"
#include "EQSpaceRelation.h"
#include "QBasePlane.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScaleMatrix3x3.h"
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
/// It represents the basic form of a 3D plane, defined by the equation \f$ ax + by + cz + d = 0\f$.
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from
/// plane to the origin, when the normal is normalized.
/// </summary>
class QDllExport QPlane : public QBasePlane
{
	// FRIENDS
	// ---------------
public:

    /// <summary>
    /// Product by a scalar: all coefficients are multiplied by the floating point value provided.
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
    friend QPlane operator*(const float_q &fScalar, const QBasePlane &plane);


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
    /// Constructor from a plane.
    /// </summary>
    /// <param name="plane">The plane on which we base the resident plane.</param>
    inline explicit QPlane(const QBasePlane &plane) : QBasePlane(plane)
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
	/// Constructor from a pointer to an array of floating point values.
	/// </summary>
	/// <param name="arValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    inline explicit QPlane(float_q* arValues) : QBasePlane(arValues)
    {
    }

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="value">[IN] 4x32 packed float containing the four components.
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
    inline explicit QPlane(const vf32_q value) : QBasePlane(value)
    {
    }

    /// <summary>
	/// Constructor from three points.
	/// </summary>
	/// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	/// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	/// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
	/// <remarks>
    /// This method produces a normalized plane.
    /// </remarks>
    inline QPlane(const QVector3 &vPoint1, const QVector3 &vPoint2, const QVector3 &vPoint3)
    {
        this->QPlaneImp(vPoint1, vPoint2, vPoint3);
    }

    /// <summary>
	/// Constructor from three points.
	/// </summary>
	/// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	/// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	/// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
	/// <remarks>
    /// This method produces a normalized plane.
    /// </remarks>
    inline QPlane(const QVector4 &vPoint1, const QVector4 &vPoint2, const QVector4 &vPoint3)
    {
        this->QPlaneImp(vPoint1, vPoint2, vPoint3);
    }

protected:

	// <summary>
	// Constructor from three points.
	// </summary>
	// <param name="vPoint1">[IN] A 3D vector which represents the first point.</param>
	// <param name="vPoint2">[IN] A 3D vector which represents the second point.</param>
	// <param name="vPoint3">[IN] A 3D vector which represents the third point.</param>
    template <class VectorType>
    inline void QPlaneImp(const VectorType &vPoint1, const VectorType &vPoint2, const VectorType &vPoint3)
    {
        // Creates two vectors, to obtain the direction vector of the plane via cross product
        VectorType vAux1(vPoint2 - vPoint1);

        vAux1.CrossProduct(vPoint3 - vPoint1);

        // Checkout to avoid the possibility of tree colineal points.
        QE_ASSERT (!vAux1.IsZero());

        // Plane equation
        *this = QBasePlane(vAux1.x, vAux1.y, vAux1.z, -(vAux1.DotProduct(vPoint1)));

        this->Normalize();
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
    inline QPlane& operator*=(const float_q &fScalar)
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
        QE_ASSERT(fScalar != SQFloat::_0);

        const float_q &fDivisor = SQFloat::_1/fScalar;

        this->a *= fDivisor;
        this->b *= fDivisor;
        this->c *= fDivisor;
        this->d *= fDivisor;

        return *this;
    }

    //Unary operators

    /// <summary>
    /// Opposite plane: multiplies each coefficient by -1, maintaining its distance to the origin.
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
    /// Normalizes the resident plane. This implies to divide all components of plane by the length of the normal.
    /// </summary>
    inline void Normalize()
    {
        float_q fDivisor = this->GetLength();

        // Checkout to avoid division by zero.
        QE_ASSERT(fDivisor != SQFloat::_0);

        fDivisor = SQFloat::_1 / fDivisor;

        *this *= fDivisor;
    }

    /// <summary>
    /// Calculates a normalized plane from the resident one, storing it in an output plane provided.
    /// This implies to divide all components of plane by the length of the normal.
    /// </summary>
    /// <param name="outPlane">[OUT] The plane where we want to store the normalized plane.</param>
    inline void Normalize(QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Normalize();
    }

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    float_q DotProduct(const QVector3 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="vVector">[IN] The vector which we want to calculate the dot product with.</param>
    float_q DotProduct(const QVector4 &vVector) const;

    /// <summary>
    /// Calculates the dot product between the direction vectors of the resident plane and the provided one.
    /// </summary>
    /// <param name="plane">[IN] The plane which we want to calculate the dot product with.</param>
    float_q DotProduct(const QBasePlane &plane) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    float_q DotProductAngle(const QVector3 &vVector) const;

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="vVector">[IN] The vector whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    float_q DotProductAngle(const QVector4 &vVector) const;

    /// <summary>
    /// Calculates the angle between resident and provided planes via dot product between their direction vectors.
    /// </summary>
    /// <param name="plane">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result.
    /// </remarks>
    float_q DotProductAngle(const QBasePlane &plane) const;

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    /// <param name="vProjection">[OUT] A 3D vector where to store the projected point.</param>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    inline void PointProjection(const QBaseVector3 &vPoint, QBaseVector3 &vProjection) const
    {
        PointProjectionImp(vPoint, vProjection);
    }

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    /// <param name="vProjection">[OUT] A 3D vector where to store the projected point.</param>
    inline void PointProjection(const QBaseVector4 &vPoint, QBaseVector4 &vProjection) const
    {
        PointProjectionImp(vPoint, vProjection);
    }

    /// <summary>
    /// Calculates if a point is contained on the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    bool Contains(const QBaseVector3 &vPoint) const;

    /// <summary>
    /// Calculates if a point is contained on the resident plane.
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
    /// <param name="vNormal">[OUT] Vector to store the direction vector.</param>
    inline void GetNormal(QBaseVector3 &vNormal) const
    {
        GetNormalImp(vNormal);
    }

    /// <summary>
    /// Calculates the direction vector of the resident plane.
    /// </summary>
    /// <param name="vNormal">[OUT] Vector to store the direction vector.</param>
    inline void GetNormal(QBaseVector4 &vNormal) const
    {
        GetNormalImp(vNormal);
    }

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="vPoint">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    float_q PointDistance(const QBaseVector3 &vPoint) const;

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <remarks>
    /// The plane must be normalized to obtain a correct result.
    /// </remarks>
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
    /// All planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: E_None, E_One and E_Infinite.
    /// </returns>
    EQIntersections IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector3 &vIntersection) const;

    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <remarks>
    /// All planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="plane1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="plane2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vIntersection">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: E_None, E_One and E_Infinite.
    /// </returns>
    EQIntersections IntersectionPoint(const QBasePlane &plane1, const QBasePlane &plane2, QBaseVector4 &vIntersection) const;

    /// <summary>
    /// Checks the relation between resident plane and the provided plane.
    /// </summary>
    /// <remarks>
    /// Both planes must be normalized to obtain a correct result.
    /// </remarks>
    /// <param name="plane">[IN] The plane we want check the relation with resident plane.</param>
    /// <returns>
    /// An enumerated value like follows: E_Contained, E_PositiveSide, E_NegativeSide.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &plane) const;

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    inline void Rotate(const QRotationMatrix3x3 &rotation)
    {
        QVector3 vAux;

        this->GetNormal(vAux);

        vAux.Transform(rotation);

        this->a = vAux.x;
        this->b = vAux.y;
        this->c = vAux.z;
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void Rotate(const QRotationMatrix3x3 &rotation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Rotate(rotation);
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    inline void Rotate(const QQuaternion &qRotation)
    {
        QVector3 vAux;

        this->GetNormal(vAux);

        vAux.Transform(qRotation);

        this->a = vAux.x;
        this->b = vAux.y;
        this->c = vAux.z;
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void Rotate(const QQuaternion &qRotation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Rotate(qRotation);
    }

    /// <summary>
    /// Applies a scale to the resident plane.
    /// </summary>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const QScaleMatrix3x3 &scale)
    {
        QE_ASSERT(scale.ij[0][0] != SQFloat::_0 && scale.ij[1][1] != SQFloat::_0 && scale.ij[2][2] != SQFloat::_0);

        this->a /= scale.ij[0][0];
        this->b /= scale.ij[1][1];
        this->c /= scale.ij[2][2];

        this->Normalize();
    }

    /// <summary>
    /// Applies a scale to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied.</param>
    /// <param name="outPlane">[OUT] The scaled plane.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const QScaleMatrix3x3 &scale, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Scale(scale);
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided vector.
    /// </summary>
    /// <param name="vScale">[IN] A vector containing the scale to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const QBaseVector3 &vScale)
    {
        QE_ASSERT(vScale.x != SQFloat::_0 && vScale.y != SQFloat::_0 && vScale.z != SQFloat::_0);

        this->a /= vScale.x;
        this->b /= vScale.y;
        this->c /= vScale.z;

        this->Normalize();
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided vector.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="vScale">[IN] A vector containing the scale to be applied.</param>
    /// <param name="outPlane">[OUT] The scaled plane.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const QBaseVector3 &vScale, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Scale(vScale);
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided amounts for every axis.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale amount to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale amount to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale amount to be applied in Z direction.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        QE_ASSERT(fScaleX != SQFloat::_0 && fScaleY != SQFloat::_0 && fScaleZ != SQFloat::_0);

        this->a /= fScaleX;
        this->b /= fScaleY;
        this->c /= fScaleZ;

        this->Normalize();
    }

    /// <summary>
    /// Applies a scale to the resident plane given by the provided amounts for every axis.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="fScaleX">[IN] The scale amount to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] The scale amount to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] The scale amount to be applied in Z direction.</param>
    /// <param name="outPlane">[OUT] The scaled plane.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Scale(fScaleX, fScaleY, fScaleZ);
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// </summary>
    /// <param name="translation">[IN] A [4x3] matrix containing the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation)
    {
        this->d -= this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2];
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="translation">[IN] A [4x3] matrix containing the translation to be applied.</param>
    /// <param name="outPlane">[OUT] The translated plane.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Translate(translation);
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// </summary>
    /// <param name="translation">[IN] A [4x4] matrix containing the translation to be applied.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation)
    {
        this->d -= this->a * translation.ij[3][0] + this->b * translation.ij[3][1] + this->c * translation.ij[3][2];
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="translation">[IN] A [4x4] matrix containing the translation to be applied.</param>
    /// <param name="outPlane">[OUT] The translated plane.</param>
    inline void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Translate(translation);
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    inline void Translate(const QBaseVector3 &vTranslation)
    {
        this->d -= this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z;
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// The resultant plane is stored in the output provided parameter.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <param name="outPlane">[OUT] The translated plane.</param>ç
    inline void Translate(const QBaseVector3 &vTranslation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Translate(vTranslation);
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    inline void Translate(const QBaseVector4 &vTranslation)
    {
        this->d -= this->a * vTranslation.x + this->b * vTranslation.y + this->c * vTranslation.z;
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided vector. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// The resultant plane is stored in the output provided parameter.
    /// </summary>
    /// <param name="vTranslation">[IN] A 3d vector containing the translation to be applied.</param>
    /// <param name="outPlane">[OUT] The translated plane.</param>ç
    inline void Translate(const QBaseVector4 &vTranslation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Translate(vTranslation);
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided amounts for every axis.
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// </summary>
    /// <param name="fTranslationX">[IN] Translation amount to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] Translation amount to be applied in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Translation amount to be applied in Z direction.</param>
    inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
    {
        this->d -= this->a * fTranslationX + this->b * fTranslationY + this->c * fTranslationZ;
    }

    /// <summary>
    /// Applies a translation to the resident plane given by the provided amounts for every axis.
    /// The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the applied translation.
    /// The resultant plane is stored in the output provided parameter.
    /// </summary>
    /// <param name="fTranslationX">[IN] Translation amount to be applied in X direction.</param>
    /// <param name="fTranslationY">[IN] Translation amount to be applied in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Translation amount to be applied in Z direction.</param>
    /// <param name="outPlane">[OUT] The translated plane.</param>ç
    inline void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Translate(fTranslationX, fTranslationY, fTranslationZ);
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation)
    {
        QMatrix4x4 mAux(transformation.ij[0][0], transformation.ij[0][1], transformation.ij[0][2], SQFloat::_0,
                        transformation.ij[1][0], transformation.ij[1][1], transformation.ij[1][2], SQFloat::_0,
                        transformation.ij[2][0], transformation.ij[2][1], transformation.ij[2][2], SQFloat::_0,
                        transformation.ij[3][0], transformation.ij[3][1], transformation.ij[3][2], SQFloat::_1);

        mAux.As< QTransformationMatrix<QMatrix4x4> >().Reverse();

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a * mAux.ij[0][0] + this->b * mAux.ij[0][1] + this->c * mAux.ij[0][2],
                        this->a * mAux.ij[1][0] + this->b * mAux.ij[1][1] + this->c * mAux.ij[1][2],
                        this->a * mAux.ij[2][0] + this->b * mAux.ij[2][1] + this->c * mAux.ij[2][2],
                        this->a * mAux.ij[3][0] + this->b * mAux.ij[3][1] + this->c * mAux.ij[3][2] + this->d);

        *this = pAux;

        this->Normalize();
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] transformation matrix.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Transform(transformation);
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation)
    {
        QTransformationMatrix<QMatrix4x4> mAux;

        transformation.Reverse(mAux);

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a * mAux.ij[0][0] + this->b * mAux.ij[0][1] + this->c * mAux.ij[0][2],
                        this->a * mAux.ij[1][0] + this->b * mAux.ij[1][1] + this->c * mAux.ij[1][2],
                        this->a * mAux.ij[2][0] + this->b * mAux.ij[2][1] + this->c * mAux.ij[2][2],
                        this->a * mAux.ij[3][0] + this->b * mAux.ij[3][1] + this->c * mAux.ij[3][2] + this->d);

        *this = pAux;

        this->Normalize();
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] transformation matrix.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Transform(transformation);
    }

    /// <summary>
    /// Applies the transformation contained in a space conversion matrix to the resident plane.
    /// </summary>
    /// <param name="spaceConversion">[IN] A [4x4] space conversion matrix containing the transformation to be applied.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Transform(const QSpaceConversionMatrix &spaceConversion)
    {
        QMatrix4x4 mAux;

        spaceConversion.As<const QMatrix4x4>().Reverse(mAux);

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a * mAux.ij[0][0] + this->b * mAux.ij[0][1] + this->c * mAux.ij[0][2] + this->d * mAux.ij[0][3],
                        this->a * mAux.ij[1][0] + this->b * mAux.ij[1][1] + this->c * mAux.ij[1][2] + this->d * mAux.ij[1][3],
                        this->a * mAux.ij[2][0] + this->b * mAux.ij[2][1] + this->c * mAux.ij[2][2] + this->d * mAux.ij[2][3],
                        this->a * mAux.ij[3][0] + this->b * mAux.ij[3][1] + this->c * mAux.ij[3][2] + this->d * mAux.ij[3][3]);

        *this = pAux;

        this->Normalize();
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="spaceConversion">[IN] A [4x4] transformation matrix.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    inline void Transform(const QSpaceConversionMatrix &spaceConversion, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().Transform(spaceConversion);
    }

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const QVector3 &vPivot)
    {
        this->RotateWithPivotImp(qRotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const QVector4 &vPivot)
    {
        this->RotateWithPivotImp(qRotation, vPivot);
    }


    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().RotateWithPivot(qRotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided quaternion to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void RotateWithPivot(const QQuaternion &qRotation, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().RotateWithPivot(qRotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector3 &vPivot)
    {
        this->RotateWithPivotImp(rotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector4 &vPivot)
    {
        this->RotateWithPivotImp(rotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().RotateWithPivot(rotation, vPivot);
    }

    /// <summary>
    /// Applies the rotation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of rotation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().RotateWithPivot(rotation, vPivot);
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
    inline void ScaleWithPivot(const QBaseVector3 &vScale, const QVector3 &vPivot)
    {
        this->ScaleWithPivotImp(vScale, vPivot);
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
    inline void ScaleWithPivot(const QBaseVector3 &vScale, const QVector4 &vPivot)
    {
        this->ScaleWithPivotImp(vScale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const QBaseVector3 &vScale, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(vScale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided vector to the resident plane,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const QBaseVector3 &vScale, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(vScale, vPivot);
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
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector3 &vPivot)
    {
        this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
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
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector4 &vPivot)
    {
        this->ScaleWithPivotImp(fScaleX, fScaleY, fScaleZ, vPivot);
    }

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot);
    }

    /// <summary>
    /// Scales the resident plane by the provided amounts for every axis,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    /// <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    /// <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(fScaleX, fScaleY, fScaleZ, vPivot);
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
    inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const QVector3 &vPivot)
    {
        this->ScaleWithPivotImp(scale, vPivot);
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
    inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const QVector4 &vPivot)
    {
        this->ScaleWithPivotImp(scale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(scale, vPivot);
    }

    /// <summary>
    /// Applies the scale contained in the provided matrix to the resident plane,
    /// acting the given point as pivot of scale.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    /// <param name="outPlane">[OUT] The rotated plane.</param>
    inline void ScaleWithPivot(const QScaleMatrix3x3 &scale, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().ScaleWithPivot(scale, vPivot);
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
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector3 &vPivot)
    {
        this->TransformWithPivotImp(transformation, vPivot);
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
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector4 &vPivot)
    {
        this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().TransformWithPivot(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().TransformWithPivot(transformation, vPivot);
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
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector3 &vPivot)
    {
        this->TransformWithPivotImp(transformation, vPivot);
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
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector4 &vPivot)
    {
        this->TransformWithPivotImp(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector3 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().TransformWithPivot(transformation, vPivot);
    }

    /// <summary>
    /// Applies the transformation contained in the provided matrix to the resident plane
    /// around the given point, that acts as pivot of transformation.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <remarks>
    /// Resultant plane is normalized after this operation.
    /// </remarks>
    /// <param name="transformation">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    /// <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    /// <param name="outPlane">[OUT] The transformed plane.</param>
    inline void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QVector4 &vPivot, QBasePlane &outPlane) const
    {
        outPlane = *this;
        outPlane.As<QPlane>().TransformWithPivot(transformation, vPivot);
    }

    /// <summary>
    /// Converts plane into a string with the following format:
    /// "PL(a, b, c, d)".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
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
        // Length of plane removed due to plane is normalized.
        const float_q &fDotLength = vVector.GetLength();

        // Checkout to avoid division by zero.
        QE_ASSERT(fDotLength != SQFloat::_0);

        const float_q &fDot = this->DotProduct(vVector)/fDotLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(SQFloat::Abs(fDot) <= SQFloat::_1);

        const float_q &fAngle = acos_q(fDot);
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = SQAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }

    // <summary>
    // Applies the rotation contained in the provided quaternion to the resident plane
    // around the given point, that acts as pivot of rotation.
    // </summary>
    // <param name="qRotation">[IN] A quaternion containing the rotation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    template <class VectorType>
    inline void RotateWithPivotImp(const QQuaternion &qRotation, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Rotate(qRotation);
        this->Translate(vPivot);
    }

    // <summary>
    // Applies the rotation contained in the provided matrix to the resident plane
    // around the given point, that acts as pivot of rotation.
    // </summary>
    // <param name="rotation">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of rotation.</param>
    template <class VectorType>
    inline void RotateWithPivotImp(const QRotationMatrix3x3 &rotation, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Rotate(rotation);
        this->Translate(vPivot);
    }

    // <summary>
    // Applies the scale contained in the provided vector to the resident plane,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="vScale">[IN] A vector containing the scale to be applied in every axis.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    template <class VectorType>
    inline void ScaleWithPivotImp(const QBaseVector3 &vScale, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Scale(vScale);
        this->Translate(vPivot);
    }

    // <summary>
    // Scales the resident plane by the provided amounts for every axis,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="fScaleX">[IN] Amount of scale to be applied in X direction.</param>
    // <param name="fScaleY">[IN] Amount of scale to be applied in Y direction.</param>
    // <param name="fScaleZ">[IN] Amount of scale to be applied in Z direction.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    template <class VectorType>
    inline void ScaleWithPivotImp(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Scale(fScaleX, fScaleY, fScaleZ);
        this->Translate(vPivot);
    }

    // <summary>
    // Applies the scale contained in the provided matrix to the resident plane,
    // acting the given point as pivot of scale.
    // </summary>
    // <param name="scale">[IN] A [3x3] matrix containing the scale to be applied in every axis.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of scale.</param>
    template <class VectorType>
    inline void ScaleWithPivotImp(const QScaleMatrix3x3 &scale, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Scale(scale);
        this->Translate(vPivot);
    }

    // <summary>
    // Applies the transformation contained in the provided matrix to the resident plane
    // around the given point, that acts as pivot of transformation.
    // </summary>
    // <param name="transformation">[IN] A [4x3] or [4x4] matrix containing the transformation to be applied.</param>
    // <param name="vPivot">[IN] The point that acts as pivot of transformation.</param>
    template <class MatrixType, class VectorType>
    inline void TransformWithPivotImp(const MatrixType &transformation, const VectorType &vPivot)
    {
        this->Translate(-vPivot);
        this->Transform(transformation);
        this->Translate(vPivot);
    }


    // <summary>
    // Calculates the orthogonal projection of a given point over the resident plane.
    // </summary>
    // <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    // <param name="vProjection">[OUT] A 3D vector where to store the projected point.</param>
    template <class VectorType>
    inline void PointProjectionImp(const VectorType &vPoint, VectorType &vProjection) const
    {
        const float_q &fProj = -(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);

        vProjection.x = fProj * this->a  + vPoint.x;
        vProjection.y = fProj * this->b  + vPoint.y;
        vProjection.z = fProj * this->c  + vPoint.z;
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
        return SQFloat::IsZero(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d);
    }

    // <summary>
    // Calculates the direction vector of the resident plane.
    // </summary>
    // <param name="vNormal">[OUT] Vector to store the direction vector.</param>
    template <class VectorType>
    inline void GetNormalImp(VectorType &vNormal) const
    {
        vNormal.x = this->a;
        vNormal.y = this->b;
        vNormal.z = this->c;
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
        // Solved by Cramer method.
        const float_q &fDetC = this->a * plane1.b * plane2.c + this->b * plane1.c * plane2.a + this->c * plane1.a * plane2.b -
                              (this->c * plane1.b * plane2.a + this->a * plane1.c * plane2.b + this->b * plane1.a * plane2.c);
        const float_q &fDetX = this->c * plane1.b * plane2.d + this->d * plane1.c * plane2.b + this->b * plane1.d * plane2.c -
                              (this->d * plane1.b * plane2.c + this->b * plane1.c * plane2.d + this->c * plane1.d * plane2.b);
        const float_q &fDetY = this->c * plane1.d * plane2.a + this->a * plane1.c * plane2.d + this->d * plane1.a * plane2.c -
                              (this->a * plane1.d * plane2.c + this->d * plane1.c * plane2.a + this->c * plane1.a * plane2.d);
        const float_q &fDetZ = this->d * plane1.b * plane2.a + this->a * plane1.d * plane2.b + this->b * plane1.a * plane2.d -
                              (this->a * plane1.b * plane2.d + this->b * plane1.d * plane2.a + this->d * plane1.a * plane2.b);

        if (!SQFloat::IsZero(fDetC)) // A range = 3, A* range = 3: Compatible system
        {
            const float_q &fInvDetC = SQFloat::_1/fDetC;

            vIntersection.x = fDetX * fInvDetC;
            vIntersection.y = fDetY * fInvDetC;
            vIntersection.z = fDetZ * fInvDetC;

            return EQIntersections::E_One;
        }
        else if (SQFloat::IsZero(fDetX) && SQFloat::IsZero(fDetY) && SQFloat::IsZero(fDetZ)) // A range < 3, A* range < 3
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
