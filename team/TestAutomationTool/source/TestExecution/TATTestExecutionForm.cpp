// [TERMS&CONDITIONS]

#include "TestExecution/TATTestExecutionForm.h"

#include <iostream>
#include <sstream>
#include <wx/imaglist.h>
#include <wx/tooltip.h>

#include "../resources/embedded/resources.h"
#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "TestExecution/ETATResultSource.h"
#include "TestExecution/TATTestResultLoaderFactory.h"
#include "TestExecution/ITATTestResultLoader.h"
#include "../../resources/embedded/tick.bmp.h"
#include "../../resources/embedded/cross.bmp.h"
#include "TestExecution/TATTestResultInfo.h"
#include "TestExecution/TATTestResultConsultant.h"
#include "TestExecution/ETATTestResultNodeType.h"
#include "ExternalDefinitions.h"

using Kinesis::TestAutomationTool::Backend::TATwxWidgetsControlLogger;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;
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

const int TATTestExecutionForm::IMAGE_INDEX_FOR_SUCCESSFULL_TREE_ITEM = 0;
const int TATTestExecutionForm::IMAGE_INDEX_FOR_FAILED_TREE_ITEM = 1;
const int TATTestExecutionForm::IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM = -1;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestExecutionForm::TATTestExecutionForm(wxWindow* parent,
                                           const wxString& strConfigurationFilePath,
                                           const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                                           const std::list<wxString>& compilationConfigurations,
                                           const std::map<wxString, TATCompilerInfo>& compilerInfos)
                                           : TestExecutionBaseForm(parent),
                                             m_bStoppedByUser(false)
{
    this->SetIcon(wxIcon(TAT_ICON_APP));

    // Loads the images for the items in the result tree
    m_imgList = new wxImageList(8, 8);
    m_imgList->Add(tick_bmp_to_wx_bitmap(), *wxWHITE);
    m_imgList->Add(cross_bmp_to_wx_bitmap(), *wxWHITE);

    m_treeResults->SetImageList(m_imgList);
    m_lstLogEvents->SetImageList(m_imgList, wxIMAGE_LIST_SMALL);
    m_rtbResultInfo->ShowScrollbars(wxSHOW_SB_ALWAYS, wxSHOW_SB_ALWAYS);

    this->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(TATTestExecutionForm::OnTreeItemSelected) );
    this->Connect( wxEVT_COMMAND_TESTEXECUTION_TESTRESULTS_UPDATED, wxCommandEventHandler(TATTestExecutionForm::OnResultUpdate) );
    this->Connect( wxEVT_COMMAND_TESTEXECUTION_FINISHED, wxCommandEventHandler(TATTestExecutionForm::OnTestExecutionFinished) );
    this->Connect( wxEVT_COMMAND_TESTEXECUTION_NOTIFICATION, wxCommandEventHandler(TATTestExecutionForm::OnTestExecutionNotificationReceived) );

    // Initializes the backend
    this->InitializeBackend(strConfigurationFilePath,
                            flagCombinations,
                            compilationConfigurations,
                            compilerInfos);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestExecutionForm::~TATTestExecutionForm()
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

void TATTestExecutionForm::InitializeBackend(const wxString& strConfigurationFilePath,
                                             const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                                             const std::list<wxString>& compilationConfigurations,
                                             const std::map<wxString, TATCompilerInfo>& compilerInfos)
{
    // Sets input data
    m_backend.SetCompilerInfos(compilerInfos);
    m_backend.SetConfigurationFilePath(strConfigurationFilePath);
    m_backend.SetFlagCombinations(flagCombinations);
    m_backend.SetCompilationConfigurations(compilationConfigurations);

    // Sets the logger
    m_backend.SetLogger(new TATwxWidgetsControlLogger(m_rtbLog, false));

    // Sets the test result loader
    TATTestResultLoaderFactory testResultLoaderFactory;
    ITATTestResultLoader* pTestResultLoader = testResultLoaderFactory.CreateConfigLoader(ETATResultSource::E_XmlFile);
    m_backend.SetTestResultLoader(pTestResultLoader);

    // Sets itself as handler for events
    m_backend.SetTestExecutionEventListener(this);
}

void TATTestExecutionForm::StartTestExecution()
{
    m_bStoppedByUser = false;
    this->ShowButtonsDependingOnExecutionStatus(true);
    m_rtbLog->Clear();
    m_lstLogEvents->ClearAll();
    m_lstLogEvents->InsertColumn(0, wxT(""));
    m_treeResults->DeleteAllItems();
    m_rtbResultInfo->Clear();
    this->EnableLogEventListDependingOnExecution(true);
    m_backend.ExecuteTests();
}

void TATTestExecutionForm::StopTestExecution()
{
    m_backend.StopTestExecution();
}

void TATTestExecutionForm::ShowButtonsDependingOnExecutionStatus(const bool &bExecuting)
{
    if(bExecuting)
    {
        m_btnStop->Show();
        m_btnRestart->Hide();
    }
    else
    {
        m_btnStop->Hide();
        m_btnRestart->Show();
    }
}

