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

#include "SQInteger.h"

using Kinesis::QuimeraEngine::Tools::DataTypes::SQInteger;
using Kinesis::QuimeraEngine::Tools::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::i16_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::i64_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Tools::DataTypes::u64_q;

typedef boost::mpl::list<i8_q, i16_q, i32_q, i64_q, u8_q, u16_q, u32_q, u64_q> TQTemplateTypes;
typedef boost::mpl::list<i8_q, i16_q, i32_q, i64_q> TQTemplateSignedTypes;
typedef boost::mpl::list<u8_q, u16_q, u32_q, u64_q> TQTemplateUnsignedTypes;

QTEST_SUITE_BEGIN( SQInteger_TestSuite )

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
QTEST_CASE ( Abs1_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i8_q INPUT = -50;
    const i8_q EXPECTED_RESULT = 50;

	// [Execution]
    i8_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
QTEST_CASE ( Abs1_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i8_q INPUT = SQInteger::MaxPositiveI8_Q;
    const i8_q EXPECTED_RESULT = SQInteger::MaxPositiveI8_Q;

	// [Execution]
    i8_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
QTEST_CASE ( Abs1_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i8_q INPUT = 0;
    const i8_q EXPECTED_RESULT = 0;

	// [Execution]
    i8_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
QTEST_CASE ( Abs1_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i8_q INPUT = SQInteger::MaxNegativeI8_Q;
    const i8_q EXPECTED_RESULT = INPUT;

	// [Execution]
    i8_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
QTEST_CASE ( Abs2_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i16_q INPUT = -50;
    const i16_q EXPECTED_RESULT = 50;

	// [Execution]
    i16_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
QTEST_CASE ( Abs2_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i16_q INPUT = SQInteger::MaxPositiveI16_Q;
    const i16_q EXPECTED_RESULT = SQInteger::MaxPositiveI16_Q;

	// [Execution]
    i16_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
QTEST_CASE ( Abs2_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i16_q INPUT = 0;
    const i16_q EXPECTED_RESULT = 0;

	// [Execution]
    i16_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
QTEST_CASE ( Abs2_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i16_q INPUT = SQInteger::MaxNegativeI16_Q;
    const i16_q EXPECTED_RESULT = INPUT;

	// [Execution]
    i16_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
QTEST_CASE ( Abs3_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i32_q INPUT = -50;
    const i32_q EXPECTED_RESULT = 50;

	// [Execution]
    i32_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
QTEST_CASE ( Abs3_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i32_q INPUT = SQInteger::MaxPositiveI32_Q;
    const i32_q EXPECTED_RESULT = SQInteger::MaxPositiveI32_Q;

	// [Execution]
    i32_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
QTEST_CASE ( Abs3_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i32_q INPUT = 0;
    const i32_q EXPECTED_RESULT = 0;

	// [Execution]
    i32_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
QTEST_CASE ( Abs3_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i32_q INPUT = SQInteger::MaxNegativeI32_Q;
    const i32_q EXPECTED_RESULT = INPUT;

	// [Execution]
    i32_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
QTEST_CASE ( Abs4_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i64_q INPUT = -50;
    const i64_q EXPECTED_RESULT = 50;

	// [Execution]
    i64_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
QTEST_CASE ( Abs4_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i64_q INPUT = SQInteger::MaxPositiveI64_Q;
    const i64_q EXPECTED_RESULT = SQInteger::MaxPositiveI64_Q;

	// [Execution]
    i64_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
QTEST_CASE ( Abs4_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i64_q INPUT = 0;
    const i64_q EXPECTED_RESULT = 0;

	// [Execution]
    i64_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
QTEST_CASE ( Abs4_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i64_q INPUT = SQInteger::MaxNegativeI64_Q;
    const i64_q EXPECTED_RESULT = INPUT;

	// [Execution]
    i64_q nResult = SQInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the bytes of the input value are correctly swapped when using a common value.
/// </summary>
QTEST_CASE_TEMPLATE ( SwapEndianess_IsCorrectlySwappedWhenUsingCommonValue_Test, TQTemplateTypes )
{
    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    T EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = (T)0xAB;
        EXPECTED_RESULT = INPUT;
        break;
    case SIZE_16:
        INPUT = (T)0xAABB;
        EXPECTED_RESULT = (T)0xBBAA;
        break;
    case SIZE_32:
        INPUT = (T)0xAABBCCDD;
        EXPECTED_RESULT =(T) 0xDDCCBBAA;
        break;
    case SIZE_64:
        INPUT = (T)0xAABBCCDDEEFF0011;
        EXPECTED_RESULT = (T)0x1100FFEEDDCCBBAA;
        break;
    default: // This will cause that the test fails
        INPUT = (T)0;
        EXPECTED_RESULT = (T)1;
    }

	// [Execution]
    T nResult = SQInteger::SwapEndianess(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the bytes of the input value are correctly swapped when using a common value.
/// </summary>
QTEST_CASE_TEMPLATE ( SwapEndianess_IsCorrectlySwappedWhenUsingZeroAsInput_Test, TQTemplateTypes )
{
    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    T EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = (T)0;
        EXPECTED_RESULT = INPUT;
        break;
    case SIZE_16:
        INPUT = (T)0;
        EXPECTED_RESULT = (T)0;
        break;
    case SIZE_32:
        INPUT = (T)0;
        EXPECTED_RESULT =(T) 0;
        break;
    case SIZE_64:
        INPUT = (T)0;
        EXPECTED_RESULT = (T)0;
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = -1;
    }

	// [Execution]
    T nResult = SQInteger::SwapEndianess(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the signed number is correctly converted to a string.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_SignedValueIsCorrectlyConverted_Test, TQTemplateSignedTypes )
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    string_q EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = SQInteger::MaxNegativeI8_Q;
        EXPECTED_RESULT = QE_L("-128");
        break;
    case SIZE_16:
        INPUT = SQInteger::MaxNegativeI16_Q;
        EXPECTED_RESULT = QE_L("-32768");
        break;
    case SIZE_32:
        INPUT = SQInteger::MaxNegativeI32_Q;
        EXPECTED_RESULT = QE_L("-2147483648");
        break;
    case SIZE_64:
        INPUT = SQInteger::MaxNegativeI64_Q;
        EXPECTED_RESULT = QE_L("-9223372036854775808");
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = -1;
    }

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the unsigned number is correctly converted to a string.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_UnsignedValueIsCorrectlyConverted_Test, TQTemplateUnsignedTypes )
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    string_q EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = SQInteger::MaxU8_Q;
        EXPECTED_RESULT = QE_L("255");
        break;
    case SIZE_16:
        INPUT = SQInteger::MaxU16_Q;
        EXPECTED_RESULT = QE_L("65535");
        break;
    case SIZE_32:
        INPUT = SQInteger::MaxU32_Q;
        EXPECTED_RESULT = QE_L("4294967295");
        break;
    case SIZE_64:
        INPUT = SQInteger::MaxU64_Q;
        EXPECTED_RESULT = QE_L("18446744073709551615");
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = -1;
    }

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that zero is correctly converted to a string.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ZeroIsCorrectlyConverted_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Tools::DataTypes::string_q;

    // [Preparation]
    T INPUT = 0;
    string_q EXPECTED_RESULT = QE_L("0");

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

// End - Test Suite: SQInteger
QTEST_SUITE_END()
