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

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"
#include "TATConfigLoaderFromIniFileWhiteBox.h"
#include "TestConfiguration/TATRuleNode.h"
#include "TestConfiguration/TATKeyValueNode.h"
#include "TATRuleNodeMock.h"
#include "TestConfiguration/TATConfigLoaderFactory.h"
#include "TestConfiguration/TATValidationException.h"

using Kinesis::TestAutomationTool::Backend::TATConfigLoaderFromIniFile;
using Kinesis::TestAutomationTool::Backend::Test::TATConfigLoaderFromIniFileWhiteBox;


QTEST_SUITE_BEGIN( TATConfigLoaderFromIniFile_TestSuite )

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;

/// <summary>
/// Compares the attributes of 2 nodes that are children of different parent nodes but have the same name.
/// It's used as a helper, in order keep the unit test's code clean.
/// </summary>
/// <param name="pParentNodeA">Parent of the first node.</param>
/// <param name="pParentNodeB">Parent of the second node.</param>
/// <param name="strName">The name of the nodes.</param>
void CheckTwoKeyValueNodesAreEqual_HelperMethod(TATKeyValueNode* pParentNodeA, TATKeyValueNode* pParentNodeB, const wxString& strName)
{
    TATKeyValueNode* pNodeA = dynamic_cast<TATKeyValueNode*>(pParentNodeA->GetChild(strName).begin()->second);
    TATKeyValueNode* pNodeB = dynamic_cast<TATKeyValueNode*>(pParentNodeB->GetChild(strName).begin()->second);

    BOOST_CHECK_EQUAL(pNodeA->GetType().ToString(), pNodeB->GetType().ToString());
    BOOST_CHECK_EQUAL(pNodeA->GetValue(), pNodeB->GetValue());
}

/// <summary>
/// Checks if the built instances are initialized as expected.
/// </summary>
QTEST_CASE ( Constructor_BuiltInstanceIsSetUpAsIntended_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATRuleNode* EXPECTED_RULE_TREE = new TATRuleNode();
    const wxString EXPECTED_SOURCE = wxT("");
    TATKeyValueNode* EXPECTED_VALUE_TREE = null_t;

	// Execution
    TATConfigLoaderFromIniFile configLoader(EXPECTED_RULE_TREE);

    // Verification
    BOOST_CHECK_EQUAL(configLoader.GetRuleTree(), EXPECTED_RULE_TREE);
    BOOST_CHECK_EQUAL(configLoader.GetSource(), EXPECTED_SOURCE);
    BOOST_CHECK_EQUAL(configLoader.GetValueTree(), EXPECTED_VALUE_TREE);
}

