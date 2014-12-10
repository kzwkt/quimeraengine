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

#include "QTextStreamReader.h"

// The QMemoryStream type is used in all the tests
#include "QMemoryStream.h"

using Kinesis::QuimeraEngine::System::IO::QTextStreamReader;
using Kinesis::QuimeraEngine::System::IO::QMemoryStream;
using Kinesis::QuimeraEngine::System::IO::EQNewLineCharacters;
using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;


QTEST_SUITE_BEGIN( QTextStreamReader_TestSuite )

/// <summary>
/// Checks that the stream is correctly stored.
/// </summary>
QTEST_CASE ( Constructor1_StreamIsCorrectlyStored_Test )
{
    // [Preparation]
    QMemoryStream<> stream(1);
    const QMemoryStream<>* EXPECTED_STREAM = &stream;

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    QMemoryStream<>* pStoredStream = &reader.GetStream();
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const EQNewLineCharacters EXPECTED_NEWLINE = EQNewLineCharacters::E_LF;
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(1);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQNewLineCharacters eNewLine = reader.GetNewLineSeparator();
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eNewLine, EXPECTED_NEWLINE);
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF8 text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF8_Test )
{
    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF8;
    const string_q STREAM_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains ISO88591 text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForISO88591_Test )
{
    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF8;
    const string_q STREAM_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = STREAM_TEXT.ToBytes(EQTextEncoding::E_ISO88591, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains ASCII text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForASCII_Test )
{
    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF8;
    const string_q STREAM_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = STREAM_TEXT.ToBytes(EQTextEncoding::E_ASCII, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF16 little endian text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF16LE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF16LE;
    const string_q STREAM_TEXT = string_q(char_q(0xFFFD)) + "TestText";
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF16 big endian text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF16BE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF16BE;
    const string_q STREAM_TEXT = string_q(char_q(0xFFFD)) + "TestText";
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFE, (i8_q)0xFF}; // Big endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF32 little endian text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF32LE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF32LE;
    const string_q STREAM_TEXT = string_q(char_q(0xFFFD)) + "TestText";
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE, 0, 0}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    arBytes[2] = BOM[2];
    arBytes[3] = BOM[3];
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF32 big endian text.
/// </summary>
QTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF32BE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_UTF32BE;
    const string_q STREAM_TEXT = string_q(char_q(0xFFFD)) + "TestText";
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING, uBufferSize);
    static const i8_q BOM[] = {0, 0, (i8_q)0xFE, (i8_q)0xFF}; // Big endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    arBytes[2] = BOM[2];
    arBytes[3] = BOM[3];
    QMemoryStream<> stream(arBytes, uBufferSize);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream);

    // [Verification]
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the stream and the encoding are correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_StreamAndTheEncodingAreCorrectlyStored_Test )
{
    // [Preparation]
    QMemoryStream<> stream(1);
    const QMemoryStream<>* EXPECTED_STREAM = &stream;
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_ASCII;

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream, EXPECTED_ENCODING);

    // [Verification]
    QMemoryStream<>* pStoredStream = &reader.GetStream();
    EQTextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
QTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const EQNewLineCharacters EXPECTED_NEWLINE = EQNewLineCharacters::E_LF;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(1);

    // [Execution]
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);

    // [Verification]
    EQNewLineCharacters eNewLine = reader.GetNewLineSeparator();
    BOOST_CHECK_EQUAL(eNewLine, EXPECTED_NEWLINE);
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
QTEST_CASE ( ReadChars_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q NUMBER_OF_CHARS = 8U;
    const string_q EXPECTED_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
QTEST_CASE ( ReadChars_ResultIncludesBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const pointer_uint_q NUMBER_OF_CHARS = 10U;
    const string_q EXPECTED_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_q(0xFFFE) || strResult[0] == char_q(0xFEFF));

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
QTEST_CASE ( ReadChars_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q NUMBER_OF_CHARS = 9;
    const string_q INPUT_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    pointer_uint_q uCurrentPosition = stream.GetPosition();
    BOOST_CHECK(uCurrentPosition > ORIGINAL_POSITION);

    // [Cleaning]
    delete[] arBytes;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of characters equals zero.
/// </summary>
QTEST_CASE ( ReadChars_AssertionFailsWhenInputNumberOfCharsEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const pointer_uint_q NUMBER_OF_CHARS = 0;
    const string_q INPUT_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadChars(strResult, NUMBER_OF_CHARS);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);

    // [Cleaning]
    delete[] arBytes;
}

#endif

/// <summary>
/// Checks that it returns empty when the stream contains only one new line separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsEmptyWhenStreamContainsJustOneNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT = string_q::GetEmpty();
    pointer_uint_q uBufferSize = 1;
    i8_q arBytes = '\n';
    QMemoryStream<> stream(&arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns a non-empty string when the stream contains only one null terminator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsNonEmptyWhenStreamContainsJustOneNullTerminator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("\0", 1U);
    pointer_uint_q uBufferSize = 1;
    i8_q arBytes = '\0';
    QMemoryStream<> stream(&arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns empty when the new line character appears at the first position.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsEmptyWhenNewLineAppearsTheFirst_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT = string_q::GetEmpty();
    pointer_uint_q uBufferSize = 4U;
    const i8_q* arBytes = "\nABC";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the entire text but the new line when this appears at the last position.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsFullStringButLastNewLineWhenItAppearsAtTheEnd_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("ABC");
    pointer_uint_q uBufferSize = 4U;
    const i8_q* arBytes = "ABC\n";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is greater than the size of the batches used internally to read the text.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsGreaterThanInternalReadBatchesSize_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ ");
    pointer_uint_q uBufferSize = 387U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ \n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is lower than the size of the batches used internally to read the text.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsLowerThanInternalReadBatchesSize_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ ");
    pointer_uint_q uBufferSize = 195U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ \n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is equal to the size of the batches used internally to read the text.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsEqualToInternalReadBatchesSize_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    pointer_uint_q uBufferSize = 312U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is greater than the size of the batches used internally to read the text, and there is no new line separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsGreaterThanInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    pointer_uint_q uBufferSize = 320U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is lower than the size of the batches used internally to read the text, and there is no length separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsLowerThanInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    pointer_uint_q uBufferSize = 128U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is equal to the size of the batches used internally to read the text, and there is no legnth separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsEqualToInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    pointer_uint_q uBufferSize = 256U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the LF character as separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineLF_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("AB");
    pointer_uint_q uBufferSize = 5U;
    const i8_q* arBytes = "AB\nCD";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the CR character as separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineCR_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("AB");
    pointer_uint_q uBufferSize = 5U;
    const i8_q* arBytes = "AB\rCD";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    reader.SetNewLineSeparator(EQNewLineCharacters::E_CR);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the CR and LF characters as separator.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineCRLF_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("AB");
    pointer_uint_q uBufferSize = 6U;
    const i8_q* arBytes = "AB\r\nCD";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    reader.SetNewLineSeparator(EQNewLineCharacters::E_CRLF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the entire text when the chosen new line separator does not match the separator used in it.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsFullTextWhenUsingWrongNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("AB\rCD");
    pointer_uint_q uBufferSize = 5U;
    const i8_q* arBytes = "AB\rCD";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
QTEST_CASE ( ReadLine_ResultIncludesBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const string_q EXPECTED_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_q(0xFFFE) || strResult[0] == char_q(0xFEFF));

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that tthe internal pointer of the stream points to the position after the new line characters.
/// </summary>
QTEST_CASE ( ReadLine_StreamInternalPointerPointsToPositionAfterNewLineSeparator_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q INPUT_TEXT("Test\r\nText");
    const pointer_uint_q EXPECTED_POSITION = 6; // After \r\n
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    reader.SetNewLineSeparator(EQNewLineCharacters::E_CRLF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    pointer_uint_q uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that it returns the correct result when the new line separator is split in two batches internally.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenTheNewLineSeparatorIsDividedInTwoBatchesInternally_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    pointer_uint_q uBufferSize = 312U;
    const i8_q* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!\r\n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_CRLF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when a UTF8 character is split in two batches internally.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenUTF8CharacterIsDividedInTwoBatchesInternally_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBN");
    EXPECTED_TEXT.Append(char_q(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    
    string_q strInput(EXPECTED_TEXT);
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = strInput.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U); // -1 to quit the trailing zero
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that it returns the correct result when a UTF16 character is split in two batches internally.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenUTF16CharacterIsDividedInTwoBatchesInternally_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_q EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzx");
    EXPECTED_TEXT.Append(char_q(0x00010300)); // A character compound of 2 codeunits in UTF16 (D800 DF00)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxc");
    
    string_q strInput(EXPECTED_TEXT);
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = strInput.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 2U); // -2 to quit the trailing zero
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that it returns the correct result when called several times.
/// </summary>
QTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenIsCalledSeveralTimes_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_q STREAM_TEXT("\
\r\n34567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    STREAM_TEXT.Append(char_q(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    STREAM_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCV\r\
\n1234567890qwertyuiopasdfghj\r\n\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM\r\n");

    string_q EXPECTED_TEXT("\
34567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    EXPECTED_TEXT.Append(char_q(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCV\
1234567890qwertyuiopasdfghj\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
    
    string_q strInput(STREAM_TEXT);
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = strInput.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U); // -1 to quit the trailing zero
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_CRLF);
    string_q strResult;

    // [Execution]
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
QTEST_CASE ( ReadToEnd_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
QTEST_CASE ( ReadToEnd_ResultIncludesBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const string_q EXPECTED_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_q(0xFFFE) || strResult[0] == char_q(0xFEFF));

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
QTEST_CASE ( ReadToEnd_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q INPUT_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    const pointer_uint_q EXPECTED_POSITION = stream.GetLength();

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    pointer_uint_q uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the text is correctly read when it contains characters of the Supplementary Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( ReadToEnd_TextIsCorrectlyReadWhenItContainsSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    string_q EXPECTED_TEXT("TestText");
    EXPECTED_TEXT.Append(char_q(0x00010300));
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
QTEST_CASE ( ReadBlock_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q NUMBER_OF_BYTES = 8U;
    const string_q EXPECTED_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
QTEST_CASE ( ReadBlock_ResultIncludesBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const pointer_uint_q NUMBER_OF_BYTES = 20U;
    const string_q EXPECTED_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_q(0xFFFE) || strResult[0] == char_q(0xFEFF));

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
QTEST_CASE ( ReadBlock_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q NUMBER_OF_BYTES = 9;
    const string_q INPUT_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    pointer_uint_q uCurrentPosition = stream.GetPosition();
    BOOST_CHECK(uCurrentPosition > ORIGINAL_POSITION);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that characters compound of more than one code unit that are not completely contained in the block of bytes are not added to the result.
/// </summary>
QTEST_CASE ( ReadBlock_IncompleteCharactersAreNotRead_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    const pointer_uint_q NUMBER_OF_BYTES = 6U;
    string_q INPUT_TEXT("Test");
    INPUT_TEXT.Append(char_q(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    INPUT_TEXT.Append("Text");
    const string_q EXPECTED_TEXT("Test");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of bytes equals zero.
/// </summary>
QTEST_CASE ( ReadBlock_AssertionFailsWhenInputNumberOfBytesEqualsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const pointer_uint_q NUMBER_OF_BYTES = 0;
    const string_q INPUT_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadBlock(strResult, NUMBER_OF_BYTES);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that an assertion fails when the number of bytes is not a multiple of the character size.
/// </summary>
QTEST_CASE ( ReadBlock_AssertionFailsWhenInputNumberOfBytesIsNotMultipleOfCharacterSize_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const pointer_uint_q NUMBER_OF_BYTES = 5U;
    const string_q INPUT_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadBlock(strResult, NUMBER_OF_BYTES);
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);

    // [Cleaning]
    delete[] arBytes;
}

#endif

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
QTEST_CASE ( OperatorRightShift_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q EXPECTED_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
QTEST_CASE ( OperatorRightShift_ResultIncludesBOM_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    const string_q EXPECTED_TEXT("*TestText");
    pointer_uint_q uBufferSize = 0;
    i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    static const i8_q BOM[] = {(i8_q)0xFF, (i8_q)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    QMemoryStream<> stream(arBytes, uBufferSize);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult[0] == char_q(0xFFFE) || strResult[0] == char_q(0xFEFF));

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
QTEST_CASE ( OperatorRightShift_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const string_q INPUT_TEXT("TestText");
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    const pointer_uint_q EXPECTED_POSITION = stream.GetLength();

    // [Execution]
    reader >> strResult;

    // [Verification]
    pointer_uint_q uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that the text is correctly read when it contains characters of the Supplementary Multilingual Plane (SMP).
/// </summary>
QTEST_CASE ( OperatorRightShift_TextIsCorrectlyReadWhenItContainsSMPCharacters_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    string_q EXPECTED_TEXT("TestText");
    EXPECTED_TEXT.Append(char_q(0x00010300));
    pointer_uint_q uBufferSize = 0;
    const i8_q* arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING, uBufferSize);
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);

    // [Cleaning]
    delete[] arBytes;
}

/// <summary>
/// Checks that it returns a reference to the text reader instance.
/// </summary>
QTEST_CASE ( OperatorRightShift_ReturnsReferenceToTextReader_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    pointer_uint_q uBufferSize = 8U;
    const i8_q* arBytes = "TestText";
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    string_q strResult;
    const QTextStreamReader< QMemoryStream<> >* EXPECTED_REFERENCE = &reader;

    // [Execution]
    const QTextStreamReader< QMemoryStream<> >* pReference = &(reader >> strResult);

    // [Verification]
    BOOST_CHECK_EQUAL(pReference, EXPECTED_REFERENCE);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetNewLineSeparator_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
QTEST_CASE ( SetNewLineSeparator_ValueIsCorrectlyStored_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const EQNewLineCharacters EXPECTED_VALUE = EQNewLineCharacters::E_CR;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    pointer_uint_q uBufferSize = 8U;
    const i8_q* arBytes = "TestText";
    QMemoryStream<> stream(arBytes, uBufferSize - 1U);
    QTextStreamReader< QMemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(EQNewLineCharacters::E_LF);
    const EQNewLineCharacters ORIGINAL_VALUE = reader.GetNewLineSeparator();
    string_q strResult;

    // [Execution]
    reader.SetNewLineSeparator(EXPECTED_VALUE);

    // [Verification]
    EQNewLineCharacters eNewLine = reader.GetNewLineSeparator();
    BOOST_CHECK(eNewLine == EXPECTED_VALUE);
    BOOST_CHECK(eNewLine != ORIGINAL_VALUE);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetStreamEncoding_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetStream_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QTextStreamReader
QTEST_SUITE_END()
