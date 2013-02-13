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

#ifndef __TESTAUTOMATIONTOOLUIAPP__
#define __TESTAUTOMATIONTOOLUIAPP__

#include <wx/app.h>

// At global namespace

/// <summary>
/// The class that defines the application to be executed.
/// </summary>
class TestAutomationToolUIApp : public wxApp
{
    // METHODS
	// ---------------
public:

    /*! @copydoc wxApp::OnInit() */
    virtual bool OnInit();

protected:

    /// <summary>
    /// Given a language identifier, initializes the application so all the needed translation dictionaries are loaded
    /// for the desired language.
    /// </summary>
    /// <param name="currentLang">The language identifier.</param>
    void InitializeI18n(wxLanguage currentLang);

    /// <summary>
    /// Shows the splash screen window.
    /// </summary>
    void ShowSplashScreen();

    /// <summary>
    /// Shows the first window of the application.
    /// </summary>
    void ShowFirstWindow();


    // EVENT HANDLERS
	// ---------------
public:

    /// <summary>
    /// Event handler called when the splash screen window is to be closed.
    /// </summary>
    /// <param name="event">The event argument.</param>
    void OnSplashScreenClose( wxCloseEvent& event );


    // ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Instance of the application's localization manager object.
    /// </summary>
    wxLocale m_locale;

    /// <summary>
    /// The splash screen window.
    /// </summary>
    wxFrame* m_pSplashScreen;

    /// <summary>
    /// The first window of the application to be shown.
    /// </summary>
    wxWindow* m_pFirstWindow;
};


#endif // __TESTAUTOMATIONTOOLUIAPP__
