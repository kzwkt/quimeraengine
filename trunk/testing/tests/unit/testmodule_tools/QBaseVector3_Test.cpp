// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QBaseVector3.h"

using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

QTEST_SUITE_BEGIN( QBaseVector3_TestSuite )

/// <summary>
/// Checks if default values has changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasntChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QBaseVector3 vVectorUT;
    
    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if values used as parameters are properly set to vector components.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreSetProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

	// Execution
    QBaseVector3 vVectorUT(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if the value provided is set to all the vector components.
/// </summary>
QTEST_CASE ( Constructor3_ValueIsSetForAllComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

	// Execution
    QBaseVector3 vVectorUT(EXPECTED_VALUE_FOR_ALL);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if the vector components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor4_VectorComponentsAreFilledWithValidReferenceTo3Floats_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

    float_q* VALID_ARRAY_OF_3_FLOATS = new float_q[3];
    VALID_ARRAY_OF_3_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_3_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_3_FLOATS[2] = EXPECTED_VALUE_FOR_Z;

	// Execution
    QBaseVector3 vVectorUT(VALID_ARRAY_OF_3_FLOATS);
    
    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, VALID_ARRAY_OF_3_FLOATS[0]);
    BOOST_CHECK_EQUAL(vVectorUT.y, VALID_ARRAY_OF_3_FLOATS[1]);
    BOOST_CHECK_EQUAL(vVectorUT.z, VALID_ARRAY_OF_3_FLOATS[2]);

    // Cleaning
    delete[] VALID_ARRAY_OF_3_FLOATS;
}

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenPointerIsNull_Test )
{
    // Preparation
    const float_q* NULL_ARRAY = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QBaseVector3 vVectorUT(NULL_ARRAY);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if no exceptions are thrown when the input array of floats points to an invalid memory space.
/// </summary>
QTEST_CASE ( Constructor4_ExceptionIsNotThrownWhenArrayIsNotFilled_Test )
{
    // Preparation
    const float_q* INVALID_ARRAY_OF_2_FLOATS = new float_q[2];

	// Execution
    bool bExceptionsThrown = false;

    try
    {
        QBaseVector3 vVectorUT(INVALID_ARRAY_OF_2_FLOATS);
    }
    catch(...)
    {
        bExceptionsThrown = true;
    }

    // Verification
    BOOST_CHECK(!bExceptionsThrown);
}

/// <summary>
/// Checks if vector components are set to the correct values packed in a valid vf32 object.
/// </summary>
QTEST_CASE ( Constructor5_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    // TODO [Thund]: QVF32 is not totally implemented yet.

	// Execution
    
    // Verification
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::Epsilon);

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::_0);

	// Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const QBaseVector3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseVector3 RIGHT_OPERAND(SQFloat::Epsilon);

	// Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseVector3
QTEST_SUITE_END()
