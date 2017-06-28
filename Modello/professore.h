#ifndef PROFESSORE_H
#define PROFESSORE_H

#include "impiegato.h"
#include "compitiuser.h"
class Professore : public Impiegato, public compitiUser{
private:
    static string ProfFolder;
    list<string> materie;
    vector<string> classi;
public:
    Professore(string NomeUtente);
    Professore* clone() const;
    bool esiste() const;
    bool VerificaPassword(const string& p) const;
    void InizializzaDatiPersonali(); 
    bool CambiaFotoProfilo(const string &path) const;
    bool CambiaPassword(const string &newPass) const;
    string createNewCompitoXml(const string & data, const string &titolo, const string& descr,
                             const string& materia, const string& classe) const;
    string aggiungiDomandaARispMult(const string& path, const string& domanda,
                                  const list<string> & risposte, const list<bool> & corrette );
    string aggiungiDomandaAperta(const string& path, const string& domanda);
    bool loadCompitoPdf(const string& filePath, const string &data, const string & titolo, const string& descr,
                        const string& materia, const string& classe) const;
    list<string> daiMaterieInsegnate()const;
    vector<string> daiClassi()const;
    vector<string> codiciCompiti()const;
    vector<string> giveCompitiTitle()const;
    vector<string> giveCompitiDates()const;
    bool commentaRispCompito(const string &codice, int risposta, const string &commento) const;
    bool cancellaCompito(const string& codice)const;
    string aggiungiClasseACompito(const string& codice, const string& classe)const;
};
#endif // PROFESSORE_H
