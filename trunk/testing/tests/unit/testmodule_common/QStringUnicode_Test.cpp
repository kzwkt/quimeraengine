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

#include "QStringUnicode.h"
#include "SQInteger.h"

#include "CommonTestDefinitions.h"
#include "UnicodeNormalizationTestData.h"
#include "EQTextEncoding.h"
#include "EQComparisonType.h"
#include "EQNormalizationForm.h"
#include "AllocationOperators.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::DataTypes::QStringUnicode;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;


QTEST_SUITE_BEGIN( QStringUnicode_TestSuite )

/// <summary>
/// This method checks if two byte arrays are exactly equal, byte to byte, same length
/// </summary>
/// <param name="pArrayA">[IN] A byte array.</param>
/// <param name="uSizeArrayA">[IN] The length of the byte array.</param>
/// <param name="pArrayB">[IN] A different byte array.</param>
/// <param name="uSizeArrayB">[IN] The length of the second byte array.</param>
/// <returns>
/// True if byte arrays are equal; False otherwise.
/// </returns>
bool CheckByteArraysAreEqual_UtilityMethod(const i8_q* pArrayA, const unsigned int uSizeArrayA, const i8_q* pArrayB, const unsigned int uSizeArrayB)
{
    bool bAreEqual = true;

    if(pArrayA == pArrayB || uSizeArrayA == 0 || uSizeArrayB == 0 || pArrayA == null_q || pArrayB == null_q || uSizeArrayA != uSizeArrayB)
    {
        bAreEqual = false;
    }
    else
    {
        unsigned int i = 0;

        while(i < uSizeArrayA && pArrayA[i] == pArrayB[i])
            ++i;

        bAreEqual = i == uSizeArrayA;
    }

    return bAreEqual;
}

