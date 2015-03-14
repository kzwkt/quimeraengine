#include "DialogoDerivada.h"

// Implementación de la clase derivada de diálogo

DialogoDerivada::DialogoDerivada(wxFrame *parent) : MyDialog1(parent)
{

}

DialogoDerivada::~DialogoDerivada()
{

}


// Método de evento añadido
void DialogoDerivada::DialogClose(wxCommandEvent& event)
{
    this->Close();
}
