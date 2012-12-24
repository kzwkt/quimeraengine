// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATCompilerInfo.h"
#include "TestExecution/TATTestModulesExecutionInfo.h"

using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

QTEST_SUITE_BEGIN( TATCompilerInfo_TestSuite )


/// <summary>
/// Checks that default values have not changed.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("");
    const wxString EXPECTED_BUILDPARAMS = wxT("");
    const wxString EXPECTED_CLEANCOMMAND = wxT("");
    const wxString EXPECTED_COMPILERPATH = wxT("");
    const wxString EXPECTED_NAME = wxT("");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;

	// Execution
    TATCompilerInfo compilerInfoUT;

    wxString strBuildCommand = compilerInfoUT.GetBuildCommand();
    wxString strBuildParams = compilerInfoUT.GetBuildParams();
    wxString strClearCommand = compilerInfoUT.GetCleanCommand();
    wxString strCompilerPath = compilerInfoUT.GetCompilerPath();
    wxString strName = compilerInfoUT.GetName();
    std::list<wxString> sutProjects = compilerInfoUT.GetSUTProjects();
    std::list<TATTestModulesExecutionInfo> testModulesExecutionInfo = compilerInfoUT.GetTestModulesExecutionInfo();
    
    // Verification
    BOOST_CHECK_EQUAL(strBuildCommand, EXPECTED_BUILDCOMMAND);
    BOOST_CHECK_EQUAL(strBuildParams, EXPECTED_BUILDPARAMS);
    BOOST_CHECK_EQUAL(strClearCommand, EXPECTED_CLEANCOMMAND);
    BOOST_CHECK_EQUAL(strCompilerPath, EXPECTED_COMPILERPATH);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
    BOOST_CHECK_EQUAL(sutProjects.size(), EXPECTED_SUTPROJECTS.size());
    BOOST_CHECK_EQUAL(testModulesExecutionInfo.size(), EXPECTED_TESTMODULESEXECUTIONINFO.size());
}

/// <summary>
/// Checks that the build command is correctly retrieved.
/// </summary>
QTEST_CASE ( GetBuildCommand_BuildCommandIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_BUILDCOMMAND = wxT("BUILDCOMMAND");
    compilerInfoUT.SetBuildCommand(EXPECTED_BUILDCOMMAND);

	// Execution
    wxString strBuildCommand = compilerInfoUT.GetBuildCommand();
    
    // Verification
    BOOST_CHECK_EQUAL(strBuildCommand, EXPECTED_BUILDCOMMAND);
}

/// <summary>
/// Checks that the build command is correctly stored.
/// </summary>
QTEST_CASE ( SetBuildCommand_BuildCommandIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("BUILDCOMMAND");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetBuildCommand(), EXPECTED_BUILDCOMMAND);
}

/// <summary>
/// Checks that the build params is correctly retrieved.
/// </summary>
QTEST_CASE ( GetBuildParams_BuildParamsIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_BUILDPARAMS = wxT("BUILDPARAMS");
    compilerInfoUT.SetBuildParams(EXPECTED_BUILDPARAMS);

	// Execution
    wxString strBuildParams = compilerInfoUT.GetBuildParams();
    
    // Verification
    BOOST_CHECK_EQUAL(strBuildParams, EXPECTED_BUILDPARAMS);
}

/// <summary>
/// Checks that the build params is correctly stored.
/// </summary>
QTEST_CASE ( SetBuildParams_BuildParamsIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_BUILDPARAMS = wxT("BUILDPARAMS");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetBuildParams(EXPECTED_BUILDPARAMS);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetBuildParams(), EXPECTED_BUILDPARAMS);
}

/// <summary>
/// Checks that the clean command is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCleanCommand_CleanCommandIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_CLEANCOMMAND = wxT("CLEANCOMMAND");
    compilerInfoUT.SetBuildCommand(EXPECTED_CLEANCOMMAND);

	// Execution
    wxString strCleanCommand = compilerInfoUT.GetBuildCommand();
    
    // Verification
    BOOST_CHECK_EQUAL(strCleanCommand, EXPECTED_CLEANCOMMAND);
}

/// <summary>
/// Checks that the clean command is correctly stored.
/// </summary>
QTEST_CASE ( SetCleanCommand_CleanCommandIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_CLEANCOMMAND = wxT("CLEANCOMMAND");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetBuildCommand(EXPECTED_CLEANCOMMAND);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetBuildCommand(), EXPECTED_CLEANCOMMAND);
}

/// <summary>
/// Checks that the compiler path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetCompilerPath_CompilerPathIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_COMPILERPATH = wxT("COMPILERPATH");
    compilerInfoUT.SetCompilerPath(EXPECTED_COMPILERPATH);

	// Execution
    wxString strCompilerPath = compilerInfoUT.GetCompilerPath();
    
    // Verification
    BOOST_CHECK_EQUAL(strCompilerPath, EXPECTED_COMPILERPATH);
}

/// <summary>
/// Checks that the compiler path is correctly stored.
/// </summary>
QTEST_CASE ( SetCompilerPath_BuildCommandIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_COMPILERPATH = wxT("COMPILERPATH");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetCompilerPath(EXPECTED_COMPILERPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetCompilerPath(), EXPECTED_COMPILERPATH);
}

