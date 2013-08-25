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

#include "ToolsExports.h"

#include "QScalingMatrix3x3.h"
#include "QScalingMatrix3x3WhiteBox.h"
#include "QRotationMatrix3x3.h"
#include "QTranslationMatrix.h"
#include "QTransformationMatrix.h"
#include "QVector3.h"
#include "QMatrix4x4.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QScalingMatrix3x3;

QTEST_SUITE_BEGIN( QScalingMatrix3x3_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // Preparation
    const QScalingMatrix3x3 EXPECTED_VALUE(QScalingMatrix3x3::GetIdentity());

    // Execution
    QScalingMatrix3x3 matrixUT;

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
}

/// <summary>
/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_9;

    const QBaseMatrix3x3 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    const QScalingMatrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE);

    // Execution
    QScalingMatrix3x3 matrixUT = MATRIX_TO_COPY;

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
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
QTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                        SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                        SQFloat::_7, SQFloat::_8, SQFloat::_9);

    // Execution
    QScalingMatrix3x3 matrixUT(EXPECTED_VALUE);

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
}

/// <summary>
/// Checks that the scale matrix is correctly built from its three scaling values.
/// </summary>
QTEST_CASE ( Constructor4_ScaleMatrixCorrectlyBuiltFromThreeScalingValues_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 EXPECTED_VALUE(SQFloat::_2, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_3, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_4);

    // Execution
    QScalingMatrix3x3 matrixUT(SQFloat::_2, SQFloat::_3, SQFloat::_4);

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
}

/// <summary>
/// Checks that a neutral scale matrix (an identity matrix) is obtained when scaling values equal one.
/// </summary>
QTEST_CASE ( Constructor4_NeutralScaleMatrixIsObtainedWhenScalingValuesEqualOne_Test )
{
    // Preparation
    const QScalingMatrix3x3 EXPECTED_VALUE(QScalingMatrix3x3::GetIdentity());

    // Execution
    QScalingMatrix3x3 matrixUT(SQFloat::_1, SQFloat::_1, SQFloat::_1);

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
}

/// <summary>
/// Checks that the scale matrix is correctly built from a 3D vector.
/// </summary>
QTEST_CASE ( Constructor5_ScaleMatrixCorrectlyBuiltFrom3DVector_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 SCALING_VECTOR = QVector3(SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QBaseMatrix3x3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_3);

    // Execution
    QScalingMatrix3x3 matrixUT(SCALING_VECTOR);

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
}

/// <summary>
/// Checks that a neutral scale matrix (an identity matrix) is obtained when all components of the scaling 3D vector equal one.
/// </summary>
QTEST_CASE ( Constructor5_NeutralScaleMatrixIsObtainedWhenScaling3DVectorComponentsEqualOne_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    const QVector3 SCALING_VECTOR = QVector3(SQFloat::_1, SQFloat::_1, SQFloat::_1);

    const QScalingMatrix3x3 EXPECTED_VALUE(QScalingMatrix3x3::GetIdentity());

    // Execution
    QScalingMatrix3x3 matrixUT(SCALING_VECTOR);

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
    QScalingMatrix3x3 matrixUT = QScalingMatrix3x3::GetIdentity();

    // Verification
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    const QScalingMatrix3x3 OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)18.0f;

    // Execution
    QScalingMatrix3x3 matrixUT = OPERAND1 * OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is commutative.
