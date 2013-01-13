// [TERMS&CONDITIONS]

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
