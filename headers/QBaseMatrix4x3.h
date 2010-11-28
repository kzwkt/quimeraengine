// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX4X3__
#define __QBASEMATRIX4X3__

#include "Configuration.h"

using namespace Kinesis::QuimeraEngine::Core::Configuration;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Base class to represent a matrix of floating point values with 4 rows and 3 columns.
/// </summary>
class QDllExport QBaseMatrix4x3
{
	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix4x3()
	{
		ij[0][0] = ij[0][1] = ij[0][2] = 0.0f;
		ij[1][0] = ij[1][1] = ij[1][2] = 0.0f;
		ij[2][0] = ij[2][1] = ij[2][2] = 0.0f;
		ij[3][0] = ij[3][1] = ij[3][2] = 0.0f;
	}

	/// <summary>
	/// Constructor that receives a pointer to 12 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 3 elements consecutive 
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">Pointer to a 12 length array of floating point values.</param>
	inline QBaseMatrix4x3(const float_q *pfMatrix)
	{
		QE_ASSERT(pfMatrix != null_q);

		ij[0][0] = pfMatrix[0];
		ij[0][1] = pfMatrix[1];
		ij[0][2] = pfMatrix[2];
		ij[1][0] = pfMatrix[3];
		ij[1][1] = pfMatrix[4];
		ij[1][2] = pfMatrix[5];
		ij[2][0] = pfMatrix[6];
		ij[2][1] = pfMatrix[7];
		ij[2][2] = pfMatrix[8];
		ij[3][0] = pfMatrix[9];
		ij[3][1] = pfMatrix[10];
		ij[3][2] = pfMatrix[11];
	}

	/// <summary>
	/// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
	/// </summary>
	/// <remarks>
	/// Last component for each 4x32 value will be ignored.
	/// </remarks>
	/// <param name="row0">4x32 values for row 0.</param>
	/// <param name="row1">4x32 values for row 1.</param>
	/// <param name="row2">4x32 values for row 2.</param>
	/// <param name="row3">4x32 values for row 3.</param>
	inline QBaseMatrix4x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3)
	{
		//[TODO]
	}

	/// <summary>
	/// Array that holds the matrix.
	/// </summary>
	float_q ij[4][3];
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEMATRIX4X3__
