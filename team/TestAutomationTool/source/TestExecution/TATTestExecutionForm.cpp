// [TERMS&CONDITIONS]

#include "TestExecution/TATTestExecutionForm.h"

#include "TestExecution/TATwxWidgetsControlLogger.h"
#include "TestExecution/ETATResultSource.h"
#include "TestExecution/TATTestResultLoaderFactory.h"
#include "TestExecution/ITATTestResultLoader.h"

using Kinesis::TestAutomationTool::Backend::TATwxWidgetsControlLogger;
using Kinesis::TestAutomationTool::Backend::TATCompilerInfo;
using Kinesis::TestAutomationTool::Backend::ETATResultSource;
using Kinesis::TestAutomationTool::Backend::TATTestResultLoaderFactory;
using Kinesis::TestAutomationTool::Backend::ITATTestResultLoader;

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

TATTestExecutionForm::TATTestExecutionForm(wxWindow* parent, 
                                           const wxString& strConfigurationFilePath, 
                                           const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                                           const std::list<wxString>& compilationConfigurations,
                                           const std::map<wxString, TATCompilerInfo>& compilerInfos) 
                                           : TestExecutionBaseForm(parent)
{
    this->InitializeBackend(strConfigurationFilePath,
                            flagCombinations,
                            compilationConfigurations,
                            compilerInfos);
}
	
	
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATTestExecutionForm::~TATTestExecutionForm()
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

void TATTestExecutionForm::InitializeBackend(const wxString& strConfigurationFilePath, 
                                             const std::map< wxString, std::map<wxString, wxString> >& flagCombinations,
                                             const std::list<wxString>& compilationConfigurations,
                                             const std::map<wxString, TATCompilerInfo>& compilerInfos)
{
    m_backend.SetCompilerInfos(compilerInfos);
    m_backend.SetConfigurationFilePath(strConfigurationFilePath);
    m_backend.SetFlagCombinations(flagCombinations);
    m_backend.SetCompilationConfigurations(compilationConfigurations);

    // Sets the logger
    m_backend.SetLogger(new TATwxWidgetsControlLogger(m_rtbLog, false));

    // Sets the test result loader
    TATTestResultLoaderFactory testResultLoaderFactory;
    ITATTestResultLoader* pTestResultLoader = testResultLoaderFactory.CreateConfigLoader(ETATResultSource::E_XmlFile);
    m_backend.SetTestResultLoader(pTestResultLoader);
}

void TATTestExecutionForm::StartTestExecution()
{
    m_rtbLog->Clear();
    m_backend.ExecuteTests();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATTestExecutionForm::OnInitDialog( wxInitDialogEvent& event )
{
    this->StartTestExecution();
}

void TATTestExecutionForm::OnDialogClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATTestExecutionForm::OnStopButtonClick( wxCommandEvent& event )
{
}

void TATTestExecutionForm::OnRestartButtonClick( wxCommandEvent& event )
{
    this->StartTestExecution();
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
