#ifndef CONTROLLERADMINSISTEMA_H
#define CONTROLLERADMINSISTEMA_H

#include "controlleradmin.h"
#include "controllergruppouser.h"

class AdminSistema;
class ControllerAdminSistema: public ControllerAdmin, public ControllerGruppoUser{
private:
    AdminSistema* utenteConnesso;
public:
    ControllerAdminSistema(loginController* p1, StackFinestre* p2=0);
    bool inizializzaUtente(const QString &u);
    void HomePageGroup(const QString& nomeGruppo);
    void HomePage();
    QString addPreside(const QString& nomeUtente, const QString& pass, const QString& Cognome, const QString& Nome,
                      const QString& dataFineCarriera)const;
    bool removePreside();
    virtual bool isAdmin()const;
    void InitialiseGruppi();
    QString addGroupCathegory(const QString& name)const;
    QString removeGroupCathegory(const QString& name)const;
    QString addNewGroup (const QString& name, const QString &titAndDescr, const QString& categoria)const;
    bool editGroup(const QString& oldName,const QString& name, const QString &titAndDescr, const QString& categoria )const;
    QString removeGroup(const QString& name)const;

};

#endif // CONTROLLERADMINSISTEMA_H
