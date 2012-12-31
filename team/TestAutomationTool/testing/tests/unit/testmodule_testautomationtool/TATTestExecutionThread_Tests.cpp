// [TERMS&CONDITIONS]

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
#include "TestExecution/TATTestResultLoaderFactory.h"
#include "TestExecution/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionWhiteBox;
using Kinesis::TestAutomationTool::Backend::Test::TATTestExecutionThreadWhiteBox;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionMock;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

// Note: Since the TATTestExecutionThread is a protected class inside the TATTestAutomationToolExecution class,
//       it's necessary to use the white box version to expose it and be able to access to it.

QTEST_SUITE_BEGIN( TATTestExecutionThread_TestSuite )
    
      
/// <summary>
/// Utility method for testing purposes. Checks whether 2 test result nodes are equal or not.
/// </summary>
/// <param name="pNodeA">First node to compare.</param>
/// <param name="pNodeB">Second node to compare.</param>
void CheckTestResultNodeEquality_UtilityMethod(TATTestResultNode* pNodeA, TATTestResultNode* pNodeB)
{
    BOOST_CHECK_EQUAL(pNodeA->GetName(), pNodeB->GetName());
    BOOST_CHECK_EQUAL(pNodeA->GetMessage(), pNodeB->GetMessage());
    BOOST_CHECK_EQUAL(pNodeA->GetTime(), pNodeB->GetTime());
    BOOST_CHECK_EQUAL(pNodeA->GetResult().ToString(), pNodeB->GetResult().ToString());
}

