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

#include "QMatrix4x4.h"

#include "QMatrix4x3.h"
#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;
using Kinesis::QuimeraEngine::Tools::Math::QMatrix4x4;


QTEST_SUITE_BEGIN( QMatrix4x4_TestSuite )

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( FriendOperatorProduct_EveryElementIsMultipliedByTheScalar_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4,
                            SQFloat::_5, SQFloat::_6, SQFloat::_7, SQFloat::_8,
                            SQFloat::_9, SQFloat::_10, (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)14.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)16.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)18.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)20.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)22.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)24.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)26.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)28.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)30.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)32.0;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // [Execution]
    QMatrix4x4 matrixUT = SCALAR_VALUE * MATRIX;

    // [Verification]
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
/// Checks if default values have changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // [Execution]
    QMatrix4x4 matrixUT;

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// Checks if copy constructor copies every matrix element properly.
/// </summary>
QTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // [Preparation]
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

    const QMatrix4x4 MATRIX_TO_COPY(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                                    EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                                    EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                                    EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX_TO_COPY;

    // [Verification]
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
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    const QBaseMatrix4x4 EXPECTED_VALUE(SQFloat::_0, SQFloat::_1, SQFloat::_2, SQFloat::_3,
                                        SQFloat::_4, SQFloat::_5, SQFloat::_6, SQFloat::_7,
                                        SQFloat::_8, SQFloat::_9, SQFloat::_10, (float_q)11.0,
                                        (float_q)12.0, (float_q)13.0, (float_q)14.0, (float_q)15.0);

    // [Execution]
    QMatrix4x4 matrixUT(EXPECTED_VALUE);

    // [Verification]
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
/// Checks if the value provided is set to all the matrix components.
/// </summary>
QTEST_CASE ( Constructor4_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_5;

    // [Execution]
    QMatrix4x4 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
QTEST_CASE ( Constructor5_ValuesAreSetProperly_Test )
{
    // [Preparation]
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

	// [Execution]
    QMatrix4x4 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                            EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                            EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                            EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    // [Verification]
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
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
QTEST_CASE ( Constructor6_MatrixComponentsAreFilledWithValidReferenceTo16Floats_Test )
{
   // [Preparation]
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
    const float_q EXPECTED_VALUE_FOR_30 = SQFloat::_10 + SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_31 = SQFloat::_10 + SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_32 = SQFloat::_10 + SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_33 = SQFloat::_10 + SQFloat::_6;


    float_q* VALID_ARRAY_OF_16_FLOATS = new float_q[16];
    VALID_ARRAY_OF_16_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_16_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_16_FLOATS[2] = EXPECTED_VALUE_FOR_02;
    VALID_ARRAY_OF_16_FLOATS[3] = EXPECTED_VALUE_FOR_03;
    VALID_ARRAY_OF_16_FLOATS[4] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_16_FLOATS[5] = EXPECTED_VALUE_FOR_11;
    VALID_ARRAY_OF_16_FLOATS[6] = EXPECTED_VALUE_FOR_12;
    VALID_ARRAY_OF_16_FLOATS[7] = EXPECTED_VALUE_FOR_13;
    VALID_ARRAY_OF_16_FLOATS[8] = EXPECTED_VALUE_FOR_20;
    VALID_ARRAY_OF_16_FLOATS[9] = EXPECTED_VALUE_FOR_21;
    VALID_ARRAY_OF_16_FLOATS[10] = EXPECTED_VALUE_FOR_22;
    VALID_ARRAY_OF_16_FLOATS[11] = EXPECTED_VALUE_FOR_23;
    VALID_ARRAY_OF_16_FLOATS[12] = EXPECTED_VALUE_FOR_30;
    VALID_ARRAY_OF_16_FLOATS[13] = EXPECTED_VALUE_FOR_31;
    VALID_ARRAY_OF_16_FLOATS[14] = EXPECTED_VALUE_FOR_32;
    VALID_ARRAY_OF_16_FLOATS[15] = EXPECTED_VALUE_FOR_33;

	// [Execution]
    QMatrix4x4 matrixUT(VALID_ARRAY_OF_16_FLOATS);

    // [Verification]
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

    // Cleaning
    delete [] VALID_ARRAY_OF_16_FLOATS;
    VALID_ARRAY_OF_16_FLOATS = null_q;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
QTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_q* NULL_ARRAY = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMatrix4x4 vMatrixUT(NULL_ARRAY);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
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
QTEST_CASE ( Constructor7_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
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
    const float_q EXPECTED_VALUE_FOR_30 = SQFloat::_10 + SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_31 = SQFloat::_10 + SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_32 = SQFloat::_10 + SQFloat::_5;
    const float_q EXPECTED_VALUE_FOR_33 = SQFloat::_10 + SQFloat::_6;


	vf32_q PACK0, PACK1, PACK2, PACK3;
	SQVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03, PACK0);
	SQVF32::Pack(EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13, PACK1);
	SQVF32::Pack(EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23, PACK2);
	SQVF32::Pack(EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33, PACK3);

	// [Execution]
	QMatrix4x4 matrixUT(PACK0, PACK1, PACK2, PACK3);

    // [Verification]
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
/// Checks that all the elements of the returned matrix equal zero.
/// </summary>
QTEST_CASE ( GetZeroMatrix_AllElementsEqualZero_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

	// [Execution]
    QMatrix4x4 matrixUT = QMatrix4x4::GetZeroMatrix();

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
QTEST_CASE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test )
{
    // [Preparation]
    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DIAGONAL = SQFloat::_1;

	// [Execution]
    QMatrix4x4 matrixUT = QMatrix4x4::GetIdentity();

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProduct1_EveryElementIsMultipliedByTheScalar_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;
    const QMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const float_q EXPECTED_VALUE_FOR_00 = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_01 = SQFloat::_4;
    const float_q EXPECTED_VALUE_FOR_02 = SQFloat::_6;
    const float_q EXPECTED_VALUE_FOR_03 = SQFloat::_8;
    const float_q EXPECTED_VALUE_FOR_10 = SQFloat::_10;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)12.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)14.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)16.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)18.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)20.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)22.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)24.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)26.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)28.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)30.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)32.0;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX * SCALAR_VALUE;

    // [Verification]
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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)250.0;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)260.0;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)270.0;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)280.0;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)618.0;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)644.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)670.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)696.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)986.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)1028.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)1070.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)1112.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)1354.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)1412.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)1470.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)1528.0;

    // [Execution]
    QMatrix4x4 matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
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
QTEST_CASE ( OperatorProduct2_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const QMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                              (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                              (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                              (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    // [Execution]
    QMatrix4x4 matrix1UT = OPERAND1 * OPERAND2;
    QMatrix4x4 matrix2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
QTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x3;

    const QMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x3 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)250.0;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)260.0;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)270.0;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)618.0;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)644.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)670.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)986.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)1028.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)1070.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)1354.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)1412.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)1470.0;

    // [Execution]
    QBaseMatrix4x3 matrixUT = OPERAND1 * OPERAND2;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivision_EveryElementIsDividedByTheScalar_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                            SQFloat::_10,   (float_q)12.0, (float_q)14.0, (float_q)16.0,
                            (float_q)18.0, (float_q)20.0, (float_q)22.0, (float_q)24.0,
                            (float_q)26.0, (float_q)28.0, (float_q)30.0, (float_q)32.0);

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
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)11.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)12.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)13.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)14.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)15.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)16.0;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX / SCALAR_VALUE;

    // [Verification]
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

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivision_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const float_q ZERO_SCALAR = SQFloat::_0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMatrix4x4 vMatrixUT;
        vMatrixUT / ZERO_SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that two common matrices are correctly added.
