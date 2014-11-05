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

#include <wx/textfile.h>
#include <wx/dir.h>

#include "TestExecution/TATTestAutomationToolExecution.h"
#include "TATTestExecutionThreadWhiteBox.h"
#include "TATTestAutomationToolExecutionWhiteBox.h"
#include "TATTestAutomationToolExecutionMock.h"
#include "TATLoggerMock.h"
#include "InternalDefinitions.h"
#include "TestResults/TATTestResultLoaderFactory.h"
#include "TestResults/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionWhiteBox;
using Kinesis::TestAutomationTool::Backend::Test::TATTestExecutionThreadWhiteBox;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionMock;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

// Note: Since the TATTestExecutionThread is a protected class inside the TATTestAutomationToolExecution class,
//       it's necessary to use the white box version to expose it and be able to access to it.

QTEST_SUITE_BEGIN( TATTestExecutionThread_TestSuite )

    
/// <summary>
/// Utility method for testing purposes. Path to the prerequired test result xml file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired text file used by many unit tests.
/// </returns>
wxString GetPathToTestResultFile_UtilityMethod()
{
    const wxString PATH_TO_TESTRESULT_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.xml");

    return PATH_TO_TESTRESULT_FILE;
}

/// <summary>
/// Utility method for testing purposes. Path to the prerequired text file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired text file used by many unit tests.
/// </returns>
wxString GetPathToExecutableFile_UtilityMethod()
{
#ifdef TAT_OS_WINDOWS
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.exe");
#elif defined(TAT_OS_LINUX)
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile");
#elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
#endif

    return PATH_TO_EXECUTABLE_FILE;
}

/// <summary>
/// Utility method for testing purposes. Path to the prerequired text file used by many unit tests.
/// </summary>
/// <returns>
/// The path to the prerequired text file used by many unit tests.
/// </returns>
wxString GetPathToTextFile_UtilityMethod()
{
    const wxString PATH_TO_TEXT_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.txt");

    return PATH_TO_TEXT_FILE;
}

/// <summary>
/// Utility method for testing purposes. Returns the token used as "new line" depending on the operative system.
/// </summary>
/// <returns>
/// The token used as "new line" depending on the operative system.
/// </returns>
wxString GetNewLineToken_UtilityMethod()
{
    // [TODO] Thund: Use the definition from ExternalDefinitions.h

#ifdef TAT_OS_WINDOWS
    const wxString TAT_NEWLINE_TOKEN = wxT("\r\n");
#elif defined(TAT_OS_LINUX)
    const wxString TAT_NEWLINE_TOKEN = wxT("\n");
#else
    const wxString TAT_NEWLINE_TOKEN = wxT("\r");
#endif

    return TAT_NEWLINE_TOKEN;
}

/// <summary>
/// Checks that the exit code is stored when the process is completed.
/// </summary>
QTEST_CASE ( ProcessCompletedHandler_ExitCodeIsStored_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);
    const int EXPECTED_EXITCODE = 1;

	// [Execution]
    executionThreadUT.ProcessCompletedHandler(EXPECTED_EXITCODE);

    // [Verification]
    BOOST_CHECK_EQUAL(executionThreadUT.GetExpectedLastExitCode(), EXPECTED_EXITCODE);
#endif
}

