#include "finestreadminsist.h"
#include "formaddpreside.h"
#include <QMessageBox>


FinestreAdminSist::FinestreAdminSist(ControllerAdminSistema *ptr):finestreAdmin(ptr), ctrl(ptr){

    setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
}

ControllerAdminSistema *FinestreAdminSist::getController() const
{
    return ctrl;
}

void FinestreAdminSist::addPreside() const
{
    FormAddPreside temp(ctrl);
    temp.setFixedSize(600,600);
    temp.exec();
}

void FinestreAdminSist::removePreside() const
{
    if(QMessageBox::information(0,"ATTENZIONE!","Sei sicuro di voler rimuovere l'attuale presidente?",
                                QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes){
        if(ctrl->removePreside())
            QMessageBox::information(0, "", "Rimosso con successo");
        else QMessageBox::information(0, "ERRORE!", "E' avvenuto un errore con i file");
    }
}

void FinestreAdminSist::GestisciGruppi() const
{
    getController()->HomePageGroup("");
}
