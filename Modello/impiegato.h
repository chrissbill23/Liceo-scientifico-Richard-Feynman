#ifndef IMPIEGATO_H
#define IMPIEGATO_H
#include "Utente.h"
#include "email.h"
class Impiegato: virtual public Utente {
private:
    string mansione;
    email em;
public:
    Impiegato(string NomeUtente = "");
    void InizializzaDatiPersonali(string n, string c, string f, string m, string mel);
    list<string> DaiDatiPersonali()const;
    int totMessNuovi()const;
    string daiMansione() const;
    string daiMail()const;
    bool isMailRead(unsigned int indice)const;
    string LeggidataMail(unsigned int indice, bool ricevuta, bool unread=false) const;
    string LeggiMailSender(unsigned int indice, bool ricevuta, bool unread=false) const;
    string LeggiMailDest(unsigned int indice)const;
    string LeggiMailOgge(unsigned int indice, bool ricevuta, bool unread=false) const;
    string LeggiMailTesto(unsigned int indice, bool ricevuta, bool unread=false);
    string SendNewMessage(const string &data, const string & dest, const string &ogg, const string & testo);
    bool eliminaMail(unsigned int index, bool ricevuta);
    int TotMailRic()const;
    int TotMailInv()const;
    int TotContatti()const;
    string daiNomeContatto(unsigned int i)const;
    string daiMailContatto(unsigned int i)const;   
    void schedaClasse(const string& nomeclasse, filexml &file)const;
    void schedaPersonaleStud(const string& matricola,filexml & file)const;
    void TuttiGliStudenti(vector<string>& matricola,vector<string>& NomeUtente,
                          vector<string>& Cognome, vector<string>& nome, vector<string>& classe)const;
};

#endif // IMPIEGATO_H
