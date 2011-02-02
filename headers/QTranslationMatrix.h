// [TERMS&CONDITIONS]

#ifndef __QTRANSLATIONMATRIX__
#define __QTRANSLATIONMATRIX__

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


/// <summary>
/// Class to represent a matrix of floating point values with 4 rows and 3 or 4 columns, depending on template parameter,
/// which contains a displacement in the direction of each coordinate axis that can be represented by a 3D or homogeneus 4D vector.
/// It's a identity matrix with the elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ replaced by the components of displacement:
///
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$
/// </summary>
template <class MatrixType>
class QDllExport QTranslationMatrix : public MatrixType
{
	// CONSTANTS
	// ---------------
public:

    /// <summary>
    /// Stores an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    /// 
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// If the matrix is 4x3, we simply remove fourth column.
    /// </summary>
    static const QTranslationMatrix<MatrixType> Identity;

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
    /// Constructor from a 4x4 or 4x3 matrix, depending on template parameter.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a translation matrix, 
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="m">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline explicit QTranslationMatrix(const MatrixType &m) : MatrixType(m) { }

    /// <summary>
    /// Constructor that receives three floating point values, one for the displacement in each axis direction. 
    /// </summary>
    /// <param name="fDispX">[IN] Displacement in X direction.</param>
    /// <param name="fDispY">[IN] Displacement in Y direction.</param>
    /// <param name="fDispZ">[IN] Displacement in Z direction.</param>
    inline QTranslationMatrix(const float_q &fDispX, const float_q &fDispY, const float_q &fDispZ) 
    { 
        this->ResetToIdentity();

        this->ij[3][0] = fDispX;
        this->ij[3][1] = fDispY;
        this->ij[3][2] = fDispZ;
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the three displacement values, one for each axis direction.
    /// </summary>
    /// <param name="vDisp">[IN] Vector with the displacement values.</param>
    inline explicit QTranslationMatrix (const QBaseVector3 &vDisp)
    {
        this->ResetToIdentity();

        this->ij[3][0] = vDisp.x;
        this->ij[3][1] = vDisp.y;
        this->ij[3][2] = vDisp.z;
    }

    /// <summary>
    /// Constructor from a 4D vector which stores the three scaling values, one for each axis direction.
    /// </summary>
    /// <param name="vDisp">[IN] Vector with the displacement values.</param>
    inline explicit QTranslationMatrix (const QBaseVector4 &vDisp)
    {
        this->ResetToIdentity();

        this->ij[3][0] = vDisp.x;
        this->ij[3][1] = vDisp.y;
        this->ij[3][2] = vDisp.z;
     }

    /// <summary>
    /// Constructor that receives a pointer to a floating point array.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so the pointer must point to a 12 floating point array if
    /// the template parameter is a 4x3 matrix and to a 16 floating point array if it is a 4x4 matrix. 
    /// Each three or four consecutive values, depending on template parameter, is used to fill a row
    /// of the matrix.
    /// If you use this constructor, be sure that you are constructing a translation matrix, 
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 12/16 length array of floating point values.</param>
    inline explicit QTranslationMatrix(const float_q *pfMatrix) : MatrixType(pfMatrix) { }

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
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
        MatrixType(row0, row1, row2, row3) { }


    // METHODS
	// ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a translation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are translation matrices, the product is calculated as follows:
    /// 
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix} 
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} = 
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <remarks>
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter that resident matrix.
    /// </returns>
    template <class MatrixTypeParam>
    QTranslationMatrix<MatrixType> operator*(const QTranslationMatrix<MatrixTypeParam> &m) const
    {
        QTranslationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[3][0] = this->ij[3][0] + m.ij[3][0];
        aux.ij[3][1] = this->ij[3][1] + m.ij[3][1];
        aux.ij[3][2] = this->ij[3][2] + m.ij[3][2];

        return aux;
    }

	/// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules. Scale matrix is
    /// extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QScaleMatrix3x3 &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = m.ij[0][0];
        aux.ij[1][1] = m.ij[1][1];
        aux.ij[2][2] = m.ij[2][2];

        aux.ij[3][0] = m.ij[0][0]*this->ij[3][0];
        aux.ij[3][1] = m.ij[1][1]*this->ij[3][1];
        aux.ij[3][2] = m.ij[2][2]*this->ij[3][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules. Rotation matrix is
    /// extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QRotationMatrix3x3 &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ij[0][3] = aux.ij[1][3] = aux.ij[2][3] = QFloat::_0;
        aux.ij[3][3] = QFloat::_1;

        aux.ij[0][0] = m.ij[0][0];
        aux.ij[0][1] = m.ij[0][1];
        aux.ij[0][2] = m.ij[0][2];

        aux.ij[1][0] = m.ij[1][0];
        aux.ij[1][1] = m.ij[1][1];
        aux.ij[1][2] = m.ij[1][2];

        aux.ij[2][0] = m.ij[2][0];
        aux.ij[2][1] = m.ij[2][1];
        aux.ij[2][2] = m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0]*m.ij[0][0] + this->ij[3][1]*m.ij[1][0] + this->ij[3][2]*m.ij[2][0];
        aux.ij[3][1] = this->ij[3][0]*m.ij[0][1] + this->ij[3][1]*m.ij[1][1] + this->ij[3][2]*m.ij[2][1];
        aux.ij[3][2] = this->ij[3][0]*m.ij[0][2] + this->ij[3][1]*m.ij[1][2] + this->ij[3][2]*m.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a transformation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<MatrixType> &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ij[0][3] = aux.ij[1][3] = aux.ij[2][3] = QFloat::_0;
        aux.ij[3][3] = QFloat::_1;

        aux.ij[0][0] = m.ij[0][0];
        aux.ij[0][1] = m.ij[0][1];
        aux.ij[0][2] = m.ij[0][2];

        aux.ij[1][0] = m.ij[1][0];
        aux.ij[1][1] = m.ij[1][1];
        aux.ij[1][2] = m.ij[1][2];

        aux.ij[2][0] = m.ij[2][0];
        aux.ij[2][1] = m.ij[2][1];
        aux.ij[2][2] = m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0]*m.ij[0][0] + this->ij[3][1]*m.ij[1][0] + this->ij[3][2]*m.ij[2][0] + m.ij[3][0];
        aux.ij[3][1] = this->ij[3][0]*m.ij[0][1] + this->ij[3][1]*m.ij[1][1] + this->ij[3][2]*m.ij[2][1] + m.ij[3][1];
        aux.ij[3][2] = this->ij[3][0]*m.ij[0][2] + this->ij[3][1]*m.ij[1][2] + this->ij[3][2]*m.ij[2][2] + m.ij[3][2];

        return aux;
    }

    // Assign operators

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// Multiplies a translation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are translation matrices, the product is calculated as follows:
    /// 
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix} 
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} = 
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <param name="m">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    template <class MatrixTypeParam>
    inline QTranslationMatrix<MatrixType>& operator*=(const QTranslationMatrix<MatrixTypeParam> &m) {
      
        this->ij[3][0] += m.ij[3][0];
        this->ij[3][1] += m.ij[3][1];
        this->ij[3][2] += m.ij[3][2];

        return *this;
    }

    /// <summary>
    /// Reverse of the matrix. In the case of translation matrices, the inverse is composed 
    /// of the opposite of the elements which defines the displacement: 
    ///
    /// \f$ T^{-1}= \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ -d_{x} & -d_{y} & -d_{z} & 1 \end{bmatrix}\f$
    ///
    /// So, it's faster than base class method.
    /// </summary>
    inline void Reverse()
    {
        this->ij[3][0] = -this->ij[3][0];
        this->ij[3][1] = -this->ij[3][1];
        this->ij[3][2] = -this->ij[3][2];
    }

    /// <summary>
    /// Reverse of the matrix. In the case of translation matrices, the inverse is composed 
    /// by the opposite of the elements which defines the displacement:
    ///
    /// \f$ T^{-1}= \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ -d_{x} & -d_{y} & -d_{z} & 1 \end{bmatrix}\f$
    ///
    /// So, it's faster than base class method.
    /// </summary>
    /// <param name="mOut">[OUT] A matrix where to store reverse matrix.</param>
    inline void Reverse(MatrixType &mOut) const
    {
        mOut.ResetToIdentity();

        mOut.ij[3][0] = -this->ij[3][0];
        mOut.ij[3][1] = -this->ij[3][1];
        mOut.ij[3][2] = -this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="fDispX">[OUT] Displacement in X axis direction.</param>
    /// <param name="fDispY">[OUT] Displacement in Y axis direction.</param>
    /// <param name="fDispZ">[OUT] Displacement in Z axis direction.</param>
    inline void GetTranslation(float_q &fDispX, float_q &fDispY, float_q &fDispZ) const
    {
        fDispX = this->ij[3][0];
        fDispY = this->ij[3][1];
        fDispZ = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="&vDisp">[OUT] Vector where to store the displacement.</param>
    inline void GetTranslation(QBaseVector3 &vDisp) const
    {
        vDisp.x = this->ij[3][0];
        vDisp.y = this->ij[3][1];
        vDisp.z = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="&vDisp">[OUT] Vector where to store the displacement. W component of this vector will be set to 0.</param>
    inline void GetTranslation(QBaseVector4 &vDisp) const
    {
        vDisp.x = this->ij[3][0];
        vDisp.y = this->ij[3][1];
        vDisp.z = this->ij[3][2];
        vDisp.w = QFloat::_0;
    }

	/// <summary>
    /// Calculates the determinant of the matrix. Since this is a translation matrix, 
    /// which is a diagonal matrix with its main diagonal composed of 1s, its determinant is 1.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
	inline float_q GetDeterminant()
	{
		return QFloat::_1;
	}

protected:
    
    // Hidden method to prevent it could be used.
    void ResetToZero();
};

// TYPEDEFS
// ---------------

//[TODO] jwladi: Uncomment this when QMatrix4x3 is implemented.
//typedef QTranslationMatrix<QMatrix4x3> QTranslationMatrix4x3;
typedef QTranslationMatrix<QMatrix4x4> QTranslationMatrix4x4;

// CONSTANTS INITIALIZATION
// ----------------------------

template <class MatrixType>
const QTranslationMatrix<MatrixType> QTranslationMatrix<MatrixType>::Identity;

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSLATIONMATRIX__
