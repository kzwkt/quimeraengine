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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQPoint.h"
#include "QTransformationMatrix3x3.h"
#include "SQFloat.h"
#include "QVector2.h"
#include "QVector3.h"
#include "QVector4.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "SQAngle.h"
#include "QTransformationMatrix.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QQuaternion.h"
#include "QSpaceConversionMatrix.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::Math::SQPoint;
using Kinesis::QuimeraEngine::Tools::Math::QBaseVector2;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
using Kinesis::QuimeraEngine::Tools::Math::QVector3;
using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
using Kinesis::QuimeraEngine::Tools::Math::QVector4;


QTEST_SUITE_BEGIN( SQPoint_TestSuite )

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                           QVector2(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7),
                                           QVector2(SQFloat::_0, SQFloat::_8)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_5),
                                   QVector2(-SQFloat::_1, SQFloat::_10)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                           QVector2(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7),
                                           QVector2(SQFloat::_0, SQFloat::_8)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_5),
                                   QVector2(-SQFloat::_1, SQFloat::_10)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 TRANSLATION(SQFloat::_1, -SQFloat::_2);

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Rotate1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_1, SQFloat::_0),
                                           QVector2(SQFloat::_0, SQFloat::_1),
                                           QVector2(-SQFloat::_4, -SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_1, SQFloat::_0),
                                   QVector2(-SQFloat::_4, SQFloat::_4)
                               };

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Rotate1_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_1, SQFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Rotate1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Rotate1_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_0, SQFloat::_3),
                                           QVector2(SQFloat::_0_5, -SQFloat::_9),
                                           QVector2(-SQFloat::_2, SQFloat::_6)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_3),
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_2, -SQFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_0, SQFloat::_3),
                                           QVector2(SQFloat::_0_5, -SQFloat::_9),
                                           QVector2(-SQFloat::_2, SQFloat::_6)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_3),
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_2, -SQFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_0_5, SQFloat::_3),
                                           QVector2(SQFloat::_3 + SQFloat::_0_5, SQFloat::_3 + SQFloat::_0_5),
                                           QVector2(-SQFloat::_4, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_5),
                                   QVector2(-SQFloat::_1, SQFloat::_10)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform1_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_0_5, SQFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform1_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                                           QVector3(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3),
                                           QVector3(SQFloat::_0, SQFloat::_8, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_2),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0),
                                   QVector3(-SQFloat::_1, SQFloat::_10, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_1, SQFloat::_0),
                                           QVector4(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3, SQFloat::_0),
                                           QVector4(SQFloat::_0, SQFloat::_8, SQFloat::_4, SQFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_2, SQFloat::_0),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0, SQFloat::_0),
                                   QVector4(-SQFloat::_1, SQFloat::_10, SQFloat::_1, SQFloat::_0)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_2, SQFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_1, SQFloat::_0),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_0),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_0),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                                           QVector3(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3),
                                           QVector3(SQFloat::_0, SQFloat::_8, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_2),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0),
                                   QVector3(-SQFloat::_1, SQFloat::_10, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_1, SQFloat::_0),
                                           QVector4(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3, SQFloat::_0),
                                           QVector4(SQFloat::_0, SQFloat::_8, SQFloat::_4, SQFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_2, SQFloat::_0),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0, SQFloat::_0),
                                   QVector4(-SQFloat::_1, SQFloat::_10, SQFloat::_1, SQFloat::_0)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_2, SQFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_1, SQFloat::_0),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_0),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_0),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                                           QVector3(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3),
                                           QVector3(SQFloat::_0, SQFloat::_8, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_2),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0),
                                   QVector3(-SQFloat::_1, SQFloat::_10, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate7_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate7_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate8_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                                           QVector3(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3),
                                           QVector3(SQFloat::_0, SQFloat::_8, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_2),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0),
                                   QVector3(-SQFloat::_1, SQFloat::_10, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate8_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, -SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate8_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate9_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                           QVector4(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3, SQFloat::_1),
                                           QVector4(SQFloat::_0, SQFloat::_8, SQFloat::_4, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_2, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_10, SQFloat::_1, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate9_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_2, SQFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate9_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate9_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Translate10_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                           QVector4(SQFloat::_0_25 + SQFloat::_1, -SQFloat::_7, SQFloat::_3, SQFloat::_1),
                                           QVector4(SQFloat::_0, SQFloat::_8, SQFloat::_4, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_2, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, SQFloat::_0, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_10, SQFloat::_1, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Translate10_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_2, SQFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, -SQFloat::_1, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Translate10_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_1, -SQFloat::_1, SQFloat::_3, SQFloat::_1),
                               };

	// [Execution]
    SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Translate10_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Rotate2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1),
                                   QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2),
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);


	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Rotate2_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Rotate2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Rotate2_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Rotate3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                   QVector4(SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1),
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);


	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Rotate3_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Rotate3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Rotate3_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Rotate4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1),
                                   QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2),
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);


	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Rotate4_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Rotate4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Rotate4_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Rotate5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                   QVector4(SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1),
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);


	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Rotate5_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Rotate5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Rotate5_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_6, -SQFloat::_2, -SQFloat::_0),
                                           QVector3(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4),
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_6, -SQFloat::_2, -SQFloat::_0, SQFloat::_1),
                                           QVector4(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4, SQFloat::_1),
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_6, -SQFloat::_2, -SQFloat::_0),
                                           QVector3(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4),
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_1, -SQFloat::_1, SQFloat::_3),
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_6, -SQFloat::_2, -SQFloat::_0, SQFloat::_1),
                                           QVector4(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4, SQFloat::_1),
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_6, -SQFloat::_2, -SQFloat::_0),
                                           QVector3(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4),
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale7_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale7_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Scale8_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_6, -SQFloat::_2, -SQFloat::_0, SQFloat::_1),
                                           QVector4(SQFloat::_0_25 + SQFloat::_0_5, SQFloat::_10, SQFloat::_4, SQFloat::_1),
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Scale8_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_3, -SQFloat::_8, -SQFloat::_2, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Scale8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Scale8_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)3.7677669529663689,  SQFloat::_4,  (float_q)-8.4748737341529168),
                                           QVector3((float_q)-8.6507958916223728, SQFloat::_3,  (float_q)4.5624075439740519),
                                           QVector3((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform2_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)10.662058069535208, (float_q)4.5, (float_q)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform2_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)3.7677669529663689,  SQFloat::_4,  (float_q)-8.4748737341529168),
                                           QVector3((float_q)-8.6507958916223728, SQFloat::_3,  (float_q)4.5624075439740519),
                                           QVector3((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform3_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)10.662058069535208, (float_q)4.5, (float_q)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform3_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)3.7677669529663689,  SQFloat::_4,  (float_q)-8.4748737341529168, SQFloat::_1),
                                           QVector4((float_q)-8.6507958916223728, SQFloat::_3,  (float_q)4.5624075439740519,  SQFloat::_1),
                                           QVector4((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933, SQFloat::_1)
                                       };

    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform4_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform4_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)3.7677669529663689,  SQFloat::_4,  (float_q)-8.4748737341529168, SQFloat::_1),
                                           QVector4((float_q)-8.6507958916223728, SQFloat::_3,  (float_q)4.5624075439740519,  SQFloat::_1),
                                           QVector4((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform5_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)10.662058069535208,  (float_q)4.5, (float_q)-14.308504678941933, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform5_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)-2.2360679774997898, (float_q)0.74535599249992979, (float_q)2.333333333333333),
                                           QVector3((float_q)-1.1180339887498949, (float_q)-2.6087459737497545, (float_q)7.5833333333333321),
                                           QVector3((float_q)0.67082039324993692, (float_q)3.577708763999663,   SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform6_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)0.67082039324993692, (float_q)3.577708763999663, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform6_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector3* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( Transform7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)-2.2360679774997898, (float_q)0.74535599249992979, (float_q)2.333333333333333,  SQFloat::_1),
                                           QVector4((float_q)-1.1180339887498949, (float_q)-2.6087459737497545, (float_q)7.5833333333333321, SQFloat::_1),
                                           QVector4((float_q)0.67082039324993692, (float_q)3.577708763999663,   SQFloat::_1,                 SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( Transform7_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)0.67082039324993692, (float_q)3.577708763999663, SQFloat::_1, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( Transform7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };

	// [Execution]
    SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( Transform7_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    QSpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    QVector4* arInputPoints = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_1, SQFloat::_0),
                                           QVector2(SQFloat::_2, SQFloat::_1),
                                           QVector2(-SQFloat::_2, -SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_1, SQFloat::_0),
                                   QVector2(-SQFloat::_4, SQFloat::_4)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_2, -SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(-SQFloat::_4, SQFloat::_4)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( RotateWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( RotateWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q ROTATION = SQAngle::_HalfPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q ROTATION = SQAngle::_90;
#endif

    QVector2* arInputPoints = null_q;
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_1, SQFloat::_1),
                                           QVector2(-SQFloat::_0_5, (float_q)-11.0),
                                           QVector2(-SQFloat::_3, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_3),
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_3, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2* arInputPoints = null_q;
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_1, SQFloat::_1),
                                           QVector2(-SQFloat::_0_5, (float_q)-11.0),
                                           QVector2(-SQFloat::_3, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_3),
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_3, SQFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(-SQFloat::_1, SQFloat::_2)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector2 SCALE(SQFloat::_2, SQFloat::_3);

    QVector2* arInputPoints = null_q;
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(SQFloat::_2, SQFloat::_2),
                                           QVector2(SQFloat::_5, SQFloat::_2 + SQFloat::_0_5),
                                           QVector2(-SQFloat::_2 - SQFloat::_0_5, SQFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);

    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_0, SQFloat::_1),
                                   QVector2(SQFloat::_0_25, -SQFloat::_5),
                                   QVector2(-SQFloat::_1, SQFloat::_10)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 EXPECTED_POINTS[] = {
                                           QVector2(-SQFloat::_2 - SQFloat::_0_5, SQFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector2);
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(-SQFloat::_1, SQFloat::_10)
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( TransformWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector2 ORIGINAL_POINTS[] = {
                                           QVector2(SQFloat::_1, -SQFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2 arInputPoints[] = {
                                   QVector2(SQFloat::_1, -SQFloat::_1),
                               };
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( TransformWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QVector2 TRANSLATION = QVector2(SQFloat::_1, SQFloat::_3);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION = SQAngle::_90;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ROTATION = SQAngle::_HalfPi;
    #endif

    const QVector2 SCALE = QVector2(SQFloat::_2, SQFloat::_0_5);

    const QTransformationMatrix3x3 TRANSFORMATION = QTransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    QVector2* arInputPoints = null_q;
    const QBaseVector2 PIVOT(SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1),
                                   QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2),
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( RotateWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( RotateWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                   QVector4(SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1),
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( RotateWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( RotateWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QQuaternion ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QQuaternion ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1),
                                   QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2),
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( RotateWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_4, SQFloat::_4, SQFloat::_3)
                               };

    const QVector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( RotateWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_0, SQFloat::_1, SQFloat::_1, SQFloat::_1),
                                   QVector4(SQFloat::_1, SQFloat::_0, SQFloat::_2, SQFloat::_1),
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( RotateWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QVector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( RotateWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_4, SQFloat::_4, SQFloat::_3, SQFloat::_1)
                               };

    const QVector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( RotateWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION(SQAngle::_HalfPi, SQAngle::_QuarterPi, SQAngle::_ThirdPi);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION(SQAngle::_90, SQAngle::_45, SQAngle::_60);
#endif

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_4, SQFloat::_1, SQFloat::_5),
                                           QVector3(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9),
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_4, SQFloat::_1, SQFloat::_5, SQFloat::_1),
                                           QVector4(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9, SQFloat::_1),
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_4, SQFloat::_1, SQFloat::_5),
                                           QVector3(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9),
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_4, SQFloat::_1, SQFloat::_5, SQFloat::_1),
                                           QVector4(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9, SQFloat::_1),
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QBaseVector3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(SQFloat::_4, SQFloat::_1, SQFloat::_5),
                                           QVector3(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9),
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot7_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3(-SQFloat::_5, -SQFloat::_5, SQFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot7_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot8_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(SQFloat::_4, SQFloat::_1, SQFloat::_5, SQFloat::_1),
                                           QVector4(-SQFloat::_0_25 - SQFloat::_1, (float_q)13.0, SQFloat::_9, SQFloat::_1),
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( ScaleWithPivot8_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4(-SQFloat::_5, -SQFloat::_5, SQFloat::_3, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( ScaleWithPivot8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( ScaleWithPivot8_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QScalingMatrix3x3 SCALE(SQFloat::_3, -SQFloat::_2, -SQFloat::_4);

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)2.823223304703363,  SQFloat::_4,  (float_q)-5.1767766952966365),
                                           QVector3((float_q)-9.59533953988538,  SQFloat::_3,  (float_q)7.8605045828303322),
                                           QVector3((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2,    SQFloat::_1,  SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1,   SQFloat::_4,  SQFloat::_0_5)
                               };

    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( TransformWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( TransformWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)2.823223304703363,  SQFloat::_4,  (float_q)-5.1767766952966365, SQFloat::_1),
                                           QVector4((float_q)-9.59533953988538,  SQFloat::_3,  (float_q)7.8605045828303322,  SQFloat::_1),
                                           QVector4((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( TransformWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( TransformWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pivot point's W component doesn't affect the result.
/// </summary>
QTEST_CASE ( TransformWithPivot3_WComponentOfPivotDoesNotMatter_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x3> TRANSLATION = QTranslationMatrix<QMatrix4x3>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION = QTransformationMatrix<QMatrix4x3>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints1[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                };
    QVector4 arInputPoints2[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                };
    const QBaseVector4 PIVOT1(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QBaseVector4 PIVOT2(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT1, arInputPoints1, POINTS_COUNT);
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT2, arInputPoints2, POINTS_COUNT);

    // [Verification]
    BOOST_CHECK(arInputPoints1[0] == arInputPoints2[0]);
}

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)2.823223304703363,  SQFloat::_4,  (float_q)-5.1767766952966365),
                                           QVector3((float_q)-9.59533953988538,  SQFloat::_3,  (float_q)7.8605045828303322),
                                           QVector3((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(SQFloat::_2, SQFloat::_1, SQFloat::_0),
                                   QVector3(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1),
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 EXPECTED_POINTS[] = {
                                           QVector3((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector3);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( TransformWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector3 ORIGINAL_POINTS[] = {
                                           QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3 arInputPoints[] = {
                                   QVector3(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5)
                               };
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( TransformWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector3* arInputPoints = null_q;
    const QBaseVector3 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)2.823223304703363,  SQFloat::_4,  (float_q)-5.1767766952966365, SQFloat::_1),
                                           QVector4((float_q)-9.59533953988538,  SQFloat::_3,  (float_q)7.8605045828303322,  SQFloat::_1),
                                           QVector4((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);

    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(SQFloat::_2, SQFloat::_1, SQFloat::_0, SQFloat::_1),
                                   QVector4(SQFloat::_0_25, -SQFloat::_5, -SQFloat::_1, SQFloat::_1),
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
QTEST_CASE ( TransformWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 EXPECTED_POINTS[] = {
                                           QVector4((float_q)9.7175144212722024, (float_q)4.5, (float_q)-11.010407640085653, SQFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(QVector4);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
QTEST_CASE ( TransformWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const QVector4 ORIGINAL_POINTS[] = {
                                           QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                               };
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
QTEST_CASE ( TransformWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4* arInputPoints = null_q;
    const QBaseVector4 PIVOT(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pivot point's W component doesn't affect the result.
/// </summary>
QTEST_CASE ( TransformWithPivot5_WComponentOfPivotDoesNotMatter_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    // [Preparation]
    const int POINTS_COUNT = 1;
    const QTranslationMatrix<QMatrix4x4> TRANSLATION = QTranslationMatrix<QMatrix4x4>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_90, SQAngle::_180, SQAngle::_45);
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
#endif
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION = QTransformationMatrix<QMatrix4x4>(TRANSLATION, ROTATION, SCALE);

    QVector4 arInputPoints1[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                };
    QVector4 arInputPoints2[] = {
                                   QVector4(-SQFloat::_1, SQFloat::_4, SQFloat::_0_5, SQFloat::_1)
                                };
    const QBaseVector4 PIVOT1(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_1);
    const QBaseVector4 PIVOT2(SQFloat::_1, SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// [Execution]
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT1, arInputPoints1, POINTS_COUNT);
    SQPoint::TransformWithPivot(TRANSFORMATION, PIVOT2, arInputPoints2, POINTS_COUNT);

    // [Verification]
    BOOST_CHECK(arInputPoints1[0] == arInputPoints2[0]);
}

// End - Test Suite: SQPoint
QTEST_SUITE_END()
