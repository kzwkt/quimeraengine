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

#include "TestExecution/TATTestExecutionForm.h"

#include <iostream>
#include <sstream>
#include <wx/imaglist.h>
#include <wx/tooltip.h>

#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "../../resources/embedded/tick.bmp.h"
#include "../../resources/embedded/cross.bmp.h"
#include "ExternalDefinitions.h"
#include "TestResults/TATTestResultsForm.h"

using Kinesis::TestAutomationTool::Backend::TATwxWidgetsControlLogger;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;

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

    m_lstLogEvents->SetImageList(m_imgList, wxIMAGE_LIST_SMALL);

    this->Connect( wxEVT_COMMAND_TESTEXECUTION_PARSE_TESTRESULTS, wxCommandEventHandler(TATTestExecutionForm::OnParseTestResults) );
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
    m_pTestResultsForm->ClearTestResultTree();
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
    // Test results window
    // ------------------------
    m_pTestResultsForm = new TATTestResultsForm(this, wxT(""), false);
    m_pTestResultsForm->Show();

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

void TATTestExecutionForm::OnParseTestResults(wxCommandEvent& event)
{
    using Kinesis::TestAutomationTool::Backend::TATTestResultNode;

    TATTestResultInfo* pResult = static_cast<TATTestResultInfo*>(event.GetClientData());

    m_pTestResultsForm->ParseTestResultFile(event.GetString(), 
                                            pResult->GetCompilationConfiguration(),
                                            pResult->GetCompilerName(),
                                            pResult->GetFlagCombinationName(),
                                            pResult->GetFlagCombinationValues());

    delete pResult;
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
