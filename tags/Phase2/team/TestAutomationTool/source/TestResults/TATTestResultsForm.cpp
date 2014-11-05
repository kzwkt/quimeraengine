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

#include "TestResults/TATTestResultsForm.h"

#include <iostream>
#include <sstream>
#include <wx/imaglist.h>
#include <wx/tooltip.h>

#include "TestResults/ETATResultSource.h"
#include "TestResults/TATTestResultLoaderFactory.h"
#include "TestResults/ITATTestResultLoader.h"
#include "../../resources/embedded/tick2.bmp.h"
#include "../../resources/embedded/cross2.bmp.h"
#include "TestResults/TATTestResultInfo.h"
#include "TestResults/TATTestResultConsultant.h"
#include "TestResults/ETATTestResultNodeType.h"
#include "ExternalDefinitions.h"
#include "STATFileSystemHelper.h"

using Kinesis::TestAutomationTool::Backend::ETATResultSource;
using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;
using Kinesis::TestAutomationTool::Backend::TATTestResultInfo;
using Kinesis::TestAutomationTool::Backend::TATTestResultConsultant;
using Kinesis::TestAutomationTool::Backend::ETATTestResultNodeType;
using Kinesis::TestAutomationTool::Backend::ETATResult;

namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const int TATTestResultsForm::IMAGE_INDEX_FOR_SUCCESSFULL_TREE_ITEM = 0;
const int TATTestResultsForm::IMAGE_INDEX_FOR_FAILED_TREE_ITEM = 1;
const int TATTestResultsForm::IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM = -1;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultsForm::TATTestResultsForm(wxWindow* parent,
                                           const wxString& strTestResultsPath,
                                           const bool& bParseTestResultsAutomatically)
                                           : TestResultsBaseForm(parent)
{
    // Loads the images for the items in the result tree
    m_imgList = new wxImageList(8, 8);
    m_imgList->Add(tick2_bmp_to_wx_bitmap(), *wxWHITE);
    m_imgList->Add(cross2_bmp_to_wx_bitmap(), *wxWHITE);

    m_treeResults->SetImageList(m_imgList);
    m_rtbResultInfo->ShowScrollbars(wxSHOW_SB_ALWAYS, wxSHOW_SB_ALWAYS);

    this->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(TATTestResultsForm::OnTreeItemSelected) );

    // Initializes the backend
    this->InitializeBackend(strTestResultsPath);

    m_bParseTestResultsAutomatically = bParseTestResultsAutomatically;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestResultsForm::~TATTestResultsForm()
{
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestResultsForm::InitializeBackend(const wxString& strTestResultsPath)
{
    // Sets input data
    m_backend.SetTestResultsPath(strTestResultsPath);

    // Sets the test result loader
    TATTestResultLoaderFactory testResultLoaderFactory;
    ITATTestResultLoader* pTestResultLoader = testResultLoaderFactory.CreateConfigLoader(ETATResultSource::E_XmlFile);
    m_backend.SetTestResultLoader(pTestResultLoader);
}

void TATTestResultsForm::ParseTestResultFile(const wxString& strTestResultFilePath, 
                                             const wxString& strCompilationConfig,
                                             const wxString& strCompilerName,
                                             const wxString& strFlagCombinationName,
                                             const wxString& strFlagCombinationValues)
{
    this->m_btnRefresh->Disable();

    try
    {
        m_backend.SetTestResultsPath(strTestResultFilePath); // [TODO] Thund: In the future, there will be only one test result path for all configurations so this line will be correct
        TATTestResultInfo result = m_backend.ParseTestResultFile(strTestResultFilePath, strCompilationConfig, strCompilerName, strFlagCombinationName, strFlagCombinationValues);
        this->BuildResultTree(this->m_treeResults, &result);
    }
    catch(...)
    {
        this->m_btnRefresh->Enable();
        throw;
    }

    this->m_btnRefresh->Enable();
}
    
void TATTestResultsForm::ClearTestResultTree()
{
    m_treeResults->DeleteAllItems();
    m_rtbResultInfo->Clear();
    m_backend.GetTestResultLoader()->Clear();
}

void TATTestResultsForm::ParseAllTestResultFiles(const wxString& strTestResultFilesPath)
{
    this->m_btnRefresh->Disable();

    try
    {
        std::list<TATTestResultInfo> resultList = m_backend.ParseAllTestResultFiles(strTestResultFilesPath);

        for(std::list<TATTestResultInfo>::iterator it = resultList.begin(); it != resultList.end(); ++it)
        {
            this->BuildResultTree(this->m_treeResults, &(*it));
        }
    }
    catch(...)
    {
        this->m_btnRefresh->Enable();
        throw;
    }

    this->m_btnRefresh->Enable();
}

void TATTestResultsForm::BuildResultTree(wxTreeCtrl* pTreeControl, TATTestResultInfo* pResult)
{
    typedef TATTestResultNode::TNodeCollection::const_iterator TTATResultIterator;
    const int NO_SELECTED_IMAGE_PROVIDED = -1;

    TATTestResultNode* pResultTree = pResult->GetResultTree();

    if(!pResultTree)
    {
        // There is no tree to build
        return;
    }

    // Root node
    wxTreeItemId rootID;

    if(pTreeControl->IsEmpty())
    {
        rootID = pTreeControl->AddRoot(wxT(""));
    }
    else
    {
        rootID = pTreeControl->GetRootItem();
    }

    pTreeControl->SetItemData(rootID, NULL);

    // Tree root
    wxTreeItemId treeRootID = pTreeControl->AppendItem(rootID,
                                                        pResultTree->GetMessage(),
                                                        this->SelectImageIndexForResult(pResultTree),
                                                        NO_SELECTED_IMAGE_PROVIDED,
                                                        new TATTestResultsForm::TATResultTreeItemData(*pResult, pResultTree));

    // Test modules
    for(TTATResultIterator iTestModule = pResultTree->GetChildren().begin(); iTestModule != pResultTree->GetChildren().end(); ++iTestModule)
    {
        TATTestResultNode* pTestModule = dynamic_cast<TATTestResultNode*>(iTestModule->second);

        wxTreeItemId moduleID = pTreeControl->AppendItem(treeRootID,
                                                            this->GetCleanTestNodeName(pTestModule->GetName(), ETATTestResultNodeType::E_Module),
                                                            this->SelectImageIndexForResult(pTestModule),
                                                            NO_SELECTED_IMAGE_PROVIDED,
                                                            new TATTestResultsForm::TATResultTreeItemData(*pResult, pTestModule));

        // Test suites
        for(TTATResultIterator iTestSuite = pTestModule->GetChildren().begin(); iTestSuite != pTestModule->GetChildren().end(); ++iTestSuite)
        {
            TATTestResultNode* pTestSuite = dynamic_cast<TATTestResultNode*>(iTestSuite->second);

            wxTreeItemId suiteID = pTreeControl->AppendItem(moduleID,
                                                            this->GetCleanTestNodeName(pTestSuite->GetName(), ETATTestResultNodeType::E_Suite),
                                                            this->SelectImageIndexForResult(pTestSuite),
                                                            NO_SELECTED_IMAGE_PROVIDED,
                                                            new TATTestResultsForm::TATResultTreeItemData(*pResult, pTestSuite));
            // Used to know when the case refers to a different method
            wxString strLastMethodNameAux = wxT("");
            wxTreeItemId methodID;

            // Test cases
            for(TTATResultIterator iTestCase = pTestSuite->GetChildren().begin(); iTestCase != pTestSuite->GetChildren().end(); ++iTestCase)
            {
                // Note: Test cases are divided into 2 nodes, one node represents the method and the other the case applied to that method

                TATTestResultNode* pTestCase = dynamic_cast<TATTestResultNode*>(iTestCase->second);

                wxString strMethodName = this->GetCleanTestNodeName(pTestCase->GetName(), ETATTestResultNodeType::E_Case, true);

                // A new method has been reached
                if(strMethodName != strLastMethodNameAux)
                {
                    methodID = pTreeControl->AppendItem(suiteID,
                                                        this->GetCleanTestNodeName(pTestCase->GetName(), ETATTestResultNodeType::E_Case),
                                                        this->SelectImageIndexForResult(pTestCase),
                                                        NO_SELECTED_IMAGE_PROVIDED,
                                                        new TATTestResultsForm::TATResultTreeItemData(*pResult, pTestCase, true));
                    strLastMethodNameAux = strMethodName;
                }

                // Appends the test case to the current method
                wxTreeItemId caseID = pTreeControl->AppendItem(methodID,
                                                                this->GetCleanTestNodeName(pTestCase->GetName(), ETATTestResultNodeType::E_Case, false),
                                                                this->SelectImageIndexForResult(pTestCase),
                                                                NO_SELECTED_IMAGE_PROVIDED,
                                                                new TATTestResultsForm::TATResultTreeItemData(*pResult, pTestCase, false));

                // Test results
                for(TTATResultIterator iTestResult = pTestCase->GetChildren().begin(); iTestResult != pTestCase->GetChildren().end(); ++iTestResult)
                {
                    TATTestResultNode* pTestResult = dynamic_cast<TATTestResultNode*>(iTestResult->second);

                    wxTreeItemId resultID = pTreeControl->AppendItem(caseID,
                                                                        this->GetLocalizedTitleForResult(pTestResult->GetResult()) + wxT(": ") + pTestResult->GetMessage(),
                                                                        this->SelectImageIndexForResult(pTestResult),
                                                                        NO_SELECTED_IMAGE_PROVIDED,
                                                                        new TATTestResultsForm::TATResultTreeItemData(*pResult, pTestResult));
                } // Test results

                // Erroneous nodes are expanded
                if(pTestCase->HasErrors())
                {
                    pTreeControl->Expand(caseID);

                    // The method node has to be expanded too and its image has to be the corresponding for a failed test
                    pTreeControl->SetItemImage(methodID, this->SelectImageIndexForResult(pTestCase));
                    pTreeControl->Expand(methodID);
                }

            } // Test cases

            // Erroneous nodes are expanded
            if(pTestSuite->HasErrors())
            {
                pTreeControl->Expand(suiteID);
            }

        } // Test suites

        // Erroneous nodes are expanded
        if(pTestModule->HasErrors())
        {
            pTreeControl->Expand(moduleID);
        }

    } // Test modules

    // Erroneous nodes are expanded
    if(pResultTree->HasErrors())
    {
        pTreeControl->Expand(treeRootID);
    }

    pTreeControl->Expand(rootID);
    
}

int TATTestResultsForm::SelectImageIndexForResult(TATTestResultNode* pNode)
{
    int nImageIndex = TATTestResultsForm::IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM;

    if(pNode->HasErrors())
    {
        nImageIndex = TATTestResultsForm::IMAGE_INDEX_FOR_FAILED_TREE_ITEM;
    }
    else
    {
        nImageIndex = TATTestResultsForm::IMAGE_INDEX_FOR_SUCCESSFULL_TREE_ITEM;
    }

    return nImageIndex;
}

void TATTestResultsForm::ShowAdditionalInformation(wxTreeCtrl* pTreeControl, const wxTreeItemId& itemId, wxRichTextCtrl* pInformationPanel)
{
    TATTestResultsForm::TATResultTreeItemData* pData = dynamic_cast<TATTestResultsForm::TATResultTreeItemData*>(pTreeControl->GetItemData(itemId));

    // Resets the panel
    pInformationPanel->Clear();

    if(pData != NULL) // It's possible, for example, clicking on the root of the tree, which doesn't correspond to a result
    {
        TATTestResultNode* pResultNode = pData->GetTestResultNode();

        TATTestResultConsultant resultConsultant;

        // Writes the name of the item
        pInformationPanel->EndUnderline(); // Sometimes, after clearing the content, the text starts with underline due to a bad content cleaning...
        pInformationPanel->BeginUnderline();

        switch(pResultNode->GetNodeType())
        {
        case ETATTestResultNodeType::E_Root:
            pInformationPanel->WriteText(pResultNode->GetMessage());
            break;
        case ETATTestResultNodeType::E_Module:
            pInformationPanel->WriteText(pResultNode->GetName());
            break;
        case ETATTestResultNodeType::E_Suite:
            pInformationPanel->WriteText(pResultNode->GetName());
            break;
        case ETATTestResultNodeType::E_Case:
            {
                if(pData->IsMethod())
                {
                    pInformationPanel->WriteText(_("Method") + wxT(": ") + pTreeControl->GetItemText(itemId));
                }
                else
                {
                    pInformationPanel->WriteText(pResultNode->GetName());
                }
            }
            break;
        case ETATTestResultNodeType::E_Result:
            pInformationPanel->WriteText(this->GetLocalizedTitleForResult(pResultNode->GetResult()));
            break;
        }

        pInformationPanel->EndUnderline();
        pInformationPanel->Newline();
        pInformationPanel->Newline();

        // Writes the test information
        if(pResultNode->GetNodeType() == ETATTestResultNodeType::E_Root)
        {
            // If the entire set of tests passed, then it's not useful to show which failed
            if(pResultNode->HasErrors())
            {
                pInformationPanel->WriteText(_("FailedModules") + wxT(": "));
                pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetFailedTestModuleCount(pData->GetTestResultNode())));
                pInformationPanel->WriteText(wxT("/"));
            }
            else
            {
                pInformationPanel->WriteText(_("ModulesInTestLog") + wxT(": "));
            }
            pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetTestModuleCount(pData->GetTestResultNode())));
            pInformationPanel->WriteText(wxT("."));
            pInformationPanel->Newline();
        }

        if(pResultNode->GetNodeType() == ETATTestResultNodeType::E_Root ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Module)
        {
            // If the entire set of tests passed, then it's not useful to show which failed
            if(pResultNode->HasErrors())
            {
                pInformationPanel->WriteText(_("FailedSuites") + wxT(": "));
                pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetFailedTestSuiteCount(pResultNode)));
                pInformationPanel->WriteText(wxT("/"));
            }
            else
            {
                pInformationPanel->WriteText(_("SuitesInTestModule") + wxT(": "));
            }
            pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetTestSuiteCount(pResultNode)));
            pInformationPanel->WriteText(wxT("."));
            pInformationPanel->Newline();
        }

        if(pResultNode->GetNodeType() == ETATTestResultNodeType::E_Root   ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Module ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Suite)
        {
            // If the entire set of tests passed, then it's not useful to show which failed
            if(pResultNode->HasErrors())
            {
                pInformationPanel->WriteText(_("FailedCases") + wxT(": "));
                pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetFailedTestCaseCount(pResultNode)));
                pInformationPanel->WriteText(wxT("/"));
            }
            else
            {
                pInformationPanel->WriteText(_("CasesInTestSuite") + wxT(": "));
            }
            pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetTestCaseCount(pResultNode)));
            pInformationPanel->WriteText(wxT("."));
            pInformationPanel->Newline();
        }

        if(pResultNode->GetNodeType() == ETATTestResultNodeType::E_Root   ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Module ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Suite  ||
            pResultNode->GetNodeType() == ETATTestResultNodeType::E_Case)
        {
            // If the entire set of tests passed, then it's not useful to show which failed
            if(pResultNode->HasErrors())
            {
                pInformationPanel->WriteText(_("FailedResults") + wxT(": "));
                pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetFailedTestResultCount(pResultNode)));
                pInformationPanel->WriteText(wxT("/"));
            }
            else
            {
                pInformationPanel->WriteText(_("ResultsInTestCase") + wxT(": "));
            }
            pInformationPanel->WriteText(wxString::FromDouble(resultConsultant.GetTestResultCount(pResultNode)));
            pInformationPanel->WriteText(wxT("."));
            pInformationPanel->Newline();
        }

        if(pResultNode->GetNodeType() == ETATTestResultNodeType::E_Result)
        {
            pInformationPanel->WriteText(pResultNode->GetMessage());
            pInformationPanel->Newline();
        }

        // Converts from microseconds to seconds
        pInformationPanel->Newline();
        float fTestingTime = static_cast<float>(pResultNode->GetTime());
        fTestingTime /= 1000000.0f;

        // And to string...
        std::ostringstream streamForConversion;
        streamForConversion << fTestingTime;

        pInformationPanel->WriteText(_("TestingTime") + wxT(" ") + streamForConversion.str());
        pInformationPanel->Newline();

        // Adds the situation of the test
        // ---------------------------------
        pInformationPanel->Newline();
        pInformationPanel->BeginUnderline();
        pInformationPanel->WriteText(_("Context"));
        pInformationPanel->EndUnderline();
        pInformationPanel->Newline();
        pInformationPanel->Newline();

        // Path to the node
        pInformationPanel->WriteText(_("At") + wxT(":"));
        pInformationPanel->Newline();
        pInformationPanel->Newline();

        wxTreeItemId parentId = pTreeControl->GetItemParent(itemId);
        wxString strPathToNode;

        while(parentId.IsOk())
        {
            TATTestResultsForm::TATResultTreeItemData* pParentData = dynamic_cast<TATTestResultsForm::TATResultTreeItemData*>(pTreeControl->GetItemData(parentId));

            if(pParentData != NULL)
            {
                TATTestResultNode* pParentNode = pParentData->GetTestResultNode();

                switch(pParentNode->GetNodeType())
                {
                case ETATTestResultNodeType::E_Root:
                    strPathToNode = wxT("--") + pParentNode->GetMessage() + TAT_NEWLINE_TOKEN + strPathToNode;
                    break;
                case ETATTestResultNodeType::E_Module:
                    strPathToNode = wxT("    |") + TAT_NEWLINE_TOKEN + wxT("   +--") + pParentNode->GetName() + TAT_NEWLINE_TOKEN + strPathToNode;
                    break;
                case ETATTestResultNodeType::E_Suite:
                    strPathToNode = wxT("      |") + TAT_NEWLINE_TOKEN + wxT("     +--") + pParentNode->GetName() + TAT_NEWLINE_TOKEN + strPathToNode;
                    break;
                case ETATTestResultNodeType::E_Case:
                    if(!dynamic_cast<TATTestResultsForm::TATResultTreeItemData*>(pTreeControl->GetItemData(parentId))->IsMethod())
                    {
                        // Only writes this node if it's not a method but a use case
                        strPathToNode = wxT("        |") + TAT_NEWLINE_TOKEN + wxT("       +--") + pParentNode->GetName() + TAT_NEWLINE_TOKEN;
                    }
                    break;
                }
            }

            parentId = pTreeControl->GetItemParent(parentId);
        }

        if(!strPathToNode.empty())
        {
            pInformationPanel->WriteText(strPathToNode);
            pInformationPanel->Newline();
        }

        pInformationPanel->WriteText(_("WithConfiguration") + wxT(":"));
        pInformationPanel->Newline();
        pInformationPanel->Newline();

        // Compilation confifuration
        pInformationPanel->WriteText(_("Configuration") + wxT(": ") + pData->GetTestResult().GetCompilationConfiguration());
        pInformationPanel->Newline();

        // Compiler name
        pInformationPanel->WriteText(_("Compiler") + wxT(": ") + pData->GetTestResult().GetCompilerName());
        pInformationPanel->Newline();

        // Flag combination name
        pInformationPanel->WriteText(_("FlagCombination") + wxT(": ") + pData->GetTestResult().GetFlagCombinationName());
        pInformationPanel->Newline();

        // Flag combination values
        pInformationPanel->WriteText(_("FlagValues") + wxT(": "));
        pInformationPanel->Newline();
        pInformationPanel->WriteText(pData->GetTestResult().GetFlagCombinationValues());
        pInformationPanel->Newline();
    }
}

