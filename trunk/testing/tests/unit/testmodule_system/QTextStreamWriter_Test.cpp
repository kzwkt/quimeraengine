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

#include "QTextStreamWriter.h"

#include "QMemoryStream.h"
#include "EQTextEncoding.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::System::IO::QTextStreamWriter;
using Kinesis::QuimeraEngine::System::IO::EQNewLineCharacters;
using Kinesis::QuimeraEngine::System::IO::QMemoryStream;
using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;


QTEST_SUITE_BEGIN( QTextStreamWriter_TestSuite )
    
/// <summary>
/// Checks that the stream and the encoding are correctly stored.
/// </summary>
QTEST_CASE ( Constructor_StreamAndTheEncodingAreCorrectlyStored_Test )
{
    // [Preparation]
    QMemoryStream<> stream(1);
    const QMemoryStream<>* EXPECTED_STREAM = &stream;
    const EQTextEncoding EXPECTED_ENCODING = EQTextEncoding::E_ASCII;

    // [Execution]
    QTextStreamWriter< QMemoryStream<> > writer(stream, EXPECTED_ENCODING);

    // [Verification]
    QMemoryStream<>* pStoredStream = &writer.GetStream();
    EQTextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that the input encoding is transformed to its endianness-dependant version when using UTF-16.
/// </summary>
QTEST_CASE ( Constructor_EncodingIsConvertedToEndiannessDependantVersionWhenUsingUTF16_Test )
{
    // [Preparation]
    QMemoryStream<> stream(1);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16;
    const EQTextEncoding EXPECTED_ENCODING = string_q::GetLocalEncodingUTF16();

    // [Execution]
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    EQTextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the input encoding is transformed to its endianness-dependant version when using UTF-32.
/// </summary>
QTEST_CASE ( Constructor_EncodingIsConvertedToEndiannessDependantVersionWhenUsingUTF32_Test )
{
    // [Preparation]
    QMemoryStream<> stream(1);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32;
    const EQTextEncoding EXPECTED_ENCODING = string_q::GetLocalEncodingUTF32();

    // [Execution]
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    EQTextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK_EQUAL(eEncoding, EXPECTED_ENCODING);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const EQNewLineCharacters EXPECTED_NEWLINE = EQNewLineCharacters::E_LF;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(1);

    // [Execution]
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    EQNewLineCharacters eNewLine = writer.GetNewLineSeparator();
    BOOST_CHECK_EQUAL(eNewLine, EXPECTED_NEWLINE);
}

/// <summary>
/// Checks that the stream position pointer does not change.
/// </summary>
QTEST_CASE ( Constructor_StreamPositionPointerIsNotChanged_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_POSITON = 2;
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(4);
    const int ANY_CONTENT = 0;
    stream.Write(&ANY_CONTENT, 0, sizeof(int));
    stream.SetPosition(EXPECTED_POSITON);

    // [Execution]
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    pointer_uint_q uPosition = writer.GetStream().GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITON);
}

/// <summary>
/// Checks that the text is written when using ASCII encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ISO88591;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size lower than the length of the text.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingBatchSizeLowerThanTextLength_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const string_q EXPECTED_TEXT("texttexttexttext\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q BATCH_SIZE = 4U;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size that produces some character to be divided into two halfs.
/// </summary>
QTEST_CASE ( WriteLine_TextIsWrittenWhenUsingBatchSizeThatDividesCharactersInTwoHalfs_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const string_q EXPECTED_TEXT("texttexttexttext\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16;
    const pointer_uint_q BATCH_SIZE = 9U;
    QMemoryStream<> stream(40);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), writer.GetStreamEncoding());
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that only the new line separator is written when the input text is empty.
/// </summary>
QTEST_CASE ( WriteLine_OnlyNewLineSeparatorIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT = string_q::GetEmpty();
    const string_q EXPECTED_TEXT("\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using CR.
/// </summary>
QTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingCR_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\r");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    const EQNewLineCharacters NEW_LINE_SEPARATOR = EQNewLineCharacters::E_CR;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using LF.
/// </summary>
QTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingLF_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    const EQNewLineCharacters NEW_LINE_SEPARATOR = EQNewLineCharacters::E_LF;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using CR-LF.
/// </summary>
QTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingCRLF_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\r\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    const EQNewLineCharacters NEW_LINE_SEPARATOR = EQNewLineCharacters::E_CRLF;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
QTEST_CASE ( WriteLine_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
QTEST_CASE ( WriteLine_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text\ntext\n");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
QTEST_CASE ( WriteLine_AssertionFailsWhenBatchSizeIsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q BATCH_SIZE = 0;
    QMemoryStream<> stream(1);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
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
/// Checks that the text is written when using ASCII encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ISO88591;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size lower than the length of the text.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingBatchSizeLowerThanTextLength_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const string_q EXPECTED_TEXT("texttexttexttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q BATCH_SIZE = 4U;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size that produces some character to be divided into two halfs.
/// </summary>
QTEST_CASE ( Write_TextIsWrittenWhenUsingBatchSizeThatDividesCharactersInTwoHalfs_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const string_q EXPECTED_TEXT("texttexttexttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16;
    const pointer_uint_q BATCH_SIZE = 9U;
    QMemoryStream<> stream(40);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), writer.GetStreamEncoding());
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that nothing is written when the input text is empty.
/// </summary>
QTEST_CASE ( Write_NothingIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT = string_q::GetEmpty();
    const string_q EXPECTED_TEXT("");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
QTEST_CASE ( Write_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
QTEST_CASE ( Write_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("texttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
QTEST_CASE ( Write_AssertionFailsWhenBatchSizeIsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q BATCH_SIZE = 0;
    QMemoryStream<> stream(1);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.Write(INPUT_TEXT, BATCH_SIZE);
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
/// Checks that the BOM is written when usint the UTF-16 LE encoding.
/// </summary>
QTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q EXPECTED_TEXT = string_q(char_q(0xFEFF));
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-16 BE encoding.
/// </summary>
QTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q EXPECTED_TEXT = string_q(char_q(0xFEFF));
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16BE;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-32 LE encoding.
/// </summary>
QTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q EXPECTED_TEXT = string_q(char_q(0xFEFF));
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32LE;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-32 BE encoding.
/// </summary>
QTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q EXPECTED_TEXT = string_q(char_q(0xFEFF));
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32BE;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
QTEST_CASE ( WriteBOM_PositionIsMovedForward_Test )
{
    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
QTEST_CASE ( WriteBOM_NoTrailingZeroIsAdded_Test )
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    // [Preparation]
    const string_q EXPECTED_TEXT = string_q(char_q(0xFEFF)) + char_q(0xFEFF);
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the encoding is neither UTF16 nor UTF32.
/// </summary>
QTEST_CASE ( WriteBOM_AssertionFailsWhenEncodingIsNotUTF16NorUTF32_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(1);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.WriteBOM();
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
/// Checks that the text is written when using ASCII encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ISO88591;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF16BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32LE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF32BE;
    QMemoryStream<> stream(12);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that nothing is written when the input text is empty.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_NothingIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT = string_q::GetEmpty();
    const string_q EXPECTED_TEXT("");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_UTF8;
    QMemoryStream<> stream(6);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    const pointer_uint_q ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_q INPUT_TEXT("text");
    const string_q EXPECTED_TEXT("texttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    QMemoryStream<> stream(18);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_q strResult(rcast_q(stream.GetCurrentPointer(), i8_q*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
QTEST_CASE ( OperatorShiftLeft_AssertionFailsWhenBatchSizeIsZero_Test )
{
    using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;

    // [Preparation]
    const string_q INPUT_TEXT("texttexttexttext");
    const EQTextEncoding INPUT_ENCODING = EQTextEncoding::E_ASCII;
    const pointer_uint_q BATCH_SIZE = 0;
    QMemoryStream<> stream(1);
    QTextStreamWriter< QMemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer << INPUT_TEXT;
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
    QMemoryStream<> stream(1U);
    QTextStreamWriter< QMemoryStream<> > reader(stream, INPUT_ENCODING);
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


// End - Test Suite: QTextStreamWriter
QTEST_SUITE_END()
