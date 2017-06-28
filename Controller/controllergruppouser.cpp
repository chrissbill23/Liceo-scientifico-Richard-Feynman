#include "controllergruppouser.h"
#include "../Modello/gruppouser.h"
#include <QString>

ControllerGruppoUser::ControllerGruppoUser(GruppoUser *utente) : utenteConnesso(utente)
{

}

void ControllerGruppoUser::setGruppoUser(GruppoUser *utente)
{
    utenteConnesso =  utente;
}

list<string> ControllerGruppoUser::MyGroupsName()
{
    return utenteConnesso->Gruppi();
}

list<string> ControllerGruppoUser::esisteGruppo(const QString &name) const
{
    return utenteConnesso->esisteGruppo(name.toStdString());
}

list<string> ControllerGruppoUser::daiMembriGroup(const QString &groupName) const
{
    return utenteConnesso->GroupMembers(groupName.toStdString());
}

list<string> ControllerGruppoUser::GroupsCathegory() const
{
     return utenteConnesso->CategorieGruppo();
}

list<string> ControllerGruppoUser::GiveGroupsInCathegory(const QString &cathName) const
{
    return utenteConnesso->GroupsInCath(cathName.toStdString());
}

bool ControllerGruppoUser::isIscrittoInGroup(const QString &nameGroup) const
{
    return utenteConnesso->isIscrittoToGroup(nameGroup.toStdString());
}

bool ControllerGruppoUser::IscrivimiAGroup(const QString &groupName)
{
    if(utenteConnesso->IscriviMiAGroup(groupName.toStdString())){
        ReloadAllWindows();
        return true;
    }
    return false;
}

bool ControllerGruppoUser::ToglimiDaGroup(const QString &group)
{
    if(utenteConnesso->removeMeFromgroup(group.toStdString())){
        ReloadAllWindows();
        return true;
       }
    return false;
}

bool ControllerGruppoUser::isAdmin() const
{
    return false;
}

QString ControllerGruppoUser::daiGroupCateg(const QString &groupName) const
{
    return QString::fromStdString(utenteConnesso->daiGroupCateg(groupName.toStdString()));
}

QString ControllerGruppoUser::daiGroupDescr(const QString &groupName) const
{
    return QString::fromStdString(utenteConnesso->daiGroupDescr(groupName.toStdString()));
}

vector<string> ControllerGruppoUser::daiInfoPost(const QString &GroupName, unsigned int i) const
{
    return utenteConnesso->daiInfoPostGroup(GroupName.toStdString(),i);
}

QString ControllerGruppoUser::daiPostData(const QString &nome, unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->daiPostData(nome.toStdString(), i));
}

QString ControllerGruppoUser::daiPostTitolo(const QString &groupName, unsigned int i) const
{
     return QString::fromStdString(utenteConnesso->daiPostTitolo(groupName.toStdString(), i));
}

QString ControllerGruppoUser::daiPostAutore(const QString &nome, unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->daiPostAutore(nome.toStdString(),i));
}

QString ControllerGruppoUser::daiTestoPostGroup(const QString &nome, unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->daiTestoPostGroup(nome.toStdString(), i));
}

int ControllerGruppoUser::totPostGroup(const QString &name) const
{
    return utenteConnesso->totPostGruppo(name.toStdString());
}

int ControllerGruppoUser::totRisposteAPost(const QString &nomegruppo, unsigned int i) const
{
    return utenteConnesso->totRisposteAPost(nomegruppo.toStdString(),i);
}

list<string> ControllerGruppoUser::daiRispostaSuPost(const QString &gruppo, unsigned int i, unsigned int j) const
{
    return utenteConnesso->daiRispostaSuPost(gruppo.toStdString(),i,j);
}

vector<int> ControllerGruppoUser::MyPost(const QString &groupName) const
{
    return utenteConnesso->MyPost(groupName.toStdString());
}

vector<int> ControllerGruppoUser::PostIAnswered(const QString &groupName) const
{
    return utenteConnesso->PostIAnswered(groupName.toStdString());
}

vector<int> ControllerGruppoUser::SearchPost(const QString &groupName, const QString &keyword) const
{
    return utenteConnesso->SearchPost(groupName.toStdString(),keyword.toStdString());
}

QString ControllerGruppoUser::addPost(const QString &groupName, const QString &data, const QString &titolo, const QString &testo)
{
    return QString::fromStdString(utenteConnesso->addPost(groupName.toStdString(), data.toStdString(), titolo.toStdString(),testo.toStdString()));
}

QString ControllerGruppoUser::addRispostaToPost(unsigned int i, const QString &groupName, const QString &data, const QString &testo)
{
    return QString::fromStdString(utenteConnesso->addRispostaToPost(i,groupName.toStdString(), data.toStdString(), testo.toStdString()));
}

bool ControllerGruppoUser::removePost(const QString &groupName, unsigned int i)
{
    return utenteConnesso->removePost(groupName.toStdString(), i);
}

QString ControllerGruppoUser::getGroupMemberFotoProfile(const QString &nu) const
{
    return QString::fromStdString(utenteConnesso->getGroupMemberFotoProfile(nu.toStdString()));
}

QString ControllerGruppoUser::daiDataRisposta(const QString &groupName, unsigned int i, unsigned int j) const
{
    return QString::fromStdString(utenteConnesso->daiDataRisposta(groupName.toStdString(),i,j));
}

QString ControllerGruppoUser::daiAutoreRisposta(const QString &groupName, unsigned int i, unsigned int j) const
{
    return QString::fromStdString(utenteConnesso->daiAutoreRisposta(groupName.toStdString(),i,j));
}

QString ControllerGruppoUser::daiTestoRisposta(const QString &groupName, unsigned int i, unsigned int j) const
{
    return QString::fromStdString(utenteConnesso->daiTestoRisposta(groupName.toStdString(),i,j));
}

filexml ControllerGruppoUser::giveSchedaGruppo(const QString &groupName) const
{
    return utenteConnesso->giveSchedaGruppo(groupName.toStdString());
}
