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

#ifndef __QTRANSLATIONMATRIX__
#define __QTRANSLATIONMATRIX__

#include "QBaseVector3.h"
#include "QBaseVector4.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "SQFloat.h"
#include "QTransformationMatrix.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

template <class MatrixType>
class QTranslationMatrix;

// Preventing friend global operator to be called.
template <class MatrixType>
QTranslationMatrix<MatrixType> operator*(const float_q &fScalar, const QTranslationMatrix<MatrixType> &matrix);

/// <summary>
/// Class to represent a matrix that contains a displacement in the direction of each coordinate axis.
/// </summary>
/// <remarks>
/// It is an identity matrix with the elements \f$ a_{30}\f$, \f$ a_{31}\f$ and \f$ a_{32}\f$ replaced by the components of displacement:<br/>
/// <br/>
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$
/// </remarks>
/// <typeparam name="MatrixTypeParam">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
template <class MatrixType>
class QTranslationMatrix : public MatrixType
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    QTranslationMatrix()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The matrix from which we want to create a copy in the resident matrix.</param>
    QTranslationMatrix(const QTranslationMatrix<MatrixType> &matrix) : MatrixType(matrix)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a translation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix in which we want the resident matrix to be based.</param>
    QTranslationMatrix(const MatrixType &matrix) : MatrixType(matrix)
    {
    }

    /// <summary>
    /// Constructor that receives three floating point values, one for the displacement in each axis direction.
    /// </summary>
    /// <param name="fTranslationX">[IN] Displacement in X direction.</param>
    /// <param name="fTranslationY">[IN] Displacement in Y direction.</param>
    /// <param name="fTranslationZ">[IN] Displacement in Z direction.</param>
    QTranslationMatrix(const float_q fTranslationX, const float_q fTranslationY, const float_q fTranslationZ)
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
    explicit QTranslationMatrix(const QBaseVector3 &vTranslation)
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
    explicit QTranslationMatrix(const QBaseVector4 &vTranslation)
    {
        this->ResetToIdentity();

        this->ij[3][0] = vTranslation.x;
        this->ij[3][1] = vTranslation.y;
        this->ij[3][2] = vTranslation.z;
     }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Stores an identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:<br/>
    /// <br/>
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$<br/>
    /// <br/>
    /// If the matrix is 4x3, the fourth column is ignored.
    /// </remarks>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    static const QTranslationMatrix<MatrixType>& GetIdentity()
    {
        static const QTranslationMatrix<MatrixType> IDENTITY(MatrixType::GetIdentity());
        return IDENTITY;
    }


    // METHODS
    // ---------------
