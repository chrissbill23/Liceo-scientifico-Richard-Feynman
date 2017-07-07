#ifndef CONTROLLERSEGRETARIO_H
#define CONTROLLERSEGRETARIO_H

#include "controllerimpiegato.h"

class Segretario;
class ControllerSegretario: public ControllerImpiegato{
private:
Segretario* utenteConnesso;
public:
    ControllerSegretario(loginController *p1, StackFinestre *p2=0);
    bool inizializzaUtente(const QString &u);
    bool CheckPassword(const QString& p) const;
    void HomePage();
    QString getNewMatricola()const;
    QString getNewStudNomeUtente(const QString &n, const QString &c)const;
    QString getNewStudPassword(const QString &n, const QString &c, int a)const;
    bool esisteNomeUtenteStud(const QString &nu)const;
    QString ModificaStudCognome(const QString &m, const QString &c)const;
    QString ModificaStudNome(const QString& matricola, const QString& nome)const;
    QString ModificaStudDataNascita(const QString &matricola, int g, int m, int a)const;
    QString ModificaStudLuogoNascita(const QString& m, const QString& l)const;
    QString ModificaStudClasse(const QString &matr, const QString &nclss)const;
    QString SetStudUserPassword(const QString &matricola, const QString &pw) const;
    QString InsertNewStud(const QString& matricola, const QString&nu, const QString&pw, const QString& cognome,
                                 const QString& nome, const QString&classe, const QString&luogo, int g, int m, int a);
    vector<string> searchForStudent(const QString & keyword)const;
    bool removeStudente(const QString & matricola);
};

#endif // CONTROLLERSEGRETARIO_H
