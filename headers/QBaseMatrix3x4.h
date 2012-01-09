// [TERMS&CONDITIONS]

#ifndef __QBASEMATRIX3X4__
#define __QBASEMATRIX3X4__

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
/// Base class to represent a matrix of floating point values with 3 rows and 4 columns.
/// </summary>
class QDllExport QBaseMatrix3x4 : public QConvertible
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. Initializes each element in the matrix to 0.
	/// </summary>
	inline QBaseMatrix3x4()
	{
		ij[0][0] = ij[0][1] = ij[0][2] = ij[0][3] =
		ij[1][0] = ij[1][1] = ij[1][2] = ij[1][3] =
		ij[2][0] = ij[2][1] = ij[2][2] = ij[2][3] = SQFloat::_0;
	}

	/// <summary>
	/// Constructor that receives a floating point value for all elements of the matrix.
	/// </summary>
	/// <param name="fValueAll">[IN] Floating point value which to fill the matrix with.</param>
	inline explicit QBaseMatrix3x4(const float_q &fValueAll)
	{
		ij[0][0] = ij[0][1] = ij[0][2] = ij[0][3] =
		ij[1][0] = ij[1][1] = ij[1][2] = ij[1][3] =
		ij[2][0] = ij[2][1] = ij[2][2] = ij[2][3] = fValueAll;
	}

	/// <summary>
	/// Constructor from a floating point value for each element of the matrix.
	/// </summary>
	/// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
	/// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
	/// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
	/// <param name="f03">[IN] Floating point value for element of row 0, column 3.</param>
	/// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
	/// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
	/// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
	/// <param name="f13">[IN] Floating point value for element of row 1, column 3.</param>
	/// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
	/// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
	/// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
	/// <param name="f23">[IN] Floating point value for element of row 2, column 3.</param>
	inline explicit QBaseMatrix3x4(	const float_q &f00, const float_q &f01, const float_q &f02, const float_q &f03,
									const float_q &f10, const float_q &f11, const float_q &f12, const float_q &f13,
									const float_q &f20, const float_q &f21, const float_q &f22, const float_q &f23)
	{
		ij[0][0] = f00;
		ij[0][1] = f01;
		ij[0][2] = f02;
		ij[0][3] = f03;
		ij[1][0] = f10;
		ij[1][1] = f11;
		ij[1][2] = f12;
		ij[1][3] = f13;
		ij[2][0] = f20;
		ij[2][1] = f21;
		ij[2][2] = f22;
		ij[2][3] = f23;
	}

	/// <summary>
	/// Constructor that receives a pointer to 12 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 4 consecutive elements
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="arValues">[IN] Pointer to a 12 length array of floating point values.</param>
	inline QBaseMatrix3x4(const float_q* arValues)
	{
		QE_ASSERT(arValues != null_q);

		ij[0][0] = arValues[0];
		ij[0][1] = arValues[1];
		ij[0][2] = arValues[2];
		ij[0][3] = arValues[3];
		ij[1][0] = arValues[4];
		ij[1][1] = arValues[5];
		ij[1][2] = arValues[6];
		ij[1][3] = arValues[7];
		ij[2][0] = arValues[8];
		ij[2][1] = arValues[9];
		ij[2][2] = arValues[10];
		ij[2][3] = arValues[11];
	}

	/// <summary>
	/// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
	/// </summary>
	/// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3, parsed in this order.</param>
	/// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3, parsed in this order.</param>
	/// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3, parsed in this order.</param>
	inline QBaseMatrix3x4(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2)
	{

		SQVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], this->ij[0][3]);
		SQVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], this->ij[1][3]);
		SQVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], this->ij[2][3]);
	}

	// METHODS
	// ---------------
public:

    /// <summary>
	/// Equality operator. Compares two [3x4] matrices.
	/// </summary>
	/// <param name="matrix">[IN] The matrix to compare to.</param>
	/// <returns>
	/// If matrices are equals, then it returns true. Otherwise, it returns false.
	/// </returns>
	inline bool operator==(const QBaseMatrix3x4 &matrix) const
	{
		return	SQFloat::AreEquals(this->ij[0][0], matrix.ij[0][0]) &&
				SQFloat::AreEquals(this->ij[0][1], matrix.ij[0][1]) &&
				SQFloat::AreEquals(this->ij[0][2], matrix.ij[0][2]) &&
				SQFloat::AreEquals(this->ij[0][3], matrix.ij[0][3]) &&
				SQFloat::AreEquals(this->ij[1][0], matrix.ij[1][0]) &&
				SQFloat::AreEquals(this->ij[1][1], matrix.ij[1][1]) &&
				SQFloat::AreEquals(this->ij[1][2], matrix.ij[1][2]) &&
				SQFloat::AreEquals(this->ij[1][3], matrix.ij[1][3]) &&
				SQFloat::AreEquals(this->ij[2][0], matrix.ij[2][0]) &&
				SQFloat::AreEquals(this->ij[2][1], matrix.ij[2][1]) &&
				SQFloat::AreEquals(this->ij[2][2], matrix.ij[2][2]) &&
				SQFloat::AreEquals(this->ij[2][3], matrix.ij[2][3]);
	}

	/// <summary>
	/// Inequality operator. Compares two [3x4] matrices.
	/// </summary>
	/// <param name="matrix">[IN] The matrix to compare to.</param>
	/// <returns>
	/// If matrices are not equals, then it returns true. Otherwise, it returns false.
	/// </returns>
	inline bool operator!=(const QBaseMatrix3x4 &matrix) const
	{
	    return !(*this == matrix);
	}

	// ATTRIBUTES
	// ---------------
public:

	/// <summary>
	/// Array that holds the matrix.
	/// </summary>
	float_q ij[3][4];
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEMATRIX3X4__
