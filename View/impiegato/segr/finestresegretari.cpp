#include "finestresegretari.h"
#include "editremovestud.h"
#include "formaddstudent.h"
#include "formeditstudinfo.h"
#include <QMessageBox>



FinestreSegretari::FinestreSegretari(ControllerSegretario *p, QWidget *parent): FinestreImpiegato(p,parent),ctrl(p){

    setStyleSheet("background-color: #29abe2;");
}

ControllerSegretario *FinestreSegretari::getController() const
{
    return ctrl;
}

void FinestreSegretari::aggiungiStud()
{
    FormAddStudent temp(ctrl);

    temp.setFixedSize(800,740);
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
    FormEditStudInfo temp(ctrl,matricola,this);
    temp.setFixedSize(700,600);
    temp.exec();
    reloadWindow();
}

void FinestreSegretari::rimuoviStudente(const QString &matricola)
{
    if(ctrl->removeStudente(matricola)){
        QMessageBox::information(0,"","Alunno rimosso!");
        reloadWindow();
    }
    else
        QMessageBox::information(0,"Errore", "E' avvenuto un errore");
}


