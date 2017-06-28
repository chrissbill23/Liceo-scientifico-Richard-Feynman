#ifndef GRUPPOUSER_H
#define GRUPPOUSER_H

#include "gruppo.h"
#include "Utente.h"
#include <map>

using std:: map;

class GruppoUser : virtual public Utente
{
private:
    map<string,Gruppo> ImieiGruppi;
public:
    void setGruppi(const map<string,Gruppo> group);
    list<string> CategorieGruppo()const;
    list<string> Gruppi();
    virtual void InitialiseGruppi();
    int totMygroups()const;
    list<string> GroupsInCath(const string& cathegory)const;
    list<string> esisteGruppo(const string& nome)const;
    list<string> GroupMembers(const string& nomeGroup)const;
    virtual string getGroupMemberFotoProfile(const string& nu = "")const;
    int totPostGruppo(const string& nome)const;
    int totRisposteAPost(const string &nomegruppo, unsigned int i)const;
    vector<string>daiInfoPostGroup(const string& nome,unsigned int i)const;
    string daiPostData(const string& nome,unsigned int i)const;
    string daiPostTitolo(const string& nome,unsigned int i)const;
    string daiPostAutore(const string& nome,unsigned int i)const;
    string daiTestoPostGroup(const string &nome, unsigned int i)const;
    list<string>daiRispostaSuPost(const string & gruppo, unsigned int i, unsigned int j)const;
    bool removeMeFromgroup(const string& group);
    bool isIscrittoToGroup(const string &) const;
    bool IscriviMiAGroup(const string &groupName);
    vector<int> MyPost(const string& groupName)const;
    vector<int> PostIAnswered(const string& groupName)const;
    vector<int> SearchPost(const string& groupName, const string& keyword)const;
    string daiGroupCateg(const string& groupName)const;
    string daiGroupDescr(const string& groupName)const;
    string daiDataRisposta(const string& groupName,unsigned int i, unsigned int j)const;
    string daiAutoreRisposta(const string& groupName,unsigned int i, unsigned int j)const;
    string daiTestoRisposta(const string& groupName, unsigned int i, unsigned int j)const;
    string addPost(const string& groupName, const string &data,
                 const string& titolo, const string& testo);
    string addRispostaToPost(unsigned int i, const string& groupName, const string &data, const string &testo);
    bool removePost(const string& groupName, unsigned int i);
    filexml giveSchedaGruppo(const string& groupName)const;
};

#endif // GRUPPOUSER_H