/// <summary>
/// Checks that the output of the process is logged by the handler's logger.
/// </summary>
QTEST_CASE ( ProcessOutputHandler_TheOutputIsLoggedByLoggerOfHandler_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // [Preparation]
    TATLoggerMock* pLogger = new TATLoggerMock();
    TATTestAutomationToolExecutionMock testExecution(pLogger);
    TATTestAutomationToolExecutionWhiteBox::TATTestExecutionThread executionThreadUT(&testExecution);

    const wxString EXPECTED_OUTPUT = wxT("OUTPUT");

	// [Execution]
    executionThreadUT.ProcessOutputHandler(EXPECTED_OUTPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(pLogger->GetLog(), EXPECTED_OUTPUT);
#endif
}

/// <summary>
/// Not test was written for this.
/// </summary>
QTEST_CASE ( Entry_NotTested_Test )
{
    BOOST_MESSAGE(wxT("Not tested: It's an orchestrator method, all its dependencies have been tested instead."));
}

/// <summary>
/// Checks that the back-up file is created.
/// </summary>
QTEST_CASE ( CreateConfigurationFileBackup_TheBackupFileIsCreated_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

    const wxString FILEPATH = GetPathToTextFile_UtilityMethod();
    const wxString EXPECTED_FILEPATH = FILEPATH + wxT(".bak");
    const bool FILE_WAS_CREATED = true;

	// [Execution]
    bool bResult = executionThreadUT.CreateConfigurationFileBackup(FILEPATH);

    bool bFileWasCreated = wxFileExists(EXPECTED_FILEPATH);

    // [Verification]
    BOOST_CHECK_EQUAL(bFileWasCreated, FILE_WAS_CREATED);
    BOOST_CHECK_EQUAL(bResult, FILE_WAS_CREATED); // This should be in another 2 tests, but there is no time for that now

    // [Cleaning]
    if(bFileWasCreated)
    {
        wxRemoveFile(EXPECTED_FILEPATH);
    }
#endif
}

/// <summary>
/// Checks that the back-up file is restored.
/// </summary>
QTEST_CASE ( RestoreConfigurationFileBackup_TheBackupFileIsCreated_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

    const wxString FILEPATH = GetPathToTextFile_UtilityMethod();
    const wxString EXPECTED_FILEPATH = FILEPATH + wxT(".bak");
    const bool FILE_WAS_RESTORED = true;

    wxRenameFile(FILEPATH, EXPECTED_FILEPATH);

	// [Execution]
    bool bResult = executionThreadUT.RestoreConfigurationFileBackup(FILEPATH);

    bool bFileWasRestored = wxFileExists(FILEPATH);

    // [Verification]
    BOOST_CHECK_EQUAL(bFileWasRestored, FILE_WAS_RESTORED);
    BOOST_CHECK_EQUAL(bResult, FILE_WAS_RESTORED); // This should be in another 2 tests, but there is no time for that now

    // [Cleaning]
    if(!bFileWasRestored)
    {
        wxRenameFile(EXPECTED_FILEPATH, FILEPATH);
    }
#endif
}

/// <summary>
/// Checks that the flag values are replaced in the text file.
/// </summary>
QTEST_CASE ( ReplaceFlagValuesInConfigurationFile_TheContentOfTheFileIsReplaced_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    const wxString NEWLINE = GetNewLineToken_UtilityMethod();

    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

    std::map<wxString, wxString> FLAGVALUES;
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG1"), wxT("NEWVALUE1")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG2"), wxT("NEWVALUE2")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG3"), wxT("NEWVALUE3")));

    const wxString FILEPATH = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.h");
    const wxString MODIFIED_FILEPATH = FILEPATH + wxT("REPLACED");
    const wxString EXPECTED_CONTENT = wxT("#define FLAG1 NEWVALUE1") + NEWLINE + wxT("#define FLAG2 NEWVALUE2") + NEWLINE + wxT("#define FLAG3 NEWVALUE3");

    wxCopyFile(FILEPATH, MODIFIED_FILEPATH);

	// [Execution]
    bool bResult = executionThreadUT.ReplaceFlagValuesInConfigurationFile(MODIFIED_FILEPATH, FLAGVALUES);

    // [Verification]
    wxTextFile file(MODIFIED_FILEPATH);
    file.Open();
    wxString strModifiedFileContent = wxT("");

    const size_t LINE_COUNT_IN_FILE = file.GetLineCount();

    // Reads the full file
    for(size_t i = 0; i < LINE_COUNT_IN_FILE; ++i)
    {
        strModifiedFileContent += file.GetLine(i);

        if(i < LINE_COUNT_IN_FILE - 1)
        {
            strModifiedFileContent += NEWLINE;
        }
    }

    file.Close();

    BOOST_CHECK_EQUAL(strModifiedFileContent, EXPECTED_CONTENT);
    BOOST_CHECK_EQUAL(bResult, true); // This should be in another 2 tests, but there is no time for that now

    // [Cleaning]
    wxRemoveFile(MODIFIED_FILEPATH);
#endif
}

/// <summary>
/// Checks that the flag values are replaced in the string.
/// </summary>
QTEST_CASE ( ReplaceFlagValues_TheContentOfTheStringIsReplaced_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    const wxString NEWLINE = GetNewLineToken_UtilityMethod();

    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

    std::map<wxString, wxString> FLAGVALUES;
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG1"), wxT("NEWVALUE1")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG2"), wxT("NEWVALUE2")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG3"), wxT("NEWVALUE3")));

    const wxString INPUT_STRING = wxT("#define FLAG1 VALUE1") + NEWLINE + wxT("#define FLAG2 VALUE2") + NEWLINE + wxT("#define FLAG3 VALUE3") + NEWLINE;
    const wxString EXPECTED_RESULT = wxT("#define FLAG1 NEWVALUE1") + NEWLINE + wxT("#define FLAG2 NEWVALUE2") + NEWLINE + wxT("#define FLAG3 NEWVALUE3") + NEWLINE;

	// [Execution]
    wxString strResult = executionThreadUT.ReplaceFlagValues(INPUT_STRING, FLAGVALUES);

    // [Verification]
    BOOST_CHECK_EQUAL(strResult, EXPECTED_RESULT);
#endif
}

