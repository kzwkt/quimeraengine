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

#include "QCallStackTrace.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QCallStackTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::Common::DataTypes::i8_q;


QTEST_SUITE_BEGIN( QCallStackTrace_TestSuite )

/// <summary>
/// Checks that the input parameters are correctly stored
/// </summary>
QTEST_CASE ( Constructor_InputParametersAreCorrectlyStored_Test )
{
    // [Preparation]
    const string_q EXPECTED_THREAD_ID("Thread(XXXX)");

    // [Execution]
    QCallStackTrace callStackTrace(EXPECTED_THREAD_ID);
    
    // [Verification]
    string_q strThreadId = callStackTrace.GetThreadId();
    BOOST_CHECK(strThreadId == EXPECTED_THREAD_ID);
}

/// <summary>
/// Checks that elements can be added to empty stacks.
/// </summary>
QTEST_CASE ( Push_ElementIsCorrectlyPushedToEmptyStack_Test )
{
    // [Preparation]
    QCallStackTrace emptyStack("Id");
    const char* szFunctionName = "void Function()";
    QCallTrace trace(szFunctionName, null_q, 0);

    // [Execution]
    emptyStack.Push(trace);

    // [Verification]
    const char* szStoredValue = emptyStack.GetTrace(0).GetFunctionSignature();
    BOOST_CHECK(string_q(szStoredValue) == string_q(szFunctionName));
}

/// <summary>
/// Checks that elements are correctly added at the end of a common stack.
/// </summary>
QTEST_CASE ( Push_ElementIsCorrectlyPushedAtTheEnd_Test )
{
    // [Preparation]
    QCallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const QCallTrace EXPECTED_TRACE(szFunctionName, null_q, 0);
    const QCallTrace TRACE("", null_q, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);

    // [Execution]
    callStack.Push(EXPECTED_TRACE);

    // [Verification]
    const char* szStoredValue = callStack.GetTrace(callStack.GetCount() - 1U).GetFunctionSignature();
    BOOST_CHECK(string_q(szStoredValue) == string_q(szFunctionName));
}

/// <summary>
/// Checks that the count of elements of the stack is increased after an element is added.
/// </summary>
QTEST_CASE ( Push_CountIsIncreasedAfterPushingAnElement_Test )
{
    // [Preparation]
    QCallStackTrace callStack("Id");
    const QCallTrace TRACE("", null_q, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);
    const pointer_uint_q ORIGINAL_COUNT = callStack.GetCount();

    // [Execution]
    callStack.Push(TRACE);

    // [Verification]
    pointer_uint_q uCount = callStack.GetCount();
    BOOST_CHECK_GT(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that elements are correctly removed from the last position of the stack.
/// </summary>
QTEST_CASE ( Pop_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    QCallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const QCallTrace EXPECTED_TRACE(szFunctionName, null_q, 0);
    const QCallTrace TRACE("", null_q, 0);
    callStack.Push(TRACE);
    callStack.Push(EXPECTED_TRACE);
    callStack.Push(TRACE);

    // [Execution]
    callStack.Pop();

    // [Verification]
    const char* szStoredValue = callStack.GetTrace(callStack.GetCount() - 1U).GetFunctionSignature();
    BOOST_CHECK(string_q(szStoredValue) == string_q(szFunctionName));
}

/// <sumary>
/// Checks if it gets the correct value at supplied position.
/// </sumary>
QTEST_CASE( GetTrace_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    QCallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const QCallTrace EXPECTED_TRACE(szFunctionName, null_q, 0);
    const QCallTrace TRACE("", null_q, 0);
    callStack.Push(TRACE);
    callStack.Push(EXPECTED_TRACE);
    callStack.Push(TRACE);
    const pointer_uint_q INPUT_INDEX = 1U;

    // [Execution]
    QCallTrace trace = callStack.GetTrace(INPUT_INDEX);

    // [Verification]
    const char* szStoredValue = trace.GetFunctionSignature();
    BOOST_CHECK(string_q(szStoredValue) == string_q(szFunctionName));
}

/// <sumary>
/// Returns the number of elements in the array.
/// </sumary>
QTEST_CASE( GetCount_ReturnsNumberOfElementsInTheStack_Test )
{
    // [Preparation]
    QCallStackTrace callStack("Id");
    const pointer_uint_q EXPECTED_COUNT = 3U;
    const QCallTrace TRACE("", null_q, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);
    callStack.Push(TRACE);

    // [Execution]
    pointer_uint_q uCount = callStack.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

// End - Test Suite: QCallStackTrace
QTEST_SUITE_END()
