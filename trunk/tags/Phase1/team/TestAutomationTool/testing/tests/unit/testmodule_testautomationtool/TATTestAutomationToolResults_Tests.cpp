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

#include "TestResults/TATTestAutomationToolResults.h"
#include "TATTestAutomationToolResultsWhiteBox.h"
#include "TATTestAutomationToolResultsMock.h"
#include "TestResults/TATTestResultLoaderFactory.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultNode;
using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolResults;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolResultsWhiteBox;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolResultsMock;

QTEST_SUITE_BEGIN( TATTestAutomationToolResults_TestSuite )


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
/// Checks that default values have not changed since last execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

    // Preparation
    ITATTestResultLoader* EXPECTED_TESTRESULTLOADER = null_t;
    wxString EXPECTED_RESULTS_PATH("");

	// Results
    TATTestAutomationToolResults testResults;
    
    // Verification
    BOOST_CHECK_EQUAL(testResults.GetTestResultLoader(), EXPECTED_TESTRESULTLOADER);
    BOOST_CHECK_EQUAL(testResults.GetTestResultsPath(), EXPECTED_RESULTS_PATH);
}

/// <summary>
/// Checks if any error occurs during destruction.
/// </summary>
QTEST_CASE ( Destroy_NoErrorOccurred_Test )
{
    // Preparation
    const bool NO_ERROR_OCURRED = true;
    
    TATTestAutomationToolResultsWhiteBox* TESTAUTOMATIONTOOL_RESULTS = new TATTestAutomationToolResultsWhiteBox();

	// Results
    bool bNoErrorOcurred = true;

    try
    {
        delete TESTAUTOMATIONTOOL_RESULTS;
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
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

    // Preparation
    const ITATTestResultLoader* EXPECTED_TESTRESULTLOADER = NULL;
    TATTestAutomationToolResultsWhiteBox TESTAUTOMATIONTOOL_RESULTS;

	// Results
    TESTAUTOMATIONTOOL_RESULTS.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_RESULTS.GetTestResultLoader(), EXPECTED_TESTRESULTLOADER);
}

/// <summary>
/// Checks that the expected test result tree is generated from the test result file.
/// </summary>
QTEST_CASE ( ParseTestResultFile_TestResultTreeIsCreatedFromTestResultFile_Test )
{
#ifdef TAT_OS_LINUX
    BOOST_CHECK_MESSAGE(false, "This test fails for Linux only. It has to be fixed as soon as possible.");
#else
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
    using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;
    using Kinesis::TestAutomationTool::Backend::ETATResult;
    using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

    // [Preparation]
    const wxString EXISTING_TESTRESULT_FILE = GetPathToTestResultFile_UtilityMethod();
    wxString NOTNECESSARY_INFORMATION("");
    TATTestResultLoaderFactory TESTRESULTLOADER_FACTORY;
    ITATTestResultLoader* TESTRESULT_LOADER = TESTRESULTLOADER_FACTORY.CreateConfigLoader(ETATResultSource::E_XmlFile);
    TATTestAutomationToolResultsMock testResultsMock(TESTRESULT_LOADER);

    TATTestResultNode EXPECTED_TESTRESULT_TREE("ROOT");
    TATTestResultNode* TESTLOG1 = new TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, GetPathToTestResultFile_UtilityMethod(), 10, ETATTestResultNodeType::E_Root);
        TATTestResultNode* TESTMODULE1 = new TATTestResultNode(wxT("TestModule1"), ETATResult::E_NoResult, wxT(""), 6, ETATTestResultNodeType::E_Module);
            TATTestResultNode* TESTSUITE1 = new TATTestResultNode(wxT("TestSuite1"), ETATResult::E_NoResult, wxT("file1"), 1, ETATTestResultNodeType::E_Suite);
                TATTestResultNode* TESTCASE1 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 1, ETATTestResultNodeType::E_Case);
                    TATTestResultNode* TESTRESULT1 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0, ETATTestResultNodeType::E_Result);
            TATTestResultNode* TESTSUITE2 = new TATTestResultNode(wxT("TestSuite2"), ETATResult::E_NoResult, wxT("file2"), 5, ETATTestResultNodeType::E_Suite);
                TATTestResultNode* TESTCASE1_2 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 2, ETATTestResultNodeType::E_Case);
                    TATTestResultNode* TESTRESULT2 = new TATTestResultNode(wxT("Error"), ETATResult::E_Fail, wxT("Message1"), 0, ETATTestResultNodeType::E_Result);
                    TATTestResultNode* TESTRESULT3 = new TATTestResultNode(wxT("Exception"), ETATResult::E_Error, wxT("Message2"), 0, ETATTestResultNodeType::E_Result);
                TATTestResultNode* TESTCASE2_2 = new TATTestResultNode(wxT("TestCase2"), ETATResult::E_NoResult, wxT(""), 3, ETATTestResultNodeType::E_Case);
                    TATTestResultNode* TESTRESULT4 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0, ETATTestResultNodeType::E_Result);
                    TATTestResultNode* TESTRESULT5 = new TATTestResultNode(wxT("Message"), ETATResult::E_NoResult, wxT("Message2"), 0, ETATTestResultNodeType::E_Result);
        TATTestResultNode* TESTMODULE2 = new TATTestResultNode(wxT("TestModule2"), ETATResult::E_NoResult, wxT(""), 4, ETATTestResultNodeType::E_Module);
            TATTestResultNode* TESTSUITE1_2 = new TATTestResultNode(wxT("TestSuite1"), ETATResult::E_NoResult, wxT("file3"), 4, ETATTestResultNodeType::E_Suite);
                TATTestResultNode* TESTCASE1_2_2 = new TATTestResultNode(wxT("TestCase1"), ETATResult::E_NoResult, wxT(""), 4, ETATTestResultNodeType::E_Case);
                    TATTestResultNode* TESTRESULT6 = new TATTestResultNode(wxT("Info"), ETATResult::E_Success, wxT("Message1"), 0, ETATTestResultNodeType::E_Result);

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

	// [Results]
    testResultsMock.ParseTestResultFile(EXISTING_TESTRESULT_FILE, NOTNECESSARY_INFORMATION, NOTNECESSARY_INFORMATION, NOTNECESSARY_INFORMATION, NOTNECESSARY_INFORMATION);

    // [Verification]
    CheckTestResultTreeEquality_UtilityMethod(testResultsMock.GetTestResultLoader()->GetTestResultTree(), &EXPECTED_TESTRESULT_TREE);
