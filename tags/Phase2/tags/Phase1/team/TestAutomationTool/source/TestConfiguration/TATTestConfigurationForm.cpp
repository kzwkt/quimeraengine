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

#include "TestConfiguration/TATTestConfigurationForm.h"

#include <map>
#include <wx/msgdlg.h>

#include "Editor/TATEditorForm.h"
#include "TestConfiguration/STATAppSettings.h"
#include "TestConfiguration/TATValidationException.h"
#include "TestExecution/TATTestExecutionForm.h"
#include "TestResults/TATTestResultsForm.h"
#include "TestConfiguration/ITATConfigLoader.h"
#include "TestConfiguration/TATKeyValueNode.h"

using Kinesis::TestAutomationTool::Backend::TATNode;
using Kinesis::TestAutomationTool::Backend::TATKeyValueNode;
using Kinesis::TestAutomationTool::Backend::STATAppSettings;
using Kinesis::TestAutomationTool::Backend::TATValidationException;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;
using Kinesis::TestAutomationTool::Backend::TATTestModulesExecutionInfo;


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

void TATTestConfigurationForm::LoadConfiguration()
{
    this->ResetConfiguration();

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
        m_clFlagCombinations->Append(iFlagCombination->first);
        m_clFlagCombinations->Check(m_clFlagCombinations->GetCount()-1);
        m_backend.SelectFlagCombination(iFlagCombination->first, true);
    }

    // Refreshes the status of the launch button
    this->EnableLaunchButtonDependingOnSelection();
}

void TATTestConfigurationForm::ResetConfiguration()
{
    this->InitializeBackend();

    // Clears the compilation configuration list
    this->m_clCompilationConfiguration->Clear();

    // Clears the flag combination list
    this->m_clFlagCombinations->Clear();

    // Clears the flag values grid
    this->ClearGrid(m_gridFlagValues);

    this->EnableLaunchButtonDependingOnSelection();
}

void TATTestConfigurationForm::ShowExecutionWindow()
{
    // Test execution window
    // ----------------------------
    wxString strConfigurationFilePath;
    std::map<wxString, TATCompilerInfo> compilerInfos;
    std::map< wxString, std::map<wxString, wxString> > filteredFlagCombinations;
    std::list<wxString> compilationConfigurations;

    // Gets the configuration file path
    TATKeyValueNode* pValueTree = m_backend.GetConfigLoader()->GetValueTree();
    TATNode* pSUTNode = pValueTree->GetChild(wxT("S")).begin()->second;
    TATNode* pConfigurationFilePathNode = pSUTNode->GetChild(wxT("ConfigurationFilePath")).begin()->second;
    strConfigurationFilePath = dynamic_cast<TATKeyValueNode*>(pConfigurationFilePathNode)->GetValue();

    // Gets the selected compilation configurations
    compilationConfigurations = m_backend.GetCompilerConfigurationSelection();

    // Gets compilers information
    this->ExtractCompilerInfosFromValueTree(pValueTree, compilerInfos);

    // Filters flag combinations by selection
    TATTestAutomationToolConfiguration::TFlagCombinationCollection flagsCombination = m_backend.GetFlagCombinations();
    std::list<wxString> flagsSelection = m_backend.GetFlagCombinationSelection();
    this->FilterFlagCombinationListBySelection(flagsCombination, flagsSelection, filteredFlagCombinations);

    // Creates the test execution forms, using the calculated values
    m_pExecutionForm = new TATTestExecutionForm(this,
                                                strConfigurationFilePath,
                                                filteredFlagCombinations,
                                                compilationConfigurations,
                                                compilerInfos);
    m_pExecutionForm->Show();
}

void TATTestConfigurationForm::ShowResultsWindow()
{
    wxString strTestResultsPath;

    // Gets the configuration file path
    TATKeyValueNode* pValueTree = m_backend.GetConfigLoader()->GetValueTree();
    TATNode* pTestNode = pValueTree->GetChild(wxT("T")).begin()->second; // [TODO] Thund: Currently, all the paths have the same value for every test configuration
    TATNode* pTestResultsPathNode = pTestNode->GetChild(wxT("ResultsPath")).begin()->second;
    strTestResultsPath = dynamic_cast<TATKeyValueNode*>(pTestResultsPathNode)->GetValue();

    // Creates the test execution forms, using the calculated values
    m_pTestResultsForm = new TATTestResultsForm(this, strTestResultsPath, true);
    m_pTestResultsForm->Show();
}

