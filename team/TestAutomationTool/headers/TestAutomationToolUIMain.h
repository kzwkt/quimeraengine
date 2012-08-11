// [TERMS&CONDITIONS]

#ifndef TESTAUTOMATIONTOOLUIMAIN_H
#define TESTAUTOMATIONTOOLUIMAIN_H

#include "TestAutomationToolUIApp.h"

#include "MainDialog.h"

class TestAutomationToolUIDialog : public MainDialog
{
    public:
        TestAutomationToolUIDialog(wxDialog *dlg);
        ~TestAutomationToolUIDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
};
#endif // TESTAUTOMATIONTOOLUIMAIN_H
