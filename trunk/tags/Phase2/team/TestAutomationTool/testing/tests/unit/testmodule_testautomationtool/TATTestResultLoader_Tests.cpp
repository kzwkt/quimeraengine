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

#include "TestResults/TATTestResultLoader.h"

#include <wx/filefn.h>

#include "TestResults/TATTestResultNode.h"
#include "TATTestResultLoaderWhiteBox.h"
#include "TestResults/TATXmlReader.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultLoader;
using Kinesis::TestAutomationTool::Backend::Test::TATTestResultLoaderWhiteBox;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

QTEST_SUITE_BEGIN( TATTestResultLoader_TestSuite )

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
/// Checks that default values have nto changed since last execution.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    TATTestResultNode* EXPECTED_TESTRESULTTREE = null_t;

	// [Execution]
    TATTestResultLoader testResultLoaderUT;

    TATTestResultNode* pTestResultNode = testResultLoaderUT.GetTestResultTree();

    // [Verification]
    BOOST_CHECK_EQUAL(pTestResultNode, EXPECTED_TESTRESULTTREE);
}

/// <summary>
/// Checks that all the resources are released (null check only).
/// </summary>
QTEST_CASE ( Destroy_AllResourcesAreReleased_Test )
{
    // [Preparation]
    TATTestResultNode* EXPECTED_TESTRESULTTREE = null_t;

    TATTestResultLoaderWhiteBox testResultLoaderUT;
    testResultLoaderUT.SetTestResultTree_ForTestingPurposes(new TATTestResultNode());

	// [Execution]
    testResultLoaderUT.Destroy();

    // [Verification]
    BOOST_CHECK_EQUAL(testResultLoaderUT.GetTestResultTree(), EXPECTED_TESTRESULTTREE);
}

/// <summary>
/// Checks that the expected test result tree is generated from the test result XML file.
/// </summary>
QTEST_CASE ( Load_ExpectedTestResultTreeGeneratedFromXmlFile_Test )
{
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
    using Kinesis::TestAutomationTool::Backend::ETATResult;
    using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

    // [Preparation]
    const wxString EXISTING_TESTRESULT_FILE = GetPathToTestResultFile_UtilityMethod();
    TATTestResultLoader testResultLoaderUT;

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

	// [Execution]
    testResultLoaderUT.Load(EXISTING_TESTRESULT_FILE);

    // [Verification]
    TATTestResultNode* pTestResultTree = testResultLoaderUT.GetTestResultTree();

    CheckTestResultTreeEquality_UtilityMethod(pTestResultTree, &EXPECTED_TESTRESULT_TREE);
}

/// <summary>
/// Checks that all the resources are released (null check only).
/// </summary>
QTEST_CASE ( Clear_TestResultTreeIsRemovedAndNullified_Test )
{
    // [Preparation]
    TATTestResultNode* EXPECTED_TESTRESULTTREE = null_t;

    TATTestResultLoaderWhiteBox testResultLoaderUT;
    testResultLoaderUT.SetTestResultTree_ForTestingPurposes(new TATTestResultNode());

	// [Execution]
    testResultLoaderUT.Clear();

    // [Verification]
    BOOST_CHECK_EQUAL(testResultLoaderUT.GetTestResultTree(), EXPECTED_TESTRESULTTREE);
}

/// <summary>
/// Checks that the expected test result tree is generated from the XML data.
/// </summary>
QTEST_CASE ( ParseXmlToTree_ExpectedTestResultTreeGeneratedFromXmlData_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResult;
    using Kinesis::TestAutomationTool::Backend::TATXmlReader;
    using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

    // [Preparation]
    const wxString TESTRESULTS_XML = wxT("                                                          \
                    <TestLog>                                                                       \
                      <TestSuite name=\"TestModule1\">                                              \
                        <TestSuite name=\"TestSuite1\">                                             \
                          <TestCase name=\"TestCase1\">                                             \
                            <Info file=\"file1\" line=\"1\"><![CDATA[Message1]]></Info>             \
                            <TestingTime>1</TestingTime>                                            \
                          </TestCase>                                                               \
                        </TestSuite>                                                                \
                        <TestSuite name=\"TestSuite2\">                                             \
                          <TestCase name=\"TestCase1\">                                             \
		                    <Error file=\"file2\" line=\"1\"><![CDATA[Message1]]></Error>           \
		                    <Exception file=\"file2\" line=\"2\"><![CDATA[Message2]]></Exception>   \
                            <TestingTime>2</TestingTime>                                            \
                          </TestCase>                                                               \
	                      <TestCase name=\"TestCase2\">                                             \
                            <Info file=\"file2\" line=\"1\"><![CDATA[Message1]]></Info>             \
                            <Message file=\"file2\" line=\"2\"><![CDATA[Message2]]></Message>       \
                            <TestingTime>3</TestingTime>                                            \
                          </TestCase>                                                               \
                        </TestSuite>                                                                \
                      </TestSuite>                                                                  \
                      <TestSuite name=\"TestModule2\">                                              \
                        <TestSuite name=\"TestSuite1\">                                             \
                          <TestCase name=\"TestCase1\">                                             \
                            <Info file=\"file3\" line=\"1\"><![CDATA[Message1]]></Info>             \
                            <TestingTime>4</TestingTime>                                            \
                          </TestCase>                                                               \
                        </TestSuite>                                                                \
                      </TestSuite>                                                                  \
                    </TestLog>");
    TATXmlReader<std::string> xmlReader;
    TATTestResultLoaderWhiteBox testResultLoaderUT;

    TATTestResultNode EXPECTED_TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, GetPathToTestResultFile_UtilityMethod(), 10, ETATTestResultNodeType::E_Root);
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
                    
        EXPECTED_TESTRESULT_TREE.AddChild(TESTMODULE1);
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
        EXPECTED_TESTRESULT_TREE.AddChild(TESTMODULE2);
            TESTMODULE2->AddChild(TESTSUITE1_2);
                TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                    TESTCASE1_2_2->AddChild(TESTRESULT6);

	// [Execution]
    TATTestResultNode* pTestResultTree = testResultLoaderUT.ParseXmlToTree(TESTRESULTS_XML, xmlReader);

    // [Verification]
    CheckTestResultTreeEquality_UtilityMethod(pTestResultTree, &EXPECTED_TESTRESULT_TREE);
}

/// <summary>
/// Checks that the test result tree is correctly retrieved.
/// </summary>
QTEST_CASE ( GetTestResultTree_IsCorrectlyRetrieved_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    // Preparation
    TATTestResultLoaderWhiteBox testResultLoaderUT;
    TATTestResultNode* EXPECTED_TEST_RESULT_TREE = new TATTestResultNode();
    testResultLoaderUT.SetTestResultTree_ForTestingPurposes(EXPECTED_TEST_RESULT_TREE);

	// Execution
    TATTestResultNode* pTestResultTree = testResultLoaderUT.GetTestResultTree();

    // Verification
    BOOST_CHECK_EQUAL(pTestResultTree, EXPECTED_TEST_RESULT_TREE);
}

// End - Test Suite: TATTestResultLoader
QTEST_SUITE_END()
