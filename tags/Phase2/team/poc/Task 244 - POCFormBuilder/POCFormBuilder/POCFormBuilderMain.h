/***************************************************************
 * Name:      POCFormBuilderMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2012-05-09
 * Copyright:  ()
 * License:
 **************************************************************/


 // Esto sería la clase derivada de la ventana principal. Es generada por el wizard inicial
 // al crear el proyecto de tipo FormWizard, y puede ser modificada.


#ifndef POCFORMBUILDERMAIN_H
#define POCFORMBUILDERMAIN_H



#include "POCFormBuilderApp.h"

#include "wx/msgdlg.h"
#include "GUIFrame.h"

class POCFormBuilderFrame: public GUIFrame
{
    public:
        POCFormBuilderFrame(wxFrame *frame);
        ~POCFormBuilderFrame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

        // Declaraciones de métodos de evento añadidas tras comprobar que FormBuilder añadió sus métodos virtuales a la clase padre.
        virtual void DialogOpen( wxCommandEvent& event );
        virtual void AppExit(wxCommandEvent& event);
};

#endif // POCFORMBUILDERMAIN_H
