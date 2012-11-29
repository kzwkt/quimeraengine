// [TERMS&CONDITIONS]

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../../testsystem/TestingExternalDefinitions.h"

#include "TestConfiguration/TATKeyValueNode.h"
#include "TestConfiguration/ETATConfigNodeType.h"

using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::ETATConfigNodeType;

QTEST_SUITE_BEGIN( TATKeyValueNode_TestSuite )

/// <summary>
/// Checks that default values has not changed.
/// </summary>
QTEST_CASE ( Constructor1_DefaultValuesHasNotChanged_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("");
    const wxString EXPECTED_NAME_VALUE = wxT("");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_ROOT;

	// Execution
    TATKeyValueNode nodeUT;
    wxString strDefaultValue = nodeUT.GetValue();
    wxString strDefaultName = nodeUT.GetName();
    ETATConfigNodeType eDefaultType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(strDefaultValue, EXPECTED_VALUE_VALUE);
    BOOST_CHECK_EQUAL(strDefaultName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(eDefaultType.ToString() == EXPECTED_TYPE_VALUE.ToString());
}

/// <summary>
/// Checks that every parameter of is correctly stored.
/// </summary>
QTEST_CASE ( Constructor2_AllValuesAreCorrectlySet_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");
    const wxString EXPECTED_NAME_VALUE = wxT("NAME");
    const ETATConfigNodeType EXPECTED_TYPE_VALUE = ETATConfigNodeType::E_VALUE;

	// Execution
    TATKeyValueNode nodeUT(EXPECTED_NAME_VALUE, EXPECTED_TYPE_VALUE, EXPECTED_VALUE_VALUE);
    wxString strValue = nodeUT.GetValue();
    wxString strName = nodeUT.GetName();
    ETATConfigNodeType eType = nodeUT.GetType();
    
    // Verification
    BOOST_CHECK_EQUAL(strValue, EXPECTED_VALUE_VALUE);
    BOOST_CHECK_EQUAL(strName, EXPECTED_NAME_VALUE);
    BOOST_CHECK(eType.ToString() == EXPECTED_TYPE_VALUE.ToString());
}

/// <summary>
/// Checks that the value is correctly retrieved.
/// </summary>
QTEST_CASE ( GetValue_ValueIsCorrectlyRetrieved_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");
    TATKeyValueNode NODE;
    NODE.SetValue(EXPECTED_VALUE_VALUE);

	// Execution
    wxString strValueUT = NODE.GetValue();
    
    // Verification
    BOOST_CHECK_EQUAL(strValueUT, EXPECTED_VALUE_VALUE);
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
QTEST_CASE ( SetValue_ValueIsCorrectlyStored_Test )
{
    // Preparation
    const wxString EXPECTED_VALUE_VALUE = wxT("VALUE");

	// Execution
    TATKeyValueNode nodeUT;
    nodeUT.SetValue(EXPECTED_VALUE_VALUE);

    // Verification
    BOOST_CHECK_EQUAL(nodeUT.GetValue(), EXPECTED_VALUE_VALUE);
}


// End - Test Suite: TATKeyValueNode
QTEST_SUITE_END()
