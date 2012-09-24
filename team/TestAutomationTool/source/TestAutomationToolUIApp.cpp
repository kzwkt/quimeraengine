// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIApp.h"
#include "SplashScreen/TATSplashScreen.h"
#include "TestConfiguration/TATTestConfigurationForm.h"

#include <wx/stdpaths.h>

using Kinesis::TestAutomationTool::UI::TATSplashScreen;
using Kinesis::TestAutomationTool::UI::TATTestConfigurationForm;

namespace Kinesis
{
namespace TestAutomationTool
{

IMPLEMENT_APP(TestAutomationToolUIApp);

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

bool TestAutomationToolUIApp::OnInit()
{
    // I18n initialization
    this->InitializeI18n(wxLANGUAGE_ENGLISH);

    // UI presentation
    this->ShowSplashScreen();

    return true;
}

void TestAutomationToolUIApp::InitializeI18n(wxLanguage currentLang)
{
    m_locale.Init(currentLang, wxLOCALE_DONT_LOAD_DEFAULT);

    // - Adds the relative path of all the translation dictionaries
    wxLocale::AddCatalogLookupPathPrefix(wxT("../../../resources/i18n/"));

    // - Adds translation dictionaries
    m_locale.AddCatalog(wxT("TestConfiguration"));
    m_locale.AddCatalog(wxT("TestExecution"));
    m_locale.AddCatalog(wxT("Editor"));
}

void TestAutomationToolUIApp::ShowSplashScreen()
{
    m_pSplashScreen = new TATSplashScreen(0L);
    m_pSplashScreen->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(TestAutomationToolUIApp::OnSplashScreenClose));
    m_pSplashScreen->Show();
}

void TestAutomationToolUIApp::ShowFirstWindow()
{
    m_pFirstWindow = new TATTestConfigurationForm();
    m_pFirstWindow->Show();
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TestAutomationToolUIApp::OnSplashScreenClose( wxCloseEvent& event )
{
    this->ShowFirstWindow();
    event.Skip();
}


}//namespace TestAutomationTool
}//namespace Kinesis
