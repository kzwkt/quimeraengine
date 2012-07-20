// [TERMS&CONDITIONS]

#ifndef __QSCALINGMATRIX3X3__
#define __QSCALINGMATRIX3X3__

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
/// in the direction of each coordinate axis.<br>
/// It's a diagonal matrix where element \f$ a_{00}\f$ stores the scaling value in X direction, element \f$ a_{11}\f$ stores it
/// in Y direction and element \f$ a_{22}\f$ does it in Z direction.
/// </summary>
class QDllExport QScalingMatrix3x3 : public QMatrix3x3
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. It's initialized to identity matrix.
	/// </summary>
    inline QScalingMatrix3x3()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="scale">[IN] The 3x3 scale matrix from which we want to create a copy in the resident 3x3 scale matrix.</param>
    inline QScalingMatrix3x3(const QScalingMatrix3x3 &scale) : QMatrix3x3(scale)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a scale matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="scale">[IN] The 3x3 matrix in which we want the resident 3x3 scale matrix to be based.</param>
    inline QScalingMatrix3x3(const QBaseMatrix3x3 &scale) : QMatrix3x3(scale)
    {
    }

    /// <summary>
    /// Constructor that receives three scaling values, one for each axis direction, to construct the scale
    /// matrix.
    /// </summary>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    inline QScalingMatrix3x3(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
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
    inline explicit QScalingMatrix3x3(const QBaseVector3 &vScale)
    {
        this->ij[0][0] = vScale.x;
        this->ij[1][1] = vScale.y;
        this->ij[2][2] = vScale.z;

        this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
        this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SQFloat::_0;
    }

    // PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets an identity matrix.<br>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    inline static const QScalingMatrix3x3& GetIdentity()
    {
        static const QScalingMatrix3x3 IDENTITY(QMatrix3x3::GetIdentity());
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
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
	QScalingMatrix3x3 operator*(const QScalingMatrix3x3 &matrix) const;

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QRotationMatrix3x3 &matrix) const;

	/// <summary>
    /// Multiplies a 4x4 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const;

    /// <summary>
    /// Multiplies a 4x3 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x3> operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const;

    /// <summary>
    /// Multiplies a 4x4 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QTransformationMatrix<QMatrix4x4> &matrix) const;

    /// <summary>
    /// Multiplies a 4x3 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x3> operator*(const QTransformationMatrix<QMatrix4x3> &matrix) const;

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QScalingMatrix3x3& operator=(const QBaseMatrix3x3 &matrix)
    {
        QBaseMatrix3x3::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Inverts the matrix.<br>
    /// In the case of scale matrices, the inverse is composed by the inverses of its non zero elements.<br>
    /// So, it's faster than base class method.<br>
    /// If one of the diagonal elements is 0, the matrix has not inverse.
    /// </summary>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    inline QMatrix3x3 Invert() const
    {
        // If one of the diagonal elements is 0, the matrix has not inverse.
        QE_ASSERT(this->ij[0][0] != SQFloat::_0 && this->ij[1][1] != SQFloat::_0 && this->ij[2][2] != SQFloat::_0)

        return QScalingMatrix3x3(SQFloat::_1 / this->ij[0][0], SQFloat::_1 / this->ij[1][1], SQFloat::_1 / this->ij[2][2]);
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
    /// <param name="vScale">[OUT] Vector where to store the scale factors.</param>
    inline void GetScale(QBaseVector3 &vScale) const
    {
        vScale.x = this->ij[0][0];
        vScale.y = this->ij[1][1];
        vScale.z = this->ij[2][2];
    }

    /// <summary>
    /// Calculates the determinant of the matrix.<br>
    /// Since this is a scale matrix, which is a diagonal matrix, its determinant is the product of the elements of the main diagonal.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
	float_q GetDeterminant() const;

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

    // Implementation of product by translation matrix operator
    template <class MatrixType>
    QTransformationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixType> &matrix) const
    {
        QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

        aux.ij[0][0] = this->ij[0][0];
        aux.ij[1][1] = this->ij[1][1];
        aux.ij[2][2] = this->ij[2][2];

        aux.ij[3][0] = matrix.ij[3][0];
        aux.ij[3][1] = matrix.ij[3][1];
        aux.ij[3][2] = matrix.ij[3][2];

        return aux;
    }

    // Implementation of product by transformation matrix operator
    template <class MatrixType>
    QTransformationMatrix<MatrixType> ProductOperatorImp(const QTransformationMatrix<MatrixType> &matrix) const
    {
        QTransformationMatrix<MatrixType> aux(QTransformationMatrix<MatrixType>::GetIdentity());

        aux.ij[3][0] = matrix.ij[3][0];
        aux.ij[3][1] = matrix.ij[3][1];
        aux.ij[3][2] = matrix.ij[3][2];

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2];

        aux.ij[1][0] = this->ij[1][1] * matrix.ij[1][0];
        aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
        aux.ij[1][2] = this->ij[1][1] * matrix.ij[1][2];

        aux.ij[2][0] = this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

        return aux;
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSCALINGMATRIX3X3__
