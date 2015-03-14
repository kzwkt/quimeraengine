/***************************************************************
 * Name:      POCFormBuilderMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2012-05-09
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "POCFormBuilderMain.h"
#include "DialogoDerivada.h"

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


POCFormBuilderFrame::POCFormBuilderFrame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("Prueba de concepto de wxWidgets"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
}

POCFormBuilderFrame::~POCFormBuilderFrame()
{
}

void POCFormBuilderFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void POCFormBuilderFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void POCFormBuilderFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


// Implementación de los eventos que se han añadido

void POCFormBuilderFrame::DialogOpen(wxCommandEvent& event)
{
    DialogoDerivada* Dlg = new DialogoDerivada(this);
    Dlg->ShowModal();
}

void POCFormBuilderFrame::AppExit(wxCommandEvent& event)
{
    this->Close();
}