#endif
}

/// <summary>
/// Checks that the test result files path is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestResultsPath_IsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_TESTRESULTSPATH = wxT("PATH");
    TATTestAutomationToolResults testResultsUT;
    testResultsUT.SetTestResultsPath(EXPECTED_TESTRESULTSPATH);

	// Results
    wxString strTestResultsPath = testResultsUT.GetTestResultsPath();
    
    // Verification
    BOOST_CHECK_EQUAL(strTestResultsPath, EXPECTED_TESTRESULTSPATH);
}

/// <summary>
/// Checks that the test result files path is correctly stored.
/// </summary>
QTEST_CASE ( SetTestResultsPath_IsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_TESTRESULTSPATH = wxT("PATH");

	// Results
    TATTestAutomationToolResults testResultsUT;
    testResultsUT.SetTestResultsPath(EXPECTED_TESTRESULTSPATH);
    
    // Verification
    BOOST_CHECK_EQUAL(testResultsUT.GetTestResultsPath(), EXPECTED_TESTRESULTSPATH);
}

/// <summary>
/// Checks that the test result loader is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestResultLoader_IsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;

    // Preparation
    TATTestResultLoaderFactory TESTRESULTLOADER_FACTORY;
    ITATTestResultLoader* EXPECTED_TESTRESULTLOADER = TESTRESULTLOADER_FACTORY.CreateConfigLoader(ETATResultSource::E_XmlFile);

    TATTestAutomationToolResults testResultsUT;
    testResultsUT.SetTestResultLoader(EXPECTED_TESTRESULTLOADER);

	// Results
    ITATTestResultLoader* pTestResultLoader = testResultsUT.GetTestResultLoader();

    // Verification
    BOOST_CHECK_EQUAL(pTestResultLoader, EXPECTED_TESTRESULTLOADER);
}

/// <summary>
/// Checks that the test result loader is correctly stored.
/// </summary>
QTEST_CASE ( SetTestResultLoader_IsCorrectlyStored_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;

    // Preparation
    TATTestResultLoaderFactory TESTRESULTLOADER_FACTORY;
    ITATTestResultLoader* EXPECTED_TESTRESULTLOADER = TESTRESULTLOADER_FACTORY.CreateConfigLoader(ETATResultSource::E_XmlFile);

	// Results
    TATTestAutomationToolResults testResultsUT;
    testResultsUT.SetTestResultLoader(EXPECTED_TESTRESULTLOADER);
    
    // Verification
    BOOST_CHECK_EQUAL(testResultsUT.GetTestResultLoader(), EXPECTED_TESTRESULTLOADER);
}

// End - Test Suite: TATTestAutomationToolResults
QTEST_SUITE_END()