wxString TATTestResultsForm::GetLocalizedTitleForResult(const ETATResult &eResult) const
{
    wxString strResult;

    switch(eResult)
    {
    case ETATResult::E_Success:
        strResult = _("SuccessResult");
        break;
    case ETATResult::E_Fail:
        strResult = _("FailResult");
        break;
    case ETATResult::E_NoResult:
        strResult = _("NotATestResult");
        break;
        case ETATResult::E_Error:
        strResult = _("ErrorResult");
        break;
    }

    return strResult;
}

wxString TATTestResultsForm::GetCleanTestNodeName(const wxString &strNodeName,
                                                    const ETATTestResultNodeType &eType,
                                                    const bool &bMethodOrCase) const
{
    wxString strResult = strNodeName;

    if(eType == ETATTestResultNodeType::E_Case)
    {
        const bool IS_METHOD = true;
        const wxString PREFIX_SEPARATOR = wxT("_");
        const wxString SUFFIX_TO_REMOVE = wxT("_Test");

        strResult.Replace(SUFFIX_TO_REMOVE, wxT(""));

        if(bMethodOrCase == IS_METHOD)
        {
            strResult.Truncate(strResult.Find(PREFIX_SEPARATOR));
        }
        else
        {
            strResult.Remove(0, strResult.Find(PREFIX_SEPARATOR) + 1);
        }
    }
    else if(eType == ETATTestResultNodeType::E_Module)
    {
        const wxString PREFIX_SEPARATOR = wxT("_");

        strResult.Remove(0, strResult.First(PREFIX_SEPARATOR) + 1);
    }
    else if(eType == ETATTestResultNodeType::E_Suite)
    {
        const wxString SUFFIX_TO_REMOVE = wxT("_TestSuite");

        strResult.Replace(SUFFIX_TO_REMOVE, wxT(""));
    }

    return strResult;
}

