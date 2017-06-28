#ifndef PRESIDENTE_H
#define PRESIDENTE_H

#include "impiegato.h"

class Presidente: public Impiegato{
private:
    string finecarriera;
    static string PresFolder;
    bool aggiornaMailSegr(const string& NomeUtente, const string &nuovamail)const;
    bool aggiornaMailProf(const string& NomeUtente, const string &nuovamail)const;
    string rimuoviClasseAProf(const string& NomeUtente, const string &classe )const;
    string rimuoviMateriaAProf(const string& NomeUtente, const string &materia )const;
    string aggiungiClasseAProf(const string& NomeUtente, const string &classe )const;
    string aggiungiMaterieAProf(const string& NomeUtente, const string &materia )const;
    string checkInputformAddImpieg(const string& NomeUtente, const string &password, const string &nome, const string &cognome)const;
public:
    Presidente(string NomeUtente);
    Presidente* clone() const;
    bool esiste() const;
    bool VerificaPassword(const string& p) const;
    void InizializzaDatiPersonali();
    bool CambiaFotoProfilo(const string &path) const;
    bool CambiaPassword(const string &newPass) const;
    list<string> DaiDatiPersonali()const;
    string aggiungiMateria(const string& materia)const;
    string RimuoviMateria(const string& materia)const;
    string generaMail(const string& nome, const string& Cognome)const;
    string generaNomeUtente(const string& nome, const string& cognome)const;
    string generaPassword(const string& nome, const string& cognome)const;
    vector<string> giveProfNU()const;
    vector<string> giveSegrNU()const;
    bool AggiungiMailImpiegato(const string& NomeUtente, const string &nuovamail)const;
    bool esisteImpiegato(const string& NomeUtente) const;
    string aggiungiSegretario(const string& NomeUtente, const string &password, const string &nome, const string &cognome)const;
    string aggiungiProfessore(const string& NomeUtente, const string& password, const string &nome, const string &cognome)const;
    string aggiungiClasseEMateriaAProf(const string& NomeUtente, const string &classe, const string& materia)const;
    string rimuoviProf(const string& NomeUtente)const;
    string rimuoviMateriaEClasseAProf(const string& NomeUtente, const string& classe, const string& materia)const;
    bool rimuoviSegr(const string &NomeUtente) const;
    string aggiungiIndirizzoClassi(const string &nome)const;
    string rimuoviIndirizzoClassi(const string &nome)const;
    string aggiungiSessioniClassi(const string &nome)const;
    string rimuoviSessioniClassi(const string &nome)const;
    string aggiungiClasse(const string& classe, const string &sessione, const string& indirizzo)const;
    string rimuoviClasse(const string& classe)const;
    string daiCognomeProf(const string& NomeUtente)const;
    string daiNomeProf(const string& NomeUtente)const;
    string daiCognomeSegr(const string& NomeUtente)const;
    string daiNomeSegr(const string& NomeUtente)const;
    filexml giveSchedaPersonaleProf(const string& NomeUtente)const;
    filexml giveSchedaPersonaleSegr(const string& NomeUtente)const;
};

#endif // PRESIDENTE_H