/// <summary>
/// Checks that the name is correctly retrieved.
/// </summary>
QTEST_CASE ( GetName_NameIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_NAME = wxT("NAME");
    compilerInfoUT.SetName(EXPECTED_NAME);

	// Execution
    wxString strName = compilerInfoUT.GetName();
    
    // Verification
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
}

/// <summary>
/// Checks that the name is correctly stored.
/// </summary>
QTEST_CASE ( SetName_NameIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_NAME = wxT("NAME");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetName(EXPECTED_NAME);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetName(), EXPECTED_NAME);
}

/// <summary>
/// Checks that the SUT projects are correctly retrieved.
/// </summary>
QTEST_CASE ( GetSUTProjects_SutProjectsAreCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    std::list<wxString> EXPECTED_SUTPROJECTS;
    EXPECTED_SUTPROJECTS.push_back(wxT("SUTPROJECT1"));
    EXPECTED_SUTPROJECTS.push_back(wxT("SUTPROJECT2"));
    compilerInfoUT.SetSUTProjects(EXPECTED_SUTPROJECTS);

	// Execution
    std::list<wxString> sutProjects = compilerInfoUT.GetSUTProjects();
    
    // Verification
    BOOST_CHECK(sutProjects == EXPECTED_SUTPROJECTS);
}

/// <summary>
/// Checks that the SUT projects are correctly stored.
/// </summary>
QTEST_CASE ( SetSUTProjects_SutProjectsAreCorrectlyStored_Test )
{
    // Preparation
    std::list<wxString> EXPECTED_SUTPROJECTS;
    EXPECTED_SUTPROJECTS.push_back(wxT("SUTPROJECT1"));
    EXPECTED_SUTPROJECTS.push_back(wxT("SUTPROJECT2"));

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetSUTProjects(EXPECTED_SUTPROJECTS);
    
    // Verification
    BOOST_CHECK(compilerInfoUT.GetSUTProjects() == EXPECTED_SUTPROJECTS);
}

/// <summary>
/// Checks that the test modules execution information is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestModulesExecutionInfo_TestModulesExecutionInfoIsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    TATCompilerInfo compilerInfoUT;
    std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;
    TATTestModulesExecutionInfo ITEM1;
    ITEM1.SetResultsPath(wxT("VALUE1"));
    TATTestModulesExecutionInfo ITEM2;
    ITEM2.SetResultsPath(wxT("VALUE2"));
    EXPECTED_TESTMODULESEXECUTIONINFO.push_back(ITEM1);
    EXPECTED_TESTMODULESEXECUTIONINFO.push_back(ITEM2);
    
    compilerInfoUT.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

	// Execution
    std::list<TATTestModulesExecutionInfo> testModulesExecutionInfo = compilerInfoUT.GetTestModulesExecutionInfo();
    
    // Verification
    BOOST_CHECK_EQUAL(testModulesExecutionInfo.size(), EXPECTED_TESTMODULESEXECUTIONINFO.size());

    std::list<TATTestModulesExecutionInfo>::const_iterator iResult = testModulesExecutionInfo.begin();
    std::list<TATTestModulesExecutionInfo>::const_iterator iExpected = EXPECTED_TESTMODULESEXECUTIONINFO.begin();
    for(; iResult != testModulesExecutionInfo.end() && iExpected != EXPECTED_TESTMODULESEXECUTIONINFO.end(); ++iResult, ++iExpected)
    {
        BOOST_CHECK_EQUAL(iResult->GetResultsPath(), iExpected->GetResultsPath());
    }
}

/// <summary>
/// Checks that the test modules execution information is correctly stored.
/// </summary>
QTEST_CASE ( SetTestModulesExecutionInfos_TestModulesExecutionInfoIsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;
    TATTestModulesExecutionInfo ITEM1;
    ITEM1.SetResultsPath(wxT("VALUE1"));
    TATTestModulesExecutionInfo ITEM2;
    ITEM2.SetResultsPath(wxT("VALUE2"));
    EXPECTED_TESTMODULESEXECUTIONINFO.push_back(ITEM1);
    EXPECTED_TESTMODULESEXECUTIONINFO.push_back(ITEM2);

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetTestModulesExecutionInfo().size(), EXPECTED_TESTMODULESEXECUTIONINFO.size());

    std::list<TATTestModulesExecutionInfo> testModulesExecutionInfo = compilerInfoUT.GetTestModulesExecutionInfo();
    std::list<TATTestModulesExecutionInfo>::const_iterator iResult = testModulesExecutionInfo.begin();
    std::list<TATTestModulesExecutionInfo>::const_iterator iExpected = EXPECTED_TESTMODULESEXECUTIONINFO.begin();
    for(; iResult != testModulesExecutionInfo.end() && iExpected != EXPECTED_TESTMODULESEXECUTIONINFO.end(); ++iResult, ++iExpected)
    {
        BOOST_CHECK_EQUAL(iResult->GetResultsPath(), iExpected->GetResultsPath());
    }
}

// End - Test Suite: TATCompilerInfo
QTEST_SUITE_END()
