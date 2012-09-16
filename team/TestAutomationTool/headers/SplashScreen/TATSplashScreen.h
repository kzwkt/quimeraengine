// [TERMS&CONDITIONS]

#ifndef __TATSPLASHSCREEN__
#define __TATSPLASHSCREEN__

#include "SplashScreen\SplashScreen.h"

#include <wx/timer.h>

namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

/// <summary>
/// Frame that shows the application title along some logos during a short period of time before the application starts.
/// </summary>
class TATSplashScreen : public SplashScreenBase
{
    // CONSTANTS
    // ---------------
protected:

    /// <summary>
	/// The ammount of time the splash screen is to be shown in the screen, in milliseconds.
	/// </summary>
    static const int VISIBILITY_INTERVAL;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Constructor that receives a parent window reference.
	/// </summary>
    /// <param name="wnd">A parent window. Should be null for now.</param>
	TATSplashScreen(wxWindow *wnd);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~TATSplashScreen();


	// METHODS
	// ---------------
public:


    // EVENT HANDLERS
	// ---------------
public:

    /// <summary>
	/// Event handler called when the window is to be closed.
	/// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnFrameClose( wxCloseEvent& event );

    /// <summary>
	/// Event handler called when the timer activates.
	/// </summary>
    /// <param name="event">The event argument.</param>
    virtual void OnTimerTick( wxTimerEvent& event );


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
	/// A timer object to be used for closing the window after some time.
	/// </summary>
    wxTimer m_timer;

};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATSPLASHSCREEN__
