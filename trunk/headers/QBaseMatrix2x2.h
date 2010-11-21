// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX2X2__
#define __QBASEMATRIX2X2__

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
/// Base class to represent a matrix of floating point values of 2 rows and 2 columns.
/// </summary>
class QDllExport QBaseMatrix2x2
{
	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix2x2()
	{
		m[0][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][0] = 0.0f;
		m[1][1] = 0.0f;
	}

	/// <summary>
	/// Constructor that receives a pointer to 4 floating point values.
	/// </summary>
	/// </remarks>
	/// Keeps the convention rows x columns, so each chunck of 2 elements consecutive 
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">Pointer to a 4 length array of floating point values.</param>
	inline QBaseMatrix2x2(const float_q *pfMatrix)
	{
		m[0][0] = pfMatrix[0];
		m[0][1] = pfMatrix[1];
		m[1][0] = pfMatrix[2];
		m[1][1] = pfMatrix[3];
	}

	/// <summary>
	/// Array that holds the matrix.
	/// </summary>
	float_q m[2][2];
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEMATRIX2X2__
