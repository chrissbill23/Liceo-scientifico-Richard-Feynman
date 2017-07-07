#ifndef SEGRETARIO_H
#define SEGRETARIO_H

#include "impiegato.h"
class Segretario : public Impiegato{
private:
    static string SegrFolder;    
    string EditStudNomeUtente(const string& matricola, const string& nu) const;
    string checkInputFormAddStud(const string& matricola, const string &nu, const string &pw, const string& cognome,
                                 const string& nome, const string &classe, const string &luogo, int g, int m, int a);
    string insertNewStudMatricola(const string& matricola, const string &nu)const;
public:
    bool esiste() const;
    Segretario(string NomeUtente);
    Segretario* clone() const;
    bool VerificaPassword(const string& p) const;
    void InizializzaDatiPersonali();
    bool CambiaFotoProfilo(const string &path) const;
    bool CambiaPassword(const string &newPass) const;
    bool esisteMatricola(const string& matricola)const;
    string createMatricola()const;
    bool esisteNomeUtenteStud(const string& nu)const;
    string InsertNewStud(const string& matricola, const string &nu, const string &pw, const string& cognome,
                                 const string& nome, const string &classe, const string &luogo, int g, int m, int a);
    string EditStudCognome(const string& matricola, const string& cognome)const;
    string EditStudNome(const string& matricola, const string& nome)const;
    string EditStudDataNascita(const string& matricola, int g, int m, int a)const;
    string EditStudLuogoNascita(const string& matricola, const string& luogo)const;
    string EditStudClasse(const string& matricola, const string& nuovaclasse)const;
    string setStudUserPassword(const string& matricola, const string& pw) const;
    string CreateStudNomeUtenteFromNomeCognome(const string &nome, const string &cognome)const;
    string CreateStudPassword(const string& nome,const string& cognome, int anno)const;
    vector<string> searchForStudent(const string& keyword)const;
    bool removeStudente(const string& matricola);

};
#endif // SEGRETARIO_H
