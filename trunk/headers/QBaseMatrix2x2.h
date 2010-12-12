// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX2X2__
#define __QBASEMATRIX2X2__

#include "QFloat.h"

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
/// Base class to represent a matrix of floating point values of 2 rows and 2 columns.
/// </summary>
class QDllExport QBaseMatrix2x2
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix2x2()
	{
		ij[0][0] = QFloat::_0;
		ij[0][1] = QFloat::_0;
		ij[1][0] = QFloat::_0;
		ij[1][1] = QFloat::_0;
	}

	/// <summary>
	/// Constructor that receives a pointer to 4 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 2 elements consecutive 
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">Pointer to a 4 length array of floating point values.</param>
	inline QBaseMatrix2x2(const float_q *pfMatrix)
	{
		QE_ASSERT(pfMatrix != null_q);

		ij[0][0] = pfMatrix[0];
		ij[0][1] = pfMatrix[1];
		ij[1][0] = pfMatrix[2];
		ij[1][1] = pfMatrix[3];
	}

    // ATTRIBUTES
    // ---------------

	/// <summary>
	/// Array that holds the matrix.
	/// </summary>
	float_q ij[2][2];
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEMATRIX2X2__
