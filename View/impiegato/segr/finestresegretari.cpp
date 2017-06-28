#include "finestresegretari.h"
#include "editremovestud.h"
#include "formaddstudent.h"
#include "formeditstudinfo.h"
#include <QMessageBox>



FinestreSegretari::FinestreSegretari(ControllerSegretario *p, QWidget *parent): FinestreImpiegato(p,parent),ctrl(p){

    setStyleSheet(" background-color: #29abe2");
}

ControllerSegretario *FinestreSegretari::getController() const
{
    return ctrl;
}

void FinestreSegretari::aggiungiStud()
{
    FormAddStudent temp(ctrl);

    temp.setFixedSize(1000,700);
    temp.exec();
    reloadWindow();
}

void FinestreSegretari::ModificaStudenti() const
{
    ctrl->ShowNewWindow(new EditRemoveStud(ctrl));
}

void FinestreSegretari::CercaStud(const QString &key) const
{
    EditRemoveStud* temp = new EditRemoveStud(ctrl);
    temp->cercaStud(key);
    ctrl->ShowNewWindow(temp);
}

void FinestreSegretari::editStudInfo(const QString &matricola)
{
    FormEditStudInfo temp(ctrl,matricola);
    temp.setFixedSize(700,700);
    temp.exec();
    reloadWindow();
}

void FinestreSegretari::rimuoviStudente(const QString &matricola)
{
    if(ctrl->removeStudente(matricola)){
        QMessageBox::information(this,"","Alunno rimosso!");
        reloadWindow();
    }
    else
        QMessageBox::information(this,"Errore", "E' avvenuto un errore");
}


