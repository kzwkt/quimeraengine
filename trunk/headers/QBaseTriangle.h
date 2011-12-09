// [TERMS&CONDITIONS]

#ifndef __QBASETRIANGLE__
#define __QBASETRIANGLE__

#include "SQFloat.h"
#include "SQVF32.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
// ----------------------
class QVector2;
class QVector3;
class QVector4;

/// <summary>
/// Class which represents a triangle in the space. The triangle may be represented in 2D or 3D,
///	and using points or vectors, depending on the parameter of the template, which may be
///	2D vector, 3D vector or 4D vector.
/// </summary>
template <class VectorType>
class QDllExport QBaseTriangle
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QBaseTriangle () : A(SQFloat::_0), B(SQFloat::_0), C(SQFloat::_0)	{ }

	/// <summary>
	/// Constructor from three vectors.
	/// </summary>
	/// <param name="vA">[IN] Vector to define vertex A.</param>
	/// <param name="vB">[IN] Vector to define vertex B.</param>
	/// <param name="vC">[IN] Vector to define vertex C.</param>
	inline QBaseTriangle (const VectorType &vA, const VectorType &vB, const VectorType &vC) : A(vA), B(vB), C(vC) { }

	/// <summary>
	/// Constructor from a pointer to floating point values to define each vertex.
	/// Pointer must have two, three or four values depending on VectorType.
	/// </summary>
	/// <param name="pValueA">[IN] Pointer to floating point value to define vertex A.</param>
	/// <param name="pValueB">[IN] Pointer to floating point value to define vertex B.</param>
	/// <param name="pValueC">[IN] Pointer to floating point value to define vertex C.</param>
	inline QBaseTriangle (const float_q *pValueA, const float_q *pValueB, const float_q *pValueC)
	{
		// Checkout to ensure pointers are not null.
		QE_ASSERT( (pValueA != null_q) && (pValueB != null_q) && (pValueC != null_q) );

		A = VectorType(pValueA);
		B = VectorType(pValueB);
		C = VectorType(pValueC);
	}

	/// <summary>
	/// Constructor from three 4x32 packed floating point values to define each vertex.
	/// </summary>
	/// <param name="vfValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="vfValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="vfValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QBaseTriangle (const vf32_q &vfValueA, const vf32_q &vfValueB, const vf32_q &vfValueC) : A(vfValueA), B(vfValueB), C(vfValueC)	{ }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two triangles.
    /// </summary>
    /// <param name="t">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are the same, false otherwise.
    /// </returns>
    inline bool operator == (const QBaseTriangle<VectorType> &t) const
    {
        return ( this->A == t.A && this->B == t.B && this->C == t.C );
    }

    /// <summary>
    /// Inequality operator. Compares two triangles.
    /// </summary>
    /// <param name="t">[IN] Triangle with which to compare.</param>
    /// <returns>
    /// True if triangles are not the same, false otherwise.
    /// </returns>
    inline bool operator != (const QBaseTriangle<VectorType> &t) const
    {
        return !(*this == t);
    }

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Vector which represents a vextex of the triangle.
	/// </summary>
	VectorType A;

	/// <summary>
	/// Vector which represents a vextex of the triangle.
	/// </summary>
	VectorType B;

	/// <summary>
	/// Vector which represents a vextex of the triangle.
	/// </summary>
	VectorType C;

};

// TYPEDEFS
// ---------------

typedef QBaseTriangle<QVector2> QBaseTriangle2;
typedef QBaseTriangle<QVector3> QBaseTriangle3;
typedef QBaseTriangle<QVector4> QBaseTriangle4;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASETRIANGLE__
