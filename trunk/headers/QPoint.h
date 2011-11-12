// [TERMS&CONDITIONS]

#ifndef __QPOINT__
#define __QPOINT__

#include "QFloat.h"
#include "QAngle.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QSpaceConversionMatrix.h"
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

/// <summary>
/// Helper class that will be used to perform transformations related to arrays of points (2D, 3D or 4D).
/// </summary>
class QDllExport QPoint
{

	// CONSTRUCTORS
	// ---------------
private:

	inline QPoint() { }

	// METHODS
	// ---------------
public:

    /// 2D TRANSFORMATIONS

	/// <summary>
	/// Translates 2D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 2D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector2& vTranslation, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] += vTranslation;
        }
	}

	/// <summary>
	/// Translates 2D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslateX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslateY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q& fTranslateX, const float_q& fTranslateY, QVector2* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].x += fTranslateX;
            arPoints[i].y += fTranslateY;
        }
	}

	/// <summary>
	/// Rotates 2D points. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="fAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	static void Rotate(const float_q& fAngle, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].Transform(fAngle);
        }
	}

	/// <summary>
	/// Scales 2D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 2D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector2& vScale, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] *= vScale;
        }
	}

	/// <summary>
	/// Scales 2D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q& fScaleX, const float_q& fScaleY, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].x *= fScaleX;
            arPoints[i].y *= fScaleY;
        }
	}

	/// <summary>
	/// Transforms 2D points using a transformation matrix. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Transformation matrix that will be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix3x3& matrix, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i].Transform(matrix);
        }
	}

	/// 3D TRANSFORMATIONS

	/// <summary>
	/// Translates 3D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector3& vTranslation, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(vTranslation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QBaseVector3& vTranslation, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(vTranslation, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslateY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslateZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="fTranslateX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslateY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslateZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(fTranslateX, fTranslateY, fTranslateZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x3 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x3>& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 3D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x4 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x4>& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x3 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x3>& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Translates 4D points. Translation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x4 matrix that contains the translation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Translate(const QTranslationMatrix<QMatrix4x4>& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Translate(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Rotates 3D points. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="q">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QQuaternion& q, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        QPoint::Rotate(q, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 4D points. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="q">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QQuaternion& q, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        QPoint::Rotate(q, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 3D points. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QRotationMatrix3x3& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
	    {
	        QPoint::Rotate(matrix, arPoints[i]);
	    }
	}

	/// <summary>
	/// Rotates 4D points. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Rotate(const QRotationMatrix3x3& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
	    {
	        QPoint::Rotate(matrix, arPoints[i]);
	    }
	}

	/// <summary>
	/// Scales 3D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector3& vScale, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(vScale, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QBaseVector3& vScale, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(vScale, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 3D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 3D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Scale matrix that contains the scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QScaleMatrix3x3& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Scales 4D points. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Scale matrix that contains the Scale to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Scale(const QScaleMatrix3x3& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Scale(matrix, arPoints[i]);
        }
	}


	/// <summary>
	/// Transforms 3D points. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x3 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x3>& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 3D points. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x4>& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points. Transformation will be applied to all points in the array.
	/// </summary>int& uElements
    /// <param name="matrix">[IN] 4x3 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x3>& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QTransformationMatrix<QMatrix4x4>& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 3D points. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QSpaceConversionMatrix& matrix, QVector3* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

	/// <summary>
	/// Transforms 4D points. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="matrix">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void Transform(const QSpaceConversionMatrix& matrix, QVector4* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            QPoint::Transform(matrix, arPoints[i]);
        }
	}

    /// <summary>
	/// Rotates 2D points, using the provided pivot as the center of transformation. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="fAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const float_q& fAngle, const QBaseVector2& vPivot, QVector2* arPoints, const unsigned int& uElements)
	{
        for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i].Transform(fAngle);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 2D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the Y dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const QBaseVector2& vPivot, QVector2* arPoints, const unsigned int& uElements)
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
	/// Scales 2D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector2& vScale, const QBaseVector2& vPivot, QVector2* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i] *= vScale;

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 2D points, using the provided pivot as the center of transformation. Transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Transformation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix3x3& transformation, const QBaseVector2& vPivot, QVector2* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            arPoints[i].Transform(transformation);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 3D points, using the provided pivot as the center of transformation. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QQuaternion& qRotation, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Rotate(qRotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 4D points, using the provided pivot as the center of transformation. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QQuaternion& qRotation, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Rotate(qRotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 3D points, using the provided pivot as the center of transformation. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QRotationMatrix3x3& rotation, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Rotate(rotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

	/// <summary>
	/// Rotates 4D points, using the provided pivot as the center of transformation. Rotation will be applied to all points in the array.
	/// </summary>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void RotateWithPivot(const QRotationMatrix3x3& rotation, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Rotate(rotation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector3& vScale, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(vScale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QBaseVector3& vScale, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(vScale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 3D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QScaleMatrix3x3& scale, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(scale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Scales 4D points, using the provided pivot as the center of transformation. Scale will be applied to all points in the array.
	/// </summary>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void ScaleWithPivot(const QScaleMatrix3x3& scale, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Scale(scale, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 3D points, using the provided pivot as the center of transformation. The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix4x3& transformation, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 4D points, using the provided pivot as the center of transformation. The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix4x3& transformation, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 3D points, using the provided pivot as the center of transformation. The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix4x4& transformation, const QBaseVector3& vPivot, QVector3* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Transform(transformation, arPoints[i]);

            arPoints[i] += vPivot;
        }
	}

    /// <summary>
	/// Transforms 4D points, using the provided pivot as the center of transformation. The transformation will be applied to all points in the array.
	/// </summary>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
	/// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed.</param>
	/// <param name="uElements">[IN] Number of elements in the array.</param>
	inline static void TransformWithPivot(const QTransformationMatrix4x4& transformation, const QBaseVector4& vPivot, QVector4* arPoints, const unsigned int& uElements)
	{
	    for(unsigned int i = 0; i < uElements; ++i)
        {
            arPoints[i] -= vPivot;

            QPoint::Transform(transformation, arPoints[i]);

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
    inline static void Translate(const QBaseVector3& vTranslation, VectorType& vPoint)
	{
	    vPoint.x += vTranslation.x;
	    vPoint.y += vTranslation.y;
	    vPoint.z += vTranslation.z;
	}

	/// <summary>
	/// Translates 3D or 4D points.
	/// </summary>
    /// <param name="fTranslateX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslateY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslateZ">[IN] Floating point value that contains the translation to be applied on Z component.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
	template <class VectorType>
	inline static void Translate(const float_q& fTranslateX, const float_q& fTranslateY, const float_q& fTranslateZ, VectorType& vPoint)
	{
	    vPoint.x += fTranslateX;
	    vPoint.y += fTranslateY;
	    vPoint.z += fTranslateZ;
	}

	/// <summary>
	/// Translates 3D or 4D points.
	/// </summary>
    /// <param name="matrix">[IN] 3x3 or 4x4 translation matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
	template <class MatrixType, class VectorType>
	inline static void Translate(const MatrixType& matrix, VectorType& vPoint)
	{
        vPoint.Transform(matrix);
	}

	/// <summary>
	/// Rotates 3D or 4D points.
	/// </summary>
    /// <param name="q">[IN] Quaternion that contains the rotation to be done.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
	template <class VectorType>
	inline static void Rotate(const QQuaternion& q, VectorType& vPoint)
	{
        vPoint.Transform(q);
	}

	/// <summary>
	/// Rotates 3D or 4D points.
	/// </summary>
    /// <param name="matrix">[IN] Rotation matrix that contains the rotation to be done.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
	template <class VectorType>
	inline static void Rotate(const QRotationMatrix3x3& matrix, VectorType& vPoint)
	{
	    vPoint.Transform(matrix);
	}

	/// <summary>
	/// Scales 3D or 4D points.
	/// </summary>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
	template <class VectorType>
    inline static void Scale(const QBaseVector3& vScale, VectorType& vPoint)
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
	inline static void Scale(const float_q& fScaleX, const float_q& fScaleY, const float_q& fScaleZ, VectorType& vPoint)
	{
	    vPoint.x *= fScaleX;
	    vPoint.y *= fScaleY;
	    vPoint.z *= fScaleZ;
	}

	/// <summary>
	/// Scales 3D or 4D points.
	/// </summary>
    /// <param name="matrix">[IN] Scale matrix that contains the scale to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
	template <class VectorType>
    inline static void Scale(const QScaleMatrix3x3& matrix, VectorType& vPoint)
	{
	    vPoint.Transform(matrix);
	}

	/// <summary>
	/// Transforms 3D or 4D points.
	/// </summary>
    /// <param name="matrix">[IN] 4x3 or 4x4 matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
	template <class MatrixType, class VectorType>
	inline static void Transform(const MatrixType& matrix, VectorType& vPoint)
	{
        vPoint.Transform(matrix);
	}

	/// <summary>
	/// Transforms 3D or 4D points.
	/// </summary>
    /// <param name="matrix">[IN] Space conversion matrix that contains the transformation to be applied.</param>
	/// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
	template <class VectorType>
	inline static void Transform(const QSpaceConversionMatrix& matrix, VectorType& vPoint)
	{
        vPoint.Transform(matrix);
	}
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QPOINT__
