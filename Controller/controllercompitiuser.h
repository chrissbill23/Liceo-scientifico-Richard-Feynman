#ifndef CONTROLLERCOMPITIUSER_H
#define CONTROLLERCOMPITIUSER_H

#include "Controller.h"

class compitiUser;
class ControllerCompitiUser : virtual public Controller
{
private:
    compitiUser* utenteConnesso;
public:
    ControllerCompitiUser(compitiUser* u = 0);
    void setUtenteConnesso(compitiUser*);
    QString getPdfCompitoPath(const QString&) const;
    vector<string> codiciCompiti()const;
    vector<string> giveCompitiTitle()const;
    QString getCompitoFormato(const QString&)const;
    QString getCompitoTitolo(const QString&)const;
    QString getCompitoDescrizione(const QString&)const;
    QString getCompitoMateria(const QString&)const;
    QString getCompitoClasse(const QString&)const;
    QString getCompitoAutore(const QString&)const;
    list<string> classiCompito(const QString&codice)const;
    QString giveCompitoXml(const QString& codice)const;
    bool salvaRispCompito(QString risposte, const QString&codice)const;
    int totRispCompito(const QString& codice)const;
    void SortcodiciCompitibyMateria(vector<string> &, const QString&)const;
    void SortcodiciCompitibyClasse(vector<string> &, const QString&)const;
    bool hasAnsweredCompito(const QString& )const;
    bool commentaRispCompito(const QString& codice, int risposta, const QString&commento) const;
    bool HasRispCompitoCom(const QString& codice, int risposta) const;
    int MyAnswrCompito(const QString& codice)const;
    QString getNomeRispCompito(const QString& codice, int risposta);
    QString getCognomeRispCompito(const QString& codice, int risposta);
    QString getPathRispCompito(const QString& codice, int risposta);
    vector<string> giveCompitiDates()const;
    bool eliminaCompito(const QString& codice) const;
    QString getRispCompComment(const QString& codice, int risp)const;
};

#endif // CONTROLLERCOMPITIUSER_H
