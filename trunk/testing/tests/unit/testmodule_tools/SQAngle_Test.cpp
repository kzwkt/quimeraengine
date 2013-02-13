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

#include "SQAngle.h"

using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

QTEST_SUITE_BEGIN( SQAngle_TestSuite )

/// <summary>
/// Checks that degrees are correctly converted to radians.
/// </summary>
QTEST_CASE ( DegreesToRadians_DegreesAreCorrectlyConvertedToRadians_Test )
{
    // Preparation
    const float_q DEGREES = SQAngle::_45;
    const float_q EXPECTED_VALUE = SQAngle::_QuarterPi;

	// Execution
    float_q fResultUT = SQAngle::DegreesToRadians(DEGREES);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that radians are correctly converted to degrees.
/// </summary>
QTEST_CASE ( RadiansToDegrees_RadiansAreCorrectlyConvertedToDegrees_Test )
{
    // Preparation
    const float_q RADIANS = SQAngle::_QuarterPi;
    const float_q EXPECTED_VALUE = SQAngle::_45;

	// Execution
    float_q fResultUT = SQAngle::RadiansToDegrees(RADIANS);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full revolution positive angle is truncated to 0.
/// </summary>
QTEST_CASE ( Truncate_FullRevolutionPositiveAngleIsTruncatedToZero_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = SQAngle::_2Pi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = SQAngle::_360;
	#endif

    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full revolution negative angle is truncated to 0.
/// </summary>
QTEST_CASE ( Truncate_FullRevolutionNegativeAngleIsTruncatedToZero_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = -SQAngle::_2Pi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = -SQAngle::_360;
	#endif

    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a positive angle greater than the full revolution positive angle is truncated to a lower equivalent angle.
/// </summary>
QTEST_CASE ( Truncate_PositiveAnglesGreaterThanFullRevolutionPositiveAngleAreCorrectlyTruncated_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = SQAngle::_2Pi + SQAngle::_QuarterPi;
		const float_q EXPECTED_VALUE = SQAngle::_QuarterPi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = SQAngle::_360 + SQAngle::_45;
		const float_q EXPECTED_VALUE = SQAngle::_45;
	#endif

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_VALUE) );   // Due to precission issues
}

/// <summary>
/// Checks that a negative angle lower than the full revolution negative angle is truncated to a greater equivalent angle.
/// </summary>
QTEST_CASE ( Truncate_NegativeAnglesLowerThanFullRevolutionNegativeAngleAreCorrectlyTruncated_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = -SQAngle::_2Pi - SQAngle::_QuarterPi;
		const float_q EXPECTED_VALUE = -SQAngle::_QuarterPi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = -SQAngle::_360 - SQAngle::_45;
		const float_q EXPECTED_VALUE = -SQAngle::_45;
	#endif

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(fResultUT, EXPECTED_VALUE) );   // Due to precission issues
}

/// <summary>
/// Checks that a positive angle lower than the full revolution positive angle is not truncated.
/// </summary>
QTEST_CASE ( Truncate_PositiveAnglesLowerThanFullRevolutionPositiveAngleAreNotTruncated_Test )
{
    // Preparation
	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = SQAngle::_3HalfsPi;
		const float_q EXPECTED_VALUE = SQAngle::_3HalfsPi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = SQAngle::_270;
		const float_q EXPECTED_VALUE = SQAngle::_270;
	#endif

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a negative angle greater than the full revolution negative angle is not truncated.
/// </summary>
QTEST_CASE ( Truncate_NegativeAnglesGreaterThanFullRevolutionNegativeAngleAreNotTruncated_Test )
{
    // Preparation
	#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
		const float_q ANGLE = -SQAngle::_3HalfsPi;
		const float_q EXPECTED_VALUE = -SQAngle::_3HalfsPi;
	#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
		const float_q ANGLE = -SQAngle::_270;
		const float_q EXPECTED_VALUE = -SQAngle::_270;
	#endif

	// Execution
    float_q fResultUT = SQAngle::Truncate(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when angle equals zero, revolutions equals zero.
/// </summary>
QTEST_CASE ( CountRevolutions_ZeroAngleIsCountAsZeroRevolutions_Test )
{
    // Preparation
    const float_q ANGLE = SQFloat::_0;
    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::CountRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when the angle describes exactly a circumference, revolutions equals one.
/// </summary>
QTEST_CASE ( CountRevolutions_CompleteCircunferenceIsCountAsOneRevolution_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = SQAngle::_2Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_360;
    #endif

    const float_q EXPECTED_VALUE = SQFloat::_1;

	// Execution
    float_q fResultUT = SQAngle::CountRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolution fractions are taken into account.
/// </summary>
QTEST_CASE ( CountRevolutions_RevolutionFractionsAreTakenIntoAccount_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = SQAngle::_2Pi + SQAngle::_Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_360 + SQAngle::_180;
    #endif

    const float_q EXPECTED_VALUE = SQFloat::_1 + SQFloat::_0_5;

	// Execution
    float_q fResultUT = SQAngle::CountRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolutions are negative when the angle is negative.
/// </summary>
QTEST_CASE ( CountRevolutions_RevolutionsAreNegativeWhenNegativeAnglesAreUsed_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = -SQFloat::_2 * SQAngle::_2Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = -SQFloat::_2 * SQAngle::_360;
    #endif

    const float_q EXPECTED_VALUE = -SQFloat::_2;

	// Execution
    float_q fResultUT = SQAngle::CountRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when angle equals zero, revolutions equals zero.
/// </summary>
QTEST_CASE ( CountCompleteRevolutions_ZeroAngleIsCountAsZeroRevolutions_Test )
{
    // Preparation
    const float_q ANGLE = SQFloat::_0;
    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::CountCompleteRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when the angle describes exactly a circumference, revolutions equals one.
/// </summary>
QTEST_CASE ( CountCompleteRevolutions_CompleteCircunferenceIsCountAsOneRevolution_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = SQAngle::_2Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_360;
    #endif

    const float_q EXPECTED_VALUE = SQFloat::_1;

	// Execution
    float_q fResultUT = SQAngle::CountCompleteRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolution fractions are not taken into account.
/// </summary>
QTEST_CASE ( CountCompleteRevolutions_RevolutionFractionsAreNotTakenIntoAccount_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = SQAngle::_2Pi + SQAngle::_Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = SQAngle::_360 + SQAngle::_180;
    #endif

    const float_q EXPECTED_VALUE = SQFloat::_1;

	// Execution
    float_q fResultUT = SQAngle::CountCompleteRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolutions are negative when the angle is negative.
/// </summary>
QTEST_CASE ( CountCompleteRevolutions_RevolutionsAreNegativeWhenNegativeAnglesAreUsed_Test )
{
    // Preparation
    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
        const float_q ANGLE = -SQFloat::_2 * SQAngle::_2Pi;
    #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ANGLE = -SQFloat::_2 * SQAngle::_360;
    #endif

    const float_q EXPECTED_VALUE = -SQFloat::_2;

	// Execution
    float_q fResultUT = SQAngle::CountCompleteRevolutions(ANGLE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

// End - Test Suite: SQAngle
QTEST_SUITE_END()
