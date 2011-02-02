// [TERMS&CONDITIONS]

#ifndef __QROTATIONMATRIX3X3__
#define __QROTATIONMATRIX3X3__

#include "QMatrix3x3.h"

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
class QBaseVector3;
class QBaseQuaternion;
class QQuaternion;
template<class MatrixType> class QTranslationMatrix;
class QScaleMatrix3x3;
template<class MatrixType> class QTransformationMatrix;


/// <summary>
/// Class to represent a matrix of floating point values with 3 rows and 3 columns which contains a rotation.
/// </summary>
class QDllExport QRotationMatrix3x3 : public QMatrix3x3
{
	// CONSTANTS
	// ---------------
public:

    /// <summary>
    /// Stores an identity matrix.
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    /// 
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    static const QRotationMatrix3x3 Identity;

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
    /// <param name="m">[IN] The 3x3 matrix in which we want the resident matrix to be based.</param>
    inline explicit QRotationMatrix3x3(const QBaseMatrix3x3 &m) : QMatrix3x3(m) { }

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to construct the rotation 
    /// matrix of a specified rotation. 
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// This is a slow operation.
    /// </summary>
    /// <param name="fAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fAngleZ">[IN] Rotation angle about Z global axis.</param>
    inline QRotationMatrix3x3(const float_q &fAngleX, const float_q &fAngleY, const float_q &fAngleZ) : 
        QMatrix3x3(fAngleX, fAngleY, fAngleZ) { }

    /// <summary>
    /// Constructor from an angle and a spin axis defined by a vector. It's computed as follows:
    ///
    /// \f$ R = \begin{bmatrix} \cos\theta & 0 & 0 \\ 0 & \cos\theta & 0 \\ 0 & 0 & \cos\theta \end{bmatrix} + (1- \cos\theta)\cdot 
    /// \begin{bmatrix} e_x & e_y & e_z\end{bmatrix} \cdot \begin{bmatrix} e_x \\ e_y \\ e_z\end{bmatrix} + 
    /// \begin{bmatrix} 0 & -e_z & e_y \\ e_z & 0 & -e_x \\ -e_y & e_x & 0 \end{bmatrix}\cdot \sin\thetaF$
    /// 
    /// where \f$ e=(e_x, e_y, e_z)\f$, is a unit vector defining spin axis.
    ///
    /// taken from http://en.wikipedia.org/wiki/Rotation_representation#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle
    /// </summary>
    /// <param name="vAxis">[IN] Vector in the direction of the spin axis.</param>
    /// <param name="fAngle">[IN] Angle of rotation.</param>
    QRotationMatrix3x3 (const QBaseVector3 &vAxis, const float_q &fAngle);


    /// <summary>
    /// Constructor from a quaternion.
    /// taken from http://en.wikipedia.org/wiki/Rotation_representation#Rotation_matrix_.E2.86.94_quaternion
    /// </summary>
    /// <param name="qQuat">[IN] Quaternion which contains the rotation.</param>
    explicit QRotationMatrix3x3(const QBaseQuaternion &qQuat);

    /// <summary>
    /// Constructor that receives a pointer to 9 floating point values.
    /// </summary>
    /// <remarks>
    /// Keeps the convention rows x columns, so each chunck of 3 consecutive elements  
    /// corresponds to a row, where each element in the chunck is the column in the row.
    /// If you use this constructor, be sure that you are constructing a rotation matrix, 
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="pfMatrix">[IN] Pointer to a 9 length array of floating point values.</param>
    inline explicit QRotationMatrix3x3(const float_q *pfMatrix) : QMatrix3x3(pfMatrix) { }

