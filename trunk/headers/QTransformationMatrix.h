//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#ifndef __QTRANSFORMATIONMATRIX__
#define __QTRANSFORMATIONMATRIX__

#include "QQuaternion.h"
#include "QScalingMatrix3x3.h"
#include "QRotationMatrix3x3.h"
#include "QVector3.h"

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
/// Class which represents a transformation matrix.<br>
/// A transformation matrix is, in general, composed of a scale, a rotation and a translation (or any combination of them).<br>
/// If we note:
///
/// \f$ S = \begin{bmatrix} s_x & 0 & 0 & 0 \\ 0 & s_y & 0 & 0 \\ 0 & 0 & s_z & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$,
///
/// \f$ R = \begin{bmatrix} r_{00} & r_{01} & r_{02} & 0 \\ r_{10} & r_{11} & r_{12} & 0 \\ r_{20} & r_{21} & r_{22} & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$, and
///
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$,
///
/// which are the scale matrix, the rotation matrix and the translation matrix respectively, we compose the transformation as follows:
///
/// \f$ SRT = \begin{bmatrix} s_x\dot r_{00} & s_x\dot r_{01} & s_x\dot r_{02} & 0 \\ s_y\dot r_{10} & s_y\dot r_{11} & s_y\dot r_{12} & 0 \\
/// s_z\dot r_{20} & s_z\dot r_{21} & s_z\dot r_{22} & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$
///
/// Since this class is a template, we allow the use of a 4x4 matrix or a 4x3 one as parameter.<br>
/// When parameter is a 4x3 matrix, we treat it as a 4x4 matrix, assuming that fourth column is:
///
/// \f$ \begin{bmatrix} 0 \\ 0 \\ 0 \\ 1 \end{bmatrix}\f$.
/// </summary>
template <class MatrixType>
class QDllExport QTransformationMatrix : public MatrixType
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    QTransformationMatrix() : MatrixType(QTransformationMatrix::GetIdentity())
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The matrix from which we want to create a copy in the resident matrix.</param>
    inline QTransformationMatrix(const QTransformationMatrix<MatrixType> &matrix) : MatrixType(matrix)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix in which we want the resident matrix to be based.</param>
    inline QTransformationMatrix(const MatrixType &matrix) : MatrixType(matrix)
    {
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 3D vector which stores the translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="qRotation">[IN] Quaternion with the rotation values. It's supposed to be normalized.</param>
    /// <param name="vScale">[IN] Vector with the scale values (where 1 means 100%).</param>
    inline QTransformationMatrix(const QBaseVector3 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale)
    {
        this->Initialize(vTranslation.x, vTranslation.y, vTranslation.z,
                         qRotation.x, qRotation.y, qRotation.z, qRotation.w,
                         vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 4D vector which stores the translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="qRotation">[IN] Quaternion with the rotation values. It's supposed to be normalized.</param>
    /// <param name="vScale">[IN] Vector with the scale values (where 1 means 100%).</param>
    inline QTransformationMatrix(const QBaseVector4 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale)
    {
        this->Initialize(vTranslation.x, vTranslation.y, vTranslation.z,
                         qRotation.x, qRotation.y, qRotation.z, qRotation.w,
                         vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor that receives three scaling values (where 1 means 100%), one for each axis direction, four rotation values
    /// which define a rotation quaternion and three displacement values which define a translation.
    /// </summary>
    /// <param name="fTranslationX">[IN] Displazament within X direction.</param>
    /// <param name="fTranslationY">[IN] Displazament within Y direction.</param>
    /// <param name="fTranslationZ">[IN] Displazament within Z direction.</param>
    /// <param name="fRotationX">[IN] X component of the rotation quaternion.</param>
    /// <param name="fRotationY">[IN] Y component of the rotation quaternion.</param>
    /// <param name="fRotationZ">[IN] Z component of the rotation quaternion.</param>
    /// <param name="fRotationw">[IN] W component of the rotation quaternion.</param>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    inline QTransformationMatrix(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ,
                                 const float_q &fRotationX, const float_q &fRotationY, const float_q &fRotationZ, const float_q &fRotationw,
                                 const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        this->Initialize(fTranslationX, fTranslationY, fTranslationZ,
                         fRotationX, fRotationY, fRotationZ, fRotationw,
                         fScaleX, fScaleY, fScaleZ);
    }

    /// <summary>
    /// Constructor from a translation matrix, a 3x3 rotation matrix and a 3x3 scale matrix.
    /// </summary>
    /// <param name="translation">[IN] A translation matrix.</param>
    /// <param name="rotation">[IN] A rotation matrix.</param>
    /// <param name="scale">[IN] A scale matrix.</param>
    QTransformationMatrix(const QTranslationMatrix<QMatrix4x3> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
    {
        QTransformationMatrixImp(translation, rotation, scale);
    }

    /// <summary>
    /// Constructor from a translation matrix, a 3x3 rotation matrix and a 3x3 scale matrix.
    /// </summary>
    /// <param name="translation">[IN] A translation matrix.</param>
    /// <param name="rotation">[IN] A rotation matrix.</param>
    /// <param name="scale">[IN] A scale matrix.</param>
    QTransformationMatrix(const QTranslationMatrix<QMatrix4x4> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
    {
        QTransformationMatrixImp(translation, rotation, scale);
    }

protected:

    // <summary>
    // Constructor from a 4x3 or 4x4 (depending on the constructor template parameter) translation matrix, a 3x3 rotation matrix and
    // a 3x3 scale matrix.
    // </summary>
    // <param name="translation">[IN] A translation matrix.</param>
    // <param name="rotation">[IN] A rotation matrix.</param>
    // <param name="scale">[IN] A scale matrix.</param>
    template <class MatrixTypeParam>
    void QTransformationMatrixImp(const QTranslationMatrix<MatrixTypeParam> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale)
    {
        this->ResetToIdentity();

        this->ij[0][0] = scale.ij[0][0] * rotation.ij[0][0];
        this->ij[0][1] = scale.ij[0][0] * rotation.ij[0][1];
        this->ij[0][2] = scale.ij[0][0] * rotation.ij[0][2];

        this->ij[1][0] = scale.ij[1][1] * rotation.ij[1][0];
        this->ij[1][1] = scale.ij[1][1] * rotation.ij[1][1];
        this->ij[1][2] = scale.ij[1][1] * rotation.ij[1][2];

        this->ij[2][0] = scale.ij[2][2] * rotation.ij[2][0];
        this->ij[2][1] = scale.ij[2][2] * rotation.ij[2][1];
        this->ij[2][2] = scale.ij[2][2] * rotation.ij[2][2];

        this->ij[3][0] = translation.ij[3][0];
        this->ij[3][1] = translation.ij[3][1];
        this->ij[3][2] = translation.ij[3][2];
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an identity matrix.<br>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:
    ///
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$
    ///
    /// </summary>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    inline static const QTransformationMatrix<MatrixType>& GetIdentity()
    {
        static const QTransformationMatrix<MatrixType> IDENTITY(MatrixType::GetIdentity());
        return IDENTITY;
    }


    // METHODS
    // ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<QMatrix4x3> &matrix) const
    {
        QTransformationMatrix<MatrixType> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix.<br>
    /// The product is calculated knowing that fourth column of is (0,0,0,1).
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTransformationMatrix<QMatrix4x4> &matrix) const
    {
        QTransformationMatrix<MatrixType> outMatrix;
        ProductOperatorImp<QMatrix4x4>(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a translation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const
    {
        QTransformationMatrix<MatrixType> outMatrix;
        ProductOperatorImp<QMatrix4x3>(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a translation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const
    {
        QTransformationMatrix<MatrixType> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.<br>
    /// The rotation matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QRotationMatrix3x3 &matrix) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules.<br>
    /// The scale matrix is extended to a 4x4 matrix to allow this product.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> operator*(const QScalingMatrix3x3 &matrix) const
    {
        QTransformationMatrix<MatrixType> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
        aux.ij[0][1] = this->ij[0][1] * matrix.ij[1][1];
        aux.ij[0][2] = this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0];
        aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
        aux.ij[1][2] = this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0];
        aux.ij[2][1] = this->ij[2][1] * matrix.ij[1][1];
        aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0];
        aux.ij[3][1] = this->ij[3][1] * matrix.ij[1][1];
        aux.ij[3][2] = this->ij[3][2] * matrix.ij[2][2];

        return aux;
    }

    // Assign operators

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.<br>
    /// Multiplies a transformation matrix by the resident matrix.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QTransformationMatrix<MatrixType>& operator*=(const QTransformationMatrix<QMatrix4x3> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.<br>
    /// Multiplies a transformation matrix by the resident matrix.<br>
    /// The product is calculated knowing that last column of matrices is (0,0,0,1).
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    inline QTransformationMatrix<MatrixType>& operator*=(const QTransformationMatrix<QMatrix4x4> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a transformation matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QTransformationMatrix<MatrixType>& operator=(const MatrixType &matrix)
    {
        MatrixType::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Calculates the determinant of the matrix.<br>
    /// Since this is a transformation matrix, its determinant can be calculated as
    /// if it was a 3x3 matrix, removing fourth row and fourth column in calculus :
    ///
    /// \f$ \left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{10}\cdot a_{21} -
    /// (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$
    ///
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_q GetDeterminant() const
    {
        return this->ij[0][0] * this->ij[1][1] * this->ij[2][2] +
               this->ij[0][1] * this->ij[1][2] * this->ij[2][0] +
               this->ij[0][2] * this->ij[1][0] * this->ij[2][1] -
               this->ij[0][2] * this->ij[1][1] * this->ij[2][0] -
               this->ij[0][0] * this->ij[1][2] * this->ij[2][1] -
               this->ij[0][1] * this->ij[1][0] * this->ij[2][2];
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
    /// Inverses the matrix.
    /// </summary>
    /// <remarks>
    /// This method is optimized with respect to the base matrix class so the fourth column is ignored. Take this into
    /// account when performing operations that include matrix transposing (use base matrix class version instead) or
    /// wrong results will be obtained.<br />
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:
    ///
    /// \f$ A\cdot A^{-1}  = A^{-1}\cdot A = I\f$
    ///
    /// We can calculate the inverse of any matrix by:
    ///
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^T_{ij}\f$,
    ///
    /// where \f$ C^T_{ij}\f$ is the matrix formed by each cofactor of each element of A, trasposed.<br>
    /// Since the matrix is a transformation matrix, then the inversion can be optimized avoiding all products by
    /// the elements of the fourth column.<br>
    /// Inverse has this general form, expressed in function of the scale, the rotation and the translation:
    ///
    /// \f$ (SRT)^{-1} = T^{-1}\cdot R^{-1}\cdot S^{-1} = \begin{bmatrix} \frac{r_{00}}{S_x} & \frac{r_{10}}{S_y} & \frac{r_{20}}{S_z} & 0 \\
    /// \frac{r_{01}}{S_x} & \frac{r_{11}}{S_y} & \frac{r_{21}}{S_z} & 0 \\
    /// \frac{r_{02}}{S_x} & \frac{r_{12}}{S_y} & \frac{r_{22}}{S_z} & 0 \\
    /// \frac{-r_{00}d_x-r_{01}d_y-r_{02}d_z}{S_x} & \frac{-r_{10}d_x-r_{11}d_y-r_{12}d_z}{S_y} & \frac{-r_{20}d_x-r_{21}d_y-r_{22}d_z}{S_z} & 1 \end{bmatrix} \f$
    /// </remarks>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    MatrixType Invert() const
    {
        // The results will be wrong when the determinant equals zero
        QE_ASSERT( this->GetDeterminant() != SQFloat::_0 );

        // Gets the inverse of the Determinant.
        const float_q INV_DET = SQFloat::_1 / this->GetDeterminant();

        // Binary products are stored in vars to avoid unnecesary repetitions
        const float_q& fA = this->ij[0][0] * this->ij[1][1];
        const float_q& fD = this->ij[2][1] * this->ij[3][0];
        const float_q& fE = this->ij[0][1] * this->ij[1][0];
        const float_q& fH = this->ij[2][0] * this->ij[3][1];
        const float_q& fJ = this->ij[2][1] * this->ij[3][2];
        const float_q& fK = this->ij[2][2] * this->ij[3][1];
        const float_q& fN = this->ij[2][0] * this->ij[3][2];
        const float_q& fO = this->ij[2][2] * this->ij[3][0];
        const float_q& fQ = this->ij[0][1] * this->ij[1][2];
        const float_q& fT = this->ij[0][2] * this->ij[1][1];
        const float_q& fU = this->ij[0][0] * this->ij[1][2];
        const float_q& fX = this->ij[0][2] * this->ij[1][0];

        MatrixType aux;

        aux = *this;

        // 1st column of inverse
        aux.ij[0][0] =  INV_DET * (this->ij[1][1] * this->ij[2][2] - this->ij[1][2] * this->ij[2][1] );
        aux.ij[1][0] = -INV_DET * (this->ij[1][0] * this->ij[2][2] - this->ij[1][2] * this->ij[2][0] );
        aux.ij[2][0] =  INV_DET * (this->ij[1][0] * this->ij[2][1] - this->ij[1][1] * this->ij[2][0] );
        aux.ij[3][0] = -INV_DET * (this->ij[1][0] * fJ + this->ij[1][1] * fO + this->ij[1][2] * fH -
                                   this->ij[1][2] * fD - this->ij[1][0] * fK - this->ij[1][1] * fN );

        // 2nd column of inverse
        aux.ij[0][1] = -INV_DET * (this->ij[0][1] * this->ij[2][2] - this->ij[0][2] * this->ij[2][1] );
        aux.ij[1][1] =  INV_DET * (this->ij[0][0] * this->ij[2][2] - this->ij[0][2] * this->ij[2][0] );
        aux.ij[2][1] = -INV_DET * (this->ij[0][0] * this->ij[2][1] - this->ij[0][1] * this->ij[2][0] );
        aux.ij[3][1] =  INV_DET * (this->ij[0][0] * fJ + this->ij[0][1] * fO + this->ij[0][2] * fH -
                                   this->ij[0][2] * fD - this->ij[0][0] * fK - this->ij[0][1] * fN );

        // 3rd column of inverse
        aux.ij[0][2] =  INV_DET * (fQ - fT);
        aux.ij[1][2] = -INV_DET * (fU - fX);
        aux.ij[2][2] =  INV_DET * (fA - fE);
        aux.ij[3][2] = -INV_DET * (fA * this->ij[3][2] + fQ * this->ij[3][0] + fX * this->ij[3][1] -
                                   fT * this->ij[3][0] - fU * this->ij[3][1] - fE * this->ij[3][2] );

        return aux;
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
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="fScaleX">[OUT] Resultant scale in X axis direction.</param>
    /// <param name="fScaleY">[OUT] Resultant scale in Y axis direction.</param>
    /// <param name="fScaleZ">[OUT] Resultant scale in Z axis direction.</param>
    inline void GetScale(float_q &fScaleX, float_q &fScaleY, float_q &fScaleZ) const
    {
        fScaleX = sqrt_q(this->ij[0][0] * this->ij[0][0] + this->ij[0][1] * this->ij[0][1] + this->ij[0][2] * this->ij[0][2]);
        fScaleY = sqrt_q(this->ij[1][0] * this->ij[1][0] + this->ij[1][1] * this->ij[1][1] + this->ij[1][2] * this->ij[1][2]);
        fScaleZ = sqrt_q(this->ij[2][0] * this->ij[2][0] + this->ij[2][1] * this->ij[2][1] + this->ij[2][2] * this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="vScale">[OUT] Vector where to store the scale factors.</param>
    inline void GetScale(QBaseVector3 &vScale) const
    {
        vScale.x = sqrt_q(this->ij[0][0] * this->ij[0][0] + this->ij[0][1] * this->ij[0][1] + this->ij[0][2] * this->ij[0][2]);
        vScale.y = sqrt_q(this->ij[1][0] * this->ij[1][0] + this->ij[1][1] * this->ij[1][1] + this->ij[1][2] * this->ij[1][2]);
        vScale.z = sqrt_q(this->ij[2][0] * this->ij[2][0] + this->ij[2][1] * this->ij[2][1] + this->ij[2][2] * this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining the Euler angles.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained angles don't match those used to build the matrix.
    /// </remarks>
    /// <param name="fRotationAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fRotationAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fRotationAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_q &fRotationAngleX, float_q &fRotationAngleY, float_q &fRotationAngleZ) const
    {
        QRotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(fRotationAngleX, fRotationAngleY, fRotationAngleZ);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining a rotation quaternion.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="qRotation">[OUT] Quaternion where to store the extracted rotation.</param>
    void GetRotation(QBaseQuaternion &qRotation) const
    {
        QRotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(qRotation.As<QQuaternion>());
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining an angle and a spin axis.
    /// </summary>
    /// <param name="fRotationAngle">[OUT] Angle of rotation.</param>
    /// <param name="vRotationAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_q &fRotationAngle, QBaseVector3 &vRotationAxis) const
    {
        QRotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(fRotationAngle, vRotationAxis);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="vTranslation">[OUT] Vector to store the translation.</param>
    /// <param name="qRotation">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    inline void Decompose(QBaseVector3 &vTranslation, QBaseQuaternion &qRotation, QBaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRotation);
        this->GetTranslation(vTranslation);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="vTranslation">[OUT] Vector to store the translation.</param>
    /// <param name="qRotation">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    inline void Decompose(QBaseVector4 &vTranslation, QBaseQuaternion &qRotation, QBaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRotation);
        this->GetTranslation(vTranslation);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(QTransformationMatrix<QMatrix4x3> &translation,
                   QTransformationMatrix<QMatrix4x3> &rotation,
                   QTransformationMatrix<QMatrix4x3> &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(QTransformationMatrix<QMatrix4x4> &translation,
                   QTransformationMatrix<QMatrix4x4> &rotation,
                   QTransformationMatrix<QMatrix4x4> &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(QTranslationMatrix<QMatrix4x3> &translation,
                   QRotationMatrix3x3 &rotation,
                   QScalingMatrix3x3 &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(QTranslationMatrix<QMatrix4x4> &translation,
                   QRotationMatrix3x3 &rotation,
                   QScalingMatrix3x3 &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.<br>
	/// Remember that Quimera Engine works with left-hand convention by default.<br>
	/// To do that, we invert both rotation (by trasposing it) and z translation component.
    /// </summary>
    /// <returns>
    /// The converted matrix.
    /// </returns>
    QTransformationMatrix<MatrixType> SwitchHandConvention() const
    {
        QVector3 vScale;
        this->GetScale(vScale);

        QE_ASSERT(vScale.x != SQFloat::_0 && vScale.y != SQFloat::_0 && vScale.z != SQFloat::_0)

        QVector3 vInvScale = QVector3::GetVectorOfOnes() / vScale;

        // Rotation correction
        QTransformationMatrix<MatrixType> switchedMatrix = *this;
        switchedMatrix.ij[0][1] = this->ij[1][0] * vInvScale.y;
        switchedMatrix.ij[1][0] = this->ij[0][1] * vInvScale.x;
        switchedMatrix.ij[0][2] = this->ij[2][0] * vInvScale.z;
        switchedMatrix.ij[2][0] = this->ij[0][2] * vInvScale.x;
        switchedMatrix.ij[2][1] = this->ij[1][2] * vInvScale.y;
        switchedMatrix.ij[1][2] = this->ij[2][1] * vInvScale.z;

        // Scale correction
        switchedMatrix.ij[0][1] *= vScale.x;
        switchedMatrix.ij[1][0] *= vScale.y;
        switchedMatrix.ij[0][2] *= vScale.x;
        switchedMatrix.ij[2][0] *= vScale.z;
        switchedMatrix.ij[2][1] *= vScale.z;
        switchedMatrix.ij[1][2] *= vScale.y;

        // Translation correction
        switchedMatrix.ij[3][2] = -this->ij[3][2];

        return switchedMatrix;
    }

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

    // Function to convert the 3x3 submatrix which contains the rotation and the scale into
    // a 3x3 rotation matrix without the scale. It uses the fact that in a 3x3 rotation matrix,
    // the length of any row o column vector is 1, so current length of each row in the transformation matrix
    // is the scale factor (each row have a scale factor which matches with an axis).
    // Dividing each row by its length we obtain the original rotation matrix.
    QRotationMatrix3x3 ToRotationMatrix3x3() const
    {
        QVector3 vScale;
        this->GetScale(vScale);

        QE_ASSERT( !vScale.IsZero() )

        QVector3 vInvScale = QVector3::GetVectorOfOnes() / vScale;

        return QRotationMatrix3x3(QMatrix3x3(this->ij[0][0] * vInvScale.x, this->ij[0][1] * vInvScale.x, this->ij[0][2] * vInvScale.x,
                                             this->ij[1][0] * vInvScale.y, this->ij[1][1] * vInvScale.y, this->ij[1][2] * vInvScale.y,
                                             this->ij[2][0] * vInvScale.z, this->ij[2][1] * vInvScale.z, this->ij[2][2] * vInvScale.z));
    }

    // <summary>
    // Initializes the transformation matrix from the components of a scale vector,
    // a rotation quaternion and a translation vector.
    // </summary>
    // <param name="fTranslationX">[IN] Displazament within X direction.</param>
    // <param name="fTranslationY">[IN] Displazament within Y direction.</param>
    // <param name="fTranslationZ">[IN] Displazament within Z direction.</param>
    // <param name="fRotationX">[IN] X component of the rotation quaternion.</param>
    // <param name="fRotationY">[IN] Y component of the rotation quaternion.</param>
    // <param name="fRotationZ">[IN] Z component of the rotation quaternion.</param>
    // <param name="fRotationW">[IN] W component of the rotation quaternion.</param>
    // <param name="fScaleX">[IN] Scale within X direction.</param>
    // <param name="fScaleY">[IN] Scale within Y direction.</param>
    // <param name="fScaleZ">[IN] Scale within Z direction.</param>
    void Initialize(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ,
                    const float_q &fRotationX, const float_q &fRotationY, const float_q &fRotationZ, const float_q &fRotationW,
                    const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ)
    {
        QQuaternion qRot(fRotationX, fRotationY, fRotationZ, fRotationW);

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

        this->ij[3][0] = fTranslationX;
        this->ij[3][1] = fTranslationY;
        this->ij[3][2] = fTranslationZ;
    }


    // <summary>
    // Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    // 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    // knowing that fourth column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    // </summary>
    // <remarks>
    // This product is not conmmutative.
    // </remarks>
    // <param name="matrix">[IN] Matrix to be multiplied by.</param>
    // <param name="outMatrix">[OUT] Resultant matrix.</param>
    template <class MatrixTypeParam>
    void ProductOperatorImp(const QTransformationMatrix<MatrixTypeParam> &matrix, QTransformationMatrix<MatrixType> &outMatrix) const
    {
        outMatrix = *this;

        outMatrix.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        outMatrix.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        outMatrix.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        outMatrix.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        outMatrix.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        outMatrix.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        outMatrix.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        outMatrix.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        outMatrix.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        outMatrix.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        outMatrix.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        outMatrix.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];
    }

    // <summary>
    // Multiplies a 4x4 or 4x3 (depending on the method template parameter) translation matrix by the current matrix,
    // following matrices product rules.
    // </summary>
    // <remarks>
    // This product is not conmmutative.
    // </remarks>
    // <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    // <param name="outMatrix">[OUT] Resultant matrix.</param>
    template <class MatrixTypeParam>
    inline void ProductOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix, QTransformationMatrix<MatrixType> &outMatrix) const
    {
        outMatrix = *this;

        outMatrix.ij[3][0] += matrix.ij[3][0];
        outMatrix.ij[3][1] += matrix.ij[3][1];
        outMatrix.ij[3][2] += matrix.ij[3][2];
    }

    // <summary>
    // Product and assign operator. Current matrix stores the result of the multiplication.
    // Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    // 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    // knowing that last column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    // </summary>
    // <param name="matrix">[IN] The matrix to be multiplied by.</param>
    template <class MatrixTypeParam>
    inline void ProductAssignationOperatorImp(const QTransformationMatrix<MatrixTypeParam> &matrix)
    {
        QTransformationMatrix<MatrixType> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];

        *this = aux;
    }

    // <summary>
    // Extracts the scale, the rotation and the translation into separated transformation matrices.
    // They can be 4x3 or 4x4 matrices, depending on the method template parameter.
    // </summary>
    // <param name="translation">[OUT] Matrix to store the translation.</param>
    // <param name="rotation">[OUT] Matrix to store the rotation.</param>
    // <param name="scale">[OUT] Matrix to store the scale.</param>
    template <class MatrixTypeParam>
    void DecomposeImp(QTransformationMatrix<MatrixTypeParam> &translation,
                      QTransformationMatrix<MatrixTypeParam> &rotation,
                      QTransformationMatrix<MatrixTypeParam> &scale) const
    {
        QBaseVector3 vAux;
        this->GetScale(vAux);

        scale.ResetToIdentity();

        scale.ij[0][0] = vAux.x;
        scale.ij[1][1] = vAux.y;
        scale.ij[2][2] = vAux.z;

        QBaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        rotation = QTransformationMatrix<MatrixTypeParam>(SQFloat::_0, SQFloat::_0, SQFloat::_0,
                                                          qRotAux.x , qRotAux.y , qRotAux.z , qRotAux.w,
                                                          SQFloat::_1, SQFloat::_1, SQFloat::_1);
        this->GetTranslation(vAux);

        translation.ResetToIdentity();

        translation.ij[3][0] = vAux.x;
        translation.ij[3][1] = vAux.y;
        translation.ij[3][2] = vAux.z;
    }

    // <summary>
    // Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    // The translation matrix can be 4x3 or 4x4 matrix, depending on the method template parameter.
    // </summary>
    // <param name="translation">[OUT] Matrix to store the translation.</param>
    // <param name="rotation">[OUT] Matrix to store the rotation.</param>
    // <param name="scale">[OUT] Matrix to store the scale.</param>
    template <class MatrixTypeParam>
    void DecomposeImp(QTranslationMatrix<MatrixTypeParam> &translation,
                      QRotationMatrix3x3 &rotation,
                      QScalingMatrix3x3 &scale) const
    {
        QBaseVector3 vAux;
        this->GetScale(vAux);

        scale.ResetToIdentity();

        scale.ij[0][0] = vAux.x;
        scale.ij[1][1] = vAux.y;
        scale.ij[2][2] = vAux.z;

        QBaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        rotation = QRotationMatrix3x3 (qRotAux);

        this->GetTranslation(vAux);

        translation.ResetToIdentity();

        translation.ij[3][0] = vAux.x;
        translation.ij[3][1] = vAux.y;
        translation.ij[3][2] = vAux.z;
    }

};


} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSFORMATIONMATRIX__
