// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestExecution/TATTestResultLoaderFactory.h"
#include "TATTestResultLoaderFactoryWhiteBox.h"

using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
using Kinesis::TestAutomationTool::Backend::Test::TATTestResultLoaderFactoryWhiteBox;

QTEST_SUITE_BEGIN( TATTestResultLoaderFactory_TestSuite )

/// <summary>
/// Checks that returns an object (not null) when the test result source is valid.
/// </summary>
QTEST_CASE ( CreateConfigLoader_ReturnsAnObjectWhenSourceIsValid_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

    // [Preparation]
    const bool RETURNS_OBJECT = true;

	// [Execution]
    TATTestResultLoaderFactory testResultLoaderFactoryUT;
    ITATTestResultLoader* pObject = testResultLoaderFactoryUT.CreateConfigLoader(ETATResultSource::E_XmlFile);

    // [Verification]
    bool bObjectWasReturned = (pObject != null_t);
    BOOST_CHECK_EQUAL(bObjectWasReturned, RETURNS_OBJECT);

	// [Cleaning]
    delete pObject;
}

/// <summary>
/// Checks that returns null when the test result source is not valid.
/// </summary>
QTEST_CASE ( CreateConfigLoader_ReturnsNullWhenSourceIsNotValid_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

    // [Preparation]
    ITATTestResultLoader* EXPECTED_RESULT = null_t;

	// [Execution]
    TATTestResultLoaderFactory testResultLoaderFactoryUT;
    ITATTestResultLoader* pObject = testResultLoaderFactoryUT.CreateConfigLoader(ETATResultSource::_NotEnumValue);

    // [Verification]
    BOOST_CHECK_EQUAL(pObject, EXPECTED_RESULT);
}

/// <summary>
/// Checks that returns an object (not null). Object's properties are not checked.
/// </summary>
QTEST_CASE ( CreateTestResultLoaderFromXmlFile_ReturnsAnObject_Test )
{
    using Kinesis::TestAutomationTool::Backend::ETATResultSource;
    using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

    // [Preparation]
    const bool RETURNS_OBJECT = true;

	// [Execution]
    TATTestResultLoaderFactoryWhiteBox testResultLoaderFactoryUT;
    ITATTestResultLoader* pObject = testResultLoaderFactoryUT.CreateTestResultLoaderFromXmlFile();

    // [Verification]
    bool bObjectWasReturned = (pObject != null_t);
    BOOST_CHECK_EQUAL(bObjectWasReturned, RETURNS_OBJECT);

	// [Cleaning]
    delete pObject;
}

// End - Test Suite: TATTestResultLoaderFactory
QTEST_SUITE_END()
