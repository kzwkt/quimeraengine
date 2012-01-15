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
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct1_ScalarIsCorrectlyMultipliedByVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector3 vVectorUT = SCALAR * VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

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

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorProduct2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;
    const float_q EXPECTED_VALUE_FOR_Z = 18;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVectorUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
QTEST_CASE ( OperatorProduct2_ProductIsCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = 10;
    const float_q EXPECTED_VALUE_FOR_Z = 18;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1 * OPERAND2;
    QVector3 vVector2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector1UT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector2UT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
QTEST_CASE ( OperatorProduct2_VectorCanBeMultipliedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_9;

    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND * OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 3 rows and 3 columns.
/// </summary>
QTEST_CASE ( OperatorProduct3_VectorIsCorrectlyMultipliedByMatrix3x3_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = 24;
    const float_q EXPECTED_VALUE_FOR_Y = 30;
    const float_q EXPECTED_VALUE_FOR_Z = 36;

    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 MATRIX = QBaseMatrix3x3(SQFloat::_0, SQFloat::_1, SQFloat::_2,
                                                 SQFloat::_3, SQFloat::_4, SQFloat::_5,
                                                 SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR * MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 3 rows and 4 columns.
/// </summary>
QTEST_CASE ( OperatorProduct4_VectorIsCorrectlyMultipliedByMatrix3x4_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = 32;
    const float_q EXPECTED_VALUE_FOR_Y = 38;
    const float_q EXPECTED_VALUE_FOR_Z = 44;
    const float_q EXPECTED_VALUE_FOR_W = 50;

    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const QBaseMatrix3x4 MATRIX = QBaseMatrix3x4(SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                 SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7,
                                                 SQFloat::_8, SQFloat::_9, (float_q)10, (float_q)11);

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QBaseVector4 vVectorUT = VECTOR * MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision1_VectorIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_2;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const float_q  SCALAR = SQFloat::_2;

	// Execution
    QVector3 vVectorUT = VECTOR / SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // Preparation
    const float_q  SCALAR = SQFloat::_0;

    // Execution
    bool bAssertionFailed = false;

    try
    {
        QVector3 vVectorUT;
        vVectorUT / SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorDivision2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = 2;
    const float_q EXPECTED_VALUE_FOR_Z = 3;

    const QVector3 OPERAND1 = QVector3(SQFloat::_2, SQFloat::_8, SQFloat::_9);
    const QVector3 OPERAND2 = QVector3(SQFloat::_2, SQFloat::_4, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND1 / OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivision2_DivisionIsNotCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.4;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0_5;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1 / OPERAND2;
    QVector3 vVector2UT = OPERAND2 / OPERAND1;

    // Verification
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector1UT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_NE(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_NE(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_NE(vVector2UT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
QTEST_CASE ( OperatorDivision2_VectorCanBeDividedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND / OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // Preparation
    const QVector3 OPERAND_WITH_ZERO_X = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1);
    const QVector3 OPERAND_WITH_ZERO_Y = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QVector3 OPERAND_WITH_ZERO_Z = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// Execution
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;
    bool bAssertionFailedWhenZEqualsZero = false;
    QVector3 vVectorUT;
    
    try
    {
        vVectorUT / OPERAND_WITH_ZERO_X;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_Y;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_Z;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenZEqualsZero = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenZEqualsZero);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_3 + SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_7;

    const QVector3 OPERAND1 = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);
    const QVector3 OPERAND2 = QVector3(SQFloat::_3, SQFloat::_4, SQFloat::_5);

	// Execution
    QVector3 vVectorUT = OPERAND1;
    vVectorUT += OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_VectorIsCorrectlyAddedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_4;

    const QVector3 OPERAND = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT += OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_VectorObjectIsCorrectlyAddedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_4;

    const QVector3 OPERAND = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT += vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)-2.75;
    const float_q EXPECTED_VALUE_FOR_Y = -SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_4;

    const QVector3 OPERAND1 = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);
    const QVector3 OPERAND2 = QVector3(SQFloat::_3, SQFloat::_4, SQFloat::_6);

	// Execution
    QVector3 vVectorUT = OPERAND1;
    vVectorUT -= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_VectorIsCorrectlySubtractedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

    const QVector3 OPERAND = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT -= OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_VectorObjectIsCorrectlySubtractedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;

    const QVector3 OPERAND = QVector3(SQFloat::_0_25, SQFloat::_1, SQFloat::_2);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT -= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

// End - Test Suite: QVector3
QTEST_SUITE_END()
