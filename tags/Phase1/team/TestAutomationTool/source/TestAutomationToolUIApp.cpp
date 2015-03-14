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
    // Image handlers initialization (necessary for using PNG images)
    wxImage::AddHandler(new wxPNGHandler());

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
    m_locale.AddCatalog(wxT("TestResult"));
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

