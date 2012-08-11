// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIApp.h"
#include "TestAutomationToolUIMain.h"

IMPLEMENT_APP(TestAutomationToolUIApp);

bool TestAutomationToolUIApp::OnInit()
{
    
    TestAutomationToolUIDialog* dlg = new TestAutomationToolUIDialog(0L);
    dlg->SetIcon(wxICON(aaaa)); // To Set App Icon
    dlg->Show();
    return true;
}