public:

    // Binary operators

    /// <summary>
    /// Multiplies a translation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// Since both are translation matrices, the product is calculated as follows:<br/>
    /// <br/>
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$<br/>
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTranslationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x3> &matrix) const
    {
        return ProductOperatorImp(matrix);
    }

    /// <summary>
    /// Multiplies a translation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// Since both are translation matrices, the product is calculated as follows:<br/>
    /// <br/>
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$<br/>
    /// <br/>
    /// This product is conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix, with the same template parameter that resident matrix.
    /// </returns>
    QTranslationMatrix<MatrixType> operator*(const QTranslationMatrix<QMatrix4x4> &matrix) const
    {
        return ProductOperatorImp(matrix);
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
    QTransformationMatrix<MatrixType> operator*(const QScalingMatrix3x3 &matrix) const
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
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// Rotation matrix is extended to a 4x4 matrix to allow this product.<br/>
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

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];

        return aux;
    }

    /// <summary>
    /// Product and assign operator. Multiplies the resident matrix and stores the result of the multiplication.
    /// </summary>
    /// <remarks>
    /// Since both are translation matrices, the product is calculated as follows:<br/>
    /// <br/>
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QTranslationMatrix<MatrixType>& operator*=(const QTranslationMatrix<QMatrix4x3> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Product and assign operator. Multiplies the resident matrix and stores the result of the multiplication.
    /// </summary>
    /// <remarks>
    /// Multiplies a translation matrix by the resident matrix. Since both are translation matrices, the product is calculated as follows:<br/>
    /// <br/>
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QTranslationMatrix<MatrixType>& operator*=(const QTranslationMatrix<QMatrix4x4> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a translation matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    QTranslationMatrix<MatrixType>& operator=(const MatrixType &matrix)
    {
        MatrixType::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Inverts the matrix.
    /// </summary>
    /// <remarks>
    /// In the case of translation matrices, the inverse is composed
    /// of the opposite of the elements which defines the displacement:<br/>
    /// <br/>
    /// \f$ T^{-1}= \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ -d_{x} & -d_{y} & -d_{z} & 1 \end{bmatrix}\f$<br/>
    /// <br/>
    /// So, it's faster than base class method.
    /// </summary>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    QTranslationMatrix<MatrixType> Invert() const
    {
        return QTranslationMatrix<MatrixType>(-this->ij[3][0], -this->ij[3][1], -this->ij[3][2]);
    }

    /// <summary>
    /// Calculates whether the matrix has inverse or not.
    /// </summary>
    /// <remarks>
    /// A matrix has inverse when its determinant doesn't equal zero.
    /// </remarks>
    /// <returns>
    /// True if the matrix has inverse, false otherwise.
    /// </returns>
    bool HasInverse() const
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
    void GetTranslation(float_q &fTranslationX, float_q &fTranslationY, float_q &fTranslationZ) const
    {
        fTranslationX = this->ij[3][0];
        fTranslationY = this->ij[3][1];
        fTranslationZ = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement.</param>
    void GetTranslation(QBaseVector3 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement. W component of this vector will be set to 0.</param>
    void GetTranslation(QBaseVector4 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
        vTranslation.w = SQFloat::_0;
    }

    /// <summary>
    /// Calculates the determinant of the matrix.
    /// </summary>
    /// <remarks>
    /// Since this is a translation matrix,
    /// which is a diagonal matrix with its main diagonal composed of 1s, its determinant is 1.
    /// </remarks>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_q GetDeterminant() const
    {
        return SQFloat::_1;
    }

private:

    // Preventing the operators from base class to be used.
    // using MatrixType::operator*; // Commented out to avoid cyclic dependency.
    using MatrixType::operator/;
    using MatrixType::operator+;
    using MatrixType::operator-;
    using MatrixType::operator*=;
    using MatrixType::operator/=;
    using MatrixType::operator+=;
    using MatrixType::operator-=;

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
    /// <typeparam name="MatrixTypeParam">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant translation matrix.
    /// </returns>
    template <class MatrixTypeParam>
    QTranslationMatrix<MatrixType> ProductOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix) const
    {
        return QTranslationMatrix<MatrixType>(this->ij[3][0] + matrix.ij[3][0],
                                              this->ij[3][1] + matrix.ij[3][1],
                                              this->ij[3][2] + matrix.ij[3][2]);
    }

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// Multiplies a translation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are translation matrices, the product is calculated as follows:
    ///
    /// \f$ \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x} & d_{1y} & d_{1z} & 1 \end{bmatrix}
    /// \cdot \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{2x} & d_{2y} & d_{2z} & 1 \end{bmatrix} =
    /// \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_{1x}+d_{2x} & d_{1y}+d_{2y} & d_{1z}+d_{2z} & 1 \end{bmatrix}\f$
    /// </summary>
    /// <typeparam name="MatrixTypeParam">Allowed types: QMatrix4x3, QMatrix4x4.</typeparam>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    template <class MatrixTypeParam>
    void ProductAssignationOperatorImp(const QTranslationMatrix<MatrixTypeParam> &matrix)
    {
        this->ij[3][0] += matrix.ij[3][0];
        this->ij[3][1] += matrix.ij[3][1];
        this->ij[3][2] += matrix.ij[3][2];
    }

    // Hidden method to prevent it could be used.
    void ResetToZero(){}
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

template class QE_LAYER_TOOLS_SYMBOLS QTranslationMatrix<Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3>;
template class QE_LAYER_TOOLS_SYMBOLS QTranslationMatrix<Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4>;

#endif // QE_EXPORT_TOOLS_TEMPLATE_SPECIALIZATION

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QTRANSLATIONMATRIX__
