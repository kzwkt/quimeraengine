// [TERMS&CONDITIONS]

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "TestAutomationToolUIMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}



TestAutomationToolUIDialog::TestAutomationToolUIDialog(wxDialog *dlg)
    : MainDialog(dlg)
{
}

TestAutomationToolUIDialog::~TestAutomationToolUIDialog()
{
}

void TestAutomationToolUIDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void TestAutomationToolUIDialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