    /// <summary>
    /// Constructor from three 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last component of each pack will be ignored.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a rotation matrix, 
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="row0">[IN] 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    inline QRotationMatrix3x3(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2) : QMatrix3x3(row0, row1, row2) { }

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
     inline QRotationMatrix3x3( const float_q &f00, const float_q &f01, const float_q &f02,
                                const float_q &f10, const float_q &f11, const float_q &f12,
                                const float_q &f20, const float_q &f21, const float_q &f22) : 
                QMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22) { }

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
    /// <param name="m">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
	QRotationMatrix3x3 operator*(const QRotationMatrix3x3 &m) const;

	/// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 or 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
    template <class MatrixType>
	QTransformationMatrix<MatrixType> operator*(const QScaleMatrix3x3 &m) const
    {
        QTransformationMatrix<MatrixType> aux;

	    aux.ResetToIdentity();

        aux.ij[0][0] = m.ij[0][0]*this->ij[0][0] ;
        aux.ij[0][1] = m.ij[1][1]*this->ij[0][1];
        aux.ij[0][2] = m.ij[2][2]*this->ij[0][2];

        aux.ij[1][0] = m.ij[0][0]*this->ij[1][0];
        aux.ij[1][1] = m.ij[1][1]*this->ij[1][1];
        aux.ij[1][2] = m.ij[2][2]*this->ij[1][2];

        aux.ij[2][0] = m.ij[0][0]*this->ij[2][0];
        aux.ij[2][1] = m.ij[1][1]*this->ij[2][1];
        aux.ij[2][2] = m.ij[2][2]*this->ij[2][2];

        return aux;
    }

	/// <summary>
    /// Multiplies a 4x4 or 4x3 translation matrix (depending on the method template parameter) by the current matrix, 
    /// following matrices product rules.
	/// Resident matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 or 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
    template <class MatrixType>
	QTransformationMatrix<MatrixType> operator*(const QTranslationMatrix<MatrixType> &m) const
    {
	    QTransformationMatrix<MatrixType> aux;

	    aux.ResetToIdentity();

	    aux.ij[3][0] = m.ij[3][0];
	    aux.ij[3][1] = m.ij[3][1];
	    aux.ij[3][2] = m.ij[3][2];

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
	/// <summary>
    /// Multiplies a 4x4 or 4x3 transformation matrix (depending on the method template parameter) by the current matrix, 
    /// following matrices product rules.
	/// Resident matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 or 4x3 transformation matrix, depending on the method template parameter.
    /// </returns>
    template <class MatrixType>
	QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<MatrixType> &m) const
    {
        QTransformationMatrix<MatrixType> aux;

	    aux.ResetToIdentity();

	    aux.ij[3][0] = m.ij[3][0];
	    aux.ij[3][1] = m.ij[3][1];
	    aux.ij[3][2] = m.ij[3][2];

        aux.ij[0][0] = this->ij[0][0]*m.ij[0][0] + this->ij[0][1]*m.ij[1][0] + this->ij[0][2]*m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0]*m.ij[0][1] + this->ij[0][1]*m.ij[1][1] + this->ij[0][2]*m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0]*m.ij[0][2] + this->ij[0][1]*m.ij[1][2] + this->ij[0][2]*m.ij[2][2];
	
        aux.ij[1][0] = this->ij[1][0]*m.ij[0][0] + this->ij[1][1]*m.ij[1][0] + this->ij[1][2]*m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0]*m.ij[0][1] + this->ij[1][1]*m.ij[1][1] + this->ij[1][2]*m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0]*m.ij[0][2] + this->ij[1][1]*m.ij[1][2] + this->ij[1][2]*m.ij[2][2];
	
        aux.ij[2][0] = this->ij[2][0]*m.ij[0][0] + this->ij[2][1]*m.ij[1][0] + this->ij[2][2]*m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0]*m.ij[0][1] + this->ij[2][1]*m.ij[1][1] + this->ij[2][2]*m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0]*m.ij[0][2] + this->ij[2][1]*m.ij[1][2] + this->ij[2][2]*m.ij[2][2];

	    return aux;
    }

    /// <summary>
    /// Reverse of the matrix. In the case of rotation matrices, the transpose is guaranteed 
    /// to be the inverse of the matrix. So, it's faster than base class method.
    /// </summary>
    inline void Reverse()
    {
        this->Transpose();
    }

    /// <summary>
    /// Reverse of the matrix. In the case of rotation matrices, the transpose is guaranteed 
    /// to be the inverse of the matrix. So, it's faster than base class method.
    /// </summary>
    /// <param name="mOut">[OUT] A rotation matrix where to store reverse matrix.</param>
    inline void Reverse(QBaseMatrix3x3 &mOut) const
    {
        this->Transpose(mOut); 
    }

    /// <summary>
    /// Converts rotation matrix to Euler angles.
    /// Quimera Engine follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// </summary>
    /// <param name="fAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_q &fAngleX, float_q &fAngleY, float_q &fAngleZ) const;

    /// <summary>
    /// Converts rotation matrix to a rotation quaternion.
    /// Since rotation matrices are special orthogonal matrices, where \f$ AA^T = AA^{-1} = I\f$, it's always verified 
    /// that (1 + trace) > 0. Then, we can calculate quaternion component from every matrix trace.
    ///
    /// Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/christian.htm
    /// </summary>
    /// <param name="qQuat">[OUT] Quaternion where to store the rotation.</param>
    void GetRotation(QQuaternion &qQuat) const;

    /// <summary>
    /// Converts rotation matrix to an angle and a spin axis. Since axis components depends on inverse of sin(angle)
    /// it's necessary to take into account when angle is 0 or \f$\pi\f$.
    /// Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
    /// Source: http://en.wikipedia.org/wiki/Rotation_representation_%28mathematics%29#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle
    /// </summary>
    /// <param name="&fAngle">[OUT] Angle of rotation.</param>
    /// <param name="&vAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_q &fAngle, QBaseVector3 &vAxis) const;

	/// <summary>
    /// Calculates the determinant of the matrix. Since this is a rotation matrix, which is
	/// a special orthogonal matrix, its determinant is 1.
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

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QROTATIONMATRIX3X3__
