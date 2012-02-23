// [TERMS&CONDITIONS]

#ifndef __QROTATIONMATRIX3X3__
#define __QROTATIONMATRIX3X3__

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
class QBaseQuaternion;
class QQuaternion;
class QScaleMatrix3x3;
template<class MatrixType> class QTransformationMatrix;
template<class MatrixType> class QTranslationMatrix;


/// <summary>
/// Class to represent a matrix of floating point values with 3 rows and 3 columns which contains a rotation.
/// </summary>
class QDllExport QRotationMatrix3x3 : public QMatrix3x3
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. It's initialized to identity matrix.
	/// </summary>
    inline QRotationMatrix3x3()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Constructor from a 3x3 matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a rotation matrix,
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="rotation">[IN] The 3x3 matrix in which we want the resident matrix to be based.</param>
    inline explicit QRotationMatrix3x3(const QBaseMatrix3x3 &rotation) : QMatrix3x3(rotation)
    {
    }

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to construct the rotation
    /// matrix of a specified rotation.<br>
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.<br>
    /// The rotation matrix is obtained as follows:
    ///
    /// \f$ R = \begin{bmatrix} 1 & 0 & 0\\ 0 & \cos x  & \sin x\\ 0 & -\sin x & \cos x \end{bmatrix}
    /// \begin{bmatrix} \cos y & 0 & -\sin y\\ 0 & 1 & 0\\ \sin y & 0 & \cos y \end{bmatrix}
    /// \begin{bmatrix} \cos z & \sin z & 0 \\ -\sin z & \cos z & 0\\ 0 & 0 & 1 \end{bmatrix} \f$
    ///
    /// This is a slow operation.
    /// </summary>
    /// <param name="fRotationAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fRotationAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fRotationAngleZ">[IN] Rotation angle about Z global axis.</param>
    QRotationMatrix3x3(const float_q &fRotationAngleX, const float_q &fRotationAngleY, const float_q &fRotationAngleZ);

	/// <summary>
	/// Constructor from an angle and a spin axis defined by a vector. It's computed as follows:
	///
	/// \f$ R = \begin{bmatrix} \cos\theta & 0 & 0 \\ 0 & \cos\theta & 0 \\ 0 & 0 & \cos\theta \end{bmatrix} + (1- \cos\theta)\cdot
	/// \begin{bmatrix} e_x \\ e_y \\ e_z\end{bmatrix} \cdot \begin{bmatrix} e_x & e_y & e_z\end{bmatrix} +
	/// \begin{bmatrix} 0 & e_z & -e_y \\ -e_z & 0 & e_x \\ e_y & -e_x & 0 \end{bmatrix}\cdot \sin\theta \f$
	///
	/// where \f$ e=(e_x, e_y, e_z)\f$, is a unit vector defining spin axis.
	/// </summary>
	/// <param name="vRotationAxis">[IN] Vector in the direction of the spin axis.</param>
	/// <param name="fRotationAngle">[IN] Angle of rotation.</param>
	/// <remarks>
    /// The axis vector must be normalized to construct the rotation matrix properly.
    /// </remarks>
    QRotationMatrix3x3(const QBaseVector3 &vRotationAxis, const float_q &fRotationAngle);

    /// <summary>
    /// Constructor from a quaternion. Is constructed as follows:
    ///
    /// \f$ R = \begin{bmatrix} 1 - 2(q_y^2 + q_z^2) & 2(q_xq_y - q_wq_z) & 2(q_xq_z + q_wq_y) \\
    /// 2(q_xq_y + q_wq_z) & 1 - 2(q_x^2 + q_z^2) & 2(q_yq_z - q_wq_x) \\
    /// 2(q_xq_z - q_wq_y) & 2(q_yq_z + q_wq_x) & 1 - 2(q_x^2 + q_y^2)
    /// \end{bmatrix}\f$
    ///
    /// </summary>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation.</param>
    /// <remarks>
    /// The quaternion must be normalized to construct the rotation matrix properly.
    /// </remarks>
    explicit QRotationMatrix3x3(const QBaseQuaternion &qRotation);

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements
    /// corresponds to a row, where each element in the chunck is the column in the row.<br>
    /// If you use this constructor, be sure that you are constructing a rotation matrix,
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="arValues">[IN] Pointer to a 9 length array of floating point values.</param>
    inline explicit QRotationMatrix3x3(const float_q* arValues) : QMatrix3x3(arValues)
    {
    }

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.<br>
    /// Last component of each pack will be ignored.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a rotation matrix,
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    inline QRotationMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2) : QMatrix3x3(row0, row1, row2)
    {
    }

    /// <summary>
    /// Constructor from a floating point value for each element of the matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a rotation matrix,
    /// otherwise unpredictable behavior could be happen.
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
     inline QRotationMatrix3x3(const float_q &f00, const float_q &f01, const float_q &f02,
                               const float_q &f10, const float_q &f11, const float_q &f12,
                               const float_q &f20, const float_q &f21, const float_q &f22) :
                                   QMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22)
    {
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
    inline static const QRotationMatrix3x3& GetIdentity()
    {
        static const QRotationMatrix3x3 IDENTITY(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                 SQFloat::_0, SQFloat::_1, SQFloat::_0,
                                                 SQFloat::_0, SQFloat::_0, SQFloat::_1);
        return IDENTITY;
    }


	// METHODS
	// ---------------
public:

    //Binary operators

	/// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
	QRotationMatrix3x3 operator*(const QRotationMatrix3x3 &matrix) const;

	/// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix, depending on the method template parameter.
    /// </returns>
	QTransformationMatrix<QMatrix4x4> operator*(const QScaleMatrix3x3 &matrix) const;

	/// <summary>
    /// Multiplies a 4x4 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
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
    /// The resultant 4x3 transformation matrix.
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
    /// The resultant 4x4 transformation matrix.
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
    /// The resultant 4x3 transformation matrix.
    /// </returns>
	QTransformationMatrix<QMatrix4x3> operator*(const QTransformationMatrix<QMatrix4x3> &matrix) const;

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QRotationMatrix3x3& operator=(const QBaseMatrix3x3 &matrix)
    {
        QBaseMatrix3x3::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Reverse of the matrix.<br>
    /// In the case of rotation matrices, the transpose is guaranteed to be the inverse of the matrix.<br>
    /// So, it's faster than base class method.
    /// </summary>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    inline QMatrix3x3 Reverse() const
    {
        return this->Transpose();
    }
    
    /// <summary>
    /// Converts rotation matrix to Euler angles.<br>
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// </summary>
    /// <param name="fRotationAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fRotationAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fRotationAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const;

    /// <summary>
    /// Converts rotation matrix to a rotation quaternion.<br>
    /// Since rotation matrices are special orthogonal matrices, where \f$ AA^T = AA^{-1} = I\f$, it's always verified
    /// that (1 + trace) > 0.<br>
    /// Then, we can calculate quaternion component from every matrix trace.<br>
    /// </summary>
    /// <param name="qRotation">[OUT] Quaternion where to store the rotation.</param>
    void GetRotation(QQuaternion &qRotation) const;

    /// <summary>
    /// Converts rotation matrix to an angle and a spin axis.<br>
    /// Since axis components depends on inverse of sin(angle) it's necessary to take into account when angle is 0 or \f$ \pi\f$.
    /// </summary>
    /// <param name="fRotationAngle">[OUT] Angle of rotation.</param>
    /// <param name="vRotationAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_q &fRotationAngle, QBaseVector3 &vRotationAxis) const;

	/// <summary>
    /// Calculates the determinant of the matrix. Since this is a rotation matrix, which is
	/// a special orthogonal matrix, its determinant is 1.
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

        aux.ij[3][0] = matrix.ij[3][0];
        aux.ij[3][1] = matrix.ij[3][1];
        aux.ij[3][2] = matrix.ij[3][2];

        aux.ij[0][0] = this->ij[0][0];
        aux.ij[0][1] = this->ij[0][1];
        aux.ij[0][2] = this->ij[0][2];

        aux.ij[1][0] = this->ij[1][0];
        aux.ij[1][1] = this->ij[1][1];
        aux.ij[1][2] = this->ij[1][2];

        aux.ij[2][0] = this->ij[2][0];
        aux.ij[2][1] = this->ij[2][1];
        aux.ij[2][2] = this->ij[2][2];

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

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        return aux;
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QROTATIONMATRIX3X3__
