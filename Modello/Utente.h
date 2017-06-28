#pragma once
#ifndef UTENTE_H
#define UTENTE_H

#include <string>
#include <list>
#include <vector>
class filexml;
using std::list;
using std::vector;
using std::string;

class Utente {
private:
    string NomeUtente;
    string Nome;
    string Cognome; 
    string fotoID;
public:
    Utente(const string& s="");
    virtual ~Utente();
    string daiNomeUtente() const;
    string daiNome() const;
    string daiCognome() const;
    string daifoto()const;
    void InizializzaDatiPersonali(string nome, string cognome, string foto);
    virtual bool esiste() const=0;
    virtual Utente* clone() const =0;
    virtual bool VerificaPassword(const string& p) const = 0;
    virtual list<string> DaiDatiPersonali() const=0;
    virtual bool CambiaFotoProfilo(const string& path)const = 0;
    virtual bool CambiaPassword(const string& newPass)const = 0;
    virtual list<string> daiMaterieInsegnate()const;
    virtual vector<string> daiClassi()const;
    list<string> daiSessioniClassi()const;
    list<string> daiIndirizzoClassi()const;
    filexml giveSchedaClasse(const string& nome)const;
    string checkForbiddenCharacters(const string& s)const;
    bool isNumeric(const string& s)const;
    bool hasSpaceOrTab(const string &s) const;
    bool hasSpaceOrTabFirst(const string& s)const;
    bool hasSpaceOrTabLast(const string& s)const;
    bool HasNoChar(const string& s)const;

};





#endif
