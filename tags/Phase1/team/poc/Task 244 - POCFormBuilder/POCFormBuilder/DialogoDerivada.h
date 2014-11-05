
#ifndef DIALOGODERIVADA_H
#define DIALOGODERIVADA_H



#include "POCFormBuilderApp.h"

#include "wx/msgdlg.h"
#include "GUIFrame.h"


// Clase derivada del diálogo. Esta clase se ha añadido a mano, se podía haber generado con FormBuilder (Tools->Generate Inherit Class)

class DialogoDerivada: public MyDialog1
{
    public:
        DialogoDerivada(wxFrame *parent);
        ~DialogoDerivada();
    private:
        // Declaración de método de evento añadido
        virtual void DialogClose( wxCommandEvent& event );
};

#endif // DIALOGODERIVADA_H