void TATTestConfigurationForm::ShowEditorWindow()
{
    // Creates the test execution forms, using the calculated values
    m_pEditorForm = new TATEditorForm(this, STATAppSettings::GetConfigurationFilePath());
    m_pEditorForm->ShowModal();
}

void TATTestConfigurationForm::ExtractCompilerInfosFromValueTree(TATKeyValueNode* pValueTree, std::map<wxString, TATCompilerInfo>& compilerInfos) const
{
    TATKeyValueNode::TNodeCollection compilersData = pValueTree->GetChild(wxT("C"));
    TATKeyValueNode::TNodeCollection testModulesData = pValueTree->GetChild(wxT("T"));
    TATKeyValueNode::TNodeCollection projectsData = pValueTree->GetChild(wxT("P"));

    TATKeyValueNode* pCompilerNode = NULL;
    TATKeyValueNode::TNodeCollection::const_iterator iCompilerData = compilersData.begin();

    for(; iCompilerData != compilersData.end(); ++iCompilerData)
    {
        pCompilerNode = dynamic_cast<TATKeyValueNode*>(iCompilerData->second);

        wxString strCompilerName = pCompilerNode->GetValue();

        // Fills the compiler data's fields
        TATCompilerInfo compilerInfo;
        compilerInfo.SetName(strCompilerName);

        TATKeyValueNode::TNodeCollection::const_iterator iCompilerDataField = pCompilerNode->GetChildren().begin();

        for(; iCompilerDataField != pCompilerNode->GetChildren().end(); ++iCompilerDataField)
        {
            wxString strFieldValue = dynamic_cast<TATKeyValueNode*>(iCompilerDataField->second)->GetValue();

            if(iCompilerDataField->first == wxT("CompilerPath"))
            {
                compilerInfo.SetCompilerPath(strFieldValue);
            }

            if(iCompilerDataField->first == wxT("CompilerCleanCommand"))
            {
                compilerInfo.SetCleanCommand(strFieldValue);
            }

            if(iCompilerDataField->first == wxT("CompilerBuildCommand"))
            {
                compilerInfo.SetBuildCommand(strFieldValue);
            }

            if(iCompilerDataField->first == wxT("CompilerBuildParams"))
            {
                compilerInfo.SetBuildParams(strFieldValue);
            }

            if(iCompilerDataField->first == wxT("CompilerCleanParams"))
            {
                compilerInfo.SetCleanParams(strFieldValue);
            }
            
            if(iCompilerDataField->first == wxT("CompilerFileSpecifier"))
            {
                compilerInfo.SetFileSpecifier(strFieldValue);
            }
        }

        // Gets projects related to the current compiler
        TATKeyValueNode::TNodeCollection::const_iterator iSUTProject = projectsData.begin();
        TATKeyValueNode* pSutProject = NULL;
        std::list<wxString> sutProjects;

        for(; iSUTProject != projectsData.end(); ++iSUTProject)
        {
            wxString strCompilerNameForProject = dynamic_cast<TATKeyValueNode*>(iSUTProject->second->GetChild(wxT("Compiler")).begin()->second)->GetValue();

            if(strCompilerNameForProject == strCompilerName)
            {
                pSutProject = dynamic_cast<TATKeyValueNode*>(iSUTProject->second);
                wxString strProjectPath = dynamic_cast<TATKeyValueNode*>(pSutProject->GetChild(wxT("CompilationInfoPath")).begin()->second)->GetValue();
                sutProjects.push_back(strProjectPath);
            }
        }

        compilerInfo.SetSUTProjects(sutProjects);

        // Gets test modules execution information related to the current compiler
        TATKeyValueNode::TNodeCollection::const_iterator iTestModuleInfo = testModulesData.begin();
        TATKeyValueNode* pTestModulesInfo = NULL;
        std::list<TATTestModulesExecutionInfo> testModulesExecutionInfo;

        for(; iTestModuleInfo != testModulesData.end(); ++iTestModuleInfo)
        {
            wxString strCompilerNameForTestModules = dynamic_cast<TATKeyValueNode*>(iTestModuleInfo->second->GetChild(wxT("Compiler")).begin()->second)->GetValue();

            if(strCompilerNameForTestModules == strCompilerName)
            {
                pTestModulesInfo = dynamic_cast<TATKeyValueNode*>(iTestModuleInfo->second);
                wxString strTestProjectPath = dynamic_cast<TATKeyValueNode*>(pTestModulesInfo->GetChild(wxT("CompilationInfoPath")).begin()->second)->GetValue();
                wxString strResultsPath = dynamic_cast<TATKeyValueNode*>(pTestModulesInfo->GetChild(wxT("ResultsPath")).begin()->second)->GetValue();
                wxString strModulesPath = dynamic_cast<TATKeyValueNode*>(pTestModulesInfo->GetChild(wxT("TestModulesPath")).begin()->second)->GetValue();

                TATTestModulesExecutionInfo executionInfo;
                executionInfo.SetResultsPath(strResultsPath);
                executionInfo.SetTestModulesPath(strModulesPath);
                executionInfo.SetTestProjectPath(strTestProjectPath);

                testModulesExecutionInfo.push_back(executionInfo);
            }
        }

        compilerInfo.SetTestModulesExecutionInfo(testModulesExecutionInfo);

        compilerInfos.insert(std::pair<wxString, TATCompilerInfo>(strCompilerName, compilerInfo));
    }
}

