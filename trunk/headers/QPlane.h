// [TERMS&CONDITIONS]

#ifndef __QPLANE__
#define __QPLANE__

#include "QBasePlane.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// It represents the basic form of a 3D plane, defined by the equation ax + by + cz + d = 0. 
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

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
    QPlane() : QBasePlane() { }

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
	/// <param name="fValues">[IN] 4x32 packed float containing the four components.
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient), 
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
    inline explicit QPlane(const vf32_q fValues) : QBasePlane(fValues) { }

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
        QE_ASSERT(fValue);

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
    /// x + y + z + 1 = 0 and 2x + 2y + 2z + 2 = 0  are the same plane but its components are different.
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
    /// x + y + z + 1 = 0 and 2x + 2y + 2z + 2 = 0  are the same plane but its components are different.
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

    //Methods

    /// <summary>
    /// Normalizes the resident plane. This implies to divide all components of plane by the length of the normal.
    /// </summary>
    inline void Normalize()
    {
        // [TODO] jwladi: Would it be necessary provide a method which returns the length of the normal (float) or the unit normal (vector)?
        float_q fDivisor = sqrt(this->a * this->a + this->b * this->b + this->c * this->c);

        // Checkout to avoid division by zero.
        QE_ASSERT(fDivisor);

        fDivisor = QFloat::_1 / fDivisor;

        *this *= fDivisor;
    }

    /// <summary>
    /// Calculates a normalized plane from the resident one, storing it in an output plane provided. 
    /// This implies to divide all components of plane by the length of the normal.
    /// </summary>
    /// <param name="pOut">[OUT] The plane where we want to store the normalized plane.</param>
    inline void Normalize(QBasePlane &pOut)
    {
        pOut = *this;
        static_cast <QPlane> (pOut).Normalize();
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

	// ATTRIBUTES
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
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPLANE__
