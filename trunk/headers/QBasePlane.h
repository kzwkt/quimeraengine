// [TERMS&CONDITIONS]

#ifndef __QBASEPLANE__
#define __QBASEPLANE__

#include "SQFloat.h"
#include "QVF32.h"

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
/// It represents the basic form of a 3D plane, defined by the equation \f$ ax + by + cz + d = 0 \f$.
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from plane to the origin.
/// </summary>
class QDllExport QBasePlane
{
    // CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBasePlane() : a(SQFloat::_0), b(SQFloat::_0), c(SQFloat::_0), d(SQFloat::_0) { }

	/// <summary>
	/// Constructor from a floating point value for each coefficient.
	/// </summary>
	/// <param name="fA">[IN] Floating point value for a coefficient.</param>
	/// <param name="fB">[IN] Floating point value for b coefficient.</param>
	/// <param name="fC">[IN] Floating point value for c coefficient.</param>
	/// <param name="fD">[IN] Floating point value for independent term d.</param>
	inline QBasePlane(float_q fA, float_q fB, float_q fC, float_q fD) : a(fA), b(fB), c(fC), d(fD) { }

	/// <summary>
	/// Constructor from a floating point value for all coefficients.
	/// </summary>
	/// <param name="fValue">[IN] Floating point value.</param>
	inline explicit QBasePlane(float_q fValue) : a(fValue), b(fValue), c(fValue), d(fValue) { }

	/// <summary>
	/// Constructor from a pointer to a array of floating point values.
	/// </summary>
	/// <param name="pValue">[IN] Pointer to array of floating point values. It must have at least four elements.</param>
	inline explicit QBasePlane(float_q *pValue)
	{
		// Null pointer checkout
		QE_ASSERT(pValue != null_q);

		// Assignments
		this->a = pValue[0];
		this->b = pValue[1];
		this->c = pValue[2];
		this->d = pValue[3];
	}

	/// <summary>
	/// Constructor from a 4x32 packed float value.
	/// </summary>
	/// <param name="vfValue">[IN] 4x32 packed float containing the four components.
	/// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
	/// 3rd value (c coefficient), 4th value (d independent term).</param>
	inline explicit QBasePlane(const vf32_q vfValue)
	{
		QVF32::Unpack(vfValue, this->a, this->b, this->c, this->d);
	}

    // METHODS
    // --------------
public:

    /// <summary>
    /// Equality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be false, even if they are the same plane:
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are the same, false otherwise.
    /// </returns>
    inline bool operator == (const QBasePlane &plane) const
    {
        return ( SQFloat::AreEquals(plane.a, this->a) && SQFloat::AreEquals(plane.b, this->b) &&
                 SQFloat::AreEquals(plane.c, this->c) && SQFloat::AreEquals(plane.d, this->d) );
    }

    /// <summary>
    /// Inequality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be true, even if they are the same plane.
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBasePlane &plane) const
    {
        return !(*this == plane);
    }


	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// X coefficient of the plane equation.
	/// </summary>
	float_q a;

	/// <summary>
	/// Y coefficient of the plane equation.
	/// </summary>
	float_q b;

	/// <summary>
	/// Z coefficient of the plane equation.
	/// </summary>
	float_q c;

	/// <summary>
	/// Independent term of the plane equation.
	/// </summary>
	float_q d;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEPLANE__
