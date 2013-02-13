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

#include <wx/filefn.h>

#include "TATShellProcess.h"
#include "TATShellProcessListenerMock.h"

using Kinesis::TestAutomationTool::Backend::TATShellProcess;

QTEST_SUITE_BEGIN( TATShellProcess_TestSuite )


/// <summary>
/// Utility method for testing purposes. Path to the prerequired executable file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired executable file used by many unit tests.
/// </returns>
wxString GetPathToExecutableFile_UtilityMethod()
{
#ifdef TAT_OS_WINDOWS
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.exe");
#elif defined(TAT_OS_LINUX)
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile");
#elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
    #error Not defined for Mac
#endif

    return PATH_TO_EXECUTABLE_FILE;
}

/// <summary>
/// Checks that default values of the class members haven't changed since last test execution.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // Preparation
    const wxString EXPECTED_COMMAND = wxT("");
    const TATShellProcess::ITATShellProcessListener* EXPECTED_LISTENER = null_t;

	// Execution
    TATShellProcess processUT;

    // Verification
    BOOST_CHECK_EQUAL(processUT.GetCommand(), EXPECTED_COMMAND);
    BOOST_CHECK_EQUAL(processUT.GetListener(), EXPECTED_LISTENER);
}

/// <summary>
/// Checks that all the values are stored properly.
/// </summary>
QTEST_CASE ( Constructor2_ValuesAreCorrectlySet_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    const wxString EXPECTED_COMMAND = wxT("VALUE");
    TATShellProcessListenerMock EXPECTED_LISTENER;

	// Execution
    TATShellProcess processUT(EXPECTED_COMMAND, &EXPECTED_LISTENER);

    // Verification
    BOOST_CHECK_EQUAL(processUT.GetCommand(), EXPECTED_COMMAND);
    BOOST_CHECK_EQUAL(processUT.GetListener(), &EXPECTED_LISTENER);
}

/// <summary>
/// Checks that the listener receives the expected output text of the process.
/// </summary>
QTEST_CASE ( Execute_ListenerReceivesProcessOutputCorrectly_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    const wxString COMMAND = GetPathToExecutableFile_UtilityMethod();
    TATShellProcessListenerMock LISTENER;
    const wxString EXPECTED_OUTPUT = wxT("OUTPUT");

	// Execution
    TATShellProcess processUT(COMMAND, &LISTENER);
    processUT.Execute(true);

    // Verification
    BOOST_CHECK_EQUAL(LISTENER.GetReceivedOutput(), EXPECTED_OUTPUT);
}

/// <summary>
/// Checks that the listener receives the expected exit code of the process.
/// </summary>
QTEST_CASE ( Execute_ListenerReceivesProcessExitCodeCorrectly_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    const wxString COMMAND = GetPathToExecutableFile_UtilityMethod();
    TATShellProcessListenerMock LISTENER;
    LISTENER.SetLastResult(-999999);
    const int EXPECTED_EXIT_CODE = 0;

	// Execution
    TATShellProcess processUT(COMMAND, &LISTENER);
    processUT.Execute(true);

    // Verification
    BOOST_CHECK_EQUAL(LISTENER.GetLastResult(), EXPECTED_EXIT_CODE);
}

/// <summary>
/// Checks that no exceptions are thrown when the listener is null.
/// </summary>
QTEST_CASE ( Execute_NoExceptionThrownWhenListenerIsNull_Test )
{
    // Preparation
    const wxString COMMAND = GetPathToExecutableFile_UtilityMethod();
    TATShellProcess::ITATShellProcessListener* NULL_LISTENER = null_t;
    const bool EXCEPTION_THROWN = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        TATShellProcess processUT(COMMAND, NULL_LISTENER);
        processUT.Execute(true);
    }
    catch(...)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, !EXCEPTION_THROWN);
}

/// <summary>
/// Checks that no exceptions are thrown when the command doesn't exist.
/// </summary>
QTEST_CASE ( Execute_NoExceptionThrownWhenCommandDoesNotExist_Test )
{
    // Preparation
    const wxString NONEXISTENT_COMMAND = wxT("");
    TATShellProcess::ITATShellProcessListener* NULL_LISTENER = null_t;
    const bool EXCEPTION_THROWN = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        TATShellProcess processUT(NONEXISTENT_COMMAND, NULL_LISTENER);
        processUT.Execute(true);
    }
    catch(...)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, !EXCEPTION_THROWN);
}

/// <summary>
/// Checks that the command is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCommand_CommandIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString COMMAND = wxT("COMMAND");
    TATShellProcess processUT;
    processUT.SetCommand(COMMAND);

	// Execution
    wxString strCommand = processUT.GetCommand();

    // Verification
    BOOST_CHECK_EQUAL(strCommand, COMMAND);
}

/// <summary>
/// Checks that the command is correctly stored.
/// </summary>
QTEST_CASE ( SetCommand_CommandIsCorrectlyStored_Test )
{
    // Preparation
    const wxString COMMAND = wxT("COMMAND");

	// Execution
    TATShellProcess processUT;
    processUT.SetCommand(COMMAND);

    // Verification
    BOOST_CHECK_EQUAL(processUT.GetCommand(), COMMAND);
}

/// <summary>
/// Checks that the listener is correctly retrieved.
/// </summary>
QTEST_CASE ( GetListener_ListenerIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    TATShellProcessListenerMock LISTENER;
    TATShellProcess processUT;
    processUT.SetListener(&LISTENER);

	// Execution
    TATShellProcess::ITATShellProcessListener* pListener = processUT.GetListener();

    // Verification
    BOOST_CHECK_EQUAL(pListener, &LISTENER);
}

/// <summary>
/// Checks that the listener is correctly stored.
/// </summary>
QTEST_CASE ( SetListener_ListenerIsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATShellProcessListenerMock;

    // Preparation
    TATShellProcessListenerMock LISTENER;

	// Execution
    TATShellProcess processUT;
    processUT.SetListener(&LISTENER);

    // Verification
    BOOST_CHECK_EQUAL(processUT.GetListener(), &LISTENER);
}


// End - Test Suite: TATShellProcess
QTEST_SUITE_END()
