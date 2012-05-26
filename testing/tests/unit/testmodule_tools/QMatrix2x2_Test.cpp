// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QMatrix2x2.h"

using Kinesis::QuimeraEngine::Tools::Math::QMatrix2x2;

QTEST_SUITE_BEGIN( QMatrix2x2_TestSuite )

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_EveryElementIsMultipliedByTheScalar_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_8;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix2x2 matrixUT = SCALAR_VALUE * MATRIX;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // Execution
    QMatrix2x2 matrixUT;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
QTEST_CASE ( Constructor2_EveryElementCopiedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;
    const QBaseMatrix2x2 EXPECTED_VALUE(SQFloat::_0, SQFloat::_1,
                                        SQFloat::_2, SQFloat::_3);

    // Execution
    QMatrix2x2 matrixUT(EXPECTED_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks if the value provided is set to all the matrix components.
/// </summary>
QTEST_CASE ( Constructor3_ValueIsSetForAllComponents_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

    // Execution
    QMatrix2x2 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_4;

	// Execution
    QMatrix2x2 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01,
                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor5_MatrixComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
   // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_4;

    float_q* VALID_ARRAY_OF_4_FLOATS = new float_q[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_11;

	// Execution
    QMatrix2x2 matrixUT(VALID_ARRAY_OF_4_FLOATS);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);

    // Cleaning
    delete [] VALID_ARRAY_OF_4_FLOATS;
    VALID_ARRAY_OF_4_FLOATS = null_q;
}

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenPointerIsNull_Test )
{
    // Preparation
    const float_q* NULL_ARRAY = null_q;

	// Execution
    bool bAssertionFailed = false;

    try
    {
        QMatrix2x2 vMatrixUT(NULL_ARRAY);
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
QTEST_CASE ( Constructor6_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_4;

	vf32_q PACK;
	SQVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, PACK);

	// Execution
	QMatrix2x2 matrixUT(PACK);

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero.
/// </summary>
QTEST_CASE ( GetZeroMatrix_AllElementsEqualZero_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

	// Execution
    QMatrix2x2 matrixUT = QMatrix2x2::GetZeroMatrix();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
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
    QMatrix2x2 matrixUT = QMatrix2x2::GetIdentity();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct1_EveryElementIsMultipliedByTheScalar_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_8;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix2x2 matrixUT = MATRIX * SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                              SQFloat::_3, SQFloat::_4);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)19.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)43.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)50.0f;

    // Execution
    QMatrix2x2 matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
QTEST_CASE ( OperatorProduct2_ProductIsNotCommutative_Test )
{
    // Preparation
    const QMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                              SQFloat::_3, SQFloat::_4);

    const QMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                              SQFloat::_7, SQFloat::_8);

    // Execution
    QMatrix2x2 matrix1UT = OPERAND1 * OPERAND2;
    QMatrix2x2 matrix2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision_EveryElementIsDividedByTheScalar_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_2, SQFloat::_4,
                            SQFloat::_6, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_4;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix2x2 matrixUT = MATRIX / SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
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
        QMatrix2x2 vMatrixUT;
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
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                              SQFloat::_3, SQFloat::_4);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0f;

    // Execution
    QMatrix2x2 matrixUT = OPERAND1 + OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that two common matrices are correctly subtraction.
