// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QVector3.h"

#include "QVector3WhiteBox.h"
#include "QMatrix4x3.h"
#include "QMatrix4x4.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QSpaceConversionMatrix.h"
#include "QQuaternion.h"
#include "QDualQuaternion.h"
#include "SQAngle.h"

using Kinesis::QuimeraEngine::Tools::Math::QVector3;

QTEST_SUITE_BEGIN( QVector3_TestSuite )

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByVector_Test )
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
/// Checks if that every input vector's component is copied to the right target vector's component.
/// </summary>
QTEST_CASE ( Constructor8_VectorComponentsAreCopiedIntoCorrectComponents_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

	QBaseVector3 INPUT_VECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

	// Execution
	QVector3 vVectorUT(INPUT_VECTOR);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if that every input vector's component is copied to the right target vector's component.
/// </summary>
QTEST_CASE ( Constructor9_VectorComponentsAreCopiedIntoCorrectComponents_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

	QBaseVector4 INPUT_VECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, SQFloat::_0);

	// Execution
	QVector3 vVectorUT(INPUT_VECTOR);

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
QTEST_CASE ( GetUnitVectorInvX_ReturnsAUnitVectorThatPointsToNegativeDirectionOfXAxis_Test )
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
QTEST_CASE ( GetUnitVectorInvY_ReturnsAUnitVectorThatPointsToNegativeDirectionOfYAxis_Test )
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
QTEST_CASE ( GetUnitVectorInvZ_ReturnsAUnitVectorThatPointsToNegativeDirectionOfZAxis_Test )
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
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)10.0f;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)18.0f;

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
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1 * OPERAND2;
    QVector3 vVector2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK(vVector1UT == vVector2UT);
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
    const float_q EXPECTED_VALUE_FOR_X = (float_q)24.0f;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)30.0f;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)36.0f;

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
    const float_q EXPECTED_VALUE_FOR_X = (float_q)32.0f;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)38.0f;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)44.0f;
    const float_q EXPECTED_VALUE_FOR_W = (float_q)50.0f;

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
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

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
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1 / OPERAND2;
    QVector3 vVector2UT = OPERAND2 / OPERAND1;

    // Verification
    BOOST_CHECK(vVector1UT != vVector2UT);
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

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_2);
    const float_q  SCALAR = SQFloat::_0_5;

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT *= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that a vector component is multiplied and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_VectorIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = (float_q)1152;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)1728;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)2304;

    const QVector3 VECTOR = QVector3(SQFloat::_2, SQFloat::_3, SQFloat::_4);

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT *= vVectorUT.x; // x2  Now x==4,    y==6,    z==8
    vVectorUT *= vVectorUT.y; // x6  Now x==24,   y==36,   z==48
    vVectorUT *= vVectorUT.z; // x48 Now x==1152, y==1728, z==2304

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)10.0f;
    const float_q EXPECTED_VALUE_FOR_Z = (float_q)18.0f;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVectorUT = OPERAND1;
    vVectorUT *= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_ProductIsCommutative_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1;
    vVector1UT *= OPERAND2;
    QVector3 vVector2UT = OPERAND2;
    vVector2UT *= OPERAND1;

    // Verification
    BOOST_CHECK(vVector1UT == vVector2UT);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorCanBeMultipliedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_9;

    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT *= OPERAND;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if a vector object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_VectorObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 OPERAND = QVector3(SQFloat::_2, SQFloat::_3, SQFloat::_1);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT *= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 3 rows and 3 columns.
