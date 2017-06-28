#ifndef COMPITIUSER_H
#define COMPITIUSER_H

#include "Utente.h"

class compitiUser : virtual public Utente
{
public:
    string getPdfCompitoPath(const string&) const;
    virtual vector<string> codiciCompiti()const;
    void SortcodiciCompitibyMateria(vector<string> &, const string&)const;
    void SortcodiciCompitibyClasse(vector<string> &, const string&)const;
    virtual vector<string> giveCompitiDates()const;
    virtual vector<string> giveCompitiTitle()const;
    list<string> classiCompito(const string &codice)const;
    string getCompitoFormato(const string&)const;
    string getCompitoTitolo(const string&)const;
    string getCompitoDescrizione(const string&)const;
    string getCompitoMateria(const string&)const;
    string getCompitoClasse(const string&)const;
    string getCompitoAutore(const string&)const;
    string giveCompitoXml(const string & codice)const;
    bool salvaRispCompito(string risposte, const string &codice)const;
    int totRispCompito(const string& codice)const;
    string getNomeRispCompito(const string& codice, int risposta);
    string getCognomeRispCompito(const string& codice, int risposta);
    string getPathRispCompito(const string& codice, int risposta);
    virtual bool commentaRispCompito(const string& codice, int risposta, const string &commento) const;
    bool HasRispCompitoCom(const string& codice, int risposta) const;
    bool eliminaCompito(const string& codice) const;
    bool hasAnsweredCompito(const string& )const;
    int MyAnswrCompito(const string& codice)const;
    string getRispCompComment(const string& codice, int risp)const;

};

#endif // COMPITIUSER_H
