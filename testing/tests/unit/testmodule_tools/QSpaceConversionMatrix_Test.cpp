// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "QSpaceConversionMatrix.h"
#include "QSpaceConversionMatrixWhiteBox.h"
#include "QQuaternion.h"
#include "QTranslationMatrix.h"
#include "QRotationMatrix3x3.h"
#include "QScalingMatrix3x3.h"
#include "QTransformationMatrix.h"

using Kinesis::QuimeraEngine::Tools::Math::QSpaceConversionMatrix;

QTEST_SUITE_BEGIN( QSpaceConversionMatrix_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]);
}

/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

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
    const float_q EXPECTED_VALUE_FOR_30 = SQFloat::_10+SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_31 = SQFloat::_10+SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_32 = SQFloat::_10+SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_33 = SQFloat::_10+SQFloat::_6;

    const QBaseMatrix4x4 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                                        EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    const QSpaceConversionMatrix MATRIX_TO_COPY(EXPECTED_VALUE);

    // Execution
    QSpaceConversionMatrix matrixUT = MATRIX_TO_COPY;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
QTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    const QBaseMatrix4x4 EXPECTED_VALUE(SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                        SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7,
                                        SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0f,
                                        (float_q)12.0f, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f);

    // Execution
    QSpaceConversionMatrix matrixUT(EXPECTED_VALUE);

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]);
}

/// <summary>
/// Checks that every matrix element is assigned to the right destination matrix element.
/// </summary>
QTEST_CASE ( OperatorAssignation_EveryElementAssignedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4, 
                                        SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8, 
                                        SQFloat::_9, SQFloat::_10, (float)11.0f, (float)12.0f,
                                        (float)13.0f, (float)14.0f, (float)15.0f, (float)16.0f);

    // Execution
    QSpaceConversionMatrix matrixUT;
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QSpaceConversionMatrix OPERAND1(QBaseMatrix4x4(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                                         SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                                         SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f,
                                                         (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f));

    const QSpaceConversionMatrix OPERAND2(QBaseMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                                         (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                                         (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f,
                                                         (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f));

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
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)1354.0f;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)1412.0f;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)1470.0f;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)1528.0f;

    // Execution
    QSpaceConversionMatrix matrixUT = OPERAND1 * OPERAND2;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