void TATTestConfigurationForm::FilterFlagCombinationListBySelection(const TATTestAutomationToolConfiguration::TFlagCombinationCollection& flagsCombination,
                                                                    const std::list<wxString>& flagsSelection,
                                                                    TATTestAutomationToolConfiguration::TFlagCombinationCollection& filteredFlagCombinations) const
{
    for(TATTestAutomationToolConfiguration::TFlagCombinationCollection::const_iterator iFlagComb = flagsCombination.begin(); iFlagComb != flagsCombination.end(); ++iFlagComb)
    {
        // Checks if the combination is selected
        std::list<wxString>::const_iterator iSelectedFlag = flagsSelection.begin();

        while(iSelectedFlag != flagsSelection.end() && (*iSelectedFlag) != iFlagComb->first)
        {
            ++iSelectedFlag;
        }

        if(iSelectedFlag != flagsSelection.end())
        {
            // If it's the case, adds it to the result
            filteredFlagCombinations.insert(TATTestAutomationToolConfiguration::TFlagCombination(iFlagComb->first, iFlagComb->second));
        }
    }
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

void TATTestConfigurationForm::EnableLaunchButtonDependingOnSelection()
{
    bool bThereIsAtLeastOneItemSelectedInBothLists = m_backend.GetCompilerConfigurationSelection().size() > 0 && 
                                                     m_backend.GetFlagCombinationSelection().size() > 0;
    m_btnLaunch->Enable(bThereIsAtLeastOneItemSelectedInBothLists);
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
    this->LoadConfiguration();
}

void TATTestConfigurationForm::OnDialogClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATTestConfigurationForm::OnCompilationConfigurationCheckListBoxToggled( wxCommandEvent& event )
{
    m_backend.SelectCompilerConfiguration(event.GetString(), m_clCompilationConfiguration->IsChecked(event.GetInt()));

    // Refreshes the status of the launch button
    this->EnableLaunchButtonDependingOnSelection();
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

    // Refreshes the status of the launch button
    this->EnableLaunchButtonDependingOnSelection();
}

void TATTestConfigurationForm::OnEditorButtonClick( wxCommandEvent& event )
{
    ShowEditorWindow();
}

void TATTestConfigurationForm::OnLaunchButtonClick( wxCommandEvent& event )
{
    ShowExecutionWindow();
}

void TATTestConfigurationForm::OnViewResultsButtonClick( wxCommandEvent& event )
{
    ShowResultsWindow();
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