/// <summary>
/// Checks if any error occurs when destroying an instance.
/// </summary>
QTEST_CASE ( Destructor_NoErrorsOccur_Test )
{
    // Preparation
    TATConfigLoaderFromIniFile* CONFIG_LOADER = new TATConfigLoaderFromIniFile(null_t);
    const bool NO_ERRORS_OCCURRED = true;

	// Execution
    bool bNoErrorsOccurred = true;

    try
    {
        delete CONFIG_LOADER;
    }
    catch(...) // TODO [Thund]: A concrete exception type should be caught
    {
        bNoErrorsOccurred = false;
    }

    // Verification
    BOOST_CHECK_EQUAL(bNoErrorsOccurred, NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that a specialy prepared file is correctly parsed and the corresponding value tree properly created.
/// </summary>
QTEST_CASE ( Load_ValueTreeIsCorrectlyCreated_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATConfigLoaderFactory;
    using Kinesis::TestAutomationTool::Backend::ETATConfigurationSource;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;

    // Preparation
    const wxString SOURCE_OF_TEST_CONFIG_FILE = wxGetCwd() + wxT("/") + TAT_ARTIFACTS_DIRECTORY + wxT("/ConfigFileMock.ini");

    TATConfigLoaderFactory CONFIG_LOADER_FACTORY;
    TATConfigLoaderFromIniFile* CONFIG_LOADER = dynamic_cast<TATConfigLoaderFromIniFile*>(CONFIG_LOADER_FACTORY.CreateConfigLoader(ETATConfigurationSource::E_INI_FILE));
    CONFIG_LOADER->SetSource(SOURCE_OF_TEST_CONFIG_FILE);

    TATKeyValueNode EXPECTED_VALUE_TREE = TATKeyValueNode(wxT("ROOT"), ETATConfigNodeType::E_ROOT, wxT(""));

    TATKeyValueNode* COMPILER_HEADER_NODE = new TATKeyValueNode(wxT("C"), ETATConfigNodeType::E_HEADER, wxT("CValue"));
    EXPECTED_VALUE_TREE.AddChild( COMPILER_HEADER_NODE );
    COMPILER_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilerPath"), ETATConfigNodeType::E_VALUE, wxT("CompilerPathValue")) );
    COMPILER_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilerCleanCommand"), ETATConfigNodeType::E_VALUE, wxT("CompilerCleanCommandValue")) );
    COMPILER_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilerBuildCommand"), ETATConfigNodeType::E_VALUE, wxT("CompilerBuildCommandValue")) );
    COMPILER_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilerBuildParams"), ETATConfigNodeType::E_VALUE, wxT("CompilerBuildParamsValue")) );

    TATKeyValueNode* PROJECT_HEADER_NODE = new TATKeyValueNode(wxT("P"), ETATConfigNodeType::E_HEADER, wxT("PValue"));
    EXPECTED_VALUE_TREE.AddChild( PROJECT_HEADER_NODE );
    PROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("Compiler"), ETATConfigNodeType::E_VALUE, wxT("CompilerValue")) );
    PROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilationInfoPath"), ETATConfigNodeType::E_VALUE, wxT("CompilationInfoPathValue")) );

    TATKeyValueNode* FLAG_HEADER_NODE = new TATKeyValueNode(wxT("F"), ETATConfigNodeType::E_HEADER, wxT("FValue"));
    EXPECTED_VALUE_TREE.AddChild( FLAG_HEADER_NODE );
    FLAG_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("Option"), ETATConfigNodeType::E_VALUE, wxT("OptionValue")) );

    TATKeyValueNode* SUT_HEADER_NODE = new TATKeyValueNode(wxT("S"), ETATConfigNodeType::E_HEADER, wxT("SValue"));
    EXPECTED_VALUE_TREE.AddChild( SUT_HEADER_NODE );
    SUT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("ConfigurationFilePath"), ETATConfigNodeType::E_VALUE, wxT("ConfigurationFilePathValue")) );
    SUT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilerConfiguration"), ETATConfigNodeType::E_VALUE, wxT("CompilerConfigurationValue")) );

    TATKeyValueNode* TESTPROJECT_HEADER_NODE = new TATKeyValueNode(wxT("T"), ETATConfigNodeType::E_HEADER, wxT("TValue"));
    EXPECTED_VALUE_TREE.AddChild( TESTPROJECT_HEADER_NODE );
    TESTPROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("Compiler"), ETATConfigNodeType::E_VALUE, wxT("CompilerValue")) );
    TESTPROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("TestModulesPath"), ETATConfigNodeType::E_VALUE, wxT("TestModulesPathValue")) );
    TESTPROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("ResultsPath"), ETATConfigNodeType::E_VALUE, wxT("ResultsPathValue")) );
    TESTPROJECT_HEADER_NODE->AddChild( new TATKeyValueNode(wxT("CompilationInfoPath"), ETATConfigNodeType::E_VALUE, wxT("CompilationInfoPathValue")) );

	// Execution
    CONFIG_LOADER->Load();

    // Verification
    TATKeyValueNode* pValueTree = CONFIG_LOADER->GetValueTree();

    TATKeyValueNode* pCompilerNode = dynamic_cast<TATKeyValueNode*>(pValueTree->GetChild(wxT("C")).begin()->second);
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pValueTree, &EXPECTED_VALUE_TREE, wxT("C"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pCompilerNode, COMPILER_HEADER_NODE, wxT("CompilerPath"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pCompilerNode, COMPILER_HEADER_NODE, wxT("CompilerCleanCommand"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pCompilerNode, COMPILER_HEADER_NODE, wxT("CompilerBuildCommand"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pCompilerNode, COMPILER_HEADER_NODE, wxT("CompilerBuildParams"));

    TATKeyValueNode* pProjectNode = dynamic_cast<TATKeyValueNode*>(pValueTree->GetChild(wxT("P")).begin()->second);
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pValueTree, &EXPECTED_VALUE_TREE, wxT("P"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pProjectNode, PROJECT_HEADER_NODE, wxT("Compiler"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pProjectNode, PROJECT_HEADER_NODE, wxT("CompilationInfoPath"));

    TATKeyValueNode* pFlagNode = dynamic_cast<TATKeyValueNode*>(pValueTree->GetChild(wxT("F")).begin()->second);
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pValueTree, &EXPECTED_VALUE_TREE, wxT("F"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pFlagNode, FLAG_HEADER_NODE, wxT("Option"));

    TATKeyValueNode* pSutNode = dynamic_cast<TATKeyValueNode*>(pValueTree->GetChild(wxT("S")).begin()->second);
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pValueTree, &EXPECTED_VALUE_TREE, wxT("S"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pSutNode, SUT_HEADER_NODE, wxT("ConfigurationFilePath"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pSutNode, SUT_HEADER_NODE, wxT("CompilerConfiguration"));

    TATKeyValueNode* pTestProjectNode = dynamic_cast<TATKeyValueNode*>(pValueTree->GetChild(wxT("T")).begin()->second);
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pValueTree, &EXPECTED_VALUE_TREE, wxT("T"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pTestProjectNode, TESTPROJECT_HEADER_NODE, wxT("Compiler"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pTestProjectNode, TESTPROJECT_HEADER_NODE, wxT("TestModulesPath"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pTestProjectNode, TESTPROJECT_HEADER_NODE, wxT("ResultsPath"));
    CheckTwoKeyValueNodesAreEqual_HelperMethod(pTestProjectNode, TESTPROJECT_HEADER_NODE, wxT("CompilationInfoPath"));

    // Cleaning
    delete CONFIG_LOADER;
}

/// <summary>
/// Checks that the rule tree has been released (checks for null and for empty).
/// </summary>
QTEST_CASE ( Destroy_RuleTreeIsReleased_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATRuleNodeMock;
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNodeMock());
    const int EXPECTED_CALLS_TO_DESTRUCTOR = 1;
    const TATRuleNode* null_t_RULE_TREE = null_t;

	// Execution
    CONFIG_LOADER.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TATRuleNodeMock::sm_nDestructorCallCounter, EXPECTED_CALLS_TO_DESTRUCTOR);
    BOOST_CHECK_EQUAL(CONFIG_LOADER.GetRuleTree(), null_t_RULE_TREE);
}

/// <summary>
/// Checks that a validation exception is thrown when there are more node occurrences than the maximum allowed by a rule.
/// </summary>
QTEST_CASE ( ApplyRule_ValidationExceptionIsThrownWhenThereAreMoreNodeOccurencesThanMaximumAllowed_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const int MAXCOUNT = 1;
    TATRuleNode RULE_NODE = TATRuleNode(wxT("TestNode"), MAXCOUNT, true, true, ETATConfigNodeType::E_HEADER);
    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("TestNodeParent"), ETATConfigNodeType::E_ROOT, wxT("ParentTestValue"));
    TATKeyValueNode* pValueNode1 = new TATKeyValueNode(wxT("TestNode"), ETATConfigNodeType::E_HEADER, wxT("TestValue1"));
    TATKeyValueNode* pValueNode2 = new TATKeyValueNode(wxT("TestNode"), ETATConfigNodeType::E_HEADER, wxT("TestValue2"));
    ROOT_VALUE_NODE.AddChild(pValueNode1);
    ROOT_VALUE_NODE.AddChild(pValueNode2);

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyRule(pValueNode1, &RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is NOT thrown when there are less or equal node occurrences than the maximum allowed by a rule.
/// </summary>
QTEST_CASE ( ApplyRule_ValidationExceptionIsNotThrownWhenThereAreLessOrEqualNodeOccurencesThanMaximumAllowed_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const int MAXCOUNT = 1;
    TATRuleNode RULE_NODE = TATRuleNode(wxT("TestNode"), MAXCOUNT, true, true, ETATConfigNodeType::E_HEADER);
    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("TestNodeParent"), ETATConfigNodeType::E_ROOT, wxT("ParentTestValue"));
    TATKeyValueNode* pValueNode = new TATKeyValueNode(wxT("TestNode"), ETATConfigNodeType::E_HEADER, wxT("TestValue"));
    ROOT_VALUE_NODE.AddChild(pValueNode);

    const bool EXPECTED_VALUE = false;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyRule(pValueNode, &RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is thrown when the value node is empty and empty values are not allowed.
/// </summary>
QTEST_CASE ( ApplyRule_ValidationExceptionIsThrownWhenNodeIsEmptyAndItIsNotAllowed_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool CAN_BE_EMPTY = false;
    const wxString EMPTY_VALUE = wxT("");
    TATRuleNode RULE_NODE = TATRuleNode(wxT("TestNode"), 1, CAN_BE_EMPTY, true, ETATConfigNodeType::E_HEADER);
    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("TestNodeParent"), ETATConfigNodeType::E_ROOT, wxT("ParentTestValue"));
    TATKeyValueNode* pValueNode = new TATKeyValueNode(wxT("TestNode"), ETATConfigNodeType::E_HEADER, EMPTY_VALUE);
    ROOT_VALUE_NODE.AddChild(pValueNode);

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyRule(pValueNode, &RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is NOT thrown when the value node is not empty and empty values are not allowed.
/// </summary>
QTEST_CASE ( ApplyRule_ValidationExceptionIsNotThrownWhenNodeIsNotEmptyAndEmptyNodeIsNotAllowed_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool CAN_BE_EMPTY = false;
    const wxString NONEMPTY_VALUE = wxT("NodeValue");
    TATRuleNode RULE_NODE = TATRuleNode(wxT("TestNode"), 1, CAN_BE_EMPTY, true, ETATConfigNodeType::E_HEADER);
    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("TestNodeParent"), ETATConfigNodeType::E_ROOT, wxT("ParentTestValue"));
    TATKeyValueNode* pValueNode = new TATKeyValueNode(wxT("TestNode"), ETATConfigNodeType::E_HEADER, NONEMPTY_VALUE);
    ROOT_VALUE_NODE.AddChild(pValueNode);

    const bool EXPECTED_VALUE = false;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyRule(pValueNode, &RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is thrown when a value tree doesn't contain an obligatory header node.
/// </summary>
QTEST_CASE ( ApplyFinalRules_ValidationExceptionIsThrownWhenValueTreeDoesntContainObligatoryHeaderNodes_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool IS_OBLIGATORY = true;

    TATRuleNode ROOT_RULE_NODE = TATRuleNode(wxT("RootRuleNode"), 1, true, true, ETATConfigNodeType::E_ROOT);
    ROOT_RULE_NODE.AddChild( new TATRuleNode(wxT("HeaderNode"), 1, true, IS_OBLIGATORY, ETATConfigNodeType::E_HEADER));

    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("RootValueNode"), ETATConfigNodeType::E_ROOT, wxT("RootValueNodeValue"));
    ROOT_VALUE_NODE.AddChild(new TATKeyValueNode(wxT("HeaderNode1"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue1")));
    ROOT_VALUE_NODE.AddChild(new TATKeyValueNode(wxT("HeaderNode2"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue2")));

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyFinalRules(&ROOT_RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is NOT thrown when a value tree contains an obligatory header node.
/// </summary>
QTEST_CASE ( ApplyFinalRules_ValidationExceptionIsNotThrownWhenValueTreeContainsObligatoryHeaderNodes_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool IS_OBLIGATORY = true;

    TATRuleNode ROOT_RULE_NODE = TATRuleNode(wxT("RootRuleNode"), 1, true, true, ETATConfigNodeType::E_ROOT);
    ROOT_RULE_NODE.AddChild( new TATRuleNode(wxT("HeaderNode"), 1, true, IS_OBLIGATORY, ETATConfigNodeType::E_HEADER));

    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("RootValueNode"), ETATConfigNodeType::E_ROOT, wxT("RootValueNodeValue"));
    ROOT_VALUE_NODE.AddChild(new TATKeyValueNode(wxT("HeaderNode"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue")));
    ROOT_VALUE_NODE.AddChild(new TATKeyValueNode(wxT("HeaderNode2"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue2")));

    const bool EXPECTED_VALUE = false;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyFinalRules(&ROOT_RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is thrown when a value tree doesn't contain an obligatory value node.
/// </summary>
QTEST_CASE ( ApplyFinalRules_ValidationExceptionIsThrownWhenValueTreeDoesntContainObligatoryValueNodes_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool IS_OBLIGATORY = true;

    TATRuleNode ROOT_RULE_NODE = TATRuleNode(wxT("RootRuleNode"), 1, true, true, ETATConfigNodeType::E_ROOT);
    TATRuleNode* pHeaderRuleNode = new TATRuleNode(wxT("HeaderNode"), 1, true, true, ETATConfigNodeType::E_HEADER);
    ROOT_RULE_NODE.AddChild(pHeaderRuleNode);
    pHeaderRuleNode->AddChild( new TATRuleNode(wxT("ValueNode"), 1, true, IS_OBLIGATORY, ETATConfigNodeType::E_VALUE) );

    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("RootValueNode"), ETATConfigNodeType::E_ROOT, wxT("RootValueNodeValue"));
    TATKeyValueNode* pHeaderValueNode = new TATKeyValueNode(wxT("HeaderNode"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue"));
    ROOT_VALUE_NODE.AddChild(pHeaderValueNode);
    pHeaderValueNode->AddChild(new TATKeyValueNode(wxT("ValueNode1"), ETATConfigNodeType::E_VALUE, wxT("ValueNodeValue1")));

    const bool EXPECTED_VALUE = true;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyFinalRules(&ROOT_RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a validation exception is thrown when a value tree contains an obligatory value node.
/// </summary>
QTEST_CASE ( ApplyFinalRules_ValidationExceptionIsNotThrownWhenValueTreeContainsObligatoryValueNodes_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;
    using Kinesis::TestAutomationTool::Backend::TATValidationException;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const bool IS_OBLIGATORY = true;

    TATRuleNode ROOT_RULE_NODE = TATRuleNode(wxT("RootRuleNode"), 1, true, true, ETATConfigNodeType::E_ROOT);
    TATRuleNode* pHeaderRuleNode = new TATRuleNode(wxT("HeaderNode"), 1, true, true, ETATConfigNodeType::E_HEADER);
    ROOT_RULE_NODE.AddChild(pHeaderRuleNode);
    pHeaderRuleNode->AddChild( new TATRuleNode(wxT("ValueNode"), 1, true, IS_OBLIGATORY, ETATConfigNodeType::E_VALUE) );

    TATKeyValueNode ROOT_VALUE_NODE = TATKeyValueNode(wxT("RootValueNode"), ETATConfigNodeType::E_ROOT, wxT("RootValueNodeValue"));
    TATKeyValueNode* pHeaderValueNode = new TATKeyValueNode(wxT("HeaderNode"), ETATConfigNodeType::E_HEADER, wxT("HeaderNodeValue"));
    ROOT_VALUE_NODE.AddChild(pHeaderValueNode);
    pHeaderValueNode->AddChild(new TATKeyValueNode(wxT("ValueNode"), ETATConfigNodeType::E_VALUE, wxT("ValueNodeValue")));

    const bool EXPECTED_VALUE = false;

	// Execution
    bool bExceptionThrown = false;

    try
    {
        CONFIG_LOADER.ApplyFinalRules(&ROOT_RULE_NODE, &ROOT_VALUE_NODE);
    }
    catch(const TATValidationException& ex)
    {
        bExceptionThrown = true;
    }

    // Verification
    BOOST_CHECK_EQUAL(bExceptionThrown, EXPECTED_VALUE);
}

/// <summary>
/// Checks whether the type returned is Header when the input line of text represents a header.
/// </summary>
QTEST_CASE ( GetTypeOfNode_HeaderTypeIsReturnedWhenTheLineOfTextContainsAHeader_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const ETATConfigNodeType EXPECTED_TYPE = ETATConfigNodeType::E_HEADER;
    const wxString INPUT_TEXT_LINE = wxT("[HeaderName=HeaderValue]");

	// Execution
    ETATConfigNodeType eReturnedType = CONFIG_LOADER.GetTypeOfNode(INPUT_TEXT_LINE);

    // Verification
    BOOST_CHECK_EQUAL(eReturnedType.ToString(), EXPECTED_TYPE.ToString());
}


/// <summary>
/// Checks whether the type returned is Value when the input line of text represents a value.
/// </summary>
QTEST_CASE ( GetTypeOfNode_ValueTypeIsReturnedWhenTheLineOfTextContainsAValue_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const ETATConfigNodeType EXPECTED_TYPE = ETATConfigNodeType::E_VALUE;
    const wxString INPUT_TEXT_LINE = wxT("ValueName=ValueValue");

	// Execution
    ETATConfigNodeType eReturnedType = CONFIG_LOADER.GetTypeOfNode(INPUT_TEXT_LINE);

    // Verification
    BOOST_CHECK_EQUAL(eReturnedType.ToString(), EXPECTED_TYPE.ToString());
}

/// <summary>
/// Checks that the name of the key-value pair represented by the line of text is correctly returned.
/// </summary>
QTEST_CASE ( GetNameOfNode_TheNamePartIsCorrectlyReturned_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const wxString EXPECTED_NAME = wxT("HeaderName");
    const wxString INPUT_TEXT_LINE = wxT("[") + EXPECTED_NAME + wxT("=HeaderValue]");

	// Execution
    wxString strName = CONFIG_LOADER.GetNameOfNode(INPUT_TEXT_LINE);

    // Verification
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME);
}

/// <summary>
/// Checks that the value of the key-value pair represented by the line of text is correctly returned.
/// </summary>
QTEST_CASE ( GetValueOfNode_TheValuePartIsCorrectlyReturned_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    const wxString EXPECTED_VALUE = wxT("HeaderValue");
    const wxString INPUT_TEXT_LINE = wxT("[HeaderName=") + EXPECTED_VALUE + wxT("]");

	// Execution
    wxString strValue = CONFIG_LOADER.GetValueOfNode(INPUT_TEXT_LINE);

    // Verification
    BOOST_CHECK_EQUAL(strValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the correct value is returned.
/// </summary>
QTEST_CASE ( GetRuleTree_ReturnedCorrectValue_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATRuleNode* EXPECTED_VALUE = new TATRuleNode();
    TATConfigLoaderFromIniFile CONFIG_LOADER(EXPECTED_VALUE);

	// Execution
    TATRuleNode* pReturnedValue = CONFIG_LOADER.GetRuleTree();

    // Verification
    BOOST_CHECK_EQUAL(pReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the correct value is returned.
/// </summary>
QTEST_CASE ( GetValueTree_ReturnedCorrectValue_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;
    using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
    using Kinesis::TestAutomationTool::Backend::Test::TATConfigLoaderFromIniFileWhiteBox;

    // Preparation
    TATKeyValueNode* EXPECTED_VALUE = new TATKeyValueNode();
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNode());
    CONFIG_LOADER.SetValueTreeForTesting(EXPECTED_VALUE);

	// Execution
    TATKeyValueNode* pReturnedValue = CONFIG_LOADER.GetValueTree();

    // Verification
    BOOST_CHECK_EQUAL(pReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the correct value is returned.
/// </summary>
QTEST_CASE ( GetSource_ReturnedCorrectValue_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE = wxT("SOURCE");
    TATConfigLoaderFromIniFile CONFIG_LOADER(null_t);
    CONFIG_LOADER.SetSource(EXPECTED_VALUE);

	// Execution
    wxString strReturnedValue = CONFIG_LOADER.GetSource();

    // Verification
    BOOST_CHECK_EQUAL(strReturnedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
QTEST_CASE ( SetSource_ValueIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE = wxT("SOURCE");
    TATConfigLoaderFromIniFile CONFIG_LOADER(null_t);

	// Execution
    CONFIG_LOADER.SetSource(EXPECTED_VALUE);

    // Verification
    wxString strReturnedValue = CONFIG_LOADER.GetSource();
    BOOST_CHECK_EQUAL(CONFIG_LOADER.GetSource(), EXPECTED_VALUE);
}

// End - Test Suite: TATConfigLoaderFromIniFile
QTEST_SUITE_END()
