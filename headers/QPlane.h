// [TERMS&CONDITIONS]

#ifndef __QPLANE__
#define __QPLANE__

#include "EQIntersections.h"
#include "EQSpaceRelation.h"
#include "QBasePlane.h"
#include "QTransformationMatrix.h"
#include "QSpaceConversionMatrix.h"
#include "QTranslationMatrix.h"
#include "QVector3.h"
#include "QVector4.h"

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
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <param name="p">[IN] Plane to be multiplied.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    friend QPlane operator * (const float_q &fValue, const QBasePlane &p);

	// CONSTANTS
	// ---------------
public:
    /// <summary>
    /// Stores a plane with all components set to 0.
    /// </summary>
    static const QPlane ZeroPlane;

    /// <summary>
    /// Stores plane y = 0. This plane contains the Z and X axis, and its normal is in the Y axis.
    /// </summary>
    static const QPlane PlaneZX;

    /// <summary>
    /// Stores plane z = 0. This plane contains the X and Y axis, and its normal is in the Z axis.
    /// </summary>
    static const QPlane PlaneXY;

    /// <summary>
    /// Stores plane x = 0. This plane contains the Y and Z axis, and its normal is in the X axis.
    /// </summary>
    static const QPlane PlaneYZ;

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    QPlane() { }

    /// <summary>
    /// Constructor from a plane.
    /// </summary>
    /// <param name="p">The plane on which we base the resident plane.</param>
    inline explicit QPlane(const QBasePlane &p) : QBasePlane(p) { }

	/// <summary>
	/// Constructor from a floating point value for each coefficient.
	/// </summary>
	/// <param name="fA">[IN] Floating point value for a coefficient.</param>
	/// <param name="fB">[IN] Floating point value for b coefficient.</param>
	/// <param name="fC">[IN] Floating point value for c coefficient.</param>
	/// <param name="fD">[IN] Floating point value for independent term d.</param>
    inline QPlane(const float_q &fA, const float_q &fB, const float_q &fC, const float_q &fD) : QBasePlane(fA, fB, fC, fD) { }

    /// <summary>
	/// Constructor from a pointer to an array of floating point values.
	/// </summary>
	/// <param name="pValues">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
    inline explicit QPlane(float_q *pValues) : QBasePlane(pValues) { }

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="vfValues">[IN] 4x32 packed float containing the four components.
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
    inline explicit QPlane(const vf32_q vfValues) : QBasePlane(vfValues) { }

	/// <summary>
	/// Constructor from three points.
	/// </summary>
	/// <param name="vP1">[IN] A 3D vector which represents the first point.</param>
	/// <param name="vP2">[IN] A 3D vector which represents the second point.</param>
	/// <param name="vP3">[IN] A 3D vector which represents the third point.</param>
    template <class VectorType>
    inline QPlane (const VectorType &vP1, const VectorType &vP2, const VectorType &vP3)
    {
        // Creates two vectors, to obtain the direction vector of the plane via cross product
        VectorType vAux1(vP2 - vP1);

        vAux1.CrossProduct(vP3 - vP1);

        // Checkout to avoid the possibility of tree colineal points.
        QE_ASSERT (vAux1.IsNotZero());

        // Plane equation
        *this = QBasePlane(vAux1.x, vAux1.y, vAux1.z, -(vAux1.DotProduct(vP1)));
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
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A plane that is the result of the product.
    /// </returns>
    QPlane operator * (const float_q &fValue) const;

    /// <summary>
    /// Division by a scalar: all coefficients are divided by the floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A plane that is the result of the division.
    /// </returns>
    QPlane operator / (const float_q &fValue) const;

    /// <summary>
    /// Multiplies resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fValue">[IN] Multiplying floating point value.</param>
    /// <returns>
    /// A reference to plane result of the product.
    /// </returns>
    inline QPlane& operator *= (const float_q &fValue)
    {
        this->a *= fValue;
        this->b *= fValue;
        this->c *= fValue;
        this->d *= fValue;

        return *this;
    }

    /// <summary>
    /// Divides resident plane coefficients by a floating point value provided.
    /// </summary>
    /// <remarks>
    /// Note that it may be necessary re-normalize the plane after this operation!!
    /// </remarks>
    /// <param name="fValue">[IN] Dividing floating point value.</param>
    /// <returns>
    /// A reference to plane result of the division.
    /// </returns>
    inline QPlane& operator /= (const float_q &fValue)
    {
        // Checkout to avoid division by 0
        QE_ASSERT(fValue != QFloat::_0);

        this->a /= fValue;
        this->b /= fValue;
        this->c /= fValue;
        this->d /= fValue;

        return *this;
    }

    /// <summary>
    /// Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes is not normalized, the result may be false, even if they are the same plane:
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but its components are different.
    /// </remarks>
    /// <param name="p">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are the same, false otherwise.
    /// </returns>
    inline bool operator == (const QBasePlane &p) const
    {
        return ( QFloat::AreEquals(p.a, this->a) && QFloat::AreEquals(p.b, this->b) &&
                 QFloat::AreEquals(p.c, this->c) && QFloat::AreEquals(p.d, this->d) );
    }

    /// <summary>
    /// Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes is not normalized, the result may be true, even if they are the same plane.
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but its components are different.
    /// </remarks>
    /// <param name="p">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBasePlane &p) const
    {
        return ( QFloat::AreNotEquals(p.a, this->a) || QFloat::AreNotEquals(p.b, this->b) ||
                 QFloat::AreNotEquals(p.c, this->c) || QFloat::AreNotEquals(p.d, this->d) );
    }

    //Unary operators

    /// <summary>
    /// Opposite plane: multiplies each coefficient by -1, maintaining its distance to the origin.
    /// </summary>
    /// <returns>
    /// A plane that is the opposite of the resident plane.
    /// </returns>
    QPlane operator- () const
    {
        return QPlane(-this->a, -this->b, -this->c, this->d);
    }

    /// <summary>
    /// Assign operator. Assigns the provided plane to the resident plane.
    /// </summary>
    /// <param name="p">[IN] The plane to be assigned.</param>
    /// <returns>
    /// A reference to the modified plane.
    /// </returns>
    inline QPlane& operator=(const QBasePlane &p)
    {
        reinterpret_cast<QBasePlane&>(*this) = p;
        return *this;
    }

    //Methods

    /// <summary>
    /// Normalizes the resident plane. This implies to divide all components of plane by the length of the normal.
    /// </summary>
    inline void Normalize()
    {
        // [TODO] jwladi: Would it be necessary provide a method which returns the length of the normal (float) or the unit normal (vector)?
        float_q fDivisor = sqrt(this->a * this->a + this->b * this->b + this->c * this->c);

        // Checkout to avoid division by zero.
        QE_ASSERT(fDivisor != QFloat::_0);

        fDivisor = QFloat::_1 / fDivisor;

        *this *= fDivisor;
    }

    /// <summary>
    /// Calculates a normalized plane from the resident one, storing it in an output plane provided.
    /// This implies to divide all components of plane by the length of the normal.
    /// </summary>
    /// <param name="plOut">[OUT] The plane where we want to store the normalized plane.</param>
    inline void Normalize(QBasePlane &plOut) const
    {
        plOut = *this;
        reinterpret_cast <QPlane&> (plOut).Normalize();
    }

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="v">[IN] The vector which we want to calculate the dot product with.</param>
    inline float_q DotProduct(const QVector3 &v) const
    {
        return this->DotProductVector(v);
    }

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="v">[IN] The vector which we want to calculate the dot product with.</param>
    inline float_q DotProduct(const QVector4 &v) const
    {
        return this->DotProductVector(v);
    }

    /// <summary>
    /// Calculates the dot product between the direction vectors of the resident plane and the provided one.
    /// </summary>
    /// <param name="p">[IN] The plane which we want to calculate the dot product with.</param>
    inline float_q DotProduct(const QBasePlane &p) const
    {
        return p.a * this->a + p.b * this->b + p.c * this->c;
    }

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="v">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    inline float_q DotProductAngle(const QVector3 &v) const
    {
        return this->DotProductAngleVector(v);
    }

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="v">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    inline float_q DotProductAngle(const QVector4 &v) const
    {
        return this->DotProductAngleVector(v);
    }

    /// <summary>
    /// Calculates the angle between resident and provided planes via dot product between their direction vectors.
    /// </summary>
    /// <param name="p">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    inline float_q DotProductAngle(const QBasePlane &p) const
    {
        const float_q fDotLength = sqrt(this->GetSquaredLength() * reinterpret_cast<const QPlane&>(p).GetSquaredLength());

        // Checkout to avoid division by zero.
        QE_ASSERT(fDotLength != QFloat::_0);

        const float_q &fDot = this->DotProduct(p)/fDotLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(abs(fDot) <= QFloat::_1);

        const float_q &fAngle = acos(fDot);
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = QAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }

    /// <summary>
    /// Calculates the orthogonal projection of a given point over the resident plane.
    /// </summary>
    /// <param name="vPoint">[IN] A 3D vector which represents the point we want project.</param>
    /// <param name="vProjection">[OUT] A 3D vector where to store the projected point.</param>
    template <class VectorType>
    inline void PointProjection(const VectorType &vPoint, VectorType &vProjection) const
    {
        const float_q &fSquaredLength = this->GetSquaredLength();

        QE_ASSERT(fSquaredLength != QFloat::_0);

        const float_q &fProj = -(this->a * vPoint.x + this->b * vPoint.y + this->c * vPoint.z + this->d) / fSquaredLength;

        vProjection.x = fProj * this->a  + vPoint.x;
        vProjection.y = fProj * this->b  + vPoint.y;
        vProjection.z = fProj * this->c  + vPoint.z;
    }

    /// <summary>
    /// Calculates if a point is contained on the resident plane.
    /// </summary>
    /// <param name="v">[IN] The point we want know if it is contained on the resident plane.</param>
    /// <returns>
    /// True if the point is contained, false otherwise.
    /// </returns>
    template <class VectorType>
    inline bool Contains(const VectorType &v) const
    {
        return QFloat::IsZero(this->a * v.x + this->b * v.y + this->c * v.z + this->d);
    }

    /// <summary>
    /// Calculates the length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated length.
    /// </returns>
    inline float_q GetLength() const
    {
        return sqrt(this->a * this->a + this->b * this->b + this->c * this->c);
    }

    /// <summary>
    /// Calculates the squared length of the direction vector of the resident plane.
    /// </summary>
    /// <returns>
    /// A floating point value representing the value of the calculated squared length.
    /// </returns>
    inline float_q GetSquaredLength() const
    {
        return this->a * this->a + this->b * this->b + this->c * this->c;
    }

    /// <summary>
    /// Calculates the direction vector of the resident plane.
    /// </summary>
    /// <param name="vOut">[OUT] Vector to store the direction vector.</param>
    template <class VectorType>
    inline void GetNormal(VectorType &vOut) const
    {
        vOut.x = this->a;
        vOut.y = this->b;
        vOut.z = this->c;
    }

    /// <summary>
    /// Calculates the minimum distance from the given point to the resident plane, which is the length
    /// of the normal to the plane which passes through the point.
    /// </summary>
    /// <param name="v">[IN] The point we want know it distance from resident plane.</param>
    /// <returns>
    /// A floating point value which represents the minimum distance between the plane and the point.
    /// </returns>
    template <class VectorType>
    inline float_q PointDistance(const VectorType &v) const
    {
        const float_q &fLength = this->GetLength();

        QE_ASSERT(fLength != QFloat::_0);

        return abs(this->a * v.x + this->b * v.y + this->c * v.z + this->d)/fLength;
    }


    /// <summary>
    /// Calculates the number of intersections between the resident plane and two planes provided,
    /// and also calculates the intersection point if there is only one.
    /// </summary>
    /// <param name="pl1">[IN] The first plane we want to calculate the intersection with.</param>
    /// <param name="pl2">[IN] The second plane we want to calculate the intersection with.</param>
    /// <param name="vOut">[OUT] The intersection point of the three planes, if it exists.</param>
    /// <returns>
    /// An enumerated value which represents the number of intersections between the three planes, and can take
    /// the following values: E_None, E_One and E_Infinite.
    /// </returns>
    template <class VectorType>
    EQIntersections IntersectionPoint (const QBasePlane &pl1, const QBasePlane &pl2, VectorType &vOut) const
    {
        // Solved by Cramer method.
        const float_q &fDetC = this->a*pl1.b*pl2.c + this->b*pl1.c*pl2.a + this->c*pl1.a*pl2.b -
                              (this->c*pl1.b*pl2.a + this->a*pl1.c*pl2.b + this->b*pl1.a*pl2.c);

        const float_q &fDetX = this->c*pl1.b*pl2.d + this->d*pl1.c*pl2.b + this->b*pl1.d*pl2.c -
                              (this->d*pl1.b*pl2.c + this->b*pl1.c*pl2.d + this->c*pl1.d*pl2.b);
        const float_q &fDetY = this->c*pl1.d*pl2.a + this->a*pl1.c*pl2.d + this->d*pl1.a*pl2.c -
                              (this->a*pl1.d*pl2.c + this->d*pl1.c*pl2.a + this->c*pl1.a*pl2.d);
        const float_q &fDetZ = this->d*pl1.b*pl2.a + this->a*pl1.d*pl2.b + this->b*pl1.a*pl2.d -
                              (this->a*pl1.b*pl2.d + this->b*pl1.d*pl2.a + this->d*pl1.a*pl2.b);

        // A range = 3, A* range = 3: Compatible system
        if (!QFloat::IsZero(fDetC))
        {
            const float_q &fInvDetC = QFloat::_1/fDetC;

            vOut.x = fDetX * fInvDetC;
            vOut.y = fDetY * fInvDetC;
            vOut.z = fDetZ * fInvDetC;

            return EQIntersections::E_One;
        }
        // A range < 3, A* range < 3
        else if (QFloat::IsZero(fDetX) && QFloat::IsZero(fDetY) && QFloat::IsZero(fDetZ))
        {
            // A range = 2, A* range < 3: Undetermined compatible system
            if (QFloat::IsNotZero(this->a*pl1.b - this->b*pl1.a) ||
                QFloat::IsNotZero(this->a*pl1.c - this->c*pl1.a) ||
                QFloat::IsNotZero(this->a*pl2.b - this->b*pl2.a) ||
                QFloat::IsNotZero(this->a*pl2.c - this->c*pl2.a) ||
                QFloat::IsNotZero(this->b*pl1.c - this->c*pl1.b) ||
                QFloat::IsNotZero(this->b*pl2.c - this->c*pl2.b) ||
                QFloat::IsNotZero(pl1.a*pl2.b - pl1.b*pl2.a) ||
                QFloat::IsNotZero(pl1.a*pl2.c - pl1.c*pl2.a) ||
                QFloat::IsNotZero(pl1.b*pl2.c - pl1.c*pl2.b))

                return EQIntersections::E_Infinite;

            //// A range = 1, A* range < 3
            else
            {
                QPlane plAux1(*this), plAux2(pl1), plAux3(pl2);
                plAux1.Normalize();
                plAux2.Normalize();
                plAux3.Normalize();

                // Coincident planes (A* range = 1)
                if (plAux1 == plAux2 && plAux1 == plAux3)

                    return EQIntersections::E_Infinite;

                // Incompatible system (A* range = 2)
                else
                    return EQIntersections::E_None;
            }
        }
        // A range < 3, A* range = 3: Incompatible system
        else
           return EQIntersections::E_None;
    }

    /// <summary>
    /// Checks the relation between resident plane and the provided plane.
    /// </summary>
    /// <param name="p">[IN] The plane we want check the relation with resident plane.</param>
    /// <returns>
    /// An enumerated value like follows: E_Contained, E_PositiveSide, E_NegativeSide.
    /// </returns>
    EQSpaceRelation SpaceRelation(const QBasePlane &p) const;

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="m">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    inline void Transform(const QRotationMatrix3x3 &m)
    {
        QVector3 vAux;

        this->GetNormal(vAux);

        vAux.Transform(m);

        this->a = vAux.x;
        this->b = vAux.y;
        this->c = vAux.z;
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [3x3] matrix containing the rotation to be applied.</param>
    /// <param name="pOut">[OUT] The rotated plane.</param>
    inline void Transform(const QRotationMatrix3x3 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a scale to the resident plane. The direction vector may become denormalized.
    /// </summary>
    /// <param name="m">[IN] A [3x3] matrix containing the scale to be applied.</param>
    inline void Transform(const QScaleMatrix3x3 &m)
    {
        QE_ASSERT(m.ij[0][0] != QFloat::_0 && m.ij[1][1] != QFloat::_0 && m.ij[2][2] != QFloat::_0);

        this->a /= m.ij[0][0];
        this->b /= m.ij[1][1];
        this->c /= m.ij[2][2];
    }

    /// <summary>
    /// Applies a scale to the resident plane. The direction vector may become denormalized.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [3x3] matrix containing the scale to be applied.</param>
    /// <param name="pOut">[OUT] The scaled plane.</param>
    inline void Transform(const QScaleMatrix3x3 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// </summary>
    /// <param name="m">[IN] A [4x3] matrix containing the translation to be applied.</param>
    inline void Transform(const QTranslationMatrix4x3 &m)
    {
        this->d -= this->a*m.ij[3][0] + this->b*m.ij[3][1] + this->c*m.ij[3][2];
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [4x3] matrix containing the translation to be applied.</param>
    /// <param name="pOut">[OUT] The translated plane.</param>
    inline void Transform(const QTranslationMatrix4x3 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// </summary>
    /// <param name="m">[IN] A [4x4] matrix containing the translation to be applied.</param>
    inline void Transform(const QTranslationMatrix4x4 &m)
    {
        this->d -= this->a*m.ij[3][0] + this->b*m.ij[3][1] + this->c*m.ij[3][2];
    }

    /// <summary>
    /// Applies a translation to the resident plane. The normal vector to the plane remains unchanged,
    /// but the distance from the plane to the origin is modified according with the translation applied.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [4x4] matrix containing the translation to be applied.</param>
    /// <param name="pOut">[OUT] The translated plane.</param>
    inline void Transform(const QTranslationMatrix4x4 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <param name="m">[IN] A [4x3] matrix containing the transformation to be applied.</param>
    inline void Transform(const QTransformationMatrix4x3 &m)
    {
        QMatrix4x4 mAux(m.ij[0][0], m.ij[0][1], m.ij[0][2], QFloat::_0,
                        m.ij[1][0], m.ij[1][1], m.ij[1][2], QFloat::_0,
                        m.ij[2][0], m.ij[2][1], m.ij[2][2], QFloat::_0,
                        m.ij[3][0], m.ij[3][1], m.ij[3][2], QFloat::_1);

        reinterpret_cast <QTransformationMatrix4x4 &>(mAux).Reverse();

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a*mAux.ij[0][0] + this->b*mAux.ij[0][1] + this->c*mAux.ij[0][2],
                        this->a*mAux.ij[1][0] + this->b*mAux.ij[1][1] + this->c*mAux.ij[1][2],
                        this->a*mAux.ij[2][0] + this->b*mAux.ij[2][1] + this->c*mAux.ij[2][2],
                        this->a*mAux.ij[3][0] + this->b*mAux.ij[3][1] + this->c*mAux.ij[3][2] + this->d);

        *this = pAux;
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [4x3] transformation matrix.</param>
    /// <param name="pOut">[OUT] The transformed plane.</param>
    inline void Transform(const QTransformationMatrix4x3 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// </summary>
    /// <param name="m">[IN] A [4x4] matrix containing the transformation to be applied.</param>
    inline void Transform(const QTransformationMatrix4x4 &m)
    {
        QTransformationMatrix4x4 mAux;

        m.Reverse(mAux);

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a*mAux.ij[0][0] + this->b*mAux.ij[0][1] + this->c*mAux.ij[0][2],
                        this->a*mAux.ij[1][0] + this->b*mAux.ij[1][1] + this->c*mAux.ij[1][2],
                        this->a*mAux.ij[2][0] + this->b*mAux.ij[2][1] + this->c*mAux.ij[2][2],
                        this->a*mAux.ij[3][0] + this->b*mAux.ij[3][1] + this->c*mAux.ij[3][2] + this->d);

        *this = pAux;
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [4x3] transformation matrix.</param>
    /// <param name="pOut">[OUT] The transformed plane.</param>
    inline void Transform(const QTransformationMatrix4x4 &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies the transformation contained in a space conversion matrix to the resident plane.
    /// </summary>
    /// <param name="m">[IN] A [4x4] space conversion matrix containing the transformation to be applied.</param>
    inline void Transform(const QSpaceConversionMatrix &m)
    {
        QMatrix4x4 mAux;

        reinterpret_cast<const QMatrix4x4 &>(m).Reverse(mAux);

        // The product is implemented using the transpose of m
        QBasePlane pAux(this->a*mAux.ij[0][0] + this->b*mAux.ij[0][1] + this->c*mAux.ij[0][2] + this->d*mAux.ij[0][3],
                        this->a*mAux.ij[1][0] + this->b*mAux.ij[1][1] + this->c*mAux.ij[1][2] + this->d*mAux.ij[1][3],
                        this->a*mAux.ij[2][0] + this->b*mAux.ij[2][1] + this->c*mAux.ij[2][2] + this->d*mAux.ij[2][3],
                        this->a*mAux.ij[3][0] + this->b*mAux.ij[3][1] + this->c*mAux.ij[3][2] + this->d*mAux.ij[3][3]);

        *this = pAux;
    }

    /// <summary>
    /// Applies a transformation to the resident plane.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="m">[IN] A [4x4] transformation matrix.</param>
    /// <param name="pOut">[OUT] The transformed plane.</param>
    inline void Transform(const QSpaceConversionMatrix &m, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(m);
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// </summary>
    /// <param name="q">[IN] A quaternion containing the rotation to be applied.</param>
    inline void Transform(const QQuaternion &q)
    {
        QVector3 vAux;

        this->GetNormal(vAux);

        vAux.Transform(q);

        this->a = vAux.x;
        this->b = vAux.y;
        this->c = vAux.z;
    }

    /// <summary>
    /// Applies a rotation to the resident plane. The normal vector to the plane is rotated,
    /// remaining unchanged the distance from the plane to the origin.
    /// The resultant plane is stored in the output parameter provided.
    /// </summary>
    /// <param name="q">[IN] A quaternion containing the rotation to be applied.</param>
    /// <param name="pOut">[OUT] The rotated plane.</param>
    inline void Transform(const QQuaternion &q, QBasePlane &pOut) const
    {
        pOut = *this;
        reinterpret_cast<QPlane &>(pOut).Transform(q);
    }

    /// <summary>
    /// Converts plane into a string with the following format:
    /// "PL(a, b, c, d)".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("PL(") + QFloat::ToString(this->a) + QE_L(", ") + QFloat::ToString(this->b) +
               QE_L(", ")  + QFloat::ToString(this->c) + QE_L(", ") + QFloat::ToString(this->d) + QE_L(")");
    }

protected:

    /// <summary>
    /// Calculates the dot product between the direction vector of the resident plane and the provided vector.
    /// </summary>
    /// <param name="v">[IN] The vector which we want to calculate the dot product with.</param>
    template <class VectorType>
    inline float_q DotProductVector(const VectorType &v) const
    {
        return v.x * this->a + v.y * this->b + v.z * this->c;
    }

    /// <summary>
    /// Calculates the angle between the direction vector of the resident plane and the provided vector via dot product.
    /// </summary>
    /// <param name="v">[IN] The plane whose angle with the resident plane we want to calculate.</param>
    template <class VectorType>
    inline float_q DotProductAngleVector(const VectorType &v) const
    {
        const float_q &fDotLength = sqrt(this->GetSquaredLength() * v.GetSquaredLength());

        // Checkout to avoid division by zero.
        QE_ASSERT(fDotLength != QFloat::_0);

        const float_q &fDot = this->DotProduct(v)/fDotLength;

        // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
        QE_ASSERT(abs(fDot) <= QFloat::_1);

        const float_q &fAngle = acos(fDot);
        #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
            // If angles are specified in degrees, then converts angle to degrees
            fAngle = QAngle::RadiansToDegrees(fAngle, fAngle);
        #endif

        return fAngle;
    }
};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPLANE__
