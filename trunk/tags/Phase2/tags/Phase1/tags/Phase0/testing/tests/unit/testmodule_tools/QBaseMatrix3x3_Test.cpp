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

#include "QBaseMatrix3x3.h"

#include "SQVF32.h"
#include "SQFloat.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix3x3;

QTEST_SUITE_BEGIN( QBaseMatrix3x3_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    QBaseMatrix3x3 matrixUT;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
}

/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_9;

    const QBaseMatrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    // [Execution]
    QBaseMatrix3x3 matrixUT = MATRIX_TO_COPY;

    // [Verification]
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
/// Checks if the value provided is set to all the matrix components.
/// </summary>
QTEST_CASE ( Constructor3_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

    QBaseMatrix3x3 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
QTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
   // [Preparation]
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_9;

	// [Execution]
    QBaseMatrix3x3 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                            EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                            EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    // [Verification]
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
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor5_MatrixComponentsAreFilledWithValidReferenceTo9Floats_Test )
{
   // [Preparation]
    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_9;

    float_q* VALID_ARRAY_OF_9_FLOATS = new float_q[9];
    VALID_ARRAY_OF_9_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_9_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_9_FLOATS[2] = EXPECTED_VALUE_FOR_02;
    VALID_ARRAY_OF_9_FLOATS[3] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_9_FLOATS[4] = EXPECTED_VALUE_FOR_11;
    VALID_ARRAY_OF_9_FLOATS[5] = EXPECTED_VALUE_FOR_12;
    VALID_ARRAY_OF_9_FLOATS[6] = EXPECTED_VALUE_FOR_20;
    VALID_ARRAY_OF_9_FLOATS[7] = EXPECTED_VALUE_FOR_21;
    VALID_ARRAY_OF_9_FLOATS[8] = EXPECTED_VALUE_FOR_22;

	// [Execution]
    QBaseMatrix3x3 matrixUT(VALID_ARRAY_OF_9_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);

    // Cleanup
    delete [] VALID_ARRAY_OF_9_FLOATS;
    VALID_ARRAY_OF_9_FLOATS=null_q;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_q* NULL_ARRAY = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QBaseMatrix3x3 vMatrixUT(NULL_ARRAY);
    }
    catch(...) // TODO [jmartin]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if matrix components are set to the correct values packed in valid vf32 objects.
/// </summary>
QTEST_CASE ( Constructor6_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_11 = SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_12 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_20 = SQFloat::_7;
    const float_q EXPECTED_VALUE_FOR_21 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_22 = SQFloat::_9;

	vf32_q PACK0, PACK1, PACK2;
	SQVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, SQFloat::_0, PACK0);
	SQVF32::Pack(EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, SQFloat::_0, PACK1);
	SQVF32::Pack(EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, SQFloat::_0, PACK2);

	// [Execution]
	QBaseMatrix3x3 matrixUT(PACK0, PACK1, PACK2);

    // [Verification]
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
/// Checks if the equility operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseMatrix3x3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equility operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_q HALF_TOLERANCE = SQFloat::Epsilon * SQFloat::_0_5;

    const QBaseMatrix3x3 LEFT_OPERAND(HALF_TOLERANCE);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equility operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_q ONE_AND_A_HALF_TOLERANCE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;

    const QBaseMatrix3x3 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the equility operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseMatrix3x3 LEFT_OPERAND(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                      SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                      SQFloat::_7, SQFloat::_8, SQFloat::_9);

    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                       SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                       SQFloat::_7, SQFloat::_8, SQFloat::_9);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const QBaseMatrix3x3 LEFT_OPERAND(SQFloat::Epsilon);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the inequality operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    const float_q HALF_TOLERANCE = SQFloat::Epsilon * SQFloat::_0_5;

   // [Preparation]
    const QBaseMatrix3x3 LEFT_OPERAND(HALF_TOLERANCE);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the inequality operator returns true when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_q ONE_AND_A_HALF_TOLERANCE = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;

    const QBaseMatrix3x3 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const QBaseMatrix3x3 LEFT_OPERAND(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                      SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                      SQFloat::_7, SQFloat::_8, SQFloat::_9);

    const QBaseMatrix3x3 RIGHT_OPERAND(SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                       SQFloat::_4, SQFloat::_5, SQFloat::_6,
                                       SQFloat::_7, SQFloat::_8, SQFloat::_9);
	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND));
}

// End - Test Suite: QBaseMatrix3x3
QTEST_SUITE_END()
