#ifndef CONTROLLERGRUPPOUSER_H
#define CONTROLLERGRUPPOUSER_H

#include "Controller.h"

class GruppoUser;
class ControllerGruppoUser : virtual public Controller
{
private:
    GruppoUser* utenteConnesso;
public:
    ControllerGruppoUser(GruppoUser* utente = 0);
    virtual void HomePageGroup(const QString& nomeGruppo) = 0;
    void setGruppoUser(GruppoUser* utente);
    list<string> MyGroupsName();
    list<string> esisteGruppo(const QString& name)const;
    list<string> daiMembriGroup(const QString& groupName)const;
    list<string> GroupsCathegory()const;
    list<string> GiveGroupsInCathegory(const QString& cathName)const;
    bool isIscrittoInGroup(const QString&nameGroup)const;
    bool IscrivimiAGroup(const QString& groupName);
    bool ToglimiDaGroup(const QString& group);
    virtual bool isAdmin()const;
    QString daiGroupCateg(const QString& groupName)const;
    QString daiGroupDescr(const QString& groupName)const;
    vector<string> daiInfoPost(const QString& GroupName, unsigned int i)const;
    QString daiPostData(const QString& nome,unsigned int i)const;
    QString daiPostTitolo(const QString& groupName, unsigned int i)const;
    QString daiPostAutore(const QString& nome,unsigned int i)const;
    QString daiTestoPostGroup(const QString&nome, unsigned int i)const;
    int totPostGroup(const QString& name)const;
    int totRisposteAPost(const QString& nomegruppo, unsigned int i) const;
    list<string> daiRispostaSuPost(const QString&gruppo, unsigned int i, unsigned int j) const;
    vector<int> MyPost(const QString& groupName)const;
    vector<int> PostIAnswered(const QString& groupName)const;
    vector<int> SearchPost(const QString& groupName, const QString& keyword)const;
    QString addPost(const QString& groupName, const QString&data, const QString& titolo, const QString& testo);
    QString addRispostaToPost(unsigned int i, const QString& groupName, const QString&data, const QString&testo);
    bool removePost(const QString& groupName, unsigned int i);
    QString getGroupMemberFotoProfile(const QString&nu) const;
    QString daiDataRisposta(const QString& groupName,unsigned int i, unsigned int j)const;
    QString daiAutoreRisposta(const QString& groupName,unsigned int i, unsigned int j)const;
    QString daiTestoRisposta(const QString& groupName, unsigned int i, unsigned int j)const;
    filexml giveSchedaGruppo(const QString& groupName)const;
};

#endif // CONTROLLERGRUPPOUSER_H
