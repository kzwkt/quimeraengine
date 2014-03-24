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

using Kinesis::QuimeraEngine::Common::DataTypes::QStringUnicode;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;


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
/// Checks that input string, encoded in ASCII, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor3_AsciiStringIsCorrectlyConverted_Test )
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
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
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

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[]        = { '�', 'B', '�', 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_ISO88591;

    //                                             
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-8, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor3_Utf8StringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                         �                       ?                                   ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Little Endian.
/// </summary>
QTEST_CASE ( Constructor3_Utf16StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM LE                  �              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Big Endian.
/// </summary>
QTEST_CASE ( Constructor3_Utf16StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM BE                  �              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is treated as if it was Big Endian when there is no BOM.
/// </summary>
QTEST_CASE ( Constructor3_Utf16StringIsTreatedAsBigEndianWhenNoBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         �              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                            BOM BE                  �              ?                       ?                       ?                      \0
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
QTEST_CASE ( Constructor3_Utf32StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         BOM LE                        �                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is correctly converted when BOM indicates Big Endian.
/// </summary>
QTEST_CASE ( Constructor3_Utf32StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         �                    ?                             ?                             ?                            \0
    //                                         BOM BE                        �                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is treated as if it was Big Endian when there is no BOM.
/// </summary>
QTEST_CASE ( Constructor3_Utf32StringIsTreatedAsBigEndianWhenNoBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         �                    ?                             ?                             ?                            \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                            BOM BE                        �                    ?                             ?                             ?                            \0
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
QTEST_CASE ( Constructor3_Utf16BEStringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         �              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16BE;

    // [TODO] Thund: Change the expected result so it depends on the endianess of the machine where the tests are being executed. 
    //               It is necessary to implement a way to know that endianess.
    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16 Little Endian, is correctly converted.
/// </summary>
QTEST_CASE ( Constructor3_Utf16LEStringIsCorrectlyConverted_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         �              ?                       ?                       ?                      \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16LE;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-16 encoding.
/// </summary>
QTEST_CASE ( Constructor3_BOMIsRemovedFromStringWhenUsingUtf16Encoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                        BOM     �       ?       ?       ?      \0
    const u16_q INPUT_STRING_CODE_UNITS[] = { 0xFFFE, 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != QStringUnicode::CHAR_BOM_LE);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-32 encoding.
/// </summary>
QTEST_CASE ( Constructor3_BOMIsRemovedFromStringWhenUsingUtf32Encoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                        BOM         �           ?           ?           ?          \0
    const u32_q INPUT_STRING_CODE_UNITS[] = { 0x0000FEFF, 0x000000A9, 0x000016A1, 0x00000634, 0x00000416, 0x00000000 }; 
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                           �       ?       ?       ?      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(rcast_q(INPUT_STRING_CODE_UNITS, const i8_q*), INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != QStringUnicode::CHAR_BOM_LE);
}

/// <summary>
/// Checks that ill-formed sequences are repaired, replacing the wrong characters by U+FFFD REPLACEMENT CHARACTER, when passing Utf8 string.
/// </summary>
QTEST_CASE ( Constructor3_IllFormedSequencesAreRepairedUsingReplacementCharacterWhenUsingUtf8_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    //                                         A           ILL-FORMED  �                       B          \0
    const i8_q INPUT_STRING_BYTES[]        = { (char)0x41, (char)0xC2, (char)0xC3, (char)0xB1, (char)0x42, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           A       REPLAC. �       B      \0
    const u16_q EXPECTED_STRING_CODE_UNITS[] = { 0x0041, 0xFFFD, 0x00F1, 0x0042, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the values of the optional parameters are ISO 8859-1 encoding and Null-terminated length, when no arguments are passed.
/// </summary>
QTEST_CASE ( Constructor3_OptionalParametersDefaultToNullTerminatedIso88591_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[] = { '�', 'B', '�', 0 };

    //                                             �       B       �
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input length equals zero.
/// </summary>
QTEST_CASE ( Constructor3_CreatesEmptyStringWhenInputLengthEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[] = { '�', 'B', '�', 0 };
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
QTEST_CASE ( Constructor3_AssertionFailsWhenUsingIncorrectParameterValueCombination_Test )
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
    catch(...)
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
QTEST_CASE ( Constructor3_StringIsCorrectlyBuiltWhenInputLengthIsUnknown_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q INPUT_STRING_BYTES[] = { '�', 'B', '�', 0 };
    const int UNKNOWN_LENGTH = QStringUnicode::LENGTH_NULL_TERMINATED;
    const EQTextEncoding ENCODING = EQTextEncoding::E_ISO88591;

    //                                             �       B       �
    const u16_q EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    const QStringUnicode EXPECTED_RESULT(rcast_q(EXPECTED_STRING_CODE_UNITS, const i8_q*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    QStringUnicode strString(INPUT_STRING_BYTES, UNKNOWN_LENGTH, ENCODING);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the resultant string contains the input character.
/// </summary>
QTEST_CASE ( Constructor4_ResultContainsInputCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
    using Kinesis::QuimeraEngine::Common::DataTypes::QCharUnicode;

    // [Preparation]
    const QCharUnicode INPUT_CHARACTER(0x1234);
    const u16_q EXPECTED_STRING_BYTES[] = { INPUT_CHARACTER.GetCodePoint() };
    // [TODO] Thund: Make this dependent on the architecture
    const QStringUnicode EXPECTED_RESULT = QStringUnicode(rcast_q(EXPECTED_STRING_BYTES, const i8_q*), sizeof(EXPECTED_STRING_BYTES), EQTextEncoding::E_UTF16LE); 

	// [Execution]
    QStringUnicode strString(INPUT_CHARACTER);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

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
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // � -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // � -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*));
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*));
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
    u16_q CHAR_STRING1[] = { 0x212B, 0 }; // � -> U+212B
    u16_q CHAR_STRING2[] = { 0x00C5, 0 }; // � -> U+00C5
    const QStringUnicode STRING1(rcast_q(CHAR_STRING1, const i8_q*));
    const QStringUnicode STRING2(rcast_q(CHAR_STRING2, const i8_q*));
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 != STRING2;
    
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
    catch(...)
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
    catch(...)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
QTEST_CASE ( Substring_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("EFGH");
    const unsigned int START_POSITION = 4;
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
QTEST_CASE ( Substring_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
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
    catch(...)
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
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
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
/// Checks that an empty string is returned when start position equals last position.
/// </summary>
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionEqualsLastPosition_Test )
{
    // [Preparation]
    const QStringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const QStringUnicode EXPECTED_RESULT("");
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
QTEST_CASE ( Substring_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
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
QTEST_CASE ( Substring_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
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
QTEST_CASE ( Substring_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
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
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
QTEST_CASE ( GetConstCharIterator_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
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
QTEST_CASE ( GetConstCharIterator_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
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
/// Checks that it converts the string to ASCII correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToAsciiCorrectly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that characters that cannot be translated to ASCII are replaced by substitution characters (26).
/// </summary>
QTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByAsciiSubstitutionCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_q EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_AsciiNullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to ISO 8859-1 correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToISO88591Correctly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that characters that cannot be translated to ISO 8859-1 are replaced by substitution characters (26).
/// </summary>
QTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByISO88591SubstitutionCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_q EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_ISO88591NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-8 correctly.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF8Correctly_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF8NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF8;

    //                                           �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-16 correctly and adds a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16CorrectlyAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                            BOM BE                  �              ?                       ?                       ?                      \0
    //const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    //                                            BOM LE                  �              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF16NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-32 correctly and adds a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32CorrectlyAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                         BOM BE                        �                    ?                             ?                             ?                            \0
    //const i8_q INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    //                                         BOM LE                        �                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_UTF32NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-16 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16LECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                              �              ?                       ?                       ?                      \0
    //const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    //                                            �              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16LE;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16LEEnconding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16LE;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-16 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF16BECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                              �              ?                       ?                       ?                      \0
    //const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    //                                            �              ?                       ?                       ?                      \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF16BE;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16BEEnconding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF16BE;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-32 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32LECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                           �                    ?                             ?                             ?                            \0
    //const i8_q INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    //                                            �                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32LE;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32LEEncoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32LE;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it converts the string to UTF-32 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
QTEST_CASE ( ToBytes_ConvertsToUTF32BECorrectlyNotAddingBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    // [TODO] Thund: Change this so it depends on the endianess of the machine
    //                                           �                    ?                             ?                             ?                            \0
    //const i8_q INPUT_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    //                                            �                    ?                             ?                             ?                            \0
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING       = EQTextEncoding::E_UTF32BE;

    //                                         �       ?       ?       ?      \0
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
QTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32BEEncoding_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const EQTextEncoding INPUT_ENCODING    = EQTextEncoding::E_UTF32BE;

    //                                         �       ?       ?       ?
    const u16_q SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 }; 
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_NE(uResultSize, sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(pByteArray, uResultSize, EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));

    // [Cleaning]
    delete[] pByteArray;
}

/// <summary>
/// Checks that it returns a null pointer when the string is empty.
/// </summary>
QTEST_CASE ( ToBytes_ReturnsNullPointerWhenStringIsEmpty_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const i8_q* EXPECTED_STRING_BYTES = null_q;
    const unsigned int EXPECTED_STRING_LENGTH = 0;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    const QStringUnicode EMPTY_STRING = QStringUnicode::GetEmpty();

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = EMPTY_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResultSize, EXPECTED_STRING_LENGTH);
    BOOST_CHECK(pByteArray == EXPECTED_STRING_BYTES);
}

/// <summary>
/// Checks that the null character is counted when calculating the output length.
/// </summary>
QTEST_CASE ( ToBytes_FinalNullCharacterIsCountedForOutputLength_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::u16_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    // [Preparation]
    const unsigned int EXPECTED_STRING_LENGTH = 4;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_q SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const EQTextEncoding NATIVE_ENCODING = EQTextEncoding::E_UTF16LE; // [TODO] Thund: Change this so it depends on the endianess of the machine
    QStringUnicode SOURCE_STRING(rcast_q(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    unsigned int uResultSize = 0;
    char* pByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING, uResultSize);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResultSize, EXPECTED_STRING_LENGTH);

    // [Cleaning]
    delete[] pByteArray;
}

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

// End - Test Suite: QStringUnicode
QTEST_SUITE_END()