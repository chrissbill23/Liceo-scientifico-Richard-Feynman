#ifndef CONTROLLERSTUD_H
#define CONTROLLERSTUD_H

#include "controllergruppouser.h"
#include "controllercompitiuser.h"

class loginController;
class Studente;
class ControllerStud: virtual public Controller, public ControllerGruppoUser , public ControllerCompitiUser{
private:
    Studente* utenteConnesso;
public:

    ControllerStud(loginController* p1, StackFinestre* p2 = 0);
    bool inizializzaUtente(const QString &u);
    bool CheckPassword(const QString& p) const;
    void HomePage();
    void HomePageGroup(const QString& nomeGruppo);
    list<string>CampiDatiProfile() const;
    list<string>daiNomiGrupi() const;

};

#endif // CONTROLLERSTUD_H