/// <summary>
/// Checks that the default constructor creates an empty string.
/// </summary>
QTEST_CASE ( Constructor1_DefaultConstructorCreatesEmptyString_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT = QStringUnicode::GetEmpty();

	// [Execution]
    QStringUnicode strString;

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the copy of a string is equal to the original.
/// </summary>
QTEST_CASE ( Constructor2_CopiedStringIsEqualToOriginal_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode strString(EXPECTED_RESULT);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor3_Iso88591StringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };

    //
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input is null-termination.
/// </summary>
QTEST_CASE ( Constructor3_CreatesEmptyStringWhenInputIsNullTermination_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[] = { 0 };
    const QStringUnicode EXPECTED_RESULT = QStringUnicode::GetEmpty();

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const i8_q* INPUT_STRING_BYTES = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QStringUnicode strString(INPUT_STRING_BYTES);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor4_Iso88591StringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);

    //
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input length equals zero.
/// </summary>
QTEST_CASE ( Constructor4_CreatesEmptyStringWhenInputLengthEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const QStringUnicode EXPECTED_RESULT = QStringUnicode::GetEmpty();
    const int ZERO_LENGTH = 0;

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, ZERO_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the string is correctly built when the length is unknown and using a null-terminated input string.
/// </summary>
QTEST_CASE ( Constructor4_StringIsCorrectlyBuiltWhenInputLengthIsUnknown_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const int UNKNOWN_LENGTH = QStringUnicode::LENGTH_NULL_TERMINATED;

    //                                             ñ       B       á
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, UNKNOWN_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ASCII, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor5_AsciiStringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                            ' '      B       _       \0
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor5_Iso88591StringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_ISO88591;

    //
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-8, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor5_Utf8StringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                         ©                       ?                                   ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Little Endian.
/// </summary>
QTEST_CASE ( Constructor5_Utf16StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM LE                  ©              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Big Endian.
/// </summary>
QTEST_CASE ( Constructor5_Utf16StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is treated as if it was Big Endian when there is no BOM.
/// </summary>
QTEST_CASE ( Constructor5_Utf16StringIsTreatedAsBigEndianWhenNoBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                            BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding EXPECTED_ENCODING    = EQTextEncoding::E_UTF16;
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_BYTES, const i8_q*), EXPECTED_STRING_LENGTH, EXPECTED_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is correctly converted when BOM indicates Little Endian.
/// </summary>
QTEST_CASE ( Constructor5_Utf32StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         BOM LE                        ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is correctly converted when BOM indicates Big Endian.
/// </summary>
QTEST_CASE ( Constructor5_Utf32StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         ©                    ?                             ?                             ?                            \0
    //                                         BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is treated as if it was Big Endian when there is no BOM.
/// </summary>
QTEST_CASE ( Constructor5_Utf32StringIsTreatedAsBigEndianWhenNoBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                            BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding EXPECTED_ENCODING    = EQTextEncoding::E_UTF32;
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_BYTES, const i8_q*), EXPECTED_STRING_LENGTH, EXPECTED_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16 Big Endian, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor5_Utf16BEStringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16BE;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16 Little Endian, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor5_Utf16LEStringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16LE;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-16 encoding.
/// </summary>
QTEST_CASE ( Constructor5_BOMIsRemovedFromStringWhenUsingUtf16Encoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    static QCharUnicode CHAR_BOM_LE = 0xFFFE;
    //                                        BOM     ©       ?       ?       ?      \0
    const u16_q INPUT_STRING_CODE_UNITS[] = { 0xFFFE, 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != CHAR_BOM_LE);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-32 encoding.
/// </summary>
QTEST_CASE ( Constructor5_BOMIsRemovedFromStringWhenUsingUtf32Encoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    static QCharUnicode CHAR_BOM_LE = 0xFFFE;
    //                                        BOM         ©           ?           ?           ?          \0
    const u32_q INPUT_STRING_CODE_UNITS[] = { 0x0000FEFF, 0x000000A9, 0x000016A1, 0x00000634, 0x00000416, 0x00000000 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != CHAR_BOM_LE);
}

/// <summary>
/// Checks that ill-formed sequences are repaired, replacing the wrong characters by U+FFFD REPLACEMENT CHARACTER, when passing Utf8 string.
/// </summary>
QTEST_CASE ( Constructor5_IllFormedSequencesAreRepairedUsingReplacementCharacterWhenUsingUtf8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                         A           ILL-FORMED  ñ                       B          \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0x41, (char)0xC2, (char)0xC3, (char)0xB1, (char)0x42, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           A       REPLAC. ñ       B      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x0041, 0xFFFD, 0x00F1, 0x0042, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the values of the optional parameters are ISO 8859-1 encoding and Null-terminated length, when no arguments are passed.
/// </summary>
QTEST_CASE ( Constructor5_OptionalParametersDefaultToNullTerminatedIso88591_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };

    //                                             ñ       B       á
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input length equals zero.
/// </summary>
QTEST_CASE ( Constructor5_CreatesEmptyStringWhenInputLengthEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const QStringUnicode EXPECTED_RESULT = QStringUnicode::GetEmpty();
    const int ZERO_LENGTH = 0;
    const EQTextEncoding ENCODING = EQTextEncoding::E_ISO88591;

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, ZERO_LENGTH, ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when an incorrect combination of parameter values is passed.
/// </summary>
QTEST_CASE ( Constructor5_AssertionFailsWhenUsingIncorrectParameterValueCombination_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[] = { 'a', 'b', 'c', 0 };
    const int INVALID_LENGTH = QStringUnicode::LENGTH_NULL_TERMINATED;
    const EQTextEncoding INVALID_ENCODING = EQTextEncoding::E_UTF8;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QStringUnicode strString(INPUT_STRING_BYTES, INVALID_LENGTH, INVALID_ENCODING);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the string is correctly built when the length is unknown and using a null-terminated input string.
/// </summary>
QTEST_CASE ( Constructor5_StringIsCorrectlyBuiltWhenInputLengthIsUnknown_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_q INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const int UNKNOWN_LENGTH = QStringUnicode::LENGTH_NULL_TERMINATED;
    const EQTextEncoding ENCODING = EQTextEncoding::E_ISO88591;

    //                                             ñ       B       á
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, UNKNOWN_LENGTH, ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the resultant string contains the input character.
/// </summary>
QTEST_CASE ( Constructor6_ResultContainsInputCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QCharUnicode INPUT_CHARACTER(0x1234);
    const u16_q EXPECTED_STRING_BYTES[] = { scast_q(INPUT_CHARACTER.GetCodePoint(), u16_q) };
    const QStringUnicode EXPECTED_RESULT = QStringUnicode(rcast_q(EXPECTED_STRING_BYTES, const i8_q*), sizeof(EXPECTED_STRING_BYTES), string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(INPUT_CHARACTER);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in either UTF16 or UTF32 depending on the OS and the compiler, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor7_CommonSequenceIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const wchar_t INPUT_STRING_BYTES[] = { 'A', 'B', 'C', 0 };
    const unsigned int EXPECTED_LENGTH = 3;

    //
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x0041, 0x0042, 0x0043 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    unsigned int uLength = strString.GetLength();
    BOOST_CHECK(strString == EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it creates an empty string when the input is null-termination.
/// </summary>
QTEST_CASE ( Constructor7_CreatesEmptyStringWhenInputIsNullTermination_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const wchar_t INPUT_STRING_BYTES[] = { 0 };
    const QStringUnicode EXPECTED_RESULT = QStringUnicode::GetEmpty();

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
QTEST_CASE ( Constructor7_AssertionFailsWhenInputIsNull_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const wchar_t* INPUT_STRING_BYTES = null_q;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QStringUnicode strString(INPUT_STRING_BYTES);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the assigned string is equal to the copied string.
/// </summary>
QTEST_CASE ( OperatorAssignment_CopiedStringIsEqualToOriginal_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    QStringUnicode strString;
    strString = EXPECTED_RESULT;

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are exactly the same.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("ABCDE");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are not the same.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenStringsAreNotEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equivalent but not exactly the same.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenStringsAreEquivalentButNotTheSame_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are exactly the same.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("ABCDE");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are not the same.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenStringsAreNotEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenStringsAreEquivalentButNotTheSame_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 < STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputStringIsLower_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 < STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equal.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 < STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsGreater_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 <= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputStringIsLower_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equal.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsGreater_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputStringIsLower_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 > STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 > STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equal.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 > STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsLower_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 > STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputStringIsLower_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 >= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is greater than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 >= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equal.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABCDE");
    const QStringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 >= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is lower than resident string.
/// </summary>
QTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsLower_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*), 2, string_q::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 >= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates both strings, the left one before the right one.
/// </summary>
QTEST_CASE ( OperatorAddition_ConcatenatesBothStrings_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABC");
    const QStringUnicode STRING2("DEF");
    const QStringUnicode EXPECTED_RESULT("ABCDEF");

	// [Execution]
    QStringUnicode strResult = STRING1 + STRING2;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_ReturnsExpectedCharacterWhenUsingCommonIndex_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QStringUnicode STRING1("ABC");
    const unsigned int COMMON_INDEX = 1;
    const QCharUnicode EXPECTED_RESULT(0x0042); // B

	// [Execution]
    QCharUnicode charResult = STRING1[COMMON_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( OperatorArraySubscript_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QCharUnicode EXPECTED_RESULT1('E');
    QCharUnicode EXPECTED_RESULT2(0x00011234);
    const unsigned int POSITION1 = 5;
    const unsigned int POSITION2 = 9;

	// [Execution]
    QCharUnicode character1 = SOURCE_STRING[POSITION1];
    QCharUnicode character2 = SOURCE_STRING[POSITION2];

    // [Verification]
    BOOST_CHECK(character1 == EXPECTED_RESULT1);
    BOOST_CHECK(character2 == EXPECTED_RESULT2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_ReturnsNonCharacterWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QStringUnicode EMPTY_STRING("");
    const unsigned int COMMON_INDEX = 1;
    const QCharUnicode EXPECTED_RESULT(0xFFFF); // Not a character

	// [Execution]
    QCharUnicode charResult = EMPTY_STRING[COMMON_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_ReturnsNonCharacterWhenIndexIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QStringUnicode STRING1("ABC");
    const unsigned int OUTOFBOUNDS_INDEX = 3;
    const QCharUnicode EXPECTED_RESULT(0xFFFF); // Not a character

	// [Execution]
    QCharUnicode charResult = STRING1[OUTOFBOUNDS_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode STRING1("ABC");
    const unsigned int OUTOFBOUNDS_INDEX = 3;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING1[OUTOFBOUNDS_INDEX];
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
QTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QStringUnicode EMPTY_STRING("");
    const unsigned int COMMON_INDEX = 1;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        EMPTY_STRING[COMMON_INDEX];
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected result when using common input position.
/// </summary>
QTEST_CASE ( Substring1_ReturnsExpectedResultWhenUsingCommonInputPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGHIJKLMN");
    const unsigned int START_POSITION = 4;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
QTEST_CASE ( Substring1_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 1;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring1_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = SOURCE_STRING.GetLength();

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( Substring1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    
    QStringUnicode EXPECTED_RESULT("EFGH");
    EXPECTED_RESULT.Append(QCharUnicode(0x00011234));
    const unsigned int START_POSITION = 5;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
QTEST_CASE ( Substring2_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGH");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION + 3;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( Substring2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKLMN");
    
    QStringUnicode EXPECTED_RESULT("EFGH");
    EXPECTED_RESULT.Append(QCharUnicode(0x00011234));
    const unsigned int START_POSITION = 5;
    const unsigned int LAST_POSITION = START_POSITION + 4;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring2_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an empty string is returned when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring2_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that an 1-length string is returned when start position equals last position.
/// </summary>
QTEST_CASE ( Substring2_ReturnsOneLenthStringWhenStartPositionEqualsLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("E");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
QTEST_CASE ( Substring2_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 1;
    const unsigned int LAST_POSITION = 3;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the rest of the string when the last position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring2_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("FGHIJKLMN");
    const unsigned int START_POSITION = 5;
    const unsigned int LAST_POSITION = SOURCE_STRING.GetLength() + 10;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring2_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = SOURCE_STRING.GetLength();
    const unsigned int LAST_POSITION = START_POSITION + 2;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input position.
/// </summary>
QTEST_CASE ( Substring3_ReturnsExpectedResultWhenUsingCommonInputPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGHIJKLMN");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
QTEST_CASE ( Substring3_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const QStringUnicode EXPECTED_RESULT("");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(1);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the entire string is returned when the start position iterator points to the end position (backward).
/// </summary>
QTEST_CASE ( Substring3_ReturnsFullStringWhenStartPositionIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT = SOURCE_STRING;
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position iterator points to the end position (forward).
/// </summary>
QTEST_CASE ( Substring3_ReturnsEmptyStringWhenStartPositionIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
QTEST_CASE ( Substring4_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGH");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(7);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring4_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(2);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an empty string is returned when the start position is greater than the last position.
/// </summary>
QTEST_CASE ( Substring4_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(2);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that an 1-length string is returned when start position equals last position.
/// </summary>
QTEST_CASE ( Substring4_ReturnsOneLenthStringWhenStartPositionEqualsLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("E");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const QStringUnicode::QConstCharIterator LAST_POSITION = START_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
QTEST_CASE ( Substring4_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const QStringUnicode EXPECTED_RESULT("");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(1);
    const QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(3);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the rest of the string when the last position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring4_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("FGHIJKLMN");
    const QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(5);
    QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
QTEST_CASE ( Substring4_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());
    QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position iterator and the last position iterator point to the end position (backward).
/// </summary>
QTEST_CASE ( Substring4_ReturnsEmptyStringWhenBothStartPositionAndLastPositionPointToBackwardEndPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator();
    --LAST_POSITION;

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the start position points to first position when it was pointing to the end position (backward).
/// </summary>
QTEST_CASE ( Substring4_StartPositionPointsToFirstPositionWhenItWasPointingToBackwardEndPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("ABCD");
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    const QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(3);

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the entire string is returned when the start position points to the end position (backward) and the last position points to the end position (forward).
/// </summary>
QTEST_CASE ( Substring4_ReturnsFullStringWhenStartPositionPointsToBackwardEndPositionAndLastPositionPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT = SOURCE_STRING;
    QStringUnicode::QConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    QStringUnicode::QConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    QStringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator1_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    QStringUnicode::QConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the obtained iterator points to the end position when the string is empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator1_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const bool IS_END = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that the iterator points to the given position.
/// </summary>
QTEST_CASE ( GetConstCharIterator2_IteratorPointsToTheGivenPosition_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const QCharUnicode EXPECTED_CHARACTER = 'F';

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(5);
    
    // [Verification]
    QCharUnicode charPointedToByIterator = iterator.GetChar();
    BOOST_CHECK(charPointedToByIterator == EXPECTED_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when input initial position is out of bounds.
/// </summary>
QTEST_CASE ( GetConstCharIterator2_IteratorPointsToEndPositionWhenInitialPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when the string is empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator2_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING = QStringUnicode::GetEmpty();
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(0);
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
QTEST_CASE ( GetCharIterator_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    QStringUnicode strSourceString("ABCDEFGHIJKLMN");
    QStringUnicode::QCharIterator EXPECTED_ITERATOR(strSourceString);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    QStringUnicode::QCharIterator iterator = strSourceString.GetCharIterator();

    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the obtained iterator points to the end position when the string is empty.
/// </summary>
QTEST_CASE ( GetCharIterator_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    QStringUnicode strEmptyString("");
    const bool IS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator iterator = strEmptyString.GetCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that it converts the string to ASCII correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToAsciiCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that characters that cannot be translated to ASCII are replaced by substitution characters (26).
/// </summary>
QTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByAsciiSubstitutionCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_q EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_AsciiNullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that it converts the string to ISO 8859-1 correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToISO88591Correctly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that characters that cannot be translated to ISO 8859-1 are replaced by substitution characters (26).
/// </summary>
QTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByISO88591SubstitutionCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_q EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_ISO88591NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-8 correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF8Correctly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF8NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 correctly and adds a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16CorrectlyAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                            BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                            BOM LE                  ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF16NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 correctly and adds a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32CorrectlyAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                         BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                         BOM LE                        ©                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF32NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16LECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                              ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                            ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16LE;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16LEEnconding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16LE;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16BECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                              ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                            ©              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16BE;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16BEEnconding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16BE;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32LECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                           ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                            ©                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32LE;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32LEEncoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32LE;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32BECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if QE_ENDIANNESS == QE_ENDIANNESS_BIGENDIAN
    //                                           ©                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#elif QE_ENDIANNESS == QE_ENDIANNESS_LITTLEENDIAN
    //                                            ©                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32BE;

    //                                         ©       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32BEEncoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32BE;

    //                                         ©       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it returns a null pointer when the string is empty.
/// </summary>
QTEST_CASE ( ToBytes_ReturnsNullPointerWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const i8_q* EXPECTED_STRING_BYTES = null_q;
    const unsigned int EXPECTED_STRING_LENGTH = 0;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    const QStringUnicode EMPTY_STRING = QStringUnicode::GetEmpty();

	// [Execution]
    QBasicArray<char> arByteArray = EMPTY_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(arByteArray.GetCount(), EXPECTED_STRING_LENGTH);
    BOOST_CHECK(arByteArray.Get() == EXPECTED_STRING_BYTES);
}

/// <summary>
/// Checks that the null character is counted when calculating the output length.
/// </summary>
QTEST_CASE ( ToBytes_FinalNullCharacterIsCountedForOutputLength_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const unsigned int EXPECTED_STRING_LENGTH = 4;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QBasicArray<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(arByteArray.GetCount(), EXPECTED_STRING_LENGTH);
}

#if QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST == QE_TEST_CONFIG_QSTRINGUNICODE_NORMALIZE_TEST_ENABLED

/// <summary>
/// Checks that the result of the normalization process is what expected. This test uses the NormalizationTest.txt file,
/// provided by the Unicode Standard, which has been modified to neither include comments nor CJK characteres. See the file UnicodeNormalizationTestData.h.
/// </summary>
QTEST_CASE ( Normalize_StringIsNormalizedAsExpected_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using namespace Kinesis::QuimeraEngine::Test::Normalization;

    // [Preparation]
    QNormalizationTestFileParser parser;
    parser.ParseFile("NormalizationTest.txt");
    const std::vector<QNormalizationTest>& arSpecificCases        = parser.GetSpecificCases();
    const std::vector<QNormalizationTest>& arCanonicalOrder       = parser.GetCanonicalOrder();
    const std::vector<QNormalizationTest>& arCharacterByCharacter = parser.GetCharacterByCharacter();
    const std::vector<QNormalizationTest>& arPublicReviewIssues   = parser.GetPublicReviewIssues();

    const EQTextEncoding ENCODING = EQTextEncoding::E_UTF32LE;
    const unsigned int CODEPOINT_SIZE = 4;

    for(unsigned int i = 0; i < arSpecificCases.size(); ++i)
    {
        QStringUnicode strOriginal((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arSpecificCases[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        QStringUnicode strExpectedNFC((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arSpecificCases[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        QStringUnicode strExpectedNFD((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arSpecificCases[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        QStringUnicode strResultNFC(strOriginal);
        QStringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(EQNormalizationForm::E_C);
        strResultNFD.Normalize(EQNormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arCanonicalOrder.size(); ++i)
    {
        QStringUnicode strOriginal((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arCanonicalOrder[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        QStringUnicode strExpectedNFC((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        QStringUnicode strExpectedNFD((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        QStringUnicode strResultNFC(strOriginal);
        QStringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(EQNormalizationForm::E_C);
        strResultNFD.Normalize(EQNormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arCharacterByCharacter.size(); ++i)
    {
        QStringUnicode strOriginal((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        QStringUnicode strExpectedNFC((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        QStringUnicode strExpectedNFD((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        QStringUnicode strResultNFC(strOriginal);
        QStringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(EQNormalizationForm::E_C);
        strResultNFD.Normalize(EQNormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arPublicReviewIssues.size(); ++i)
    {
        QStringUnicode strOriginal((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        QStringUnicode strExpectedNFC((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        QStringUnicode strExpectedNFD((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        QStringUnicode strResultNFC(strOriginal);
        QStringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(EQNormalizationForm::E_C);
        strResultNFD.Normalize(EQNormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    BOOST_MESSAGE("Normalization test finished");
}

#endif

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ACC");
    const QStringUnicode INPUT_STRING("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsLowerByLetterCaseAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsGreaterByLetterCaseAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("abcde");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(QCharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const QStringUnicode INPUT_STRING(QCharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode INPUT_STRING("ACC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const u16_q INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using binary case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingBinaryInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ACC");
    const QStringUnicode INPUT_STRING("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is upper case and input is lower case, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByLetterCaseAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("Abcde");
    const QStringUnicode INPUT_STRING("abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the only difference is the casing, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsLowerByLetterCaseAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("abcde");
    const QStringUnicode INPUT_STRING("Abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it does not return "equal" when the only difference is in the weight of punctuation, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsNotEqualWhenDifferenceIsPunctuationWeightUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(QCharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const QStringUnicode INPUT_STRING(QCharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode INPUT_STRING("ACC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const u16_q INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using binary case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingBinarySensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ACC");
    const QStringUnicode INPUT_STRING("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsLowerByLetterCaseAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsGreaterByLetterCaseAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("abcde");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(QCharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const QStringUnicode INPUT_STRING(QCharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode INPUT_STRING("ACC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const u16_q INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using canonical case insensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingCanonicalInsensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ACC");
    const QStringUnicode INPUT_STRING("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the resident string is upper case and input is lower case, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByLetterCaseAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("Abcde");
    const QStringUnicode INPUT_STRING("abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the only difference is the casing, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByLetterCaseAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("abcde");
    const QStringUnicode INPUT_STRING("Abcde");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(QCharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const QStringUnicode INPUT_STRING(QCharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode INPUT_STRING("ACC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABCDE");
    const u16_q INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const QStringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using canonical case sensitive comparison type.
/// </summary>
QTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingCanonicalSensitiveComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode INPUT_STRING("ABCDE");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than letters.
/// </summary>
QTEST_CASE ( CompareTo_PunctuationMarksAreLowerThanLetters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(",");
    const QStringUnicode INPUT_STRING("a");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that whitespace characters are lower than letters.
/// </summary>
QTEST_CASE ( CompareTo_WhitespacesAreLowerThanLetters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(" ");
    const QStringUnicode INPUT_STRING("a");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that number characters are lower than letters.
/// </summary>
QTEST_CASE ( CompareTo_NumbersAreLowerThanLetters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("5");
    const QStringUnicode INPUT_STRING("a");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than number characters.
/// </summary>
QTEST_CASE ( CompareTo_PunctuationMarksAreLowerThanNumbers_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(",");
    const QStringUnicode INPUT_STRING("5");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than number characters.
/// </summary>
QTEST_CASE ( CompareTo_WhitespacesAreLowerThanNumbers_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(" ");
    const QStringUnicode INPUT_STRING("6");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that number characters are lower than letters.
/// </summary>
QTEST_CASE ( CompareTo_WhitespacesAreLowerThanPunctuationMarks_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING(" ");
    const QStringUnicode INPUT_STRING(",");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of any string does not affect the result, since they are normalized when needed internally.
/// </summary>
QTEST_CASE ( CompareTo_NormalizationDoesNotAffectTheResultWhenUsingCanonicalComparisons_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                 A       _        ?        ¨       ñ
    u16_q NONNORMALIZED_SEQUENCE[] = { 0x0041, 0x0331, 0x0341, 0x00A8, 0x00F1 }; // Á_¨ñ
    const QStringUnicode NONNORMALIZED_STRING((char*)NONNORMALIZED_SEQUENCE, sizeof(NONNORMALIZED_SEQUENCE), string_q::GetLocalEncodingUTF16());
    QStringUnicode NORMALIZED_STRING(NONNORMALIZED_STRING);
    NORMALIZED_STRING.Normalize(EQNormalizationForm::E_D);
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResultNormalized = NORMALIZED_STRING.CompareTo(NORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNonNormalized = NORMALIZED_STRING.CompareTo(NONNORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNormalized2 = NORMALIZED_STRING.CompareTo(NORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNonNormalized2 = NORMALIZED_STRING.CompareTo(NONNORMALIZED_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultNormalized, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNonNormalized);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNonNormalized2);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNormalized2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( IndexOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
QTEST_CASE ( IndexOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
QTEST_CASE ( IndexOf1_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("A");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
QTEST_CASE ( IndexOf1_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
QTEST_CASE ( IndexOf1_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
QTEST_CASE ( IndexOf1_MatchesExactlyAtZeroIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( IndexOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( IndexOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.IndexOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.IndexOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( IndexOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
QTEST_CASE ( IndexOf2_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
QTEST_CASE ( IndexOf2_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("A");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
QTEST_CASE ( IndexOf2_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of strings affects the result.
/// </summary>
QTEST_CASE ( IndexOf2_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE, START_INDEX);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
QTEST_CASE ( IndexOf2_MatchesExactlyAtZeroIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;
    const unsigned int START_INDEX = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( IndexOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 6;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
QTEST_CASE ( IndexOf2_MatchesPreviousToStartIndexAreNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 7;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches are found at the start index.
/// </summary>
QTEST_CASE ( IndexOf2_MatchesExactlyAtStartIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
QTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStartPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 50;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( IndexOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.IndexOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION1);
    int uPosition2 = SOURCE_STRING.IndexOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION2);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( LastIndexOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
QTEST_CASE ( LastIndexOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
QTEST_CASE ( LastIndexOf1_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("A");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from right to left.
/// </summary>
QTEST_CASE ( LastIndexOf1_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 3;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
QTEST_CASE ( LastIndexOf1_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
QTEST_CASE ( LastIndexOf1_MatchesExactlyAtZeroIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( LastIndexOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( LastIndexOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.LastIndexOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.LastIndexOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("A");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from right to left.
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 3;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence after the index, from right to left.
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsTheFirstOccurrenceAfterIndex_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 2;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 13;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 13;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of strings affects the result.
/// </summary>
QTEST_CASE ( LastIndexOf2_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE, START_INDEX);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
QTEST_CASE ( LastIndexOf2_MatchesExactlyAtZeroIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( LastIndexOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
QTEST_CASE ( LastIndexOf2_MatchesPreviousToStartIndexAreNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {'A', 'b'}; // Ab
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = QStringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 9;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches are found at the start index.
/// </summary>
QTEST_CASE ( LastIndexOf2_MatchesExactlyAtStartIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when the start position is out of bounds.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStartPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 50;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( LastIndexOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.LastIndexOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION1);
    int uPosition2 = SOURCE_STRING.LastIndexOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION2);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that the pattern is found when the index lays inside of an occurrence, using canonical comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenIndexIsInsideAnOccurrenceUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("xZA");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 'x', 'Z', 'A', 'b'}; // áÁñ¨ CX`*xZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 9;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when the index lays inside of an occurrence, using canonical comparison.
/// </summary>
QTEST_CASE ( LastIndexOf2_PatternIsFoundWhenIndexIsInsideAnOccurrenceUsingBinaryComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("xZA");
    const u16_q RESIDENT_CHARS[] = {'A', 'B', 'C', '*', 'x', 'Z', 'A', 'b'}; // ABC*xZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 4;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE, START_INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the pattern is empty.
/// </summary>
QTEST_CASE ( Contains_ReturnsFalseWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident string is empty.
/// </summary>
QTEST_CASE ( Contains_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the pattern is not found.
/// </summary>
QTEST_CASE ( Contains_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("A");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
QTEST_CASE ( Contains_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    bool bResultNormalized    = NORMALIZED_RESIDENT_STRING.Contains(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    bool bResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.Contains(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(bResultNormalized, bResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
QTEST_CASE ( Contains_TheMatchesExactlyAtZeroIndexAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( Contains_TheMatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("DEF");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at zero position.
/// </summary>
QTEST_CASE ( PositionOf1_MatchesExactlyAtZeroPositionAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( PositionOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( PositionOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const QStringUnicode::QConstCharIterator EXPECTED_POSITION1(SOURCE_STRING, 5);
    const QStringUnicode::QConstCharIterator EXPECTED_POSITION2(SOURCE_STRING, 9);

	// [Execution]
    QStringUnicode::QConstCharIterator position1 = SOURCE_STRING.PositionOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive);
    QStringUnicode::QConstCharIterator position2 = SOURCE_STRING.PositionOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK(position1 == EXPECTED_POSITION1);
    BOOST_CHECK(position2 == EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsTheFirstOccurrence_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const QStringUnicode RESIDENT_STRING = QStringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 22, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(4);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 28, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(4);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at zero position.
/// </summary>
QTEST_CASE ( PositionOf2_MatchesExactlyAtZeroPositionAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    const QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
QTEST_CASE ( PositionOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(6);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}
    
/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
QTEST_CASE ( PositionOf2_MatchesPreviousToStartPositionAreNotFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN(rcast_q(PATTERN_CHARS, const char*), 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(7);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the matches are found at the start position.
/// </summary>
QTEST_CASE ( PositionOf2_MatchesExactlyAtStartPositionAreFound_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    QStringUnicode::QConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(5);
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(5);

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( PositionOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    QStringUnicode PATTERN1("EFGH");
    PATTERN1.Append(QCharUnicode(0x00011234));
    QStringUnicode PATTERN2(QCharUnicode(0x00011234));
    const QStringUnicode::QConstCharIterator EXPECTED_POSITION1(SOURCE_STRING, 5);
    const QStringUnicode::QConstCharIterator EXPECTED_POSITION2(SOURCE_STRING, 9);

	// [Execution]
    QStringUnicode::QConstCharIterator position1 = SOURCE_STRING.PositionOf(PATTERN1, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION1);
    QStringUnicode::QConstCharIterator position2 = SOURCE_STRING.PositionOf(PATTERN2, EQComparisonType::E_BinaryCaseSensitive, EXPECTED_POSITION2);

    // [Verification]
    BOOST_CHECK(position1 == EXPECTED_POSITION1);
    BOOST_CHECK(position2 == EXPECTED_POSITION2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
QTEST_CASE ( PositionOf2_AssertionFailsWhenStartPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ASSERTION_FAILED = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
QTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStartPositionIsOutOfBounds_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("CX");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING(rcast_q(RESIDENT_CHARS, const char*), 26, string_q::GetLocalEncodingUTF16());
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    QStringUnicode::QConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    QStringUnicode::QCharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE, START_POSITION);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

#endif

/// <summary>
/// Checks that the string does not change when the pattern is empty.
/// </summary>
QTEST_CASE ( Replace_StringDoesNotChangeWhenPatternIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("");
    const QStringUnicode REPLACEMENT("XX");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that resident string does not change when it is empty.
/// </summary>
QTEST_CASE ( Replace_StringDoesNotChangeWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("");
    const QStringUnicode PATTERN("ABC");
    const QStringUnicode REPLACEMENT("XX");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are removed when replacement string is empty.
/// </summary>
QTEST_CASE ( Replace_MatchesAreRemovedWhenReplacementStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("ABC");
    const QStringUnicode PATTERN("B");
    const QStringUnicode REPLACEMENT("");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT("AC");

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that all occurrences are replaced.
/// </summary>
QTEST_CASE ( Replace_ReplacesAllOccurrences_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode RESIDENT_STRING("AXBXCXDXEXF");
    const QStringUnicode PATTERN("X");
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT("A_B_C_D_E_F");

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("X");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("X");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("X");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("A");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("X");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
QTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZÁñabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, '_', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // á_CX`*ºZÁñabc
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
QTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZÁñabc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, '_', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // á_CX`*ºZÁñabc
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
QTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("Ab");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñab¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'c'}; // áÁñab¨ CX`*ºZ_c
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 30, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
QTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñab¨ CX`*ºZAbc
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, EQTextEncoding::E_UTF16LE);
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, '_', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'c'}; // áÁñab¨ CX`*ºZAbc
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 28, EQTextEncoding::E_UTF16LE);

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
QTEST_CASE ( Replace_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQNormalizationForm;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;

    // [Preparation]
    //                                          B       A       ?        _        C
    u16_q NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const QStringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_q::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_q NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const QStringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_q::GetLocalEncodingUTF16());

    QStringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(EQNormalizationForm::E_D);

    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseSensitive;
    const QStringUnicode EXPECTED_RESULT("B_C");

	// [Execution]
    QStringUnicode strNormalizedString(NORMALIZED_RESIDENT_STRING);
    QStringUnicode strNonNormalizedString(NONNORMALIZED_RESIDENT_STRING);
    strNormalizedString.Replace(NONNORMALIZED_PATTERN, REPLACEMENT, COMPARISON_TYPE);
    strNonNormalizedString.Replace(NONNORMALIZED_PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strNormalizedString != strNonNormalizedString);
}

/// <summary>
/// Checks that the pattern is replaced at zero index.
/// </summary>
QTEST_CASE ( Replace_MatchesExactlyAtZeroIndexAreReplaced_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const u16_q PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const QStringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_q::GetLocalEncodingUTF16());
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {'_', 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // _ñ¨ CX`*ºZAb
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 24, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is replaced at last position possible.
/// </summary>
QTEST_CASE ( Replace_MatchesExactlyAtLastPartOfResidentStringAreReplaced_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("aB");
    const u16_q RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_'}; // áÁñ¨ CX`*ºZ_
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 24, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the replacement string's length is greater than one.
/// </summary>
QTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementIsLongerThanOneCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("a");
    const u16_q RESIDENT_CHARS[] = {0xE1, 'a', 0xF1, 0xA8, 'a', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áañ¨aCX`*ºZAb
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("123456");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 56, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the pattern string's length is greater than one.
/// </summary>
QTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenSearchPatternIsLongerThanOneCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("123456");
    const u16_q RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 56, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("_");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, '_', 0xF1, 0xA8, '_', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'b'}; // á_ñ¨_CX`*ºZ_b
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the pattern string's and replacement string's length are greater than one.
/// </summary>
QTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementAndSearchPatternAreLongerThanOneCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("123456");
    const u16_q RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 56, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, 'A', 'B', 'C', 0xF1, 0xA8, 'A', 'B', 'C', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'B', 'C', 'b'}; // áABCñ¨ABCCX`*ºZABCb
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 38, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the resident string does not change when the pattern is larger.
/// </summary>
QTEST_CASE ( Replace_StringDoesNotChangeWhenPatternIsBigger_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("123456");
    const u16_q RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4'}; // á1234
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("ABC");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctlty replaced when the replacement string is larger than the resident string.
/// </summary>
QTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementIsBiggerThanResidentString_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("12");
    const u16_q RESIDENT_CHARS[] = {0xE1, '1', '2', 'b', '1', '2'}; // á12b12
    const QStringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 12, string_q::GetLocalEncodingUTF16());
    const QStringUnicode REPLACEMENT("ABCDEFGHI");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const u16_q EXPECTED_CHARS[] = {0xE1, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'b', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}; // áABCDEFGHIbABCDEFGHI
    const QStringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 40, string_q::GetLocalEncodingUTF16());

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the string is completely replaced when it equals the search pattern.
/// </summary>
QTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenResidentStringIsEqualToPattern_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // [Preparation]
    const QStringUnicode PATTERN("123456");
    const QStringUnicode RESIDENT_STRING = PATTERN;
    const QStringUnicode REPLACEMENT("ABCDEFGHI");
    const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_CanonicalCaseInsensitive;
    const QStringUnicode EXPECTED_RESULT = REPLACEMENT;

	// [Execution]
    QStringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that a common string is correctly appended.
/// </summary>
QTEST_CASE ( Append_CommonStringIsCorrectlyAppended_Test )
{
    // [Preparation]
    const QStringUnicode ORIGINAL_STRING("123456");
    const QStringUnicode APPENDIX("789");
    const QStringUnicode EXPECTED_RESULT("123456789");

	// [Execution]
    QStringUnicode strString(ORIGINAL_STRING);
    strString.Append(APPENDIX);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that appending an empty string takes no effect.
/// </summary>
QTEST_CASE ( Append_AppendingEmptyStringTakesNoEffect_Test )
{
    // [Preparation]
    const QStringUnicode ORIGINAL_STRING("123456");
    const QStringUnicode APPENDIX("");
    const QStringUnicode EXPECTED_RESULT = ORIGINAL_STRING;

	// [Execution]
    QStringUnicode strString(ORIGINAL_STRING);
    strString.Append(APPENDIX);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the resident string is empty.
/// </summary>
QTEST_CASE ( Split_ReturnsOneEmptyStringWhenResidentStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = QStringUnicode::GetEmpty();
    const unsigned int EXPECTED_SIZE = 1U;
    const QStringUnicode EXPECTED_STRING = QStringUnicode::GetEmpty();
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
}

/// <summary>
/// Checks that two empty strings are returned when the resident string contains only 1 separator.
/// </summary>
QTEST_CASE ( Split_ReturnsTwoEmptyStringsWhenResidentStringIsCompoundOfOnlyOneSeparator_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "/";
    const unsigned int EXPECTED_SIZE = 2U;
    const QStringUnicode EXPECTED_STRING = QStringUnicode::GetEmpty();
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING);
}

/// <summary>
/// Checks that several empty strings are returned when the resident string contains more than 1 separator only.
/// </summary>
QTEST_CASE ( Split_ReturnsSeveralEmptyStringsWhenResidentStringIsCompoundOfMoreThanOneSeparatorOnly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "///";
    const unsigned int EXPECTED_SIZE = 4U;
    const QStringUnicode EXPECTED_STRING = QStringUnicode::GetEmpty();
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[3] == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the value of a part that is surrounded by separators, when they are placed at the beginning and at the end of the string.
/// </summary>
QTEST_CASE ( Split_ReturnsTheValueOfPartSurroundedBySeparatorsWhenTheyArePlacedAtBeginningAndEnd_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "/123/";
    const unsigned int EXPECTED_SIZE = 3U;
    const QStringUnicode EXPECTED_STRING_NON_EMPTY = "123";
    const QStringUnicode EXPECTED_STRING_EMPTY = QStringUnicode::GetEmpty();
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING_EMPTY);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING_NON_EMPTY);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING_EMPTY);
}

/// <summary>
/// Checks that it returns the value of one part when there are not separators in the string.
/// </summary>
QTEST_CASE ( Split_ReturnsTheValueOfOnePartWhenThereAreNotSeparatorsInString_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "123";
    const unsigned int EXPECTED_SIZE = 1U;
    const QStringUnicode EXPECTED_STRING_NON_EMPTY = "123";
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING_NON_EMPTY);
}

/// <summary>
/// Checks that it returns every part of a common string divided by separators.
/// </summary>
QTEST_CASE ( Split_ReturnsEveryPartOfCommonStringDividedBySeparators_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "123/456/789";
    const unsigned int EXPECTED_SIZE = 3U;
    const QStringUnicode EXPECTED_STRING1 = "123";
    const QStringUnicode EXPECTED_STRING2 = "456";
    const QStringUnicode EXPECTED_STRING3 = "789";
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that it returns every part of a common string divided by separators whose length is greater than one.
/// </summary>
QTEST_CASE ( Split_ReturnsEveryPartOfCommonStringDividedBySeparatorsOfLengthGreaterThanOne_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "123-/-456-/-789";
    const unsigned int EXPECTED_SIZE = 3U;
    const QStringUnicode EXPECTED_STRING1 = "123";
    const QStringUnicode EXPECTED_STRING2 = "456";
    const QStringUnicode EXPECTED_STRING3 = "789";
    const QStringUnicode SEPARATOR = "-/-";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that it returns the entire string when the seperator is empty.
/// </summary>
QTEST_CASE ( Split_ReturnsEntireStringWhenSeparatorIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;

    // [Preparation]
    const QStringUnicode ORIGINAL_STRING = "123/456/789";
    const unsigned int EXPECTED_SIZE = 1U;
    const QStringUnicode EXPECTED_STRING = ORIGINAL_STRING;
    const QStringUnicode SEPARATOR = QStringUnicode::GetEmpty();

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( Split_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QBasicArray;
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    QStringUnicode ORIGINAL_STRING = "123/";
    ORIGINAL_STRING.Append(QCharUnicode(0x00010300));
    ORIGINAL_STRING.Append("/789");
    const unsigned int EXPECTED_SIZE = 3U;
    const QStringUnicode EXPECTED_STRING1 = "123";
    const QStringUnicode EXPECTED_STRING2 = QCharUnicode(0x00010300);
    const QStringUnicode EXPECTED_STRING3 = "789";
    const QStringUnicode SEPARATOR = "/";

	// [Execution]
    QBasicArray<QStringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that a common number is correctly parsed.
/// </summary>
QTEST_CASE ( ToInteger_CommonNumberIsParsed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("123456");
    const i64_q EXPECTED_NUMBER = 123456;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a negative number is correctly parsed.
/// </summary>
QTEST_CASE ( ToInteger_NegativeNumberIsParsed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("-123456");
    const i64_q EXPECTED_NUMBER = -123456;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a fractional number is correctly parsed when the separator is a period.
/// </summary>
QTEST_CASE ( ToInteger_FractionalNumberIsParsedWhenSeparatorIsPeriod_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("123.456");
    const i64_q EXPECTED_NUMBER = 123;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that commas are ignored when used to express a fractional number.
/// </summary>
QTEST_CASE ( ToInteger_FractionalNumberCommaSeparatorIsIgnored_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("123,456");
    const i64_q EXPECTED_NUMBER = 123456;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that there is no rounding performed when a fractional number is parsed.
/// </summary>
QTEST_CASE ( ToInteger_NoRoundingWhenFractionalNumberIsParsed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("123.999");
    const i64_q EXPECTED_NUMBER = 123;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that number preceded by a plus sign (+) are allowed.
/// </summary>
QTEST_CASE ( ToInteger_PlusSignIsAllowed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("+123");
    const i64_q EXPECTED_NUMBER = 123;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid number.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenStringStoresNoValidNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a positive number that exceeds the limits of the type.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenStringContainsATooBigPositiveNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("92233720368547758070");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a negative number that exceeds the limits of the type.
/// </summary>
QTEST_CASE ( ToInteger_AssertionFailsWhenStringContainsATooBigNegativeNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("92233720368547758080");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns zero when the string is empty.
/// </summary>
QTEST_CASE ( ToInteger_ReturnsZeroWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("");
    const i64_q EXPECTED_NUMBER = 0;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the string does not contain a valid number.
/// </summary>
QTEST_CASE ( ToInteger_ReturnsZeroWhenStringIsNotValid_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const i64_q EXPECTED_NUMBER = 0;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the number is clamped to the maximum range when the string contains a too big positive number.
/// </summary>
QTEST_CASE ( ToInteger_ReturnsMaximumWhenStringsContainsTooBigPositiveNumber_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    // [Preparation]
    const QStringUnicode STRING("92233720368547758070");
    const i64_q EXPECTED_NUMBER = SQInteger::MaxPositiveI64_Q;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the number is clamped to the maximum range when the string contains a too big negative number.
/// </summary>
QTEST_CASE ( ToInteger_ReturnsMaximumWhenStringsContainsTooBigNegativeNumber_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    // [Preparation]
    const QStringUnicode STRING("-92233720368547758080");
    const i64_q EXPECTED_NUMBER = SQInteger::MaxNegativeI64_Q;

	// [Execution]
    i64_q nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

#endif

/// <summary>
/// Checks that the full "true" word is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_FullTrueWordIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("true");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "T", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_TrueAbbreviationTIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("t");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "Y", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_TrueAbbreviationYIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("y");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "1", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_TrueAbbreviation1IsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("1");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full "false" word is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_FullFalseWordIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("false");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "F", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_FalseAbbreviationFIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("f");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "N", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_FalseAbbreviationNIsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("n");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "0", is correctly parsed.
/// </summary>
QTEST_CASE ( ToBoolean_FalseAbbreviation0IsCorrectlyParsed_Test )
{
    // [Preparation]
    const QStringUnicode STRING("0");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
QTEST_CASE ( ToBoolean_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToBoolean();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid boolean value.
/// </summary>
QTEST_CASE ( ToBoolean_AssertionFailsWhenStringDoesNotContainValidValue_Test )
{
    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToBoolean();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the string is empty.
/// </summary>
QTEST_CASE ( ToBoolean_ReturnsFalseWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode STRING("");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the string does not contain a valid boolean value.
/// </summary>
QTEST_CASE ( ToBoolean_ReturnsFalseWhenStringDoesNotContainValidValue_Test )
{
    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

#endif

/// <summary>
/// Checks that it is case insensitive.
/// </summary>
QTEST_CASE ( ToBoolean_IsCaseInsensitive_Test )
{
    // [Preparation]
    const QStringUnicode STRING("TrUe");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common number is correctly parsed.
/// </summary>
QTEST_CASE ( ToFloat_CommonNumberIsParsed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("123456");
    const f64_q EXPECTED_NUMBER = 123456.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a negative number is correctly parsed.
/// </summary>
QTEST_CASE ( ToFloat_NegativeNumberIsParsed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("-123456");
    const f64_q EXPECTED_NUMBER = -123456.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a fractional number is correctly parsed when the separator is a period.
/// </summary>
QTEST_CASE ( ToFloat_FractionalNumberIsParsedWhenSeparatorIsPeriod_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("123.456");
    const f64_q EXPECTED_NUMBER = 123.456;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the fractional part of the number is ignored if a comma is used as decimal separator.
/// </summary>
QTEST_CASE ( ToFloat_IfDecimalSeparatorIsCommaFractionalPartIsIgnored_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("123,456");
    const f64_q EXPECTED_NUMBER = 123.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that scientific notation is also allowed.
/// </summary>
QTEST_CASE ( ToFloat_ScientificNotationIsAllowed_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("1e03");
    const f64_q EXPECTED_NUMBER = 1000.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
QTEST_CASE ( ToFloat_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid number.
/// </summary>
QTEST_CASE ( ToFloat_AssertionFailsWhenStringStoresNoValidNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a positive number that exceeds the limits of the type.
/// </summary>
QTEST_CASE ( ToFloat_AssertionFailsWhenStringContainsATooBigPositiveNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("1e400");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a negative number that exceeds the limits of the type.
/// </summary>
QTEST_CASE ( ToFloat_AssertionFailsWhenStringContainsATooBigNegativeNumber_Test )
{
    // [Preparation]
    const QStringUnicode STRING("-1e400");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns zero when the string is empty.
/// </summary>
QTEST_CASE ( ToFloat_ReturnsZeroWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("");
    const f64_q EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the string does not contain a valid number.
/// </summary>
QTEST_CASE ( ToFloat_ReturnsZeroWhenStringIsNotValid_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("NotValid");
    const f64_q EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns positive infinite when the string contains a too big positive number.
/// </summary>
QTEST_CASE ( ToFloat_ReturnsPlusInfiniteWhenStringsContainsTooBigPositiveNumber_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    union UIntToFloat64
    {
        u64_q int_number;
        f64_q float_number;
    };

    // [Preparation]
    const QStringUnicode STRING("1e400");
    UIntToFloat64 uitof;
    uitof.int_number = 0x7FF0000000000000; // Positive infinite
    const f64_q EXPECTED_NUMBER = uitof.float_number;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns negative infinite when the string contains a too big negative number.
/// </summary>
QTEST_CASE ( ToFloat_ReturnsMinusInfiniteWhenStringsContainsTooBigNegativeNumber_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;

    union UIntToFloat64
    {
        u64_q int_number;
        f64_q float_number;
    };

    // [Preparation]
    const QStringUnicode STRING("-1e400");
    UIntToFloat64 uitof;
    uitof.int_number = 0xFFF0000000000000; // Negative infinite
    const f64_q EXPECTED_NUMBER = uitof.float_number;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the number is too small.
/// </summary>
QTEST_CASE ( ToFloat_ReturnsZeroWhenStringsContainsTooSmallNumber_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;

    // [Preparation]
    const QStringUnicode STRING("1e-400");
    const f64_q EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_q fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

#endif

/// <summary>
/// Checks that it returns zero when the string is empty.
/// </summary>
QTEST_CASE ( GetLength_ReturnsZeroWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("");
    const QStringUnicode::QConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    const bool IS_END = true;

	// [Execution]
    QStringUnicode::QConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that it returns the expected result value when using a common non-empty string.
/// </summary>
QTEST_CASE ( GetLength_ReturnsCorrectValueWhenUsingCommonString_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABC");
    const unsigned int EXPECTED_LENGTH = 3;

	// [Execution]
    unsigned int nLength = SOURCE_STRING.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(nLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( GetLength_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    QStringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(QCharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(QCharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    const int EXPECTED_LENGTH = 14;

	// [Execution]
    unsigned int uLength = SOURCE_STRING.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns True when the string is empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsTrueWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING = QStringUnicode::GetEmpty();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = SOURCE_STRING.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the string is not empty.
/// </summary>
QTEST_CASE ( IsEmpty_ReturnsFalseWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABC");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = SOURCE_STRING.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned buffer contains UTF-16 text.
/// </summary>
QTEST_CASE ( GetInternalBuffer_ReturnedBufferContainsUTF16Text_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABC");

	// [Execution]
    const u16_q* szCharacters = SOURCE_STRING.GetInternalBuffer();

    // [Verification]
    string_q strStringFromBuffer(rcast_q(szCharacters, const i8_q*), SOURCE_STRING.GetLength() * sizeof(u16_q), string_q::GetLocalEncodingUTF16());
    BOOST_CHECK(strStringFromBuffer == SOURCE_STRING);
}

/// <summary>
/// Checks that the returned buffer is not null when the string is empty.
/// </summary>
QTEST_CASE ( GetInternalBuffer_ReturnedBufferIsNotNullWhenStringIsEmpty_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING;

	// [Execution]
    const u16_q* szCharacters = SOURCE_STRING.GetInternalBuffer();

    // [Verification]
    BOOST_CHECK(szCharacters != null_q);
}

/// <summary>
/// Checks that it's an empty string, a string whose length is zero.
/// </summary>
QTEST_CASE ( GetEmpty_ReturnsZeroLengthString_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("");

	// [Execution]
    QStringUnicode strResult = QStringUnicode::GetEmpty();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to upper case works fine.
/// </summary>
QTEST_CASE ( ToUpperCase_StringWithEnglishCharactersConvertedToUpperCase_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("ABCDEFG");
    QStringUnicode INPUT_STRING("aBcdefg");

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToUpperCase();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with non-ASCII characters and numbers to upper case works fine.
/// </summary>
QTEST_CASE ( ToUpperCase_StringWithNonASCIICharsAndNumbersConvertedToUpperCase_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();

    // Info for inputs&outputs extracted from:
    // ftp://ftp.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt

    // Inputs:
    // 00F2;LATIN SMALL LETTER O WITH GRAVE
    // 010D;LATIN SMALL LETTER C WITH CARON
    // 0121;LATIN SMALL LETTER G WITH DOT ABOVE
    // 00DB;LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    // 0037;DIGIT SEVEN
    const u16_q INPUT_STRING_CODE_UNITS[]   = { 0x00F2, 0x010D, 0x0121, 0x0037, 0x00DB, 0 };
    const QStringUnicode INPUT_STRING(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);

    // Outputs:
    // 00D2;LATIN CAPITAL LETTER O WITH GRAVE
    // 010C;LATIN CAPITAL LETTER C WITH CARON
    // 0120;LATIN CAPITAL LETTER G WITH DOT ABOVE
    // 00DB;LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    // 0037;DIGIT SEVEN
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00D2, 0x010C, 0x0120, 0x0037, 0x00DB, 0 };
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    QStringUnicode strResult = INPUT_STRING.ToUpperCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to upper case.
/// </summary>
QTEST_CASE ( ToUpperCase_EmptyStringConvertedToUpperCase_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode INPUT_STRING("");

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToUpperCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to lower case works fine.
/// </summary>
QTEST_CASE ( ToLowerCase_StringWithEnglishCharactersConvertedToLowerCase_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("abcdefg");
    QStringUnicode INPUT_STRING("AbCDEFG");

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToLowerCase();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with non-ASCII characters and numbers to lower case works fine.
/// </summary>
QTEST_CASE ( ToLowerCase_StringWithNonASCIICharsAndNumbersConvertedToLowerCase_Test )
{
    // [Preparation]
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    
    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF16();

    // Info for inputs&outputs extracted from:
    // ftp://ftp.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt

    // Inputs:
    // 00D2;LATIN CAPITAL LETTER O WITH GRAVE
    // 010C;LATIN CAPITAL LETTER C WITH CARON
    // 0120;LATIN CAPITAL LETTER G WITH DOT ABOVE
    // 013C;LATIN SMALL LETTER L WITH CEDILLA
    // 0037;DIGIT SEVEN
    const u16_q INPUT_STRING_CODE_UNITS[]   = { 0x00D2, 0x010C, 0x0120, 0x0037, 0x013C, 0 };
    const QStringUnicode INPUT_STRING(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);

    // Outputs:
    // 00F2;LATIN SMALL LETTER O WITH GRAVE
    // 010D;LATIN SMALL LETTER C WITH CARON
    // 0121;LATIN SMALL LETTER G WITH DOT ABOVE
    // 013C;LATIN SMALL LETTER L WITH CEDILLA
    // 0037;DIGIT SEVEN
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F2, 0x010D, 0x0121, 0x0037, 0x013C, 0 };
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    QStringUnicode strResult = INPUT_STRING.ToLowerCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to lower case.
/// </summary>
QTEST_CASE ( ToLowerCase_EmptyStringConvertedToLowerCase_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode INPUT_STRING("");

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToLowerCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to folded case works fine.
/// </summary>
QTEST_CASE ( ToCaseFolded_StringConvertedToFoldedCase_Test )
{
    // [Preparation]

    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF32();

    // Data extracted from:
    // http://www.unicode.org/Public/UNIDATA/CaseFolding.txt
    // First row the original value.
    // 01F4; C; 01F5; # LATIN CAPITAL LETTER G WITH ACUTE
    // 0181; C; 0253; # LATIN CAPITAL LETTER B WITH HOOK
    // 004E; C; 006E; # LATIN CAPITAL LETTER N
    // 10426; C; 1044E; # DESERET CAPITAL LETTER OI
    // 00C3; C; 00E3; # LATIN CAPITAL LETTER A WITH TILDE
    // Useful to see the mappings:
    // http://www.branah.com/unicode-converter
    const u32_q INPUT_STRING_CODE_UNITS[]   = { 0x01F4, 0x0181, 0x004E, 0x10426, 0x00C3, 0 };
    const QStringUnicode INPUT_STRING(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);
   
    // Third row the mapped value.
    // 01F4; C; 01F5; # LATIN CAPITAL LETTER G WITH ACUTE
    // 0181; C; 0253; # LATIN CAPITAL LETTER B WITH HOOK
    // 004E; C; 006E; # LATIN CAPITAL LETTER N
    // 10426; C; 1044E; # DESERET CAPITAL LETTER OI
    // 00C3; C; 00E3; # LATIN CAPITAL LETTER A WITH TILDE
    const u32_q EXPECTED_STRING_CODE_UNITS[]   = { 0x01F5, 0x0253, 0x006E, 0x1044E, 0x00E3 ,0 };
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the conversion to folded case works fine in the case of the conversion to may change the length in bytes of the resultant string.
/// </summary>
QTEST_CASE ( ToCaseFolded_StringConvertedToFoldedCaseStringLengthMayChange_Test ) 
{
    // [Preparation]

    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;

    const EQTextEncoding NATIVE_ENCODING = string_q::GetLocalEncodingUTF32();

    // Data extracted from:
    // http://www.unicode.org/Public/UNIDATA/CaseFolding.txt
    // First row the original value.
    // 03B0; F; 03C5 0308 0301; # GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS.
    // Useful to see the mappings:
    // http://www.branah.com/unicode-converter
    const u32_q INPUT_STRING_CODE_UNITS[]   = { 0x03B0, 0 };
    const QStringUnicode INPUT_STRING(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);
   
    // Third row the mapped value.
    // 03B0; F; 03C5 0308 0301; # GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS.
    const u32_q EXPECTED_STRING_CODE_UNITS[]   = { 0x03C5, 0x0308, 0x0301, 0 };
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to folded case.
/// </summary>
QTEST_CASE ( ToCaseFolded_EmptyStringConvertedToFoldedCase_Test )
{
    // [Preparation]
    const QStringUnicode EXPECTED_RESULT("");
    QStringUnicode INPUT_STRING("");

	// [Execution]
    QStringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

// End - Test Suite: QStringUnicode
QTEST_SUITE_END()
