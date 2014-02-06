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

#include "TestResults/TATTestResultConsultant.h"
#include "TestResults/TATTestResultNode.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultConsultant;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;
using Kinesis::TestAutomationTool::Backend::ETATResult;
using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;

QTEST_SUITE_BEGIN( TATTestResultConsultant_TestSuite )

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetTestModuleCount_ReturnsRightNumberOfTestModulesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 2;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestModuleCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of module type.
/// </summary>
QTEST_CASE ( GetTestModuleCount_ReturnsRightNumberOfTestModulesForModuleNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTMODULE = TATTestResultNode(wxT("TestModule"), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Module);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestModuleCount(&TESTMODULE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetTestSuiteCount_ReturnsRightNumberOfTestSuitesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 3;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestSuiteCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of suite type.
/// </summary>
QTEST_CASE ( GetTestSuiteCount_ReturnsRightNumberOfTestSuitesForSuiteNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTSUITE = TATTestResultNode(wxT("TestSuite"), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Suite);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestSuiteCount(&TESTSUITE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetTestCaseCount_ReturnsRightNumberOfTestCasesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 4;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestCaseCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of case type.
/// </summary>
QTEST_CASE ( GetTestCaseCount_ReturnsRightNumberOfTestCasesForCaseNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTCASE = TATTestResultNode(wxT("TestCase"), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Case);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestCaseCount(&TESTCASE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetTestResultCount_ReturnsRightNumberOfTestResultsForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 6;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestResultCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of result type.
/// </summary>
QTEST_CASE ( GetTestResultCount_ReturnsRightNumberOfTestResultsForResultNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT = TATTestResultNode(wxT("TestResult"), ETATResult::E_NoResult, wxT(""), 0, ETATTestResultNodeType::E_Result);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetTestResultCount(&TESTRESULT);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetFailedTestModuleCount_ReturnsRightNumberOfFailedTestModulesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestModuleCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of module type.
/// </summary>
QTEST_CASE ( GetFailedTestModuleCount_ReturnsRightNumberOfFailedTestModulesForModuleNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTMODULE = TATTestResultNode(wxT("TestModule"), ETATResult::E_Error, wxT(""), 0, ETATTestResultNodeType::E_Module);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestModuleCount(&TESTMODULE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetFailedTestSuiteCount_ReturnsRightNumberOfFailedTestSuitesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestSuiteCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of suite type.
/// </summary>
QTEST_CASE ( GetFailedTestSuiteCount_ReturnsRightNumberOfFailedTestSuitesForSuiteNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTSUITE = TATTestResultNode(wxT("TestSuite"), ETATResult::E_Error, wxT(""), 0, ETATTestResultNodeType::E_Suite);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestSuiteCount(&TESTSUITE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetFailedTestCaseCount_ReturnsRightNumberOfFailedTestCasesForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestCaseCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of case type.
/// </summary>
QTEST_CASE ( GetFailedTestCaseCount_ReturnsRightNumberOfFailedTestCasesForCaseNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTCASE = TATTestResultNode(wxT("TestCase"), ETATResult::E_Error, wxT(""), 0, ETATTestResultNodeType::E_Case);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestCaseCount(&TESTCASE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of root type.
/// </summary>
QTEST_CASE ( GetFailedTestResultCount_ReturnsRightNumberOfFailedTestResultsForRootNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT_TREE = TATTestResultNode(wxT("ROOT"), ETATResult::E_NoResult, wxT(""), 10, ETATTestResultNodeType::E_Root);
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

    TESTRESULT_TREE.AddChild(TESTMODULE1);
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
    TESTRESULT_TREE.AddChild(TESTMODULE2);
        TESTMODULE2->AddChild(TESTSUITE1_2);
            TESTSUITE1_2->AddChild(TESTCASE1_2_2);
                TESTCASE1_2_2->AddChild(TESTRESULT6);

    const int EXPECTED_COUNT = 2;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestResultCount(&TESTRESULT_TREE);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the expected number of elements is returned when passing a node of result type.
/// </summary>
QTEST_CASE ( GetFailedTestResultCount_ReturnsRightNumberOfFailedTestResultsForResultNode_Test )
{
    // [Preparation]
    TATTestResultNode TESTRESULT = TATTestResultNode(wxT("TestResult"), ETATResult::E_Error, wxT(""), 0, ETATTestResultNodeType::E_Result);

    const int EXPECTED_COUNT = 1;

    TATTestResultConsultant consultantUT;

	// [Execution]
    int nCount = consultantUT.GetFailedTestResultCount(&TESTRESULT);

    // [Verification]
    BOOST_CHECK_EQUAL(nCount, EXPECTED_COUNT);
}

// End - Test Suite: TATTestResultConsultant
QTEST_SUITE_END()
