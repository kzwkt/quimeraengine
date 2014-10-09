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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "SQAnyTypeToStringConverter.h"

#include "QType.h"
#include "EQComparisonType.h"
#include "QDerivedFromObject.h"

using Kinesis::QuimeraEngine::Common::DataTypes::SQAnyTypeToStringConverter;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
using Kinesis::QuimeraEngine::Core::QObject;
using Kinesis::QuimeraEngine::Common::DataTypes::QType;
using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
using Kinesis::QuimeraEngine::Common::DataTypes::Test::QDerivedFromObject;

// This struct is used as example of "unknown type", not a QObject, not a basic type, not a string_q.
struct UnknownType
{
};
    
    
QTEST_SUITE_BEGIN( SQAnyTypeToStringConverter_TestSuite )
    
/// <summary>
/// Checks that the object is correctly converted to string when using bool.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingBool_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "true";
    const bool OBJECT = true;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "255";
    const u8_q OBJECT = 255;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "65535";
    const u16_q OBJECT = 65535;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "123456789";
    const u32_q OBJECT = 123456789U;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "12345678912345678912";
    const u64_q OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "-128";
    const i8_q OBJECT = -128;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "-32768";
    const i16_q OBJECT = -32768;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "-214748364";
    const i32_q OBJECT = -214748364;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "-9223372036854775807";
    const i64_q OBJECT = -9223372036854775807;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using floating point numbers of 32 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingF32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "1234.54004";
    const f32_q OBJECT = 1234.54f;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using floating point numbers of 64 bits.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingF64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "12345678.90123";
    const f64_q OBJECT = 12345678.90123;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using strings.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "STRING";
    const string_q OBJECT = "STRING";

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using non-basic data types.
/// </summary>
QTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    bool bContainsExpectedText = strResult.Contains(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bContainsExpectedText);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to bool.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToBool_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " true";
    bool OBJECT = true;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 255";
    u8_q OBJECT = 255;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 65535";
    u16_q OBJECT = 65535;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 123456789";
    u32_q OBJECT = 123456789U;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678912345678912";
    u64_q OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -128";
    i8_q OBJECT = -128;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -32768";
    i16_q OBJECT = -32768;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -214748364";
    i32_q OBJECT = -214748364;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -9223372036854775807";
    i64_q OBJECT = -9223372036854775807;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 32 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "1234.54004";
    f32_q OBJECT = 1234.54f;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 64 bits.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678.90123";
    f64_q OBJECT = 12345678.90123;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to strings.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " STRING";
    string_q OBJECT = "STRING";

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to non-basic data types.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Unknown type at 0x";
    UnknownType OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.Contains(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    QObject* pObject = new QDerivedFromObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);

    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to class derived from QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    QDerivedFromObject* pObject = new QDerivedFromObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a basic data type.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    f64_q* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to string.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    string_q* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to non-basic data type.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    UnknownType* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    QObject* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a class derived from QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    QDerivedFromObject* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to a basic data type.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678.90123";
    f64_q OBJECT = 12345678.90123;
    f64_q* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to strings.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " STRING";
    string_q OBJECT = "STRING";
    string_q* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to non-basic data types.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Unknown type at 0x";
    UnknownType OBJECT;
    UnknownType* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.Contains(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    QObject* pObject = new QDerivedFromObject;
    QObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to class derived from QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    QDerivedFromObject* pObject = new QDerivedFromObject;
    QDerivedFromObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a basic data type.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    f64_q* pObject = null_q;
    f64_q** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with <Null>
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to string.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    string_q* pObject = null_q;
    string_q** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to non-basic data type.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    UnknownType* pObject = null_q;
    UnknownType** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    QObject* pObject = null_q;
    QObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a class derived from QObject.
/// </summary>
QTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    QDerivedFromObject* pObject = null_q;
    QDerivedFromObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to bool.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToBool_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " true";
    const bool OBJECT = true;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 255";
    const u8_q OBJECT = 255;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 65535";
    const u16_q OBJECT = 65535;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 123456789";
    const u32_q OBJECT = 123456789U;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678912345678912";
    const u64_q OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 8 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI8_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -128";
    const i8_q OBJECT = -128;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 16 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI16_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -32768";
    const i16_q OBJECT = -32768;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 32 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -214748364";
    const i32_q OBJECT = -214748364;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 64 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " -9223372036854775807";
    const i64_q OBJECT = -9223372036854775807;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 32 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF32_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "1234.54004";
    const f32_q OBJECT = 1234.54f;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 64 bits.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF64_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678.90123";
    const f64_q OBJECT = 12345678.90123;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to strings.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " STRING";
    const string_q OBJECT = "STRING";

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to non-basic data types.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    const QObject* pObject = new QDerivedFromObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to class derived from QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    const QDerivedFromObject* pObject = new QDerivedFromObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a basic data type.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    const f64_q* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to string.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    const string_q* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to non-basic data type.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    const UnknownType* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    const QObject* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a class derived from QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = "<Null>";
    const QDerivedFromObject* pObject = null_q;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to a basic data type.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " 12345678.90123";
    const f64_q OBJECT = 12345678.90123;
    const f64_q* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to strings.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " STRING";
    const string_q OBJECT = "STRING";
    const string_q* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to non-basic data types.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();
    const UnknownType* pObject = &OBJECT;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.Contains(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    const QObject* pObject = new QDerivedFromObject;
    const QObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to class derived from QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " QDerivedFromObject";
    const QDerivedFromObject* pObject = new QDerivedFromObject;
    const QDerivedFromObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive, 1U) != string_q::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
    
    // [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a basic data type.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    const f64_q* pObject = null_q;
    const f64_q** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with <Null>
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to string.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToString_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    const string_q* pObject = null_q;
    const string_q** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to non-basic data type.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    const UnknownType* pObject = null_q;
    const UnknownType** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    const QObject* pObject = null_q;
    const QObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a class derived from QObject.
/// </summary>
QTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToClassDerivedFromQObject_Test )
{
    // [Preparation]
    const string_q EXPECTED_RESULT = " <Null>";
    const QDerivedFromObject* pObject = null_q;
    const QDerivedFromObject** ppObject = &pObject;

    // [Execution]
    string_q strResult = SQAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_q("0x"), EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EQComparisonType::E_BinaryCaseSensitive) != string_q::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

// End - Test Suite: SQAnyTypeToStringConverter
QTEST_SUITE_END()