QTEST_CASE ( OperatorProduct_ProductIsNotCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QSpaceConversionMatrix OPERAND1(QBaseMatrix4x4(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                                         SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                                         SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f,
                                                         (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f));

    const QSpaceConversionMatrix OPERAND2(QBaseMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                                         (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                                         (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f,
                                                         (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f));

    // Execution
    QSpaceConversionMatrix matrix1UT = OPERAND1 * OPERAND2;
    QSpaceConversionMatrix matrix2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                  SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                  SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f,
                                  (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f);

    const QSpaceConversionMatrix OPERAND2(QBaseMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                                         (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                                         (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f,
                                                         (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f));

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
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)1354.0f;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)1412.0f;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)1470.0f;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)1528.0f;

    // Execution
    QSpaceConversionMatrix matrixUT(OPERAND1);
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_ProductIsNotCommutative_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QSpaceConversionMatrix OPERAND1(QBaseMatrix4x4(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                                         SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                                         SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f,
                                                         (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f));

    const QSpaceConversionMatrix OPERAND2(QBaseMatrix4x4((float_q)17.0f, (float_q)18.0f, (float_q)19.0f, (float_q)20.0f,
                                                         (float_q)21.0f, (float_q)22.0f, (float_q)23.0f, (float_q)24.0f,
                                                         (float_q)25.0f, (float_q)26.0f, (float_q)27.0f, (float_q)28.0f,
                                                         (float_q)29.0f, (float_q)30.0f, (float_q)31.0f, (float_q)32.0f));

    // Execution
    QSpaceConversionMatrix matrix1UT(OPERAND1);
    matrix1UT *= OPERAND2;
    QSpaceConversionMatrix matrix2UT(OPERAND2);
    matrix2UT *= OPERAND1;

    // Verification
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QSpaceConversionMatrix OPERAND(QBaseMatrix4x4(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                             SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                             SQFloat::_9,    SQFloat::_10,   (float_q)11.0f, (float_q)12.0f,
                             (float_q)13.0f, (float_q)14.0f, (float_q)15.0f, (float_q)16.0f));

    const QSpaceConversionMatrix EXPECTED_VALUE = OPERAND * OPERAND;

	// Execution
    QSpaceConversionMatrix matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // Verification
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE ( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE ( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_ResultIsDifferentDependingOnQuaternionNormalization_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QSpaceConversionMatrix matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    QSpaceConversionMatrix matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_FollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector3 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    QSpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0), SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0), SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE), SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix1_CompositionOrderIsScaleRotationTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector3 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QSpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    QSpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(QVector3::GetZeroVector(), ROTATION, QVector3::GetVectorOfOnes());
    QSpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QBaseVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE ( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion ROTATION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE ( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QBaseVector3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseQuaternion ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QBaseVector3 SCALE(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_ResultIsDifferentDependingOnQuaternionNormalization_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QQuaternion NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize();
    const QQuaternion NOT_NORMALIZED_QUATERNION = QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QBaseVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Execution
    QSpaceConversionMatrix matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    QSpaceConversionMatrix matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // Verification
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_FollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QVector4 TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    QSpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0), SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0), SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, QQuaternion(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE), SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix2_CompositionOrderIsScaleRotationTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const QVector4 TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QQuaternion ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7);
    const QVector3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QSpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    QSpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(QVector3::GetZeroVector(), ROTATION, QVector3::GetVectorOfOnes());
    QSpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QBaseMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QBaseMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QMatrix4x4 TRANSLATION = QMatrix4x4::GetZeroMatrix();
    const QMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_FollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    QSpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix3_CompositionOrderIsScaleRotationTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QMatrix4x4 NEUTRAL_TRANSLATION = QMatrix4x4::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    QSpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QMatrix4x4 TRANSLATION = QMatrix4x4::GetZeroMatrix();
    const QMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_FollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    QSpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix4_CompositionOrderIsScaleRotationTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QMatrix4x4 NEUTRAL_TRANSLATION = QMatrix4x4::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    QSpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3), QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> ROTATION(QVector3::GetZeroVector(), QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> SCALE(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), QVector3(SQFloat::_8, SQFloat::_9, SQFloat::_10));

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> ROTATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> SCALE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION = QTransformationMatrix<QMatrix4x4>(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3), QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> ROTATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> SCALE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> ROTATION(QVector3::GetZeroVector(), QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> SCALE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    QMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> ROTATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> SCALE = QTransformationMatrix<QMatrix4x4>(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), QVector3(SQFloat::_2, SQFloat::_3, SQFloat::_4));

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION(QMatrix4x4::GetZeroMatrix());
    const QTransformationMatrix<QMatrix4x4> ROTATION(QMatrix4x4::GetZeroMatrix());
    const QTransformationMatrix<QMatrix4x4> SCALE(QMatrix4x4::GetZeroMatrix());

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_FollowsLeftHandedRules_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTransformationMatrix<QMatrix4x4> TRANSLATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> SCALE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    const QTransformationMatrix<QMatrix4x4> ROTATION_QUATERNION_AROUND_X(QVector3::GetZeroVector(), QQuaternion(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0).Normalize(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> ROTATION_QUATERNION_AROUND_Y(QVector3::GetZeroVector(), QQuaternion(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0).Normalize(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> ROTATION_QUATERNION_AROUND_Z(QVector3::GetZeroVector(), QQuaternion(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE).Normalize(), QVector3::GetVectorOfOnes());

    QSpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    QSpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrix5_CompositionOrderIsScaleRotationTranslation_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QTransformationMatrix<QMatrix4x4> TRANSLATION(QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3), QQuaternion::GetIdentity(), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> ROTATION(QVector3::GetZeroVector(), QQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7), QVector3::GetVectorOfOnes());
    const QTransformationMatrix<QMatrix4x4> SCALE(QVector3::GetZeroVector(), QQuaternion::GetIdentity(), QVector3(SQFloat::_8, SQFloat::_9, SQFloat::_10));

    const QTransformationMatrix<QMatrix4x4> NEUTRAL_TRANSLATION = QTransformationMatrix<QMatrix4x4>::GetZeroMatrix();
    const QTransformationMatrix<QMatrix4x4> NEUTRAL_ROTATION = QTransformationMatrix<QMatrix4x4>::GetIdentity();
    const QTransformationMatrix<QMatrix4x4> NEUTRAL_SCALE = QTransformationMatrix<QMatrix4x4>::GetIdentity();

    QSpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the view matrix is correctly built when using common vectors as up, point of view and target.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix1_ViewMatrixIsCorrectlyBuiltFromCommonInputVectors_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 UP_DIRECTION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 POINT_OF_VIEW = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 TARGET = QVector3(SQFloat::_7, SQFloat::_8, SQFloat::_9);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    // D3DXVECTOR3 vEye(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    // D3DXVECTOR3 vTarget(SQFloat::_7, SQFloat::_8, SQFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtLH(&viewMatrix, &vEye, &vTarget, &vUp);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)-0.40824828f, (float_q)-0.70710671f, (float_q)0.57735026f, SQFloat::_0,
                                                               (float_q)0.81649655f,  SQFloat::_0,           (float_q)0.57735026f, SQFloat::_0,
                                                               (float_q)-0.40824828f, (float_q)0.70710671f,  (float_q)0.57735026f, SQFloat::_0,
                                                               SQFloat::_0,           (float_q)-1.4142137f,  (float_q)-8.6602535f, SQFloat::_1));

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the assertion fails when "up" vector is null.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix1_AssertionFailsWhenUpVectorIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 UP_DIRECTION = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QVector3 POINT_OF_VIEW = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 TARGET = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFailed = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the point of view equals target vector.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix1_AssertionFailsWhenPointOfViewEqualsTarget_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 UP_DIRECTION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 POINT_OF_VIEW = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 TARGET = POINT_OF_VIEW;

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFailed = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the view matrix is correctly built when using common vectors as up, point of view and target.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix2_ViewMatrixIsCorrectlyBuiltFromCommonInputVectors_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QVector4 UP_DIRECTION = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_10);
    const QVector4 POINT_OF_VIEW = QVector4(SQFloat::_4, SQFloat::_5, SQFloat::_6, (float_q)11.0f);
    const QVector4 TARGET = QVector4(SQFloat::_7, SQFloat::_8, SQFloat::_9, (float_q)12.0f);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    // D3DXVECTOR3 vEye(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    // D3DXVECTOR3 vTarget(SQFloat::_7, SQFloat::_8, SQFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtLH(&viewMatrix, &vEye, &vTarget, &vUp);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)-0.40824828f, (float_q)-0.70710671f, (float_q)0.57735026f, SQFloat::_0,
                                                               (float_q)0.81649655f,  SQFloat::_0,           (float_q)0.57735026f, SQFloat::_0,
                                                               (float_q)-0.40824828f, (float_q)0.70710671f,  (float_q)0.57735026f, SQFloat::_0,
                                                               SQFloat::_0,           (float_q)-1.4142137f,  (float_q)-8.6602535f, SQFloat::_1));

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the assertion fails when "up" vector is null.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix2_AssertionFailsWhenUpVectorIsNull_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QVector4 UP_DIRECTION = QVector4::GetZeroVector();
    const QVector4 POINT_OF_VIEW = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QVector4 TARGET = QVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFailed = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the point of view equals target vector.
