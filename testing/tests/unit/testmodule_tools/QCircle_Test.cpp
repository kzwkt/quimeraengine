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

#include "QCircle.h"

#include "QTransformationMatrix3x3.h"
#include "SQPoint.h"
#include "SQAngle.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Common::DataTypes::float_q;
using Kinesis::QuimeraEngine::Common::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QCircle;
using Kinesis::QuimeraEngine::Tools::Math::QOrb;
using Kinesis::QuimeraEngine::Tools::Math::QVector2;
using Kinesis::QuimeraEngine::Tools::Math::SQPoint;
using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix3x3;
using Kinesis::QuimeraEngine::Tools::Math::EQIntersections;
using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

QTEST_SUITE_BEGIN( QCircle_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2();
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QCircle circleUT;
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets circle components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_5, SQFloat::_6);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_4;

    const QCircle CIRCLE_TO_COPY = QCircle(EXPECTED_VALUE_FOR_CENTER,
                                           EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QCircle circleUT(CIRCLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if base type constructor sets circle components properly.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_8, SQFloat::_9);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_3;

    const QOrb<QVector2> ORB_TO_COPY = QOrb<QVector2>(EXPECTED_VALUE_FOR_CENTER,
                                                      EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QCircle circleUT(ORB_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_1, SQFloat::_5);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_4;

	// [Execution]
    QCircle circleUT = QCircle(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned unit circle has not changed since the last time the test was executed.
/// </summary>
QTEST_CASE ( GetUnitCircle_ValueHasNotChanged_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;

	// [Execution]
    QCircle circleUT = QCircle::GetUnitCircle();
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly assigned to another circle.
/// </summary>
QTEST_CASE ( OperatorAssignation_CircleIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_2, SQFloat::_3);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_8;
    const QCircle CIRCLE_TO_COPY = QCircle(EXPECTED_VALUE_FOR_CENTER,
                                           EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    QCircle circleUT;
    circleUT = CIRCLE_TO_COPY;
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly translated.
/// </summary>
QTEST_CASE ( Translate1_CircleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_7);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::Translate(TRANSLATION_VECTOR, &vExpectedValueForCenter,1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not translated if traslation is zero.
/// </summary>
QTEST_CASE ( Translate1_CircleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(INIT_CENTER_POS);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly translated.
/// </summary>
QTEST_CASE ( Translate2_CircleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_3, SQFloat::_7);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::Translate(TRANSLATION_VECTOR, &vExpectedValueForCenter,1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not translated if components of traslation are zero.
/// </summary>
QTEST_CASE ( Translate2_CircleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const QVector2 TRANSLATION_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(INIT_CENTER_POS);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated.
/// </summary>
QTEST_CASE ( Rotate_CircleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_Pi;
    #endif
    
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::Rotate(ANGLE, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is not rotated if angle is zero.
/// </summary>
QTEST_CASE ( Rotate_CircleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q ANGLE = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated with a pivot point.
/// </summary>
QTEST_CASE ( RotateWithPivot_CircleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_Pi;
    #endif
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::RotateWithPivot(ANGLE, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle not rotated if angle is zero.
/// </summary>
QTEST_CASE ( RotateWithPivot_CircleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q ANGLE = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_1, SQFloat::_9);
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly rotated with a pivot point in its center.
/// </summary>
QTEST_CASE ( RotateWithPivot_CircleIsCorrectlyRotatedWithPivotInCenter_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_Pi;
    #endif
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = INIT_CENTER_POS;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::RotateWithPivot(ANGLE, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, EXPECTED_VALUE_FOR_RADIUS);
    circleUT = circleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_2, SQFloat::_2);
    const float_q SCALE_RADIUS = SQFloat::_3;

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
QTEST_CASE ( Scale1_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);
    const float_q SCALE_RADIUS = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle is correctly scaled by zero.
/// </summary>
QTEST_CASE ( Scale1_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q SCALE_RADIUS = SQFloat::_0;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle with zero radius is correctly scaled.
/// </summary>
QTEST_CASE ( Scale1_CircleWidthZeroRadiusIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_0;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_4, SQFloat::_4);
    const float_q SCALE_RADIUS = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_2, SQFloat::_2);
    const float_q SCALE_RADIUS = SQFloat::_3;

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
QTEST_CASE ( Scale2_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);
    const float_q SCALE_RADIUS = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle is correctly scaled by zero.
/// </summary>
QTEST_CASE ( Scale2_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q SCALE_RADIUS = SQFloat::_0;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a the circle with zero radius is correctly scaled.
/// </summary>
QTEST_CASE ( Scale2_CircleWidthRadiusEqualsToZeroIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_0;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_4, SQFloat::_4);
    const float_q SCALE_RADIUS = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);
    SQPoint::Scale(SCALE_VECTOR, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Scale(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled with a pivot point.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_2, SQFloat::_2);
    const float_q SCALE_RADIUS = SQFloat::_3;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::ScaleWithPivot(SCALE_VECTOR, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_3;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);
    const float_q SCALE_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled by zero with a pivot point.
/// </summary>
QTEST_CASE ( ScaleWithPivot1_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_3;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q SCALE_RADIUS = SQFloat::_0;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled with a pivot point.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_CircleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_2;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_2, SQFloat::_2);
    const float_q SCALE_RADIUS = SQFloat::_3;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::ScaleWithPivot(SCALE_VECTOR, PIVOT_POINT, &vExpectedValueForCenter, 1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not scaled if scalation is one.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_CircleIsNotScaledWhenScalationIsOne_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_3;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_1, SQFloat::_1);
    const float_q SCALE_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly scaled by zero with a pivot point.
/// </summary>
QTEST_CASE ( ScaleWithPivot2_CircleRadiusEqualsZeroWhenIsScaledByZero_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_3;
    const QVector2 SCALE_VECTOR = QVector2(SQFloat::_0, SQFloat::_0);
    const float_q SCALE_RADIUS = SQFloat::_0;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);
    const QVector2 EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_q EXPECTED_VALUE_FOR_RADIUS = SQFloat::_0;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.ScaleWithPivot(SCALE_VECTOR.x, SCALE_VECTOR.y, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly transformed.
/// </summary>
QTEST_CASE ( Transform_CircleIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_1;
    const float_q SCALE_RADIUS = SQFloat::_3;
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_Pi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(QVector2(SQFloat::_2, SQFloat::_3),
            ANGLE,
            QVector2(SQFloat::_4, SQFloat::_6));

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::Transform(TRANSFORMATION_MATRIX, &vExpectedValueForCenter,1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Transform(TRANSFORMATION_MATRIX, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not transformed when matrix is identity.
/// </summary>
QTEST_CASE ( Transform_CircleIsNotTransformedWhenTransformationIsIdentity_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_1;
    const float_q SCALE_RADIUS = SQFloat::_1;
    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX = QTransformationMatrix3x3::GetIdentity();
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.Transform(TRANSFORMATION_MATRIX, SCALE_RADIUS);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a circle is correctly transformed with a pivot point.
/// </summary>
QTEST_CASE ( TransformWithPivot_CircleIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_1;
    const float_q SCALE_RADIUS = SQFloat::_3;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_90;
    #else
        const float_q ANGLE = SQAngle::_Pi;
    #endif

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX =
            QTransformationMatrix3x3(QVector2(SQFloat::_2, SQFloat::_3),
            ANGLE,
            QVector2(SQFloat::_4, SQFloat::_6));

    float_q fExpectedValueForRadius = INIT_RADIUS;
    QVector2 vExpectedValueForCenter = QVector2(INIT_CENTER_POS);

    fExpectedValueForRadius *= SCALE_RADIUS; 
    SQPoint::TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT, &vExpectedValueForCenter,1);

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.TransformWithPivot(TRANSFORMATION_MATRIX, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == vExpectedValueForCenter);
    BOOST_CHECK(circleUT.Radius == fExpectedValueForRadius);
}

/// <summary>
/// Checks that a circle is not transformed when matrix is identity.
/// </summary>
QTEST_CASE ( TransformWithPivot_CircleIsNotTransformedWhenTransformationIsIdentity_Test )
{
    // [Preparation]
    const QVector2 INIT_CENTER_POS = QVector2(SQFloat::_2, SQFloat::_4);
    const float_q INIT_RADIUS = SQFloat::_1;
    const float_q SCALE_RADIUS = SQFloat::_1;
    const QVector2 PIVOT_POINT = QVector2(SQFloat::_6, SQFloat::_7);
    const float_q EXPECTED_VALUE_FOR_RADIUS = INIT_RADIUS;
    const QVector2 EXPECTED_VALUE_FOR_CENTER = INIT_CENTER_POS;

    const QTransformationMatrix3x3 TRANSFORMATION_MATRIX = QTransformationMatrix3x3::GetIdentity();

	// [Execution]
    QCircle circleUT= QCircle(INIT_CENTER_POS, INIT_RADIUS);
    circleUT = circleUT.TransformWithPivot(TRANSFORMATION_MATRIX, SCALE_RADIUS, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(circleUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(circleUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned value is none when the two circles are not intersecting.
/// </summary>
QTEST_CASE ( IntersectionPoint_ReturnsNoneWhenCirclesNotIntersecting_Test )
{
    // [Preparation]
    const EQIntersections EXPECTED_VALUE_FOR_INTERSECTION = EQIntersections::E_None;
    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_1);
    const QCircle CIRCLE_TWO = QCircle(QVector2(SQFloat::_3, SQFloat::_0), SQFloat::_1);

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();
    EQIntersections intersectionUT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersectionUT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is one when circles are intersecting in one point (tangent).
/// </summary>
QTEST_CASE ( IntersectionPoint_ReturnsOneWhenCirclesAreIntersectingInOnePoint_Test )
{
    // [Preparation]
    const EQIntersections EXPECTED_VALUE_FOR_INTERSECTION = EQIntersections::E_One;
    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_1);
    const QCircle CIRCLE_TWO = QCircle(QVector2(SQFloat::_2, SQFloat::_0), SQFloat::_1);

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();
    EQIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EQIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is two when circles are intersecting in two points.
/// </summary>
QTEST_CASE ( IntersectionPoint_ReturnsTwoWhenCirclesAreIntersectingInTwoPoints_Test )
{
    // [Preparation]
    const EQIntersections EXPECTED_VALUE_FOR_INTERSECTION = EQIntersections::E_Two;
    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_1);
    const QCircle CIRCLE_TWO = QCircle(QVector2(SQFloat::_1, SQFloat::_0), SQFloat::_1);

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();
    EQIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EQIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is infinite when two circles are the same.
/// </summary>
QTEST_CASE ( IntersectionPoint_ReturnsInfiniteWhenTwoCirclesAreTheSame_Test )
{
    // [Preparation]
    const EQIntersections EXPECTED_VALUE_FOR_INTERSECTION = EQIntersections::E_Infinite;
    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_1);
    const QCircle CIRCLE_TWO = CIRCLE_ONE;

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();
    EQIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EQIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

/// <summary>
/// Checks that the returned value is infinite when one circle is contained into the other.
/// </summary>
QTEST_CASE ( IntersectionPoint_ReturnsInfiniteWhenOneCircleIsContainedIntoTheOther_Test )
{
    // [Preparation]
    const EQIntersections EXPECTED_VALUE_FOR_INTERSECTION = EQIntersections::E_Infinite;
    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_1);
    const QCircle CIRCLE_TWO = QCircle(QVector2(SQFloat::_0, SQFloat::_0), SQFloat::_2);

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();
    EQIntersections intersection1UT = CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    EQIntersections intersection2UT = CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    
    // [Verification]
    BOOST_CHECK(intersection1UT == EXPECTED_VALUE_FOR_INTERSECTION);
    BOOST_CHECK(intersection2UT == EXPECTED_VALUE_FOR_INTERSECTION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of one of the circles equals zero.
/// </summary>
QTEST_CASE ( IntersectionPoint_AssertionFailsWhenRadiusEqualsZero_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

    const QCircle CIRCLE_ONE = QCircle(QVector2(SQFloat::_8, SQFloat::_7), SQFloat::_0);
    const QCircle CIRCLE_TWO = QCircle(QVector2(SQFloat::_6, SQFloat::_5), SQFloat::_1);

	// [Execution]
    QVector2 intersection1 = QVector2();
    QVector2 intersection2 = QVector2();

    bool bAssertionFailed1 = false;
    try
    {
        CIRCLE_ONE.IntersectionPoint(CIRCLE_TWO, intersection1, intersection2);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;
    try
    {
        CIRCLE_TWO.IntersectionPoint(CIRCLE_ONE, intersection1, intersection2);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed2 = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed1 == ASSERTION_FAILED);
    BOOST_CHECK(bAssertionFailed2 == ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: QCircle
QTEST_SUITE_END()
