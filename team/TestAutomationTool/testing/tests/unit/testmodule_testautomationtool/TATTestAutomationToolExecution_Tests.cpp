//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATTestAutomationToolExecution.h"
#include "TATTestAutomationToolExecutionWhiteBox.h"
#include "TATLoggerMock.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionWhiteBox;

QTEST_SUITE_BEGIN( TATTestAutomationToolExecution_TestSuite )

/// <summary>
/// Checks that default values have not changed since last execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::ITATLogger;
    using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

    // Preparation
    ITATLogger* EXPECTED_LOGGER = null_t;
    std::map<wxString, TATCompilerInfo> EXPECTED_COMPILERS_INFO;
    std::list<wxString> EXPECTED_COMPILATION_CONFIGURATIONS;
    wxString EXPECTED_CONFIGURATION_FILE_PATH("");
    std::map< wxString, std::map<wxString, wxString> > EXPECTED_FLAG_COMBINATIONS;

	// Execution
    TATTestAutomationToolExecution testExecution;
    
    // Verification
    BOOST_CHECK_EQUAL(testExecution.GetLogger(), EXPECTED_LOGGER);
    BOOST_CHECK(testExecution.GetCompilationConfigurations() == EXPECTED_COMPILATION_CONFIGURATIONS);
    BOOST_CHECK(testExecution.GetCompilerInfos() == EXPECTED_COMPILERS_INFO);
    BOOST_CHECK_EQUAL(testExecution.GetConfigurationFilePath(), EXPECTED_CONFIGURATION_FILE_PATH);
    BOOST_CHECK(testExecution.GetFlagCombinations() == EXPECTED_FLAG_COMBINATIONS);
}

/// <summary>
/// Checks if any error occurs during destruction.
/// </summary>
QTEST_CASE ( Destroy_NoErrorOccurred_Test )
{
    // Preparation
    const bool NO_ERROR_OCURRED = true;
    
    TATTestAutomationToolExecutionWhiteBox* TESTAUTOMATIONTOOL_EXECUTION = new TATTestAutomationToolExecutionWhiteBox();

	// Execution
    bool bNoErrorOcurred = true;

    try
    {
        delete TESTAUTOMATIONTOOL_EXECUTION;
    }
    catch(...) // TODO [Thund]: A concrete exception type should be caught
    {
        bNoErrorOcurred = false;
    }

    // Verification
    BOOST_CHECK_EQUAL(bNoErrorOcurred, NO_ERROR_OCURRED);
}

/// <summary>
/// Checks if all the injected dependencies have been destroyed. It's not a deep check but a "check for null" or "check for empty" test.
/// </summary>
QTEST_CASE ( Destroy_AllDependenciesAreDestroyed_Test )
{
    using Kinesis::TestAutomationTool::Backend::ITATLogger;

    // Preparation
    const ITATLogger* EXPECTED_LOGGER = NULL;
    TATTestAutomationToolExecutionWhiteBox TESTAUTOMATIONTOOL_EXECUTION;

	// Execution
    TESTAUTOMATIONTOOL_EXECUTION.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_EXECUTION.GetLogger(), EXPECTED_LOGGER);
}

/// <summary>
/// Not tested. It's not a testable method: no inputs, no outputs, just executes other method in other thread.
/// </summary>
QTEST_CASE ( ExecuteTests_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's not a testable method: no inputs, no outputs, just executes other method in other thread."));
}

/// <summary>
/// Not tested. It's not a testable method: no inputs, no outputs, just executes a method of a component.
/// </summary>
QTEST_CASE ( StopTestExecution_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's not a testable method: no inputs, no outputs, just executes a method of a component."));
}

/// <summary>
/// Not tested. It's an event handler.
/// </summary>
QTEST_CASE ( ParseTestResultFile_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's not a testable method: no outputs, no state changes, just enqueues an event.."));
}

/// <summary>
/// Not tested. It's not a testable method: no outputs and event system can't be mocked up.
/// </summary>
QTEST_CASE ( NotifyEvent_NotTested_Test )
{
    BOOST_MESSAGE(wxT("Not tested. It's not a testable method: no outputs and event system can't be mocked up."));
}