/// </summary>
QTEST_CASE( SetViewSpaceMatrix2_AssertionFailsWhenPointOfViewEqualsTarget_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QVector4;

    const QVector4 UP_DIRECTION = QVector4(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    const QVector4 POINT_OF_VIEW = QVector4(SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8);
    const QVector4 TARGET = POINT_OF_VIEW;

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFailed = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFailed = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the projection matrix is correctly built when using common inputs.
/// </summary>
QTEST_CASE( SetProjectionSpaceMatrix_ProjectionMatrixIsCorrectlyBuiltFromCommonInputs_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = SQFloat::_2;
    const float_q VERTICAL_FOV = SQFloat::_3;
    const float_q ASPECT_RATIO = SQFloat::_4;

    // Reference values obtained by using DirectX SDK:
    // float_q fNearClipPlane = SQFloat::_1;
    // float_q fFarClipPlane = SQFloat::_2;
    // float_q fVerticalFOV = SQFloat::_3;
    // float_q fAspectRatio = SQFloat::_4;
    // D3DXMATRIX projectionMatrix;
    // D3DXMatrixPerspectiveFovLH(&projectionMatrix, fVerticalFOV, fAspectRatio, fNearClipPlane, fFarClipPlane);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)0.017728711f, SQFloat::_0,           SQFloat::_0,  SQFloat::_0,
                                                               (float_q)SQFloat::_0,  (float_q)0.070914842f, SQFloat::_0,  SQFloat::_0,
                                                               SQFloat::_0,           SQFloat::_0,           SQFloat::_2,  SQFloat::_1,
                                                               SQFloat::_0,           SQFloat::_0,           -SQFloat::_2, SQFloat::_0));

    // Execution
    QSpaceConversionMatrix matrixUT;
    matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the assertion fails when the near clip plane equals the far clip plane.
/// </summary>
QTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenNearAndFarClipPlanesAreTheSame_Test )
{
    // Preparation
    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = NEAR_CLIP_PLANE;
    const float_q VERTICAL_FOV = SQFloat::_3;
    const float_q ASPECT_RATIO = SQFloat::_4;

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFail = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFail = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the vertical FOV equals zero.
/// </summary>
QTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenVerticalFovEqualsZero_Test )
{
    // Preparation
    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = SQFloat::_1;
    const float_q VERTICAL_FOV = SQFloat::_0;
    const float_q ASPECT_RATIO = SQFloat::_4;

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFail = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFail = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the aspect ratio equals zero.
/// </summary>
QTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenAspectRatioEqualsZero_Test )
{
    // Preparation
    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = SQFloat::_1;
    const float_q VERTICAL_FOV = SQFloat::_3;
    const float_q ASPECT_RATIO = SQFloat::_0;

    const bool EXPECTED_VALUE = true;

    // Execution
    bool bAssertionFail = false;
    QSpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(...) // TODO Thund: A concrete exception type should be caught when it's implemented
    {
        bAssertionFail = true;
    }

    // Verification
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the hand convention of the transformations represented by the matrix are correctly switched.
/// </summary>
QTEST_CASE ( SwitchHandConventionWorldSpaceMatrix_MatrixHandConventionIsCorrectlySwitched_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QTranslationMatrix<QMatrix4x4> INVERTED_TRANSLATION(SQFloat::_1, SQFloat::_2, -SQFloat::_3);
    const QRotationMatrix3x3 INVERTED_ROTATION = QRotationMatrix3x3(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert();

    const QSpaceConversionMatrix TRANSFORMATION(SCALE * ROTATION * TRANSLATION);
    const QSpaceConversionMatrix EXPECTED_RESULT(SCALE * INVERTED_ROTATION * INVERTED_TRANSLATION);

    // Execution
    QSpaceConversionMatrix matrixUT = TRANSFORMATION.SwitchHandConventionWorldSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_RESULT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_RESULT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_RESULT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_RESULT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_RESULT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_RESULT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_RESULT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_RESULT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_RESULT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_RESULT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_RESULT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_RESULT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_RESULT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_RESULT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_RESULT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_RESULT.ij[3][3]) );
}

