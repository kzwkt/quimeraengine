// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QVector3.h"

#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QTranslationMatrix.h"

using Kinesis::QuimeraEngine::Tools::Math::QVector3;

QTEST_SUITE_BEGIN( QVector3_TestSuite )

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
    QVector3 vVectorUT;

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
    QVector3 vVectorUT(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

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
    QVector3 vVectorUT(EXPECTED_VALUE_FOR_ALL);

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
    QVector3 vVectorUT(VALID_ARRAY_OF_3_FLOATS);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);

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
        QVector3 vVectorUT(NULL_ARRAY);
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
        QVector3 vVectorUT(INVALID_ARRAY_OF_2_FLOATS);
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
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

	vf32_q PACK;
	SQVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, SQFloat::_0, PACK);

	// Execution
	QVector3 vVectorUT(PACK);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if vector components are set to the correct values of the translation matrix.
/// </summary>
QTEST_CASE ( Constructor6_VectorComponentsAreFilledWithRightMatrixElements_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_4;

    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    const QMatrix4x3 MATRIX(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                            SQFloat::_0, SQFloat::_1, SQFloat::_0,
                            SQFloat::_0, SQFloat::_0, SQFloat::_1,
                            EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(MATRIX);

	// Execution
    QVector3 vVectorUT(TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if vector components are set to the correct values of the translation matrix.
/// </summary>
QTEST_CASE ( Constructor7_VectorComponentsAreFilledWithRightMatrixElements_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_4;

    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    const QMatrix4x4 MATRIX(SQFloat::_1, SQFloat::_0, SQFloat::_0, SQFloat::_0,
                            SQFloat::_0, SQFloat::_1, SQFloat::_0, SQFloat::_0,
                            SQFloat::_0, SQFloat::_0, SQFloat::_1, SQFloat::_0,
                            EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, SQFloat::_1);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(MATRIX);

	// Execution
    QVector3 vVectorUT(TRANSLATION);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a vector with all components set to zero.
/// </summary>
QTEST_CASE ( GetZeroVector_ReturnsANullVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QVector3 vVectorUT = QVector3::GetZeroVector();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a vector with all components set to one.
/// </summary>
QTEST_CASE ( GetVectorOfOnes_ReturnsAVectorOfOnes_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

	// Execution
    QVector3 vVectorUT = QVector3::GetVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to positive direction.
/// </summary>
QTEST_CASE ( GetUnitVectorX_ReturnsAUnitVectorThatPointsToPositiveDirectionOfXAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorX();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to positive direction.
/// </summary>
QTEST_CASE ( GetUnitVectorY_ReturnsAUnitVectorThatPointsToPositiveDirectionOfYAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorY();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in Z axis that points to positive direction.
/// </summary>
QTEST_CASE ( GetUnitVectorZ_ReturnsAUnitVectorThatPointsToPositiveDirectionOfZAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorZ();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to negative direction.
/// </summary>
QTEST_CASE ( GetUnitVectorX_ReturnsAUnitVectorThatPointsToNegativeDirectionOfXAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorInvX();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to negative direction.
/// </summary>
QTEST_CASE ( GetUnitVectorY_ReturnsAUnitVectorThatPointsToNegativeDirectionOfYAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorInvY();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if it returns a unit vector contained in Z axis that points to negative direction.
/// </summary>
QTEST_CASE ( GetUnitVectorZ_ReturnsAUnitVectorThatPointsToNegativeDirectionOfZAxis_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_1;

	// Execution
    QVector3 vVectorUT = QVector3::GetUnitVectorInvZ();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;

    const QVector3 OPERAND1 = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);
    const QVector3 OPERAND2 = QVector3(SQFloat::_3, SQFloat::_4, SQFloat::_5);

	// Execution
    QVector3 vVectorUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorAddition_VectorIsCorrectlyAddedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_4;

    const QVector3 OPERAND = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND + OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtraction_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_2 - SQFloat::_0_5 - SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_4;

    const QVector3 OPERAND1 = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);
    const QVector3 OPERAND2 = QVector3(SQFloat::_3, SQFloat::_4, SQFloat::_6);

	// Execution
    QVector3 vVectorUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorSubtraction_VectorIsCorrectlySubtractedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

    const QVector3 OPERAND = QVector3(-SQFloat::_0_25, SQFloat::_1, -SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND - OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector3 vVectorUT = VECTOR * SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

// End - Test Suite: QVector3
QTEST_SUITE_END()