TATTestResultsForm::TATResultTreeItemData::TATResultTreeItemData(const TATTestResultInfo result,
                                                                   TATTestResultNode* pNode,
                                                                   const bool &bIsMethod) :
                                                                                  m_testResult(result),
                                                                                  m_pTestResultNode(pNode),
                                                                                  m_bIsMethod(bIsMethod)
{
}

TATTestResultInfo TATTestResultsForm::TATResultTreeItemData::GetTestResult() const
{
    return m_testResult;
}

TATTestResultNode* TATTestResultsForm::TATResultTreeItemData::GetTestResultNode() const
{
    return m_pTestResultNode;
}

bool TATTestResultsForm::TATResultTreeItemData::IsMethod() const
{
    return m_bIsMethod;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestResultsForm::OnInitDialog( wxInitDialogEvent& event )
{
    if(m_bParseTestResultsAutomatically)
    {
        this->ParseAllTestResultFiles(m_backend.GetTestResultsPath());
    }

    m_dirPickerTestResults->SetPath(m_backend.GetTestResultsPath());
}

void TATTestResultsForm::OnDialogClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATTestResultsForm::OnTreeItemSelected(wxTreeEvent& event)
{
    // Shows additional information about the result selected
    this->ShowAdditionalInformation(m_treeResults, event.GetItem(), m_rtbResultInfo);
}

void TATTestResultsForm::OnRefreshButtonClick(wxCommandEvent& event)
{
    this->ClearTestResultTree();
    this->ParseAllTestResultFiles(m_backend.GetTestResultsPath());
}

void TATTestResultsForm::OnTestResultsDirChanged(wxFileDirPickerEvent& event)
{
    using Kinesis::TestAutomationTool::Backend::STATFileSystemHelper;

    m_backend.SetTestResultsPath(event.GetPath() + wxFILE_SEP_PATH);
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis
