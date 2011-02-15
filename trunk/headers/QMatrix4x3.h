// [TERMS&CONDITIONS]

#ifndef __QMATRIX4X3__
#define __QMATRIX4X3__

#include "QBaseMatrix4x3.h"

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
/// This class implements the functionality of a matrix with 4 rows and 3 columns.
///
/// A matrix is a rectangular arrangement of numbers. The horizontal and vertical lines in a matrix 
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m x n matrix, 
/// while m and n are called its dimensions. Every element is referenced by its position in the matrix.
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted \f$ A_{ij} \f$. In this case, we will work with 4x3 matrices, 
/// therefore our matrix will be:
/// 
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02}\\ a_{10} & a_{11} & a_{12}\\ a_{20} & a_{21} & a_{22}\\ a_{30} & a_{31} & a_{32}\end{bmatrix}\f$
///
/// This allows us to compute the special case of transformatios, where 4th column has the values (0, 0, 0, 1), and
/// we can ignore it in some cases.
/// </summary>
class QDllExport QMatrix4x3 : public QBaseMatrix4x3
{
	// FRIENDS
	// ---------------
public:
	/// <summary>
	/// Multiply by scalar operator. All matrix components are multiplied by the scalar.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar term of product.</param>
	/// <param name="m">[IN] The matrix term of product.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	friend QMatrix4x3 operator*(const float_q &fScalar, const QBaseMatrix4x3 &m);

	// CONSTANTS
	// ---------------
public:

	/// <summary>
	/// Stores a matrix with all components setted to 0.
	/// </summary>
	static const QMatrix4x3 ZeroMatrix;

 	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QMatrix4x3() : QBaseMatrix4x3() { }

	/// <summary>
	/// Constructor from a 4x3 matrix.
	/// </summary>
	/// <param name="m">[IN] The 4x3 matrix in which we want the resident matrix to be based.</param>
	inline explicit QMatrix4x3(const QBaseMatrix4x3 &m) : QBaseMatrix4x3(m) { }

	/// <summary>
	/// Constructor from a floating point value which with fill all matrix's elements.
	/// </summary>
	/// <param name="fValue">[IN] The floating point value used to fill the matrix.</param>
	inline explicit QMatrix4x3(const float_q &fValue) : QBaseMatrix4x3(fValue) { }

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
	/// <param name="f30">[IN] Floating point value for element of row 3, column 0.</param>
	/// <param name="f31">[IN] Floating point value for element of row 3, column 1.</param>
	/// <param name="f32">[IN] Floating point value for element of row 3, column 2.</param>
	inline QMatrix4x3(	const float_q &f00, const float_q &f01, const float_q &f02,
						const float_q &f10, const float_q &f11, const float_q &f12,
						const float_q &f20, const float_q &f21, const float_q &f22,
						const float_q &f30, const float_q &f31, const float_q &f32) : 

						QBaseMatrix4x3(f00, f01, f02, f10, f11, f12, f20, f21, f22, f30, f31, f32) { }

	/// <summary>
	/// Constructor that receives a pointer to 12 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">[IN] Pointer to a 12 length array of floating point values.</param>
	inline explicit QMatrix4x3(const float_q *pfMatrix) : QBaseMatrix4x3(pfMatrix) { }

	/// <summary>
	/// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
	/// Last value of each 4x32 pack is ignored.
	/// </summary>
	/// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 2 unpacked in this order.</param>
	/// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 2 unpacked in this order.</param>
	/// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 2 unpacked in this order.</param>
	/// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 2 unpacked in this order.</param>
	inline QMatrix4x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) : 
		QBaseMatrix4x3(row0, row1, row2, row3) { }

	// METHODS
	// ---------------
