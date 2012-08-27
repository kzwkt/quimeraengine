// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIApp.h"
#include "SplashScreen\TATSplashScreen.h"
#include "TestConfiguration\TestConfiguration.h"

#include <wx/stdpaths.h>

using Kinesis::TestAutomationTool::UI::TATSplashScreen;
using Kinesis::TestAutomationTool::UI::TestConfigurationBaseForm;

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
    InitializeI18n(wxLANGUAGE_ENGLISH);

    // UI presentation

    //TATSplashScreen* splashScreen = new TATSplashScreen(0L);
    //splashScreen->Show();
    TestConfigurationBaseForm* pForm = new TestConfigurationBaseForm(0L);
    pForm->Show();
    return true;
}

void TestAutomationToolUIApp::InitializeI18n(wxLanguage currentLang)
{
    m_locale.Init(currentLang, wxLOCALE_DONT_LOAD_DEFAULT);

    // - Adds the relative path of all the translation dictionaries
    wxLocale::AddCatalogLookupPathPrefix(wxT("..\\..\\..\\resources\\i18n\\"));

    // - Adds translation dictionaries
    m_locale.AddCatalog(wxT("TestConfiguration"));
    m_locale.AddCatalog(wxT("TestExecution"));
    m_locale.AddCatalog(wxT("Editor"));
}

}//namespace TestAutomationTool
}//namespace Kinesis
