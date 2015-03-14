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

#ifndef __SQPOINT__
#define __SQPOINT__

#include "QBaseVector3.h"
#include "QQuaternion.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QSpaceConversionMatrix.h"

using Kinesis::QuimeraEngine::Common::DataTypes::float_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

// Forward declarations
// ---------------------
class QBaseVector2;
class QBaseVector4;
class QVector2;
class QVector3;
class QVector4;
class QMatrix4x3;
class QMatrix4x4;
template<class MatrixType> class QTransformationMatrix;
template<class MatrixType> class QTranslationMatrix;
class QTransformationMatrix3x3;


/// <summary>
/// Helper class that will be used to perform transformations related to arrays of points (2D, 3D or 4D).
/// </summary>
class QE_LAYER_TOOLS_SYMBOLS SQPoint
{

    // CONSTRUCTORS
    // ---------------
private:

    SQPoint() { }


    // METHODS
    // ---------------
public:

    /// 2D TRANSFORMATIONS

    /// <summary>
    /// Translates 2D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 2D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QBaseVector2 &vTranslation, QVector2* arPoints, const unsigned int& uElements);

    /// <summary>
    /// Translates 2D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 2D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const float_q &fRotationAngle, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 2D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 2D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const QBaseVector2 &vScale, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 2D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_q &fScaleX, const float_q &fScaleY, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 2D points using a transformation matrix.<br/>
    /// Transformation will be applied to all points in the array.
    /// </summary>
    /// <param name="transformation">[IN] Transformation matrix that will be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QTransformationMatrix3x3 &transformation, QVector2* arPoints, const unsigned int &uElements);

    // 3D TRANSFORMATIONS

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QBaseVector3 &vTranslation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QBaseVector3 &vTranslation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 3D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const QQuaternion &qRotation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 4D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const QQuaternion &qRotation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 3D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const QRotationMatrix3x3 &rotation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 4D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const QRotationMatrix3x3 &rotation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const QBaseVector3 &vScale, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const QBaseVector3 &vScale, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale matrix that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const QScalingMatrix3x3 &scale, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale matrix that contains the Scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const QScalingMatrix3x3 &scale, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QSpaceConversionMatrix &spaceConversion, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const QSpaceConversionMatrix &spaceConversion, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the Y dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Transformation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const QQuaternion &qRotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const QQuaternion &qRotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Rotates 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const QBaseVector3& vScale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const QBaseVector3 &vScale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_q &fScaleX, const float_q  fScaleY, const float_q &fScaleZ, const QBaseVector3 &vPivot,
                                      QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QBaseVector4 &vPivot,
                                      QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements);

    /// <summary>
    /// Transforms 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                          const unsigned int &uElements);

    /// <summary>
    /// Transforms 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                          const unsigned int &uElements);

    /// <summary>
    /// Transforms 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                          const unsigned int &uElements);

    /// <summary>
    /// Transforms 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                          const unsigned int &uElements);

private:

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class VectorType>
    static void Translate(const QBaseVector3 &vTranslation, VectorType &vPoint)
    {
        vPoint.x += vTranslation.x;
        vPoint.y += vTranslation.y;
        vPoint.z += vTranslation.z;
    }

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Floating point value that contains the translation to be applied on Z component.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class VectorType>
    static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, VectorType &vPoint)
    {
        vPoint.x += fTranslationX;
        vPoint.y += fTranslationY;
        vPoint.z += fTranslationZ;
    }

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="MatrixType">Allowed types: QTranslationMatrix<QMatrix4x3>, QTranslationMatrix<QMatrix4x4>.</typeparam>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="translation">[IN] 3x3 or 4x4 translation matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class MatrixType, class VectorType>
    static void Translate(const MatrixType &translation, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(translation);
    }

    /// <summary>
    /// Rotates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
    template <class VectorType>
    static void Rotate(const QQuaternion &qRotation, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(qRotation);
    }

    /// <summary>
    /// Rotates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
    template <class VectorType>
    static void Rotate(const QRotationMatrix3x3 &rotation, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(rotation);
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorType>
    static void Scale(const QBaseVector3 &vScale, VectorType &vPoint)
    {
        vPoint.x *= vScale.x;
        vPoint.y *= vScale.y;
        vPoint.z *= vScale.z;
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="fScaleX">[IN] Scalar value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Scalar value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Scalar value that contains the scale to be applied on Z component.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorType>
    static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, VectorType &vPoint)
    {
        vPoint.x *= fScaleX;
        vPoint.y *= fScaleY;
        vPoint.z *= fScaleZ;
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <param name="scale">[IN] Scale matrix that contains the scale to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorType>
    static void Scale(const QScalingMatrix3x3 &scale, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(scale);
    }

    /// <summary>
    /// Transforms 3D or 4D points.
    /// </summary>
    /// <typeparam name="MatrixType">Allowed types: QTransformationMatrix<QMatrix4x3>, QTransformationMatrix<QMatrix4x4>.</typeparam>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="transformation">[IN] 4x3 or 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
    template <class MatrixType, class VectorType>
    static void Transform(const MatrixType &transformation, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(transformation);
    }

    /// <summary>
    /// Transforms 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorType">Allowed types: QVector3, QVector4.</typeparam>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
    template <class VectorType>
    static void Transform(const QSpaceConversionMatrix &spaceConversion, VectorType &vPoint)
    {
        vPoint = vPoint.Transform(spaceConversion);
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQPOINT__
