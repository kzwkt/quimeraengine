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

#include "TestConfiguration/TATTestAutomationToolConfiguration.h"

#include "TestConfiguration/ITATConfigLoader.h"
#include "TestConfiguration/TATConfigLoaderFactory.h"
#include "TestConfiguration/STATAppSettings.h"
#include "TestConfiguration/TATKeyValueNode.h"

namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
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

TATTestAutomationToolConfiguration::TATTestAutomationToolConfiguration()
{
    TATConfigLoaderFactory factory;
    m_pConfigLoader = factory.CreateConfigLoader(ETATConfigurationSource::E_INI_FILE);
    m_pConfigLoader->SetSource(STATAppSettings::GetConfigurationFilePath());
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestAutomationToolConfiguration::~TATTestAutomationToolConfiguration()
{
    this->Destroy();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestAutomationToolConfiguration::Destroy()
{
    if(m_pConfigLoader)
    {
        delete m_pConfigLoader;
        m_pConfigLoader = NULL;
    }
}

void TATTestAutomationToolConfiguration::LoadConfiguration(const wxString& strConfigurationSource)
{
    // Loads the configuration source and creates the value tree
    m_pConfigLoader->SetSource(strConfigurationSource);
    m_pConfigLoader->Load();

    // Creates a list of flags
    TATKeyValueNode::TNodeCollection flags = m_pConfigLoader->GetValueTree()->GetChild(wxT("F"));
    std::list<TATKeyValueNode*> flagList = std::list<TATKeyValueNode*>();

    for(TATKeyValueNode::TNodeCollection::const_iterator iFlagNode = flags.begin(); iFlagNode != flags.end(); ++iFlagNode)
    {
        flagList.push_back(dynamic_cast<TATKeyValueNode*>(iFlagNode->second));
    }

    // Generates flag combinations
    this->CombineFlags(flagList);

    // Resets selections to avoid inconsistences
    m_compilerConfigurationSelection.clear();
    m_flagCombinationSelection.clear();
}

void TATTestAutomationToolConfiguration::SelectCompilerConfiguration(const wxString& strCompilerConfig, const bool& bSelected)
{
    if(bSelected)
    {
        m_compilerConfigurationSelection.push_back(strCompilerConfig);
    }
    else
    {
        m_compilerConfigurationSelection.remove(strCompilerConfig);
    }
}

void TATTestAutomationToolConfiguration::SelectFlagCombination(const wxString& strFlagCombination, const bool& bSelected)
{
    if(bSelected)
    {
        m_flagCombinationSelection.push_back(strFlagCombination);
    }
    else
    {
        m_flagCombinationSelection.remove(strFlagCombination);
    }
}

void TATTestAutomationToolConfiguration::CombineFlags(const std::list<TATKeyValueNode*>& flags)
{
    if(flags.size() > 0)
    {
        // Combines the flag value with values of the rest of the flags
        std::list< std::map<wxString, wxString> > flagCombinations;
        this->CombineFlagValue(flags.begin(), flags.end(), std::map<wxString, wxString>(), flagCombinations);

        // Stores the combinations using numerated keys
        int nCombinationNumber = 0;

        for(std::list< std::map<wxString, wxString> >::const_iterator iCombination = flagCombinations.begin(); iCombination != flagCombinations.end(); ++iCombination)
        {
            m_flagCombinations.insert(TATTestAutomationToolConfiguration::TFlagCombination(wxT("C") + wxString::FromDouble(nCombinationNumber), *iCombination));
            ++nCombinationNumber;
        }
    }
}

void TATTestAutomationToolConfiguration::CombineFlagValue(std::list<TATKeyValueNode*>::const_iterator flagToCombine,
                                                          std::list<TATKeyValueNode*>::const_iterator flagListEnd,
                                                          std::map<wxString, wxString> flagCombination,
                                                          std::list< std::map<wxString, wxString> >& outFlagCombinations) const
{
    // Obtains the first flag and its values
    TATKeyValueNode* pFlagToCombine = dynamic_cast<TATKeyValueNode*>(*flagToCombine);
    TATKeyValueNode::TNodeCollection flagValues = pFlagToCombine->GetChildren();

    // Gets the next flag in the list of flags to combine
    std::list<TATKeyValueNode*>::const_iterator nextFlagToCombineWith = flagToCombine;
    nextFlagToCombineWith++;

    // Combines the flag values with other flags' values or stores the current combination if there are no more flags to combine
    for(TATKeyValueNode::TNodeCollection::const_iterator iFlagValue = flagValues.begin(); iFlagValue != flagValues.end(); ++iFlagValue)
    {
        TATKeyValueNode* pFlagValue = dynamic_cast<TATKeyValueNode*>(iFlagValue->second);

        // Stores the flag value in the current combination (flag name, flag value)
        std::map<wxString, wxString> modifiedCombination = flagCombination;
        modifiedCombination.insert(std::pair<wxString, wxString>(pFlagToCombine->GetValue(), pFlagValue->GetValue()));

        if(nextFlagToCombineWith != flagListEnd)
        {
            // Combines the flag value with values of the next flag
            this->CombineFlagValue(nextFlagToCombineWith, flagListEnd, modifiedCombination, outFlagCombinations);
        }
        else // There are no more flags to combine
        {
            // Combination is stored in the list
            outFlagCombinations.push_back(modifiedCombination);
        }
    }
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

std::list<wxString> TATTestAutomationToolConfiguration::GetCompilerConfigurations() const
{
    std::list<wxString> compilerConfigurationNames;

    if(m_pConfigLoader->GetValueTree() != NULL)
    {
        // Gets the value tree
        TATKeyValueNode* pValueTree = m_pConfigLoader->GetValueTree();
        // Gets the SUT node, which contains the available compiler configurations
        TATNode* pSutNode = pValueTree->GetChild(wxT("S")).begin()->second;
        // Gets the available compiler configurations
        TATKeyValueNode::TNodeCollection compileConfigurations = pSutNode->GetChild(wxT("CompilerConfiguration"));

        // Collects the compiler configuration names
        for(TATKeyValueNode::TNodeCollection::iterator iNode = compileConfigurations.begin(); iNode != compileConfigurations.end(); ++iNode)
        {
            compilerConfigurationNames.push_back(dynamic_cast<TATKeyValueNode*>(iNode->second)->GetValue());
        }
    }

    return compilerConfigurationNames;
}

ITATConfigLoader* TATTestAutomationToolConfiguration::GetConfigLoader() const
{
    return m_pConfigLoader;
}

std::list<wxString> TATTestAutomationToolConfiguration::GetCompilerConfigurationSelection() const
{
    return m_compilerConfigurationSelection;
}

std::list<wxString> TATTestAutomationToolConfiguration::GetFlagCombinationSelection() const
{
    return m_flagCombinationSelection;
}

TATTestAutomationToolConfiguration::TFlagCombinationCollection TATTestAutomationToolConfiguration::GetFlagCombinations() const
{
    return m_flagCombinations;
}

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
