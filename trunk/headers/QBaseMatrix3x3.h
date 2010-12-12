// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX3X3__
#define __QBASEMATRIX3X3__

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
/// Base class to represent a matrix of floating point values with 3 rows and 3 columns.
/// </summary>
class QDllExport QBaseMatrix3x3
{
	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix3x3()
	{
		ij[0][0] = ij[0][1] = ij[0][2] = QFloat::_0;
		ij[1][0] = ij[1][1] = ij[1][2] = QFloat::_0;
		ij[2][0] = ij[2][1] = ij[2][2] = QFloat::_0;
	}

	/// <summary>
	/// Constructor that receives a pointer to 9 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 3 elements consecutive 
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">[IN] Pointer to a 9 length array of floating point values.</param>
	inline explicit QBaseMatrix3x3(const float_q *pfMatrix)
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
	}

	/// <summary>
	/// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
	/// </summary>
	/// <remarks>
	/// Last component for each 4x32 value will be ignored.
	/// </remarks>
	/// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 2, parsed in this order.</param>
	/// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 2, parsed in this order.</param>
	/// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 2, parsed in this order.</param>
	inline QBaseMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2)
	{
		float_q aux;

		QVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], aux);
		QVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], aux);
		QVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], aux);
	}

	/// <summary>
	/// Array that holds the matrix.
	/// </summary>
	float_q ij[3][3];
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEMATRIX3X3__