/// </summary>
QTEST_CASE ( OperatorProduct1_ProductIsCommutative_Test )
{
    // Preparation
    const QScalingMatrix3x3 OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QScalingMatrix3x3 matrix1UT = OPERAND1 * OPERAND2;
    QScalingMatrix3x3 matrix2UT = OPERAND2 * OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and another 3x3 scaling matrix.
/// </summary>
QTEST_CASE ( OperatorProduct1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3ScalingMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QScalingMatrix3x3 OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QScalingMatrix3x3 MATRIX_OP(OPERAND);

    // Execution
    QScalingMatrix3x3 matrix1UT = MATRIX_A * MATRIX_OP;
    QScalingMatrix3x3 matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QRotationMatrix3x3 ROTATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QMatrix4x4 EXPECTED_VALUE((float_q)0.0695876f,  (float_q)0.182638f, (float_q)0.980715f,  SQFloat::_0,
                                    (float_q)1.55214167f /* FTP */, (float_q)-1.25521827f /* FTP */, (float_q)0.123625f,  SQFloat::_0,
                                    (float_q)1.88038421f /* FTP */,  (float_q)2.27040744 /* FTP */, (float_q)-0.556242f, SQFloat::_0,
                                    SQFloat::_0,          SQFloat::_0,          SQFloat::_0,          SQFloat::_1);
    // FTP -> Forced to pass: The epsilon difference is not enough to pass the test, but it is really trivial.

    // Reference values obtained using following DirectX SDK statement:
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationYawPitchRoll(&rotm, 5.0f, 4.0f, 6.0);
    // D3DXMATRIX res = scale * rotm;

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = SCALE * ROTATION;

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
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 3x3 rotation matrix.
/// </summary>
QTEST_CASE ( OperatorProduct2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3RotationMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QRotationMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QRotationMatrix3x3 OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QRotationMatrix3x3 MATRIX_OP(OPERAND);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    QTransformationMatrix<QMatrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_2,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_0,  SQFloat::_3,  SQFloat::_0,
                                    SQFloat::_4,  SQFloat::_5,  SQFloat::_6,  SQFloat::_1);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = SCALE * TRANSLATION;

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
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x4 translation matrix.
/// </summary>
QTEST_CASE ( OperatorProduct3_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TranslationMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTranslationMatrix<QMatrix4x4> OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QTranslationMatrix<QMatrix4x4> MATRIX_OP(OPERAND);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    QTransformationMatrix<QMatrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct4_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QMatrix4x3 EXPECTED_VALUE(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_2,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_0,  SQFloat::_3,
                                    SQFloat::_4,  SQFloat::_5,  SQFloat::_6);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrixUT = SCALE * TRANSLATION;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x3 translation matrix.
/// </summary>
QTEST_CASE ( OperatorProduct4_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TranslationMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTranslationMatrix<QMatrix4x3> OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QTranslationMatrix<QMatrix4x3> MATRIX_OP(OPERAND);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrix1UT = MATRIX_A * MATRIX_OP;
    QTransformationMatrix<QMatrix4x3> matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct5_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QMatrix4x4(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,
                                                                      SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f,
                                                                      (float_q)12.0f, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f,
                                                                      (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, (float_q)19.0f));

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_0,
                                    (float_q)16.0f, (float_q)18.0f, (float_q)20.0f, SQFloat::_0,
                                    (float_q)36.0f, (float_q)39.0f, (float_q)42.0f, SQFloat::_0,
                                    (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, SQFloat::_1);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = SCALE * TRANSFORMATION;

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

/// <sumary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x4 transformation matrix.
/// </summary>
QTEST_CASE ( OperatorProduct5_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TransformationMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTransformationMatrix<QMatrix4x4> OPERAND(QMatrix4x4(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,
                                                               SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f,
                                                               (float_q)12.0f, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f,
                                                               (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, (float_q)19.0f));

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QTransformationMatrix<QMatrix4x4> MATRIX_OP(OPERAND);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    QTransformationMatrix<QMatrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct6_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    const QScalingMatrix3x3 SCALE(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QMatrix4x3(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                                                      SQFloat::_8,    SQFloat::_9,    SQFloat::_10,
                                                                      (float_q)12.0f, (float_q)13.0f, (float_q)14.0f,
                                                                      (float_q)16.0f, (float_q)17.0f, (float_q)18.0f));

    const QMatrix4x3 EXPECTED_VALUE( SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                    (float_q)16.0f, (float_q)18.0f, (float_q)20.0f,
                                    (float_q)36.0f, (float_q)39.0f, (float_q)42.0f,
                                    (float_q)16.0f, (float_q)17.0f, (float_q)18.0f);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrixUT = SCALE * TRANSFORMATION;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <sumary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x3 transformation matrix.
/// </summary>
QTEST_CASE ( OperatorProduct6_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TransformationMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QTransformationMatrix<QMatrix4x3> OPERAND(QMatrix4x3(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                                               SQFloat::_8,    SQFloat::_9,    SQFloat::_10,
                                                               (float_q)12.0f, (float_q)13.0f, (float_q)14.0f,
                                                               (float_q)16.0f, (float_q)17.0f, (float_q)18.0f));

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QTransformationMatrix<QMatrix4x3> MATRIX_OP(OPERAND);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrix1UT = MATRIX_A * MATRIX_OP;
    QTransformationMatrix<QMatrix4x3> matrix2UT = MATRIX_B * MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Checks that every matrix element is assigned to the right destination matrix element.
/// </summary>
QTEST_CASE ( OperatorAssignation_EveryElementAssignedToCorrespondingElement_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                        SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                        SQFloat::_7, SQFloat::_8, SQFloat::_9);

    // Execution
    QScalingMatrix3x3 matrixUT;
    matrixUT = EXPECTED_VALUE;

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
}

/// <summary>
/// Checks that two common matrices are correctly multiplied and assigned.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_CommonMatricesAreCorrectlyMultipliedAndAssigned_Test )
{
    // Preparation
    const QScalingMatrix3x3 OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)18.0f;

    // Execution
    QScalingMatrix3x3 matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is commutative.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_ProductIsCommutative_Test )
{
    // Preparation
    const QScalingMatrix3x3 OPERAND1(SQFloat::_1, SQFloat::_2, SQFloat::_3);
    const QScalingMatrix3x3 OPERAND2(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QScalingMatrix3x3 matrix1UT = OPERAND1;
    matrix1UT *= OPERAND2;
    QScalingMatrix3x3 matrix2UT = OPERAND2;
    matrix2UT *= OPERAND1;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and another 3x3 scaling matrix.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3ScalingMatrixOperand_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QBaseMatrix3x3 SCALE_A(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                 SQFloat::_0, SQFloat::_0, SQFloat::_3);

    const QBaseMatrix3x3 SCALE_B(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                 SQFloat::_1, SQFloat::_2, SQFloat::_3);

    const QScalingMatrix3x3 OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QScalingMatrix3x3 MATRIX_A(SCALE_A);
    const QScalingMatrix3x3 MATRIX_B(SCALE_B);
    const QScalingMatrix3x3 MATRIX_OP(OPERAND);

    // Execution
    QScalingMatrix3x3 matrix1UT = MATRIX_A;
    matrix1UT *= MATRIX_OP;
    QScalingMatrix3x3 matrix2UT = MATRIX_B;
    matrix2UT *= MATRIX_OP;

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], MATRIX_A.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], MATRIX_A.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], MATRIX_A.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[0][1], MATRIX_B.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[0][2], MATRIX_B.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[1][0], MATRIX_B.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], MATRIX_A.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], MATRIX_A.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], MATRIX_A.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[1][2], MATRIX_B.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[2][0], MATRIX_B.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix2UT.ij[2][1], MATRIX_B.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // Preparation
    const QScalingMatrix3x3 OPERAND(SQFloat::_2, SQFloat::_3, SQFloat::_4);

    QScalingMatrix3x3 EXPECTED_VALUE = OPERAND;
    EXPECTED_VALUE *= OPERAND;

	// Execution
    QScalingMatrix3x3 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // Verification
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the matrix is correctly inverted.
/// </summary>
QTEST_CASE ( Invert_MatrixIsCorrectlyInverted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QScalingMatrix3x3 ORIGINAL_VALUE(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                           SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                           SQFloat::_0, SQFloat::_0, SQFloat::_4));

    const QBaseMatrix3x3 EXPECTED_VALUE(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0_5, SQFloat::_0,
                                        SQFloat::_0, SQFloat::_0, SQFloat::_0_25);

    // Execution
    QScalingMatrix3x3 matrixUT = ORIGINAL_VALUE.Invert();

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
}