/// <summary>
/// Checks that a twice switched matrix equals original value.
/// </summary>
QTEST_CASE ( SwitchHandConventionWorldSpaceMatrix_SwitchingIsReversible_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_X = SQAngle::_45;
        const float_q ROTATION_Y = SQAngle::_60;
        const float_q ROTATION_Z = SQAngle::_90;
    #else
        const float_q ROTATION_X = SQAngle::_QuarterPi;
        const float_q ROTATION_Y = SQAngle::_ThirdPi;
        const float_q ROTATION_Z = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const QScalingMatrix3x3 SCALE(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QSpaceConversionMatrix TRANSFORMATION(SCALE * ROTATION * TRANSLATION);

    // Execution
    QSpaceConversionMatrix matrixUT = TRANSFORMATION.SwitchHandConventionWorldSpaceMatrix().SwitchHandConventionWorldSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], TRANSFORMATION.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], TRANSFORMATION.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], TRANSFORMATION.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], TRANSFORMATION.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], TRANSFORMATION.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], TRANSFORMATION.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], TRANSFORMATION.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], TRANSFORMATION.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], TRANSFORMATION.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], TRANSFORMATION.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], TRANSFORMATION.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], TRANSFORMATION.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], TRANSFORMATION.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], TRANSFORMATION.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], TRANSFORMATION.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], TRANSFORMATION.ij[3][3]) );
}

