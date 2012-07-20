// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QMatrix3x4.h"
#include "QBaseMatrix4x3.h"
#include "QBaseMatrix4x4.h"
#include "QBaseMatrix3x3.h"

using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x4;

QTEST_SUITE_BEGIN( QMatrix3x4_TestSuite )

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_EveryElementIsMultipliedByTheScalar_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_1, SQFloat::_2,  SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5, SQFloat::_6,  SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9, SQFloat::_10, (float_q)11.0f, (float_q)12.0f);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)14.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)18.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)20.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)24.0f;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix3x4 matrixUT = SCALAR_VALUE * MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // Execution
    QMatrix3x4 matrixUT;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_10 + SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_23 = SQFloat::_10 + SQFloat::_2;

	// Execution
    const QMatrix3x4 MATRIX_TO_COPY(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                                    EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                                    EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23);

    // Execution
    QMatrix3x4 matrixUT = MATRIX_TO_COPY;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
QTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;
    const QBaseMatrix3x4 EXPECTED_VALUE(SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                        SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7,
                                        SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0f);

    // Execution
    QMatrix3x4 matrixUT(EXPECTED_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks if the value provided is set to all the matrix components.
/// </summary>
QTEST_CASE ( Constructor4_ValueIsSetForAllComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

    // Execution
    QMatrix3x4 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
QTEST_CASE ( Constructor5_ValuesAreSetProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_10+SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_23 = SQFloat::_10+SQFloat::_2;

	// Execution
    QMatrix3x4 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor6_MatrixComponentsAreFilledWithValidReferenceTo12Floats_Test )
{
   // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_10 + SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_23 = SQFloat::_10 + SQFloat::_2;


    float_q* VALID_ARRAY_OF_12_FLOATS = new float_q[16];
    VALID_ARRAY_OF_12_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_12_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_12_FLOATS[2] = EXPECTED_VALUE_FOR_02;
    VALID_ARRAY_OF_12_FLOATS[3] = EXPECTED_VALUE_FOR_03;
    VALID_ARRAY_OF_12_FLOATS[4] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_12_FLOATS[5] = EXPECTED_VALUE_FOR_11;
    VALID_ARRAY_OF_12_FLOATS[6] = EXPECTED_VALUE_FOR_12;
    VALID_ARRAY_OF_12_FLOATS[7] = EXPECTED_VALUE_FOR_13;
    VALID_ARRAY_OF_12_FLOATS[8] = EXPECTED_VALUE_FOR_20;
    VALID_ARRAY_OF_12_FLOATS[9] = EXPECTED_VALUE_FOR_21;
    VALID_ARRAY_OF_12_FLOATS[10] = EXPECTED_VALUE_FOR_22;
    VALID_ARRAY_OF_12_FLOATS[11] = EXPECTED_VALUE_FOR_23;

	// Execution
    QMatrix3x4 matrixUT(VALID_ARRAY_OF_12_FLOATS);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);

    // Cleaning
    delete [] VALID_ARRAY_OF_12_FLOATS;
    VALID_ARRAY_OF_12_FLOATS = null_q;
}

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // Preparation
    const float_q* NULL_ARRAY = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QMatrix3x4 vMatrixUT(NULL_ARRAY);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if matrix components are set to the correct values packed in valid vf32 objects.
/// </summary>
QTEST_CASE ( Constructor7_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_10 + SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_23 = SQFloat::_10 + SQFloat::_2;


	vf32_q PACK0, PACK1, PACK2;
	SQVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03, PACK0);
	SQVF32::Pack(EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13, PACK1);
	SQVF32::Pack(EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23, PACK2);

	// Execution
	QMatrix3x4 matrixUT(PACK0, PACK1, PACK2);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero.
/// </summary>
QTEST_CASE ( GetZeroMatrix_AllElementsEqualZero_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

	// Execution
    QMatrix3x4 matrixUT = QMatrix3x4::GetZeroMatrix();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
QTEST_CASE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DIAGONAL = SQFloat::_1;

	// Execution
    QMatrix3x4 matrixUT = QMatrix3x4::GetIdentity();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct1_EveryElementIsMultipliedByTheScalar_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;
    const QMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)14.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)16.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)18.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)20.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)24.0f;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix3x4 matrixUT = MATRIX * SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QMatrix3x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix4x3 OPERAND2((float_q)13.0f, (float_q)14.0f, (float_q)15.0f,
                                  (float_q)16.0f, (float_q)17.0f, (float_q)18.0f,
                                  (float_q)19.0f, (float_q)20.0f, (float_q)21.0f,
                                  (float_q)22.0f, (float_q)23.0f, (float_q)24.0f);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)190.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)200.0f;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)210.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)470.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)496.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)522.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)750.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)792.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)834.0f;

    // Execution
    QBaseMatrix3x3 matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix3x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix4x4 OPERAND2((float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f,
                                  (float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)210.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)220.0f;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)230.0f;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)240.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)514.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)540.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)566.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)592.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)818.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)860.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)902.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)944.0f;

    // Execution
    QMatrix3x4 matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision_EveryElementIsDividedByTheScalar_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                            SQFloat::_10,   (float_q)12.0f, (float_q)14.0f, (float_q)16.0f,
                            (float_q)18.0f, (float_q)20.0f, (float_q)22.0f, (float_q)24.0f);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)11.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)12.0f;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix3x4 matrixUT = MATRIX / SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision_AssertionFailsWhenScalarEqualsZero_Test )
{
    // Preparation
    const float_q ZERO_SCALAR = SQFloat::_0;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QMatrix3x4 vMatrixUT;
        vMatrixUT / ZERO_SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that two common matrices are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_CommonMatricesAreCorrectlyAdded_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QMatrix3x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix3x4 OPERAND2((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)18.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)20.0f;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)24.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)26.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)28.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)30.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)32.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)34.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)36.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)38.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)40.0f;

    // Execution
    QMatrix3x4 matrixUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that two common matrices are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtraction_CommonMatricesAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QMatrix3x4 OPERAND1((float_q)18.0f, (float_q)20.0f, (float_q)22.0f, (float_q)24.0f,
                              (float_q)26.0f, (float_q)28.0f, (float_q)30.0f, (float_q)32.0f,
                              (float_q)34.0f, (float_q)36.0f, (float_q)38.0f, (float_q)40.0f);

    const QBaseMatrix3x4 OPERAND2((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f);

    const QMatrix3x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    // Execution
    QMatrix3x4 matrixUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_EveryElementIsDividedByTheScalar_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                            SQFloat::_10,   (float_q)12.0f, (float_q)14.0f, (float_q)16.0f,
                            (float_q)18.0f, (float_q)20.0f, (float_q)22.0f, (float_q)24.0f);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_13 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_9;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)11.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)12.0f;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix3x4 matrixUT = MATRIX;
    matrixUT /= SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that a matrix element is divided and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_MatrixIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    QMatrix3x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][3];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][3];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][3];

	// Execution
    QMatrix3x4 matrixUT = MATRIX;
    matrixUT /= matrixUT.ij[0][0];
    matrixUT /= matrixUT.ij[0][1];
    matrixUT /= matrixUT.ij[0][2];
    matrixUT /= matrixUT.ij[0][3];
    matrixUT /= matrixUT.ij[1][0];
    matrixUT /= matrixUT.ij[1][1];
    matrixUT /= matrixUT.ij[1][2];
    matrixUT /= matrixUT.ij[1][3];
    matrixUT /= matrixUT.ij[2][0];
    matrixUT /= matrixUT.ij[2][1];
    matrixUT /= matrixUT.ij[2][2];
    matrixUT /= matrixUT.ij[2][3];

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_AssertionFailsWhenScalarEqualsZero_Test )
{
    // Preparation
    const float_q ZERO_SCALAR = SQFloat::_0;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QMatrix3x4 vMatrixUT;
        vMatrixUT /= ZERO_SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that two common matrices are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_CommonMatricesAreCorrectlyAdded_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QMatrix3x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix3x4 OPERAND2((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)18.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)20.0f;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)24.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)26.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)28.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)30.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)32.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)34.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)36.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)38.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)40.0f;

    // Execution
    QMatrix3x4 matrixUT = OPERAND1;
    matrixUT += OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that two common matrices are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_CommonMatricesAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QMatrix3x4 OPERAND1((float_q)18.0f, (float_q)20.0f, (float_q)22.0f, (float_q)24.0f,
                              (float_q)26.0f, (float_q)28.0f, (float_q)30.0f, (float_q)32.0f,
                              (float_q)34.0f, (float_q)36.0f, (float_q)38.0f, (float_q)40.0f);

    const QBaseMatrix3x4 OPERAND2((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f);

    const QMatrix3x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    // Execution
    QMatrix3x4 matrixUT = OPERAND1;
    matrixUT -= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks if all the elements of the matrix are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_MatrixIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const float_q  SCALAR = SQFloat::_2;

    const QMatrix3x4 EXPECTED_VALUE(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                                    SQFloat::_10,   (float_q)12.0f, (float_q)14.0f, (float_q)16.0f,
                                    (float_q)18.0f, (float_q)20.0f, (float_q)22.0f, (float_q)24.0f);

	// Execution
    QMatrix3x4 matrixUT = MATRIX;
    matrixUT *= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks that a matrix element is multiplied and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_MatrixIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX((float_q)0.9f,  SQFloat::_1,    SQFloat::_2,     (float_q)0.3f,
                            SQFloat::_7,    SQFloat::_0_5,  SQFloat::_4,     (float_q)0.02f,
                            SQFloat::_3,    (float_q)0.07f, (float_q)0.033f, (float_q)0.001f);

    QMatrix3x4 EXPECTED_VALUE((float_q)0.9f,  SQFloat::_1,    SQFloat::_2,     (float_q)0.3f,
                              SQFloat::_7,    SQFloat::_0_5,  SQFloat::_4,     (float_q)0.02f,
                              SQFloat::_3,    (float_q)0.07f, (float_q)0.033f, (float_q)0.001f);

    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][3];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][3];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][3];

	// Execution
    QMatrix3x4 matrixUT = MATRIX;
    matrixUT *= matrixUT.ij[0][0];
    matrixUT *= matrixUT.ij[0][1];
    matrixUT *= matrixUT.ij[0][2];
    matrixUT *= matrixUT.ij[0][3];
    matrixUT *= matrixUT.ij[1][0];
    matrixUT *= matrixUT.ij[1][1];
    matrixUT *= matrixUT.ij[1][2];
    matrixUT *= matrixUT.ij[1][3];
    matrixUT *= matrixUT.ij[2][0];
    matrixUT *= matrixUT.ij[2][1];
    matrixUT *= matrixUT.ij[2][2];
    matrixUT *= matrixUT.ij[2][3];

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix3x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                  (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                  (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f,
                                  (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)250.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)260.0f;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)270.0f;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)280.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)618.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)644.0f;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)670.0f;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)696.0f;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)986.0f;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)1028.0f;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)1070.0f;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)1112.0f;

    // Execution
    QMatrix3x4 matrixUT(OPERAND1);
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
}

