#ifndef ADMINSISTEMA_H
#define ADMINSISTEMA_H

#include "admin.h"
#include "gruppouser.h"
class AdminSistema : public Admin, public GruppoUser
{
private:
    static string pathDB;
    string checkInputaddPreside(const string &nomeUtente, const string &pass, const string &Cognome,
                                const string &Nome, const string &dataFineCarriera)const;
public:
    AdminSistema(const string &nU);
    bool VerificaPassword(const string& p) const;
    bool esiste() const;
    string addPreside(const string& nomeUtente, const string& pass, const string& Cognome, const string& Nome,
                      const string& dataFineCarriera)const;
    bool removePreside();
    void InitialiseGruppi();
    string addGroupCathegory(const string& name)const;
    string removeGroupCathegory(const string& name)const;
    string addNewGroup (const string& name, const string &Descr, const string& categoria)const;
    bool editGroup(const string &oldName, const string& name, const string &Descr, const string& categoria )const;
    string removeGroup(const string& name)const;
};

#endif // ADMINSISTEMA_H