/// </summary>
QTEST_CASE ( OperatorSubtraction_CommonMatricesAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QMatrix2x2 OPERAND1(SQFloat::_6,  SQFloat::_8,
                              SQFloat::_10, (float_q)12.0f);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const QMatrix2x2 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2,
                                    SQFloat::_3, SQFloat::_4);

    // Execution
    QMatrix2x2 matrixUT = OPERAND1 - OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks if all the elements of the matrix are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_MatrixIsCorrectlyMultipliedByScalar_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const float_q  SCALAR = SQFloat::_2;

    const QMatrix2x2 EXPECTED_VALUE(SQFloat::_2, SQFloat::_4,
                                    SQFloat::_6, SQFloat::_8);

	// Execution
    QMatrix2x2 matrixUT = MATRIX;
    matrixUT *= SCALAR;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks that a matrix element is multiplied and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_MatrixIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX((float_q)0.9f, SQFloat::_1, SQFloat::_2, (float_q)0.3f);

    QMatrix2x2 EXPECTED_VALUE((float_q)0.9f, SQFloat::_1, SQFloat::_2, (float_q)0.3f);
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][1];

	// Execution
    QMatrix2x2 matrixUT = MATRIX;
    matrixUT *= matrixUT.ij[0][0];
    matrixUT *= matrixUT.ij[0][1];
    matrixUT *= matrixUT.ij[1][0];
    matrixUT *= matrixUT.ij[1][1];

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                                  SQFloat::_3, SQFloat::_4);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)19.0f;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)22.0f;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)43.0f;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)50.0f;

    // Execution
    QMatrix2x2 matrixUT(OPERAND1);
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_ProductIsNotCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                                  SQFloat::_3, SQFloat::_4);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    // Execution
    QMatrix2x2 matrix1UT(OPERAND1);
    matrix1UT *= OPERAND2;
    QMatrix2x2 matrix2UT(OPERAND2);
    matrix2UT *= OPERAND1;

    // Verification
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // Preparation
    const QMatrix2x2 OPERAND(SQFloat::_1, SQFloat::_2,
                             SQFloat::_3, SQFloat::_4);

    const QMatrix2x2 EXPECTED_VALUE = OPERAND * OPERAND;

	// Execution
    QMatrix2x2 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // Verification
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_EveryElementIsDividedByTheScalar_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_2, SQFloat::_4,
                            SQFloat::_6, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_4;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // Execution
    QMatrix2x2 matrixUT = MATRIX;
    matrixUT /= SCALAR_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that a matrix element is divided and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_MatrixIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix2x2 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][1];

	// Execution
    QMatrix2x2 matrixUT = MATRIX;
    matrixUT /= matrixUT.ij[0][0];
    matrixUT /= matrixUT.ij[0][1];
    matrixUT /= matrixUT.ij[1][0];
    matrixUT /= matrixUT.ij[1][1];

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
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
        QMatrix2x2 vMatrixUT;
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
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QMatrix2x2 OPERAND1(SQFloat::_1, SQFloat::_2,
                              SQFloat::_3, SQFloat::_4);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0f;

    // Execution
    QMatrix2x2 matrixUT = OPERAND1;
    matrixUT += OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
}

/// <summary>
/// Checks that two common matrices are correctly subtraction.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_CommonMatricesAreCorrectlySubtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QMatrix2x2 OPERAND1(SQFloat::_6,  SQFloat::_8,
                              SQFloat::_10, (float_q)12.0f);

    const QBaseMatrix2x2 OPERAND2(SQFloat::_5, SQFloat::_6,
                                  SQFloat::_7, SQFloat::_8);

    const QMatrix2x2 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2,
                                    SQFloat::_3, SQFloat::_4);

    // Execution
    QMatrix2x2 matrixUT = OPERAND1;
    matrixUT -= OPERAND2;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
QTEST_CASE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2,
                                        SQFloat::_3, SQFloat::_4);

    // Execution
    QMatrix2x2 matrixUT;
    matrixUT = EXPECTED_VALUE;

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks that every element of the matrix equals zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllElementsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix2x2;

    const QBaseMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                                SQFloat::_3, SQFloat::_4);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // Execution
    QMatrix2x2 matrixUT(MATRIX);
    matrixUT.ResetToZero();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that every element of the matrix equals zero but diagonal's, which equal one.
