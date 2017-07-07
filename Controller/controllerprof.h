#ifndef CONTROLLERPROF_H
#define CONTROLLERPROF_H

#include "controllerimpiegato.h"
#include "controllercompitiuser.h"

class loginController;
class Professore;
class ControllerProf: public ControllerImpiegato, public ControllerCompitiUser{
private:
Professore* utenteConnesso;
public:
    ControllerProf(loginController *p1, StackFinestre *p2=0);
    bool inizializzaUtente(const QString &u);
    bool CheckPassword(const QString& p) const;
    void HomePage();
    list<string> tipiFileCompito()const;
    QString createNewCompitoXml(const QString&data, const QString& titolo, const QString& descr,
                             const QString& materia, const QString& classe, QString &error);
    QString aggiungiDomandaARispMult(const QString& path, const QString& domanda,
                                  const list<string> & risposte, const list<bool> & corrette );
    QString aggiungiDomandaAperta(const QString& path, const QString& domanda);
    bool loadCompitoPdf(const QString& filePath, const QString& data, const QString& titolo, const QString& descr,
                        const QString& materia, const QString& classe) const;
    bool cancellaCompito(const QString& codice)const;
    QString aggiungiClasseACompito(const QString& codice, const QString& classe)const;
};

#endif // CONTROLLERPROF_H