void TATTestExecutionForm::SwitchStopButtonText(const bool &bStopped)
{
    if(bStopped)
    {
        m_btnStop->SetLabelText(_("ButtonStop"));
        m_btnStop->Enable(true);
    }
    else
    {
        m_btnStop->SetLabelText(_("ButtonStopping"));
        m_btnStop->Enable(false);
    }
}

void TATTestExecutionForm::BuildResultTree(wxTreeCtrl* pTreeControl, TATTestResultInfo* pResult)
{
    typedef TATTestResultNode::TNodeCollection::const_iterator TTATResultIterator;
    const int NO_SELECTED_IMAGE_PROVIDED = -1;

    TATTestResultNode* pResultTree = pResult->GetResultTree();

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
                                                       new TATTestExecutionForm::TATResultTreeItemData(*pResult, pResultTree));

    // Test modules
    for(TTATResultIterator iTestModule = pResultTree->GetChildren().begin(); iTestModule != pResultTree->GetChildren().end(); ++iTestModule)
    {
        TATTestResultNode* pTestModule = dynamic_cast<TATTestResultNode*>(iTestModule->second);

        wxTreeItemId moduleID = pTreeControl->AppendItem(treeRootID,
                                                         this->GetCleanTestNodeName(pTestModule->GetName(), ETATTestResultNodeType::E_Module),
                                                         this->SelectImageIndexForResult(pTestModule),
                                                         NO_SELECTED_IMAGE_PROVIDED,
                                                         new TATTestExecutionForm::TATResultTreeItemData(*pResult, pTestModule));

        // Test suites
        for(TTATResultIterator iTestSuite = pTestModule->GetChildren().begin(); iTestSuite != pTestModule->GetChildren().end(); ++iTestSuite)
        {
            TATTestResultNode* pTestSuite = dynamic_cast<TATTestResultNode*>(iTestSuite->second);

            wxTreeItemId suiteID = pTreeControl->AppendItem(moduleID,
                                                            this->GetCleanTestNodeName(pTestSuite->GetName(), ETATTestResultNodeType::E_Suite),
                                                            this->SelectImageIndexForResult(pTestSuite),
                                                            NO_SELECTED_IMAGE_PROVIDED,
                                                            new TATTestExecutionForm::TATResultTreeItemData(*pResult, pTestSuite));
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
                                                        new TATTestExecutionForm::TATResultTreeItemData(*pResult, pTestCase, true));
                    strLastMethodNameAux = strMethodName;
                }

                // Appends the test case to the current method
                wxTreeItemId caseID = pTreeControl->AppendItem(methodID,
                                                               this->GetCleanTestNodeName(pTestCase->GetName(), ETATTestResultNodeType::E_Case, false),
                                                               this->SelectImageIndexForResult(pTestCase),
                                                               NO_SELECTED_IMAGE_PROVIDED,
                                                               new TATTestExecutionForm::TATResultTreeItemData(*pResult, pTestCase, false));

                // Test results
                for(TTATResultIterator iTestResult = pTestCase->GetChildren().begin(); iTestResult != pTestCase->GetChildren().end(); ++iTestResult)
                {
                    TATTestResultNode* pTestResult = dynamic_cast<TATTestResultNode*>(iTestResult->second);

                    wxTreeItemId resultID = pTreeControl->AppendItem(caseID,
                                                                     this->GetLocalizedTitleForResult(pTestResult->GetResult()) + wxT(": ") + pTestResult->GetMessage(),
                                                                     this->SelectImageIndexForResult(pTestResult),
                                                                     NO_SELECTED_IMAGE_PROVIDED,
                                                                     new TATTestExecutionForm::TATResultTreeItemData(*pResult, pTestResult));
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

int TATTestExecutionForm::SelectImageIndexForResult(TATTestResultNode* pNode)
{
    int nImageIndex = TATTestExecutionForm::IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM;

    if(pNode->HasErrors())
    {
        nImageIndex = TATTestExecutionForm::IMAGE_INDEX_FOR_FAILED_TREE_ITEM;
    }
    else
    {
        nImageIndex = TATTestExecutionForm::IMAGE_INDEX_FOR_SUCCESSFULL_TREE_ITEM;
    }

    return nImageIndex;
}

void TATTestExecutionForm::ShowAdditionalInformation(wxTreeCtrl* pTreeControl, const wxTreeItemId& itemId, wxRichTextCtrl* pInformationPanel)
{
    TATTestExecutionForm::TATResultTreeItemData* pData = dynamic_cast<TATTestExecutionForm::TATResultTreeItemData*>(pTreeControl->GetItemData(itemId));

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
            TATTestExecutionForm::TATResultTreeItemData* pParentData = dynamic_cast<TATTestExecutionForm::TATResultTreeItemData*>(pTreeControl->GetItemData(parentId));

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
                    if(!dynamic_cast<TATTestExecutionForm::TATResultTreeItemData*>(pTreeControl->GetItemData(parentId))->IsMethod())
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

void TATTestExecutionForm::AddLogEvent(const wxString &strMessage)
{
    // Expected prefixes
    const wxString INFO_NOTIFICATION = wxT("[i] ");
    const wxString ERROR_NOTIFICATION = wxT("[E] ");

    int nImageIndex;
    wxString itemText;

    if(strMessage.StartsWith(INFO_NOTIFICATION))
    {
        nImageIndex = IMAGE_INDEX_FOR_UNDEFINED_TREE_ITEM;
        itemText = strMessage.substr(INFO_NOTIFICATION.size());
    }
    else if(strMessage.StartsWith(ERROR_NOTIFICATION))
    {
        nImageIndex = IMAGE_INDEX_FOR_FAILED_TREE_ITEM;
        itemText = strMessage.substr(ERROR_NOTIFICATION.size());
    }

    wxListItem newItem;
    newItem.SetMask(wxLIST_MASK_TEXT);
    newItem.SetImage(nImageIndex);
    newItem.SetText(itemText);
    newItem.SetId(m_lstLogEvents->GetItemCount()); // Always at the end
    newItem.SetData(m_rtbLog->GetCaretPosition()); // Saves the current position of the log cursor. This is not the purpose of the property but it does the trick
    newItem.SetColumn(0);
    newItem.SetAlign(wxLIST_FORMAT_LEFT);
    newItem.SetWidth(150);

    m_lstLogEvents->InsertItem(newItem);
}

void TATTestExecutionForm::EnableLogEventListDependingOnExecution(bool bExecuting)
{
    m_lstLogEvents->Enable(!bExecuting);
}

wxString TATTestExecutionForm::GetLocalizedTitleForResult(const ETATResult &eResult) const
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

wxString TATTestExecutionForm::GetCleanTestNodeName(const wxString &strNodeName,
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

TATTestExecutionForm::TATResultTreeItemData::TATResultTreeItemData(const TATTestResultInfo result,
                                                                   TATTestResultNode* pNode,
                                                                   const bool &bIsMethod) :
                                                                                  m_testResult(result),
                                                                                  m_pTestResultNode(pNode),
                                                                                  m_bIsMethod(bIsMethod)
{
}

TATTestResultInfo TATTestExecutionForm::TATResultTreeItemData::GetTestResult() const
{
    return m_testResult;
}

TATTestResultNode* TATTestExecutionForm::TATResultTreeItemData::GetTestResultNode() const
{
    return m_pTestResultNode;
}

bool TATTestExecutionForm::TATResultTreeItemData::IsMethod() const
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

void TATTestExecutionForm::OnInitDialog( wxInitDialogEvent& event )
{
    this->StartTestExecution();
}

void TATTestExecutionForm::OnDialogClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATTestExecutionForm::OnStopButtonClick( wxCommandEvent& event )
{
    m_bStoppedByUser = true;
    this->SwitchStopButtonText(false);
    this->StopTestExecution();
}

void TATTestExecutionForm::OnRestartButtonClick( wxCommandEvent& event )
{
    this->StartTestExecution();
}

void TATTestExecutionForm::OnResultUpdate(wxCommandEvent& event)
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    TATTestResultInfo* pResult = static_cast<TATTestResultInfo*>(event.GetClientData());

    this->BuildResultTree(m_treeResults, pResult);
}

void TATTestExecutionForm::OnTestExecutionFinished(wxCommandEvent& event)
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::TATMessageFormat;
    using Kinesis::TestAutomationTool::Backend::ETATColor;

    this->ShowButtonsDependingOnExecutionStatus(false);
    this->SwitchStopButtonText(true);
    this->EnableLogEventListDependingOnExecution(false);

    // If it was stopped by the user, writes a note in the log
    if(m_bStoppedByUser)
    {
        m_backend.GetLogger()->Log(TATFormattedMessage(_("LogTestExecutionCancelled"), TATMessageFormat(ETATColor::E_Green, TATMessageFormat::TEXT_STYLE_BOLD)));
        m_backend.GetLogger()->Flush();
    }
}

void TATTestExecutionForm::OnTreeItemSelected(wxTreeEvent& event)
{
    // Shows additional information about the result selected
    this->ShowAdditionalInformation(m_treeResults, event.GetItem(), m_rtbResultInfo);

}

void TATTestExecutionForm::OnTestExecutionNotificationReceived(wxCommandEvent& event)
{
    this->AddLogEvent(event.GetString());
}

void TATTestExecutionForm::OnLogEventItemSelected(wxListEvent& event)
{
    long nLogCaretPosition = event.GetItem().GetData();
    m_rtbLog->SetCaretPosition(nLogCaretPosition, true);
    m_rtbLog->ShowPosition(nLogCaretPosition);
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