/// </summary>
QTEST_CASE ( ResetToIdentity_AllElementsEqualZeroButDiagonalThatEqualsOne_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DIAGONAL = SQFloat::_1;

    // Execution
    QMatrix2x2 matrixUT(MATRIX);
    matrixUT.ResetToIdentity();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks that every element that occupies the position ij, now is at the position ji.
/// </summary>
QTEST_CASE ( Transpose_TheRowAndColumOfElementsAreSwapped_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const QMatrix2x2 EXPECTED_VALUE(SQFloat::_1, SQFloat::_3,
                                    SQFloat::_2, SQFloat::_4);

    // Execution
    QMatrix2x2 matrixUT = MATRIX.Transpose();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // Preparation
    const QMatrix2x2 ZERO_MATRIX = QMatrix2x2::GetZeroMatrix();
    const bool EXPECTED_VALUE = true;

    // Execution
    QMatrix2x2 matrixUT = ZERO_MATRIX;
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
    const QMatrix2x2 ZERO_MATRIX = QMatrix2x2::GetZeroMatrix();
    const bool EXPECTED_VALUE = false;

    // Execution
    QMatrix2x2 matrixUT = ZERO_MATRIX;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][0] = SQFloat::_0;
    matrixUT.ij[0][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][1] = SQFloat::_0;
    matrixUT.ij[1][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][0] = SQFloat::_0;
    matrixUT.ij[1][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();

    // Verification
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero but the diagonal's, which equal one.
/// </summary>
QTEST_CASE ( IsIdentity_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // Preparation
    const QMatrix2x2 IDENTITY = QMatrix2x2::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // Execution
    QMatrix2x2 matrixUT = IDENTITY;
    bool bResult = matrixUT.IsIdentity();

    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the matrix is not an identity matrix.
/// </summary>
QTEST_CASE ( IsIdentity_ReturnsFalseWhenItsNotIdentity_Test )
{
    // Preparation
    const QMatrix2x2 IDENTITY = QMatrix2x2::GetIdentity();
    const bool EXPECTED_VALUE = false;

    // Execution
    QMatrix2x2 matrixUT = IDENTITY;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][0] = SQFloat::_1;
    matrixUT.ij[0][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][1] = SQFloat::_0;
    matrixUT.ij[1][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][0] = SQFloat::_0;
    matrixUT.ij[1][1] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();

    // Verification
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of a common matrix is correctly obtained.
/// </summary>
QTEST_CASE ( GetDeterminant_ItsCorrectlyCalculatedForCommonMatrix_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const float_q EXPECTED_VALUE = -SQFloat::_2;

    // Execution
    float_q fResultUT = MATRIX.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the identity equals one.
/// </summary>
QTEST_CASE ( GetDeterminant_DeterminantOfIdentityEqualsOne_Test )
{
    // Preparation
    const QMatrix2x2 IDENTITY = QMatrix2x2::GetIdentity();
    const float_q EXPECTED_VALUE = SQFloat::_1;

    // Execution
    float_q fResultUT = IDENTITY.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the zero matrix equals zero.
/// </summary>
QTEST_CASE ( GetDeterminant_DeterminantOfZeroMatrixEqualsZero_Test )
{
    // Preparation
    const QMatrix2x2 ZERO_MATRIX = QMatrix2x2::GetZeroMatrix();
    const float_q EXPECTED_VALUE = SQFloat::_0;

    // Execution
    float_q fResultUT = ZERO_MATRIX.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common matrix is correctly inverted.
/// </summary>
QTEST_CASE ( Reverse_CommonMatrixIsCorrectlyInverted_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_1, SQFloat::_2,
                            SQFloat::_3, SQFloat::_4);

    const QMatrix2x2 EXPECTED_VALUE(-SQFloat::_2,  SQFloat::_1,
                                    (float_q)1.5f, -SQFloat::_0_5);

    // Execution
    QMatrix2x2 matrixUT = MATRIX.Invert();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
}

/// <summary>
/// Checks that it returns True when the determinant of the matrix doesn't equal zero.
/// </summary>
QTEST_CASE ( HasReverse_ReturnsTrueWhenDeterminantIsNotZero_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX = QMatrix2x2::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // Execution
    bool bResultUT = MATRIX.HasInverse();

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the determinant of the matrix equals zero.
/// </summary>
QTEST_CASE ( HasReverse_ReturnsFalseWhenDeterminantIsZero_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX = QMatrix2x2::GetZeroMatrix();
    const bool EXPECTED_VALUE = false;

    // Execution
    bool bResultUT = MATRIX.HasInverse();

    // Verification
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // Preparation
    const QMatrix2x2 MATRIX(SQFloat::_0,          SQFloat::_1,
                            (float_q)1234567.89f, (float_q)-0.654321f);
    const string_q EXPECTED_STRING_FORM = QE_L("M2x2((0,1)(1234567.88,-0.654321015))");

	// Execution
    QMatrix2x2 matrixUT = MATRIX;
    string_q strStringForm = matrixUT.ToString();

    // Verification
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: QMatrix2x2
QTEST_SUITE_END()
