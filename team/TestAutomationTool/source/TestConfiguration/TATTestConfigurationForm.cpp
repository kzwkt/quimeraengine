// [TERMS&CONDITIONS]

#include "TestConfiguration/TATTestConfigurationForm.h"

#include <map>
#include <wx/msgdlg.h>

#include "TestExecution/TestExecution.h"
#include "TestConfiguration/STATAppSettings.h"
#include "TestConfiguration/TATValidationException.h"

using Kinesis::TestAutomationTool::Backend::STATAppSettings;
using Kinesis::TestAutomationTool::Backend::TATValidationException;

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



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestConfigurationForm::TATTestConfigurationForm() : TestConfigurationBaseForm(NULL)
{
    InitializeBackend();
}
	
	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestConfigurationForm::~TATTestConfigurationForm()
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

void TATTestConfigurationForm::ShowExecutionWindow()
{
    m_pExecutionForm = new TestExecutionBaseForm(this);
    m_pExecutionForm->Show();
}

void TATTestConfigurationForm::InitializeBackend()
{
    try
    {
        m_backend.LoadConfiguration(STATAppSettings::GetConfigurationFilePath());
    }
    catch(const TATValidationException& validationEx)
    {
        std::map<wxString, wxString> translationDictionary;
        translationDictionary.insert(std::pair<wxString, wxString>("MULTIPLE_RULES", _("ERROR_MESSAGE_DUPLICATED_RULE")));
        translationDictionary.insert(std::pair<wxString, wxString>("MAXCOUNT", _("ERROR_MESSAGE_MAXCOUNT_RULE_VIOLATED")));
        translationDictionary.insert(std::pair<wxString, wxString>("CANTBEEMPTY", _("ERROR_MESSAGE_CANTBEEMPTY_RULE_VIOLATED")));
        translationDictionary.insert(std::pair<wxString, wxString>("ISOBLIGATORY", _("ERROR_MESSAGE_ISOBLIGATORY_RULE_VIOLATED")));

        wxMessageDialog messageBox(this, translationDictionary[validationEx.what()] + validationEx.GetNodeName(), _("ERROR_OCURRED_WHEN_LOADING_CONFIG"), wxOK | wxICON_ERROR);
        messageBox.ShowModal();
    }
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestConfigurationForm::OnInitDialog( wxInitDialogEvent& event )
{
    std::list<wxString> compilerConfigurations = m_backend.GetCompilerConfigurations();

    for(std::list<wxString>::iterator iCompilerConfigName = compilerConfigurations.begin(); iCompilerConfigName != compilerConfigurations.end(); ++iCompilerConfigName)
    {
        m_clCompilationConfiguration->Insert(*iCompilerConfigName, 0);
    }
}

void TATTestConfigurationForm::OnDialogClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATTestConfigurationForm::OnCompilationConfigurationCheckListBoxToggled( wxCommandEvent& event )
{
    m_backend.SelectCompilerConfiguration(event.GetString(), m_clCompilationConfiguration->IsChecked(event.GetInt()));
}

void TATTestConfigurationForm::OnFlagCombinationsCheckListBoxSelected( wxCommandEvent& event )
{
}

void TATTestConfigurationForm::OnFlagCombinationsCheckListBoxToggled( wxCommandEvent& event )
{
}

void TATTestConfigurationForm::OnEditorButtonClick( wxCommandEvent& event )
{
}

void TATTestConfigurationForm::OnLaunchButtonClick( wxCommandEvent& event )
{
    ShowExecutionWindow();
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
