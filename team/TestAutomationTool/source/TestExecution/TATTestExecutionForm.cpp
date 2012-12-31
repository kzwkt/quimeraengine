// [TERMS&CONDITIONS]

#include "TestExecution/TATTestExecutionForm.h"

#include <iostream>
#include <sstream>
#include <wx/imaglist.h>
#include <wx/tooltip.h>

#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "TestExecution/ETATResultSource.h"
#include "TestExecution/TATTestResultLoaderFactory.h"
#include "TestExecution/ITATTestResultLoader.h"
#include "../../resources/embedded/tick.bmp.h"
#include "../../resources/embedded/cross.bmp.h"

using Kinesis::TestAutomationTool::Backend::TATwxWidgetsControlLogger;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;
using Kinesis::TestAutomationTool::Backend::ETATResultSource;
using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;
using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

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
    // Loads the images for the items in the result tree
    m_imgList = new wxImageList(8, 8);
    m_imgList->Add(tick_bmp_to_wx_bitmap(), *wxWHITE);
    m_imgList->Add(cross_bmp_to_wx_bitmap(), *wxWHITE);

    m_treeResults->SetImageList(m_imgList);

    this->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(TATTestExecutionForm::OnTreeItemSelected) );
    this->Connect( wxEVT_COMMAND_TESTEXECUTION_TESTRESULTS_UPDATED, wxCommandEventHandler(TATTestExecutionForm::OnResultUpdate) );
    this->Connect( wxEVT_COMMAND_TESTEXECUTION_FINISHED, wxCommandEventHandler(TATTestExecutionForm::OnTestExecutionFinished) );

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
    ShowButtonsDependingOnExecutionStatus(true);
    m_rtbLog->Clear();
    m_treeResults->DeleteAllItems();
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

void TATTestExecutionForm::BuildResultTree(wxTreeCtrl* pTreeControl, TATTestResultNode* pResultTree)
{
    typedef TATTestResultNode::TNodeCollection::const_iterator TTATResultIterator;
    const int NO_SELECTED_IMAGE_PROVIDED = -1;

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

    // Tree root
    wxTreeItemId treeRootID = pTreeControl->AppendItem(rootID,
                                                       pResultTree->GetMessage(),
                                                       this->SelectImageIndexForResult(pResultTree),
                                                       NO_SELECTED_IMAGE_PROVIDED,
                                                       new TATTestExecutionForm::TATResultTreeItemData(pResultTree));

    // Test modules
    for(TTATResultIterator iTestModule = pResultTree->GetChildren().begin(); iTestModule != pResultTree->GetChildren().end(); ++iTestModule)
    {
        TATTestResultNode* pTestModule = dynamic_cast<TATTestResultNode*>(iTestModule->second);

        wxTreeItemId moduleID = pTreeControl->AppendItem(treeRootID,
                                                         pTestModule->GetName(),
                                                         this->SelectImageIndexForResult(pTestModule),
                                                         NO_SELECTED_IMAGE_PROVIDED,
                                                         new TATTestExecutionForm::TATResultTreeItemData(pTestModule));

        // Test suites
        for(TTATResultIterator iTestSuite = pTestModule->GetChildren().begin(); iTestSuite != pTestModule->GetChildren().end(); ++iTestSuite)
        {
            TATTestResultNode* pTestSuite = dynamic_cast<TATTestResultNode*>(iTestSuite->second);

            wxTreeItemId suiteID = pTreeControl->AppendItem(moduleID,
                                                            pTestSuite->GetName(),
                                                            this->SelectImageIndexForResult(pTestSuite),
                                                            NO_SELECTED_IMAGE_PROVIDED,
                                                            new TATTestExecutionForm::TATResultTreeItemData(pTestSuite));

            // Test cases
            for(TTATResultIterator iTestCase = pTestSuite->GetChildren().begin(); iTestCase != pTestSuite->GetChildren().end(); ++iTestCase)
            {
                TATTestResultNode* pTestCase = dynamic_cast<TATTestResultNode*>(iTestCase->second);

                wxTreeItemId caseID = pTreeControl->AppendItem(suiteID,
                                                               pTestCase->GetName(),
                                                               this->SelectImageIndexForResult(pTestCase),
                                                               NO_SELECTED_IMAGE_PROVIDED,
                                                               new TATTestExecutionForm::TATResultTreeItemData(pTestCase));

                // Test results
                for(TTATResultIterator iTestResult = pTestCase->GetChildren().begin(); iTestResult != pTestCase->GetChildren().end(); ++iTestResult)
                {
                    TATTestResultNode* pTestResult = dynamic_cast<TATTestResultNode*>(iTestResult->second);

                    wxTreeItemId resultID = pTreeControl->AppendItem(caseID,
                                                                     pTestResult->GetMessage(),
                                                                     this->SelectImageIndexForResult(pTestResult),
                                                                     NO_SELECTED_IMAGE_PROVIDED,
                                                                     new TATTestExecutionForm::TATResultTreeItemData(pTestResult));
                } // Test results

                // Erroneous nodes are expanded
                if(pTestCase->HasErrors())
                {
                    pTreeControl->Expand(caseID);
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

    }// Test modules

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

void TATTestExecutionForm::ShowToolTipWithAdditionalInfo(wxTreeCtrl* pTreeControl, const wxTreeItemId& itemId)
{
    TATTestExecutionForm::TATResultTreeItemData* pData = dynamic_cast<TATTestExecutionForm::TATResultTreeItemData*>(pTreeControl->GetItemData(itemId));

    // Converts from microseconds to seconds
    float fTestingTime = static_cast<float>(pData->GetTestResultNode()->GetTime());
    fTestingTime /= 1000000.0f;

    // And to string...
    std::ostringstream streamForConversion;
    streamForConversion << fTestingTime;

    // Shows the tooltip
    pTreeControl->SetToolTip(_("TestingTime") + wxT(" ") + streamForConversion.str());
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

    TATTestResultNode* pNewResultTree = static_cast<TATTestResultNode*>(event.GetClientData());

    this->BuildResultTree(m_treeResults, pNewResultTree);
}

void TATTestExecutionForm::OnTestExecutionFinished(wxCommandEvent& event)
{
    using Kinesis::TestAutomationTool::Backend::TATFormattedMessage;
    using Kinesis::TestAutomationTool::Backend::TATMessageFormat;
    using Kinesis::TestAutomationTool::Backend::ETATColor;

    this->ShowButtonsDependingOnExecutionStatus(false);
    this->SwitchStopButtonText(true);

    // If it was stopped by the user, writes a note in the log
    if(m_bStoppedByUser)
    {
        m_backend.GetLogger()->Log(TATFormattedMessage(_("LogTestExecutionCancelled"), TATMessageFormat(ETATColor::E_Green, TATMessageFormat::TEXT_STYLE_BOLD)));
        m_backend.GetLogger()->Flush();
    }
}

void TATTestExecutionForm::OnTreeItemSelected(wxTreeEvent& event)
{
    // Show tooltip with additional information
    this->ShowToolTipWithAdditionalInfo(m_treeResults, event.GetItem());

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
