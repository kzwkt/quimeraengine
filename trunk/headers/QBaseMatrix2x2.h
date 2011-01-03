// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX2X2__
#define __QBASEMATRIX2X2__

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
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    inline QBaseMatrix2x2( const float_q &f00, const float_q &f01, const float_q &f10, const float_q &f11) 
    {
        ij[0][0] = f00;
		ij[0][1] = f01;
		ij[1][0] = f10;
		ij[1][1] = f11;
    }

	/// <summary>
	/// Constructor that receives a pointer to 4 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 2 consecutive elements 
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

    /// <summary>
	/// Constructor from one 4x32 floating point packed values. Each value contains an element of the matrix.
    /// Each pack element is unpacked following the row x column convention.
	/// </summary>
	/// <param name="vfValues">[IN] 4x32 values for the matrix.</param>
	inline QBaseMatrix2x2(const vf32_q &vfValues)
	{
		QVF32::Unpack(vfValues, this->ij[0][0], this->ij[0][1], this->ij[1][0], this->ij[1][1]);
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
