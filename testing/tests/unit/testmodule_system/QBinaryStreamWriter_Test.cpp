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

#include "QBinaryStreamWriter.h"
#include "QMemoryStream.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::System::IO::QBinaryStreamWriter;
using Kinesis::QuimeraEngine::System::IO::QMemoryStream;


QTEST_SUITE_BEGIN( QBinaryStreamWriter_TestSuite )

/// <summary>
/// Checks that the stream is correctly stored.
/// </summary>
QTEST_CASE ( Constructor_StreamIsCorrectlyStored_Test )
{
    // [Preparation]
    QMemoryStream<> memoryStream(1U);

    // [Execution]
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);
    
    // [Verification]
    bool bStreamIsStoredCorrectly = &memoryStream == &writer.GetStream();
    BOOST_CHECK(bStreamIsStoredCorrectly);
}

/// <summary>
/// Checks that the buffer is correctly written.
/// </summary>
QTEST_CASE ( WriteBytes_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);

    // [Execution]
    writer.WriteBytes(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
QTEST_CASE ( WriteBytes_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);
    const pointer_uint_q ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer.WriteBytes(&EXPECTED_VALUE, sizeof(EXPECTED_VALUE));
    
    // [Verification]
    pointer_uint_q uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
QTEST_CASE ( WriteBytes_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    QMemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    QBinaryStreamWriter< QMemoryStream<> > writer(stream);
    
    const bool ASSERTION_FAILED = true;
    void* pNullPointer = null_q;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        writer.WriteBytes(pNullPointer, sizeof(unsigned int));
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input buffer size equals zero.
/// </summary>
QTEST_CASE ( WriteBytes_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const unsigned int STREAM_VALUE = 0xFEDCBA98;
    QMemoryStream<> stream(&STREAM_VALUE, sizeof(STREAM_VALUE));
    QBinaryStreamWriter< QMemoryStream<> > writer(stream);
    
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q ZERO_SIZE = 0;

    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        unsigned int uValue;
        writer.WriteBytes(&uValue, ZERO_SIZE);
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
/// Checks that the instance is correctly written.
/// </summary>
QTEST_CASE ( Write_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);

    // [Execution]
    writer.Write(EXPECTED_VALUE);
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
QTEST_CASE ( Write_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);
    const pointer_uint_q ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer.Write(EXPECTED_VALUE);
    
    // [Verification]
    pointer_uint_q uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that the instance is correctly written.
/// </summary>
QTEST_CASE ( OperatorLeftShift_BufferIsCorrectlyWritten_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);

    // [Execution]
    writer << EXPECTED_VALUE;
    
    // [Verification]
    int nValue = 0;
    memoryStream.SetPosition(0);
    memoryStream.Read(&nValue, 0, sizeof(nValue));
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the internal pointer of the stream is moved forward.
/// </summary>
QTEST_CASE ( OperatorLeftShift_StreamInternalPointerIsMovedForward_Test )
{
    // [Preparation]
    const int EXPECTED_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);
    const pointer_uint_q ORIGINAL_POSITION = memoryStream.GetPosition();

    // [Execution]
    writer << EXPECTED_VALUE;
    
    // [Verification]
    pointer_uint_q uPosition = memoryStream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that it returns a reference to the same instance of the writer.
/// </summary>
QTEST_CASE ( OperatorLeftShift_ReturnsReferenceToSameInstance_Test )
{
    // [Preparation]
    const int INPUT_VALUE = 123456;
    QMemoryStream<> memoryStream(4U);
    QBinaryStreamWriter<QMemoryStream<> > writer(memoryStream);
    QBinaryStreamWriter<QMemoryStream<> >* EXPECTED_POINTER = &writer;

    // [Execution]
    QBinaryStreamWriter<QMemoryStream<> >* pWriter = &(writer << INPUT_VALUE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(pWriter, EXPECTED_POINTER);
}

/// <summary>
/// It is not necessary to test this method since it is just calls another method and there are no inputs nor outputs.
/// </summary>
QTEST_CASE ( Flush_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just calls another method and there are no inputs nor outputs");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
QTEST_CASE ( GetStream_NotNecessaryToTest_Test )
{
    BOOST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: QBinaryStreamWriter
QTEST_SUITE_END()