/// <summary>
/// Checks that the flag values are replaced in the string when the latest flag value doesn't end with a "new line" token.
/// </summary>
QTEST_CASE ( ReplaceFlagValues_TheContentOfTheStringIsReplacedWhenLastLineDoesNotEndWithNewLineToken_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    const wxString NEWLINE = GetNewLineToken_UtilityMethod();

    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

    std::map<wxString, wxString> FLAGVALUES;
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG1"), wxT("NEWVALUE1")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG2"), wxT("NEWVALUE2")));
    FLAGVALUES.insert(std::pair<wxString, wxString>(wxT("FLAG3"), wxT("NEWVALUE3")));

    const wxString INPUT_STRING = wxT("#define FLAG1 VALUE1") + NEWLINE + wxT("#define FLAG2 VALUE2") + NEWLINE + wxT("#define FLAG3 VALUE3");
    const wxString EXPECTED_RESULT = wxT("#define FLAG1 NEWVALUE1") + NEWLINE + wxT("#define FLAG2 NEWVALUE2") + NEWLINE + wxT("#define FLAG3 NEWVALUE3");

	// [Execution]
    wxString strResult = executionThreadUT.ReplaceFlagValues(INPUT_STRING, FLAGVALUES);

    // [Verification]
    BOOST_CHECK_EQUAL(strResult, EXPECTED_RESULT);
#endif
}

/// <summary>
/// Checks that it returns all the executable files and only executable files.
/// </summary>
QTEST_CASE ( ReadTestModuleFiles_OnlyExecutableFilesAreListed_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    #ifdef TAT_OS_WINDOWS
    const wxString EXISTING_EXECURABLE_FILE = wxT("TestFile.exe");
    #elif defined(TAT_OS_LINUX)
    const wxString EXISTING_EXECURABLE_FILE = wxT("TestFile");
    #elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
    #endif

    const wxString FOLDER_TO_SEARCH_INTO = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY;
    const size_t EXPECTED_NUMBER_OF_FILES = 1;

    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

	// [Execution]
    std::list<wxString> foundFiles = executionThreadUT.ReadTestModuleFiles(FOLDER_TO_SEARCH_INTO);

    // [Verification]
    BOOST_CHECK_EQUAL(foundFiles.size(), EXPECTED_NUMBER_OF_FILES);
    BOOST_CHECK_EQUAL(*foundFiles.begin(), EXISTING_EXECURABLE_FILE);
#endif
}

/// <summary>
/// Checks that it returns all the test result files (xml files).
/// </summary>
QTEST_CASE ( ReadTestResultFiles_OnlyTestResultFilesAreListed_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    const wxString FOLDER_TO_SEARCH_INTO = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY;
    const wxString EXISTING_TESTRESULT_FILE = wxT("TestFile.xml");
    const size_t EXPECTED_NUMBER_OF_FILES = 1;

    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);

	// [Execution]
    std::list<wxString> foundFiles = executionThreadUT.ReadTestResultFiles(FOLDER_TO_SEARCH_INTO);

    // [Verification]
    BOOST_CHECK_EQUAL(foundFiles.size(), EXPECTED_NUMBER_OF_FILES);
    BOOST_CHECK_EQUAL(*foundFiles.begin(), EXISTING_TESTRESULT_FILE);
#endif
}

/// <summary>
/// Checks that the logger of the handler component receives the messages.
/// </summary>
QTEST_CASE ( Log_LoggerOfHandlerReceivesMessages_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;

    // [Preparation]
    TATFormattedMessage MESSAGE = TATFormattedMessage(wxT("MESSAGECONTENT"));
    TATLoggerMock* LOGGER = new TATLoggerMock();
    TATTestAutomationToolExecutionMock testExecutionMock(LOGGER);
    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

	// [Execution]
    executionThreadUT.Log(MESSAGE);

    // [Verification]
    BOOST_CHECK_EQUAL(LOGGER->GetLog(), MESSAGE.GetFullMessage());
#endif
}

/// <summary>
/// Checks that all the test result files are deleted.
/// </summary>
QTEST_CASE ( DeletePreviousResultFiles_TestResultFilesAreDeleted_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    // [Preparation]
    const wxString TESTRESULTFILES_FOLDER = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/");
    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);
    const bool TEST_RESULT_FILES_ARE_DELETED = true;

    // Creates a copy that will be restored after the test
    wxCopyFile(GetPathToTestResultFile_UtilityMethod(), GetPathToTestResultFile_UtilityMethod() + wxT(".bak"));

	// [Execution]
    executionThreadUT.DeletePreviousResultFiles(TESTRESULTFILES_FOLDER);

    // [Verification]
    wxDir directory(TESTRESULTFILES_FOLDER);
    wxString strAux;
    bool bTestResultFilesWereDeleted = !directory.GetFirst(&strAux, wxT("*.xml"), wxDIR_FILES);

    BOOST_CHECK_EQUAL(bTestResultFilesWereDeleted, TEST_RESULT_FILES_ARE_DELETED);

    // [Cleaning]
    wxRenameFile(GetPathToTestResultFile_UtilityMethod() + wxT(".bak"), GetPathToTestResultFile_UtilityMethod());
#endif
}


// End - Test Suite: TATTestExecutionThread
QTEST_SUITE_END()
