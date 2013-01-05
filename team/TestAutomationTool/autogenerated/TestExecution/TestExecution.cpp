///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TestExecution.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

TestExecutionBaseForm::TestExecutionBaseForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_txtLog = new wxStaticText( this, wxID_ANY, _("LogTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtLog->Wrap( -1 );
	m_txtLog->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_txtLog, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_rtbLog = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,250 ), wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_rtbLog->SetFont( wxFont( 8, 74, 90, 90, false, wxT("Tahoma") ) );
	m_rtbLog->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_rtbLog->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	m_rtbLog->SetMinSize( wxSize( -1,250 ) );
	
	bSizer3->Add( m_rtbLog, 3, wxEXPAND | wxALL, 5 );
	
	m_lstLogEvents = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 70,-1 ), wxLC_ALIGN_TOP|wxLC_SINGLE_SEL|wxLC_SMALL_ICON );
	m_lstLogEvents->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	m_lstLogEvents->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer3->Add( m_lstLogEvents, 1, wxALL|wxEXPAND, 5 );
	
	bSizer5->Add( bSizer3, 1, wxEXPAND, 5 );
	
	m_txtResultsTitle = new wxStaticText( this, wxID_ANY, _("ResultsTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtResultsTitle->Wrap( -1 );
	m_txtResultsTitle->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_txtResultsTitle, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_treeResults = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,250 ), wxTR_DEFAULT_STYLE );
	m_treeResults->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	m_treeResults->SetMinSize( wxSize( -1,250 ) );
	
	bSizer4->Add( m_treeResults, 3, wxALL|wxEXPAND, 5 );
	
	m_rtbResultInfo = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 200,-1 ), wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_rtbResultInfo->SetFont( wxFont( 8, 74, 90, 90, false, wxT("Tahoma") ) );
	m_rtbResultInfo->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_rtbResultInfo->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer4->Add( m_rtbResultInfo, 2, wxEXPAND | wxALL, 5 );
	
	bSizer5->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnStop = new wxButton( this, wxID_ANY, _("ButtonStop"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnStop, 0, wxALL, 5 );
	
	m_btnRestart = new wxButton( this, wxID_ANY, _("ButtonRestart"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnRestart, 0, wxALL, 5 );
	
	bSizer5->Add( bSizer6, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestExecutionBaseForm::OnDialogClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestExecutionBaseForm::OnInitDialog ) );
	m_lstLogEvents->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( TestExecutionBaseForm::OnLogEventItemSelected ), NULL, this );
	m_lstLogEvents->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( TestExecutionBaseForm::OnLogEventItemSelected ), NULL, this );
	m_btnStop->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestExecutionBaseForm::OnStopButtonClick ), NULL, this );
	m_btnRestart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestExecutionBaseForm::OnRestartButtonClick ), NULL, this );
}

TestExecutionBaseForm::~TestExecutionBaseForm()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestExecutionBaseForm::OnDialogClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestExecutionBaseForm::OnInitDialog ) );
	m_lstLogEvents->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( TestExecutionBaseForm::OnLogEventItemSelected ), NULL, this );
	m_lstLogEvents->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( TestExecutionBaseForm::OnLogEventItemSelected ), NULL, this );
	m_btnStop->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestExecutionBaseForm::OnStopButtonClick ), NULL, this );
	m_btnRestart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestExecutionBaseForm::OnRestartButtonClick ), NULL, this );
	
}
