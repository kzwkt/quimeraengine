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

#include "TestResults/TATTestResultLoader.h"

#include "TestResults/TATXmlReader.h"
#include "TestResults/ETATResult.h"
#include "TestResults/TATTestResultNode.h"
#include "STATFileSystemHelper.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultLoader::TATTestResultLoader() : m_pTestResultTree(NULL)
{
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultLoader::~TATTestResultLoader()
{
    this->Destroy();
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestResultLoader::Load(const wxString &strSource)
{
    if(m_pTestResultTree == NULL)
    {
        // Creates the root node
        m_pTestResultTree = new TATTestResultNode(wxT("ROOT"));
    }

    TATTestResultNode* pResultTree = NULL;

    // Reads file content
    wxString strFileContent;
    
    if(STATFileSystemHelper::Read(strSource, strFileContent))
    {
        // Parses the XML string
        TATXmlReader<std::string> reader;
        pResultTree = this->ParseXmlToTree(strFileContent, reader);

        // Processes the result
        pResultTree->SetMessage(strSource);
    }

    if(pResultTree != NULL)
    {
        m_pTestResultTree->AddChild(pResultTree);
    }
}

void TATTestResultLoader::Destroy()
{
    if(m_pTestResultTree != NULL)
    {
        delete m_pTestResultTree;
        m_pTestResultTree = NULL;
    }
}

TATTestResultNode* TATTestResultLoader::ParseXmlToTree(const wxString &strXmlData, TATXmlReader<std::string> &xmlReader)
{
    // [TODO] Thund: Add a fallback mechanism to delete all created nodes when something fails

    const wxString XMLROOT_TAG = wxT("TestLog");
    const wxString TESTMODULE_TAG = wxT("TestSuite");
    const wxString TESTSUITE_TAG = wxT("TestSuite");
    const wxString TESTCASE_TAG = wxT("TestCase");
    const wxString MESSAGE_TAG = wxT("Message");
    const wxString ERROR_TAG = wxT("Error");
    const wxString INFO_TAG = wxT("Info");
    const wxString EXCEPTION_TAG = wxT("Exception");
    const wxString TIME_TAG = wxT("TestingTime");
    const wxString NAME_ATTRIB = wxT("name");
    const wxString FILE_ATTRIB = wxT("file");

    TATTestResultNode* pResultTree = NULL;

    // Parses the xml
    std::istringstream inputData(strXmlData.ToStdString());
    TATXmlReader<std::string>::TXmlTree xmlTree;

    xmlReader.ParseXml(inputData, xmlTree);

    // Processes the XML elements

    typedef TATXmlReader<std::string>::TXmlTree::iterator TXmlTreeIterator;

    // Root
    TXmlTreeIterator rootNode = xmlTree.begin();

    if(rootNode->first == XMLROOT_TAG)
    {
        TATTestResultNode* pRootNode = new TATTestResultNode(wxT("ROOT"));

        // Test modules
        for(TXmlTreeIterator iTestModule = rootNode->second.begin(); iTestModule != rootNode->second.end(); ++iTestModule)
        {
            // Name
            wxString strTestSuiteName = xmlReader.GetAttribute<std::string>(iTestModule->second, NAME_ATTRIB.ToStdString());

            TATTestResultNode* pTestModuleNode = new TATTestResultNode(strTestSuiteName);
            pTestModuleNode->SetNodeType(ETATTestResultNodeType::E_Module);

            for(TXmlTreeIterator iTestSuite = iTestModule->second.begin(); iTestSuite != iTestModule->second.end(); ++iTestSuite)
            {
                if(iTestSuite->first == TESTSUITE_TAG)
                {
                    // Name
                    wxString strTestSuiteName = xmlReader.GetAttribute<std::string>(iTestSuite->second, NAME_ATTRIB.ToStdString());

                    TATTestResultNode* pTestSuiteNode = new TATTestResultNode(strTestSuiteName);
                    pTestSuiteNode->SetNodeType(ETATTestResultNodeType::E_Suite);

                    // Test cases
                    for(TXmlTreeIterator iTestCase = iTestSuite->second.begin(); iTestCase != iTestSuite->second.end(); ++iTestCase)
                    {
                        if(iTestCase->first == TESTCASE_TAG)
                        {
                            // Name
                            wxString strTestCaseName = xmlReader.GetAttribute<std::string>(iTestCase->second, NAME_ATTRIB.ToStdString());

                            TATTestResultNode* pTestCaseNode = new TATTestResultNode(strTestCaseName);
                            pTestCaseNode->SetNodeType(ETATTestResultNodeType::E_Case);

                            if(iTestCase->second.size() == 0)
                            {
                                // This is an strange case, a test case without results. Normally, this is due to a malfunction or unexpected errors
                                pTestCaseNode->AddChild(new TATTestResultNode(ERROR_TAG, 
                                                                              ETATResult::E_Error, 
                                                                              wxT("Empty test case. Maybe some unexpected errors occurred during test execution."), 
                                                                              0, 
                                                                              ETATTestResultNodeType::E_Result));
                            }

                            // Test results
                            for(TXmlTreeIterator iTestResult = iTestCase->second.begin(); iTestResult != iTestCase->second.end(); ++iTestResult)
                            {
                                TATTestResultNode* pTestResultNode = NULL;

                                // Time
                                if(iTestResult->first == TIME_TAG)
                                {
                                    unsigned int nTestingTime = xmlReader.GetContent<unsigned int>(iTestResult->second);

                                    // The time is calculated for the full test case
                                    pTestCaseNode->SetTime(nTestingTime);
                                }
                                else if(iTestResult->first == MESSAGE_TAG || 
                                        iTestResult->first == ERROR_TAG   || 
                                        iTestResult->first == INFO_TAG    || 
                                        iTestResult->first == EXCEPTION_TAG)
                                {
                                    // File
                                    wxString strTestResultFile = xmlReader.GetAttribute<std::string>(iTestResult->second, FILE_ATTRIB.ToStdString());

                                    // The test suite covers the test cases in a file, so the file information is set into it
                                    pTestSuiteNode->SetMessage(strTestResultFile);

                                    // Content
                                    wxString strTestResultContent = xmlReader.GetContent<std::string>(iTestResult->second);

                                    if(iTestResult->first == MESSAGE_TAG)
                                    {
                                        pTestResultNode = new TATTestResultNode(MESSAGE_TAG, ETATResult::E_NoResult, strTestResultContent, 0, ETATTestResultNodeType::E_Result);
                                    }
                                    else if(iTestResult->first == ERROR_TAG)
                                    {
                                        pTestResultNode = new TATTestResultNode(ERROR_TAG, ETATResult::E_Fail, strTestResultContent, 0, ETATTestResultNodeType::E_Result);
                                    }
                                    else if(iTestResult->first == INFO_TAG)
                                    {
                                        pTestResultNode = new TATTestResultNode(INFO_TAG, ETATResult::E_Success, strTestResultContent, 0, ETATTestResultNodeType::E_Result);
                                    }
                                    else if(iTestResult->first == EXCEPTION_TAG)
                                    {
                                        pTestResultNode = new TATTestResultNode(EXCEPTION_TAG, ETATResult::E_Error, strTestResultContent, 0, ETATTestResultNodeType::E_Result);
                                    }
                                }

                                if(pTestResultNode != NULL)
                                {
                                    pTestCaseNode->AddChild(pTestResultNode);
                                }
                            } // for(TXmlTreeIterator iTestResult =...

                            pTestSuiteNode->AddChild(pTestCaseNode);
                        }
                    } // for(TXmlTreeIterator iTestCase =...

                    // Calculates the sum of the testing time of all test cases to fill the time of the test suite
                    TATTestResultNode::TNodeCollection::const_iterator iTestCase = pTestSuiteNode->GetChildren().begin();
                    int nTotalTime = 0;

                    for(; iTestCase != pTestSuiteNode->GetChildren().end(); ++iTestCase)
                    {
                        nTotalTime += dynamic_cast<TATTestResultNode*>(iTestCase->second)->GetTime();
                    }

                    pTestSuiteNode->SetTime(nTotalTime);

                    pTestModuleNode->AddChild(pTestSuiteNode);
                }
            } // for(TXmlTreeIterator iTestSuite =...

            // Calculates the sum of the testing time of all test suites to fill the time of the test module
            TATTestResultNode::TNodeCollection::const_iterator iTestSuite = pTestModuleNode->GetChildren().begin();
            int nTotalTime = 0;

            for(; iTestSuite != pTestModuleNode->GetChildren().end(); ++iTestSuite)
            {
                nTotalTime += dynamic_cast<TATTestResultNode*>(iTestSuite->second)->GetTime();
            }

            pTestModuleNode->SetTime(nTotalTime);

            pRootNode->AddChild(pTestModuleNode);
        } // for(TXmlTreeIterator iTestModule =...

        // Calculates the sum of the testing time of all test modules to fill the total time
        TATTestResultNode::TNodeCollection::const_iterator iTestModule = pRootNode->GetChildren().begin();
        int nTotalTime = 0;

        for(; iTestModule != pRootNode->GetChildren().end(); ++iTestModule)
        {
            nTotalTime += dynamic_cast<TATTestResultNode*>(iTestModule->second)->GetTime();
        }

        pRootNode->SetTime(nTotalTime);

        pResultTree = pRootNode;
    }

    return pResultTree;
}

void TATTestResultLoader::Clear()
{
    if(m_pTestResultTree != NULL)
    {
        delete m_pTestResultTree;
        m_pTestResultTree = NULL;
    }
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultNode* TATTestResultLoader::GetTestResultTree() const
{
    return m_pTestResultTree;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
