// [TERMS&CONDITIONS]

#ifndef __KSPLASHSCREEN__
#define __KSPLASHSCREEN__

#include "SplashScreen.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace UI
{

/// <summary>
/// [DOC]
/// </summary>
class KSplashScreen : public SplashScreenBase
{
	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	KSplashScreen(wxWindow *wnd);


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~KSplashScreen();


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

#endif // __KSPLASHSCREEN__
