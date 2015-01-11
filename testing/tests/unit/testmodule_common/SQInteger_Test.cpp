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

using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

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
#ifdef QE_COMPILER_MSVC
    // This silents the warning caused by the switch structure below due to a type overflow, which is known and deliberated
    #pragma warning( push )
    #pragma warning( disable : 4244)
#endif

    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

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
        EXPECTED_RESULT = "";
    }

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);

#ifdef QE_COMPILER_MSVC
    #pragma warning( pop )
#endif
}

/// <summary>
/// Checks that the unsigned number is correctly converted to a string.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_UnsignedValueIsCorrectlyConverted_Test, TQTemplateUnsignedTypes )
{
#ifdef QE_COMPILER_MSVC
    // This silents the warning caused by the switch structure below due to a type overflow, which is known and deliberated
    #pragma warning( push )
    #pragma warning( disable : 4244)
#endif

    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

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
        EXPECTED_RESULT = "";
    }

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);

#ifdef QE_COMPILER_MSVC
    #pragma warning( pop )
#endif

}

/// <summary>
/// Checks that zero is correctly converted to a string.
/// </summary>
QTEST_CASE_TEMPLATE ( ToString_ZeroIsCorrectlyConverted_Test, TQTemplateTypes )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    T INPUT = 0;
    string_q EXPECTED_RESULT = QE_L("0");

	// [Execution]
    string_q strResult = SQInteger::ToString(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the length of the string depends on the size of the integer type when the value is zero.
/// </summary>
QTEST_CASE_TEMPLATE ( ToStringHexadecimal_TheLengthOfStringDependsOnTypeSizeWhenValueIsZero_Test, TQTemplateUnsignedTypes )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;

    // [Preparation]
    T INPUT = 0;
    pointer_uint_q EXPECTED_LENGTH = sizeof(T) * 2U; // 2 letters per byte

	// [Execution]
    string_q strResult = SQInteger::ToStringHexadecimal(INPUT);

    // [Verification]
    pointer_uint_q uLength = strResult.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns the expected string when using 1 byte.
/// </summary>
QTEST_CASE ( ToStringHexadecimal_ItReturnsExpectedValueWhenUsingOneByte_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    u8_q INPUT = 0x0F;
    string_q EXPECTED_STRING = "0F";

	// [Execution]
    string_q strResult = SQInteger::ToStringHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 2 bytes.
/// </summary>
QTEST_CASE ( ToStringHexadecimal_ItReturnsExpectedValueWhenUsingTwoBytes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    u16_q INPUT = 0x01EF;
    string_q EXPECTED_STRING = "01EF";

	// [Execution]
    string_q strResult = SQInteger::ToStringHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 4 bytes.
/// </summary>
QTEST_CASE ( ToStringHexadecimal_ItReturnsExpectedValueWhenUsingFourBytes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    u32_q INPUT = 0x0123CDEF;
    string_q EXPECTED_STRING = "0123CDEF";

	// [Execution]
    string_q strResult = SQInteger::ToStringHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 8 bytes.
/// </summary>
QTEST_CASE ( ToStringHexadecimal_ItReturnsExpectedValueWhenUsingEightBytes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::string_q;

    // [Preparation]
    u64_q INPUT = 0x0123456789ABCDEF;
    string_q EXPECTED_STRING = "0123456789ABCDEF";

	// [Execution]
    string_q strResult = SQInteger::ToStringHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that a common hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( FromHexadecimalString_CreatesIntegerFromCommonHexadecimalValue_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "6AC5FF01";
    const u32_q EXPECTED_VALUE = 0x6AC5FF01;
    u32_q uResult = 0;

    // [Execution]
    uResult = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a zero hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( FromHexadecimalString_CreatesIntegerFromHexadecimalValueWhenItEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "00000000";
    const u32_q EXPECTED_VALUE = 0;
    u32_q uResult = 0;

    // [Execution]
    uResult = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a maximum hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( FromHexadecimalString_CreatesIntegerFromHexadecimalValueWhenItEqualsMaximum_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "FFFFFFFF";
    const u32_q EXPECTED_VALUE = 0xFFFFFFFF;
    u32_q uResult = 0;

    // [Execution]
    uResult = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a 0x-prefixed hexadecimal value is correctly converted to an integer.
/// </summary>
QTEST_CASE ( FromHexadecimalString_CreatesIntegerFromHexadecimalValueWhenItHas0xPrefix_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "0xFFFFFFFF";
    const u32_q EXPECTED_VALUE = 0xFFFFFFFF;
    u32_q uResult = 0;

    // [Execution]
    uResult = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the 0x prefix is case insensitive.
/// </summary>
QTEST_CASE ( FromHexadecimalString_ThePrefixIsCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING_LOWER_CASE = "0xFFFFFFFF";
    const string_q INPUT_STRING_UPPER_CASE = "0XFFFFFFFF";
    u32_q uResultLowerCase = 0;
    u32_q uResultUpperCase = 0;

    // [Execution]
    uResultLowerCase = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING_LOWER_CASE);
    uResultUpperCase = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING_UPPER_CASE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResultLowerCase, uResultUpperCase);
}

/// <summary>
/// Checks that it can create integers of different sizes.
/// </summary>
QTEST_CASE ( FromHexadecimalString_CreatesIntegersOfDifferentSizes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    // [Preparation]
    const string_q INPUT_STRING_8BITS  = "2A";
    const string_q INPUT_STRING_16BITS = "6AC5";
    const string_q INPUT_STRING_32BITS = "6AC5FF01";
    const string_q INPUT_STRING_64BITS = "6AC5FF016AC5FF01";
    const u8_q  EXPECTED_VALUE_8BITS  = 0x2AU;
    const u16_q EXPECTED_VALUE_16BITS = 0x6AC5U;
    const u32_q EXPECTED_VALUE_32BITS = 0x6AC5FF01U;
    const u64_q EXPECTED_VALUE_64BITS = 0x6AC5FF016AC5FF01ULL;
    u8_q  uResult8Bits  = 0;
    u16_q uResult16Bits = 0;
    u32_q uResult32Bits = 0;
    u64_q uResult64Bits = 0;

    // [Execution]
    uResult8Bits = SQInteger::FromHexadecimalString<u8_q>(INPUT_STRING_8BITS);
    uResult16Bits = SQInteger::FromHexadecimalString<u16_q>(INPUT_STRING_16BITS);
    uResult32Bits = SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING_32BITS);
    uResult64Bits = SQInteger::FromHexadecimalString<u64_q>(INPUT_STRING_64BITS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult8Bits,  EXPECTED_VALUE_8BITS);
    BOOST_CHECK_EQUAL(uResult16Bits, EXPECTED_VALUE_16BITS);
    BOOST_CHECK_EQUAL(uResult32Bits, EXPECTED_VALUE_32BITS);
    BOOST_CHECK_EQUAL(uResult64Bits, EXPECTED_VALUE_64BITS);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when string's length is greater than the integer type's size.
/// </summary>
QTEST_CASE ( FromHexadecimalString_AssertionFailsWhenInputStringLengthIsGreaterThanntegerSize_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;

    // [Preparation]
    const string_q INPUT_STRING = "A45FA45FA45FA45F";
    const bool ASSERTION_FAILED = true;
    u32_q uResult32Bits = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        SQInteger::FromHexadecimalString<u32_q>(INPUT_STRING);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif


// End - Test Suite: SQInteger
QTEST_SUITE_END()
