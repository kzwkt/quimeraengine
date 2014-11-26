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

#include "SQPoint.h"

#include "Assertions.h"
#include "SQFloat.h"
#include "SQAngle.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix4x3.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QSpaceConversionMatrix.h"


namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void SQPoint::Translate(const QBaseVector2 &vTranslation, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] += vTranslation;
    }
}

void SQPoint::Translate(const float_q fTranslationX, const float_q fTranslationY, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x += fTranslationX;
        arPoints[i].y += fTranslationY;
    }
}

void SQPoint::Rotate(const float_q fRotationAngle, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] = arPoints[i].Transform(fRotationAngle);
    }
}

void SQPoint::Scale(const QBaseVector2 &vScale, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] *= vScale;
    }
}

void SQPoint::Scale(const float_q fScaleX, const float_q fScaleY, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x *= fScaleX;
        arPoints[i].y *= fScaleY;
    }
}

void SQPoint::Transform(const QTransformationMatrix3x3 &transformation, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] = arPoints[i].Transform(transformation);
    }
}

void SQPoint::Translate(const QBaseVector3 &vTranslation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(vTranslation, arPoints[i]);
    }
}

void SQPoint::Translate(const QBaseVector3 &vTranslation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(vTranslation, arPoints[i]);
    }
}

void SQPoint::Translate(const float_q fTranslationX, const float_q fTranslationY, const float_q fTranslationZ, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
    }
}

void SQPoint::Translate(const float_q fTranslationX, const float_q fTranslationY, const float_q fTranslationZ, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
    }
}

void SQPoint::Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(translation, arPoints[i]);
    }
}

void SQPoint::Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(translation, arPoints[i]);
    }
}

void SQPoint::Translate(const QTranslationMatrix<QMatrix4x3> &translation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(translation, arPoints[i]);
    }
}

void SQPoint::Translate(const QTranslationMatrix<QMatrix4x4> &translation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Translate(translation, arPoints[i]);
    }
}

void SQPoint::Rotate(const QQuaternion &qRotation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Rotate(qRotation, arPoints[i]);
    }
}

void SQPoint::Rotate(const QQuaternion &qRotation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Rotate(qRotation, arPoints[i]);
    }
}

void SQPoint::Rotate(const QRotationMatrix3x3 &rotation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Rotate(rotation, arPoints[i]);
    }
}

void SQPoint::Rotate(const QRotationMatrix3x3 &rotation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Rotate(rotation, arPoints[i]);
    }
}

void SQPoint::Scale(const QBaseVector3 &vScale, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(vScale, arPoints[i]);
    }
}

void SQPoint::Scale(const QBaseVector3 &vScale, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(vScale, arPoints[i]);
    }
}

void SQPoint::Scale(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
    }
}

void SQPoint::Scale(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
    }
}

void SQPoint::Scale(const QScalingMatrix3x3 &scale, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(scale, arPoints[i]);
    }
}

void SQPoint::Scale(const QScalingMatrix3x3 &scale, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Scale(scale, arPoints[i]);
    }
}

void SQPoint::Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(transformation, arPoints[i]);
    }
}

void SQPoint::Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(transformation, arPoints[i]);
    }
}

void SQPoint::Transform(const QTransformationMatrix<QMatrix4x3> &transformation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(transformation, arPoints[i]);
    }
}

void SQPoint::Transform(const QTransformationMatrix<QMatrix4x4> &transformation, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(transformation, arPoints[i]);
    }
}

void SQPoint::Transform(const QSpaceConversionMatrix &spaceConversion, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(spaceConversion, arPoints[i]);
    }
}

void SQPoint::Transform(const QSpaceConversionMatrix &spaceConversion, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SQPoint::Transform(spaceConversion, arPoints[i]);
    }
}

void SQPoint::RotateWithPivot(const float_q fRotationAngle, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] = arPoints[i].Transform(fRotationAngle);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i].x *= fScaleX;
        arPoints[i].y *= fScaleY;

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const QBaseVector2 &vScale, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] *= vScale;

        arPoints[i] += vPivot;
    }
}

void SQPoint::TransformWithPivot(const QTransformationMatrix3x3 &transformation, const QBaseVector2 &vPivot, QVector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] = arPoints[i].Transform(transformation);

        arPoints[i] += vPivot;
    }
}

void SQPoint::RotateWithPivot(const QQuaternion &qRotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Rotate(qRotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::RotateWithPivot(const QQuaternion &qRotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Rotate(qRotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Rotate(rotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::RotateWithPivot(const QRotationMatrix3x3 &rotation, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Rotate(rotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const QBaseVector3& vScale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(vScale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const QBaseVector3 &vScale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(vScale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const QBaseVector3 &vPivot,
                                    QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const float_q fScaleX, const float_q fScaleY, const float_q fScaleZ, const QBaseVector4 &vPivot,
                                    QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector3 &vPivot, QVector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(scale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::ScaleWithPivot(const QScalingMatrix3x3 &scale, const QBaseVector4 &vPivot, QVector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Scale(scale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Transform(transformation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::TransformWithPivot(const QTransformationMatrix<QMatrix4x3> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x -= vPivot.x;
        arPoints[i].y -= vPivot.y;
        arPoints[i].z -= vPivot.z;

        SQPoint::Transform(transformation, arPoints[i]);

        arPoints[i].x += vPivot.x;
        arPoints[i].y += vPivot.y;
        arPoints[i].z += vPivot.z;
    }
}

void SQPoint::TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector3 &vPivot, QVector3* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SQPoint::Transform(transformation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SQPoint::TransformWithPivot(const QTransformationMatrix<QMatrix4x4> &transformation, const QBaseVector4 &vPivot, QVector4* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    QE_ASSERT_ERROR( arPoints != null_q, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x -= vPivot.x;
        arPoints[i].y -= vPivot.y;
        arPoints[i].z -= vPivot.z;

        SQPoint::Transform(transformation, arPoints[i]);

        arPoints[i].x += vPivot.x;
        arPoints[i].y += vPivot.y;
        arPoints[i].z += vPivot.z;
    }
}

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis
