// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIApp.h"
#include "SplashScreen/KSplashScreen.h"

using Kinesis::TestAutomationTool::UI::KSplashScreen;

namespace Kinesis
{
namespace TestAutomationTool
{

IMPLEMENT_APP(TestAutomationToolUIApp);

bool TestAutomationToolUIApp::OnInit()
{
    
    KSplashScreen* splashScreen = new KSplashScreen(0L);
    splashScreen->Show();
    return true;
}

}//namespace TestAutomationTool
}//namespace Kinesis
