#include "controlleradmin.h"
#include"loginController.h"
#include "../Modello/admin.h"
#include <QString>

ControllerAdmin::ControllerAdmin(loginController *p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0){}


bool ControllerAdmin::CheckPassword(const QString &p) const
{
    return utenteConnesso != NULL && utenteConnesso->VerificaPassword(p.toStdString());
}

list<string> ControllerAdmin::CampiDatiProfile() const
{
    list<string> l;
    l.push_back("Nome utente");
    return l;
}

list<string> ControllerAdmin::DaiValoreCampiDatiProfile() const
{
    return utenteConnesso->DaiDatiPersonali();
}

void ControllerAdmin::setUtente(Admin * u)
{
    utenteConnesso = u;
    Controller::setUtente(u);
}


