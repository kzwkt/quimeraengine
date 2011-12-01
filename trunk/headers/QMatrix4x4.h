// [TERMS&CONDITIONS]

#ifndef __QMATRIX4X4__
#define __QMATRIX4X4__

#include "QBaseMatrix4x4.h"
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
/// This class implements the functionality of a matrix with 4 rows and 4 columns.
///
/// A matrix is a rectangular arrangement of numbers. The horizontal and vertical lines in a matrix
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m × n matrix,
/// while m and n are called its dimensions. Every element is referenced by its position in the matrix.
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted A_ij. In this case, we will work with 4x4 matrices,
/// therefore our matrix will be:
///
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02} & a_{03}\\ a_{10} & a_{11} & a_{12} & a_{13}\\ a_{20} & a_{21} & a_{22} & a_{23}\\ a_{30} & a_{31} & a_{32} & a_{33}\end{bmatrix}\f$
///
/// </summary>
class QDllExport QMatrix4x4 : public QBaseMatrix4x4
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
	friend QMatrix4x4 operator*(const float_q &fScalar, const QBaseMatrix4x4 &m);

	// CONSTANTS
	// ---------------
public:

	/// <summary>
	/// Stores a matrix with all components set to 0.
	/// </summary>
	static const QMatrix4x4 ZeroMatrix;

	/// <summary>
	/// Stores an identity matrix.
	/// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$
    ///
	/// </summary>
	static const QMatrix4x4 Identity;

 	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QMatrix4x4() { }

	/// <summary>
	/// Constructor from a 4x4 matrix.
	/// </summary>
	/// <param name="m">[IN] The 4x4 matrix in which we want the resident matrix to be based.</param>
	inline explicit QMatrix4x4(const QBaseMatrix4x4 &m) : QBaseMatrix4x4(m) { }

	/// <summary>
	/// Constructor from a floating point value which with fill all matrix's elements.
	/// </summary>
	/// <param name="fValue">[IN] The floating point value used to fill the matrix.</param>
	inline explicit QMatrix4x4(const float_q &fValue) : QBaseMatrix4x4(fValue) { }

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
	/// <param name="f30">[IN] Floating point value for element of row 3, column 0.</param>
	/// <param name="f31">[IN] Floating point value for element of row 3, column 1.</param>
	/// <param name="f32">[IN] Floating point value for element of row 3, column 2.</param>
	/// <param name="f33">[IN] Floating point value for element of row 3, column 3.</param>
	inline QMatrix4x4(	const float_q &f00, const float_q &f01, const float_q &f02, const float_q &f03,
						const float_q &f10, const float_q &f11, const float_q &f12, const float_q &f13,
						const float_q &f20, const float_q &f21, const float_q &f22, const float_q &f23,
						const float_q &f30, const float_q &f31, const float_q &f32, const float_q &f33) :

						QBaseMatrix4x4(f00, f01, f02, f03, f10, f11, f12, f13, f20, f21, f22, f23, f30, f31, f32, f33) { }

	/// <summary>
	/// Constructor that receives a pointer to 16 floating point values.
	/// </summary>
	/// <remarks>
	/// Keeps the convention rows x columns, so each chunck of 4 consecutive elements
	/// corresponds to a row, where each element in the chunck is the column in the row.
	/// </remarks>
	/// <param name="pfMatrix">[IN] Pointer to a 16 length array of floating point values.</param>
	inline explicit QMatrix4x4(const float_q *pfMatrix) : QBaseMatrix4x4(pfMatrix) { }

	/// <summary>
	/// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
	/// </summary>
	/// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
	/// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
	/// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
	/// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 3 unpacked in this order.</param>
	inline QMatrix4x4(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) :
		QBaseMatrix4x4(row0, row1, row2, row3) { }

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
	QMatrix4x4 operator*(const float_q &fScalar) const;

	/// <summary>
	/// Multiplies a QMatrix4x4 by the current matrix.
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.
    /// So, left matrix must have same number of columns than rows have right matrix.
	/// The product is not conmutative. To perform a product of matrices, each element is calculated as
    /// (being \f$ A(m x n), B(n x p), C (m x p) \f$):
    ///
    /// \f$ A x B = C \f$
    ///
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$
    ///
	/// </summary>
	/// <remarks>
	/// This product is not conmmutative.
	/// </remarks>
	/// <param name="m">[IN] Matrix to be multiplied by.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x4 operator*(const QBaseMatrix4x4 &m) const;

	/// <summary>
	/// Multiplies a 4x3 matrix by the current matrix.
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.
    /// So, left matrix must have same number of columns than rows have right matrix.
	/// The product is not conmutative. To perform a product of matrices, each element is calculated as
    /// (being \f$ A(m x n), B(n x p), C (m x p) \f$):
    ///
    /// \f$ A x B = C \f$
    ///
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$
    ///
	/// </summary>
	/// <remarks>
	/// This product is not conmmutative.
	/// </remarks>
	/// <param name="m">[IN] Matrix to be multiplied by.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QBaseMatrix4x3 operator*(const QBaseMatrix4x3 &m) const;

	/// <summary>
	/// Divides current matrix by a floating point value.
	/// </summary>
	/// <param name="fScalar">[IN] Floating point value to be divided by.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x4 operator/(const float_q &fScalar) const;

	/// <summary>
	/// Adds a QMatrix4x4 to the current matrix.
	/// </summary>
	/// <param name="m">[IN] The matrix to be added to.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x4 operator+(const QBaseMatrix4x4 &m) const;

	/// <summary>
	/// Subtracts a QMatrix4x4 to the current matrix.
	/// </summary>
	/// <param name="m">[IN] The matrix to be subtracted to.</param>
	/// <returns>
	/// The resultant matrix.
	/// </returns>
	QMatrix4x4 operator-(const QBaseMatrix4x4 &m) const;

	/// <summary>
	/// Product and assign operator. Current matrix stores the result of the multiplication.
	/// </summary>
	/// <param name="m">[IN] The matrix to be multiplied by.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	QMatrix4x4& operator*=(const QBaseMatrix4x4 &m);

    /// <summary>
	/// Product by an scalar and assign operator. Current matrix stores the result of the multiplication.
	/// </summary>
	/// <param name="fScalar">[IN] The scalar to be multiplied by.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x4& operator*=(const float_q &fScalar)
    {
        *this = fScalar * *this;
        return *this;
    }

	/// <summary>
	/// Division and assign operator. Current matrix stores the result of the division.
	/// </summary>
	/// <param name="fScalar">[IN] The floating point value by which to divide.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x4& operator/=(const float_q &fScalar)
	{
		QE_ASSERT(fScalar != SQFloat::_0);

		this->ij[0][0] /= fScalar;
		this->ij[0][1] /= fScalar;
		this->ij[0][2] /= fScalar;
		this->ij[0][3] /= fScalar;
		this->ij[1][0] /= fScalar;
		this->ij[1][1] /= fScalar;
		this->ij[1][2] /= fScalar;
		this->ij[1][3] /= fScalar;
		this->ij[2][0] /= fScalar;
		this->ij[2][1] /= fScalar;
		this->ij[2][2] /= fScalar;
		this->ij[2][3] /= fScalar;
		this->ij[3][0] /= fScalar;
		this->ij[3][1] /= fScalar;
		this->ij[3][2] /= fScalar;
		this->ij[3][3] /= fScalar;

		return *this;
	}

	/// <summary>
	/// Addition and assign operator. Current matrix stores the result of the addition.
	/// </summary>
	/// <param name="m">[IN] The matrix to be added to.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x4& operator+=(const QBaseMatrix4x4 &m)
	{
		this->ij[0][0] += m.ij[0][0];
		this->ij[0][1] += m.ij[0][1];
		this->ij[0][2] += m.ij[0][2];
		this->ij[0][3] += m.ij[0][3];
		this->ij[1][0] += m.ij[1][0];
		this->ij[1][1] += m.ij[1][1];
		this->ij[1][2] += m.ij[1][2];
		this->ij[1][3] += m.ij[1][3];
		this->ij[2][0] += m.ij[2][0];
		this->ij[2][1] += m.ij[2][1];
		this->ij[2][2] += m.ij[2][2];
		this->ij[2][3] += m.ij[2][3];
		this->ij[3][0] += m.ij[3][0];
		this->ij[3][1] += m.ij[3][1];
		this->ij[3][2] += m.ij[3][2];
		this->ij[3][3] += m.ij[3][3];

		return *this;
	}

	/// <summary>
	/// Subtraction and assign operator. Current matrix stores the result of the subtraction.
	/// </summary>
	/// <param name="m">[IN] The matrix to be subtracted to.</param>
	/// <returns>
	/// The modified matrix.
	/// </returns>
	inline QMatrix4x4& operator-=(const QBaseMatrix4x4 &m)
	{
		this->ij[0][0] -= m.ij[0][0];
		this->ij[0][1] -= m.ij[0][1];
		this->ij[0][2] -= m.ij[0][2];
		this->ij[0][3] -= m.ij[0][3];
		this->ij[1][0] -= m.ij[1][0];
		this->ij[1][1] -= m.ij[1][1];
		this->ij[1][2] -= m.ij[1][2];
		this->ij[1][3] -= m.ij[1][3];
		this->ij[2][0] -= m.ij[2][0];
		this->ij[2][1] -= m.ij[2][1];
		this->ij[2][2] -= m.ij[2][2];
		this->ij[2][3] -= m.ij[2][3];
		this->ij[3][0] -= m.ij[3][0];
		this->ij[3][1] -= m.ij[3][1];
		this->ij[3][2] -= m.ij[3][2];
		this->ij[3][3] -= m.ij[3][3];

		return *this;
	}

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QMatrix4x4& operator=(const QBaseMatrix4x4 &m)
    {
        QBaseMatrix4x4::operator=(m);
        return *this;
    }

	/// <summary>
	/// Resets all matrix elements to 0.
	/// </summary>
	inline void ResetToZero()
	{
		this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
		this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = this->ij[1][3] =
		this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = this->ij[2][3] =
		this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = this->ij[3][3] = SQFloat::_0;
	}

	/// <summary>
	/// Resets the matrix to a identity matrix. The element \f$ A_{ij} \f$ is set to 0 if \f$ i\neq j \f$,
    /// and it's set to 1 if \f$ i=j\f$.
	/// </summary>
	inline void ResetToIdentity()
	{
		this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = this->ij[3][3] = SQFloat::_1;

		this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
		this->ij[1][0] = this->ij[1][2] = this->ij[1][3] =
		this->ij[2][0] = this->ij[2][1] = this->ij[2][3] =
		this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SQFloat::_0;
	}

	/// <summary>
	/// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$. It's noted \f$ A^T \f$.
 	/// </summary>
	/// <remarks>
	/// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
	/// </remarks>
	void Transpose();

	/// <summary>
	/// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$. It's noted \f$ A^T \f$.
	/// </summary>
	/// <remarks>
	/// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
	/// </remarks>
	/// <param name="m">[OUT] Stores the resultant transposed matrix.</param>
	inline void Transpose(QBaseMatrix4x4 &m) const
	{
        m = *this;
        reinterpret_cast<QMatrix4x4&> (m).Transpose();
	}

	/// <summary>
	/// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
	/// </summary>
	/// <returns>
	/// True if all elements are 0, false otherwise.
	/// </returns>
	inline bool IsZero() const
	{
		return	SQFloat::IsZero(this->ij[0][0]) &&
				SQFloat::IsZero(this->ij[0][1]) &&
				SQFloat::IsZero(this->ij[0][2]) &&
				SQFloat::IsZero(this->ij[0][3]) &&
				SQFloat::IsZero(this->ij[1][0]) &&
				SQFloat::IsZero(this->ij[1][1]) &&
				SQFloat::IsZero(this->ij[1][2]) &&
				SQFloat::IsZero(this->ij[1][3]) &&
				SQFloat::IsZero(this->ij[2][0]) &&
				SQFloat::IsZero(this->ij[2][1]) &&
				SQFloat::IsZero(this->ij[2][2]) &&
				SQFloat::IsZero(this->ij[2][3]) &&
				SQFloat::IsZero(this->ij[3][0]) &&
				SQFloat::IsZero(this->ij[3][1]) &&
				SQFloat::IsZero(this->ij[3][2]) &&
				SQFloat::IsZero(this->ij[3][3]);
	}

	/// <summary>
	/// Checks if all elements of the matrix are 0 or under tolerance (absolute value) except
	/// elements where i==j, which must be 1.
	/// </summary>
	/// <returns>
	/// True if all elements are 0 except i==j which are 1, false otherwise.
	/// </returns>
	inline bool IsIdentity() const
	{
		return	SQFloat::AreEquals(this->ij[0][0], SQFloat::_1) &&
				SQFloat::IsZero(this->ij[0][1]) &&
				SQFloat::IsZero(this->ij[0][2]) &&
				SQFloat::IsZero(this->ij[0][3]) &&
				SQFloat::IsZero(this->ij[1][0]) &&
				SQFloat::AreEquals(this->ij[1][1], SQFloat::_1) &&
				SQFloat::IsZero(this->ij[1][2]) &&
				SQFloat::IsZero(this->ij[1][3]) &&
				SQFloat::IsZero(this->ij[2][0]) &&
				SQFloat::IsZero(this->ij[2][1]) &&
				SQFloat::AreEquals(this->ij[2][2], SQFloat::_1) &&
				SQFloat::IsZero(this->ij[2][3]) &&
				SQFloat::IsZero(this->ij[3][0]) &&
				SQFloat::IsZero(this->ij[3][1]) &&
				SQFloat::IsZero(this->ij[3][2]) &&
				SQFloat::AreEquals(this->ij[3][3], SQFloat::_1);
	}

	/// <summary>
    /// Calculates the determinant of the matrix.
    /// It's only applicable to square matrices. A determinant is a real number obtained
    /// through the addition of all possible products between elements of different
    /// row and column, where the sign of a product derives from the parity of the permutation involved.
    /// In practice, we can calculate any determinant this way:
    ///
    /// Order 1: \f$\left|A\right| = a_{00}\f$
    ///
    /// Order 2: \f$\left|A\right| = a_{00}\cdot a_{11} - a_{01}\cdot a_{10}\f$
    ///
    /// Order 3: \f$\left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{21} - (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$
    ///
    /// Any other order can be solved developing determinant by a row or a column, reducing
    /// the problem to other of one order less.
    /// To do that, we multiply each element of the row or column selected by his cofactor, defined as:
    ///
    /// \f$ C_{ij} = -1^{i+j} \cdot \left|M_{ij}\right|\f$,
    ///
    /// where \f$ M_{ij}\f$ is the submatrix obtained by deleting from the original matrix the i row and the j column.
    /// After that, we add all products to obtain the final value of the determinant.
	/// </summary>
	/// <returns>
	/// Floating point value which is the result of the determinant.
	/// </returns>
	inline float_q GetDeterminant() const
	{
		// Binary products are stored in vars to avoid unnecesary repetitions
		// (each binary product appears 2 times in determinant expresion)
		const float_q& A = this->ij[1][1] * this->ij[2][2];
		const float_q& B = this->ij[1][2] * this->ij[2][3];
		const float_q& C = this->ij[1][3] * this->ij[2][1];
		const float_q& D = this->ij[1][3] * this->ij[2][2];
		const float_q& E = this->ij[1][1] * this->ij[2][3];
		const float_q& F = this->ij[1][2] * this->ij[2][1];
		const float_q& G = this->ij[1][0] * this->ij[2][2];
		const float_q& H = this->ij[1][3] * this->ij[2][0];
		const float_q& I = this->ij[1][0] * this->ij[2][3];
		const float_q& J = this->ij[1][2] * this->ij[2][0];
		const float_q& K = this->ij[1][0] * this->ij[2][1];
		const float_q& L = this->ij[1][1] * this->ij[2][0];

		return this->ij[0][0] * (	A * this->ij[3][3] + B * this->ij[3][1] + C * this->ij[3][2] -
									D * this->ij[3][1] - E * this->ij[3][2] - F * this->ij[3][3] ) -
			   this->ij[0][1] * (	G * this->ij[3][3] + B * this->ij[3][0] + H * this->ij[3][2] -
									D * this->ij[3][0] - I * this->ij[3][2] - J * this->ij[3][3] ) +
			   this->ij[0][2] * (	K * this->ij[3][3] + E * this->ij[3][0] + H * this->ij[3][1] -
									C * this->ij[3][0] - I * this->ij[3][1] - L * this->ij[3][3] ) -
			   this->ij[0][3] * (	K * this->ij[3][2] + A * this->ij[3][0] + J * this->ij[3][1] -
									F * this->ij[3][0] - G * this->ij[3][1] - L * this->ij[3][2] );
	}

	/// <summary>
	/// Inverses the matrix.
	/// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
	///
    /// \f$ A\cdot A^{-1} = A^{-1}\cdot A = I\f$
    ///
    /// We can calculate the inverse of any matrix by:
    ///
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^{T}_{ij}\f$,
    ///
    /// where \f$ C^{T}_{ij}\f$ is the matrix formed by each cofactor of each element of A, trasposed.
    ///
	/// </summary>
	/// <remarks>
	/// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
	/// </remarks>
	/// <returns>
	/// True if the matrix is invertible, false otherwise.
	/// </returns>
	bool Reverse();

	/// <summary>
	/// Calculates the inverse of the matrix and stores it in the matrix provided.
	/// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
	///
    /// \f$ A\cdot A^{-1} = A^{-1}\cdot A = I\f$
    ///
    /// We can calculate the inverse of any matrix by:
    ///
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^{T}_{ij}\f$,
    ///
    /// where \f$ C^{T}_{ij}\f$ is the matrix formed by each cofactor of each element of A, trasposed.
    ///
	/// </summary>
	/// <remarks>
	/// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
	/// </remarks>
	/// <param name="m">[OUT] Stores the resultant inversed matrix.</param>
	/// <returns>
	/// True if the matrix is invertible, false otherwise.
	/// </returns>
	bool Reverse(QBaseMatrix4x4 &m) const
    {
        m = *this;
        return reinterpret_cast<QMatrix4x4&> (m).Reverse();
    }
	/// <summary>
	/// Converts matrix into a string with the following format:
	/// "M4x4( 11, 12, 13, 14 )( 21, 22, 23, 24 )( 31, 32, 33, 34 )( 41, 42, 43, 44 )".
	/// </summary>
	/// <returns>The string with the format specified.</returns>
	string_q ToString() const;
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMATRIX4X4__
