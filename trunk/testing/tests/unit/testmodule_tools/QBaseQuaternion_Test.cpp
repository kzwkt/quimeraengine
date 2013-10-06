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

#include "QBaseQuaternion.h"

#include "SQFloat.h"
#include "SQVF32.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQVF32;
using Kinesis::QuimeraEngine::Tools::DataTypes::vf32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::float_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::SQFloat;
using Kinesis::QuimeraEngine::Tools::Math::QBaseQuaternion;

QTEST_SUITE_BEGIN( QBaseQuaternion_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_0;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_0;
    
    // Execution
    QBaseQuaternion qQuaternionUT;
    
    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if copy constructor sets quaternion components properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;
    
    const QBaseQuaternion QUAT_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);
    
    // Execution
    QBaseQuaternion qQuatUT = QUAT_TO_COPY;
    
    // Verification
    BOOST_CHECK_EQUAL(qQuatUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuatUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuatUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuatUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
QTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_W = SQFloat::_4;
    
    // Execution
    QBaseQuaternion qQuaternionUT(SQFloat::_1, SQFloat::_2, SQFloat::_3, SQFloat::_4);
    
    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that every element of the array is put in the correct component.
/// </summary>
QTEST_CASE ( Constructor4_QuaternionComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;
    
    float_q* VALID_ARRAY_OF_4_FLOATS = new float_q[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_Z;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_W;
    
    // Execution
    QBaseQuaternion qQuaternionUT(VALID_ARRAY_OF_4_FLOATS);
    
    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, VALID_ARRAY_OF_4_FLOATS[0]);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, VALID_ARRAY_OF_4_FLOATS[1]);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, VALID_ARRAY_OF_4_FLOATS[2]);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, VALID_ARRAY_OF_4_FLOATS[3]);
    
    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

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
        QBaseQuaternion qQuaternionUT(NULL_ARRAY);
    }
    catch(...) // TODO [Thund]: Only must catch the proper exception class, not implemented yet
    {
        bAssertionFailed = true;
    }
    
    // Verification
    BOOST_CHECK(bAssertionFailed);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if quaternion components are set to the correct values packed in a valid vf32 object.
/// </summary>
QTEST_CASE ( Constructor5_QuaternionComponentsAreSetToValidVF32PackedValues_Test )
{
    // Preparation
    const float_q EXPECTED_VALUE_FOR_X = SQFloat::_1;
    const float_q EXPECTED_VALUE_FOR_Y = SQFloat::_2;
    const float_q EXPECTED_VALUE_FOR_Z = SQFloat::_3;
    const float_q EXPECTED_VALUE_FOR_W = SQFloat::_4;
    
    vf32_q PACK;
    SQVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W, PACK);
    
    // Execution
    QBaseQuaternion qQuaternionUT(PACK);
    
    // Verification
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const QBaseQuaternion LEFT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0,SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const QBaseQuaternion LEFT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    
    // Execution / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // Preparation
    const QBaseQuaternion LEFT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // Preparation
    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon - SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
QTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // Preparation
    const float_q VALUE_FOR_LEFT_OPERAND_COMPONENTS = SQFloat::Epsilon + SQFloat::Epsilon * SQFloat::_0_5;
    const QBaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::_0, SQFloat::_0, SQFloat::_0, SQFloat::_0);
    
    // Execution / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
QTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // Preparation
    const QBaseQuaternion LEFT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    const QBaseQuaternion RIGHT_OPERAND(SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon, SQFloat::Epsilon);
    
    // Execution / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: QBaseQuaternion
QTEST_SUITE_END()