/// </summary>
QTEST_CASE ( OperatorAddition_CommonMatricesAreCorrectlyAdded_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)18.0;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)20.0;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)22.0;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)24.0;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)26.0;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)28.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)30.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)32.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)34.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)36.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)38.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)40.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)42.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)44.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)46.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)48.0;

    // [Execution]
    QMatrix4x4 matrixUT = OPERAND1 + OPERAND2;

    // [Verification]
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
/// Checks that two common matrices are correctly subtraction.
/// </summary>
QTEST_CASE ( OperatorSubtraction_CommonMatricesAreCorrectlySubtracted_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix4x4 OPERAND1((float_q)18.0, (float_q)20.0, (float_q)22.0, (float_q)24.0,
                              (float_q)26.0, (float_q)28.0, (float_q)30.0, (float_q)32.0,
                              (float_q)34.0, (float_q)36.0, (float_q)38.0, (float_q)40.0,
                              (float_q)42.0, (float_q)44.0, (float_q)46.0, (float_q)48.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                    SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                    (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    // [Execution]
    QMatrix4x4 matrixUT = OPERAND1 - OPERAND2;

    // [Verification]
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
QTEST_CASE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                  SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                  SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                  (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)250.0;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)260.0;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)270.0;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)280.0;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)618.0;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)644.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)670.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)696.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)986.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)1028.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)1070.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)1112.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)1354.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)1412.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)1470.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)1528.0;

    // [Execution]
    QMatrix4x4 matrixUT(OPERAND1);
    matrixUT *= OPERAND2;

    // [Verification]
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
QTEST_CASE ( OperatorProductAssignation1_ProductIsNotCommutative_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                  SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                  SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                  (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    // [Execution]
    QMatrix4x4 matrix1UT(OPERAND1);
    matrix1UT *= OPERAND2;
    QMatrix4x4 matrix2UT(OPERAND2);
    matrix2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
QTEST_CASE ( OperatorProductAssignation1_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const QMatrix4x4 OPERAND(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                             SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                             SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                             (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QMatrix4x4 EXPECTED_VALUE = OPERAND * OPERAND;

	// [Execution]
    QMatrix4x4 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // [Verification]
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if all the elements of the matrix are multiplied by the scalar.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_MatrixIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const float_q  SCALAR = SQFloat::_2;

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                                    SQFloat::_10,   (float_q)12.0, (float_q)14.0, (float_q)16.0,
                                    (float_q)18.0, (float_q)20.0, (float_q)22.0, (float_q)24.0,
                                    (float_q)26.0, (float_q)28.0, (float_q)30.0, (float_q)32.0);

	// [Execution]
    QMatrix4x4 matrixUT = MATRIX;
    matrixUT *= SCALAR;

    // [Verification]
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
/// Checks that a matrix element is multiplied and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorProductAssignation2_MatrixIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX((float_q)0.9,  SQFloat::_1,    SQFloat::_2,     (float_q)0.3,
                            SQFloat::_7,    SQFloat::_0_5,  SQFloat::_4,     (float_q)0.02,
                            SQFloat::_3,    (float_q)0.07, (float_q)0.033, (float_q)0.001,
                            SQFloat::_0_25, (float_q)0.08, (float_q)6.6,   SQFloat::_5);

    QMatrix4x4 EXPECTED_VALUE((float_q)0.9,  SQFloat::_1,    SQFloat::_2,     (float_q)0.3,
                              SQFloat::_7,    SQFloat::_0_5,  SQFloat::_4,     (float_q)0.02,
                              SQFloat::_3,    (float_q)0.07, (float_q)0.033, (float_q)0.001,
                              SQFloat::_0_25, (float_q)0.08, (float_q)6.6,   SQFloat::_5);

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
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[3][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[3][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[3][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[3][3];

	// [Execution]
    QMatrix4x4 matrixUT = MATRIX;
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
    matrixUT *= matrixUT.ij[3][0];
    matrixUT *= matrixUT.ij[3][1];
    matrixUT *= matrixUT.ij[3][2];
    matrixUT *= matrixUT.ij[3][3];

    // [Verification]
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
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_EveryElementIsDividedByTheScalar_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_2,    SQFloat::_4,    SQFloat::_6,    SQFloat::_8,
                            SQFloat::_10,   (float_q)12.0, (float_q)14.0, (float_q)16.0,
                            (float_q)18.0, (float_q)20.0, (float_q)22.0, (float_q)24.0,
                            (float_q)26.0, (float_q)28.0, (float_q)30.0, (float_q)32.0);

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
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)11.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)12.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)13.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)14.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)15.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)16.0;

    const float_q SCALAR_VALUE = SQFloat::_2;

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX;
    matrixUT /= SCALAR_VALUE;

    // [Verification]
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
/// Checks that a matrix element is divided and assigned to itself.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_MatrixIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    QMatrix4x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

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
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[3][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[3][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[3][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[3][3];

	// [Execution]
    QMatrix4x4 matrixUT = MATRIX;
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
    matrixUT /= matrixUT.ij[3][0];
    matrixUT /= matrixUT.ij[3][1];
    matrixUT /= matrixUT.ij[3][2];
    matrixUT /= matrixUT.ij[3][3];

    // [Verification]
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

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
QTEST_CASE ( OperatorDivisionAssignation_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const float_q ZERO_SCALAR = SQFloat::_0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMatrix4x4 vMatrixUT;
        vMatrixUT /= ZERO_SCALAR;
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that two common matrices are correctly added.
/// </summary>
QTEST_CASE ( OperatorAdditionAssignation_CommonMatricesAreCorrectlyAdded_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix4x4 OPERAND1(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                              SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                              SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                              (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const float_q EXPECTED_VALUE_FOR_00 = (float_q)18.0;
    const float_q EXPECTED_VALUE_FOR_01 = (float_q)20.0;
    const float_q EXPECTED_VALUE_FOR_02 = (float_q)22.0;
    const float_q EXPECTED_VALUE_FOR_03 = (float_q)24.0;
    const float_q EXPECTED_VALUE_FOR_10 = (float_q)26.0;
    const float_q EXPECTED_VALUE_FOR_11 = (float_q)28.0;
    const float_q EXPECTED_VALUE_FOR_12 = (float_q)30.0;
    const float_q EXPECTED_VALUE_FOR_13 = (float_q)32.0;
    const float_q EXPECTED_VALUE_FOR_20 = (float_q)34.0;
    const float_q EXPECTED_VALUE_FOR_21 = (float_q)36.0;
    const float_q EXPECTED_VALUE_FOR_22 = (float_q)38.0;
    const float_q EXPECTED_VALUE_FOR_23 = (float_q)40.0;
    const float_q EXPECTED_VALUE_FOR_30 = (float_q)42.0;
    const float_q EXPECTED_VALUE_FOR_31 = (float_q)44.0;
    const float_q EXPECTED_VALUE_FOR_32 = (float_q)46.0;
    const float_q EXPECTED_VALUE_FOR_33 = (float_q)48.0;

    // [Execution]
    QMatrix4x4 matrixUT = OPERAND1;
    matrixUT += OPERAND2;

    // [Verification]
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
/// Checks that two common matrices are correctly subtracted.
/// </summary>
QTEST_CASE ( OperatorSubtractionAssignation_CommonMatricesAreCorrectlySubtracted_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QMatrix4x4 OPERAND1((float_q)18.0, (float_q)20.0, (float_q)22.0, (float_q)24.0,
                              (float_q)26.0, (float_q)28.0, (float_q)30.0, (float_q)32.0,
                              (float_q)34.0, (float_q)36.0, (float_q)38.0, (float_q)40.0,
                              (float_q)42.0, (float_q)44.0, (float_q)46.0, (float_q)48.0);

    const QBaseMatrix4x4 OPERAND2((float_q)17.0, (float_q)18.0, (float_q)19.0, (float_q)20.0,
                                  (float_q)21.0, (float_q)22.0, (float_q)23.0, (float_q)24.0,
                                  (float_q)25.0, (float_q)26.0, (float_q)27.0, (float_q)28.0,
                                  (float_q)29.0, (float_q)30.0, (float_q)31.0, (float_q)32.0);

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                    SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                    SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                    (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    // [Execution]
    QMatrix4x4 matrixUT = OPERAND1;
    matrixUT -= OPERAND2;

    // [Verification]
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
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
QTEST_CASE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 EXPECTED_VALUE(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                        SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                        SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                        (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    // [Execution]
    QMatrix4x4 matrixUT;
    matrixUT = EXPECTED_VALUE;

    // [Verification]
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
/// Checks that every element of the matrix equals zero.
/// </summary>
QTEST_CASE ( ResetToZero_AllElementsEqualZero_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Tools::Math::QBaseMatrix4x4;

    const QBaseMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                                SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                                SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                                (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;

    // [Execution]
    QMatrix4x4 matrixUT(MATRIX);
    matrixUT.ResetToZero();

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that every element of the matrix equals zero but diagonal's, which equal one.
/// </summary>
QTEST_CASE ( ResetToIdentity_AllElementsEqualZeroButDiagonalThatEqualsOne_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const float_q EXPECTED_VALUE_FOR_ALL = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_DIAGONAL = SQFloat::_1;

    // [Execution]
    QMatrix4x4 matrixUT(MATRIX);
    matrixUT.ResetToIdentity();

    // [Verification]
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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks that every element that occupies the position ij, now is at the position ji.
/// </summary>
QTEST_CASE ( Transpose_TheRowAndColumOfElementsAreSwapped_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_1,    SQFloat::_2,    SQFloat::_3,    SQFloat::_4,
                            SQFloat::_5,    SQFloat::_6,    SQFloat::_7,    SQFloat::_8,
                            SQFloat::_9,    SQFloat::_10,   (float_q)11.0, (float_q)12.0,
                            (float_q)13.0, (float_q)14.0, (float_q)15.0, (float_q)16.0);

    const QMatrix4x4 EXPECTED_VALUE(SQFloat::_1, SQFloat::_5, SQFloat::_9,    (float_q)13.0,
                                    SQFloat::_2, SQFloat::_6, SQFloat::_10,   (float_q)14.0,
                                    SQFloat::_3, SQFloat::_7, (float_q)11.0, (float_q)15.0,
                                    SQFloat::_4, SQFloat::_8, (float_q)12.0, (float_q)16.0);

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX.Transpose();

    // [Verification]
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
/// Checks that it returns True when all the matrix elements equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // [Preparation]
    const QMatrix4x4 ZERO_MATRIX = QMatrix4x4::GetZeroMatrix();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    QMatrix4x4 matrixUT = ZERO_MATRIX;
    bool bResult = matrixUT.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when not all the matrix elements equal zero.
/// </summary>
QTEST_CASE ( IsZero_ReturnsFalseWhenNotAllElementsEqualZero_Test )
{
    // [Preparation]
    const QMatrix4x4 ZERO_MATRIX = QMatrix4x4::GetZeroMatrix();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    QMatrix4x4 matrixUT = ZERO_MATRIX;
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
    matrixUT.ij[2][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][3] = SQFloat::_0;
    matrixUT.ij[3][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[3][0] = SQFloat::_0;
    matrixUT.ij[3][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[3][1] = SQFloat::_0;
    matrixUT.ij[3][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[3][2] = SQFloat::_0;
    matrixUT.ij[3][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero but the diagonal's, which equal one.
/// </summary>
QTEST_CASE ( IsIdentity_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // [Preparation]
    const QMatrix4x4 IDENTITY = QMatrix4x4::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    QMatrix4x4 matrixUT = IDENTITY;
    bool bResult = matrixUT.IsIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the matrix is not an identity matrix.
/// </summary>
QTEST_CASE ( IsIdentity_ReturnsFalseWhenItsNotIdentity_Test )
{
    // [Preparation]
    const QMatrix4x4 IDENTITY = QMatrix4x4::GetIdentity();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    QMatrix4x4 matrixUT = IDENTITY;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][0] = SQFloat::_1;
    matrixUT.ij[0][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][1] = SQFloat::_0;
    matrixUT.ij[0][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][2] = SQFloat::_0;
    matrixUT.ij[0][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][3] = SQFloat::_0;
    matrixUT.ij[1][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][0] = SQFloat::_0;
    matrixUT.ij[1][1] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][1] = SQFloat::_1;
    matrixUT.ij[1][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][2] = SQFloat::_0;
    matrixUT.ij[1][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][3] = SQFloat::_0;
    matrixUT.ij[2][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][0] = SQFloat::_0;
    matrixUT.ij[2][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][1] = SQFloat::_0;
    matrixUT.ij[2][2] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][2] = SQFloat::_1;
    matrixUT.ij[2][3] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][3] = SQFloat::_0;
    matrixUT.ij[3][0] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[3][0] = SQFloat::_0;
    matrixUT.ij[3][1] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[3][1] = SQFloat::_0;
    matrixUT.ij[3][2] = SQFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[3][2] = SQFloat::_0;
    matrixUT.ij[3][3] = SQFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of a common matrix is correctly obtained.
/// </summary>
QTEST_CASE ( GetDeterminant_ItsCorrectlyCalculatedForCommonMatrix_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_3,    SQFloat::_2,    SQFloat::_0,    SQFloat::_1,
                            SQFloat::_4,    SQFloat::_0,    SQFloat::_1,    SQFloat::_2,
                            SQFloat::_3,    SQFloat::_0,    SQFloat::_2,    SQFloat::_1,
                            SQFloat::_9,    SQFloat::_2,    SQFloat::_3,    SQFloat::_1);

    const float_q EXPECTED_VALUE = (float_q)24.0;

    // [Execution]
    float_q fResultUT = MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the identity equals one.
/// </summary>
QTEST_CASE ( GetDeterminant_DeterminantOfIdentityEqualsOne_Test )
{
    // [Preparation]
    const QMatrix4x4 IDENTITY = QMatrix4x4::GetIdentity();
    const float_q EXPECTED_VALUE = SQFloat::_1;

    // [Execution]
    float_q fResultUT = IDENTITY.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the zero matrix equals zero.
/// </summary>
QTEST_CASE ( GetDeterminant_DeterminantOfZeroMatrixEqualsZero_Test )
{
    // [Preparation]
    const QMatrix4x4 ZERO_MATRIX = QMatrix4x4::GetZeroMatrix();
    const float_q EXPECTED_VALUE = SQFloat::_0;

    // [Execution]
    float_q fResultUT = ZERO_MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common matrix is correctly inverted.
/// </summary>
QTEST_CASE ( Invert_CommonMatrixIsCorrectlyInverted_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_3,    SQFloat::_2,    SQFloat::_0,    SQFloat::_1,
                            SQFloat::_4,    SQFloat::_0,    SQFloat::_1,    SQFloat::_2,
                            SQFloat::_3,    SQFloat::_0,    SQFloat::_2,    SQFloat::_1,
                            SQFloat::_9,    SQFloat::_2,    SQFloat::_3,    SQFloat::_1);

    const QMatrix4x4 EXPECTED_VALUE(-SQFloat::_0_25,      SQFloat::_0_25,  -SQFloat::_0_5, SQFloat::_0_25,
                                    (float_q)0.66666666666666663, -SQFloat::_0_5,  SQFloat::_0_5,  (float_q)-0.16666666666666666,
                                    (float_q)0.16666666666666666, -SQFloat::_0_5,  SQFloat::_1,    (float_q)-0.16666666666666666,
                                    (float_q)0.41666666666666663, SQFloat::_0_25,  SQFloat::_0_5,  (float_q)-0.41666666666666663);

    // [Execution]
    QMatrix4x4 matrixUT = MATRIX.Invert();

    // [Verification]
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
/// Checks that it returns True when the determinant of the matrix doesn't equal zero.
/// </summary>
QTEST_CASE ( HasInverse_ReturnsTrueWhenDeterminantIsNotZero_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX = QMatrix4x4::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the determinant of the matrix equals zero.
/// </summary>
QTEST_CASE ( HasInverse_ReturnsFalseWhenDeterminantIsZero_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX = QMatrix4x4::GetZeroMatrix();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
QTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const QMatrix4x4 MATRIX(SQFloat::_0,    SQFloat::_1,    SQFloat::_2,    (float_q)0.654321,
                            SQFloat::_4,    SQFloat::_5,    SQFloat::_6,    (float_q)-2.2,
                            SQFloat::_8,    SQFloat::_9,    SQFloat::_10,   (float_q)123456.0,
                            (float_q)12.0, (float_q)13.0, (float_q)14.0, (float_q)1234567.89);

    #if QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_SIMPLE
        const string_q EXPECTED_STRING_FORM = QE_L("M4x4(0,1,2,0.654321015,4,5,6,-2.20000005,8,9,10,123456,12,13,14,1234567.88)");
    #elif QE_CONFIG_PRECISION_DEFAULT == QE_CONFIG_PRECISION_DOUBLE
        const string_q EXPECTED_STRING_FORM = QE_L("M4x4(0,1,2,0.65432100000000004,4,5,6,-2.2000000000000002,8,9,10,123456,12,13,14,1234567.8899999999)");
    #endif

	// [Execution]
    QMatrix4x4 matrixUT = MATRIX;
    string_q strStringForm = matrixUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: QMatrix4x4
QTEST_SUITE_END()
