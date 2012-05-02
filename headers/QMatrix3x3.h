// [TERMS&CONDITIONS]

#ifndef __QMATRIX3X3__
#define __QMATRIX3X3__

#include "QBaseMatrix3x3.h"
#include "QBaseMatrix3x4.h"

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
/// This class implements the functionality of a matrix with 3 rows and 3 columns.<br>
/// A matrix is a rectangular arrangement of numbers.<br>
/// The horizontal and vertical lines in a matrix
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.<br>
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m × n matrix,
/// while m and n are called its dimensions.<br>
/// Every element is referenced by its position in the matrix.<br>
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted A_ij.<br>
/// In this case, we will work with 3x3 matrices, therefore our matrix will be:
///
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} & a_{02}\\ a_{10} & a_{11} & a_{12}\\ a_{20} & a_{21} & a_{22}\end{bmatrix}\f$
///
/// </summary>
class QDllExport QMatrix3x3 : public QBaseMatrix3x3
{
    // FRIENDS
    // ---------------
public:
    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar term of product.</param>
    /// <param name="matrix">[IN] The matrix term of product.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    friend QMatrix3x3 operator*(const float_q &fScalar, const QBaseMatrix3x3 &matrix);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QMatrix3x3()
    {
    }

    /// <summary>
    /// Constructor from a 3x3 matrix.
    /// </summary>
    /// <param name="matrix">[IN] The 3x3 matrix in which we want the resident matrix to be based.</param>
    inline explicit QMatrix3x3(const QBaseMatrix3x3 &matrix) : QBaseMatrix3x3(matrix)
    {
    }

