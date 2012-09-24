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
	
	m_rtbLog = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_rtbLog->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	m_rtbLog->SetForegroundColour( wxColour( 255, 255, 255 ) );
	m_rtbLog->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer5->Add( m_rtbLog, 1, wxEXPAND | wxALL, 5 );
	
	m_txtResultsTitle = new wxStaticText( this, wxID_ANY, _("ResultsTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtResultsTitle->Wrap( -1 );
	m_txtResultsTitle->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_txtResultsTitle, 0, wxALL, 5 );
	
	m_treeResults = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE );
	m_treeResults->SetFont( wxFont( 7, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( m_treeResults, 1, wxALL|wxEXPAND, 5 );
	
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
}

TestExecutionBaseForm::~TestExecutionBaseForm()
{
}
