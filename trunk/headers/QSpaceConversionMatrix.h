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

#ifndef __QSPACECONVERSIONMATRIX__
#define __QSPACECONVERSIONMATRIX__

#include "QVector3.h"
#include "QVector4.h"
#include "QBaseQuaternion.h"
#include "QMatrix4x4.h"
#include "QMatrix4x3.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;


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
template<class MatrixType> class QTransformationMatrix;
class QRotationMatrix3x3;
class QScalingMatrix3x3;


/// <summary>
/// Class representing a matrix which symbolizes coordinate system transformations.<br>
/// It adds functionality to change to view, projection and world spaces.
/// </summary>
class QDllExport QSpaceConversionMatrix : public QMatrix4x4
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    inline QSpaceConversionMatrix()
    {
        this->ResetToIdentity();
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The space conversion matrix from which we want to create a copy in the resident space conversion matrix.</param>
    inline QSpaceConversionMatrix(const QSpaceConversionMatrix &matrix) : QMatrix4x4(matrix)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The 4x4 matrix in which we want the resident space conversion matrix to be based.</param>
    inline QSpaceConversionMatrix(const QBaseMatrix4x4 &matrix) : QMatrix4x4(matrix)
    {
    }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assign operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a space conversion matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    inline QSpaceConversionMatrix& operator=(const QBaseMatrix4x4 &matrix)
    {
        QBaseMatrix4x4::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Multiplies a space conversion matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    QSpaceConversionMatrix operator*(const QSpaceConversionMatrix &matrix) const;


    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    QSpaceConversionMatrix& operator*=(const QSpaceConversionMatrix &matrix);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QBaseVector3 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QBaseVector4 &vTranslation, const QBaseQuaternion &qRotation, const QBaseVector3 &vScale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QTranslationMatrix<QMatrix4x3> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QTranslationMatrix<QMatrix4x4> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const QTransformationMatrix<QMatrix4x4> &translation, const QTransformationMatrix<QMatrix4x4> &rotation,
                             const QTransformationMatrix<QMatrix4x4> &scale);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction".</param>
    void SetViewSpaceMatrix(const QVector3 &vPointOfView, const QVector3 &vTarget, const QVector3 &vUpDirection);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction".</param>
    void SetViewSpaceMatrix(const QVector4 &vPointOfView, const QVector4 &vTarget, const QVector4 &vUpDirection);

    /// <summary>
    /// Sets the projection space matrix, which defines how perspective is applied to the scene.
    /// </summary>
    /// <param name="fNearClipPlane">[IN] Floating point value which defines the distance to the nearest clipping plane.</param>
    /// <param name="fFarClipPlane">[IN] Floating point value which defines the distance to the farthest clipping plane.</param>
    /// <param name="fAspectRatio">[IN] Floating point value which defines the frame width/height ratio.</param>
    /// <param name="fVerticalFOV">[IN] Floating point value which defines the vertical field of view.</param>
    void SetProjectionSpaceMatrix(const float_q &fNearClipPlane, const float_q &fFarClipPlane,
                                  const float_q &fAspectRatio, const float_q &fVerticalFOV);

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.<br>
    /// Remember that Quimera Engine works with left-hand convention by default.<br>
    /// To do that, we treat the world space matrix as a transformation matrix,
    /// inverting both rotation (by trasposing it) and z translation component.
    /// </summary>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    QSpaceConversionMatrix SwitchHandConventionWorldSpaceMatrix() const;

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.<br>
    /// Remember that Quimera Engine works with left-hand convention by default.<br>
    /// To do that, we invert the Z axis, and then the matrix is recalculated.
    /// </summary>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    QSpaceConversionMatrix SwitchHandConventionViewSpaceMatrix() const;

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.<br>
    /// Remember that Quimera Engine works with left-hand convention by default.<br>
    /// To do that, we change the sign of elements \f$ a_{22}\f$ and \f$ a_{23}\f$.
    /// </summary>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    inline QSpaceConversionMatrix SwitchHandConventionProjectionSpaceMatrix() const
    {
        QSpaceConversionMatrix switchedMatrix = *this;
        switchedMatrix.ij[2][2] = -this->ij[2][2];
        switchedMatrix.ij[2][3] = -this->ij[2][3];
        return switchedMatrix;
    }

protected:

    // Hidden method to prevent it could be used.
    void ResetToZero();

    // <summary>
    // Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    // </summary>
    // <param name="translation">[IN] Matrix which contains the translation (position).</param>
    // <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    // <param name="scale">[IN] Matrix which contains the scale (size).</param>
    template <class MatrixType>
    void SetWorldSpaceMatrixImp(const QTranslationMatrix<MatrixType> &translation, const QRotationMatrix3x3 &rotation, const QScalingMatrix3x3 &scale);
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QSPACECONVERSIONMATRIX__
