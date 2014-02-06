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

#include "TestResults/TATXmlReader.h"

using Kinesis::TestAutomationTool::Backend::TATXmlReader;

typedef std::string string_t;

QTEST_SUITE_BEGIN( TATXmlReader_TestSuite )

/// <summary>
/// Not tested. It only calls read_xml function with the same parameters, there is no additional logic. The cost of testing that is so high.
/// </summary>
QTEST_CASE ( ParseXml_NotTested_Test )
{
    BOOST_MESSAGE("It only calls read_xml function with the same parameters, there is no additional logic. The cost of testing that is so high.");
}

/// <summary>
/// Checks that the value of the given attribute, which exists in the XML data, is returned.
/// </summary>
QTEST_CASE ( GetAttribute_ExpectedValueReturnedWhenAttributeExists_Test )
{
    // [Preparation]
    const string_t ATTRIBUTE_NAME = string_t("name");
    const string_t EXPECTED_VALUE = string_t("TestModule1");
    TATXmlReader<string_t> xmlReaderUT;

    std::istringstream XML_DATA(string_t("                                                          \
                    <TestLog>                                                                       \
                      <TestSuite name=\"") + EXPECTED_VALUE + "\">                                  \
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

    TATXmlReader<string_t>::TXmlTree XML_TREE;
    xmlReaderUT.ParseXml(XML_DATA, XML_TREE);
    TATXmlReader<string_t>::TXmlTree TESTMODULE1_SUBTREE = XML_TREE.begin()->second.begin()->second;

	// [Execution]
    string_t strAttributeValue = xmlReaderUT.GetAttribute<string_t>(TESTMODULE1_SUBTREE, ATTRIBUTE_NAME);

    // [Verification]
    BOOST_CHECK_EQUAL(strAttributeValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the expected value of the content of a concrete node (sub-tree) is returned.
/// </summary>
QTEST_CASE ( GetContent_ExpectedValueReturned_Test )
{
    // [Preparation]
    const string_t EXPECTED_VALUE = string_t("Message1");
    TATXmlReader<string_t> xmlReaderUT;

    std::istringstream XML_DATA(string_t("                                                          \
                    <TestLog>                                                                       \
                      <TestSuite name=\"") + EXPECTED_VALUE + "\">                                  \
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

    TATXmlReader<string_t>::TXmlTree XML_TREE;
    xmlReaderUT.ParseXml(XML_DATA, XML_TREE);
    TATXmlReader<string_t>::TXmlTree TESTRESULT1_SUBTREE = XML_TREE.begin()->second.begin()->second.begin()->second.begin()->second;
    string_t yeah = TESTRESULT1_SUBTREE.get_value<string_t>();

	// [Execution]
    string_t strContentValue = xmlReaderUT.GetContent<string_t>(TESTRESULT1_SUBTREE);

    // [Verification]
    BOOST_CHECK_EQUAL(strContentValue, EXPECTED_VALUE);
}

// End - Test Suite: TATXmlReader
QTEST_SUITE_END()
