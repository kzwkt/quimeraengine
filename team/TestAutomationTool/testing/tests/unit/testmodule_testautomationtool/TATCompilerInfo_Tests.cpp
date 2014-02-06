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
    const wxString EXPECTED_CLEANPARAMS = wxT("");
    const wxString EXPECTED_COMPILERPATH = wxT("");
    const wxString EXPECTED_FILESPECIFIER = wxT("");
    const wxString EXPECTED_NAME = wxT("");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;

	// Execution
    TATCompilerInfo compilerInfoUT;

    wxString strBuildCommand = compilerInfoUT.GetBuildCommand();
    wxString strBuildParams = compilerInfoUT.GetBuildParams();
    wxString strClearCommand = compilerInfoUT.GetCleanCommand();
    wxString strClearParams = compilerInfoUT.GetCleanParams();
    wxString strCompilerPath = compilerInfoUT.GetCompilerPath();
    wxString strFileSpecifier = compilerInfoUT.GetFileSpecifier();
    wxString strName = compilerInfoUT.GetName();
    std::list<wxString> sutProjects = compilerInfoUT.GetSUTProjects();
    std::list<TATTestModulesExecutionInfo> testModulesExecutionInfo = compilerInfoUT.GetTestModulesExecutionInfo();
    
    // Verification
    BOOST_CHECK_EQUAL(strBuildCommand, EXPECTED_BUILDCOMMAND);
    BOOST_CHECK_EQUAL(strBuildParams, EXPECTED_BUILDPARAMS);
    BOOST_CHECK_EQUAL(strClearCommand, EXPECTED_CLEANCOMMAND);
    BOOST_CHECK_EQUAL(strClearParams, EXPECTED_CLEANPARAMS);
    BOOST_CHECK_EQUAL(strCompilerPath, EXPECTED_COMPILERPATH);
    BOOST_CHECK_EQUAL(strFileSpecifier, EXPECTED_FILESPECIFIER);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
    BOOST_CHECK_EQUAL(sutProjects.size(), EXPECTED_SUTPROJECTS.size());
    BOOST_CHECK_EQUAL(testModulesExecutionInfo.size(), EXPECTED_TESTMODULESEXECUTIONINFO.size());
}

/// <summary>
/// Checks that it returns true when objects are equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsTrueWhenObjectsAreEqual_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("A");
    const wxString EXPECTED_BUILDPARAMS = wxT("B");
    const wxString EXPECTED_CLEANCOMMAND = wxT("C");
    const wxString EXPECTED_CLEANPARAMS = wxT("D");
    const wxString EXPECTED_COMPILERPATH = wxT("E");
    const wxString EXPECTED_FILESPECIFIER = wxT("F");
    const wxString EXPECTED_NAME = wxT("G");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;

    TATCompilerInfo compilerInfoA;
    compilerInfoA.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoA.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoA.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoA.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoA.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoA.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoA.SetName(EXPECTED_NAME);
    compilerInfoA.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoA.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    TATCompilerInfo compilerInfoB;
    compilerInfoB.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoB.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoB.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoB.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoB.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoB.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoB.SetName(EXPECTED_NAME);
    compilerInfoB.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoB.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = compilerInfoA == compilerInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when objects are not equal.
