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

#include "QMemoryStream.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::System::IO::QMemoryStream;

using Kinesis::QuimeraEngine::Common::DataTypes::u64_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u32_q;
using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;


QTEST_SUITE_BEGIN( QMemoryStream_TestSuite )

/// <summary>
/// Checks that the stream is correctly constructed when using a common buffer size.
/// </summary>
QTEST_CASE ( Constructor1_ItIsCorrectlyConstructedWhenUsingCommonSize_Test )
{
    // [Preparation]
    const pointer_uint_q BUFFER_SIZE = 4U;
    const pointer_uint_q EXPECTED_LENGTH = 0;

    // [Execution]
    QMemoryStream<> stream(BUFFER_SIZE);
    
    // [Verification]
    pointer_uint_q uLength = stream.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMemoryStream<> stream(INPUT_SIZE);
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
/// Checks that the stream is correctly constructed when using a common buffer size and a valid buffer.
/// </summary>
QTEST_CASE ( Constructor2_ItIsCorrectlyConstructedWhenUsingCommonSizeAndValidBuffer_Test )
{
    // [Preparation]
    const pointer_uint_q BUFFER_SIZE = sizeof(u32_q);
    const u32_q CONTENT = 0x01020304;
    const pointer_uint_q EXPECTED_LENGTH = BUFFER_SIZE;

    // [Execution]
    QMemoryStream<> stream(&CONTENT, BUFFER_SIZE);
    
    // [Verification]
    pointer_uint_q uLength = stream.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 0;
    const u32_q CONTENT = 0x01020304;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMemoryStream<> stream(&CONTENT, INPUT_SIZE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the buffer is null.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenBufferIsNull_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    void* pBuffer = null_q;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QMemoryStream<> stream(pBuffer, INPUT_SIZE);
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
/// Checks that the stream is correctly copied.
/// </summary>
QTEST_CASE ( Constructor3_ItIsCorrectlyCopied_Test )
{
    // [Preparation]
    const pointer_uint_q BUFFER_SIZE = 8U;
    const u32_q CONTENT = 1234;
    QMemoryStream<> originalStream(BUFFER_SIZE);
    originalStream.Write(&CONTENT, 0, sizeof(CONTENT));

    // [Execution]
    QMemoryStream<> stream(originalStream);
    
    // [Verification]
    pointer_uint_q uLength = stream.GetLength();
    u32_q nContent = 0;
    stream.Read(&nContent, 0, sizeof(CONTENT));

    BOOST_CHECK_EQUAL(uLength, sizeof(CONTENT));
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

/// <summary>
/// Checks that the stream is correctly copied when it is empty.
/// </summary>
QTEST_CASE ( Constructor3_ItIsCorrectlyCopiedWhenInputIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q BUFFER_SIZE = 8U;
    const pointer_uint_q EXPECTED_LENGTH = 0;
    QMemoryStream<> originalStream(BUFFER_SIZE);

    // [Execution]
    QMemoryStream<> stream(originalStream);
    
    // [Verification]
    pointer_uint_q uLength = stream.GetLength();

    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that output offset affects the result.
/// </summary>
QTEST_CASE ( Read_OutputOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_q CONTENT = 0x01020304;
    const pointer_uint_q OFFSET1 = 1U;
    const pointer_uint_q OFFSET2 = 2U;
    const u32_q EXPECTED_CONTENT_OFFSET1 = 0x00030400;
    const u32_q EXPECTED_CONTENT_OFFSET2 = 0x03040000;
    const pointer_uint_q READ_BLOCK_SIZE = 2U;
    const pointer_uint_q BUFFER_SIZE = 4U;
    QMemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_q nContentOffset1 = 0;
    stream.Read(&nContentOffset1, OFFSET1, READ_BLOCK_SIZE);

    u32_q nContentOffset2 = 0;
    stream.SetPosition(0); // To read from the beginning again
    stream.Read(&nContentOffset2, OFFSET2, READ_BLOCK_SIZE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that the complete stream can be read.
/// </summary>
QTEST_CASE ( Read_TheCompleteStreamCanBeRead_Test )
{
    // [Preparation]
    const u32_q CONTENT = 0x01020304;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = 4U;
    const pointer_uint_q READ_BLOCK_SIZE = BUFFER_SIZE;
    QMemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_q nContent = 0;
    stream.Read(&nContent, OFFSET, READ_BLOCK_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

/// <summary>
/// Checks that the read pointer is moved forward after every read operation.
/// </summary>
QTEST_CASE ( Read_InternalReadPointerIsMovedForwardAutomatically_Test )
{
    // [Preparation]
    const u32_q CONTENT = 0x01020304;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = 4U;
    const pointer_uint_q READ_BLOCK_SIZE = 2U;
    QMemoryStream<> stream(&CONTENT, BUFFER_SIZE);

    // [Execution]
    u32_q nContent = 0;
    stream.Read(&nContent, OFFSET, READ_BLOCK_SIZE);
    stream.Read(&nContent, OFFSET + READ_BLOCK_SIZE, READ_BLOCK_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(nContent, CONTENT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the output buffer is null.
/// </summary>
QTEST_CASE ( Read_AssertionFailsWhenOutputBufferIsNull_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    void* pBuffer = null_q;
    QMemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(pBuffer, 0, INPUT_SIZE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the output size equals zero.
/// </summary>
QTEST_CASE ( Read_AssertionFailsWhenOutputSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 0;
    u32_q nBuffer;
    QMemoryStream<> stream(4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(&nBuffer, 0, INPUT_SIZE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when trying to read out of the buffer.
/// </summary>
QTEST_CASE ( Read_AssertionFailsWhenTryingToReadOutOfBounds_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const pointer_uint_q OFFSET = 2U;
    u64_q uBuffer;
    u32_q* pBuffer = rcast_q(&uBuffer, u32_q*);
    QMemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Read(pBuffer, OFFSET, INPUT_SIZE);
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
/// Checks that input offset affects the result.
/// </summary>
QTEST_CASE ( Write_InputOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_q NEW_CONTENT = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q OFFSET1 = 1U;
    const pointer_uint_q OFFSET2 = 2U;
    const u32_q EXPECTED_CONTENT_OFFSET1 = 0x00000203;
    const u32_q EXPECTED_CONTENT_OFFSET2 = 0x00000102;
    const pointer_uint_q WRITE_BLOCK_SIZE = 2U;
    const pointer_uint_q BUFFER_SIZE = 4U;
    QMemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream1.Write(&NEW_CONTENT, OFFSET1, WRITE_BLOCK_SIZE);
    stream2.Write(&NEW_CONTENT, OFFSET2, WRITE_BLOCK_SIZE);
    
    // [Verification]
    u32_q nContentOffset1 = 0;
    u32_q nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, BUFFER_SIZE);
    stream2.Read(&nContentOffset2, 0, BUFFER_SIZE);
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that it is possible to write blocks that are bigger than the buffer's size.
/// </summary>
QTEST_CASE ( Write_ItIsPossibleToWriteABlockBiggerThanBufferSize_Test )
{
    // [Preparation]
    const u64_q EXPECTED_CONTENT = 0x0102030405060708;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = 4U;
    const pointer_uint_q WRITE_BLOCK_SIZE = sizeof(u64_q);
    QMemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&EXPECTED_CONTENT, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    u64_q nContent = 0;
    stream.SetPosition(0);
    stream.Read(&nContent, 0, sizeof(u64_q));
    BOOST_CHECK_EQUAL(nContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that the buffer grows as more memory is necessary.
/// </summary>
QTEST_CASE ( Write_TheBufferGrowsAsMoreMemoryIsNecessary_Test )
{
    // [Preparation]
    const u32_q CONTENT_TO_WRITE1 = 0x05060708;
    const u32_q CONTENT_TO_WRITE2 = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q ORIGINAL_BUFFER_SIZE = sizeof(u32_q);
    const pointer_uint_q WRITE_BLOCK_SIZE = sizeof(u32_q);
    QMemoryStream<> stream(&ORIGINAL_CONTENT, ORIGINAL_BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    pointer_uint_q uBufferLength = stream.GetLength();
    BOOST_CHECK(uBufferLength > ORIGINAL_BUFFER_SIZE);
}

/// <summary>
/// Checks that the internal write pointer is automatically moved forward on every write operation.
/// </summary>
QTEST_CASE ( Write_TheInternalPointerIsMovedAutomatically_Test )
{
    // [Preparation]
    const u64_q EXPECTED_CONTENT = 0x0102030405060708;
    const u32_q CONTENT_TO_WRITE1 = 0x05060708;
    const u32_q CONTENT_TO_WRITE2 = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(u32_q);
    const pointer_uint_q WRITE_BLOCK_SIZE = sizeof(u32_q);
    QMemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    u64_q nContent = 0;
    stream.SetPosition(0);
    stream.Read(&nContent, 0, sizeof(u64_q));
    BOOST_CHECK_EQUAL(nContent, EXPECTED_CONTENT);
}

/// <summary>
/// Checks that blocks are correctly written when they occupy both allocated and non-allocated memory.
/// </summary>
QTEST_CASE ( Write_ItWorksWhenWrittenBlockOccupiesBothAllocatedAndNonAllocatedMemory_Test )
{
    // [Preparation]
    const u32_q CONTENT_TO_WRITE1 = 0x05060708;
    const u32_q CONTENT_TO_WRITE2 = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(u32_q);
    const pointer_uint_q WRITE_BLOCK_SIZE = sizeof(u32_q);
    QMemoryStream<> stream(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    stream.Write(&CONTENT_TO_WRITE1, OFFSET, WRITE_BLOCK_SIZE);
    stream.SetPosition(2U);
    stream.Write(&CONTENT_TO_WRITE2, OFFSET, WRITE_BLOCK_SIZE);

    // [Verification]
    pointer_uint_q uBufferLength = stream.GetLength();
    BOOST_CHECK(uBufferLength > BUFFER_SIZE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
QTEST_CASE ( Write_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    void* pBuffer = null_q;
    QMemoryStream<> stream(INPUT_SIZE);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Write(pBuffer, 0, INPUT_SIZE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input size equals zero.
/// </summary>
QTEST_CASE ( Write_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 0;
    u32_q nBuffer;
    QMemoryStream<> stream(4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.Write(&nBuffer, 0, INPUT_SIZE);
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
/// Checks that the source stream's offset affects the result.
/// </summary>
QTEST_CASE ( CopyTo_SourceOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_q NEW_CONTENT = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q OFFSET1 = 1U;
    const pointer_uint_q OFFSET2 = 2U;
    const u32_q EXPECTED_CONTENT_OFFSET1 = 0x00020304;
    const u32_q EXPECTED_CONTENT_OFFSET2 = 0x00000304;
    const pointer_uint_q BUFFER_SIZE = 4U;
    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream1, OFFSET1, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET1);
    sourceStream.CopyTo(stream2, OFFSET2, DESTINATION_OFFSET, BUFFER_SIZE - OFFSET2);
    
    // [Verification]
    u32_q nContentOffset1 = 0;
    u32_q nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, sizeof(u32_q));
    stream2.Read(&nContentOffset2, 0, sizeof(u32_q));
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that the destination stream's offset affects the result.
/// </summary>
QTEST_CASE ( CopyTo_DestinationOffsetAffectsTheResult_Test )
{
    // [Preparation]
    const u32_q NEW_CONTENT = 0x01020304;
    const u32_q ORIGINAL_CONTENT = 0;
    const pointer_uint_q SOURCE_OFFSET = 0;
    const pointer_uint_q OFFSET1 = 1U;
    const pointer_uint_q OFFSET2 = 2U;
    const u32_q EXPECTED_CONTENT_OFFSET1 = 0x02030400;
    const u32_q EXPECTED_CONTENT_OFFSET2 = 0x03040000;
    const pointer_uint_q BUFFER_SIZE = 4U;
    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream1(&ORIGINAL_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream2(&ORIGINAL_CONTENT, BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream1, SOURCE_OFFSET, OFFSET1, BUFFER_SIZE);
    sourceStream.CopyTo(stream2, SOURCE_OFFSET, OFFSET2, BUFFER_SIZE);
    
    // [Verification]
    u32_q nContentOffset1 = 0;
    u32_q nContentOffset2 = 0;
    stream1.SetPosition(0);
    stream2.SetPosition(0);
    stream1.Read(&nContentOffset1, 0, sizeof(u32_q));
    stream2.Read(&nContentOffset2, 0, sizeof(u32_q));
    BOOST_CHECK_EQUAL(nContentOffset1, EXPECTED_CONTENT_OFFSET1);
    BOOST_CHECK_EQUAL(nContentOffset2, EXPECTED_CONTENT_OFFSET2);
}

/// <summary>
/// Checks that streams can be completely copied.
/// </summary>
QTEST_CASE ( CopyTo_StreamCanBeCompletelyCopied_Test )
{
    // [Preparation]
    u8_q NEW_CONTENT[10000];
    memset(NEW_CONTENT, 0x01, sizeof(NEW_CONTENT));

    const bool ARE_EQUAL = true;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q SOURCE_OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream(4U);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    u8_q arContent[10000];
    stream.SetPosition(0);
    stream.Read(arContent, 0, sizeof(NEW_CONTENT));
    bool bAreEqual = memcmp(arContent, NEW_CONTENT, sizeof(NEW_CONTENT)) == 0;

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the destination stream grows when it is necessary.
/// </summary>
QTEST_CASE ( CopyTo_DestinationStreamGrowsWhenNecessary_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q SOURCE_OFFSET = 0;
    const pointer_uint_q SOURCE_BUFFER_SIZE = sizeof(NEW_CONTENT);
    const pointer_uint_q DESTINATION_BUFFER_SIZE = 4U;

    QMemoryStream<> sourceStream(&NEW_CONTENT, SOURCE_BUFFER_SIZE);
    QMemoryStream<> stream(DESTINATION_BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, SOURCE_BUFFER_SIZE);
    
    // [Verification]
    pointer_uint_q uDestinationLength = stream.GetLength();
    BOOST_CHECK(uDestinationLength > DESTINATION_BUFFER_SIZE);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved forward.
/// </summary>
QTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q SOURCE_OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);
    const pointer_uint_q EXPECTED_POSITION = BUFFER_SIZE;

    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    sourceStream.GetCurrentPointer();

    QMemoryStream<> stream(BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    pointer_uint_q uPosition = sourceStream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that the internal pointer of the destination stream is moved forward.
/// </summary>
QTEST_CASE ( CopyTo_DestinationStreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q SOURCE_OFFSET = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    QMemoryStream<> stream(BUFFER_SIZE);
    void* pOriginalPointer = stream.GetCurrentPointer();

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, BUFFER_SIZE);
    
    // [Verification]
    void* pCurrentPointer = stream.GetCurrentPointer();
    BOOST_CHECK_NE(pOriginalPointer, pCurrentPointer);
}

/// <summary>
/// Checks that the internal pointer of the source stream is moved to the source offset when the number of bytes to copy is zero.
/// </summary>
QTEST_CASE ( CopyTo_SourceStreamInternalPointerIsMovedToOffsetWhenNumberOfBytesToCopyEqualsZero_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q DESTINATION_OFFSET = 0;
    const pointer_uint_q SOURCE_OFFSET = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);
    const pointer_uint_q EXPECTED_POSITION = SOURCE_OFFSET;
    const pointer_uint_q NUMBER_OF_BYTES = 0;

    QMemoryStream<> sourceStream(&NEW_CONTENT, BUFFER_SIZE);
    sourceStream.GetCurrentPointer();

    QMemoryStream<> stream(BUFFER_SIZE);

    // [Execution]
    sourceStream.CopyTo(stream, SOURCE_OFFSET, DESTINATION_OFFSET, NUMBER_OF_BYTES);
    
    // [Verification]
    pointer_uint_q uPosition = sourceStream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the source stream's offset is out of bounds.
/// </summary>
QTEST_CASE ( CopyTo_AssertionFailsWhenSourceOffsetIsOutOfBounds_Test )
{
    // [Preparation]
    const pointer_uint_q SOURCE_OFFSET = 5U;
    u32_q nBuffer;
    QMemoryStream<> sourceStream(&nBuffer, 4U);
    QMemoryStream<> destinationStream(&nBuffer, 4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, 4U);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the destination stream's offset is out of bounds.
/// </summary>
QTEST_CASE ( CopyTo_AssertionFailsWhenDestinationOffsetIsOutOfBounds_Test )
{
    // [Preparation]
    const pointer_uint_q DESTINATION_OFFSET = 5U;
    u32_q nBuffer;
    QMemoryStream<> sourceStream(&nBuffer, 4U);
    QMemoryStream<> destinationStream(&nBuffer, 4U);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, 0, DESTINATION_OFFSET, 4U);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the number of bytes to copy exceeds the limits of the source stream.
/// </summary>
QTEST_CASE ( CopyTo_AssertionFailsWhenNumberOfBytesExceedsSourceStreamBounds_Test )
{
    // [Preparation]
    const pointer_uint_q SOURCE_OFFSET = 2U;
    u32_q nBuffer;
    QMemoryStream<> sourceStream(&nBuffer, 4U);
    QMemoryStream<> destinationStream(&nBuffer, 4U);
    const pointer_uint_q NUMBER_OF_BYTES = 3U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, NUMBER_OF_BYTES);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
QTEST_CASE ( CopyTo_AssertionFailsWhenBatchSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q SOURCE_OFFSET = 2U;
    u32_q nBuffer;
    QMemoryStream<> sourceStream(&nBuffer, 4U);
    QMemoryStream<> destinationStream(&nBuffer, 4U);
    const pointer_uint_q NUMBER_OF_BYTES = 2U;
    const pointer_uint_q BATCH_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceStream.CopyTo(destinationStream, SOURCE_OFFSET, 0, NUMBER_OF_BYTES, BATCH_SIZE);
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
/// It is not necessary to test this method since it does nothing.
/// </summary>
QTEST_CASE ( Flush_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it does nothing");
}

/// <summary>
/// Checks that the internal pointer is correctly moved.
/// </summary>
QTEST_CASE ( MoveBackward_PointerIsCorrectlyMoved_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(1);
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK(uCurrentPointer < uOriginalPointer);
}

/// <summary>
/// Checks that the internal pointer is not moved when the amount of movement is zero.
/// </summary>
QTEST_CASE ( MoveBackward_PointerIsNotMovedWhenMovementIsZero_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(1);
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the internal pointer points to the first position of the buffer.
/// </summary>
QTEST_CASE ( MoveBackward_AssertionFailsWhenPointerPointsToFirstPosition_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);
    const bool ASSERTION_FAILED = true;

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.MoveBackward(MOVEMENT);
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
/// Checks that the pointer does not moves when it points to the first position of the buffer.
/// </summary>
QTEST_CASE ( MoveBackward_PointerIsNotMovedWhenPointerPointsToFirstPosition_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveBackward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#endif

/// <summary>
/// Checks that the internal pointer is correctly moved.
/// </summary>
QTEST_CASE ( MoveForward_PointerIsCorrectlyMoved_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK(uCurrentPointer > uOriginalPointer);
}

/// <summary>
/// Checks that the internal pointer is not moved when the amount of movement is zero.
/// </summary>
QTEST_CASE ( MoveForward_PointerIsNotMovedWhenMovementIsZero_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 0;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the internal pointer points outside of the buffer.
/// </summary>
QTEST_CASE ( MoveForward_AssertionFailsWhenPointerPointsOutsideOfTheBuffer_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);
    const bool ASSERTION_FAILED = true;

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(sizeof(NEW_CONTENT));

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.MoveForward(MOVEMENT);
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
/// Checks that the pointer does not moves when the internal pointer points outside of the buffer.
/// </summary>
QTEST_CASE ( MoveForward_PointerIsNotMovedWhenPointerPointsOutsideOfTheBuffer_Test )
{
    // [Preparation]
    const u64_q NEW_CONTENT = 0x0102030405060708;
    const pointer_uint_q MOVEMENT = 1U;
    const pointer_uint_q BUFFER_SIZE = sizeof(NEW_CONTENT);

    QMemoryStream<> stream(&NEW_CONTENT, BUFFER_SIZE);
    stream.SetPosition(sizeof(NEW_CONTENT));
    pointer_uint_q uOriginalPointer = stream.GetPosition();

    // [Execution]
    stream.MoveForward(MOVEMENT);
    
    // [Verification]
    pointer_uint_q uCurrentPointer = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPointer, uOriginalPointer);
}

#endif

/// <summary>
/// Checks that it returns zero when the stream is empty.
/// </summary>
QTEST_CASE ( GetLength_ReturnsZeroWhenStreamIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_LENGTH = 0;
    QMemoryStream<> stream(4U);

    // [Execution]
    pointer_uint_q uLength = stream.GetLength();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns expected length when the stream is not empty.
/// </summary>
QTEST_CASE ( GetLength_ReturnsExpectedLengthWhenStreamIsNotEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_LENGTH = 4U;
    const u32_q CONTENT = 0;
    QMemoryStream<> stream(&CONTENT, EXPECTED_LENGTH);

    // [Execution]
    pointer_uint_q uLength = stream.GetLength();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetPosition_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that the internal pointer is correctly moved to the given position.
/// </summary>
QTEST_CASE ( SetPosition_ThePointerIsCorrectlyMovedToTheGivenPosition_Test )
{
    // [Preparation]
    const pointer_uint_q EXPECTED_POSITION = 4U;
    const u32_q CONTENT = 0;
    QMemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    stream.SetPosition(EXPECTED_POSITION);
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the internal pointer is not moved when the input position is out of bounds.
/// </summary>
QTEST_CASE ( SetPosition_AssertionFailsWhenTheInputPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q NEW_POSITION = 5U;
    const u32_q CONTENT = 0;
    QMemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stream.SetPosition(NEW_POSITION);
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
/// Checks that the internal pointer is not moved when the input position is out of bounds.
/// </summary>
QTEST_CASE ( SetPosition_ThePointerIsNotMovedWhenTheInputPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const pointer_uint_q ORIGINAL_POSITION = 0;
    const pointer_uint_q NEW_POSITION = 5U;
    const u32_q CONTENT = 0;
    QMemoryStream<> stream(&CONTENT, sizeof(CONTENT));

    // [Execution]
    stream.SetPosition(NEW_POSITION);
    
    // [Verification]
    pointer_uint_q uPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uPosition, ORIGINAL_POSITION);
}

#endif

/// <summary>
/// Checks that the returned address depends on the position of the internal pointer.
/// </summary>
QTEST_CASE ( GetCurrentPointer_ReturnedAddressDespendsOnInternalPointerPosition_Test )
{
    // [Preparation]
    const pointer_uint_q POSITION = 4U;
    const u32_q CONTENT = 0;
    QMemoryStream<> stream(&CONTENT, sizeof(CONTENT));
    void* pOriginalPointer = stream.GetCurrentPointer();
    stream.SetPosition(POSITION);

    // [Execution]
    void* pCurrentPointer = stream.GetCurrentPointer();
    
    // [Verification]
    pointer_uint_q uOriginalPosition = rcast_q(pOriginalPointer, pointer_uint_q);
    pointer_uint_q uCurrentPosition = rcast_q(pCurrentPointer, pointer_uint_q);
    pointer_uint_q uActualPosition = uCurrentPosition - uOriginalPosition;
    BOOST_CHECK_EQUAL(uActualPosition, POSITION);
}

// End - Test Suite: QMemoryStream
QTEST_SUITE_END()
