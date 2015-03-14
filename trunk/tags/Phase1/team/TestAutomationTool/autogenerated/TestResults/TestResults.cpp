///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TestResults.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

TestResultsBaseForm::TestResultsBaseForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_txtResults = new wxStaticText( this, wxID_ANY, _("ResultsTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtResults->Wrap( -1 );
	m_txtResults->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_txtResults, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	m_dirPickerTestResults = new wxDirPickerCtrl( this, ID_DIRPICKER_DIRSELECTED, wxEmptyString, _("SelectFolder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer3->Add( m_dirPickerTestResults, 0, wxALL|wxEXPAND, 5 );
	
	m_treeResults = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,250 ), wxTR_DEFAULT_STYLE );
	m_treeResults->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	m_treeResults->SetMinSize( wxSize( -1,250 ) );
	
	bSizer3->Add( m_treeResults, 3, wxALL|wxEXPAND, 5 );
	
	bSizer5->Add( bSizer3, 4, wxEXPAND, 5 );
	
	m_txtResultInfo = new wxStaticText( this, wxID_ANY, _("ResultInfo"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtResultInfo->Wrap( -1 );
	m_txtResultInfo->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_txtResultInfo, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_rtbResultInfo = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 70,-1 ), wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_rtbResultInfo->SetFont( wxFont( 8, 74, 90, 90, false, wxT("Tahoma") ) );
	m_rtbResultInfo->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_rtbResultInfo->SetMinSize( wxSize( 70,-1 ) );
	
	bSizer4->Add( m_rtbResultInfo, 1, wxEXPAND | wxALL, 5 );
	
	bSizer5->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnRefresh = new wxButton( this, ID_BUTTON_REFRESH, _("ButtonRefresh"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnRefresh, 0, wxALL, 5 );
	
	bSizer5->Add( bSizer6, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestResultsBaseForm::OnDialogClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestResultsBaseForm::OnInitDialog ) );
	m_dirPickerTestResults->Connect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( TestResultsBaseForm::OnTestResultsDirChanged ), NULL, this );
	m_btnRefresh->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestResultsBaseForm::OnRefreshButtonClick ), NULL, this );
}

TestResultsBaseForm::~TestResultsBaseForm()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestResultsBaseForm::OnDialogClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestResultsBaseForm::OnInitDialog ) );
	m_dirPickerTestResults->Disconnect( wxEVT_COMMAND_DIRPICKER_CHANGED, wxFileDirPickerEventHandler( TestResultsBaseForm::OnTestResultsDirChanged ), NULL, this );
	m_btnRefresh->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestResultsBaseForm::OnRefreshButtonClick ), NULL, this );
	
}
