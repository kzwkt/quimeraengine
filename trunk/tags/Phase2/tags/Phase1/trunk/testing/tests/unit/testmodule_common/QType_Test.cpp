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

#include "QType.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QType;

QTEST_SUITE_BEGIN( QType_TestSuite )

/// <summary>
/// Checks that every argument is correctly set to the class attributes.
/// </summary>
QTEST_CASE ( Constructor_ValuesAreCorrectlySet_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    const string_q EXPECTED_NAME(QE_L("TYPE NAME"));

	// [Execution]
    QType type(EXPECTED_NAME);
    
    // [Verification]
    string_q strName = type.GetName();

    BOOST_CHECK(strName == EXPECTED_NAME);
}

/// <summary>
/// Checks that it returns True when instances are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME1"));
    const QType RIGHT_OPERAND(QE_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal, even if their attributes are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME1"));
    const QType RIGHT_OPERAND(QE_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal, even if their attributes are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const QType LEFT_OPERAND(QE_L("TYPE NAME"));
    const QType RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetName_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QType
QTEST_SUITE_END()