    /// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValueAll">[IN] The floating point value used to fill the matrix.</param>
    inline explicit QMatrix3x3(const float_q &fValueAll) : QBaseMatrix3x3(fValueAll)
    {
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
    inline QMatrix3x3(const float_q &f00, const float_q &f01, const float_q &f02,
                      const float_q &f10, const float_q &f11, const float_q &f12,
                      const float_q &f20, const float_q &f21, const float_q &f22) :
                          QBaseMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22)
    {
    }

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="arValues">[IN] Pointer to a 9 length array of floating point values.</param>
    inline explicit QMatrix3x3(const float_q *arValues) : QBaseMatrix3x3(arValues)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last component of each pack will be ignored.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    inline QMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2) : QBaseMatrix3x3(row0, row1, row2)
    {
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets a null matrix.
    /// </summary>
    /// <returns>
    /// A matrix with all components set to 0.
    /// </returns>
    inline static const QMatrix3x3& GetZeroMatrix()
    {
        static const QMatrix3x3 ZEROMATRIX(SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                           SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                           SQFloat::_0, SQFloat::_0, SQFloat::_0);
        return ZEROMATRIX;
    }

    /// <summary>
    /// Gets an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// An identity matrix
    /// </returns>
    inline static const QMatrix3x3& GetIdentity()
    {
        static const QMatrix3x3 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                         SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                         SQFloat::_0, SQFloat::_0, SQFloat::_1);
        return IDENTITY;
    }


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
    QMatrix3x3 operator*(const float_q &fScalar) const;

    /// <summary>
    /// Multiplies a 3x3 matrix by the current matrix.<br>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br>
    /// So, left matrix must have same number of columns than rows have right matrix.<br>
    /// The product is not conmutative.<br>
    /// To perform a product of matrices, each element is calculated as
    /// ( being A(m x n), B(n x p), C (m x p) ):
    ///
    /// \f$ A \times B = C \f$
    ///
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$
    ///
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator*(const QBaseMatrix3x3 &matrix) const;

    /// <summary>
    /// Multiplies a 3x4 matrix by the current matrix.<br>
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p.<br>
    /// So, left matrix must have same number of columns than rows have right matrix.<br>
    /// The product is not conmutative.<br>
    /// To perform a product of matrices, each element is calculated as ( being A(m x n), B(n x p), C (m x p) ):
    ///
    /// \f$ A\times B = C \f$
    ///
    /// \f$ C_{ij} = \sum_{r=1}^{n} A_{ir}B_{rj} \f$
    ///
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
	QBaseMatrix3x4 operator*(const QBaseMatrix3x4& matrix) const;

    /// <summary>
    /// Multiply by scalar operator. All matrix components are multiplied by the scalar.
    /// </summary>
    /// <param name="fScalar">[IN] The scalar to multiply by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3& operator*=(const float_q fScalar);

    /// <summary>
    /// Divides current matrix by a floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] Floating point value to be divided by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator/(const float_q &fScalar) const;

    /// <summary>
    /// Adds a 3x3 matrix to the current matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator+(const QBaseMatrix3x3 &matrix) const;

    /// <summary>
    /// Subtracts a 3x3 matrix to the current matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator-(const QBaseMatrix3x3 &matrix) const;

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QMatrix3x3& operator*=(const QBaseMatrix3x3 &matrix);

    /// <summary>
    /// Division and assign operator. Current matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator/=(const float_q &fScalar)
    {
        QE_ASSERT(fScalar != SQFloat::_0)

        const float_q &DIVISOR = SQFloat::_1/fScalar;

        this->ij[0][0] *= DIVISOR;
        this->ij[0][1] *= DIVISOR;
        this->ij[0][2] *= DIVISOR;
        this->ij[1][0] *= DIVISOR;
        this->ij[1][1] *= DIVISOR;
        this->ij[1][2] *= DIVISOR;
        this->ij[2][0] *= DIVISOR;
        this->ij[2][1] *= DIVISOR;
        this->ij[2][2] *= DIVISOR;

        return *this;
    }

    /// <summary>
    /// Addition and assign operator. Current matrix stores the result of the addition.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator+=(const QBaseMatrix3x3 &matrix)
    {
        this->ij[0][0] += matrix.ij[0][0];
        this->ij[0][1] += matrix.ij[0][1];
        this->ij[0][2] += matrix.ij[0][2];
        this->ij[1][0] += matrix.ij[1][0];
        this->ij[1][1] += matrix.ij[1][1];
        this->ij[1][2] += matrix.ij[1][2];
        this->ij[2][0] += matrix.ij[2][0];
        this->ij[2][1] += matrix.ij[2][1];
        this->ij[2][2] += matrix.ij[2][2];

        return *this;
    }

    /// <summary>
    /// Subtraction and assign operator. Current matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator-=(const QBaseMatrix3x3 &matrix)
    {
        this->ij[0][0] -= matrix.ij[0][0];
        this->ij[0][1] -= matrix.ij[0][1];
        this->ij[0][2] -= matrix.ij[0][2];
        this->ij[1][0] -= matrix.ij[1][0];
        this->ij[1][1] -= matrix.ij[1][1];
        this->ij[1][2] -= matrix.ij[1][2];
        this->ij[2][0] -= matrix.ij[2][0];
        this->ij[2][1] -= matrix.ij[2][1];
        this->ij[2][2] -= matrix.ij[2][2];

        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QMatrix3x3& operator=(const QBaseMatrix3x3 &matrix)
    {
        QBaseMatrix3x3::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    inline void ResetToZero()
    {
        this->ij[0][0] = this->ij[0][1] = this->ij[0][2] =
        this->ij[1][0] = this->ij[1][1] = this->ij[1][2] =
        this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = SQFloat::_0;
    }

    /// <summary>
    /// Resets the matrix to a identity matrix. The element \f$ A_{ij} \f$ is set to 0 if \f$ i\neq j \f$,
    /// and it's set to 1 if \f$ i=j\f$.
    /// </summary>
    inline void ResetToIdentity()
    {
        this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = SQFloat::_1;

        this->ij[0][1] = this->ij[0][2] =
        this->ij[1][0] = this->ij[1][2] =
        this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
    }

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row.<br>
    /// Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$.<br>
    /// It's noted \f$ A^T \f$.
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <returns>
    /// The transposed matrix.
    /// </returns>
    QMatrix3x3 Transpose() const;

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value).
    /// </summary>
    /// <returns>
    /// True if all elements are 0, false otherwise.
    /// </returns>
    inline bool IsZero() const
    {
        return  SQFloat::IsZero(this->ij[0][0]) &&
                SQFloat::IsZero(this->ij[0][1]) &&
                SQFloat::IsZero(this->ij[0][2]) &&
                SQFloat::IsZero(this->ij[1][0]) &&
                SQFloat::IsZero(this->ij[1][1]) &&
                SQFloat::IsZero(this->ij[1][2]) &&
                SQFloat::IsZero(this->ij[2][0]) &&
                SQFloat::IsZero(this->ij[2][1]) &&
                SQFloat::IsZero(this->ij[2][2]);
    }

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (absolute value) except
    /// elements where i=j, which must be 1.
    /// </summary>
    /// <returns>
    /// True if all elements are 0 except i=j which are 1, false otherwise.
    /// </returns>
    inline bool IsIdentity() const
    {
        return  SQFloat::AreEquals(this->ij[0][0], SQFloat::_1) &&
                SQFloat::IsZero(this->ij[0][1]) &&
                SQFloat::IsZero(this->ij[0][2]) &&
                SQFloat::IsZero(this->ij[1][0]) &&
                SQFloat::AreEquals(this->ij[1][1], SQFloat::_1) &&
                SQFloat::IsZero(this->ij[1][2]) &&
                SQFloat::IsZero(this->ij[2][0]) &&
                SQFloat::IsZero(this->ij[2][1]) &&
                SQFloat::AreEquals(this->ij[2][2], SQFloat::_1);
    }

    /// <summary>
    /// Calculates the determinant of the matrix.<br>
    /// It's only applicable to square matrices.<br>
    /// A determinant is a real number obtained
    /// through the addition of all possible products between elements of different
    /// row and column, where the sign of a product derives from the parity of the permutation involved.<br>
    /// In practice, we can calculate any determinant this way:
    ///
    /// Order 1: \f$\left|A\right| = a_{00}\f$
    ///
    /// Order 2: \f$\left|A\right| = a_{00}\cdot a_{11} - a_{01}\cdot a_{10}\f$
    ///
    /// Order 3: \f$\left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{21} - (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$
    ///
    /// Any other order can be solved developing determinant by a row or a column, reducing
    /// the problem to other of one order less.<br>
    /// To do that, we multiply each element of the row or column selected by his cofactor, defined as:
    ///
    /// \f$ C_{ij} = -1^{i+j} \cdot \left|M_{ij}\right|\f$,
    ///
    /// where \f$ M_{ij}\f$ is the submatrix obtained by deleting from the original matrix the i row and the j column.<br>
    /// After that, we add all products to obtain the final value of the determinant.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_q GetDeterminant() const;

    /// <summary>
    /// Inverses the matrix.<br>
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
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    QMatrix3x3 Invert() const;
    
    /// <summary>
    /// Calculates whether the matrix has inverse or not. 
    /// A matrix has inverse when its determinant doesn't equal zero.
    /// </summary>
    /// <returns>
    /// True if the matrix has inverse, false otherwise.
    /// </returns>
    inline bool HasInverse() const
    {
        // If Determinant is 0, this matrix has not inverse.
        return SQFloat::IsNotZero(this->GetDeterminant());
    }

    /// <summary>
    /// Converts matrix into a string with the following format:<br>
    /// "M3x3(($ij[0][0],$ij[0][1],$ij[0][2])($ij[1][0],$ij[1][1],$ij[1][2])
    ///       ($ij[2][0],$ij[2][1],$ij[2][2]))".<br>
    /// Where "$" means "string representation of attribute".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
    string_q ToString() const;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMATRIX3X3__
