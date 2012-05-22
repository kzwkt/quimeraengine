// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQFloat.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;

QTEST_SUITE_BEGIN( SQFloat_TestSuite )

/// <summary>
/// Checks that it returns True when the floating point value is Not a Number.
/// </summary>
QTEST_CASE ( IsNaN_ReturnsTrueWhenValueIsNaN_Test )
{
    // Preparation
    const float_q NAN_VALUE = SQFloat::_0 / SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNaN(NAN_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is a number.
/// </summary>
QTEST_CASE ( IsNaN_ReturnsFalseWhenValueIsANumber_Test )
{
    // Preparation
    const float_q NUMBER = SQFloat::_1;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNaN(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is an infinite number.
/// </summary>
QTEST_CASE ( IsNaN_ReturnsFalseWhenValueIsInfinite_Test )
{
    // Preparation
    const float_q INFINITE = SQFloat::MaxFloat_Q * SQFloat::MaxFloat_Q;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNaN(INFINITE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is infinite.
/// </summary>
QTEST_CASE ( IsInfinite_ReturnsTrueWhenValueIsInfinite_Test )
{
    // Preparation
    const float_q INFINITE = SQFloat::MaxFloat_Q * SQFloat::MaxFloat_Q;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsInfinite(INFINITE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is not infinite.
/// </summary>
QTEST_CASE ( IsInfinite_ReturnsFalseWhenValueIsNotInfinite_Test )
{
    // Preparation
    const float_q NOT_INFINITE = SQFloat::_1;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsInfinite(NOT_INFINITE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is not a number.
/// </summary>
QTEST_CASE ( IsInfinite_ReturnsFalseWhenValueIsNaN_Test )
{
    // Preparation
    const float_q NAN_VALUE = SQFloat::_0 / SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsInfinite(NAN_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is Not a Number.
/// </summary>
QTEST_CASE ( IsNanOrInfinite_ReturnsTrueWhenValueIsNaN_Test )
{
    // Preparation
    const float_q NAN_VALUE = SQFloat::_0 / SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNanOrInfinite(NAN_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is a common number.
/// </summary>
QTEST_CASE ( IsNanOrInfinite_ReturnsFalseWhenValueIsACommonNumber_Test )
{
    // Preparation
    const float_q NUMBER = SQFloat::_1;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNanOrInfinite(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is an infinite number.
/// </summary>
QTEST_CASE ( IsNanOrInfinite_ReturnsTrueWhenValueIsInfinite_Test )
{
    // Preparation
    const float_q INFINITE = SQFloat::MaxFloat_Q * SQFloat::MaxFloat_Q;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNanOrInfinite(INFINITE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences equal tolerance value.
/// </summary>
QTEST_CASE ( AreEquals_ReturnsTrueWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::AreEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( AreEquals_ReturnsTrueWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::AreEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( AreEquals_ReturnsFalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::AreEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are exactly equal.
/// </summary>
QTEST_CASE ( AreEquals_ReturnsTrueWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::AreEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences equal tolerance value.
/// </summary>
QTEST_CASE ( AreNotEquals_ReturnsFalseWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::AreNotEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( AreNotEquals_ReturnsFalseWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::AreNotEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( AreNotEquals_ReturnsTrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::AreNotEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are exactly equal.
/// </summary>
QTEST_CASE ( AreNotEquals_ReturnsFalseWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::AreNotEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsGreaterThan_ReturnsTrueWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by exactly tolerance.
/// </summary>
QTEST_CASE ( IsGreaterThan_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByExactlyTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are equal.
/// </summary>
QTEST_CASE ( IsGreaterThan_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsGreaterThan_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsLessThan_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is lower than right one, by exactly tolerance.
/// </summary>
QTEST_CASE ( IsLessThan_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when operands are equal.
/// </summary>
QTEST_CASE ( IsLessThan_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsLessThan_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsGreaterOrEquals_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is greater than right one, by exactly tolerance.
/// </summary>
QTEST_CASE ( IsGreaterOrEquals_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByExactlyTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are equal.
/// </summary>
QTEST_CASE ( IsGreaterOrEquals_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsGreaterOrEquals_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsLessOrEquals_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by exactly tolerance.
/// </summary>
QTEST_CASE ( IsLessOrEquals_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when operands are equal.
/// </summary>
QTEST_CASE ( IsLessOrEquals_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::Epsilon;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
QTEST_CASE ( IsLessOrEquals_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // Preparation
    const float_q LEFT_OPERAND = SQFloat::_0;
    const float_q RIGHT_OPERAND = SQFloat::Epsilon + SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals tolerance value.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenValueEqualsTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals negative tolerance value.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenValueEqualsNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than tolerance value.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenValueIsLessThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is greater than tolerance value.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenValueIsGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than negative tolerance value.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenValueIsLessThanNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value exactly equals zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenValueExactlyEqualsZero_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals tolerance value.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsFalseWhenValueEqualsTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals negative tolerance value.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsFalseWhenValueEqualsNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than tolerance value.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsFalseWhenValueIsLessThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is greater than tolerance value.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsTrueWhenValueIsGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than negative tolerance value.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsTrueWhenValueIsLessThanNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value exactly equals zero.
/// </summary>
QTEST_CASE ( IsNotZero_ReturnsFalseWhenValueExactlyEqualsZero_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::_0;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNotZero(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a NaN is what expected.
/// </summary>
QTEST_CASE ( ToString_NaNIsCorrectlyConverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    const float_q NAN_VALUE = SQFloat::_0 / SQFloat::_0;
    string_q EXPECTED_RESULT = QE_L("-1.#IND");

	// Execution
    string_q strResultUT = SQFloat::ToString(NAN_VALUE);

    // Verification
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for an infinite number is what expected.
/// </summary>
QTEST_CASE ( ToString_InfiniteIsCorrectlyConverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    const float_q INFINITE = SQFloat::MaxFloat_Q * SQFloat::MaxFloat_Q;
    string_q EXPECTED_RESULT = QE_L("1.#INF");

	// Execution
    string_q strResultUT = SQFloat::ToString(INFINITE);

    // Verification
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for an high number (which requires scientific notation) is what expected.
/// </summary>
QTEST_CASE ( ToString_HighNumberIsCorrectlyConverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    const float_q NUMBER = (float_q)-12345678901234.0f;
    string_q EXPECTED_RESULT = QE_L("-1.2345679e+013");

	// Execution
    string_q strResultUT = SQFloat::ToString(NUMBER);

    // Verification
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a tiny number (which requires scientific notation) is what expected.
/// </summary>
QTEST_CASE ( ToString_TinyNumberIsCorrectlyConverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    const float_q NUMBER = (float_q)-0.0000000012345678901234f;
    string_q EXPECTED_RESULT = QE_L("-1.23456789e-009");

	// Execution
    string_q strResultUT = SQFloat::ToString(NUMBER);

    // Verification
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a common number is what expected.
/// </summary>
QTEST_CASE ( ToString_CommonNumberIsCorrectlyConverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    const float_q NUMBER = (float_q)-12345.6789f;
    string_q EXPECTED_RESULT = QE_L("-12345.6787"); // There is a strange round here

	// Execution
    string_q strResultUT = SQFloat::ToString(NUMBER);

    // Verification
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded off to zero when it equals zero point five.
/// </summary>
QTEST_CASE ( ToInteger_WhenValueEqualsZeroPointFiveItsRoundedOffToZero_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
#endif

    const float_q NUMBER = SQFloat::_0_5;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)0;

	// Execution
    IntegerTypeForTest nResultUT = SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded off to one when it is greater than zero point five.
/// </summary>
QTEST_CASE ( ToInteger_WhenValueIsGreaterThanZeroPointFiveItsRoundedOffToOne_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
#endif

    const float_q NUMBER = SQFloat::_0_5 + SQFloat::_0_25;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)1;

	// Execution
    IntegerTypeForTest nResultUT = SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded to zero when it is lower than zero point five.
/// </summary>
QTEST_CASE ( ToInteger_WhenValueIsLessThanZeroPointFiveItsRoundedToZero_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
#endif

    const float_q NUMBER = SQFloat::_0_25;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)0;

	// Execution
    IntegerTypeForTest nResultUT = SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the assertion fails when the size of the Integer type used as template parameter is different from the size of the floating point type used by default.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenTheMemorySizeOfIntegerTypeIsDifferentFromSizeOfFloatType_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
#endif

    const float_q NUMBER = SQFloat::_0;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion fails when number is higher than the maximum integer representation possible for default precission.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenFloatNumberIsHigherThanTheMaximumIntegerPossible_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
    const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  8388608; // Maximum convertible integer value = 2^23
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
    const float_q MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  4503599627370496l; // Maximum convertible integer value = 2^52
#endif

    const float_q NUMBER = MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED + SQFloat::_1;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion fails when number is lower than the minimum integer representation possible for default precission.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenFloatNumberIsLowerThanTheMinimumIntegerPossible_Test )
{
    // Preparation
#if QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_SIMPLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
    typedef i32_q IntegerTypeForTest;
    const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -4194304; // Maximum convertible integer negative value = 2^22
#elif QE_CONFIG_PRECISSION_DEFAULT == QE_CONFIG_PRECISSION_DOUBLE
    using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
    typedef i64_q IntegerTypeForTest;
    const float_q MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -2251799813685248l; // Maximum convertible integer negative value = 2^51
#endif

    const float_q NUMBER = MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED - SQFloat::_1;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        SQFloat::ToInteger<IntegerTypeForTest>(NUMBER);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if that values are not rounded off.
/// </summary>
QTEST_CASE ( Truncate_ValueIsNotRoundedOff_Test )
{
    // Preparation
    const float_q NUMBER = (float_q)1.9999999f;
    const float_q EXPECTED_RESULT = SQFloat::_1;

	// Execution
    float_q fResultUT = SQFloat::Truncate(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the fractional part of the number dissapears.
/// </summary>
QTEST_CASE ( Truncate_FractionalPartDissapears_Test )
{
    // Preparation
    const float_q NUMBER = (float_q)12345.6789f;
    const float_q EXPECTED_RESULT = (float_q)12345;

	// Execution
    float_q fResultUT = SQFloat::Truncate(NUMBER);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if a value that is greater than maximum bound is set to that bound.
/// </summary>
QTEST_CASE ( Clamp_ReturnsMaxWhenValueIsHigherThanMax_Test )
{
    // Preparation
    const float_q NUMBER = SQFloat::_5;
    const float_q MAX_BOUND = SQFloat::_2;
    const float_q MIN_BOUND = SQFloat::_1;
    const float_q EXPECTED_RESULT = MAX_BOUND;

	// Execution
    float_q fResultUT = SQFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if a value that is lower than minimum bound is set to that bound.
/// </summary>
QTEST_CASE ( Clamp_ReturnsMinWhenValueIsLowerThanMin_Test )
{
    // Preparation
    const float_q NUMBER = -SQFloat::_5;
    const float_q MAX_BOUND = SQFloat::_2;
    const float_q MIN_BOUND = SQFloat::_1;
    const float_q EXPECTED_RESULT = MIN_BOUND;

	// Execution
    float_q fResultUT = SQFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is enclosed in the range Max..Min, then it's returned as is.
/// </summary>
QTEST_CASE ( Clamp_WhenValueIsEnclosedBetweenMaxAndMinItsReturnedAsIs_Test )
{
    // Preparation
    const float_q NUMBER = (float_q)1.5f;
    const float_q MAX_BOUND = SQFloat::_2;
    const float_q MIN_BOUND = SQFloat::_1;
    const float_q EXPECTED_RESULT = NUMBER;

	// Execution
    float_q fResultUT = SQFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if bytes that compound the floating point value are correctly reordered.
/// </summary>
QTEST_CASE ( SwapEndianess_BytesAreCorrectlyReordered_Test )
{
    // Preparation
    const float_q VALUE = (float_q)123456789.1234f;      // a3 79 eb 4c
    const float_q EXPECTED_RESULT = -1.3548143e-017f;    // 4c eb 79 a3

	// Execution
    float_q fResultUT = SQFloat::SwapEndianess(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals negative tolerance value.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsFalseWhenValueEqualsNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNegative(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than tolerance value.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsTrueWhenValueIsLessThanNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsNegative(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is greater than tolerance value.
/// </summary>
QTEST_CASE ( IsNegative_ReturnsFalseWhenValueIsGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsNegative(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals negative tolerance value.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsTrueWhenValueEqualsNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsPositive(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than tolerance value.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsFalseWhenValueIsLessThanNegativeTolerance_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResultUT = SQFloat::IsPositive(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is greater than tolerance value.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsTrueWhenValueIsGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsPositive(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value equals zero.
/// </summary>
QTEST_CASE ( IsPositive_ReturnsTrueWhenValueEqualsZero_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::_0;
    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResultUT = SQFloat::IsPositive(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is copied when the source value is positive and the target one is negative.
/// </summary>
QTEST_CASE ( CopySign_SignIsCopiedWhenSourceIsPositiveAndTargetIsNegative_Test )
{
    // Preparation
    const float_q SOURCE = SQFloat::_1;
    float_q fTargetUT = -SQFloat::_1;

    const float_q EXPECTED_RESULT = SQFloat::_1;

	// Execution
    SQFloat::CopySign(SOURCE, fTargetUT);

    // Verification
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is copied when the source value is positive and the target one is negative.
/// </summary>
QTEST_CASE ( CopySign_SignIsCopiedWhenSourceIsNegativeAndTargetIsPositive_Test )
{
    // Preparation
    const float_q SOURCE = -SQFloat::_1;
    float_q fTargetUT = SQFloat::_1;

    const float_q EXPECTED_RESULT = -SQFloat::_1;

	// Execution
    SQFloat::CopySign(SOURCE, fTargetUT);

    // Verification
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is the same when the source value is positive and the target one is positive.
/// </summary>
QTEST_CASE ( CopySign_SignIsTheSameWhenSourceIsPositiveAndTargetIsPositive_Test )
{
    // Preparation
    const float_q SOURCE = SQFloat::_1;
    float_q fTargetUT = SQFloat::_1;

    const float_q EXPECTED_RESULT = SQFloat::_1;

	// Execution
    SQFloat::CopySign(SOURCE, fTargetUT);

    // Verification
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is the same when the source value is negative and the target one is negative.
/// </summary>
QTEST_CASE ( CopySign_SignIsTheSameWhenSourceIsNegativeAndTargetIsNegative_Test )
{
    // Preparation
    const float_q SOURCE = -SQFloat::_1;
    float_q fTargetUT = -SQFloat::_1;

    const float_q EXPECTED_RESULT = -SQFloat::_1;

	// Execution
    SQFloat::CopySign(SOURCE, fTargetUT);

    // Verification
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns a positive value when original value was already positive.
/// </summary>
QTEST_CASE ( Abs_ReturnsPositiveWhenValueIsAlreadyPositive_Test )
{
    // Preparation
    const float_q VALUE = SQFloat::_1;
    const float_q EXPECTED_RESULT = SQFloat::_1;

	// Execution
    float_q fResultUT = SQFloat::Abs(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns a positive value when original value was negative.
/// </summary>
QTEST_CASE ( Abs_ReturnsPositiveWhenValueIsNegative_Test )
{
    // Preparation
    const float_q VALUE = -SQFloat::_1;
    const float_q EXPECTED_RESULT = SQFloat::_1;

	// Execution
    float_q fResultUT = SQFloat::Abs(VALUE);

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

// End - Test Suite: SQFloat
QTEST_SUITE_END()
