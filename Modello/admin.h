#ifndef ADMIN_H
#define ADMIN_H
#include "Utente.h"

class Admin: virtual public Utente{
private:
    static string pathDB;
public:
    Admin(const string& nU = "");
    bool esiste() const;
    Utente *clone() const;
    bool VerificaPassword(const string& p) const;
    list<string> DaiDatiPersonali() const;
    bool CambiaFotoProfilo(const string &path) const;
    bool CambiaPassword(const string &newPass) const;

};



#endif // ADMIN_H
