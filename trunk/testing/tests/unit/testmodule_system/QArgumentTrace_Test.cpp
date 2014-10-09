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

#include "QArgumentTrace.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;

#include "QDerivedFromObject.h"
#include "EQComparisonType.h"

using Kinesis::QuimeraEngine::Common::DataTypes::Test::QDerivedFromObject;
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
using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
using Kinesis::QuimeraEngine::Core::QObject;
using Kinesis::QuimeraEngine::Common::DataTypes::QType;

// This struct is used as example of "custom type", not a QObject, not a basic type, not a string_q.
struct CustomType
{
    i32_q i;
};


QTEST_SUITE_BEGIN( QArgumentTrace_TestSuite )

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("u8");
    const string_q EXPECTED_VALUE("123");
    u8_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("u16");
    const string_q EXPECTED_VALUE("123");
    u16_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("u32");
    const string_q EXPECTED_VALUE("123");
    u32_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("u64");
    const string_q EXPECTED_VALUE("123");
    u64_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("i8");
    const string_q EXPECTED_VALUE("123");
    i8_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("i16");
    const string_q EXPECTED_VALUE("123");
    i16_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("i32");
    const string_q EXPECTED_VALUE("123");
    i32_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("i64");
    const string_q EXPECTED_VALUE("123");
    i64_q object = 123;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("f32");
    const string_q EXPECTED_VALUE("123.456001");
    f32_q object = 123.456f;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("f64");
    const string_q EXPECTED_VALUE("123.456");
    f64_q object = 123.456;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("bool");
    const string_q EXPECTED_VALUE("true");
    bool object = true;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_q.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    // [Preparation]
    const string_q EXPECTED_NAME("string");
    const string_q EXPECTED_VALUE("text");
    string_q object = "text";

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
QTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("<Unknown type (size:");
    const string_q EXPECTED_VALUE("<Unknown type at 0x");
    CustomType object;

    // [Execution]
    QArgumentTrace trace(object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME, EQComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("u8*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    u8_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("u16*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    u16_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("u32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    u32_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("u64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    u64_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("i8*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    i8_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("i16*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    i16_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("i32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    i32_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("i64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    i64_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("f32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123.456001");
    f32_q object = 123.456f;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("f64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123.456");
    f64_q object = 123.456;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("bool*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("true");
    bool object = true;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_q.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("string*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("text");
    string_q object = "text";

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME1("<Unknown type (size:");
    const string_q EXPECTED_NAME2(">*");
    const string_q EXPECTED_VALUE("<Unknown type at 0x");

    CustomType object;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME1, EQComparisonType::E_BinaryCaseSensitive) &&
                                         strTypeName.Contains(EXPECTED_NAME2, EQComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to class derived from QObject.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingNullClassDerivedFromQObject_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("QObject*");
    const string_q EXPECTED_VALUE("<Null>");

    QObject* pObject = null_q;

    // [Execution]
    QArgumentTrace trace(pObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to a basic type.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingNullPointerToBasicType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("bool*");
    const string_q EXPECTED_VALUE("<Null>");
    bool* pObject = null_q;

    // [Execution]
    QArgumentTrace trace(pObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using pointer to pointer to a basic type.
/// </summary>
QTEST_CASE ( Constructor2_TypeNameAndValueAreStoredWhenUsingPointerToPointerToBasicType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("bool**");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("true");
    bool object = true;
    bool* pObject = &object;
    bool** ppObject = &pObject;

    // [Execution]
    QArgumentTrace trace(ppObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive, 1) != string_q::PATTERN_NOT_FOUND &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const u8*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const u8_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const u16*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const u16_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const u32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const u32_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const u64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const u64_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const i8*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const i8_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const i16*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const i16_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const i32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const i32_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const i64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123");
    const i64_q object = 123;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const f32*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123.456001");
    const f32_q object = 123.456f;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const f64*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("123.456");
    const f64_q object = 123.456;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const bool*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("true");
    const bool object = true;

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_q.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const string*");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("text");
    const string_q object = "text";

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME1("const <Unknown type (size:");
    const string_q EXPECTED_NAME2(">*");
    const string_q EXPECTED_VALUE("<Unknown type at 0x");

    const CustomType object = CustomType();

    // [Execution]
    QArgumentTrace trace(&object);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME1, EQComparisonType::E_BinaryCaseSensitive) &&
                                         strTypeName.Contains(EXPECTED_NAME2, EQComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to class derived from QObject.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingNullClassDerivedFromQObject_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const QObject*");
    const string_q EXPECTED_VALUE("<Null>");

    const QObject* pObject = null_q;

    // [Execution]
    QArgumentTrace trace(pObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to a basic type.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingNullPointerToBasicType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const bool*");
    const string_q EXPECTED_VALUE("<Null>");
    const bool* pObject = null_q;

    // [Execution]
    QArgumentTrace trace(pObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using pointer to pointer to a basic type.
/// </summary>
QTEST_CASE ( Constructor3_TypeNameAndValueAreStoredWhenUsingPointerToPointerToBasicType_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const string_q EXPECTED_NAME("const bool**");
    const string_q EXPECTED_VALUE1("0x");
    const string_q EXPECTED_VALUE2("true");
    const bool object = true;
    const bool* pObject = &object;
    const bool** ppObject = &pObject;

    // [Execution]
    QArgumentTrace trace(ppObject);

    // [Verification]
    string_q strTypeName = trace.GetTypeName();
    string_q strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.IndexOf(EXPECTED_VALUE1, EQComparisonType::E_BinaryCaseSensitive, 1) != string_q::PATTERN_NOT_FOUND &&
                                      strValue.Contains(EXPECTED_VALUE2, EQComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetTypeName_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetValue_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}


// End - Test Suite: QArgumentTrace
QTEST_SUITE_END()
