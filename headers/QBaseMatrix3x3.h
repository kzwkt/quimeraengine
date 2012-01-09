// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX3X3__
#define __QBASEMATRIX3X3__

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
/// Base class to represent a matrix of floating point values with 3 rows and 3 columns.
/// </summary>
class QDllExport QBaseMatrix3x3 : public QConvertible
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix3x3()
	{
		ij[0][0] = ij[0][1] = ij[0][2] = SQFloat::_0;
		ij[1][0] = ij[1][1] = ij[1][2] = SQFloat::_0;
		ij[2][0] = ij[2][1] = ij[2][2] = SQFloat::_0;
	}

    /// <summary>
	/// Constructor that receives a floating point value for all elements of the matrix.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
	inline explicit QBaseMatrix3x3(const float_q &fValueAll)
	{
		ij[0][0] = ij[0][1] = ij[0][2] =
		ij[1][0] = ij[1][1] = ij[1][2] =
		ij[2][0] = ij[2][1] = ij[2][2] = fValueAll;
	}

	/// <summary>
	/// Constructor from a floating point value for each element of the matrix.
	/// </summary>
	/// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
	/// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
	/// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
	/// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
	/// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
	/// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
	/// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
	/// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
	/// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
	inline explicit QBaseMatrix3x3(const float_q &f00, const float_q &f01, const float_q &f02,
                                   const float_q &f10, const float_q &f11, const float_q &f12,
                                   const float_q &f20, const float_q &f21, const float_q &f22)
	{
		ij[0][0] = f00;
		ij[0][1] = f01;
		ij[0][2] = f02;
		ij[1][0] = f10;
		ij[1][1] = f11;
		ij[1][2] = f12;
		ij[2][0] = f20;
		ij[2][1] = f21;
		ij[2][2] = f22;
	}

	/// <summary>
	/// Constructor that receives a pointer to 9 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="arValues">[IN] Pointer to a 9 length array of floating point values.</param>
	inline explicit QBaseMatrix3x3(const float_q* arValues)
	{
		QE_ASSERT(arValues != null_q);

		ij[0][0] = arValues[0];
		ij[0][1] = arValues[1];
		ij[0][2] = arValues[2];
		ij[1][0] = arValues[3];
		ij[1][1] = arValues[4];
		ij[1][2] = arValues[5];
		ij[2][0] = arValues[6];
		ij[2][1] = arValues[7];
		ij[2][2] = arValues[8];
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
		float_q fAux;

		SQVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], fAux);
		SQVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], fAux);
		SQVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], fAux);
	}

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two [3x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseMatrix3x3 &matrix) const
    {
        return SQFloat::AreEquals(this->ij[0][0], matrix.ij[0][0]) &&
               SQFloat::AreEquals(this->ij[0][1], matrix.ij[0][1]) &&
               SQFloat::AreEquals(this->ij[0][2], matrix.ij[0][2]) &&
               SQFloat::AreEquals(this->ij[1][0], matrix.ij[1][0]) &&
               SQFloat::AreEquals(this->ij[1][1], matrix.ij[1][1]) &&
               SQFloat::AreEquals(this->ij[1][2], matrix.ij[1][2]) &&
               SQFloat::AreEquals(this->ij[2][0], matrix.ij[2][0]) &&
               SQFloat::AreEquals(this->ij[2][1], matrix.ij[2][1]) &&
               SQFloat::AreEquals(this->ij[2][2], matrix.ij[2][2]);
    }

    /// <summary>
    /// Inequality operator. Compares two [3x3] matrices.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseMatrix3x3 &matrix) const
    {
        return  !(*this == matrix);
    }

    // ATTRIBUTES
    // ---------------
public:

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
