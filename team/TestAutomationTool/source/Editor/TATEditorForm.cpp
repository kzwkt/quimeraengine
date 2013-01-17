// [TERMS&CONDITIONS]

#include "Editor/TATEditorForm.h"

#include <map>
#include <wx/msgdlg.h>

#include "../resources/embedded/resources.h"
#include "TestConfiguration/TATTestConfigurationForm.h"
#include "STATFileSystemHelper.h"

using Kinesis::TestAutomationTool::Backend::STATFileSystemHelper;

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

TATEditorForm::TATEditorForm(wxWindow* pParent, const wxString &strConfigurationFilePath) : 
                                                                      EditorBaseForm(pParent),
                                                                      m_bIsModified(false),
                                                                      m_bWasModified(false),
                                                                      m_bFileLoaded(false),
                                                                      m_strConfigurationFilePath(strConfigurationFilePath)
{
    this->SetIcon(wxIcon(TAT_ICON_APP));

    m_btnSave->Enable(false);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATEditorForm::~TATEditorForm()
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

bool TATEditorForm::SaveConfigurationFile(const wxString &strFilePath)
{
    // Sets the moification flags
    m_bIsModified = false;
    m_bWasModified = true;

    m_btnSave->Enable(false);

    // Saves the file
    wxString strFileContent = m_rtbConfigurationFile->GetValue();
    return STATFileSystemHelper::Write(strFilePath, strFileContent);
}

bool TATEditorForm::LoadConfigurationFile(const wxString &strFilePath)
{
    // Loads the file
    wxString strFileContent;
    bool bResult = STATFileSystemHelper::Read(strFilePath, strFileContent);

    // Puts the text in the box
    m_rtbConfigurationFile->WriteText(strFileContent);
    
    if(bResult)
    {
        m_bFileLoaded = true;
    }

    return bResult;
}

void TATEditorForm::ForceConfigurationFormToReload()
{
    if(m_bWasModified)
    {
        TATTestConfigurationForm* pConfigurationForm = dynamic_cast<TATTestConfigurationForm*>(m_parent);
        pConfigurationForm->LoadConfiguration();
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

void TATEditorForm::OnInitDialog( wxInitDialogEvent& event )
{
    // Loads the configuration file
    if(!this->LoadConfigurationFile(m_strConfigurationFilePath))
    {
        m_lblMessages->SetLabelText(_("ErrorOccurredWhileLoadingFile"));
        m_rtbConfigurationFile->Enable(false);
    }
    else
    {
        m_lblMessages->SetLabelText(_("FileLoaded"));
        m_rtbConfigurationFile->Enable(true);
    }
}

void TATEditorForm::OnDialogClose( wxCloseEvent& event )
{
    this->ForceConfigurationFormToReload();

    this->Destroy();
}

void TATEditorForm::OnConfigurationFileTextChanged( wxCommandEvent& event )
{
    if(m_bFileLoaded)
    {
        m_bIsModified = true;
        m_btnSave->Enable(true);
    }
}

void TATEditorForm::OnSaveButtonClick( wxCommandEvent& event )
{
    if(!this->SaveConfigurationFile(m_strConfigurationFilePath))
    {
        m_lblMessages->SetLabelText(_("ErrorOccurredWhileSavingFile"));
    }
    else
    {
        m_lblMessages->SetLabelText(_("FileSaved"));
    }
}

void TATEditorForm::OnCloseButtonClick( wxCommandEvent& event )
{
    this->Close();
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