/// <summary>
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
QTEST_CASE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QBaseMatrix3x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                        SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                        SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    // Execution
    QMatrix3x4 matrixUT;
    matrixUT = EXPECTED_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
}

/// <summary>
/// Checks that every element of the matrix equals zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllElementsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x4;

    const QBaseMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // Execution
    QMatrix3x4 matrixUT(MATRIX);
    matrixUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that every element that occupies the position ij, now is at the position ji.
/// </summary>
QTEST_CASE ( Transpose_TheRowAndColumOfElementsAreSwapped_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x3;

    const QMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const QBaseMatrix4x3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_5, SQFloat::_9,
                                        SQFloat::_2, SQFloat::_6, SQFloat::_10,
                                        SQFloat::_3, SQFloat::_7, (float_q)11.0f,
                                        SQFloat::_4, SQFloat::_8, (float_q)12.0f);

    // Execution
    QBaseMatrix4x3 matrixUT = MATRIX.Transpose();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // Preparation
    const QMatrix3x4 ZERO_MATRIX = QMatrix3x4::GetZeroMatrix();
    const bool EXPECTED_VALUE = true;

    // Execution
    QMatrix3x4 matrixUT = ZERO_MATRIX;
    bool bResult = matrixUT.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when not all the matrix elements equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenNotAllElementsEqualZero_Test )
{
    // Preparation
    const QMatrix3x4 ZERO_MATRIX = QMatrix3x4::GetZeroMatrix();
    const bool EXPECTED_VALUE = false;

    // Execution
    QMatrix3x4 matrixUT = ZERO_MATRIX;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][0] = SQFloat::_0;
    matrixUT.ij[0][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][1] = SQFloat::_0;
    matrixUT.ij[0][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][2] = SQFloat::_0;
    matrixUT.ij[0][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][3] = SQFloat::_0;
    matrixUT.ij[1][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][0] = SQFloat::_0;
    matrixUT.ij[1][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][1] = SQFloat::_0;
    matrixUT.ij[1][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][2] = SQFloat::_0;
    matrixUT.ij[1][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][3] = SQFloat::_0;
    matrixUT.ij[2][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][0] = SQFloat::_0;
    matrixUT.ij[2][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][1] = SQFloat::_0;
    matrixUT.ij[2][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][2] = SQFloat::_0;
    matrixUT.ij[2][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that every element of the matrix equals zero but diagonal's, which equal one.
/// </summary>
QTEST_CASE ( ResetToIdentity_AllElementsEqualZeroButDiagonalThatEqualsOne_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DIAGONAL = SQFloat::_1;

    // Execution
    QMatrix3x4 matrixUT(MATRIX);
    matrixUT.ResetToIdentity();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    const QMatrix3x4 MATRIX(SQFloat::_0,    SQFloat::_1,    SQFloat::_2,    (float_q)0.654321f,
                            SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    (float_q)-2.2f,
                            SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)123456.0f);
    const string_q EXPECTED_STRING_FORM = QE_L("M3x4((0,1,2,0.654321015)(4,5,6,-2.20000005)(8,9,10,123456))");

	// Execution
    QMatrix3x4 matrixUT = MATRIX;
    string_q strStringForm = matrixUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: QMatrix3x4
QTEST_SUITE_END()
