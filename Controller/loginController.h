#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "Controller.h"

class login;

class loginController{
private:
    Controller * c;
    StackFinestre * firstpage;
public:
    loginController(Controller *con = 0, StackFinestre *h = 0);
    ~loginController();
    bool checkNomeUtente(const QString &u);
    bool passwordchecker(const QString& p) const;
    void comincia();
    void homepage();
    void signout();
    void closeAll();

};





#endif
