// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIApp.h"
#include "SplashScreen/TATSplashScreen.h"

using Kinesis::TestAutomationTool::UI::TATSplashScreen;

namespace Kinesis
{
namespace TestAutomationTool
{

IMPLEMENT_APP(TestAutomationToolUIApp);

bool TestAutomationToolUIApp::OnInit()
{

    TATSplashScreen* splashScreen = new TATSplashScreen(0L);
    splashScreen->Show();
    return true;
}

}//namespace TestAutomationTool
}//namespace Kinesis
