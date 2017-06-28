#ifndef STUDENTE_H
#define STUDENTE_H

#include "gruppouser.h"
#include "compitiuser.h"
class Studente: virtual public Utente, public GruppoUser, public compitiUser  {
private:
    string matricola;
    string classe;
    static string StudFolder;
public:
    Studente(string NomeUtente = "" );
    Studente* clone() const;
    bool esiste() const;
    void InizializzaDatiPersonali();
    bool VerificaPassword(const string& p) const;
    bool CambiaFotoProfilo(const string &path) const;
    bool CambiaPassword(const string &newPass) const;
    string getGroupMemberFotoProfile(const string &nu) const;
    list<string> DaiDatiPersonali() const;
    list<string> daiMaterieInsegnate()const;
    vector<string> giveCompitiTitle()const;
    vector<string> giveCompitiDates()const;
    vector<string> codiciCompiti()const;

};


#endif // STUDENTE_H
