// [TERMS&CONDITIONS]

#ifndef __TATSPLASHSCREEN__
#define __TATSPLASHSCREEN__

#include "SplashScreen\SplashScreen.h"


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


	// PROPERTIES
	// ---------------
public:


	// ATTRIBUTES
	// ---------------
protected:


};

} //namespace UI
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATSPLASHSCREEN__
