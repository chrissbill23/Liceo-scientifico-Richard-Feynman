#include "finestreprof.h"
#include "../../popupdialog.h"
#include "viewcompitiprof.h"
#include "createcompito.h"
#include <QLabel>

FinestreProf::FinestreProf(ControllerProf *p):FinestreImpiegato(p), ctrl(p){

    setStyleSheet(" background-color: #29abe2");
}

ControllerProf *FinestreProf::getController() const
{
    return ctrl;
}

void FinestreProf::CreateNewCompito()
{
    CreateCompito n(ctrl);
    n.exec();
}

void FinestreProf::vediCompiti() const
{
    ctrl->ShowNewWindow(new ViewCompitiProf(ctrl));
}

void FinestreProf::cancellaCompito(const QString &codice) const
{
    ctrl->cancellaCompito(codice);
}
