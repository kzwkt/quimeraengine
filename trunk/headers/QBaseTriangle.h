// [TERMS&CONDITIONS]

#ifndef __QBASETRIANGLE__
#define __QBASETRIANGLE_



#include "QFloat.h"
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
	inline QBaseTriangle ()
	{
		A.ResetToZero();
		B.ResetToZero();
		C.ResetToZero();
	}

	/// <summary>
	/// Constructor from three vectors.
	/// </summary>
	/// <param name="vA">[IN] Vector to define vertex A.</param>
	/// <param name="vB">[IN] Vector to define vertex B.</param>
	/// <param name="vC">[IN] Vector to define vertex C.</param>
	inline QBaseTriangle (const VectorType &vA, const VectorType &vB, const VectorType &vC)
	{
		A = vA;
		B = vB;
		C = vC;
	}

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
	/// <param name="fValueA">[IN] 4x32 packed value which defines vertex A.</param>
	/// <param name="fValueB">[IN] 4x32 packed value which defines vertex B.</param>
	/// <param name="fValueC">[IN] 4x32 packed value which defines vertex C.</param>
	inline QBaseTriangle (const vf32_q &fValueA, const vf32_q &fValueB, const &vf32_q fValueC)
	{
		A = VectorType(fValueA);
		B = VectorType(fValueB);
		C = VectorType(fValueC);
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

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASETRIANGLE__
