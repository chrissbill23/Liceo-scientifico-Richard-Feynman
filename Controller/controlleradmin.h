#ifndef CONTROLLERADMIN_H
#define CONTROLLERADMIN_H

#include "Controller.h"
class loginController;
class Admin;
class ControllerAdmin: virtual public Controller
{
private:
    Admin* utenteConnesso;
public:
    ControllerAdmin(loginController* p1 = 0, StackFinestre* p2 = 0);
    bool CheckPassword(const QString& p) const;
    list<string>CampiDatiProfile() const;
    list<string>DaiValoreCampiDatiProfile() const;
    void setUtente(Admin*);
};

#endif // CONTROLLEADMIN_H
