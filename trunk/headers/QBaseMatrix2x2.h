// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX2X2__
#define __QBASEMATRIX2X2__

#include <memory>

#include "SQFloat.h"
#include "SQVF32.h"
#include "QConvertible.h"

using Kinesis::QuimeraEngine::Core::QConvertible;
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
class QDllExport QBaseMatrix2x2 : public QConvertible
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix2x2()
	{
		ij[0][0] = SQFloat::_0;
		ij[0][1] = SQFloat::_0;
		ij[1][0] = SQFloat::_0;
		ij[1][1] = SQFloat::_0;
	}

	/// <summary>
	/// Copy constructor. Copies attributes from given matrix.
	/// </summary>
	/// <param name="matrix">[IN] The 2x2 matrix from which we want to create a copy in the resident matrix.</param>
	inline QBaseMatrix2x2(const QBaseMatrix2x2 &matrix)
	{
        memcpy(this->ij, matrix.ij, sizeof(float_q) * 4);
	}

	/// <summary>
	/// Constructor that receives a floating point value for all elements of the matrix.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
	inline explicit QBaseMatrix2x2(const float_q &fValueAll)
	{
		ij[0][0] = ij[0][1] =
		ij[1][0] = ij[1][1] = fValueAll;
	}

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    inline QBaseMatrix2x2(const float_q &f00, const float_q &f01, const float_q &f10, const float_q &f11)
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
	/// <param name="arValues">Pointer to a 4 length array of floating point values.</param>
	inline QBaseMatrix2x2(const float_q* arValues)
	{
		QE_ASSERT(arValues != null_q)

		ij[0][0] = arValues[0];
		ij[0][1] = arValues[1];
		ij[1][0] = arValues[2];
		ij[1][1] = arValues[3];
	}

    /// <summary>
	/// Constructor from one 4x32 floating point packed values. Each value contains an element of the matrix.<br>
    /// Each pack element is unpacked following the row x column convention.
	/// </summary>
	/// <param name="value">[IN] 4x32 values for the matrix.</param>
	inline QBaseMatrix2x2(const vf32_q &value)
	{
		SQVF32::Unpack(value, this->ij[0][0], this->ij[0][1], this->ij[1][0], this->ij[1][1]);
	}


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two [2x2] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseMatrix2x2 &matrix) const
    {
        return SQFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
               SQFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
               SQFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
               SQFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]);
    }

    /// <summary>
    /// Inequality operator. Compares two [2x2] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseMatrix2x2 &matrix) const
    {
        return  !(*this == matrix);
    }

    // ATTRIBUTES
    // ---------------
public:

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
