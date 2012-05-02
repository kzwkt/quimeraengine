// [TERMS&CONDITIONS]

#ifndef __QTRANSLATIONMATRIX__
#define __QTRANSLATIONMATRIX__

#include "QBaseVector3.h"
#include "QBaseVector4.h"
#include "QRotationMatrix3x3.h"
#include "QScaleMatrix3x3.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
class QMatrix4x4;
class QMatrix4x3;
template<class MatrixType> class QTransformationMatrix;


/// <summary>
/// Class to represent a matrix of floating point values with 4 rows and 3 or 4 columns, depending on template parameter,
/// which contains a displacement in the direction of each coordinate axis that can be represented by a 3D or homogeneus 4D vector.<br>
/// It's a identity matrix with the elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ replaced by the components of displacement:
///
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$
/// </summary>
template <class MatrixType>
class QDllExport QTranslationMatrix : public MatrixType
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. It's initialized to identity matrix.
	/// </summary>
	inline QTranslationMatrix()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a translation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline QTranslationMatrix(const MatrixType &matrix) : MatrixType(matrix)
    {
    }

    /// <summary>
    /// Constructor that receives three floating point values, one for the displacement in each axis direction.
    /// </summary>
    /// <param name="fTranslationX">[IN] Displacement in X direction.</param>
    /// <param name="fTranslationY">[IN] Displacement in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Displacement in Z direction.</param>
    inline QTranslationMatrix(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ)
    {
        this->ResetToIdentity();

        this->ij[3][0] = fTranslationX;
        this->ij[3][1] = fTranslationY;
        this->ij[3][2] = fTranslationZ;
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the three displacement values, one for each axis direction.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    inline explicit QTranslationMatrix(const QBaseVector3 &vTranslation)
    {
        this->ResetToIdentity();

        this->ij[3][0] = vTranslation.x;
        this->ij[3][1] = vTranslation.y;
        this->ij[3][2] = vTranslation.z;
    }

    /// <summary>
    /// Constructor from a 4D vector which stores the three scaling values, one for each axis direction.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    inline explicit QTranslationMatrix(const QBaseVector4 &vTranslation)
    {
        this->ResetToIdentity();

        this->ij[3][0] = vTranslation.x;
        this->ij[3][1] = vTranslation.y;
        this->ij[3][2] = vTranslation.z;
     }

    /// <summary>
    /// Constructor that receives a pointer to a floating point array.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so the pointer must point to a 12 floating point array if
    /// the template parameter is a 4x3 matrix and to a 16 floating point array if it is a 4x4 matrix.<br>
    /// Each three or four consecutive values, depending on template parameter, is used to fill a row
    /// of the matrix.<br>
    /// If you use this constructor, be sure that you are constructing a translation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="arValues">[IN] Pointer to a 12/16 length array of floating point values.</param>
    inline explicit QTranslationMatrix(const float_q* arValues) : MatrixType(arValues)
    {
    }

    /// <summary>
    /// Constructor from four 4x32 floating point packed values.<br>
    /// Each param contains a row of the matrix.<br>
    /// Last component of each pack will be ignored if the template parameter is a 4x3 matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a translation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row3">[IN] 4x32 values for row 3, columns 0 to 3 unpacked in this order.</param>
    inline QTranslationMatrix(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) :
                                  MatrixType(row0, row1, row2, row3)
    {
    }


    // PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Stores an identity matrix.<br>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// If the matrix is 4x3, we simply remove fourth column.
    /// </summary>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    inline static const QTranslationMatrix<MatrixType>& GetIdentity()
    {
        static const QTranslationMatrix<MatrixType> IDENTITY(MatrixType::GetIdentity());
        return IDENTITY;
    }


    // METHODS
	// ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a translation matrix by the resident matrix.<br>
    /// Since both are translation matrices, the product is calculated as follows:
    ///
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <remarks>
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTranslationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const
    {
        QTranslationMatrix<MatrixType> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a translation matrix by the resident matrix.<br>
    /// Since both are translation matrices, the product is calculated as follows:
    ///
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <remarks>
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTranslationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const
    {
        QTranslationMatrix<MatrixType> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;

    }

	/// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QScaleMatrix3x3 &matrix) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = matrix.ij[0][0];
        aux.ij[1][1] = matrix.ij[1][1];
        aux.ij[2][2] = matrix.ij[2][2];

        aux.ij[3][0] = matrix.ij[0][0]*this->ij[3][0];
        aux.ij[3][1] = matrix.ij[1][1]*this->ij[3][1];
        aux.ij[3][2] = matrix.ij[2][2]*this->ij[3][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.<br>
    /// Rotation matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QRotationMatrix3x3 &matrix) const
    {
        QTransformationMatrix<MatrixType> aux = QTransformationMatrix<MatrixType>::GetIdentity();

        aux.ij[0][0] = matrix.ij[0][0];
        aux.ij[0][1] = matrix.ij[0][1];
        aux.ij[0][2] = matrix.ij[0][2];

        aux.ij[1][0] = matrix.ij[1][0];
        aux.ij[1][1] = matrix.ij[1][1];
        aux.ij[1][2] = matrix.ij[1][2];

        aux.ij[2][0] = matrix.ij[2][0];
        aux.ij[2][1] = matrix.ij[2][1];
        aux.ij[2][2] = matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a transformation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<MatrixType> &matrix) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ij[0][3] = aux.ij[1][3] = aux.ij[2][3] = SQFloat::_0;
        aux.ij[3][3] = SQFloat::_1;

        aux.ij[0][0] = matrix.ij[0][0];
        aux.ij[0][1] = matrix.ij[0][1];
        aux.ij[0][2] = matrix.ij[0][2];

        aux.ij[1][0] = matrix.ij[1][0];
        aux.ij[1][1] = matrix.ij[1][1];
        aux.ij[1][2] = matrix.ij[1][2];

        aux.ij[2][0] = matrix.ij[2][0];
        aux.ij[2][1] = matrix.ij[2][1];
        aux.ij[2][2] = matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];

        return aux;
    }

    // Assign operators

    /// <summary>
    /// Product and assign operator.<br>
    /// Current matrix stores the result of the multiplication.<br>
    /// Multiplies a translation matrix by the resident matrix.<br>
    /// Since both are translation matrices, the product is calculated as follows:
    ///
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QTranslationMatrix<MatrixType>& operator*=(const QTranslationMatrix<QMatrix4x3> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Product and assign operator.<br>
    /// Current matrix stores the result of the multiplication.<br>
    /// Multiplies a translation matrix by the resident matrix. Since both are translation matrices, the product is calculated as follows:
    ///
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QTranslationMatrix<MatrixType>& operator*=(const QTranslationMatrix<QMatrix4x4> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTranslationMatrix<MatrixType>& operator=(const MatrixType &matrix)
    {
        MatrixType::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Inverts the matrix.<br>
    /// In the case of translation matrices, the inverse is composed
    /// of the opposite of the elements which defines the displacement:
    ///
    /// \f$ T^{-1}= \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ -d_{x} & -d_{y} & -d_{z} & 1 \end{bmatrix}\f$
    ///
    /// So, it's faster than base class method.
    /// </summary>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    inline MatrixType Invert() const
    {
        return QTranslationMatrix<MatrixType>(-this->ij[3][0], -this->ij[3][1], -this->ij[3][2]);
    }
    
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
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="fTranslationX">[OUT] Displacement in X axis direction.</param>
    /// <param name="fTranslationY">[OUT] Displacement in Y axis direction.</param>
    /// <param name="fTranslationZ">[OUT] Displacement in Z axis direction.</param>
    inline void GetTranslation(float_q &fTranslationX, float_q &fTranslationY, float_q &fTranslationZ) const
    {
        fTranslationX = this->ij[3][0];
        fTranslationY = this->ij[3][1];
        fTranslationZ = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement.</param>
    inline void GetTranslation(QBaseVector3 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement. W component of this vector will be set to 0.</param>
    inline void GetTranslation(QBaseVector4 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
        vTranslation.w = SQFloat::_0;
    }

	/// <summary>
    /// Calculates the determinant of the matrix.<br>
    /// Since this is a translation matrix,
    /// which is a diagonal matrix with its main diagonal composed of 1s, its determinant is 1.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
	float_q GetDeterminant() const
	{
		return SQFloat::_1;
	}

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

    // <summary>
    // Multiplies a translation matrix by the resident matrix. No matter if the input matrix or the resident one are
    // 4x3 or 4x4 matrices ore one of each type. Since both are translation matrices, the product is calculated as follows:
    //
    // \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    // \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    // \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    // </summary>
    // <remarks>
    // This product is conmmutative.
    // </remarks>
    // <param name="matrix">[IN] Matrix to be multiplied by.</param>
    // <returns>
    // The resultant translation matrix.
    // </returns>
    template <class MatrixTypeParam>
    QTranslationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix) const
    {
        return QTranslationMatrix<MatrixType>(this->ij[3][0] + matrix.ij[3][0], 
                                              this->ij[3][1] + matrix.ij[3][1], 
                                              this->ij[3][2] + matrix.ij[3][2]);
    }

    // <summary>
    // Product and assign operator. Current matrix stores the result of the multiplication.
    // Multiplies a translation matrix by the resident matrix. No matter if the input matrix or the resident one are
    // 4x3 or 4x4 matrices ore one of each type. Since both are translation matrices, the product is calculated as follows:
    //
    // \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    // \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    // \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    // </summary>
    // <param name="matrix">[IN] The matrix to be multiplied by.</param>
    template <class MatrixTypeParam>
    inline void ProductAssignationOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix)
    {
        this->ij[3][0] += matrix.ij[3][0];
        this->ij[3][1] += matrix.ij[3][1];
        this->ij[3][2] += matrix.ij[3][2];
    }

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSLATIONMATRIX__
