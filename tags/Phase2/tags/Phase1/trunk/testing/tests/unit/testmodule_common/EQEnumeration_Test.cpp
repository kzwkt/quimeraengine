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

#include "EQEnumerationMock.h"

using namespace Kinesis::QuimeraEngine::Common::DataTypes;
using Kinesis::QuimeraEngine::Test::EQEnumerationMock;


QTEST_SUITE_BEGIN( EQEnumerationMock_TestSuite )

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
QTEST_CASE ( Constructor1_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EQEnumerationMock::EnumType EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input integer value is correctly converted to the corresponding enumeration value.
/// </summary>
QTEST_CASE ( Constructor2_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;
    const enum_int_q INPUT_VALUE = 1;

	// [Execution]
    EQEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration value is undefined when the input integer value doesn't correspondo to a valid value.
/// </summary>
QTEST_CASE ( Constructor2_EnumGetsUndefinedValueWhenInvalidInputValueIsSet_Test )
{
    // [Preparation]
    const std::vector<EQEnumerationMock::EnumType> VALID_VALUES = EQEnumerationMock::GetValues();
    const enum_int_q INPUT_VALUE = EQEnumerationMock::_NotEnumValue - 1;

	// [Execution]
    EQEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    for(size_t i = 0; i < VALID_VALUES.size(); ++i)
    {
        BOOST_CHECK(eEnumeration != VALID_VALUES[i]);
    }
}

/// <summary>
/// Checks that the input string value is correctly converted to the corresponding enumeration value.
/// </summary>
QTEST_CASE ( Constructor3_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const string_q INPUT_VALUE = QE_L("Value2");
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is set to an undefined value when the input value name doesn't match any of the valid values available.
/// </summary>
QTEST_CASE ( Constructor3_NotEnumValueIsSetWhenTheNameDoesNotMatchValidEnumValue_Test )
{
    // [Preparation]
    const string_q INPUT_VALUE = QE_L("-");
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::_NotEnumValue;

	// [Execution]
    EQEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
QTEST_CASE ( Constructor4_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input integer value is correctly converted to the corresponding enumeration value.
/// </summary>
QTEST_CASE ( OperatorAssignation1_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;
    const enum_int_q INPUT_VALUE = 1;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration value is undefined when the input integer value doesn't correspondo to a valid value.
/// </summary>
QTEST_CASE ( OperatorAssignation1_EnumGetsUndefinedValueWhenInvalidInputValueIsSet_Test )
{
    // [Preparation]
    const std::vector<EQEnumerationMock::EnumType> VALID_VALUES = EQEnumerationMock::GetValues();
    const enum_int_q INPUT_VALUE = EQEnumerationMock::_NotEnumValue - 1;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    for(size_t i = 0; i < VALID_VALUES.size(); ++i)
    {
        BOOST_CHECK(eEnumeration != VALID_VALUES[i]);
    }
}

/// <summary>
/// Checks that the input string value is correctly converted to the corresponding enumeration value.
/// </summary>
QTEST_CASE ( OperatorAssignation2_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const string_q INPUT_VALUE = QE_L("Value2");
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is set to an undefined value when the input value name doesn't match any of the valid values available.
/// </summary>
QTEST_CASE ( OperatorAssignation2_NotEnumValueIsSetWhenTheNameDoesNotMatchValidEnumValue_Test )
{
    // [Preparation]
    const string_q INPUT_VALUE = QE_L("-");
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::_NotEnumValue;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
QTEST_CASE ( OperatorAssignation3_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EQEnumerationMock::EnumType EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
QTEST_CASE ( OperatorAssignation4_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EQEnumerationMock EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock eEnumeration(EQEnumerationMock::E_Value1);
    eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
QTEST_CASE ( OperatorEquality1_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value2;
    const EQEnumerationMock OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality1_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value1;
    const EQEnumerationMock OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
QTEST_CASE ( OperatorEquality2_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value2;
    const string_q OPERAND2 = QE_L("Value2");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality2_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value1;
    const string_q OPERAND2 = QE_L("Value2");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
QTEST_CASE ( OperatorEquality3_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value2;
    const enum_int_q OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality3_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value1;
    const enum_int_q OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
QTEST_CASE ( OperatorEquality4_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value2;
    const EQEnumerationMock::EnumType OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality4_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EQEnumerationMock OPERAND1 = EQEnumerationMock::E_Value1;
    const EQEnumerationMock::EnumType OPERAND2 = EQEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned values match what expected.
/// </summary>
QTEST_CASE ( GetValues_ReturnsAllTheValues_Test )
{
    // [Preparation]
    std::vector<EQEnumerationMock::EnumType> EXPECTED_RESULT;
    EXPECTED_RESULT.push_back(EQEnumerationMock::E_Value1);
    EXPECTED_RESULT.push_back(EQEnumerationMock::E_Value2);
    EXPECTED_RESULT.push_back(EQEnumerationMock::E_Value3);

	// [Execution]
    const std::vector<EQEnumerationMock::EnumType> arResult = EQEnumerationMock::GetValues();

    // [Verification]
    BOOST_CHECK_EQUAL(arResult.size(), EXPECTED_RESULT.size());

    std::vector<EQEnumerationMock::EnumType>::const_iterator iResult = arResult.begin();
    std::vector<EQEnumerationMock::EnumType>::const_iterator iExpected = EXPECTED_RESULT.begin();

    for(; iExpected != EXPECTED_RESULT.end(); ++iResult, ++iExpected)
    {
        BOOST_CHECK_EQUAL(*iResult, *iExpected);
    }
}

/// <summary>
/// Checks that the _NotEnumValue value is not included in the list.
/// </summary>
QTEST_CASE ( GetValues_DoesNotIncludeNotEnumValue_Test )
{
    // [Preparation]
    const EQEnumerationMock::EnumType NOT_INCLUDED_VALUE = EQEnumerationMock::_NotEnumValue;

	// [Execution]
    const std::vector<EQEnumerationMock::EnumType> arResult = EQEnumerationMock::GetValues();

    // [Verification]
    std::vector<EQEnumerationMock::EnumType>::const_iterator iResult = arResult.begin();

    for(; iResult != arResult.end(); ++iResult)
    {
        BOOST_CHECK_NE(*iResult, NOT_INCLUDED_VALUE);
    }
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
QTEST_CASE ( CastToEnumType_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::E_Value2;
    const EQEnumerationMock::EnumType EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    EQEnumerationMock::EnumType eConvertedValue = ORIGINAL_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(eConvertedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
QTEST_CASE ( ToInteger_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::E_Value2;
    const enum_int_q EXPECTED_VALUE = EQEnumerationMock::E_Value2;

	// [Execution]
    enum_int_q nConvertedValue = ORIGINAL_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(nConvertedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
QTEST_CASE ( CastToString_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::E_Value2;
    const string_q EXPECTED_VALUE = QE_L("Value2");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE;

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an empty string is returned when the enumeration value is _NotEnumValue.
/// </summary>
QTEST_CASE ( CastToString_ReturnsEmptyStringWhenEnumerationIsNotEnumValue_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::_NotEnumValue;
    const string_q EXPECTED_VALUE = QE_L("");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an empty string is returned when the enumeration value is not valid.
/// </summary>
QTEST_CASE ( CastToString_ReturnsEmptyStringWhenEnumerationIsNotValid_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::_NotEnumValue - 1;
    const string_q EXPECTED_VALUE = QE_L("");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
QTEST_CASE ( ToString_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::E_Value2;
    const string_q EXPECTED_VALUE = QE_L("Value2");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an empty string is returned when the enumeration value is _NotEnumValue.
/// </summary>
QTEST_CASE ( ToString_ReturnsEmptyStringWhenEnumerationIsNotEnumValue_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::_NotEnumValue;
    const string_q EXPECTED_VALUE = QE_L("");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that an empty string is returned when the enumeration value is not valid.
/// </summary>
QTEST_CASE ( ToString_ReturnsEmptyStringWhenEnumerationIsNotValid_Test )
{
    // [Preparation]
    const EQEnumerationMock ORIGINAL_VALUE = EQEnumerationMock::_NotEnumValue - 1;
    const string_q EXPECTED_VALUE = QE_L("");

	// [Execution]
    string_q strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

// End - Test Suite: EQEnumerationMock
QTEST_SUITE_END()
