// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATTestAutomationToolExecution.h"
#include "TATTestAutomationToolExecutionWhiteBox.h"

using Kinesis::TestAutomationTool::Backend::TATTestAutomationToolExecution;
using Kinesis::TestAutomationTool::Backend::Test::TATTestAutomationToolExecutionWhiteBox;

QTEST_SUITE_BEGIN( TATTestAutomationToolExecution_TestSuite )

/// <summary>
/// Checks that all the parameters are stored as members of the class as expected.
/// </summary>
QTEST_CASE ( Constructor_AllParametersAreStored_Test )
{
    // [TODO] Thund: Implement when the constructor is implemented
    // Preparation

	// Execution
    
    // Verification

	// Cleaning
}

/// <summary>
/// Checks if any error occurs during destruction.
/// </summary>
QTEST_CASE ( Destroy_NoErrorOccurred_Test )
{
    // Preparation
    const bool NO_ERROR_OCURRED = true;
    
    TATTestAutomationToolExecutionWhiteBox* TESTAUTOMATIONTOOL_EXECUTION = new TATTestAutomationToolExecutionWhiteBox();

	// Execution
    bool bNoErrorOcurred = true;

    try
    {
        delete TESTAUTOMATIONTOOL_EXECUTION;
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
    // [TODO] Thund: Implement when there are resources to free

    // Preparation
    TATTestAutomationToolExecutionWhiteBox TESTAUTOMATIONTOOL_EXECUTION;

	// Execution
    TESTAUTOMATIONTOOL_EXECUTION.Destroy();

    // Verification
    //BOOST_CHECK_EQUAL(TESTAUTOMATIONTOOL_EXECUTION.GetConfigLoader(), CONFIGURATION_LOADER_NULL);
}

// End - Test Suite: TATTestAutomationToolExecution
QTEST_SUITE_END()