/// <summary>
/// Checks that the view matrix is correctly converted from left-handed to right-handed rules and vice versa.
/// </summary>
QTEST_CASE( SwitchHandConventionViewSpaceMatrix_HandRulesAreCorrectlySwitched_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 UP_DIRECTION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 POINT_OF_VIEW = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 TARGET = QVector3(SQFloat::_7, SQFloat::_8, SQFloat::_9);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    // D3DXVECTOR3 vEye(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    // D3DXVECTOR3 vTarget(SQFloat::_7, SQFloat::_8, SQFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtRH(&viewMatrix, &vEye, &vTarget, &vUp);

    QSpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)0.40824828f, (float_q)-0.70710671f, (float_q)-0.57735026f, SQFloat::_0,
                                                               (float_q)-0.81649655f,  SQFloat::_0,           (float_q)-0.57735026f, SQFloat::_0,
                                                               (float_q)0.40824828f, (float_q)0.70710671f,  (float_q)-0.57735026f, SQFloat::_0,
                                                               SQFloat::_0,           (float_q)-1.4142137f,  (float_q)8.6602554f, SQFloat::_1));

    // Execution
    QSpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionViewSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a twice switched matrix equals original value.
/// </summary>
QTEST_CASE( SwitchHandConventionViewSpaceMatrix_SwitchingIsReversible_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 UP_DIRECTION = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QVector3 POINT_OF_VIEW = QVector3(SQFloat::_4, SQFloat::_5, SQFloat::_6);
    const QVector3 TARGET = QVector3(SQFloat::_7, SQFloat::_8, SQFloat::_9);

    QSpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)-0.40824845f, (float_q)-0.70710713f, (float_q)0.57735032f, SQFloat::_0,
                                                               (float_q)0.81649691f,  SQFloat::_0,           (float_q)0.57735032f, SQFloat::_0,
                                                               (float_q)-0.40824845f, (float_q)0.70710713f,  (float_q)0.57735032f, SQFloat::_0,
                                                               SQFloat::_0,           (float_q)-1.4142156f,  (float_q)-8.6602573f, SQFloat::_1));

    // Execution
    QSpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionViewSpaceMatrix().SwitchHandConventionViewSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the projection matrix is correctly converted from left-handed to right-handed rules and vice versa.
