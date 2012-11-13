// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestConfiguration/TATConfigLoaderFromIniFile.h"
#include "TATConfigLoaderFromIniFileWhiteBox.h"
#include "TestConfiguration/TATRuleNode.h"
#include "TATRuleNodeMock.h"

using Kinesis::TestAutomationTool::Backend::TATConfigLoaderFromIniFile;
using Kinesis::TestAutomationTool::Backend::Test::TATConfigLoaderFromIniFileWhiteBox;


QTEST_SUITE_BEGIN( TATConfigLoaderFromIniFile_TestSuite )

/// <summary>
/// Checks if the built instances are initialized as expected.
/// </summary>
QTEST_CASE ( Constructor_BuiltInstanceIsSetUpAsIntended_Test )
{
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATRuleNode* EXPECTED_RULE_TREE = new TATRuleNode();
    const wxString EXPECTED_SOURCE = wxT("");

	// Execution
    TATConfigLoaderFromIniFile configLoader(EXPECTED_RULE_TREE);

    // Verification
    BOOST_CHECK_EQUAL(configLoader.GetRuleTree(), EXPECTED_RULE_TREE);
    BOOST_CHECK_EQUAL(configLoader.GetSource(), EXPECTED_SOURCE);
}

/// <summary>
/// Checks if any error occurs when destroying an instance.
/// </summary>
QTEST_CASE ( Destructor_NoErrorsOccur_Test )
{
    // Preparation
    TATConfigLoaderFromIniFile* CONFIG_LOADER = new TATConfigLoaderFromIniFile(NULL);
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
/// Checks that all the resources have been released (checks for null and for empty).
/// </summary>
QTEST_CASE ( Destroy_AllResourcesAreReleased_Test )
{
    using Kinesis::TestAutomationTool::Backend::Test::TATRuleNodeMock;
    using Kinesis::TestAutomationTool::Backend::TATRuleNode;

    // Preparation
    TATConfigLoaderFromIniFileWhiteBox CONFIG_LOADER(new TATRuleNodeMock());
    const int EXPECTED_CALLS_TO_DESTRUCTOR = 1;
    const TATRuleNode* NULL_RULE_TREE = NULL;

	// Execution
    CONFIG_LOADER.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TATRuleNodeMock::sm_nDestructorCallCounter, EXPECTED_CALLS_TO_DESTRUCTOR);
    BOOST_CHECK_EQUAL(CONFIG_LOADER.GetRuleTree(), NULL_RULE_TREE);
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
QTEST_CASE ( GetSource_ReturnedCorrectValue_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE = wxT("SOURCE");
    TATConfigLoaderFromIniFile CONFIG_LOADER(NULL);
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
    TATConfigLoaderFromIniFile CONFIG_LOADER(NULL);
    
	// Execution
    CONFIG_LOADER.SetSource(EXPECTED_VALUE);
    
    // Verification
    wxString strReturnedValue = CONFIG_LOADER.GetSource();
    BOOST_CHECK_EQUAL(CONFIG_LOADER.GetSource(), EXPECTED_VALUE);
}

// End - Test Suite: TATConfigLoaderFromIniFile
QTEST_SUITE_END()
