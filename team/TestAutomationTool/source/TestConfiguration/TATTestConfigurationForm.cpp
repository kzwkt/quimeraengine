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

void TATTestConfigurationForm::ClearGrid(wxGrid* pGrid) const
{
    if(pGrid->GetNumberRows() > 0)
    {
        pGrid->DeleteRows(0, pGrid->GetNumberRows());
    }

    if(pGrid->GetNumberCols() > 0)
    {
        pGrid->DeleteCols(0, pGrid->GetNumberCols());
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
    // Loads the compiler configurations on the UI
    std::list<wxString> compilerConfigurations = m_backend.GetCompilerConfigurations();

    for(std::list<wxString>::iterator iCompilerConfigName = compilerConfigurations.begin(); iCompilerConfigName != compilerConfigurations.end(); ++iCompilerConfigName)
    {
        m_clCompilationConfiguration->Insert(*iCompilerConfigName, 0);

        // Checked by default
        m_clCompilationConfiguration->Check(0);
        m_backend.SelectCompilerConfiguration(*iCompilerConfigName, true);
    }

    // Loads the flag combinations on the UI
    TATTestAutomationToolConfiguration::TFlagCombinationCollection flagCombinations = m_backend.GetFlagCombinations();

    for(TATTestAutomationToolConfiguration::TFlagCombinationCollection::iterator iFlagCombination = flagCombinations.begin(); iFlagCombination != flagCombinations.end(); ++iFlagCombination)
    {
        m_clFlagCombinations->Insert(iFlagCombination->first, 0);
        m_clFlagCombinations->Check(0);
    }

    // Clears the flag values grid
    this->ClearGrid(m_gridFlagValues);
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
    // Updates the UI, showing all the values in the selected flag combination
    std::map<wxString, wxString> flagValues = m_backend.GetFlagCombinations()[event.GetString()];

    // Clears the grid
    this->ClearGrid(m_gridFlagValues);

    // One row per flag value
    m_gridFlagValues->AppendRows(flagValues.size());
    m_gridFlagValues->AppendCols(2);

    const int FLAG_NAME_COLUMN = 0;
    const int FLAG_VALUE_COLUMN = 1;
    int nRow = 0;

    // Configures the labels
    m_gridFlagValues->SetColLabelValue(FLAG_NAME_COLUMN, _("FLAG_NAME"));
    m_gridFlagValues->SetColLabelValue(FLAG_VALUE_COLUMN, _("FLAG_VALUE"));

    for(std::map<wxString, wxString>::iterator iFlagValue = flagValues.begin(); iFlagValue != flagValues.end(); ++iFlagValue)
    {
        // Headers: Flag name - Flag value
        m_gridFlagValues->SetCellValue(iFlagValue->first, nRow, FLAG_NAME_COLUMN);
        m_gridFlagValues->SetCellValue(iFlagValue->second, nRow, FLAG_VALUE_COLUMN);

        ++nRow;
    }

    m_gridFlagValues->AutoSizeColumns();
}

void TATTestConfigurationForm::OnFlagCombinationsCheckListBoxToggled( wxCommandEvent& event )
{
    m_backend.SelectFlagCombination(event.GetString(), m_clFlagCombinations->IsChecked(event.GetInt()));
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