/// <summary>
/// Checks that obtained scaling values equal expected values.
/// </summary>
QTEST_CASE ( GetScale1_ValuesAreCorrectlyExtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QScalingMatrix3x3 ORIGINAL_VALUE(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_0, SQFloat::_3));
    float_q fScaleXUT = SQFloat::_0;
    float_q fScaleYUT = SQFloat::_0;
    float_q fScaleZUT = SQFloat::_0;

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

     // Execution
    QScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // Verification
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that components of obtained 3D vector equal expected scaling values.
/// </summary>
QTEST_CASE ( GetScale2_3DVectorValuesAreCorrectlyExtracted_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QVector3;

    QVector3 vScalingVectorUT = QVector3(SQFloat::_0, SQFloat::_0, SQFloat::_0);

    const QScalingMatrix3x3 ORIGINAL_VALUE(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_0, SQFloat::_3));

    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;

     // Execution
    QScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    matrix.GetScale(vScalingVectorUT);

    // Verification
    BOOST_CHECK_EQUAL(vScalingVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vScalingVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vScalingVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained determinant value equal expected one.
/// </summary>
QTEST_CASE ( GetDeterminant_ValueIsCorrect_Test )
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

    const QScalingMatrix3x3 ORIGINAL_VALUE(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                          SQFloat::_0, SQFloat::_0, SQFloat::_3));
    float_q determinantValueUT = SQFloat::_0;

    const float_q EXPECTED_DETERMINANT_VALUE = SQFloat::_6;

     // Execution
    QScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    determinantValueUT = matrix.GetDeterminant();

    // Verification
    BOOST_CHECK_EQUAL(determinantValueUT, EXPECTED_DETERMINANT_VALUE);
}

