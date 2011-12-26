// [TERMS&CONDITIONS]

#ifndef __QSCALEMATRIX3X3__
#define __QSCALEMATRIX3X3__

#include "QBaseVector3.h"
#include "QMatrix3x3.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"

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
// ----------------------
class QRotationMatrix3x3;
template<class MatrixType> class QTransformationMatrix;
template<class MatrixType> class QTranslationMatrix;

/// <summary>
/// Class to represent a matrix of floating point values with 3 rows and 3 columns which contains a scale factor
/// in the direction of each coordinate axis.
/// It's a diagonal matrix where element \f$ a_{00}\f$ stores the scaling value in X direction, element \f$ a_{11}\f$ stores it
/// in Y direction and element \f$ a_{22}\f$ does it in Z direction.
/// </summary>
class QDllExport QScaleMatrix3x3 : public QMatrix3x3
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. It's initialized to identity matrix.
	/// </summary>
    inline QScaleMatrix3x3()
    {
        this->ResetToIdentity();

    }

    /// <summary>
    /// Constructor from a 3x3 matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a scale matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="m">[IN] The 3x3 matrix in which we want the resident matrix to be based.</param>
    inline explicit QScaleMatrix3x3(const QBaseMatrix3x3 &m) : QMatrix3x3(m) { }

    /// <summary>
    /// Constructor that receives three scaling values, one for each axis direction, to construct the scale
    /// matrix.
    /// </summary>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    inline QScaleMatrix3x3(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        this->ij[0][0] = fScaleX;
        this->ij[1][1] = fScaleY;
        this->ij[2][2] = fScaleZ;

        this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
        this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the three scaling values, one for each axis direction.
    /// </summary>
    /// <param name="vScale">[IN] Vector with the scaling values.</param>
    inline explicit QScaleMatrix3x3 (const QBaseVector3 &vScale)
    {
        this->ij[0][0] = vScale.x;
        this->ij[1][1] = vScale.y;
        this->ij[2][2] = vScale.z;

        this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
        this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
    }

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// If you use this constructor, be sure that you are constructing a scale matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 9 length array of floating point values.</param>
    inline explicit QScaleMatrix3x3(const float_q *pfMatrix) : QMatrix3x3(pfMatrix) { }

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last component of each pack will be ignored.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a scale matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    inline QScaleMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2) : QMatrix3x3(row0, row1, row2) { }

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a scale matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="f00">[IN] Floating point value for element of row 0, column 0.</param>
    /// <param name="f01">[IN] Floating point value for element of row 0, column 1.</param>
    /// <param name="f02">[IN] Floating point value for element of row 0, column 2.</param>
    /// <param name="f10">[IN] Floating point value for element of row 1, column 0.</param>
    /// <param name="f11">[IN] Floating point value for element of row 1, column 1.</param>
    /// <param name="f12">[IN] Floating point value for element of row 1, column 2.</param>
    /// <param name="f20">[IN] Floating point value for element of row 2, column 0.</param>
    /// <param name="f21">[IN] Floating point value for element of row 2, column 1.</param>
    /// <param name="f22">[IN] Floating point value for element of row 2, column 2.</param>
     inline QScaleMatrix3x3( const float_q &f00, const float_q &f01, const float_q &f02,
                             const float_q &f10, const float_q &f11, const float_q &f12,
                             const float_q &f20, const float_q &f21, const float_q &f22) :
                QMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22) { }


    // PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    inline static const QScaleMatrix3x3& GetIdentity()
    {
        static const QScaleMatrix3x3 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                              SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                              SQFloat::_0, SQFloat::_0, SQFloat::_1);
        return IDENTITY;
    }


	// METHODS
	// ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
	QScaleMatrix3x3 operator*(const QScaleMatrix3x3 &m) const;

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QRotationMatrix3x3 &m) const;

	/// <summary>
    /// Multiplies a 4x4 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QTranslationMatrix<QMatrix4x4> &m) const;

    /// <summary>
    /// Multiplies a 4x3 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x3> operator*(const QTranslationMatrix<QMatrix4x3> &m) const;

    /// <summary>
    /// Multiplies a 4x4 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QTransformationMatrix<QMatrix4x4> &m) const;

    /// <summary>
    /// Multiplies a 4x3 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x3> operator*(const QTransformationMatrix<QMatrix4x3> &m) const;

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QScaleMatrix3x3& operator=(const QBaseMatrix3x3 &m)
    {
        QBaseMatrix3x3::operator=(m);
        return *this;
    }

    /// <summary>
    /// Reverse of the matrix. In the case of scale matrices, the inverse is composed
    /// by the inverses of its non zero elements. So, it's faster than base class method.
    /// If one of the diagonal elements is 0, the matrix has not inverse.
    /// </summary>
    inline void Reverse()
    {
        // If one of the diagonal elements is 0, the matrix has not inverse.
        QE_ASSERT(this->ij[0][0] != SQFloat::_0 && this->ij[1][1] != SQFloat::_0 && this->ij[2][2] != SQFloat::_0);

        this->ij[0][0] = SQFloat::_1 / this->ij[0][0];
        this->ij[1][1] = SQFloat::_1 / this->ij[1][1];
        this->ij[2][2] = SQFloat::_1 / this->ij[2][2];
    }

    /// <summary>
    /// Reverse of the matrix. In the case of scale matrices, the inverse is composed
    /// by the inverses of its non zero elements. So, it's faster than base class method.
    /// If one of the diagonal elements is 0, the matrix has not inverse.
    /// </summary>
    /// <param name="mOut">[OUT] A matrix where to store reverse matrix.</param>
    inline void Reverse(QBaseMatrix3x3 &mOut) const
    {
        mOut = *this;
        mOut.As<QScaleMatrix3x3>().Reverse();
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="fScaleX">[OUT] Resultant scale in X axis direction.</param>
    /// <param name="fScaleY">[OUT] Resultant scale in Y axis direction.</param>
    /// <param name="fScaleZ">[OUT] Resultant scale in Z axis direction.</param>
    inline void GetScale(float_q &fScaleX, float_q &fScaleY, float_q &fScaleZ) const
    {
        fScaleX = this->ij[0][0];
        fScaleY = this->ij[1][1];
        fScaleZ = this->ij[2][2];
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="&vScale">[OUT] Vector where to store the scale factors.</param>
    inline void GetScale(QBaseVector3 &vScale) const
    {
        vScale.x = this->ij[0][0];
        vScale.y = this->ij[1][1];
        vScale.z = this->ij[2][2];
    }

    /// <summary>
    /// Calculates the determinant of the matrix. Since this is a scale matrix, which is
	/// a diagonal matrix, its determinant is the product of the elements of the main diagonal.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
	inline float_q GetDeterminant()
	{
		return this->ij[0][0]*this->ij[1][1]*this->ij[2][2];
	}

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

    // Implementation of product by translation matrix operator
    template <class MatrixType>
    QTransformationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixType> &m) const
    {
        QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

        aux.ij[0][0] = this->ij[0][0];
        aux.ij[1][1] = this->ij[1][1];
        aux.ij[2][2] = this->ij[2][2];

        aux.ij[3][0] = m.ij[3][0];
        aux.ij[3][1] = m.ij[3][1];
        aux.ij[3][2] = m.ij[3][2];

        return aux;
    }

    // Implementation of product by transformation matrix operator
    template <class MatrixType>
    QTransformationMatrix<MatrixType> ProductOperatorImp(const QTransformationMatrix<MatrixType> &m) const
    {
        QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

        aux.ij[3][0] = m.ij[3][0];
        aux.ij[3][1] = m.ij[3][1];
        aux.ij[3][2] = m.ij[3][2];

        aux.ij[0][0] = this->ij[0][0]*m.ij[0][0];
        aux.ij[0][1] = this->ij[0][0]*m.ij[0][1];
        aux.ij[0][2] = this->ij[0][0]*m.ij[0][2];

        aux.ij[1][0] = this->ij[1][1]*m.ij[1][0];
        aux.ij[1][1] = this->ij[1][1]*m.ij[1][1];
        aux.ij[1][2] = this->ij[1][1]*m.ij[1][2];

        aux.ij[2][0] = this->ij[2][2]*m.ij[2][0];
        aux.ij[2][1] = this->ij[2][2]*m.ij[2][1];
        aux.ij[2][2] = this->ij[2][2]*m.ij[2][2];

        return aux;
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSCALEMATRIX3X3__