/// </summary>
QTEST_CASE ( OperatorEquality_ReturnsFalseWhenObjectsAreNotEqual_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("A");
    const wxString EXPECTED_BUILDPARAMS = wxT("B");
    const wxString EXPECTED_CLEANCOMMAND = wxT("C");
    const wxString EXPECTED_CLEANPARAMS = wxT("D");
    const wxString EXPECTED_COMPILERPATH = wxT("E");
    const wxString EXPECTED_FILESPECIFIER = wxT("F");
    const wxString EXPECTED_NAME = wxT("G");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;

    const wxString DIFFERENT_VALUE("X");

    TATCompilerInfo compilerInfoA;
    compilerInfoA.SetBuildCommand(DIFFERENT_VALUE);
    compilerInfoA.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoA.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoA.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoA.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoA.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoA.SetName(EXPECTED_NAME);
    compilerInfoA.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoA.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    TATCompilerInfo compilerInfoB;
    compilerInfoB.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoB.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoB.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoB.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoB.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoB.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoB.SetName(EXPECTED_NAME);
    compilerInfoB.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoB.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = compilerInfoA == compilerInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when objects are equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsFalseWhenObjectsAreEqual_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("A");
    const wxString EXPECTED_BUILDPARAMS = wxT("B");
    const wxString EXPECTED_CLEANCOMMAND = wxT("C");
    const wxString EXPECTED_CLEANPARAMS = wxT("D");
    const wxString EXPECTED_COMPILERPATH = wxT("E");
    const wxString EXPECTED_FILESPECIFIER = wxT("F");
    const wxString EXPECTED_NAME = wxT("G");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;

    TATCompilerInfo compilerInfoA;
    compilerInfoA.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoA.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoA.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoA.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoA.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoA.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoA.SetName(EXPECTED_NAME);
    compilerInfoA.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoA.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    TATCompilerInfo compilerInfoB;
    compilerInfoB.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoB.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoB.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoB.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoB.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoB.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoB.SetName(EXPECTED_NAME);
    compilerInfoB.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoB.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    const bool EXPECTED_RESULT = false;

	// Execution
    bool bResult = compilerInfoA != compilerInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when objects are not equal.
/// </summary>
QTEST_CASE ( OperatorInequality_ReturnsTrueWhenObjectsAreNotEqual_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;

    // Preparation
    const wxString EXPECTED_BUILDCOMMAND = wxT("A");
    const wxString EXPECTED_BUILDPARAMS = wxT("B");
    const wxString EXPECTED_CLEANCOMMAND = wxT("C");
    const wxString EXPECTED_CLEANPARAMS = wxT("D");
    const wxString EXPECTED_COMPILERPATH = wxT("E");
    const wxString EXPECTED_FILESPECIFIER = wxT("F");
    const wxString EXPECTED_NAME = wxT("G");
    const std::list<wxString> EXPECTED_SUTPROJECTS;
    const std::list<TATTestModulesExecutionInfo> EXPECTED_TESTMODULESEXECUTIONINFO;
        
    const wxString DIFFERENT_VALUE("X");

    TATCompilerInfo compilerInfoA;
    compilerInfoA.SetBuildCommand(DIFFERENT_VALUE);
    compilerInfoA.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoA.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoA.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoA.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoA.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoA.SetName(EXPECTED_NAME);
    compilerInfoA.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoA.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    TATCompilerInfo compilerInfoB;
    compilerInfoB.SetBuildCommand(EXPECTED_BUILDCOMMAND);
    compilerInfoB.SetBuildParams(EXPECTED_BUILDPARAMS);
    compilerInfoB.SetCleanCommand(EXPECTED_CLEANCOMMAND);
    compilerInfoB.SetCleanParams(EXPECTED_CLEANPARAMS);
    compilerInfoB.SetCompilerPath(EXPECTED_COMPILERPATH);
    compilerInfoB.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    compilerInfoB.SetName(EXPECTED_NAME);
    compilerInfoB.SetSUTProjects(EXPECTED_SUTPROJECTS);
    compilerInfoB.SetTestModulesExecutionInfo(EXPECTED_TESTMODULESEXECUTIONINFO);

    const bool EXPECTED_RESULT = true;

	// Execution
    bool bResult = compilerInfoA != compilerInfoB;
    
    // Verification
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
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
/// Checks that the build parameters are correctly retrieved.
/// </summary>
QTEST_CASE ( GetBuildParams_BuildParamsAreCorrectlyRetrieved_Test )
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
/// Checks that the build parameters are correctly stored.
/// </summary>
QTEST_CASE ( SetBuildParams_BuildParamsAreCorrectlyStored_Test )
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
/// Checks that the clean parameters are correctly retrieved.
/// </summary>
QTEST_CASE ( GetCleanParams_CleanParamsAreCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_CLEANPARAMS = wxT("CLEANPARAMS");
    compilerInfoUT.SetCleanParams(EXPECTED_CLEANPARAMS);

	// Execution
    wxString strCleanParams = compilerInfoUT.GetCleanParams();
    
    // Verification
    BOOST_CHECK_EQUAL(strCleanParams, EXPECTED_CLEANPARAMS);
}

/// <summary>
/// Checks that the clean parmeters are correctly stored.
/// </summary>
QTEST_CASE ( SetCleanParams_CleanParamsAreCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_CLEANPARAMS = wxT("CLEANPARAMS");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetCleanParams(EXPECTED_CLEANPARAMS);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetCleanParams(), EXPECTED_CLEANPARAMS);
}

/// <summary>
/// Checks that the file specifier is correctly retrieved.
/// </summary>
QTEST_CASE ( GetFileSpecifier_FileSpecifierIsCorrectlyRetrieved_Test )
{
    // Preparation
    TATCompilerInfo compilerInfoUT;
    const wxString EXPECTED_FILESPECIFIER = wxT("FILESPECIFIER");
    compilerInfoUT.SetFileSpecifier(EXPECTED_FILESPECIFIER);

	// Execution
    wxString strFileSpecifier = compilerInfoUT.GetFileSpecifier();
    
    // Verification
    BOOST_CHECK_EQUAL(strFileSpecifier, EXPECTED_FILESPECIFIER);
}

/// <summary>
/// Checks that the file specifier is correctly stored.
/// </summary>
QTEST_CASE ( SetFileSpecifier_FileSpecifierIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_FILESPECIFIER = wxT("FILESPECIFIER");

	// Execution
    TATCompilerInfo compilerInfoUT;
    compilerInfoUT.SetFileSpecifier(EXPECTED_FILESPECIFIER);
    
    // Verification
    BOOST_CHECK_EQUAL(compilerInfoUT.GetFileSpecifier(), EXPECTED_FILESPECIFIER);
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