/// <summary>
/// Utility method for testing purposes. Checks whether 2 test result trees are equal or not.
/// </summary>
/// <param name="pNodeA">First tree to compare.</param>
/// <param name="pNodeB">Second tree to compare.</param>
void CheckTestResultTreeEquality_UtilityMethod(TATTestResultNode* pNodeA, TATTestResultNode* pNodeB)
{
    typedef TATTestResultNode::TNodeCollection::const_iterator node_iterator;

    // Same number of test result roots?
    BOOST_CHECK_EQUAL(pNodeA->GetChildren().size(), pNodeB->GetChildren().size());

    node_iterator iTestRootA = pNodeA->GetChildren().begin();
    node_iterator iTestRootB = pNodeB->GetChildren().begin();

    for(; iTestRootA != pNodeA->GetChildren().end() && iTestRootB != pNodeB->GetChildren().end(); ++iTestRootA, ++iTestRootB)
    {
        TATTestResultNode* pTestRootA = dynamic_cast<TATTestResultNode*>(iTestRootA->second);
        TATTestResultNode* pTestRootB = dynamic_cast<TATTestResultNode*>(iTestRootB->second);

        // Test result roots are equal?
        CheckTestResultNodeEquality_UtilityMethod(pTestRootA, pTestRootB);

        // Same number of test modules?
        BOOST_CHECK_EQUAL(pTestRootA->GetChildren().size(), pTestRootB->GetChildren().size());

        node_iterator iTestModuleA = pTestRootA->GetChildren().begin();
        node_iterator iTestModuleB = pTestRootB->GetChildren().begin();

        for(; iTestModuleA != pTestRootA->GetChildren().end() && iTestModuleB != pTestRootB->GetChildren().end(); ++iTestModuleA, ++iTestModuleB)
        {
            TATTestResultNode* pTestModuleA = dynamic_cast<TATTestResultNode*>(iTestModuleA->second);
            TATTestResultNode* pTestModuleB = dynamic_cast<TATTestResultNode*>(iTestModuleB->second);

            // Test modules are equal?
            CheckTestResultNodeEquality_UtilityMethod(pTestModuleA, pTestModuleB);

            // Same number of test suites?
            BOOST_CHECK_EQUAL(pTestModuleA->GetChildren().size(), pTestModuleB->GetChildren().size());

            node_iterator iTestSuiteA = pTestModuleA->GetChildren().begin();
            node_iterator iTestSuiteB = pTestModuleB->GetChildren().begin();

            for(; iTestSuiteA != pTestModuleA->GetChildren().end() && iTestSuiteB != pTestModuleB->GetChildren().end(); ++iTestSuiteA, ++iTestSuiteB)
            {
                TATTestResultNode* pTestSuiteA = dynamic_cast<TATTestResultNode*>(iTestSuiteA->second);
                TATTestResultNode* pTestSuiteB = dynamic_cast<TATTestResultNode*>(iTestSuiteB->second);

                // Test suites are equal?
                CheckTestResultNodeEquality_UtilityMethod(pTestSuiteA, pTestSuiteB);

                // Same number of test cases?
                BOOST_CHECK_EQUAL(pTestSuiteA->GetChildren().size(), pTestSuiteB->GetChildren().size());

                node_iterator iTestCaseA = pTestSuiteA->GetChildren().begin();
                node_iterator iTestCaseB = pTestSuiteB->GetChildren().begin();

                for(; iTestCaseA != pTestSuiteA->GetChildren().end() && iTestCaseB != pTestSuiteB->GetChildren().end(); ++iTestCaseA, ++iTestCaseB)
                {
                    TATTestResultNode* pTestCaseA = dynamic_cast<TATTestResultNode*>(iTestCaseA->second);
                    TATTestResultNode* pTestCaseB = dynamic_cast<TATTestResultNode*>(iTestCaseB->second);

                    // Test cases are equal?
                    CheckTestResultNodeEquality_UtilityMethod(pTestCaseA, pTestCaseB);

                    // Same number of test results?
                    BOOST_CHECK_EQUAL(pTestCaseA->GetChildren().size(), pTestCaseB->GetChildren().size());

                    node_iterator iTestResultA = pTestCaseA->GetChildren().begin();
                    node_iterator iTestResultB = pTestCaseB->GetChildren().begin();

                    for(; iTestResultA != pTestCaseA->GetChildren().end() && iTestResultB != pTestCaseB->GetChildren().end(); ++iTestResultA, ++iTestResultB)
                    {
                        TATTestResultNode* pTestResultA = dynamic_cast<TATTestResultNode*>(iTestResultA->second);
                        TATTestResultNode* pTestResultB = dynamic_cast<TATTestResultNode*>(iTestResultB->second);
                        
                        // Test cases are equal?
                        CheckTestResultNodeEquality_UtilityMethod(pTestResultA, pTestResultB);
                    }
                }
            }
        }
    }
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
    const wxString PATH_TO_EXECUTABLE_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/TestFile.sh");
#elif defined(TAT_OS_MAC)
    // TODO [Thund]: Complete this with Mac configuration.
#endif

    return PATH_TO_EXECUTABLE_FILE;
}

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
    // [Preparation]
    TATTestExecutionThreadWhiteBox executionThreadUT(null_t);
    const int EXPECTED_EXITCODE = 1;

	// [Execution]
    executionThreadUT.ProcessCompletedHandler(EXPECTED_EXITCODE);
    
    // [Verification]
    BOOST_CHECK_EQUAL(executionThreadUT.GetExpectedLastExitCode(), EXPECTED_EXITCODE);
}

/// <summary>
/// Checks that the output of the process is logged by the handler's logger.
/// </summary>
QTEST_CASE ( ProcessOutputHandler_TheOutputIsLoggedByLoggerOfHandler_Test )
{
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
}

/// <summary>
/// Checks that the back-up file is restored.
/// </summary>
QTEST_CASE ( RestoreConfigurationFileBackup_TheBackupFileIsCreated_Test )
{
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
}

/// <summary>
/// Checks that the flag values are replaced in the text file.
/// </summary>
QTEST_CASE ( ReplaceFlagValuesInConfigurationFile_TheContentOfTheFileIsReplaced_Test )
{
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
}

/// <summary>
/// Checks that the flag values are replaced in the string.
/// </summary>
QTEST_CASE ( ReplaceFlagValues_TheContentOfTheStringIsReplaced_Test )
{
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
}

