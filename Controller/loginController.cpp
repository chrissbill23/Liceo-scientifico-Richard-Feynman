#include"loginController.h"
#include "../View/login.h"
#include "controllerstud.h"
#include "controllersegretario.h"
#include "controllerprof.h"
#include "controllerpreside.h"
#include "controlleradminsistema.h"
#include "controlleradminbiblio.h"
#include "../View/stackfinestre.h"

bool loginController::checkNomeUtente(const QString& u)
{
   Controller* c1 = new ControllerStud(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
        }
    delete c1;
    c1 = new ControllerProf(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
        }
    delete c1;
    c1 = new ControllerSegretario(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
       }
    delete c1;
    c1 = new ControllerPreside(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
        }
    delete c1;
    c1 = new ControllerAdminBiblio(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
        }
    delete c1;
    c1 = new ControllerAdminSistema(this);
    if(c1->inizializzaUtente(u))
       {
        c = c1;
        c->setWidgets(firstpage);
        return true;
        }
    return false;
}

bool loginController::passwordchecker(const QString& p) const
{
    return c && c->CheckPassword(p);
}

void loginController::comincia()
{
    firstpage->setCurrentIndex(0);
    firstpage->showMaximized();
}

void loginController::homepage()
{
    c->HomePage();
}

void loginController::signout()
{

    firstpage->reset();
    delete c;
    c = 0;
    firstpage->insertWidget(0, new login(this));
    firstpage->setCurrentIndex(0);
    firstpage->showMaximized();



}

void loginController::closeAll()
{
    if(firstpage){
        delete firstpage;
        firstpage = 0;
    }
    if(c){
        delete c;
        c = 0;
    }
}



loginController::loginController(Controller* con, StackFinestre *h):c(con), firstpage(h)
{
    if(!firstpage){
    firstpage=new StackFinestre(this);
    firstpage->insertWidget(0, new login(this));
    }
}

loginController::~loginController()
{
    if(firstpage)
        delete firstpage;
    if(c)
        delete c;
}