/// <summary>
/// Not tested. It's an event handler.
/// </summary>
QTEST_CASE ( OnTestExecutionThreadLogUpdate_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's an event handler."));
}

/// <summary>
/// Not tested. It's an event handler.
/// </summary>
QTEST_CASE ( OnTestExecutionThreadCompletion_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's an event handler."));
}

/// <summary>
/// Not tested. It's an event handler.
/// </summary>
QTEST_CASE ( OnTestExecutionThreadNotification_NotTested_Test )
{
    BOOST_MESSAGE(wxT("It's an event handler."));
}

/// <summary>
/// Checks that the configuration file path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetConfigurationFilePath_IsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_CONFIGURATIONFILEPATH = wxT("PATH");
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetConfigurationFilePath(EXPECTED_CONFIGURATIONFILEPATH);

	// Execution
    wxString strConfigurationFilePath = testExecutionUT.GetConfigurationFilePath();
    
    // Verification
    BOOST_CHECK_EQUAL(strConfigurationFilePath, EXPECTED_CONFIGURATIONFILEPATH);
}

/// <summary>
/// Checks that the configuration file path is correctly stored.
/// </summary>
QTEST_CASE ( SetConfigurationFilePath_IsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_CONFIGURATIONFILEPATH = wxT("PATH");

	// Execution
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetConfigurationFilePath(EXPECTED_CONFIGURATIONFILEPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(testExecutionUT.GetConfigurationFilePath(), EXPECTED_CONFIGURATIONFILEPATH);
}

/// <summary>
/// Checks that the flag combinations are correctly retrieved.
/// </summary>
QTEST_CASE ( GetFlagCombinations_AreCorrectlyRetrieved_Test )
{
    // Preparation
    TATTestAutomationToolExecutionWhiteBox::TFlagCombinationCollection EXPECTED_FLAGCOMBINATIONS;
    EXPECTED_FLAGCOMBINATIONS.insert(std::pair< wxString, std::map<wxString, wxString> >(wxT("FIRST"), TATTestAutomationToolExecutionWhiteBox::TFlagCombinationValues()));
    EXPECTED_FLAGCOMBINATIONS.insert(std::pair< wxString, std::map<wxString, wxString> >(wxT("SECOND"), TATTestAutomationToolExecutionWhiteBox::TFlagCombinationValues()));

    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetFlagCombinations(EXPECTED_FLAGCOMBINATIONS);

	// Execution
    TATTestAutomationToolExecutionWhiteBox::TFlagCombinationCollection flagCombinations = testExecutionUT.GetFlagCombinations();

    // Verification
    BOOST_CHECK(flagCombinations == EXPECTED_FLAGCOMBINATIONS);
}

/// <summary>
/// Checks that the flag combinations are correctly stored.
/// </summary>
QTEST_CASE ( SetFlagCombinations_AreCorrectlyStored_Test )
{
    // Preparation
    TATTestAutomationToolExecutionWhiteBox::TFlagCombinationCollection EXPECTED_FLAGCOMBINATIONS;
    EXPECTED_FLAGCOMBINATIONS.insert(std::pair< wxString, std::map<wxString, wxString> >(wxT("FIRST"), TATTestAutomationToolExecutionWhiteBox::TFlagCombinationValues()));
    EXPECTED_FLAGCOMBINATIONS.insert(std::pair< wxString, std::map<wxString, wxString> >(wxT("SECOND"), TATTestAutomationToolExecutionWhiteBox::TFlagCombinationValues()));

	// Execution
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetFlagCombinations(EXPECTED_FLAGCOMBINATIONS);
    
    // Verification
    BOOST_CHECK(testExecutionUT.GetFlagCombinations() == EXPECTED_FLAGCOMBINATIONS);
}

/// <summary>
/// Checks that the compiler information structures are correctly retrieved.
/// </summary>
QTEST_CASE ( GetCompilerInfos_AreCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

    // Preparation
    std::map<wxString, TATCompilerInfo> EXPECTED_COMPILERINFOS;
    EXPECTED_COMPILERINFOS.insert(std::pair< wxString, TATCompilerInfo >(wxT("FIRST"), TATCompilerInfo()));

    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetCompilerInfos(EXPECTED_COMPILERINFOS);

	// Execution
    std::map<wxString, TATCompilerInfo> compilerInfos = testExecutionUT.GetCompilerInfos();

    // Verification
    BOOST_CHECK_EQUAL(compilerInfos.begin()->first, EXPECTED_COMPILERINFOS.begin()->first);
}

/// <summary>
/// Checks that the compiler information structures are correctly stored.
/// </summary>
QTEST_CASE ( SetCompilerInfos_AreCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

    // Preparation
    std::map<wxString, TATCompilerInfo> EXPECTED_COMPILERINFOS;
    EXPECTED_COMPILERINFOS.insert(std::pair< wxString, TATCompilerInfo >(wxT("FIRST"), TATCompilerInfo()));

	// Execution
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetCompilerInfos(EXPECTED_COMPILERINFOS);
    
    // Verification
    BOOST_CHECK_EQUAL(testExecutionUT.GetCompilerInfos().begin()->first, EXPECTED_COMPILERINFOS.begin()->first);
}

/// <summary>
/// Checks that the compilation configurations are correctly retrieved.
/// </summary>
QTEST_CASE ( GetCompilationConfigurations_AreCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

    // Preparation
    std::list<wxString> EXPECTED_COMPILATION_CONFIGURATIONS;
    EXPECTED_COMPILATION_CONFIGURATIONS.push_back(wxT("FIRST"));
    EXPECTED_COMPILATION_CONFIGURATIONS.push_back(wxT("SECOND"));

    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetCompilationConfigurations(EXPECTED_COMPILATION_CONFIGURATIONS);

	// Execution
    std::list<wxString> compilationConfigurations = testExecutionUT.GetCompilationConfigurations();

    // Verification
    BOOST_CHECK(compilationConfigurations == EXPECTED_COMPILATION_CONFIGURATIONS);
}

/// <summary>
/// Checks that the compilation configurations are correctly stored.
/// </summary>
QTEST_CASE ( SetCompilationConfigurations_AreCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

    // Preparation
    std::list<wxString> EXPECTED_COMPILATION_CONFIGURATIONS;
    EXPECTED_COMPILATION_CONFIGURATIONS.push_back(wxT("FIRST"));
    EXPECTED_COMPILATION_CONFIGURATIONS.push_back(wxT("SECOND"));

	// Execution
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetCompilationConfigurations(EXPECTED_COMPILATION_CONFIGURATIONS);
    
    // Verification
    BOOST_CHECK(testExecutionUT.GetCompilationConfigurations() == EXPECTED_COMPILATION_CONFIGURATIONS);
}

/// <summary>
/// Checks that the logger is correctly retrieved.
/// </summary>
QTEST_CASE ( GetLogger_IsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;
    using Kinesis::TestAutomationTool::Backend::ITATLogger;

    // Preparation
    TATLoggerMock* EXPECTED_LOGGER = new TATLoggerMock();

    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetLogger(EXPECTED_LOGGER);

	// Execution
    ITATLogger* pLogger = testExecutionUT.GetLogger();

    // Verification
    BOOST_CHECK_EQUAL(pLogger, EXPECTED_LOGGER);
}

/// <summary>
/// Checks that the logger is correctly stored.
/// </summary>
QTEST_CASE ( SetLogger_IsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // Preparation
    TATLoggerMock* EXPECTED_LOGGER = new TATLoggerMock();

	// Execution
    TATTestAutomationToolExecution testExecutionUT;
    testExecutionUT.SetLogger(EXPECTED_LOGGER);
    
    // Verification
    BOOST_CHECK_EQUAL(testExecutionUT.GetLogger(), EXPECTED_LOGGER);
}

/// <summary>
/// Checks that the listener is correctly stored.
/// </summary>
QTEST_CASE ( SetTestExecutionEventListener_IsCorrectlyStored_Test )
{
    // Preparation
    TATTestAutomationToolExecutionWhiteBox testExecutionUT;
    wxEvtHandler EVENT_LISTENER;

	// Execution
    testExecutionUT.SetTestExecutionEventListener(&EVENT_LISTENER);
    
    // Verification
    BOOST_CHECK_EQUAL(testExecutionUT.GetTestExecutionEventListener_ForTestingPurposes(), &EVENT_LISTENER);
}

// End - Test Suite: TATTestAutomationToolExecution
QTEST_SUITE_END()
