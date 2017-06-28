#include "controlleradminsistema.h"
#include "../Modello/adminsistema.h"
#include "../View/admin/adminsist/homepageadminsist.h"
#include "../View/admin/adminsist/gestgruppi.h"
#include "../View/stackfinestre.h"

ControllerAdminSistema::ControllerAdminSistema(loginController *p1, StackFinestre *p2):Controller(p1,p2){}


bool ControllerAdminSistema::inizializzaUtente(const QString& u)
{
    utenteConnesso = new AdminSistema(u.toStdString());
    if(utenteConnesso->esiste()){
    setUtente(utenteConnesso);
    setGruppoUser(utenteConnesso);
    return true;
    }
    delete utenteConnesso;
    utenteConnesso = 0;
    return false;
}

void ControllerAdminSistema::HomePageGroup(const QString &nomeGruppo)
{
    ShowNewWindow(new GestGruppi(this,nomeGruppo));
}

void ControllerAdminSistema::HomePage()
{
    StackFinestre*Stack = giveStack();
    if(Stack){
    int index =  Stack->addWidget(new HomePageAdminSist(this));
    Stack->setCurrentIndex(index);
    Stack->show();
    }
}

QString ControllerAdminSistema::addPreside(const QString &nomeUtente, const QString &pass, const QString &Cognome, const QString &Nome, const QString &dataFineCarriera) const
{
    return QString::fromStdString(utenteConnesso->addPreside(nomeUtente.toStdString(),
                                                  pass.toStdString(),Cognome.toStdString(),
                                                             Nome.toStdString(),dataFineCarriera.toStdString()));
}

bool ControllerAdminSistema::removePreside()
{
    return utenteConnesso->removePreside();
}

bool ControllerAdminSistema::isAdmin() const
{
    return true;
}

QString ControllerAdminSistema::addGroupCathegory(const QString &name) const
{
    return QString::fromStdString(utenteConnesso->addGroupCathegory(name.toStdString()));
}

QString ControllerAdminSistema::removeGroupCathegory(const QString &name) const
{
    return QString::fromStdString(utenteConnesso->removeGroupCathegory(name.toStdString()));
}

QString ControllerAdminSistema::addNewGroup(const QString &name, const QString &titAndDescr, const QString &categoria) const
{
    return QString::fromStdString(utenteConnesso->addNewGroup(name.toStdString(), titAndDescr.toStdString(), categoria.toStdString()));
}

bool ControllerAdminSistema::editGroup(const QString &oldName, const QString &name, const QString &titAndDescr, const QString &categoria) const
{
    return utenteConnesso->editGroup(oldName.toStdString(), name.toStdString(), titAndDescr.toStdString(), categoria.toStdString());
}

QString ControllerAdminSistema::removeGroup(const QString &name) const
{
    return QString::fromStdString(utenteConnesso->removeGroup(name.toStdString()));
}