/// </summary>
QTEST_CASE( SwitchHandConventionProjectionSpaceMatrix_HandRulesAreCorrectlySwitched_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = SQFloat::_2;
    const float_q VERTICAL_FOV = SQFloat::_3;
    const float_q ASPECT_RATIO = SQFloat::_4;

    // Reference values obtained by using DirectX SDK:
    // float_q fNearClipPlane = SQFloat::_1;
    // float_q fFarClipPlane = SQFloat::_2;
    // float_q fVerticalFOV = SQFloat::_3;
    // float_q fAspectRatio = SQFloat::_4;
    // D3DXMATRIX projectionMatrix;
    // D3DXMatrixPerspectiveFovRH(&projectionMatrix, fVerticalFOV, fAspectRatio, fNearClipPlane, fFarClipPlane);

    QSpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);

    const QSpaceConversionMatrix EXPECTED_VALUE(QBaseMatrix4x4((float_q)0.017728711f, SQFloat::_0,           SQFloat::_0,  SQFloat::_0,
                                                               (float_q)SQFloat::_0,  (float_q)0.070914842f, SQFloat::_0,  SQFloat::_0,
                                                               SQFloat::_0,           SQFloat::_0,           -SQFloat::_2,  -SQFloat::_1,
                                                               SQFloat::_0,           SQFloat::_0,           -SQFloat::_2, SQFloat::_0));

    // Execution
    QSpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionProjectionSpaceMatrix();
    QSpaceConversionMatrix matrixSwitchedAgainUT = matrixUT.SwitchHandConventionProjectionSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a twice switched matrix equals original value.
/// </summary>
QTEST_CASE( SwitchHandConventionProjectionSpaceMatrix_SwitchingIsReversible_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const float_q NEAR_CLIP_PLANE = SQFloat::_1;
    const float_q FAR_CLIP_PLANE = SQFloat::_2;
    const float_q VERTICAL_FOV = SQFloat::_3;
    const float_q ASPECT_RATIO = SQFloat::_4;

    QSpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);

    // Execution
    QSpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionProjectionSpaceMatrix().SwitchHandConventionProjectionSpaceMatrix();

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], ORIGINAL_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], ORIGINAL_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], ORIGINAL_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], ORIGINAL_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], ORIGINAL_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], ORIGINAL_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], ORIGINAL_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], ORIGINAL_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], ORIGINAL_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], ORIGINAL_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], ORIGINAL_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], ORIGINAL_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], ORIGINAL_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], ORIGINAL_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], ORIGINAL_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], ORIGINAL_VALUE.ij[3][3]) );
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    QBaseMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)-968.0f;
    EXPECTED_VALUE.ij[0][1] = (float_q)992.0f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-176.0f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-396.0f;
    EXPECTED_VALUE.ij[1][1] = (float_q)-927.0f;
    EXPECTED_VALUE.ij[1][2] = (float_q)1044.0f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)1180.0f;
    EXPECTED_VALUE.ij[2][1] = (float_q)40.0f;
    EXPECTED_VALUE.ij[2][2] = (float_q)-810.0f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_TransformationIsCorrectlyBuiltFromCommonTransformations_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsTranslation_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(QQuaternion(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4).Normalize());
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    QBaseMatrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_q)0.13333344f;
    EXPECTED_VALUE.ij[0][1] = (float_q)0.93333322f;
    EXPECTED_VALUE.ij[0][2] = (float_q)-0.33333325f;
    EXPECTED_VALUE.ij[0][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_q)-0.66666657f;
    EXPECTED_VALUE.ij[1][1] = (float_q)0.33333343f;
    EXPECTED_VALUE.ij[1][2] = (float_q)0.66666657f;
    EXPECTED_VALUE.ij[1][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_q)0.73333323f;
    EXPECTED_VALUE.ij[2][1] = (float_q)0.13333333f;
    EXPECTED_VALUE.ij[2][2] = (float_q)0.66666675f;
    EXPECTED_VALUE.ij[2][3] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SQFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsRotation_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_CorrectResultObtainedWhenOnlyContainsScale_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetZeroMatrix();
    const QRotationMatrix3x3 ROTATION = QMatrix3x3::GetZeroMatrix();
    const QScalingMatrix3x3 SCALE = QMatrix3x3::GetZeroMatrix();

    QMatrix4x4 EXPECTED_VALUE = QMatrix4x4::GetZeroMatrix();
    EXPECTED_VALUE.ij[3][3] = SQFloat::_1;

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_FollowsLeftHandedRules_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_FollowsLeftHandedRules_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;
    using Kinesis::QuimeraEngine::Tools::Math::SQAngle;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
        const float_q ROTATION_ANGLE = SQAngle::_90;
    #else
        const float_q ROTATION_ANGLE = SQAngle::_HalfPi;
    #endif

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_0, SQFloat::_0, SQFloat::_0);
    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SQFloat::_0, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SQFloat::_0, ROTATION_ANGLE, SQFloat::_0);
    const QRotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SQFloat::_0, SQFloat::_0, ROTATION_ANGLE);

    QSpaceConversionMatrixWhiteBox ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    QSpaceConversionMatrixWhiteBox ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    QSpaceConversionMatrixWhiteBox ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SQFloat::_0, SQFloat::_0, SQFloat::_1);
    const QVector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SQFloat::_1, SQFloat::_0, SQFloat::_0);

    const QVector3 POSITION_BEFORE_ROTATION_AROUND_X(SQFloat::_0, SQFloat::_1, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SQFloat::_1, SQFloat::_0, SQFloat::_0);
    const QVector3 POSITION_BEFORE_ROTATION_AROUND_Z(SQFloat::_0, SQFloat::_1, SQFloat::_0);

    // Execution
    QVector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    QVector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    QVector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SQFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_FollowsLeftHandedRules_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_FollowsLeftHandedRules_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_FollowsLeftHandedRules_Template<QMatrix4x4>();
}

