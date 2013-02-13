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

#include "SQFloat.h"
#include "SQAngle.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QSpaceConversionMatrix.h"
#include "QQuaternion.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"

using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Helper class that will be used to perform transformations related to arrays of points (2D, 3D or 4D).
/// </summary>
class QDllExport SQPoint
{

	// CONSTRUCTORS
	// ---------------
private:

	inline SQPoint() { }

	// METHODS
	// ---------------
public:

    /// 2D TRANSFORMATIONS

	/// <summary>
	/// Translates 2D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 2D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector2 &vTranslation, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] += vTranslation;
        }
	}

	/// <summary>
	/// Translates 2D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, QVector2* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].x += fTranslationX;
            arPoints[i].y += fTranslationY;
        }
	}

	/// <summary>
	/// Rotates 2D points.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	static void Rotate(const float_q &fRotationAngle, QVector2* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] = arPoints[i].Transform(fRotationAngle);
        }
	}

	/// <summary>
	/// Scales 2D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 2D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector2 &vScale, QVector2* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] *= vScale;
        }
	}

	/// <summary>
	/// Scales 2D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q &fScaleX, const float_q &fScaleY, QVector2* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].x *= fScaleX;
            arPoints[i].y *= fScaleY;
        }
	}

	/// <summary>
	/// Transforms 2D points using a transformation matrix.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Transformation matrix that will be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix3x3 &transformation, QVector2* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] = arPoints[i].Transform(transformation);
        }
	}

	// 3D TRANSFORMATIONS

	/// <summary>
	/// Translates 3D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector3 &vTranslation, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(vTranslation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector3 &vTranslation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(vTranslation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(translation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(translation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(translation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points.<br>
	/// Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Translate(translation, arPoints[i]);
        }
	}

	/// <summary>
	/// Rotates 3D points.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QQuaternion &qRotation, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        SQPoint::Rotate(qRotation, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 4D points.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QQuaternion &qRotation, QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        SQPoint::Rotate(qRotation, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 3D points.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QRotationMatrix3x3 &rotation, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        SQPoint::Rotate(rotation, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 4D points.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QRotationMatrix3x3 &rotation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
	    {
	        SQPoint::Rotate(rotation, arPoints[i]);
	    }
	}

	/// <summary>
	/// Scales 3D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector3 &vScale, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(vScale, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector3 &vScale, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(vScale, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 3D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 3D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale matrix that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QScalingMatrix3x3 &scale, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(scale, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale matrix that contains the Scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QScalingMatrix3x3 &scale, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Scale(scale, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 3D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(transformation, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 3D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(transformation, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(transformation, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(transformation, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 3D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QSpaceConversionMatrix &spaceConversion, QVector3* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(spaceConversion, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QSpaceConversionMatrix &spaceConversion, QVector4* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            SQPoint::Transform(spaceConversion, arPoints[i]);
        }
	}

    /// <summary>
	/// Rotates 2D points, using the provided pivot as the center of transformation.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const float_q &fRotationAngle, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i] = arPoints[i].Transform(fRotationAngle);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 2D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the Y dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i].x *= fScaleX;
            arPoints[i].y *= fScaleY;

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 2D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i] *= vScale;

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 2D points, using the provided pivot as the center of transformation.<br>
	/// Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Transformation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i] = arPoints[i].Transform(transformation);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 3D points, using the provided pivot as the center of transformation.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QQuaternion &qRotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Rotate(qRotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 4D points, using the provided pivot as the center of transformation.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QQuaternion &qRotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Rotate(qRotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 3D points, using the provided pivot as the center of transformation.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Rotate(rotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 4D points, using the provided pivot as the center of transformation.<br>
	/// Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Rotate(rotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector3& vScale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(vScale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector3 &vScale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(vScale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q &fScaleX, const float_q  fScaleY, const float_q &fScaleZ, const QBaseVector3 &vPivot,
                                      QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, const QBaseVector4 &vPivot,
                                      QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(scale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation.<br>
	/// Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Scale(scale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 3D points, using the provided pivot as the center of transformation.<br>
	/// The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                          const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 4D points, using the provided pivot as the center of transformation.<br>
	/// The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                          const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 3D points, using the provided pivot as the center of transformation.<br>
	/// The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                          const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 4D points, using the provided pivot as the center of transformation.<br>
	/// The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                          const unsigned int &uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            SQPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

private:

	/// <summary>
	/// Translates 3D or 4D points.
	/// </summary>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
	template <class VectorType>
    inline static void Translate(const QBaseVector3 &vTranslation, VectorType &vPoint)
	{
	    vPoint.x += vTranslation.x;
	    vPoint.y += vTranslation.y;
	    vPoint.z += vTranslation.z;
	}

	/// <summary>
	/// Translates 3D or 4D points.
	/// </summary>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Floating point value that contains the translation to be applied on Z component.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
	template <class VectorType>
	inline static void Translate(const float_q &fTranslationX, const float_q &fTranslationY, const float_q &fTranslationZ, VectorType &vPoint)
	{
	    vPoint.x += fTranslationX;
	    vPoint.y += fTranslationY;
	    vPoint.z += fTranslationZ;
	}

	/// <summary>
	/// Translates 3D or 4D points.
	/// </summary>
    /// <param name="translation">[IN] 3x3 or 4x4 translation matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
	template <class MatrixType, class VectorType>
	inline static void Translate(const MatrixType &translation, VectorType &vPoint)
	{
        vPoint = vPoint.Transform(translation);
	}

	/// <summary>
	/// Rotates 3D or 4D points.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
	template <class VectorType>
	inline static void Rotate(const QQuaternion &qRotation, VectorType &vPoint)
	{
        vPoint = vPoint.Transform(qRotation);
	}

	/// <summary>
	/// Rotates 3D or 4D points.
	/// </summary>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
	template <class VectorType>
	inline static void Rotate(const QRotationMatrix3x3 &rotation, VectorType &vPoint)
	{
	    vPoint = vPoint.Transform(rotation);
	}

	/// <summary>
	/// Scales 3D or 4D points.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
	template <class VectorType>
    inline static void Scale(const QBaseVector3 &vScale, VectorType &vPoint)
	{
	    vPoint.x *= vScale.x;
	    vPoint.y *= vScale.y;
	    vPoint.z *= vScale.z;
	}

	/// <summary>
	/// Scales 3D or 4D points.
	/// </summary>
    /// <param name="fScaleX">[IN] Scalar value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Scalar value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Scalar value that contains the scale to be applied on Z component.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
	template <class VectorType>
	inline static void Scale(const float_q &fScaleX, const float_q &fScaleY, const float_q &fScaleZ, VectorType &vPoint)
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
    inline static void Scale(const QScalingMatrix3x3 &scale, VectorType &vPoint)
	{
	    vPoint = vPoint.Transform(scale);
	}

	/// <summary>
	/// Transforms 3D or 4D points.
	/// </summary>
    /// <param name="transformation">[IN] 4x3 or 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
	template <class MatrixType, class VectorType>
	inline static void Transform(const MatrixType &transformation, VectorType &vPoint)
	{
        vPoint = vPoint.Transform(transformation);
	}

	/// <summary>
	/// Transforms 3D or 4D points.
	/// </summary>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
	template <class VectorType>
	inline static void Transform(const QSpaceConversionMatrix &spaceConversion, VectorType &vPoint)
	{
        vPoint = vPoint.Transform(spaceConversion);
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQPOINT__
