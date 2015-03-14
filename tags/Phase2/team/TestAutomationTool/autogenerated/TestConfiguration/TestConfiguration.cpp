///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec  2 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "TestConfiguration.h"

///////////////////////////////////////////////////////////////////////////
using namespace Kinesis::TestAutomationTool::UI;

TestConfigurationBaseForm::TestConfigurationBaseForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_txtSelectCompilationConfiguration = new wxStaticText( this, wxID_ANY, _("CompilationConfigurationTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtSelectCompilationConfiguration->Wrap( -1 );
	m_txtSelectCompilationConfiguration->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_txtSelectCompilationConfiguration, 0, wxALL, 5 );
	
	wxArrayString m_clCompilationConfigurationChoices;
	m_clCompilationConfiguration = new wxCheckListBox( this, ID_CHECKLIST_COMPILATION_CONFIG, wxDefaultPosition, wxDefaultSize, m_clCompilationConfigurationChoices, wxLB_MULTIPLE|wxLB_NEEDED_SB );
	bSizer1->Add( m_clCompilationConfiguration, 1, wxALL|wxEXPAND, 5 );
	
	m_txtFlagCombinationsTitle = new wxStaticText( this, wxID_ANY, _("FlagCombinationsTitle"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_txtFlagCombinationsTitle->Wrap( -1 );
	m_txtFlagCombinationsTitle->SetFont( wxFont( 12, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer1->Add( m_txtFlagCombinationsTitle, 0, wxALL, 5 );
	
	m_txtFlagCombinationSelectionTitle = new wxStaticText( this, wxID_ANY, _("FlagCombinationsSelectionTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtFlagCombinationSelectionTitle->Wrap( -1 );
	bSizer1->Add( m_txtFlagCombinationSelectionTitle, 0, wxALL, 5 );
	
	wxArrayString m_clFlagCombinationsChoices;
	m_clFlagCombinations = new wxCheckListBox( this, ID_CHECKLIST_FLAG_COMBINATION, wxDefaultPosition, wxDefaultSize, m_clFlagCombinationsChoices, 0 );
	bSizer1->Add( m_clFlagCombinations, 1, wxALL|wxEXPAND, 5 );
	
	m_txtFlagValuesTitle = new wxStaticText( this, wxID_ANY, _("FlagValuesTitle"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtFlagValuesTitle->Wrap( -1 );
	m_txtFlagValuesTitle->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	bSizer1->Add( m_txtFlagValuesTitle, 0, wxALL, 5 );
	
	m_gridFlagValues = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	m_gridFlagValues->CreateGrid( 5, 5 );
	m_gridFlagValues->EnableEditing( false );
	m_gridFlagValues->EnableGridLines( true );
	m_gridFlagValues->EnableDragGridSize( false );
	m_gridFlagValues->SetMargins( 0, 0 );
	
	// Columns
	m_gridFlagValues->SetColSize( 0, 80 );
	m_gridFlagValues->SetColSize( 1, 80 );
	m_gridFlagValues->SetColSize( 2, 80 );
	m_gridFlagValues->SetColSize( 3, 80 );
	m_gridFlagValues->SetColSize( 4, 80 );
	m_gridFlagValues->AutoSizeColumns();
	m_gridFlagValues->EnableDragColMove( false );
	m_gridFlagValues->EnableDragColSize( true );
	m_gridFlagValues->SetColLabelSize( 30 );
	m_gridFlagValues->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_gridFlagValues->EnableDragRowSize( true );
	m_gridFlagValues->SetRowLabelSize( 0 );
	m_gridFlagValues->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	m_gridFlagValues->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	bSizer1->Add( m_gridFlagValues, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer2->SetMinSize( wxSize( -1,30 ) ); 
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnEditor = new wxButton( this, ID_BUTTON_EDITOR, _("EditorButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_btnEditor, 0, wxALL, 5 );
	
	bSizer2->Add( bSizer3, 0, 0, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	bSizer2->Add( bSizer5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_btnViewResults = new wxButton( this, ID_BUTTON_VIEWRESULTS, _("ViewResultsButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_btnViewResults, 0, wxALIGN_TOP|wxALL, 5 );
	
	m_btnLaunch = new wxButton( this, ID_BUTTON_LAUNCH, _("LaunchButton"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_btnLaunch, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	bSizer2->Add( bSizer4, 0, 0, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestConfigurationBaseForm::OnDialogClose ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestConfigurationBaseForm::OnInitDialog ) );
	m_clCompilationConfiguration->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( TestConfigurationBaseForm::OnCompilationConfigurationCheckListBoxToggled ), NULL, this );
	m_clFlagCombinations->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( TestConfigurationBaseForm::OnFlagCombinationsCheckListBoxSelected ), NULL, this );
	m_clFlagCombinations->Connect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( TestConfigurationBaseForm::OnFlagCombinationsCheckListBoxToggled ), NULL, this );
	m_btnEditor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnEditorButtonClick ), NULL, this );
	m_btnViewResults->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnViewResultsButtonClick ), NULL, this );
	m_btnLaunch->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnLaunchButtonClick ), NULL, this );
}

TestConfigurationBaseForm::~TestConfigurationBaseForm()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( TestConfigurationBaseForm::OnDialogClose ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( TestConfigurationBaseForm::OnInitDialog ) );
	m_clCompilationConfiguration->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( TestConfigurationBaseForm::OnCompilationConfigurationCheckListBoxToggled ), NULL, this );
	m_clFlagCombinations->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( TestConfigurationBaseForm::OnFlagCombinationsCheckListBoxSelected ), NULL, this );
	m_clFlagCombinations->Disconnect( wxEVT_COMMAND_CHECKLISTBOX_TOGGLED, wxCommandEventHandler( TestConfigurationBaseForm::OnFlagCombinationsCheckListBoxToggled ), NULL, this );
	m_btnEditor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnEditorButtonClick ), NULL, this );
	m_btnViewResults->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnViewResultsButtonClick ), NULL, this );
	m_btnLaunch->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TestConfigurationBaseForm::OnLaunchButtonClick ), NULL, this );
	
}