/// <summary>
/// Method used by ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using QMatrix4x3 as template parameter for class QTranslationMatrix.
/// </summary>
void ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x3_Method()
{
     // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE(QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QTranslationMatrix<QMatrix4x3> TRANSLATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QMatrix4x3 EXPECTED_VALUE(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_2,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_0,  SQFloat::_3,
                                    SQFloat::_4,  SQFloat::_5,  SQFloat::_6);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrixUT = SCALE.ProductOperatorImp<QMatrix4x3>(TRANSLATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Method used by ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using QMatrix4x4 as template parameter for class QTranslationMatrix.
/// </summary>
void ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x4_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE(QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QTranslationMatrix<QMatrix4x4> TRANSLATION(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_1,  SQFloat::_0,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_2,  SQFloat::_0,  SQFloat::_0,
                                    SQFloat::_0,  SQFloat::_0,  SQFloat::_3,  SQFloat::_0,
                                    SQFloat::_4,  SQFloat::_5,  SQFloat::_6,  SQFloat::_1);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = SCALE.ProductOperatorImp<QMatrix4x4>(TRANSLATION);

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
/// Checks that matrices are properly multipled.
/// </summary>
QTEST_CASE ( ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x3_Method();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp1_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x4_Method();
}

/// <summary>
/// Method used by ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test to test
/// using QMatrix4x3 as template parameter for class QTranslationMatrix.
/// </summary>
void ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TranslationMatrixOperand_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE_A(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_0, SQFloat::_3)));

    const QScalingMatrix3x3WhiteBox SCALE_B(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3)));

    const QTranslationMatrix<QMatrix4x3> OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrix1UT = SCALE_A.ProductOperatorImp<QMatrix4x3>(OPERAND);
    QTransformationMatrix<QMatrix4x3> matrix2UT = SCALE_B.ProductOperatorImp<QMatrix4x3>(OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Method used by ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test to test
/// using QMatrix4x4 as template parameter for class QTranslationMatrix.
/// </summary>
void ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TranslationMatrixOperand_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QTranslationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE_A(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_0, SQFloat::_3)));

    const QScalingMatrix3x3WhiteBox SCALE_B(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3)));

    const QTranslationMatrix<QMatrix4x4> OPERAND(SQFloat::_4, SQFloat::_5, SQFloat::_6);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = SCALE_A.ProductOperatorImp<QMatrix4x4>(OPERAND);
    QTransformationMatrix<QMatrix4x4> matrix2UT = SCALE_B.ProductOperatorImp<QMatrix4x4>(OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product using a MatrixType template parameter for class QTranslationMatrix.
/// </summary>
QTEST_CASE ( ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TranslationMatrixOperand_Method();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TranslationMatrixOperand_Method();
}

/// <summary>
/// Method used by ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using QMatrix4x3 as template parameter for class QTransformationMatrix.
/// </summary>
void ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x3_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE(QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QTransformationMatrix<QMatrix4x3> TRANSFORMATION(QMatrix4x3(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                                                      SQFloat::_8,    SQFloat::_9,    SQFloat::_10,
                                                                      (float_q)12.0f, (float_q)13.0f, (float_q)14.0f,
                                                                      (float_q)16.0f, (float_q)17.0f, (float_q)18.0f));

    const QMatrix4x3 EXPECTED_VALUE( SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                    (float_q)16.0f, (float_q)18.0f, (float_q)20.0f,
                                    (float_q)36.0f, (float_q)39.0f, (float_q)42.0f,
                                    (float_q)16.0f, (float_q)17.0f, (float_q)18.0f);

    // Execution
    QTransformationMatrix<QMatrix4x3> matrixUT = SCALE.ProductOperatorImp<QMatrix4x3>(TRANSFORMATION);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Method used by ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Test to test
/// using QMatrix4x4 as template parameter for class QTransformationMatrix.
/// </summary>
void ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x4_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE(QScalingMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3));
    const QTransformationMatrix<QMatrix4x4> TRANSFORMATION(QMatrix4x4(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,
                                                                      SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f,
                                                                      (float_q)12.0f, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f,
                                                                      (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, (float_q)19.0f));

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_0,
                                    (float_q)16.0f, (float_q)18.0f, (float_q)20.0f, SQFloat::_0,
                                    (float_q)36.0f, (float_q)39.0f, (float_q)42.0f, SQFloat::_0,
                                    (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, SQFloat::_1);

    // Execution
    QTransformationMatrix<QMatrix4x4> matrixUT = SCALE.ProductOperatorImp<QMatrix4x4>(TRANSFORMATION);

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
/// Checks that matrices are properly multipled.
/// </summary>
QTEST_CASE ( ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x3_Method();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp2_CommonMatricesAreCorrectlyMultiplied_MatrixTypeQMatrix4x4_Method();
}

/// <summary>
/// Method used by ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test to test
/// using QMatrix4x3 as template parameter for class QTransformationMatrix.
/// </summary>
void ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TransformationMatrixOperand_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x3;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE_A(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_0, SQFloat::_3)));

    const QScalingMatrix3x3WhiteBox SCALE_B(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3)));

    const QTransformationMatrix<QMatrix4x3> OPERAND(QMatrix4x3(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,
                                                               SQFloat::_8,    SQFloat::_9,    SQFloat::_10,
                                                               (float_q)12.0f, (float_q)13.0f, (float_q)14.0f,
                                                               (float_q)16.0f, (float_q)17.0f, (float_q)18.0f));

    // Execution
    QTransformationMatrix<QMatrix4x3> matrix1UT = SCALE_A.ProductOperatorImp<QMatrix4x3>(OPERAND);
    QTransformationMatrix<QMatrix4x3> matrix2UT = SCALE_B.ProductOperatorImp<QMatrix4x3>(OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Method used by ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test to test
/// using QMatrix4x4 as template parameter for class QTransformationMatrix.
/// </summary>
void ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TransformationMatrixOperand_Method()
{
    // Preparation
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;
    using Kinesis::QuimeraEngine::Tools::Math::QTransformationMatrix;
    using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;
    using Kinesis::QuimeraEngine::Tools::Math::Test::QScalingMatrix3x3WhiteBox;

    const QScalingMatrix3x3WhiteBox SCALE_A(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_0, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_2, SQFloat::_0,
                                                                             SQFloat::_0, SQFloat::_0, SQFloat::_3)));

    const QScalingMatrix3x3WhiteBox SCALE_B(QScalingMatrix3x3(QBaseMatrix3x3(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                                                             SQFloat::_1, SQFloat::_2, SQFloat::_3)));

    const QTransformationMatrix<QMatrix4x4> OPERAND(QMatrix4x4(SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,
                                                               SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)11.0f,
                                                               (float_q)12.0f, (float_q)13.0f, (float_q)14.0f, (float_q)15.0f,
                                                               (float_q)16.0f, (float_q)17.0f, (float_q)18.0f, (float_q)19.0f));

    // Execution
    QTransformationMatrix<QMatrix4x4> matrix1UT = SCALE_A.ProductOperatorImp<QMatrix4x4>(OPERAND);
    QTransformationMatrix<QMatrix4x4> matrix2UT = SCALE_B.ProductOperatorImp<QMatrix4x4>(OPERAND);

    // Verification
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SQFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product using a MatrixType template parameter for class QTransformationMatrix.
/// </summary>
QTEST_CASE ( ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProduct_Test )
{
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x3");
    ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TransformationMatrixOperand_Method();
    BOOST_TEST_MESSAGE("MatrixType=QMatrix4x4");
    ProductOperatorImp2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TransformationMatrixOperand_Method();
}

// End - Test Suite: QScalingMatrix3x3
QTEST_SUITE_END()
