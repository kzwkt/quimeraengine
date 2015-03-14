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

#include "QCallTrace.h"

using Kinesis::QuimeraEngine::System::Diagnosis::QCallTrace;
using Kinesis::QuimeraEngine::System::Diagnosis::QArgumentTrace;


QTEST_SUITE_BEGIN( QCallTrace_TestSuite )

/// <summary>
/// Checks that all the parameters are correctly stored
/// </summary>
QTEST_CASE ( Constructor1_ParametersAreCorrectlyStored_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace EXPECTED_ARGUMENTS[] = { QArgumentTrace(int(4)) };
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 1;

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments()->GetTypeName() == EXPECTED_ARGUMENTS->GetTypeName() &&
                                    callTrace.GetArguments()->GetValue() == EXPECTED_ARGUMENTS->GetValue();
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
}

/// <summary>
/// Checks that all the parameters are correctly stored when the input argument array is null.
/// </summary>
QTEST_CASE ( Constructor1_ParametersAreCorrectlyStoredWhenPassingNullArgumentArray_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace* EXPECTED_ARGUMENTS = null_q;
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 0;

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments() == EXPECTED_ARGUMENTS;
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
}

/// <summary>
/// Checks that all the parameters are correctly stored
/// </summary>
QTEST_CASE ( Constructor2_ParametersAreCorrectlyStored_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace EXPECTED_ARGUMENTS[] = { QArgumentTrace(int(4)) };
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 1;
    const char EXPECTED_CLASS_NAME[] = "MyClass";

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT, EXPECTED_CLASS_NAME);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments()->GetTypeName() == EXPECTED_ARGUMENTS->GetTypeName() &&
                                    callTrace.GetArguments()->GetValue() == EXPECTED_ARGUMENTS->GetValue();
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    bool bClassNameIsWhatExpected = strcmp(callTrace.GetClassName(), EXPECTED_CLASS_NAME) == 0;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
    BOOST_CHECK(bClassNameIsWhatExpected);
}

/// <summary>
/// Checks that all the parameters are correctly stored when the input argument array is null.
/// </summary>
QTEST_CASE ( Constructor2_ParametersAreCorrectlyStoredWhenPassingNullArgumentArray_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace* EXPECTED_ARGUMENTS = null_q;
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 0;
    const char EXPECTED_CLASS_NAME[] = "MyClass";

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT, EXPECTED_CLASS_NAME);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments() == EXPECTED_ARGUMENTS;
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    bool bClassNameIsWhatExpected = strcmp(callTrace.GetClassName(), EXPECTED_CLASS_NAME) == 0;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
    BOOST_CHECK(bClassNameIsWhatExpected);
}

/// <summary>
/// Checks that all the parameters are correctly stored
/// </summary>
QTEST_CASE ( Constructor3_ParametersAreCorrectlyStored_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace EXPECTED_ARGUMENTS[] = { QArgumentTrace(int(4)) };
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 1;
    const char EXPECTED_CLASS_NAME[] = "MyClass";
    const string_q EXPECTED_OBJECT_STATE("ObjectState");

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT, EXPECTED_CLASS_NAME, EXPECTED_OBJECT_STATE);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments()->GetTypeName() == EXPECTED_ARGUMENTS->GetTypeName() &&
                                    callTrace.GetArguments()->GetValue() == EXPECTED_ARGUMENTS->GetValue();
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    bool bClassNameIsWhatExpected = strcmp(callTrace.GetClassName(), EXPECTED_CLASS_NAME) == 0;
    bool bObjectStateIsWhatExpected = callTrace.GetObjectState() == EXPECTED_OBJECT_STATE;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
    BOOST_CHECK(bClassNameIsWhatExpected);
    BOOST_CHECK(bObjectStateIsWhatExpected);
}

/// <summary>
/// Checks that all the parameters are correctly stored when the input argument array is null.
/// </summary>
QTEST_CASE ( Constructor3_ParametersAreCorrectlyStoredWhenPassingNullArgumentArray_Test )
{
    // [Preparation]
    const char EXPECTED_FUNCTION_SIGNATURE[] = "void FunctionSignature(const int nValue)";
    const QArgumentTrace* EXPECTED_ARGUMENTS = null_q;
    const unsigned int EXPECTED_ARGUMENTS_COUNT = 0;
    const char EXPECTED_CLASS_NAME[] = "MyClass";
    const string_q EXPECTED_OBJECT_STATE("ObjectState");

    // [Execution]
    QCallTrace callTrace(EXPECTED_FUNCTION_SIGNATURE, EXPECTED_ARGUMENTS, EXPECTED_ARGUMENTS_COUNT, EXPECTED_CLASS_NAME, EXPECTED_OBJECT_STATE);
    
    // [Verification]
    bool bFunctionSignatureIsWhatExpected = strcmp(callTrace.GetFunctionSignature(), EXPECTED_FUNCTION_SIGNATURE) == 0;
    bool bArgumentsIsWhatExpected = callTrace.GetArguments() == EXPECTED_ARGUMENTS;
    bool bArgumentsCountIsWhatExpected = callTrace.GetArgumentsCount() == EXPECTED_ARGUMENTS_COUNT;
    bool bClassNameIsWhatExpected = strcmp(callTrace.GetClassName(), EXPECTED_CLASS_NAME) == 0;
    bool bObjectStateIsWhatExpected = callTrace.GetObjectState() == EXPECTED_OBJECT_STATE;
    BOOST_CHECK(bFunctionSignatureIsWhatExpected);
    BOOST_CHECK(bArgumentsIsWhatExpected);
    BOOST_CHECK(bArgumentsCountIsWhatExpected);
    BOOST_CHECK(bClassNameIsWhatExpected);
    BOOST_CHECK(bObjectStateIsWhatExpected);
}

// End - Test Suite: QCallTrace
QTEST_SUITE_END()
