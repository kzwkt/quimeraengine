///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Editor.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

EditorBaseForm::EditorBaseForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_rtbConfigurationFile = new wxRichTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	m_rtbConfigurationFile->SetFont( wxFont( 8, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer5->Add( m_rtbConfigurationFile, 1, wxEXPAND | wxALL, 5 );
	
	m_lblReminder = new wxStaticText( this, wxID_ANY, _("ReminderAboutConfigurationForm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblReminder->Wrap( -1 );
	m_lblReminder->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_lblReminder->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOWTEXT ) );
	
	bSizer5->Add( m_lblReminder, 0, wxALL|wxEXPAND, 5 );
	
	m_lblMessages = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_lblMessages->Wrap( -1 );
	m_lblMessages->SetForegroundColour( wxColour( 0, 70, 234 ) );
	
	bSizer5->Add( m_lblMessages, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnSave = new wxButton( this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnSave, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	m_btnClose = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnClose, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );
	
	bSizer5->Add( bSizer6, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorBaseForm::OnDialogClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( EditorBaseForm::OnInitDialog ) );
	m_rtbConfigurationFile->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( EditorBaseForm::OnConfigurationFileTextChanged ), NULL, this );
	m_btnSave->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorBaseForm::OnSaveButtonClick ), NULL, this );
	m_btnClose->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorBaseForm::OnCloseButtonClick ), NULL, this );
}

EditorBaseForm::~EditorBaseForm()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EditorBaseForm::OnDialogClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( EditorBaseForm::OnInitDialog ) );
	m_rtbConfigurationFile->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( EditorBaseForm::OnConfigurationFileTextChanged ), NULL, this );
	m_btnSave->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorBaseForm::OnSaveButtonClick ), NULL, this );
	m_btnClose->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditorBaseForm::OnCloseButtonClick ), NULL, this );
	
}
