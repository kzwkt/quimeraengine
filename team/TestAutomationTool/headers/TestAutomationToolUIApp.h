// [TERMS&CONDITIONS]

#ifndef __TESTAUTOMATIONTOOLUIAPP__
#define __TESTAUTOMATIONTOOLUIAPP__

#include <wx/app.h>

namespace Kinesis
{
namespace TestAutomationTool
{

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


    // ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Instance of the application's localization manager object.
    /// </summary>
    wxLocale m_locale;
};

}//namespace TestAutomationTool
}//namespace Kinesis

#endif // __TESTAUTOMATIONTOOLUIAPP__