/// <summary>
/// Checks that the flag values are replaced in the string when the latest flag value doesn't end with a "new line" token.
/// </summary>
QTEST_CASE ( ReplaceFlagValues_TheContentOfTheStringIsReplacedWhenLastLineDoesNotEndWithNewLineToken_Test )
{
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
}

/// <summary>
/// Checks that it returns True when the executable file exists.
/// </summary>
QTEST_CASE ( ExecuteCompilerCommand_ReturnsTrueWhenExecutableFileExists_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // [Preparation]
    const wxString EXISTING_EXECURABLE_FILE = GetPathToExecutableFile_UtilityMethod();
    const wxString EMPTY_VALUE = wxT("");
    const bool EXPECTED_RESULT = true;
    TATTestAutomationToolExecutionMock testExecutionMock(new TATLoggerMock());

    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

	// [Execution]
    bool bResult = executionThreadUT.ExecuteCompilerCommand(EXISTING_EXECURABLE_FILE, EMPTY_VALUE, EMPTY_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the executable file doesn't exist.
/// </summary>
QTEST_CASE ( ExecuteCompilerCommand_ReturnsFalseWhenExecutableFileExists_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // [Preparation]
    const wxString NONEXISTING_EXECURABLE_FILE = wxT("Non_Existent_Exe");
    const wxString EMPTY_VALUE = wxT("");
    const bool EXPECTED_RESULT = false;
    TATTestAutomationToolExecutionMock testExecutionMock(new TATLoggerMock());

    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

	// [Execution]
    bool bResult = executionThreadUT.ExecuteCompilerCommand(NONEXISTING_EXECURABLE_FILE, EMPTY_VALUE, EMPTY_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the executable file exists.
/// </summary>
QTEST_CASE ( ExecuteTestModule_ReturnsTrueWhenExecutableFileExists_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // [Preparation]
    const wxString EXISTING_EXECURABLE_FILE = GetPathToExecutableFile_UtilityMethod();
    const bool EXPECTED_RESULT = true;
    TATTestAutomationToolExecutionMock testExecutionMock(new TATLoggerMock());

    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

	// [Execution]
    bool bResult = executionThreadUT.ExecuteTestModule(EXISTING_EXECURABLE_FILE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the executable file doesn't exist.
/// </summary>
QTEST_CASE ( ExecuteTestModule_ReturnsFalseWhenExecutableFileExists_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATLoggerMock;

    // [Preparation]
    const wxString NONEXISTING_EXECURABLE_FILE = wxT("Non_Existent_Exe");
    const bool EXPECTED_RESULT = false;
    TATTestAutomationToolExecutionMock testExecutionMock(new TATLoggerMock());

    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

	// [Execution]
    bool bResult = executionThreadUT.ExecuteTestModule(NONEXISTING_EXECURABLE_FILE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns all the executable files and only executable files.
/// </summary>
QTEST_CASE ( ReadTestModuleFiles_OnlyExecutableFilesAreListed_Test )
{
    // [Preparation]
#ifdef TAT_OS_WINDOWS
    const wxString EXISTING_EXECURABLE_FILE = wxT("TestFile.exe");
#elif defined(TAT_OS_LINUX)
    const wxString EXISTING_EXECURABLE_FILE = wxT("TestFile.sh");
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
}

/// <summary>
/// Checks that it returns all the test result files (xml files).
/// </summary>
QTEST_CASE ( ReadTestResultFiles_OnlyTestResultFilesAreListed_Test )
{
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
}

/// <summary>
/// Checks that the logger of the handler component receives the messages.
/// </summary>
QTEST_CASE ( Log_LoggerOfHandlerReceivesMessages_Test )
{
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
}

/// <summary>
/// Checks that the expected test result tree is generated from the test result file.
/// </summary>
QTEST_CASE ( ParseTestResultFile_TestResultTreeIsCreatedFromTestResultFile_Test )
{
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
    using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;
    using Kinesis::TestAutomationTool::Backend::ETATResult;

    // [Preparation]
    const wxString EXISTING_TESTRESULT_FILE = GetPathToTestResultFile_UtilityMethod();
    TATTestResultLoaderFactory TESTRESULTLOADER_FACTORY;
    ITATTestResultLoader* TESTRESULT_LOADER = TESTRESULTLOADER_FACTORY.CreateConfigLoader(ETATResultSource::E_XmlFile);
    TATTestAutomationToolExecutionMock testExecutionMock(TESTRESULT_LOADER);
    TATTestExecutionThreadWhiteBox executionThreadUT(&testExecutionMock);

    TATTestResultNode EXPECTED_TESTRESULT_TREE("ROOT");
    TATTestResultNode* TESTLOG1 = new TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, GetPathToTestResultFile_UtilityMethod(), 10);
        TATTestResultNode* TESTMODULE1 = new TATTestResultNode(wxT("TestModule1"), ETATResult::E_NoResult, wxT(""), 6);
            TATTestResultNode* TESTSUITE1 = new TATTestResultNode(wxT("TestSuite1"), ETATResult::E_NoResult, wxT("file1"), 1);
                TATTestResultNode* TESTCASE1 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 1);
                    TATTestResultNode* TESTRESULT1 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0);
            TATTestResultNode* TESTSUITE2 = new TATTestResultNode(wxT("TestSuite2"), ETATResult::E_NoResult, wxT("file2"), 5);
                TATTestResultNode* TESTCASE1_2 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 2);
                    TATTestResultNode* TESTRESULT2 = new TATTestResultNode(wxT("Error"), ETATResult::E_Fail, wxT("Message1"), 0);
                    TATTestResultNode* TESTRESULT3 = new TATTestResultNode(wxT("Exception"), ETATResult::E_Error, wxT("Message2"), 0);
                TATTestResultNode* TESTCASE2_2 = new TATTestResultNode(wxT("TestCase2"), ETATResult::E_NoResult, wxT(""), 3);
                    TATTestResultNode* TESTRESULT4 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0);
                    TATTestResultNode* TESTRESULT5 = new TATTestResultNode(wxT("Message"), ETATResult::E_NoResult, wxT("Message2"), 0);
        TATTestResultNode* TESTMODULE2 = new TATTestResultNode(wxT("TestModule2"), ETATResult::E_NoResult, wxT(""), 4);
            TATTestResultNode* TESTSUITE1_2 = new TATTestResultNode(wxT("TestSuite1"), ETATResult::E_NoResult, wxT("file3"), 4);
                TATTestResultNode* TESTCASE1_2_2 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 4);
                    TATTestResultNode* TESTRESULT6 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0);
    
    EXPECTED_TESTRESULT_TREE.AddChild(TESTLOG1);
        TESTLOG1->AddChild(TESTMODULE1);
            TESTMODULE1->AddChild(TESTSUITE1);
                TESTSUITE1->AddChild(TESTCASE1);
                    TESTCASE1->AddChild(TESTRESULT1);
            TESTMODULE1->AddChild(TESTSUITE2);
                TESTSUITE2->AddChild(TESTCASE1_2);
                    TESTCASE1_2->AddChild(TESTRESULT2);
                    TESTCASE1_2->AddChild(TESTRESULT3);
                TESTSUITE2->AddChild(TESTCASE2_2);
                    TESTCASE2_2->AddChild(TESTRESULT4);
                    TESTCASE2_2->AddChild(TESTRESULT5);
        TESTLOG1->AddChild(TESTMODULE2);
            TESTMODULE2->AddChild(TESTSUITE1_2);
                TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                    TESTCASE1_2_2->AddChild(TESTRESULT6);

	// [Execution]
    executionThreadUT.ParseTestResultFile(EXISTING_TESTRESULT_FILE);

    // [Verification]
    CheckTestResultTreeEquality_UtilityMethod(testExecutionMock.GetTestResultLoader()->GetTestResultTree(), &EXPECTED_TESTRESULT_TREE);
}

/// <summary>
/// Checks that all the test result files are deleted.
/// </summary>
QTEST_CASE ( DeletePreviousResultFiles_TestResultFilesAreDeleted_Test )
{
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
}


// End - Test Suite: TATTestExecutionThread
QTEST_SUITE_END()
