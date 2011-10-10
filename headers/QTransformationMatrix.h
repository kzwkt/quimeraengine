// [TERMS&CONDITIONS]

#ifndef __QTRANSFORMATIONMATRIX__
#define __QTRANSFORMATIONMATRIX__

#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QQuaternion.h"
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
template<class MatrixType> class QTranslationMatrix;

/// <summary>
/// Class which represents a transformation matrix. A transformation matrix is, in general, composed of a scale,
/// a rotation and a translation (or any combination of them). If we note:
/// \f$ S = \begin{bmatrix} s_x & 0 & 0 & 0 \\ 0 & s_y & 0 & 0 \\ 0 & 0 & s_z & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$,
/// \f$ R = \begin{bmatrix} r_{00} & r_{01} & r_{02} & 0 \\ r_{10} & r_{11} & r_{12} & 0 \\ r_{20} & r_{21} & r_{22} & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$, and
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$,\\
/// which are the scale matrix, the rotation matrix and the translation matrix respectively, we compose the transformation as follows:
/// \f$ SRT = \begin{bmatrix} s_x\dot r_{00} & s_x\dot r_{01} & s_x\dot r_{02} & 0 \\ s_y\dot r_{10} & s_y\dot r_{11} & s_y\dot r_{12} & 0 \\
/// s_z\dot r_{20} & s_z\dot r_{21} & s_z\dot r_{22} & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$
/// Since this class is a template, we allow the use of a 4x4 matrix (QMatrix4x4) or a 4x3 one (QMatrix4x3) as parameter.
/// When parameter is a 4x3 matrix, we treat it as a 4x4 matrix, assuming that fourth column
/// is \f$ \begin{bmatrix} 0 \\ 0 \\ 0 \\ 1 \end{bmatrix}\f$.
/// </summary>
template <class MatrixType>
class QDllExport QTransformationMatrix : public MatrixType
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
    /// </summary>
    static const QTransformationMatrix<MatrixType> Identity;

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    QTransformationMatrix() : MatrixType(QTransformationMatrix::Identity)
    {
    }

    /// <summary>
    /// Constructor from a 4x4 or 4x3 matrix, depending on template parameter.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="m">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline explicit QTransformationMatrix(const MatrixType &m) : MatrixType(m) { }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 3D vector which stores the translation.
    /// </summary>
    /// <param name="vDisp">[IN] Vector with the displacement values.</param>
    /// <param name="qRot">[IN] Quaternion with the rotation values.</param>
    /// <param name="vScale">[IN] Vector with the scale values.</param>
    inline QTransformationMatrix (const QBaseVector3 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale)
    {
        this->Initialize(vDisp.x, vDisp.y, vDisp.z, QFloat::_0, qRot.x, qRot.y, qRot.z, qRot.w, vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 4D vector which stores the translation.
    /// </summary>
    /// <param name="vDisp">[IN] Vector with the displacement values.</param>
    /// <param name="qRot">[IN] Quaternion with the rotation values.</param>
    /// <param name="vScale">[IN] Vector with the scale values.</param>
    inline QTransformationMatrix (const QBaseVector4 &vDisp, const QBaseQuaternion &qRot, const QBaseVector3 &vScale)
    {
        this->Initialize(vDisp.x, vDisp.y, vDisp.z, vDisp.w, qRot.x, qRot.y, qRot.z, qRot.w, vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor that receives three scaling values, one for each axis direction, four rotation values
    /// which define a rotation quaternion and four displacement values (like a 4D vector) which define a translation.
    /// </summary>
    /// <param name="fDispX">[IN] Displazament within X direction.</param>
    /// <param name="fDispY">[IN] Displazament within Y direction.</param>
    /// <param name="fDispZ">[IN] Displazament within Z direction.</param>
    /// <param name="fDispW">[IN] W component of a 4d translation vector (0 generally).</param>
    /// <param name="fRotX">[IN] X component of the rotation quaternion.</param>
    /// <param name="fRotY">[IN] Y component of the rotation quaternion.</param>
    /// <param name="fRotZ">[IN] Z component of the rotation quaternion.</param>
    /// <param name="fRotW">[IN] W component of the rotation quaternion.</param>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    inline QTransformationMatrix(const float_q &fDispX, const float_q &fDispY, const float_q &fDispZ, const float_q &fDispW,
                                 const float_q &fRotX, const float_q &fRotY, const float_q &fRotZ, const float_q &fRotW,
                                 const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        this->Initialize(fDispX, fDispY, fDispZ, fDispW, fRotX, fRotY, fRotZ, fRotW, fScaleX, fScaleY, fScaleZ);
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
    inline explicit QTransformationMatrix(const float_q *pfMatrix) : MatrixType(pfMatrix) { }

    /// <summary>
    /// Constructor from four 4x32 floating point packed values. Each param contains a row of the matrix.
    /// Last component of each pack will be ignored if the template parameter is a 4x3 matrix.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a translation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="row0">[IN] A 4x32 values for row 0, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row1">[IN] A 4x32 values for row 1, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row2">[IN] A 4x32 values for row 2, columns 0 to 3 unpacked in this order.</param>
    /// <param name="row3">[IN] A 4x32 values for row 3, columns 0 to 3 unpacked in this order.</param>
    inline QTransformationMatrix(const vf32_q &row0, const vf32_q &row1, const vf32_q &row2, const vf32_q &row3) :
        MatrixType(row0, row1, row2, row3) { }

    /// <summary>
    /// Constructor from a 4x3 or 4x4 (depending on the constructor template parameter) translation matrix, a 3x3 rotation matrix and
    /// a 3x3 scale matrix.
    /// </summary>
    /// <param name="mDisp">[IN] A 4x3 or 4x4 translation matrix.</param>
    /// <param name="mRot">[IN] A 3x3 rotation matrix.</param>
    /// <param name="mScale">[IN] A 3x3 scale matrix.</param>
    template <class MatrixTypeParam>
    QTransformationMatrix (const QTranslationMatrix<MatrixTypeParam> &mDisp, const QRotationMatrix3x3 &mRot, const QScaleMatrix3x3 &mScale)
    {
        this->ResetToIdentity();

        this->ij[0][0] = mScale.ij[0][0] * mRot.ij[0][0];
        this->ij[0][1] = mScale.ij[0][0] * mRot.ij[0][1];
        this->ij[0][2] = mScale.ij[0][0] * mRot.ij[0][2];

        this->ij[1][0] = mScale.ij[1][1] * mRot.ij[1][0];
        this->ij[1][1] = mScale.ij[1][1] * mRot.ij[1][1];
        this->ij[1][2] = mScale.ij[1][1] * mRot.ij[1][2];

        this->ij[2][0] = mScale.ij[2][2] * mRot.ij[2][0];
        this->ij[2][1] = mScale.ij[2][2] * mRot.ij[2][1];
        this->ij[2][2] = mScale.ij[2][2] * mRot.ij[2][2];

        this->ij[3][0] = mDisp.ij[3][0];
        this->ij[3][1] = mDisp.ij[3][1];
        this->ij[3][2] = mDisp.ij[3][2];
    }

    // METHODS
    // ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    /// knowing that fourth column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter as resident matrix.
    /// </returns>
    template <class MatrixTypeParam>
    QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<MatrixTypeParam> &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = this->ij[0][0] * m.ij[0][0] + this->ij[0][1] * m.ij[1][0] + this->ij[0][2] * m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * m.ij[0][1] + this->ij[0][1] * m.ij[1][1] + this->ij[0][2] * m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * m.ij[0][2] + this->ij[0][1] * m.ij[1][2] + this->ij[0][2] * m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * m.ij[0][0] + this->ij[1][1] * m.ij[1][0] + this->ij[1][2] * m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * m.ij[0][1] + this->ij[1][1] * m.ij[1][1] + this->ij[1][2] * m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * m.ij[0][2] + this->ij[1][1] * m.ij[1][2] + this->ij[1][2] * m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * m.ij[0][0] + this->ij[2][1] * m.ij[1][0] + this->ij[2][2] * m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * m.ij[0][1] + this->ij[2][1] * m.ij[1][1] + this->ij[2][2] * m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * m.ij[0][2] + this->ij[2][1] * m.ij[1][2] + this->ij[2][2] * m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * m.ij[0][0] + this->ij[3][1] * m.ij[1][0] + this->ij[3][2] * m.ij[2][0] + m.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * m.ij[0][1] + this->ij[3][1] * m.ij[1][1] + this->ij[3][2] * m.ij[2][1] + m.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * m.ij[0][2] + this->ij[3][1] * m.ij[1][2] + this->ij[3][2] * m.ij[2][2] + m.ij[3][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 4x4 or 4x3 (depending on the method template parameter) translation matrix by the current matrix,
    /// following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    template <class MatrixTypeParam>
    QTransformationMatrix<MatrixType> operator*(const QTranslationMatrix<MatrixTypeParam> &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux = *this;

        aux.ij[3][0] += m.ij[3][0];
        aux.ij[3][1] += m.ij[3][1];
        aux.ij[3][2] += m.ij[3][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// The rotation matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QRotationMatrix3x3 &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = this->ij[0][0] * m.ij[0][0] + this->ij[0][1] * m.ij[1][0] + this->ij[0][2] * m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * m.ij[0][1] + this->ij[0][1] * m.ij[1][1] + this->ij[0][2] * m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * m.ij[0][2] + this->ij[0][1] * m.ij[1][2] + this->ij[0][2] * m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * m.ij[0][0] + this->ij[1][1] * m.ij[1][0] + this->ij[1][2] * m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * m.ij[0][1] + this->ij[1][1] * m.ij[1][1] + this->ij[1][2] * m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * m.ij[0][2] + this->ij[1][1] * m.ij[1][2] + this->ij[1][2] * m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * m.ij[0][0] + this->ij[2][1] * m.ij[1][0] + this->ij[2][2] * m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * m.ij[0][1] + this->ij[2][1] * m.ij[1][1] + this->ij[2][2] * m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * m.ij[0][2] + this->ij[2][1] * m.ij[1][2] + this->ij[2][2] * m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * m.ij[0][0] + this->ij[3][1] * m.ij[1][0] + this->ij[3][2] * m.ij[2][0];
        aux.ij[3][1] = this->ij[3][0] * m.ij[0][1] + this->ij[3][1] * m.ij[1][1] + this->ij[3][2] * m.ij[2][1];
        aux.ij[3][2] = this->ij[3][0] * m.ij[0][2] + this->ij[3][1] * m.ij[1][2] + this->ij[3][2] * m.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules.
    /// The scale matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QScaleMatrix3x3 &m) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = this->ij[0][0] * m.ij[0][0];
        aux.ij[0][1] = this->ij[0][1] * m.ij[1][1];
        aux.ij[0][2] = this->ij[0][2] * m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * m.ij[0][0];
        aux.ij[1][1] = this->ij[1][1] * m.ij[1][1];
        aux.ij[1][2] = this->ij[1][2] * m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * m.ij[0][0];
        aux.ij[2][1] = this->ij[2][1] * m.ij[1][1];
        aux.ij[2][2] = this->ij[2][2] * m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * m.ij[0][0];
        aux.ij[3][1] = this->ij[3][1] * m.ij[1][1];
        aux.ij[3][2] = this->ij[3][2] * m.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a matrix of the same MatrixType of the current matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="m">[IN] Matrix of the same MatrixType to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
	inline QTransformationMatrix<MatrixType> operator*(MatrixType &m)
	{
		return reinterpret_cast<QTransformationMatrix<MatrixType>&>(MatrixType::operator*(m)); 
	}

    // Assign operators

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    /// knowing that last column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    /// </summary>
    /// <param name="m">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    template <class MatrixTypeParam>
    inline QTransformationMatrix<MatrixType>& operator*=(const QTransformationMatrix<MatrixTypeParam> &m) {

        QTransformationMatrix<MatrixType> aux;

        aux.ResetToIdentity();

        aux.ij[0][0] = this->ij[0][0] * m.ij[0][0] + this->ij[0][1] * m.ij[1][0] + this->ij[0][2] * m.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * m.ij[0][1] + this->ij[0][1] * m.ij[1][1] + this->ij[0][2] * m.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * m.ij[0][2] + this->ij[0][1] * m.ij[1][2] + this->ij[0][2] * m.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * m.ij[0][0] + this->ij[1][1] * m.ij[1][0] + this->ij[1][2] * m.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * m.ij[0][1] + this->ij[1][1] * m.ij[1][1] + this->ij[1][2] * m.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * m.ij[0][2] + this->ij[1][1] * m.ij[1][2] + this->ij[1][2] * m.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * m.ij[0][0] + this->ij[2][1] * m.ij[1][0] + this->ij[2][2] * m.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * m.ij[0][1] + this->ij[2][1] * m.ij[1][1] + this->ij[2][2] * m.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * m.ij[0][2] + this->ij[2][1] * m.ij[1][2] + this->ij[2][2] * m.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * m.ij[0][0] + this->ij[3][1] * m.ij[1][0] + this->ij[3][2] * m.ij[2][0] + m.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * m.ij[0][1] + this->ij[3][1] * m.ij[1][1] + this->ij[3][2] * m.ij[2][1] + m.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * m.ij[0][2] + this->ij[3][1] * m.ij[1][2] + this->ij[3][2] * m.ij[2][2] + m.ij[3][2];

        *this = aux;

        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <param name="m">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTransformationMatrix<MatrixType>& operator=(const MatrixType &m)
    {
        MatrixType::operator=(m);
        return *this;
    }

    /// <summary>
    /// Calculates the determinant of the matrix. Since this is a transformation matrix,
    /// its determinant can be calculated as if it was a 3x3 matrix, removing fourth row and fourth column
    /// in calculus :
    ///
    /// \f$ \left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{10}\cdot a_{21} -
    /// (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$
    ///
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
    /// \f$ A\cdot A^{-1}  = A^{-1}\cdot A = I\f$
    ///
    /// We can calculate the inverse of any matrix by:
    ///
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^T_{ij}\f$ , where \f$ C^T_{ij}\f$ is the matrix
    /// formed by each cofactor of each element of A, trasposed.
    /// Since the matrix is a transformation matrix, then the inversion can be optimized avoiding all products by
    /// the elements of the fourth column.
    /// Inverse has this general form, expressed in function of the scale, the rotation and the translation:
    /// \f$ (SRT)^{-1} = T^{-1}\cdot R^{-1}\cdot S^{-1} = \begin{bmatrix} \frac{r_{00}}{S_x} & \frac{r_{10}}{S_y} & \frac{r_{20}}{S_z} & 0 \\ \frac{r_{01}}{S_x} & \frac{r_{11}}{S_y} & \frac{r_{21}}{S_z} & 0 \\ \frac{r_{02}}{S_x} & \frac{r_{12}}{S_y} & \frac{r_{22}}{S_z} & 0 \\ \frac{-r_{00}d_x-r_{01}d_y-r_{02}d_z}{S_x} & \frac{-r_{10}d_x-r_{11}d_y-r_{12}d_z}{S_y} & \frac{-r_{20}d_x-r_{21}d_y-r_{22}d_z}{S_z} & 1 \end{bmatrix} \f$
    /// </summary>
    /// <returns>
    /// True if the matrix is invertible, false otherwise.
    /// </returns>
    bool Reverse()
    {
        // Special case where matrix is identity. Then inverse of the matrix is itself.
        if (this->IsIdentity())
        {
            return true;
        }

        // Gets Determinant.
        float_q fDet = this->GetDeterminant();

        // If Determinant is 0, this matrix has not inverse.
        if (QFloat::IsZero(fDet))
            return false;

        // We need inverse of determinant in calculus.
        fDet = QFloat::_1/fDet;

        // Binary products are stored in vars to avoid unnecesary repetitions
        const float_q& A = this->ij[0][0] * this->ij[1][1];
        const float_q& D = this->ij[2][1] * this->ij[3][0];
        const float_q& E = this->ij[0][1] * this->ij[1][0];
        const float_q& H = this->ij[2][0] * this->ij[3][1];
        const float_q& J = this->ij[2][1] * this->ij[3][2];
        const float_q& K = this->ij[2][2] * this->ij[3][1];
        const float_q& N = this->ij[2][0] * this->ij[3][2];
        const float_q& O = this->ij[2][2] * this->ij[3][0];
        const float_q& Q = this->ij[0][1] * this->ij[1][2];
        const float_q& T = this->ij[0][2] * this->ij[1][1];
        const float_q& U = this->ij[0][0] * this->ij[1][2];
        const float_q& X = this->ij[0][2] * this->ij[1][0];

        MatrixType aux;

        aux.ResetToIdentity();

        // 1st column of inverse
        aux.ij[0][0] =  fDet * (this->ij[1][1] * this->ij[2][2] - this->ij[1][2] * this->ij[2][1] );
        aux.ij[1][0] = -fDet * (this->ij[1][0] * this->ij[2][2] - this->ij[1][2] * this->ij[2][0] );
        aux.ij[2][0] =  fDet * (this->ij[1][0] * this->ij[2][1] - this->ij[1][1] * this->ij[2][0] );
        aux.ij[3][0] = -fDet * (this->ij[1][0] * J + this->ij[1][1] * O + this->ij[1][2] * H -
                                this->ij[1][2] * D - this->ij[1][0] * K - this->ij[1][1] * N );

        // 2nd column of inverse
        aux.ij[0][1] = -fDet * (this->ij[0][1] * this->ij[2][2] - this->ij[0][2] * this->ij[2][1] );
        aux.ij[1][1] =  fDet * (this->ij[0][0] * this->ij[2][2] - this->ij[0][2] * this->ij[2][0] );
        aux.ij[2][1] = -fDet * (this->ij[0][0] * this->ij[2][1] - this->ij[0][1] * this->ij[2][0] );
        aux.ij[3][1] =  fDet * (this->ij[0][0] * J + this->ij[0][1] * O + this->ij[0][2] * H -
                                this->ij[0][2] * D - this->ij[0][0] * K - this->ij[0][1] * N );

        // 3rd column of inverse
        aux.ij[0][2] =  fDet * (Q - T);
        aux.ij[1][2] = -fDet * (U - X);
        aux.ij[2][2] =  fDet * (A - E);
        aux.ij[3][2] = -fDet * (A * this->ij[3][2] + Q * this->ij[3][0] + X * this->ij[3][1] -
                                T * this->ij[3][0] - U * this->ij[3][1] - E * this->ij[3][2] );

        *this = aux;

        return true;
    }

    /// <summary>
    /// Inverses the matrix and stores result in a matrix provided.
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
    ///
    /// \f$ A\cdot A^{-1}  = A^{-1}\cdot A = I\f$
    ///
    /// We can calculate the inverse of any matrix by:
    ///
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^T_{ij}\f$ , where \f$ C^T_{ij}\f$ is the matrix
    /// formed by each cofactor of each element of A, trasposed.
    /// Since the matrix is a transformation matrix, then the inversion can be optimized avoiding all products by
    /// the elements of the fourth column.
    /// Inverse has this general form, expressed in function of the scale, the rotation and the translation:
    /// \f$ (SRT)^{-1} = T^{-1}\cdot R^{-1}\cdot S^{-1} = \begin{bmatrix} \frac{r_{00}}{S_x} & \frac{r_{10}}{S_y} & \frac{r_{20}}{S_z} & 0 \\ \frac{r_{01}}{S_x} & \frac{r_{11}}{S_y} & \frac{r_{21}}{S_z} & 0 \\ \frac{r_{02}}{S_x} & \frac{r_{12}}{S_y} & \frac{r_{22}}{S_z} & 0 \\ \frac{-r_{00}d_x-r_{01}d_y-r_{02}d_z}{S_x} & \frac{-r_{10}d_x-r_{11}d_y-r_{12}d_z}{S_y} & \frac{-r_{20}d_x-r_{21}d_y-r_{22}d_z}{S_z} & 1 \end{bmatrix} \f$
    /// </summary>
    /// <param name="m">[OUT] The matrix where to store the inverse matrix.</param>
    /// <returns>
    /// True if the matrix is invertible, false otherwise.
    /// </returns>
    bool Reverse(MatrixType &m) const
    {
        m = *this;
        return m.Reverse();
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
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="fScaleX">[OUT] Resultant scale in X axis direction.</param>
    /// <param name="fScaleY">[OUT] Resultant scale in Y axis direction.</param>
    /// <param name="fScaleZ">[OUT] Resultant scale in Z axis direction.</param>
    inline void GetScale(float_q &fScaleX, float_q &fScaleY, float_q &fScaleZ) const
    {
        fScaleX = sqrt(this->ij[0][0]*this->ij[0][0] + this->ij[0][1]*this->ij[0][1] + this->ij[0][2]*this->ij[0][2]);
        fScaleY = sqrt(this->ij[1][0]*this->ij[1][0] + this->ij[1][1]*this->ij[1][1] + this->ij[1][2]*this->ij[1][2]);
        fScaleZ = sqrt(this->ij[2][0]*this->ij[2][0] + this->ij[2][1]*this->ij[2][1] + this->ij[2][2]*this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="&vScale">[OUT] Vector where to store the scale factors.</param>
    inline void GetScale(QBaseVector3 &vScale) const
    {
        vScale.x = sqrt(this->ij[0][0]*this->ij[0][0] + this->ij[0][1]*this->ij[0][1] + this->ij[0][2]*this->ij[0][2]);
        vScale.y = sqrt(this->ij[1][0]*this->ij[1][0] + this->ij[1][1]*this->ij[1][1] + this->ij[1][2]*this->ij[1][2]);
        vScale.z = sqrt(this->ij[2][0]*this->ij[2][0] + this->ij[2][1]*this->ij[2][1] + this->ij[2][2]*this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining the Euler angles.
    /// </summary>
    /// <param name="fAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_q &fAngleX, float_q &fAngleY, float_q &fAngleZ) const
    {
        QRotationMatrix3x3 mAux;

        this->ToRotationMatrix3x3(mAux);
        mAux.GetRotation(fAngleX, fAngleY, fAngleZ);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining a rotation quaternion.
    /// </summary>
    /// <param name="qRot">[OUT] Quaternion where to store the extracted rotation.</param>
    void GetRotation(QBaseQuaternion &qRot) const
    {
        QRotationMatrix3x3 mAux;

        this->ToRotationMatrix3x3(mAux);
        mAux.GetRotation(static_cast<QQuaternion&>(qRot));
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining an angle and a spin axis.
    /// </summary>
    /// <param name="&fAngle">[OUT] Angle of rotation.</param>
    /// <param name="&vAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_q &fAngle, QBaseVector3 &vAxis) const
    {
        QRotationMatrix3x3 mAux;

        this->ToRotationMatrix3x3(mAux);
        mAux.GetRotation(fAngle, vAxis);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <param name="vDisp">[OUT] Vector to store the translation.</param>
    /// <param name="qRot">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    inline void Decompose(QBaseVector3 &vDisp, QBaseQuaternion &qRot, QBaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRot);
        this->GetTranslation(vDisp);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <param name="vDisp">[OUT] Vector to store the translation.</param>
    /// <param name="qRot">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    inline void Decompose(QBaseVector4 &vDisp, QBaseQuaternion &qRot, QBaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRot);
        this->GetTranslation(vDisp);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// They can be 4x3 or 4x4 matrices, depending on the method template parameter.
    /// </summary>
    /// <param name="mDisp">[OUT] Matrix to store the translation.</param>
    /// <param name="mRot">[OUT] Matrix to store the rotation.</param>
    /// <param name="mScale">[OUT] Matrix to store the scale.</param>
    template <class MatrixTypeParam>
    void Decompose(QTransformationMatrix<MatrixTypeParam> &mDisp,
                   QTransformationMatrix<MatrixTypeParam> &mRot,
                   QTransformationMatrix<MatrixTypeParam> &mScale) const
    {
        QBaseVector3 vAux;
        this->GetScale(vAux);

        mScale.ResetToIdentity();

        mScale.ij[0][0] = vAux.x;
        mScale.ij[1][1] = vAux.y;
        mScale.ij[2][2] = vAux.z;

        QBaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        mRot = QTransformationMatrix<MatrixTypeParam> (QFloat::_0, QFloat::_0, QFloat::_0, QFloat::_0,
                                                       qRotAux.x , qRotAux.y , qRotAux.z , qRotAux.w,
                                                       QFloat::_1, QFloat::_1, QFloat::_1);
        this->GetTranslation(vAux);

        mDisp.ResetToIdentity();

        mDisp.ij[3][0] = vAux.x;
        mDisp.ij[3][1] = vAux.y;
        mDisp.ij[3][2] = vAux.z;
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// The translation matrix can be 4x3 or 4x4 matrix, depending on the method template parameter.
    /// </summary>
    /// <param name="mDisp">[OUT] Matrix to store the translation.</param>
    /// <param name="mRot">[OUT] Matrix to store the rotation.</param>
    /// <param name="mScale">[OUT] Matrix to store the scale.</param>
    template <class MatrixTypeParam>
    void Decompose(QTranslationMatrix<MatrixTypeParam> &mDisp,
                   QRotationMatrix3x3 &mRot,
                   QScaleMatrix3x3 &mScale) const
    {
        QBaseVector3 vAux;
        this->GetScale(vAux);

        mScale.ResetToIdentity();

        mScale.ij[0][0] = vAux.x;
        mScale.ij[1][1] = vAux.y;
        mScale.ij[2][2] = vAux.z;

        QBaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        mRot = QRotationMatrix3x3 (qRotAux);

        this->GetTranslation(vAux);

        mDisp.ResetToIdentity();

        mDisp.ij[3][0] = vAux.x;
        mDisp.ij[3][1] = vAux.y;
        mDisp.ij[3][2] = vAux.z;
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
	/// Remember that Quimera Engine works with left-hand convention by default.
	/// To do that, we invert both rotation (by trasposing it) and z translation component.
    /// </summary>
    void SwitchHandConvention()
    {
        QBaseVector3 vScale, vInvScale(QFloat::_1, QFloat::_1, QFloat::_1);
        this->GetScale(vScale);

        QE_ASSERT(vScale.x != QFloat::_0 && vScale.y != QFloat::_0 && vScale.z != QFloat::_0);

        vInvScale.x /= vScale.x;
        vInvScale.y /= vScale.y;
        vInvScale.z /= vScale.z;

        // Rotation correction
        std::swap(this->ij[0][1], this->ij[1][0]);
        std::swap(this->ij[0][2], this->ij[2][0]);
        std::swap(this->ij[2][1], this->ij[1][2]);

        // Scale correction
        this->ij[0][1] *= vInvScale.y * vScale.x;
        this->ij[1][0] *= vInvScale.x * vScale.y;

        this->ij[0][2] *= vInvScale.z * vScale.x;
        this->ij[2][0] *= vInvScale.x * vScale.z;

        this->ij[2][1] *= vInvScale.z * vScale.y;
        this->ij[1][2] *= vInvScale.y * vScale.z;

        // Translation correction
        this->ij[3][2] = -this->ij[3][2];

    }

	/// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
	/// Remember that Quimera Engine works with left-hand convention by default.
	/// To do that, we inverting both rotation (by trasposing it) and z translation component.
    /// </summary>
	/// <param name="m">[OUT] Matrix to store the changed transformation matrix.</param>
    template <class MatrixTypeParam>
    void SwitchHandConvention(QTransformationMatrix<MatrixTypeParam> &m)
    {
		m = *this;
        m.SwitchHandConvention();
    }


protected:
    // Hidden method to prevent it could be used.
    void ResetToZero();

    // Function to convert the 3x3 submatrix which contains the rotation and the scale into
    // a 3x3 rotation matrix without the scale. It uses the fact that in a 3x3 rotation matrix,
    // the length of any row o column vector is 1, so current length of each row in the transformation matrix
    // is the scale factor (each row have a scale factor which matches with an axis).
    // Dividing each row by its length we obtain the original rotation matrix.
    void ToRotationMatrix3x3(QRotationMatrix3x3 &m) const
    {
        QBaseVector3 fScale, fInvScale(QFloat::_1, QFloat::_1, QFloat::_1);

        this->GetScale(fScale);

        QE_ASSERT(fScale.x != QFloat::_0 && fScale.y != QFloat::_0 && fScale.z != QFloat::_0);

        fInvScale.x /= fScale.x;
        fInvScale.y /= fScale.y;
        fInvScale.z /= fScale.z;

        m.ij[0][0] = this->ij[0][0] * fInvScale.x;
        m.ij[0][1] = this->ij[0][1] * fInvScale.x;
        m.ij[0][2] = this->ij[0][2] * fInvScale.x;
        m.ij[1][0] = this->ij[1][0] * fInvScale.y;
        m.ij[1][1] = this->ij[1][1] * fInvScale.y;
        m.ij[1][2] = this->ij[1][2] * fInvScale.y;
        m.ij[2][0] = this->ij[2][0] * fInvScale.z;
        m.ij[2][1] = this->ij[2][1] * fInvScale.z;
        m.ij[2][2] = this->ij[2][2] * fInvScale.z;
    }

    // <summary>
    // Initializes the transformation matrix from the components of a scale vector,
    // a rotation quaternion and a translation vector.
    // </summary>
    // <param name="fDispX">[IN] Displazament within X direction.</param>
    // <param name="fDispY">[IN] Displazament within Y direction.</param>
    // <param name="fDispZ">[IN] Displazament within Z direction.</param>
    // <param name="fDispW">[IN] W component of a 4d translation vector (0 generally).</param>
    // <param name="fRotX">[IN] X component of the rotation quaternion.</param>
    // <param name="fRotY">[IN] Y component of the rotation quaternion.</param>
    // <param name="fRotZ">[IN] Z component of the rotation quaternion.</param>
    // <param name="fRotW">[IN] W component of the rotation quaternion.</param>
    // <param name="fScaleX">[IN] Scale within X direction.</param>
    // <param name="fScaleY">[IN] Scale within Y direction.</param>
    // <param name="fScaleZ">[IN] Scale within Z direction.</param>
    void Initialize(const float_q &fDispX, const float_q &fDispY, const float_q &fDispZ, const float_q &fDispW,
                    const float_q &fRotX, const float_q &fRotY, const float_q &fRotZ, const float_q &fRotW,
                    const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        QQuaternion qRot(fRotX, fRotY, fRotZ, fRotW);

        QRotationMatrix3x3 mRot(qRot);

        this->ResetToIdentity();

        this->ij[0][0] = fScaleX * mRot.ij[0][0];
        this->ij[0][1] = fScaleX * mRot.ij[0][1];
        this->ij[0][2] = fScaleX * mRot.ij[0][2];

        this->ij[1][0] = fScaleY * mRot.ij[1][0];
        this->ij[1][1] = fScaleY * mRot.ij[1][1];
        this->ij[1][2] = fScaleY * mRot.ij[1][2];

        this->ij[2][0] = fScaleZ * mRot.ij[2][0];
        this->ij[2][1] = fScaleZ * mRot.ij[2][1];
        this->ij[2][2] = fScaleZ * mRot.ij[2][2];

        this->ij[3][0] = fDispX;
        this->ij[3][1] = fDispY;
        this->ij[3][2] = fDispZ;
    }
};

    // TYPEDEFS
	// ---------------

    typedef QTransformationMatrix<QMatrix4x3> QTransformationMatrix4x3;
    typedef QTransformationMatrix<QMatrix4x4> QTransformationMatrix4x4;

    // CONSTANTS INITIALIZATION
    // -----------------------------

    template <class MatrixType>
    const QTransformationMatrix<MatrixType> QTransformationMatrix<MatrixType>::Identity(MatrixType::Identity);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSFORMATIONMATRIX__