/// <summary>
/// Template method used by SetWorldSpaceMatrixImp_CompositionOrderIsScaleRotationTranslation_Template to test
/// using different template parameters for class QTranslationMatrix.
/// </summary>
template<class MatrixType>
void SetWorldSpaceMatrixImp_CompositionOrderIsScaleRotationTranslation_Template()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;
    using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QSpaceConversionMatrixWhiteBox;

    const QTranslationMatrix<MatrixType> TRANSLATION(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(QBaseQuaternion(SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7));
    const QScalingMatrix3x3 SCALE(SQFloat::_8, SQFloat::_9, SQFloat::_10);

    const QTranslationMatrix<QMatrix4x4> NEUTRAL_TRANSLATION = QMatrix4x4::GetZeroMatrix();
    const QRotationMatrix3x3 NEUTRAL_ROTATION = QRotationMatrix3x3::GetIdentity();
    const QScalingMatrix3x3 NEUTRAL_SCALE = QScalingMatrix3x3::GetIdentity();

    QSpaceConversionMatrixWhiteBox TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrixImp(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrixWhiteBox ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrixImp(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    QSpaceConversionMatrixWhiteBox SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrixImp(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const QSpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // Execution
    QSpaceConversionMatrixWhiteBox matrixUT;
    matrixUT.SetWorldSpaceMatrixImp(TRANSLATION, ROTATION, SCALE);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
QTEST_CASE( SetWorldSpaceMatrixImp_CompositionOrderIsScaleRotationTranslation_Test )
{
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    SetWorldSpaceMatrixImp_CompositionOrderIsScaleRotationTranslation_Template<QMatrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    SetWorldSpaceMatrixImp_CompositionOrderIsScaleRotationTranslation_Template<QMatrix4x4>();
}

// End - Test Suite: QSpaceConversionMatrix
QTEST_SUITE_END()
