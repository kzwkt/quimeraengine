// [TERMS&CONDITIONS]

#include "SplashScreen/TATSplashScreen.h"

#include "../resources/embedded/resources.h"

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

const int TATSplashScreen::VISIBILITY_INTERVAL = 1000;

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATSplashScreen::TATSplashScreen(wxWindow *wnd) : SplashScreenBase(wnd)
{
    this->SetIcon(wxIcon(TAT_ICON_APP));
    m_timer.SetOwner(this);
    this->Connect(wxEVT_TIMER, wxTimerEventHandler(TATSplashScreen::OnTimerTick));
    m_timer.Start(VISIBILITY_INTERVAL, true);
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATSplashScreen::~TATSplashScreen()
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



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		EVENT HANDLERS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void TATSplashScreen::OnFrameClose( wxCloseEvent& event )
{
    this->Destroy();
}

void TATSplashScreen::OnTimerTick( wxTimerEvent& event )
{
    this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(TATSplashScreen::OnTimerTick));
    this->Close(true);
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
