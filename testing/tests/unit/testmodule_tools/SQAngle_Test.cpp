// [TERMS&CONDITIONS]

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
/// Checks that a value of 360º is not truncated to 0º.
/// </summary>
QTEST_CASE ( TruncateDegrees_360IsNotTruncatedToZero_Test )
{
    // Preparation
    const float_q DEGREES = SQAngle::_360;
    const float_q NOT_EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::TruncateDegrees(DEGREES);
    
    // Verification
    BOOST_CHECK_NE(fResultUT, NOT_EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value of -360º is not truncated to 0º.
/// </summary>
QTEST_CASE ( TruncateDegrees_Minus360IsNotTruncatedToZero_Test )
{
    // Preparation
    const float_q DEGREES = -SQAngle::_360;
    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::TruncateDegrees(DEGREES);
    
    // Verification
    BOOST_CHECK_NE(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value greater than 360º is truncated to the equivalent value lower than 360º.
/// </summary>
QTEST_CASE ( TruncateDegrees_AnglesGreaterThan360AreCorrectlyTruncated_Test )
{
    // Preparation
    const float_q DEGREES = (float_q)405.0f;
    const float_q EXPECTED_VALUE = SQAngle::_360;

	// Execution
    float_q fResultUT = SQAngle::TruncateDegrees(DEGREES);
    
    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value lower than 360º is not truncated.
/// </summary>
QTEST_CASE ( TruncateDegrees_AnglesLowerThan360AreNotTruncated_Test )
{
    // Preparation
    const float_q DEGREES = SQAngle::_270;
    const float_q EXPECTED_VALUE = SQAngle::_270;

	// Execution
    float_q fResultUT = SQAngle::TruncateDegrees(DEGREES);
    
    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value of 2 Pi is not truncated to 0.
/// </summary>
QTEST_CASE ( TruncateRadians_2PiIsNotTruncatedToZero_Test )
{
    // Preparation
    const float_q RADIANS = SQAngle::_2Pi;
    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::TruncateRadians(RADIANS);
    
    // Verification
    BOOST_CHECK_NE(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value of -2 Pi is not truncated to 0.
/// </summary>
QTEST_CASE ( TruncateRadians_Minus2PiIsNotTruncatedToZero_Test )
{
    // Preparation
    const float_q RADIANS = -SQAngle::_2Pi;
    const float_q EXPECTED_VALUE = SQFloat::_0;

	// Execution
    float_q fResultUT = SQAngle::TruncateRadians(RADIANS);
    
    // Verification
    BOOST_CHECK_NE(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value greater than 2 Pi is truncated to the equivalent value lower than 2 Pi.
/// </summary>
QTEST_CASE ( TruncateRadians_AnglesGreaterThan2PiAreCorrectlyTruncated_Test )
{
    // Preparation
    const float_q RADIANS = SQAngle::_2Pi + SQAngle::_QuarterPi;
    const float_q EXPECTED_VALUE = SQAngle::_2Pi;

	// Execution
    float_q fResultUT = SQAngle::TruncateRadians(RADIANS);
    
    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a value lower than 2 Pi is not truncated.
/// </summary>
QTEST_CASE ( TruncateRadians_AnglesLowerThan2PiAreNotTruncated_Test )
{
    // Preparation
    const float_q RADIANS = SQAngle::_3HalfsPi;
    const float_q EXPECTED_VALUE = SQAngle::_3HalfsPi;

	// Execution
    float_q fResultUT = SQAngle::TruncateRadians(RADIANS);
    
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