public:

	/// <summary>
	/// Multiply by scalar operator. All matrix components are multiplied by the scalar.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to multiply by.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x3 operator*(const float_q &fScalar) const;

	/// <summary>
	/// Divides resident matrix by a floating point value.
	/// </summary>
	/// <param name="fScalar">[IN] Floating point value to be divided by.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x3 operator/(const float_q &fScalar) const;

	/// <summary>
	/// Adds a 4x3 matrix to the resident matrix.
	/// </summary>
	/// <param name="m">[IN] The matrix to be added to.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x3 operator+(const QBaseMatrix4x3 &m) const;

	/// <summary>
	/// Subtracts a QMatrix4x3 to the resident matrix.
	/// </summary>
	/// <param name="m">[IN] The matrix to be subtracted to.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x3 operator-(const QBaseMatrix4x3 &m) const;

	/// <summary>
	/// Division and assign operator. Resident matrix stores the result of the division.
	/// </summary>
	/// <param name="fScalar">[IN] The floating point value by which to divide.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x3& operator/=(const float_q &fScalar)
	{
		QE_ASSERT(fScalar != QFloat::_0);
				
		this->ij[0][0] /= fScalar;
		this->ij[0][1] /= fScalar;
		this->ij[0][2] /= fScalar;
		this->ij[1][0] /= fScalar;
		this->ij[1][1] /= fScalar;
		this->ij[1][2] /= fScalar;
		this->ij[2][0] /= fScalar;
		this->ij[2][1] /= fScalar;
		this->ij[2][2] /= fScalar;
		this->ij[3][0] /= fScalar;
		this->ij[3][1] /= fScalar;
		this->ij[3][2] /= fScalar;

		return *this;
	}

	/// <summary>
	/// Addition and assign operator. Resident matrix stores the result of the addition.
	/// </summary>
	/// <param name="m">[IN] The matrix to be added to.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x3& operator+=(const QBaseMatrix4x3 &m)
	{
		this->ij[0][0] += m.ij[0][0];
		this->ij[0][1] += m.ij[0][1];
		this->ij[0][2] += m.ij[0][2];
		this->ij[1][0] += m.ij[1][0];
		this->ij[1][1] += m.ij[1][1];
		this->ij[1][2] += m.ij[1][2];
		this->ij[2][0] += m.ij[2][0];
		this->ij[2][1] += m.ij[2][1];
		this->ij[2][2] += m.ij[2][2];
		this->ij[3][0] += m.ij[3][0];
		this->ij[3][1] += m.ij[3][1];
		this->ij[3][2] += m.ij[3][2];

		return *this;
	}

	/// <summary>
	/// Subtraction and assign operator. Resident matrix stores the result of the subtraction.
	/// </summary>
	/// <param name="m">[IN] The matrix to be subtracted to.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x3& operator-=(const QBaseMatrix4x3 &m)
	{
		this->ij[0][0] -= m.ij[0][0];
		this->ij[0][1] -= m.ij[0][1];
		this->ij[0][2] -= m.ij[0][2];
		this->ij[1][0] -= m.ij[1][0];
		this->ij[1][1] -= m.ij[1][1];
		this->ij[1][2] -= m.ij[1][2];
		this->ij[2][0] -= m.ij[2][0];
		this->ij[2][1] -= m.ij[2][1];
		this->ij[2][2] -= m.ij[2][2];
		this->ij[3][0] -= m.ij[3][0];
		this->ij[3][1] -= m.ij[3][1];
		this->ij[3][2] -= m.ij[3][2];

		return *this;
	}

	/// <summary>
	/// Equal operator. A tolerance value "Epsilon" is used to discriminate whether the matrices are equal or not.
	/// </summary>
	/// <param name="m">[IN] The matrix to compare to.</param>
	/// <returns>
	/// If matrices are equal, then it returns true. Otherwise, it returns false.
	/// </returns>
	inline bool operator==(const QBaseMatrix4x3 &m) const
	{
		return	QFloat::AreEquals(this->ij[0][0], m.ij[0][0]) && 
				QFloat::AreEquals(this->ij[0][1], m.ij[0][1]) && 
				QFloat::AreEquals(this->ij[0][2], m.ij[0][2]) &&
				QFloat::AreEquals(this->ij[1][0], m.ij[1][0]) &&
				QFloat::AreEquals(this->ij[1][1], m.ij[1][1]) &&
				QFloat::AreEquals(this->ij[1][2], m.ij[1][2]) &&
				QFloat::AreEquals(this->ij[2][0], m.ij[2][0]) &&
				QFloat::AreEquals(this->ij[2][1], m.ij[2][1]) &&
				QFloat::AreEquals(this->ij[2][2], m.ij[2][2]) &&
				QFloat::AreEquals(this->ij[3][0], m.ij[3][0]) &&
				QFloat::AreEquals(this->ij[3][1], m.ij[3][1]) &&
				QFloat::AreEquals(this->ij[3][2], m.ij[3][2]);  
	}

	/// <summary>
	/// Non-Equal operator. A tolerance value "Epsilon" is used to discriminate whether the matrices are equal or not.
	/// </summary>
	/// <param name="m">[IN] The matrix to compare to.</param>
	/// <returns>
	/// If matrices are not equal, then it returns true. Otherwise, it returns false.
	/// </returns>
	inline bool operator!=(const QBaseMatrix4x3 &m) const
	{
	    return	QFloat::AreNotEquals(this->ij[0][0], m.ij[0][0]) ||
				QFloat::AreNotEquals(this->ij[0][1], m.ij[0][1]) ||
				QFloat::AreNotEquals(this->ij[0][2], m.ij[0][2]) ||
				QFloat::AreNotEquals(this->ij[1][0], m.ij[1][0]) ||
				QFloat::AreNotEquals(this->ij[1][1], m.ij[1][1]) ||
				QFloat::AreNotEquals(this->ij[1][2], m.ij[1][2]) ||
				QFloat::AreNotEquals(this->ij[2][0], m.ij[2][0]) ||
				QFloat::AreNotEquals(this->ij[2][1], m.ij[2][1]) ||
				QFloat::AreNotEquals(this->ij[2][2], m.ij[2][2]) ||
				QFloat::AreNotEquals(this->ij[3][0], m.ij[3][0]) ||
				QFloat::AreNotEquals(this->ij[3][1], m.ij[3][1]) ||
				QFloat::AreNotEquals(this->ij[3][2], m.ij[3][2]);  
	}

	/// <summary>
	/// Resets all matrix elements to 0.
	/// </summary>
	inline void ResetToZero()
	{
		this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = 
		this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = 
		this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = 
		this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = QFloat::_0;
	}

	/// <summary>
	/// Transpose: the transpose of a matrix m x n is a matrix n x m where each row becomes a column
	/// and each column becomes a row. Every element Aij becomes Aji. It's noted A^T
 	/// </summary>
	/// <remarks>
	/// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
	/// </remarks>
	/// <param name="m">[OUT] Stores the resultant trasposed matrix.</param>

    //[TODO] jwladi: Uncomment this when QBaseMatrix3x4 is implemented.

	/*inline void Transpose(QBaseMatrix3x4 &m) const
	{
		m.ij[0][0] = this->ij[0][0];
		m.ij[0][1] = this->ij[1][0];
		m.ij[0][2] = this->ij[2][0];
        m.ij[0][3] = this->ij[3][0];

		m.ij[1][0] = this->ij[0][1];
		m.ij[1][1] = this->ij[1][1];
		m.ij[1][2] = this->ij[2][1];
		m.ij[1][3] = this->ij[3][1];

        m.ij[2][0] = this->ij[0][2];
		m.ij[2][1] = this->ij[1][2];
		m.ij[2][2] = this->ij[2][2];
        m.ij[2][3] = this->ij[3][2];
	}*/

	/// <summary>
	/// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
	/// </summary>
	/// <returns>
	/// True if all elements are 0, false otherwise.
	/// </returns>
	inline bool IsZero() const
	{
		return	QFloat::IsZero(this->ij[0][0]) &&
				QFloat::IsZero(this->ij[0][1]) &&
				QFloat::IsZero(this->ij[0][2]) &&
				QFloat::IsZero(this->ij[1][0]) &&
				QFloat::IsZero(this->ij[1][1]) &&
				QFloat::IsZero(this->ij[1][2]) &&
				QFloat::IsZero(this->ij[2][0]) &&
				QFloat::IsZero(this->ij[2][1]) &&
				QFloat::IsZero(this->ij[2][2]) &&
				QFloat::IsZero(this->ij[3][0]) &&
				QFloat::IsZero(this->ij[3][1]) &&
				QFloat::IsZero(this->ij[3][2]);  
	}

	/// <summary>
	/// Converts matrix into a string with the following format:
	/// “M4x3( 11, 12, 13 )( 21, 22, 23 )( 31, 32, 33 )( 41, 42, 43 )”.
	/// </summary>
	/// <returns>The string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("M4x3(") + QFloat::ToString(this->ij[0][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[0][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[0][2]) + QE_L(")(") +
                               QFloat::ToString(this->ij[1][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[1][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[1][2]) + QE_L(")(") +
                               QFloat::ToString(this->ij[2][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[2][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[2][2]) + QE_L(")(") +
                               QFloat::ToString(this->ij[3][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[3][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[3][2]) + QE_L(")"); 
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMATRIX4X3__

