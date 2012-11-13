// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestConfiguration/TATTestAutomationToolConfiguration.h"
#include "TestConfiguration/ITATConfigLoader.h"
#include "TATTestAutomationToolConfigurationWhiteBox.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolConfiguration;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolConfigurationWhiteBox;
using Kinesis::TestAutomationTool::Backend::ITATConfigLoader;

QTEST_SUITE_BEGIN( TATTestAutomationToolConfiguration_TestSuite )

/// <summary>
/// Checks if the values set in the default constructor have changed.
/// </summary>
QTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // TODO [Thund]: This test has to be completed when more properties are initialized in future tasks.

    // Preparation
    ITATConfigLoader* CONFIGURATION_LOADER_NULL = NULL;
    const wxString CONFIGURATION_LOADER_SOURCE = wxT("config.ini");
    
	// Execution
    TATTestAutomationToolConfiguration testAutomationToolConfigurationUT;
    
    // Verification
    BOOST_CHECK_NE(testAutomationToolConfigurationUT.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
    BOOST_CHECK_EQUAL(testAutomationToolConfigurationUT.GetConfigLoader()->GetSource(), CONFIGURATION_LOADER_SOURCE);
}

/// <summary>
/// Checks if any error occurs during destruction.
/// </summary>
QTEST_CASE ( Destroy_NoErrorOccurred_Test )
{
    // Preparation
    const bool NO_ERROR_OCURRED = true;
    
    TATTestAutomationToolConfigurationWhiteBox* TESTAUTOMATIONTOOL_CONFIGURATION = new TATTestAutomationToolConfigurationWhiteBox();

	// Execution
    bool bNoErrorOcurred = true;

    try
    {
        delete TESTAUTOMATIONTOOL_CONFIGURATION;
    }
    catch(...) // TODO [Thund]: A concrete exception type should be caught
    {
        bNoErrorOcurred = false;
    }

    // Verification
    BOOST_CHECK_EQUAL(bNoErrorOcurred, NO_ERROR_OCURRED);
}

/// <summary>
/// Checks if all the resources have been released. It's not a deep check but a "check for null" or "check for empty" test.
/// </summary>
QTEST_CASE ( Destroy_AllResourcesAreReleased_Test )
{
    // Preparation
    ITATConfigLoader* CONFIGURATION_LOADER_NULL = NULL;
    TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;

	// Execution
    TESTAUTOMATIONTOOL_CONFIGURATION.Destroy();

    // Verification
    BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_CONFIGURATION.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
}

/// <summary>
/// Checks if the property returns what's expected.
/// </summary>
QTEST_CASE ( GetConfigLoader_ExpectedValueIsReturned_Test )
{
    // Preparation
    const TATTestAutomationToolConfigurationWhiteBox TESTAUTOMATIONTOOL_CONFIGURATION;
    ITATConfigLoader* EXPECTED_CONFIGLOADER = TESTAUTOMATIONTOOL_CONFIGURATION.GetExpectedConfigLoader();

	// Execution
    ITATConfigLoader* pReturnedValue = TESTAUTOMATIONTOOL_CONFIGURATION.GetConfigLoader();

    // Verification
    BOOST_CHECK_EQUAL(pReturnedValue, EXPECTED_CONFIGLOADER);
}

// End - Test Suite: TATTestAutomationToolConfiguration
QTEST_SUITE_END()
