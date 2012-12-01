// [TERMS&CONDITIONS]

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
    m_pConfigLoader->SetSource(strConfigurationSource);
    m_pConfigLoader->Load();
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
    // Gets the value tree
    TATKeyValueNode* pValueTree = m_pConfigLoader->GetValueTree();
    // Gets the SUT node, which contains the available compiler configurations
    TATNode* pSutNode = pValueTree->GetChild(wxT("S")).begin()->second;
    // Gets the available compiler configurations
    TATKeyValueNode::TNodeCollection compileConfigurations = pSutNode->GetChild(wxT("CompilerConfiguration"));

    // Collects the compiler configuration names
    std::list<wxString> compilerConfigurationNames = std::list<wxString>();

    for(TATKeyValueNode::TNodeCollection::iterator iNode = compileConfigurations.begin(); iNode != compileConfigurations.end(); ++iNode)
    {
        compilerConfigurationNames.push_back(dynamic_cast<TATKeyValueNode*>(iNode->second)->GetValue());
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

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis
