#ifndef CONTROLLERPRESIDE_H
#define CONTROLLERPRESIDE_H

#include "controllerimpiegato.h"

class Presidente;
class ControllerPreside: public ControllerImpiegato{
private:
Presidente* utenteConnesso;
public:
    ControllerPreside(loginController *p1, StackFinestre *p2=0);
    bool inizializzaUtente(const QString &u);
    bool CheckPassword(const QString& p) const;
    void HomePage();
    list<string> CampiDatiProfile() const;
    list<string>DaiValoreCampiDatiProfile() const;
    vector<string> giveProfNU()const;
    vector<string> giveSegrNU()const;
    QString aggiungiMateria(const QString& materia)const;
    QString RimuoviMateria(const QString& materia)const;
    QString generaMail(const QString& nome, const QString& Cognome)const;
    QString generaNomeUtente(const QString& nome, const QString& cognome)const;
    QString generaPassword(const QString& nome, const QString& cognome)const;
    bool AggiungiMailImpiegato(const QString& NomeUtente, const QString &nuovamail)const;
    bool esisteImpiegato(const QString& NomeUtente) const;
    QString aggiungiSegretario(const QString& NomeUtente, const QString &password, const QString &nome, const QString &cognome)const;
    QString aggiungiProfessore(const QString& NomeUtente,const QString &password, const QString &nome, const QString &cognome)const;
    QString aggiungiClasseEMateriaAProf(const QString& NomeUtente, const QString &classe, const QString& materia)const;
    QString rimuoviMateriaEClasseAProf(const QString& NomeUtente, const QString &classe, const QString &materia )const;
    QString rimuoviProf(const QString& NomeUtente)const;
    bool rimuoviSegr(const QString &NomeUtente) const;
    QString aggiungiIndirizzoClassi(const QString &nome)const;
    QString rimuoviIndirizzoClassi(const QString &nome)const;
    QString aggiungiSessioniClassi(const QString &nome)const;
    QString rimuoviSessioniClassi(const QString &nome)const;
    QString aggiungiClasse(const QString& classe, const QString &sessione, const QString& indirizzo)const;
    QString rimuoviClasse(const QString& classe)const;
    filexml giveSchedaPersonaleProf(const QString& NomeUtente)const;
    filexml giveSchedaPersonaleSegr(const QString& NomeUtente)const;
    QString daiCognomeProf(const QString& NomeUtente)const;
    QString daiNomeProf(const QString& NomeUtente)const;
    QString daiCognomeSegr(const QString& NomeUtente)const;
    QString daiNomeSegr(const QString& NomeUtente)const;
};

#endif // CONTROLLERPRESIDE_H
