#include"controllerstud.h"
#include "../View/studenti/homepagestud.h"
#include "../View/biblio/homebiblio.h"
#include"loginController.h"
#include "../View/studenti/homegruppostud.h"
#include "../Modello/studente.h"
#include "../View/stackfinestre.h"


ControllerStud::ControllerStud(loginController* p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0){
}

bool ControllerStud::inizializzaUtente(const QString &u)
{
    utenteConnesso = new Studente(u.toStdString());

        if(utenteConnesso->esiste()){
            setUtente(utenteConnesso);
            setGruppoUser(utenteConnesso);
            setUtenteConnesso(utenteConnesso);
            utenteConnesso->InizializzaDatiPersonali();
            return true;
        }
        delete utenteConnesso;
        utenteConnesso = 0;
        return false;
}

bool ControllerStud::CheckPassword(const QString &p) const
{
    return utenteConnesso->VerificaPassword(p.toStdString());
}


void ControllerStud::HomePage()
{StackFinestre*Stack = giveStack();
    if(Stack){
    int index =  Stack->addWidget(new HomePageStud(this));
    Stack->setCurrentIndex(index);
    Stack->showMaximized();
    }

}

void ControllerStud::HomePageGroup(const QString &nomeGruppo)
{
    ShowNewWindow(new HomeGruppoStud(this, nomeGruppo));
}

list<string> ControllerStud::CampiDatiProfile() const
{
    list<string> l;
    l.push_back("Cognome");
    l.push_back("Nome");
    l.push_back("Matricola");
    l.push_back("Classe");
    return l;

}

list<string> ControllerStud::daiNomiGrupi() const
{
    return utenteConnesso->Gruppi();
}


