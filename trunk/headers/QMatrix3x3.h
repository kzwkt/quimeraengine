// [TERMS&CONDITIONS]

#ifndef __QMATRIX3X3__
#define __QMATRIX3X3__

#include "QBaseMatrix3x3.h"

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
/// This class implements the functionality of a matrix with 3 rows and 3 columns.
///
/// A matrix is a rectangular arrangement of numbers. The horizontal and vertical lines in a matrix 
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m × n matrix, 
/// while m and n are called its dimensions. Every element is referenced by its position in the matrix.
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted A_ij. In this case, we will work with 3x3 matrices, 
/// therefore our matrix will be:
///      _           _
///     | a00 a01 a02 |
/// A = | a10 a11 a12 |
///     |_a20 a21 a22_|
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
    /// <param name="m">[IN] The matrix term of product.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    friend QMatrix3x3 operator*(const float_q &fScalar, const QBaseMatrix3x3 &m);

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Stores a matrix with all components set to 0.
    /// </summary>
    static const QMatrix3x3 ZeroMatrix;
    /// <summary>
    /// Stores an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    /// 
    ///      _     _
    ///     | 1 0 0 |
    /// A = | 0 1 0 |
    ///     |_0 0 1_|
    ///
    /// </summary>
    static const QMatrix3x3 Identity;

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QMatrix3x3() : QBaseMatrix3x3() { }

    /// <summary>
    /// Constructor from a QBaseMatrix3x3.
    /// </summary>
    /// <param name="m">[IN] The QBaseMatrix3x3 in which we want the QMatrix3x3 to be based.</param>
    inline explicit QMatrix3x3(const QBaseMatrix3x3 &m) : QBaseMatrix3x3(m) { }

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to construct the rotation 
    /// matrix of a specified rotation. 
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// This is a slow operation.
    /// </summary>
    /// <param name="fAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fAngleZ">[IN] Rotation angle about Z global axis.</param>
    QMatrix3x3(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ);

    /// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValue">[IN] The floating point value used to fill the matrix.</param>
    inline explicit QMatrix3x3(const float_q &fValue) : QBaseMatrix3x3(fValue) { }

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
     inline QMatrix3x3( const float_q &f00, const float_q &f01, const float_q &f02,
                        const float_q &f10, const float_q &f11, const float_q &f12,
                        const float_q &f20, const float_q &f21, const float_q &f22) : 

                        QBaseMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22) { }

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements 
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 9 length array of floating point values.</param>
    inline explicit QMatrix3x3(const float_q *pfMatrix) : QBaseMatrix3x3(pfMatrix) { }

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last component of each pack will be ignored.
    /// </summary>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    inline QMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2) : QBaseMatrix3x3(row0, row1, row2) { }

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
    /// Multiplies a 3x3 matrix by the current matrix.
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix m x p. 
    /// So, left matrix must have same number of columns than rows have right matrix.
    /// The product is not conmutative. To perform a product of matrices, each element is calculated as 
    /// (being A(m x n), B(n x p), C (m x p) ):
    /// 
    /// A x B = C
    /// 
    ///         _n_
    /// Cij =   \    Air*Brj
    ///         /__
    ///         r=1
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator*(const QBaseMatrix3x3 &m) const;

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
    /// <param name="m">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator+(const QBaseMatrix3x3 &m) const;

    /// <summary>
    /// Subtracts a 3x3 matrix to the current matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix3x3 operator-(const QBaseMatrix3x3 &m) const;

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="m">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QMatrix3x3& operator*=(const QBaseMatrix3x3 &m);

    /// <summary>
    /// Division and assign operator. Current matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator/=(const float_q &fScalar)
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

        return *this;
    }

    /// <summary>
    /// Addition and assign operator. Current matrix stores the result of the addition.
    /// </summary>
    /// <param name="m">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator+=(const QBaseMatrix3x3 &m)
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

        return *this;
    }

    /// <summary>
    /// Subtraction and assign operator. Current matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="m">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix3x3& operator-=(const QBaseMatrix3x3 &m)
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

        return *this;
    }

    /// <summary>
    /// Equal operator. A tolerance value "Epsilon" is used for discriminate whether the matrices are equal or not.
    /// </summary>
    /// <param name="m">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseMatrix3x3 &m) const
    {
        return QFloat::AreEquals(this->ij[0][0], m.ij[0][0]) &&
               QFloat::AreEquals(this->ij[0][1], m.ij[0][1]) &&
               QFloat::AreEquals(this->ij[0][2], m.ij[0][2]) &&
               QFloat::AreEquals(this->ij[1][0], m.ij[1][0]) &&
               QFloat::AreEquals(this->ij[1][1], m.ij[1][1]) &&
               QFloat::AreEquals(this->ij[1][2], m.ij[1][2]) &&
               QFloat::AreEquals(this->ij[2][0], m.ij[2][0]) &&
               QFloat::AreEquals(this->ij[2][1], m.ij[2][1]) &&
               QFloat::AreEquals(this->ij[2][2], m.ij[2][2]);  
    }

    /// <summary>
    /// Non-Equal operator. A tolerance value "Epsilon" is used for discriminate whether the 
    /// matrices are equal or not.
    /// </summary>
    /// <param name="m">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseMatrix3x3 &m) const
    {
        return  QFloat::AreNotEquals(this->ij[0][0], m.ij[0][0]) ||
                QFloat::AreNotEquals(this->ij[0][1], m.ij[0][1]) ||
                QFloat::AreNotEquals(this->ij[0][2], m.ij[0][2]) ||
                QFloat::AreNotEquals(this->ij[1][0], m.ij[1][0]) ||
                QFloat::AreNotEquals(this->ij[1][1], m.ij[1][1]) ||
                QFloat::AreNotEquals(this->ij[1][2], m.ij[1][2]) ||
                QFloat::AreNotEquals(this->ij[2][0], m.ij[2][0]) ||
                QFloat::AreNotEquals(this->ij[2][1], m.ij[2][1]) ||
                QFloat::AreNotEquals(this->ij[2][2], m.ij[2][2]);  
    }

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    inline void ResetToZero()
    {
        this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = 
        this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = 
        this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = QFloat::_0;
    }

    /// <summary>
    /// Resets the matrix to a identity matrix. The element _ij is set to 0 if i != j, 
    /// and it's set to 1 if i=j.
    /// </summary>
    inline void ResetToIdentity()
    {
        this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = QFloat::_1;

        this->ij[0][1] = this->ij[0][2] = 
        this->ij[1][0] = this->ij[1][2] = 
        this->ij[2][0] = this->ij[2][1] = QFloat::_0;
    }

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element Aij becomes Aji. It's noted A^T.
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    void Transpose();

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element Aij becomes Aji. It's noted A^T.
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <param name="m">[OUT] Stores the resultant transposed matrix.</param>
    inline void Transpose(QBaseMatrix3x3 &m) const
    {
        m.ij[0][0] = this->ij[0][0];
        m.ij[0][1] = this->ij[1][0];
        m.ij[0][2] = this->ij[2][0];
        m.ij[1][0] = this->ij[0][1];
        m.ij[1][1] = this->ij[1][1];
        m.ij[1][2] = this->ij[2][1];
        m.ij[2][0] = this->ij[0][2];
        m.ij[2][1] = this->ij[1][2];
        m.ij[2][2] = this->ij[2][2];
    }

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (abs value).
    /// </summary>
    /// <returns>
    /// True if all elements are 0, false otherwise.
    /// </returns>
    inline bool IsZero() const
    {
        return  QFloat::IsZero(this->ij[0][0]) &&
                QFloat::IsZero(this->ij[0][1]) &&
                QFloat::IsZero(this->ij[0][2]) &&
                QFloat::IsZero(this->ij[1][0]) &&
                QFloat::IsZero(this->ij[1][1]) &&
                QFloat::IsZero(this->ij[1][2]) &&
                QFloat::IsZero(this->ij[2][0]) &&
                QFloat::IsZero(this->ij[2][1]) &&
                QFloat::IsZero(this->ij[2][2]);  
    }

    /// <summary>
    /// Checks if all elements of the matrix are 0 or under tolerance (abs value) except 
    /// elements where i==j, which must be 1.
    /// </summary>
    /// <returns>
    /// True if all elements are 0 except i==j which are 1, false otherwise.
    /// </returns>
    inline bool IsIdentity() const
    {
        return  QFloat::AreEquals(this->ij[0][0], QFloat::_1) &&
                QFloat::IsZero(this->ij[0][1]) &&
                QFloat::IsZero(this->ij[0][2]) &&
                QFloat::IsZero(this->ij[1][0]) &&
                QFloat::AreEquals(this->ij[1][1], QFloat::_1) &&
                QFloat::IsZero(this->ij[1][2]) &&
                QFloat::IsZero(this->ij[2][0]) &&
                QFloat::IsZero(this->ij[2][1]) &&
                QFloat::AreEquals(this->ij[2][2], QFloat::_1);  
    }

    /// <summary>
    /// Calculates the determinant of the matrix.
    /// It's only applicable to square matrices. A determinant is a real number obtained 
    /// through the addition of all possible products between elements of different 
    /// row and column, where the sign of a product derives from the parity of the permutation involved.
    /// In practice, we can calculate any determinant this way:
    /// 
    /// Order 1: |A| = a00
    ///                  
    /// Order 2: |A| = a00*a11 - a01*a10
    /// 
    /// Order 3: |A| = a00*a11*a22 + a01*a12*a20 + a02*a10*a21 - (a02*a11*a20 + a00*a12*a21 + a01*a10*a22)
    /// 
    /// Any other order can be solved developing determinant by a row or a column, reducing 
    /// the problem to other of one order less. 
    /// To do that, we multiply each element of the row or column selected by his cofactor, defined as:
    /// 
    /// Cij = (-1)^(i+j) * |Mij|, 
    ///
    /// where Mij is the submatrix obtained by deleting from the original matrix the i row and the j column. 
    /// After that, we add all products to obtain the final value of the determinant.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    inline float_q GetDeterminant() const
    {
        return this->ij[0][0] * this->ij[1][1] * this->ij[2][2] +
               this->ij[0][1] * this->ij[1][2] * this->ij[2][0] +
               this->ij[0][2] * this->ij[1][0] * this->ij[2][1] -
               this->ij[0][2] * this->ij[1][1] * this->ij[2][0] -
               this->ij[0][0] * this->ij[1][2] * this->ij[2][1] -
               this->ij[0][1] * this->ij[1][0] * this->ij[2][2];
    }                            
    
    /// <summary>
    /// Inverses the matrix.
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
    /// 
    /// A * A^-1  = A^-1 * A = I
    /// 
    /// We can calculate the inverse of any matrix by:
    /// 
    ///         1
    /// A^-1 = --- * (C^T)ij , where (C^T)ij is the matrix formed by each cofactor of each element of A, trasposed.
    ///        |A|
    /// </summary>
    /// <returns>
    /// True if the matrix is invertible, false otherwise.
    /// </returns>
    bool Reverse();

    /// <summary>
    /// Calculates the inverse of the matrix and stores it in the matrix provided.
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
    /// 
    /// A * A^-1  = A^-1 * A = I
    /// 
    /// We can calculate the inverse of any matrix by:
    /// 
    ///         1
    /// A^-1 = --- * (C^T)ij , where (C^T)ij is the matrix formed by each cofactor of each element of A, trasposed.
    ///        |A|
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <param name="m">[OUT] Stores the resultant inversed matrix.</param>
    /// <returns>
    /// True if the matrix is invertible, false otherwise.
    /// </returns>
    bool Reverse(QMatrix3x3 &m) const;
    
    /// <summary>
    /// Converts matrix into a string with the following format:
    /// "M3x3( 11, 12, 13, 14 )( 21, 22, 23, 24 )( 31, 32, 33, 34 )( 41, 42, 43, 44 )".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("M3x3(") + QFloat::ToString(this->ij[0][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[0][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[0][2]) + QE_L(")(") +
                               QFloat::ToString(this->ij[1][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[1][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[1][2]) + QE_L(")(") +
                               QFloat::ToString(this->ij[2][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[2][1]) + QE_L(",") +
                               QFloat::ToString(this->ij[2][2]) + QE_L(")");  
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMATRIX3X3__