/// </summary>
QTEST_CASE ( OperatorProductAssignation3_VectorIsCorrectlyMultipliedByMatrix3x3_Test )
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
    QVector3 vVectorUT = VECTOR;
    vVectorUT *= MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_VectorIsCorrectlyDividedByScalar_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_2;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const float_q  SCALAR = SQFloat::_2;

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT /= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // Preparation
    const float_q  SCALAR = SQFloat::_0;

    // Execution
    bool bAssertionFailed = false;

    try
    {
        QVector3 vVectorUT;
        vVectorUT /= SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that a vector component is divided and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation1_VectorComponentIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0_5;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_2, SQFloat::_4, SQFloat::_8);

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT /= vVectorUT.x; // :2 Now x==1,    y==2,   z==4
    vVectorUT /= vVectorUT.y; // :2 Now x==0.5,  y==1,   z==2
    vVectorUT /= vVectorUT.z; // :2 Now x==0.25, y==0.5, z==1

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = 2;
    const float_q EXPECTED_VALUE_FOR_Z = 3;

    const QVector3 OPERAND1 = QVector3(SQFloat::_2, SQFloat::_8, SQFloat::_9);
    const QVector3 OPERAND2 = QVector3(SQFloat::_2, SQFloat::_4, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND1;
    vVectorUT /= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_DivisionIsNotCommutative_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0_25;
    const float_q EXPECTED_VALUE_FOR_Y = (float_q)0.4;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0_5;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    QVector3 vVector1UT = OPERAND1;
    vVector1UT /= OPERAND2;
    QVector3 vVector2UT = OPERAND2;
    vVector2UT /= OPERAND1;

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
QTEST_CASE ( OperatorDivisionAssignation2_VectorCanBeDividedByItself_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_1;

    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = OPERAND;
    vVectorUT /= vVectorUT;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation2_AssertionFailsWhenAnyComponentEqualsZero_Test )
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
        vVectorUT /= OPERAND_WITH_ZERO_X;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_Y;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_Z;
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
/// Checks that a vector is correctly assigned to another vector.
/// </summary>
QTEST_CASE ( OperatorAssignation_VectorIsAssignedProperlyToAnother_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that all vector components are correctly negated.
/// </summary>
QTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = -VECTOR;

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the length of the vector is correctly calculated.
/// </summary>
QTEST_CASE ( GetLength_LengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // Preparation
    const float_q EXPECTED_LENGTH = SQFloat::_7;

    const QVector3 VECTOR = QVector3(SQFloat::_2, SQFloat::_3, SQFloat::_6);

	// Execution
    float_q fLengthUT = VECTOR.GetLength();

    // Verification
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the squared length of the vector is correctly calculated.
/// </summary>
QTEST_CASE ( GetSquaredLength_SquaredLengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE = (float_q)49.0f;

    const QVector3 VECTOR = QVector3(SQFloat::_2, SQFloat::_3, SQFloat::_6);

	// Execution
    float_q fSquaredLengthUT = VECTOR.GetSquaredLength();

    // Verification
    BOOST_CHECK_EQUAL(fSquaredLengthUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common vector becomes a unit vector.
/// </summary>
QTEST_CASE ( Normalize_CommonVectorIsCorrectlyNormalized_Test )
{
    // Preparation
    const float_q EXPECTED_SQUAREDLENGTH = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR.Normalize();

    // Verification
    float_q fSquaredLength = vVectorUT.GetSquaredLength();

    BOOST_CHECK(SQFloat::AreEquals(fSquaredLength, EXPECTED_SQUAREDLENGTH));
}

/// <summary>
/// Checks that the assertion fails when a null vector is to be normalized.
/// </summary>
QTEST_CASE ( Normalize_AssertionFailsWhenNullVectorIsToBeNormalized_Test )
{
    // Preparation
    const QVector3 VECTOR = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QVector3 vVectorUT = VECTOR.Normalize();
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that a common vector is correctly inverted.
/// </summary>
QTEST_CASE ( Invert_CommonVectorIsCorrectlyInverted_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = -SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = -SQFloat::_3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR.Invert();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that all vector components are set to one.
/// </summary>
QTEST_CASE ( ResetToOne_AllVectorComponentsAreSetToOne_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_1;

    const QVector3 VECTOR = QVector3(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT.ResetToOne();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all vector components are set to zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllVectorComponentsAreSetToZero_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    const QVector3 VECTOR = QVector3(SQFloat::_1, -SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = VECTOR;
    vVectorUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that it returns true when all vector components equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenAllVectorComponentsEqualZero_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = true;

    const QVector3 VECTOR = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);

	// Execution
    bool bResult = VECTOR.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenNotAllVectorComponentsEqualZero_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = false;

    const QVector3 VECTOR_X_NOT_EQUAL_ZERO = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 VECTOR_Y_NOT_EQUAL_ZERO = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 VECTOR_Z_NOT_EQUAL_ZERO = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1);

	// Execution
    bool bResult = VECTOR_X_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Y_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Z_NOT_EQUAL_ZERO.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when all vector components equal one.
/// </summary>
QTEST_CASE ( IsVectorOfOnes_ReturnsTrueWhenAllVectorComponentsEqualOne_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = true;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);

	// Execution
    bool bResult = VECTOR.IsVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal one.
/// </summary>
QTEST_CASE ( IsVectorOfOnes_ReturnsFalseWhenNotAllVectorComponentsEqualOne_Test )
{
    // Preparation
    const bool EXPECTED_RESULT = false;

    const QVector3 VECTOR_X_NOT_EQUAL_ONE = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_1);
    const QVector3 VECTOR_Y_NOT_EQUAL_ONE = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_1);
    const QVector3 VECTOR_Z_NOT_EQUAL_ONE = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);

	// Execution
    bool bResult = VECTOR_X_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Y_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Z_NOT_EQUAL_ONE.IsVectorOfOnes();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned dot product result for 2 common vectors equals the expected value.
/// </summary>
QTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonVectors_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = (float_q)32;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    float_q fResultUT = OPERAND1.DotProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
QTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

	// Execution
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals zero when vectors are orthogonal.
/// </summary>
QTEST_CASE ( DotProduct_DotProductEqualsZeroWhenVectorsAreOrthogonal_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QVector3 OPERAND1 = QVector3(SQFloat::_3, SQFloat::_0, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_0, SQFloat::_3, SQFloat::_0);
    const QVector3 OPERAND3 = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_3);

	// Execution
    float_q fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProduct(OPERAND3);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null vector.
/// </summary>
QTEST_CASE ( DotProduct_ReturnsZeroWhenAOperandIsNullVector_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QVector3 NONNULL_VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 NULL_VECTOR = QVector3::GetZeroVector();

	// Execution
    float_q fResult1UT = NONNULL_VECTOR.DotProduct(NULL_VECTOR);
    float_q fResult2UT = NULL_VECTOR.DotProduct(NONNULL_VECTOR);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common vectors equals the expected value.
/// </summary>
QTEST_CASE ( DotProductAngle_ReturnsAngleBetween2CommonVectors_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
QTEST_CASE ( DotProductAngle_DotProductAngleIsCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        float_q EXPECTED_RESULT = SQAngle::_45;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_QuarterPi;
    #endif

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);

	// Execution
    float_q fResult1UT = OPERAND1.DotProductAngle(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProductAngle(OPERAND1);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when vectors are parallel.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsZeroWhenVectorsAreParallel_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT = SQFloat::_0;

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_9, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when vectors are orthogonal.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorsAreOrthogonal_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_90;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_HalfPi;
    #endif

    const QVector3 OPERAND1 = QVector3(SQFloat::_5, SQFloat::_0, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_0, SQFloat::_5, SQFloat::_0);
    const QVector3 OPERAND3 = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_5);

	// Execution
    float_q fResult1UT = OPERAND1.DotProductAngle(OPERAND2);
    float_q fResult2UT = OPERAND2.DotProductAngle(OPERAND3);

    // Verification
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vectors are opposite.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleEqualsPiRadiansOr180DegreesWhenVectorsAreOpposite_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q EXPECTED_RESULT = SQAngle::_180;
    #else
        const float_q EXPECTED_RESULT = SQAngle::_Pi;
    #endif

    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

	// Execution
    float_q fResultUT = OPERAND1.DotProductAngle(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleIsAlwaysPositive_Test )
{
    // Preparation
    const QVector3 REFERENCE_OPERAND = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);                                // _
    const QVector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, SQFloat::_1, SQFloat::_0);  // \_
    const QVector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, -SQFloat::_1, SQFloat::_0); // /¨

	// Execution
    float_q fResult1UT = REFERENCE_OPERAND.DotProductAngle(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.DotProductAngle(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // Verification
    BOOST_CHECK( SQFloat::IsPositive(fResult1UT) );
    BOOST_CHECK( SQFloat::IsPositive(fResult2UT) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector are not opposite.
/// </summary>
QTEST_CASE ( DotProductAngle_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorsAreNotOpposite_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_180;
    #else
        const float_q HALF_CIRCUMFERENCE_ANGLE = SQAngle::_Pi;
    #endif

    const QVector3 REFERENCE_OPERAND = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);                                // _
    const QVector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, SQFloat::_1, SQFloat::_0);  // \_
    const QVector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = QVector3(-SQFloat::_1, -SQFloat::_1, SQFloat::_0); // /¨

	// Execution
    float_q fResult1UT = REFERENCE_OPERAND.DotProductAngle(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_q fResult2UT = REFERENCE_OPERAND.DotProductAngle(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // Verification
    BOOST_CHECK( SQFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SQFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that a correct vector is obtained by applying the cross product to 2 common vectors.
/// </summary>
QTEST_CASE ( CrossProduct_AThirdVectorIsCorrectlyCalculated_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QVector3 OPERAND2 = QVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 EXPECTED_RESULT = QVector3(-SQFloat::_10, (float_q)13.0, (float_q)-4.0);

	// Execution
    QVector3 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that a null vector is obtained by applying the cross product to 2 parallel vectors that point at the same direction.
/// </summary>
QTEST_CASE ( CrossProduct_ResultIsNullWhenVectorsAreParallelAndSameDirection_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_2, SQFloat::_4, SQFloat::_6);
    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that a null vector is obtained by applying the cross product to 2 parallel vectors that point at opposite direction.
/// </summary>
QTEST_CASE ( CrossProduct_ResultIsNullWhenVectorsAreParallelAndOppositeDirection_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(-SQFloat::_1, -SQFloat::_2, -SQFloat::_3);
    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that follows left-handed rules, so +X x +Y = +Z.
/// </summary>
QTEST_CASE ( CrossProduct_FollowsLeftHandedRule_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 OPERAND2 = QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1);

	// Execution
    QVector3 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that null vector is obtained when at least one of the operands is null vector.
/// </summary>
QTEST_CASE ( CrossProduct_ReturnsNullVectorWhenAOperandIsNullVector_Test )
{
    // Preparation
    const float_q EXPECTED_RESULT_FOR_ALL = SQFloat::_0;

    const QVector3 NULL_VECTOR = QVector3::GetZeroVector();
    const QVector3 NONNULL_VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT1 = NULL_VECTOR.CrossProduct(NONNULL_VECTOR);;
    QVector3 vVectorUT2 = NONNULL_VECTOR.CrossProduct(NULL_VECTOR);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT1.x, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT1.y, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT1.z, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.x, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.y, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.z, EXPECTED_RESULT_FOR_ALL);
}

/// <summary>
/// Checks that the cross product is correctly calculated when the same instance is used for both operands.
/// </summary>
QTEST_CASE ( CrossProduct_BehavesCorrectlyWhenSameInstanceIsUsedAsParameter_Test )
{
    // Preparation
    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = OPERAND.CrossProduct(OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that a correct vector is obtained as result of interpolating between 2 common vectors.
/// </summary>
QTEST_CASE ( Lerp_CorrectLerpedVectorIsObtainedForTwoCommonVectors_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 EXPECTED_RESULT = QVector3((float_q)2.5f, (float_q)3.5f, (float_q)4.5f);

	// Execution
    QVector3 vVectorUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent vectors is the same vector.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingTwoEquivalentVectorsGivesSameVector_Test )
{
    // Preparation
    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

	// Execution
    QVector3 vVectorUT = EXPECTED_RESULT.Lerp(SQFloat::_0_5, EXPECTED_RESULT);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 opposite vectors is a null vector.
/// </summary>
QTEST_CASE ( Lerp_InterpolatingInTheMiddleOfTwoOppositeVectorsGivesNullVector_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = -OPERAND1;
    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = OPERAND1.Lerp(SQFloat::_0_5, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector obtained when using a non-null vector and a null vector is just the proportion of the non-null vector.
/// </summary>
QTEST_CASE ( Lerp_WhenUsedNonNullVectorAndNullVectorTheResultIsAScaledNonNullVector_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3::GetZeroVector();
    const QVector3 EXPECTED_RESULT = OPERAND1 * SQFloat::_0_25;

	// Execution
    QVector3 vVectorUT = OPERAND1.Lerp(SQFloat::_0_25, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned vector is the input vector.
/// </summary>
QTEST_CASE ( Lerp_ProportionZeroMeansInputVector_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 EXPECTED_RESULT = OPERAND2;

	// Execution
    QVector3 vVectorUT = OPERAND1.Lerp(SQFloat::_0, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned vector is the resident vector.
/// </summary>
QTEST_CASE ( Lerp_ProportionOneMeansResidentVector_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 EXPECTED_RESULT = OPERAND1;

	// Execution
    QVector3 vVectorUT = OPERAND1.Lerp(SQFloat::_1, OPERAND2);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the distance is correctly calcualted for two common vectors.
/// </summary>
QTEST_CASE ( Distance_CorrectlyCalculatedForTwoCommonVectors_Test )
{
    // Preparation
    const QVector3 OPERAND1 = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 OPERAND2 = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const float_q EXPECTED_RESULT = (float_q)5.196152422706632;

	// Execution
    float_q fDistancerUT = OPERAND1.Distance(OPERAND2);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(fDistancerUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the distance equals zero when both vectors are the same.
/// </summary>
QTEST_CASE ( Distance_ExactlyZeroWhenTwoVectorsAreTheSame_Test )
{
    // Preparation
    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const float_q EXPECTED_RESULT = SQFloat::_0;

	// Execution
    float_q fDistancerUT = OPERAND.Distance(OPERAND);

    // Verification
    BOOST_CHECK_EQUAL(fDistancerUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks the distance between 2 opposite vectors equals the sume of their lengths.
/// </summary>
QTEST_CASE ( Distance_ForTwoOppositeVectorsResultEqualsSumOfTheirLengths_Test )
{
    // Preparation
    const QVector3 OPERAND = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QVector3 OPPOSITE_OPERAND = QVector3(-SQFloat::_0_5, -SQFloat::_1, -SQFloat::_2);
    const float_q EXPECTED_RESULT = OPERAND.GetLength() + OPPOSITE_OPERAND.GetLength();

	// Execution
    float_q fDistancerUT = OPERAND.Distance(OPPOSITE_OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(fDistancerUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary quaternion.
/// </summary>
QTEST_CASE ( Transform1_VectorIsCorrectlyTransformedByCommonQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QQuaternion TRANSFORMATION = QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QVector3 EXPECTED_RESULT = QVector3( (float_q)-3.5355339,
                                               (float_q)-2.1213205,
                                               (float_q)-1.9999995);

    // Results have been obtained by using DirectX SDK
    // D3DXQUATERNION qRot, qVector, qConjugate;
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXQuaternionRotationYawPitchRoll(&qRot, fYaw, fPitch, fRoll);
    // D3DXQuaternionNormalize(&qRot, &qRot);
    // D3DXQuaternionConjugate(&qConjugate, &qRot);
    // qVector.x = 1; qVector.y = 2; qVector.z = 4; qVector.w = 0;
    // D3DXQuaternionMultiply(&qVector, &qRot, &qv);
    // D3DXQuaternionMultiply(&qVector, &qVector, &qConjugate);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity quaternion.
/// </summary>
QTEST_CASE ( Transform1_VectorDoesntChangeWhenTransformedByIdentityQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QQuaternion UNIT_QUATERNION = QQuaternion::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(UNIT_QUATERNION);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector is nulled when the quaternion is null.
/// </summary>
QTEST_CASE ( Transform1_VectorIsNullWhenQuaternionIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QQuaternion NULL_QUATERNION = QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_QUATERNION);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary dual quaternion.
/// </summary>
QTEST_CASE ( Transform2_VectorIsCorrectlyTransformedByCommonDualQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QDualQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QDualQuaternion TRANSFORMATION = QDualQuaternion(QVector3(SQFloat::_3, SQFloat::_4, SQFloat::_5),
                                                           QQuaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z));
    const QVector3 EXPECTED_RESULT = QVector3( (float_q)-6.5355339,
                                               (float_q)-6.1213205,
                                               (float_q)-6.9999995);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION); // [TODO] Thund: Fails.

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity dual quaternion.
/// </summary>
QTEST_CASE ( Transform2_VectorDoesntChangeWhenTransformedByIdentityDualQuaternion_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QDualQuaternion;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QDualQuaternion TRANSFORMATION = QDualQuaternion::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector is nulled when the dual quaternion is null.
/// </summary>
QTEST_CASE ( Transform2_VectorIsNullWhenDualQuaternionIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QDualQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QDualQuaternion NULL_DUALQUATERNION = QDualQuaternion(QVector3::GetZeroVector(), QQuaternion(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0));

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_DUALQUATERNION);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary rotation matrix.
/// </summary>
QTEST_CASE ( Transform3_VectorIsCorrectlyTransformedByCommonRotationMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const QVector3 EXPECTED_RESULT = QVector3( (float_q)0.70710671,
                                               (float_q)-3.9999990,
                                               (float_q)-2.1213202);

    // Results calculated with DirectX SDK
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 2, 4);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform3_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector is nulled when the rotation matrix is null.
/// </summary>
QTEST_CASE ( Transform3_VectorIsNullWhenRotationMatrixIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QRotationMatrix3x3 NULL_MATRIX = QRotationMatrix3x3(QMatrix3x3::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks the the rotation is applied following left-handed rules.
/// </summary>
QTEST_CASE ( Transform3_RotationFollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQFloat::_0;
    const float_q EULER_ANGLE_Y = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Z = SQFloat::_0;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQFloat::_0;
    const float_q EULER_ANGLE_Y = SQAngle::_90;
    const float_q EULER_ANGLE_Z = SQFloat::_0;
#endif

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 TRANSFORMATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_0, SQFloat::_0, -SQFloat::_1);

    // Results calculated with DirectX SDK
    // float_q fYaw = SQAngle::_HalfPi;
    // float_q fPitch = SQFloat::_0;
    // float_q fRoll = SQFloat::_0;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 0, 0);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary scale matrix.
/// </summary>
QTEST_CASE ( Transform4_VectorIsCorrectlyTransformedByCommonScaleMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_0_25, SQFloat::_6, -SQFloat::_4);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform4_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QScalingMatrix3x3 TRANSFORMATION = QScalingMatrix3x3::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector is nulled when the scale matrix is null.
/// </summary>
QTEST_CASE ( Transform4_VectorIsNullWhenScaleMatrixIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QScalingMatrix3x3 NULL_MATRIX = QScalingMatrix3x3(QMatrix3x3::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Template method used by Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSFORMATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);

    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_3, SQFloat::_6, -SQFloat::_2);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary translation matrix.
/// </summary>
QTEST_CASE ( Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSFORMATION = QTranslationMatrix<MatrixType>::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform5_VectorIsNullWhenTranslationMatrixIsNull_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorIsNullWhenTranslationMatrixIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> NULL_MATRIX = QTranslationMatrix<MatrixType>(MatrixType::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector doesn't change when the translation matrix is null.
/// </summary>
QTEST_CASE ( Transform5_VectorIsNullWhenTranslationMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform5_VectorIsNullWhenTranslationMatrixIsNull_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform5_VectorIsNullWhenTranslationMatrixIsNull_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(SQAngle::_HalfPi, SQAngle::_Pi, SQAngle::_QuarterPi);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const QVector3 EXPECTED_RESULT = QVector3((float_q)4.0658631, (float_q)4.0000000, (float_q)-4.4194174);

    // Results calculated using DirectX SDK
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    // D3DXMatrixTranslation(&translation, SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    // D3DXVECTOR3 vVector(1, 2, 4);
    // transformation = scaling * rotation * translation;
    // D3DXVec3TransformNormal(&vVector, &vVector, &transformation);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION); // [TODO] Thund: Fails.

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary translation matrix.
/// </summary>
QTEST_CASE ( Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorIsNullWhenTransformationMatrixIsNull_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_VectorIsNullWhenTransformationMatrixIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTransformationMatrix<MatrixType> NULL_MATRIX = QTransformationMatrix<MatrixType>(MatrixType::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector is nulled when the transformation matrix is null.
/// </summary>
QTEST_CASE ( Transform6_VectorIsNullWhenTransformationMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    Transform6_VectorIsNullWhenTransformationMatrixIsNull_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    Transform6_VectorIsNullWhenTransformationMatrixIsNull_Template<QMatrix4x4>();
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
QTEST_CASE ( Transform7_VectorIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3),
                                  QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_1),
                                  QVector3(SQFloat::_0, SQFloat::_1, SQFloat::_0));

    const QVector3 EXPECTED_RESULT = QVector3( (float_q)0.89442724,
                                               (float_q)-1.1925696,
                                               (float_q)-4.3333330);

    // Results calculated with DirectX SDK
    // D3DXMATRIX transformation;
    // D3DXVECTOR3 vEye(1, 2, 3), vUp(0, 1, 0), vAt(0, 0, 1);
    // D3DXMatrixLookAtLH(&transformation, &vEye, &vAt, &vUp);
    // D3DXVec3TransformNormal(&vVector, &vVector, &transformation);

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(CONVERSION); // [TODO] Thund: Fails.

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( Transform7_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QSpaceConversionMatrix CONVERSION = QSpaceConversionMatrix(QMatrix4x4::GetIdentity());
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(CONVERSION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector is nulled when the space conversion matrix is null.
/// </summary>
QTEST_CASE ( Transform7_VectorIsNullWhenSpaceConversionMatrixIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

    const QVector3 VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QSpaceConversionMatrix NULL_MATRIX = QSpaceConversionMatrix(QMatrix4x4::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    const QVector3 VECTOR = QVector3(SQFloat::_0_25, (float_q)-0.000002f, (float_q)40000.0f );
    const string_q EXPECTED_STRING_FORM = QE_L("V3(0.25,-1.99999999e-006,40000)");

	// Execution
    QVector3 vVectorUT = VECTOR;
    string_q strStringForm = vVectorUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

/// <summary>
/// Template method used by TransformImp1_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp1_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSFORMATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);

    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_3, SQFloat::_6, -SQFloat::_2);

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary translation matrix.
/// </summary>
QTEST_CASE ( TransformImp1_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp1_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp1_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp1_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp1_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSFORMATION = QTranslationMatrix<MatrixType>::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( TransformImp1_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp1_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp1_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp1_VectorIsNullWhenTranslationMatrixIsNull_Test to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp1_VectorDoesntChangeWhenTranslationMatrixIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> NULL_MATRIX = QTranslationMatrix<MatrixType>(MatrixType::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector doesn't change when the transformation matrix is null.
/// </summary>
QTEST_CASE ( TransformImp1_VectorDoesntChangeWhenTranslationMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp1_VectorDoesntChangeWhenTranslationMatrixIsNull_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp1_VectorDoesntChangeWhenTranslationMatrixIsNull_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp2_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp2_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Y = SQAngle::_Pi;
    const float_q EULER_ANGLE_Z = SQAngle::_QuarterPi;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQAngle::_90;
    const float_q EULER_ANGLE_Y = SQAngle::_180;
    const float_q EULER_ANGLE_Z = SQAngle::_45;
#endif

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const QVector3 EXPECTED_RESULT = QVector3((float_q)4.0658631, (float_q)4.0000000, (float_q)-4.4194174);

    // Results calculated using DirectX SDK
    // float_q fYaw = SQAngle::_Pi;
    // float_q fPitch = SQAngle::_HalfPi;
    // float_q fRoll = SQAngle::_QuarterPi;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SQFloat::_0_25, SQFloat::_3, -SQFloat::_1);
    // D3DXMatrixTranslation(&translation, SQFloat::_2, SQFloat::_4, -SQFloat::_6);
    // D3DXVECTOR3 vVector(1, 2, 4);
    // transformation = scaling * rotation * translation;
    // D3DXVec3TransformNormal(&vVector, &vVector, &transformation);

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(TRANSFORMATION); // [TODO] Thund: Fails.

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks the vector is correctly transformed by an arbitrary transformation matrix.
/// </summary>
QTEST_CASE ( TransformImp2_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp2_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp2_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>::GetIdentity();
    const QVector3 EXPECTED_RESULT = VECTOR;

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
QTEST_CASE ( TransformImp2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp2_VectorIsNullWhenTransformationMatrixIsNull_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp2_VectorIsNullWhenTransformationMatrixIsNull_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_4);
    const QTransformationMatrix<MatrixType> NULL_MATRIX = QTransformationMatrix<MatrixType>(MatrixType::GetZeroMatrix());

    const QVector3 EXPECTED_RESULT = QVector3::GetZeroVector();

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(NULL_MATRIX);

    // Verification
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
}

/// <summary>
/// Checks that the vector is nulled when the transformation matrix is null.
/// </summary>
QTEST_CASE ( TransformImp2_VectorIsNullWhenTransformationMatrixIsNull_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp2_VectorIsNullWhenTransformationMatrixIsNull_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp2_VectorIsNullWhenTransformationMatrixIsNull_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by TransformImp2_RotationFollowsLeftHandedRules_Test to test
/// using different template parameters for class QTransformationMatrix.
/// </summary>
template<class MatrixType>
void TransformImp2_RotationFollowsLeftHandedRules_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QVector3WhiteBox;

#if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
    const float_q EULER_ANGLE_X = SQFloat::_0;
    const float_q EULER_ANGLE_Y = SQAngle::_HalfPi;
    const float_q EULER_ANGLE_Z = SQFloat::_0;
#elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
    const float_q EULER_ANGLE_X = SQFloat::_0;
    const float_q EULER_ANGLE_Y = SQAngle::_90;
    const float_q EULER_ANGLE_Z = SQFloat::_0;
#endif

    const QVector3WhiteBox VECTOR = QVector3(SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QTranslationMatrix<MatrixType> TRANSLATION = QTranslationMatrix<MatrixType>(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION = QRotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const QScalingMatrix3x3 SCALE = QScalingMatrix3x3(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QTransformationMatrix<MatrixType> TRANSFORMATION = QTransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const QVector3 EXPECTED_RESULT = QVector3(SQFloat::_0, SQFloat::_0, -SQFloat::_1);

    // Results calculated using DirectX SDK
    // float_q fYaw = SQAngle::_HalfPi;
    // float_q fPitch = SQFloat::_0;
    // float_q fRoll = SQFloat::_0;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SQFloat::_1, SQFloat::_1, -SQFloat::_1);
    // D3DXMatrixTranslation(&translation, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    // D3DXVECTOR3 vVector(1, 0, 0);
    // transformation = scaling * rotation * translation;
    // D3DXVec3TransformNormal(&vVector, &vVector, &transformation);

	// Execution
    QVector3WhiteBox vVectorUT = VECTOR.TransformImp(TRANSFORMATION); // [TODO] Thund: Fails.

    // Verification
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SQFloat::AreEquals(vVectorUT.z, EXPECTED_RESULT.z) );
}

/// <summary>
/// Checks that the vector is nulled when the transformation matrix is null.
/// </summary>
QTEST_CASE ( TransformImp2_RotationFollowsLeftHandedRules_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    TransformImp2_RotationFollowsLeftHandedRules_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    TransformImp2_RotationFollowsLeftHandedRules_Template<QMatrix4x4>();
}
// End - Test Suite: QVector3
QTEST_SUITE_END()
