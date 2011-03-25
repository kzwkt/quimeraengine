// [TERMS&CONDITIONS]

#ifndef __QMATRIX2X2__
#define __QMATRIX2X2__

#include "QBaseMatrix2x2.h"

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
/// This class implements the functionality of a matrix with 2 rows and 2 columns.
///
/// A matrix is a rectangular arrangement of numbers. The horizontal and vertical lines in a matrix 
/// are called rows and columns, respectively. The numbers in the matrix are called its entries or its elements.
/// To specify the size of a matrix, a matrix with m rows and n columns is called an m-by-n matrix or m x n matrix, 
/// while m and n are called its dimensions. Every element is referenced by its position in the matrix.
/// Due to we use a row by column convention, we will always write first the row of the element and then its
/// column: the element in the i row and the j column is denoted A_ij. In this case, we will work with 2x2 matrices, 
/// therefore our matrix will be:
/// 
/// \f$ A = \begin{bmatrix} a_{00} & a_{01} \\ a_{10} & a_{11} \end{bmatrix}\f$
///     
/// </summary>
class QDllExport QMatrix2x2 : public QBaseMatrix2x2
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
    friend QMatrix2x2 operator*(const float_q &fScalar, const QBaseMatrix2x2 &m);

    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Stores a matrix with all components set to 0.
    /// </summary>
    static const QMatrix2x2 ZeroMatrix;

    /// <summary>
    /// Stores an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    /// 
    /// \f$ I = \begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    static const QMatrix2x2 Identity;

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QMatrix2x2() : QBaseMatrix2x2() { }

    /// <summary>
    /// Constructor from a 2x2 matrix.
    /// </summary>
    /// <param name="m">[IN] The 2x2 matrix in which we want the resident matrix to be based.</param>
    inline explicit QMatrix2x2(const QBaseMatrix2x2 &m) : QBaseMatrix2x2(m) { }

	/// <summary>
    /// Constructor from a floating point value which with fill all matrix's elements.
    /// </summary>
    /// <param name="fValue">[IN] The floating point value used to fill the matrix.</param>
    inline explicit QMatrix2x2(const float_q &fValue)
	{
		ij[0][0] = ij[0][1] = 
		ij[1][0] = ij[1][1] = fValue; 
	}

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
     inline QMatrix2x2( const float_q &f00, const float_q &f01, const float_q &f10, const float_q &f11) : 
        QBaseMatrix2x2(f00, f01, f10, f11) { }

    /// <summary>
    /// Constructor that receives a pointer to 4 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 2 consecutive elements  
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 4 length array of floating point values.</param>
    inline explicit QMatrix2x2(const float_q *pfMatrix) : QBaseMatrix2x2(pfMatrix) { }

    /// <summary>
    /// Constructor from one 4x32 floating point packed values. Each pack component contains an element of the matrix.
    /// </summary>
    /// <param name="vfValues">[IN] 4x32 values for the matrix.</param>
    inline QMatrix2x2(const vf32_q &vfValues) : QBaseMatrix2x2(vfValues) { }

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
    QMatrix2x2 operator*(const float_q &fScalar) const;

    /// <summary>
    /// Multiplies a 2x2 matrix by the current matrix.
    /// A matrix [m x n] can only be multiplied by a matrix [n x p], being the resultant matrix [m x p]. 
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
    QMatrix2x2 operator*(const QBaseMatrix2x2 &m) const;

    /// <summary>
    /// Divides current matrix by a floating point value.
    /// </summary>
    /// <param name="fScalar">[IN] Floating point value to be divided by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix2x2 operator/(const float_q &fScalar) const;

    /// <summary>
    /// Adds a 2x2 matrix to the current matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix2x2 operator+(const QBaseMatrix2x2 &m) const;

    /// <summary>
    /// Subtracts a 2x2 matrix to the current matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QMatrix2x2 operator-(const QBaseMatrix2x2 &m) const;

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="m">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QMatrix2x2& operator*=(const QBaseMatrix2x2 &m);

    /// <summary>
    /// Division and assign operator. Current matrix stores the result of the division.
    /// </summary>
    /// <param name="fScalar">[IN] The floating point value by which to divide.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix2x2& operator/=(const float_q &fScalar)
    {
        QE_ASSERT(fScalar != QFloat::_0);
                
        this->ij[0][0] /= fScalar;
        this->ij[0][1] /= fScalar;
        this->ij[1][0] /= fScalar;
        this->ij[1][1] /= fScalar;

        return *this;
    }

    /// <summary>
    /// Addition and assign operator. Current matrix stores the result of the addition.
    /// </summary>
    /// <param name="m">[IN] The matrix to be added to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix2x2& operator+=(const QBaseMatrix2x2 &m)
    {
        this->ij[0][0] += m.ij[0][0];
        this->ij[0][1] += m.ij[0][1];
        this->ij[1][0] += m.ij[1][0];
        this->ij[1][1] += m.ij[1][1];

        return *this;
    }

    /// <summary>
    /// Subtraction and assign operator. Current matrix stores the result of the subtraction.
    /// </summary>
    /// <param name="m">[IN] The matrix to be subtracted to.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QMatrix2x2& operator-=(const QBaseMatrix2x2 &m)
    {
        this->ij[0][0] -= m.ij[0][0];
        this->ij[0][1] -= m.ij[0][1];
        this->ij[1][0] -= m.ij[1][0];
        this->ij[1][1] -= m.ij[1][1];

        return *this;
    }

    /// <summary>
    /// Equal operator. A tolerance value "Epsilon" is used for discriminate whether the matrices are equal or not.
    /// </summary>
    /// <param name="m">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator==(const QBaseMatrix2x2 &m) const
    {
        return QFloat::AreEquals(this->ij[0][0], m.ij[0][0]) &&
               QFloat::AreEquals(this->ij[0][1], m.ij[0][1]) &&
               QFloat::AreEquals(this->ij[1][0], m.ij[1][0]) &&
               QFloat::AreEquals(this->ij[1][1], m.ij[1][1]);  
    }

    /// <summary>
    /// Non-Equal operator. A tolerance value "Epsilon" is used for discriminate whether the 
    /// matrices are equal or not.
    /// </summary>
    /// <param name="m">[IN] The matrix to compare to.</param>
    /// <returns>
    /// If matrices are not equal, then it returns true. Otherwise, it returns false.
    /// </returns>
    inline bool operator!=(const QBaseMatrix2x2 &m) const
    {
        return  QFloat::AreNotEquals(this->ij[0][0], m.ij[0][0]) ||
                QFloat::AreNotEquals(this->ij[0][1], m.ij[0][1]) ||
                QFloat::AreNotEquals(this->ij[1][0], m.ij[1][0]) ||
                QFloat::AreNotEquals(this->ij[1][1], m.ij[1][1]);  
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QMatrix2x2& operator=(const QMatrix2x2 &m)
    {
        reinterpret_cast<QBaseMatrix2x2&>(*this) = m;
        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QMatrix2x2& operator=(const QBaseMatrix2x2 &m)
    {
        reinterpret_cast<QBaseMatrix2x2&>(*this) = m;    
        return *this;
    }

    /// <summary>
    /// Resets all matrix elements to 0.
    /// </summary>
    inline void ResetToZero()
    {
        this->ij[0][0] = this->ij[0][1] =
        this->ij[1][0] = this->ij[1][1] = QFloat::_0;
    }

    /// <summary>
    /// Resets the matrix to a identity matrix. The element \f$ A_{ij} \f$ is set to 0 if \f$ i\neq j \f$, 
    /// and it's set to 1 if \f$ i=j\f$.
    /// </summary>
    inline void ResetToIdentity()
    {
        this->ij[0][0] = this->ij[1][1] = QFloat::_1;
        this->ij[0][1] = this->ij[1][0] = QFloat::_0;
    }

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$. It's noted \f$ A^T \f$.
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    inline void Transpose()
    {
        float_q f01 = this->ij[0][1];
                
        this->ij[0][1] = this->ij[1][0];
        this->ij[1][0] = f01;
     }

    /// <summary>
    /// The transpose of a matrix m x n is a matrix n x m where each row becomes a column
    /// and each column becomes a row. Every element \f$ A_{ij} \f$  becomes \f$ A_{ji}\f$. It's noted \f$ A^T \f$.
    /// </summary>
    /// <remarks>
    /// If the matrix is a rotation matrix, then the transpose is guaranteed to be the inverse of the matrix.
    /// </remarks>
    /// <param name="m">[OUT] Stores the resultant transposed matrix.</param>
    inline void Transpose(QBaseMatrix2x2 &m) const
    {
        m.ij[0][0] = this->ij[0][0];
        m.ij[0][1] = this->ij[1][0];
        m.ij[1][0] = this->ij[0][1];
        m.ij[1][1] = this->ij[1][1];
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
                QFloat::IsZero(this->ij[1][0]) &&
                QFloat::IsZero(this->ij[1][1]);  
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
                QFloat::IsZero(this->ij[1][0]) &&
                QFloat::AreEquals(this->ij[1][1], QFloat::_1);  
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
        return this->ij[0][0] * this->ij[1][1] - this->ij[0][1] * this->ij[1][0];
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
    inline bool Reverse(QBaseMatrix2x2 &m) const
    {
        m = *this;
        return reinterpret_cast<QMatrix2x2&> (m).Reverse();
    }
    
    /// <summary>
    /// Converts matrix into a string with the following format:
    /// "M2x2( 00, 01 )( 10, 11 )".
    /// </summary>
    /// <returns>The string with the format specified.</returns>
    inline string_q ToString() const
    {
        return QE_L("M2x2(") + QFloat::ToString(this->ij[0][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[0][1]) + QE_L(")(") +
                               QFloat::ToString(this->ij[1][0]) + QE_L(",") +
                               QFloat::ToString(this->ij[1][1]) + QE_L(")");  
    }   
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QMATRIX2X2__
