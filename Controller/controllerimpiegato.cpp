#include "controllerimpiegato.h"
#include"loginController.h"
#include "../View/biblio/homebiblio.h"
#include "../Modello/impiegato.h"


ControllerImpiegato::ControllerImpiegato(loginController *p2, StackFinestre *p1):Controller(p2,p1), utenteConnesso(0){}


void ControllerImpiegato::setUtente(Impiegato *u)
{
    utenteConnesso=u;
    Controller::setUtente(u);
}

list<string> ControllerImpiegato::CampiDatiProfile() const
{
    list<string> l;
    l.push_back("Cognome");
    l.push_back("Nome");
    l.push_back("Nome utente");
    l.push_back("Mail scuola");
    l.push_back("Mansione attuale");
    return l;
}

int ControllerImpiegato::TotMessRic() const
{
    return utenteConnesso->TotMailRic();
}

int ControllerImpiegato::TotMessInv() const
{
    return utenteConnesso->TotMailInv();
}



int ControllerImpiegato::totContacts() const
{
    return utenteConnesso->TotContatti();
}

QString ControllerImpiegato::daiNomeContatto(unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->daiNomeContatto(i));
}

QString ControllerImpiegato::daiMailContatto(unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->daiMailContatto(i));
}

void ControllerImpiegato::TuttiGliStudenti(vector<string> &matricola, vector<string> &NomeUtente,
                                           vector<string> &Cognome, vector<string> &nome,
                                           vector<string> &classe) const
{
    return utenteConnesso->TuttiGliStudenti(matricola, NomeUtente, Cognome, nome, classe);
}

void ControllerImpiegato::schedaClasse(const QString &nomeclasse, filexml& file) const
{
     utenteConnesso->schedaClasse(nomeclasse.toStdString(),file);
}

void ControllerImpiegato::schedaPersonaleStud(const QString &matricola, filexml& file) const
{
    utenteConnesso->schedaPersonaleStud(matricola.toStdString(),file);
}
int ControllerImpiegato::totNuoviMess() const
{
    return utenteConnesso->totMessNuovi();
}

QString ControllerImpiegato::LeggidataMail(unsigned int indice, bool ricevuta, bool OnlyUnread) const
{
    return QString::fromStdString(utenteConnesso->LeggidataMail(indice, ricevuta, OnlyUnread));
}

QString ControllerImpiegato::LeggiMailSender(unsigned int indice,bool ricevuta, bool unread) const
{
    return QString::fromStdString(utenteConnesso->LeggiMailSender(indice,ricevuta, unread));
}

QString ControllerImpiegato::LeggiMailDest(unsigned int i) const
{
    return QString::fromStdString(utenteConnesso->LeggiMailDest(i));
}

QString ControllerImpiegato::LeggiMailOgge(unsigned int indice, bool ricevuta, bool unread) const
{
    return QString::fromStdString(utenteConnesso->LeggiMailOgge(indice, ricevuta,unread));
}

QString ControllerImpiegato::LeggiMailTesto(unsigned int indice, bool ricevuta, bool unread)
{
    return QString::fromStdString(utenteConnesso->LeggiMailTesto(indice, ricevuta,unread));
}

QString ControllerImpiegato::SendNewMessage(const QString& data, const QString& dest, const QString& ogg, const QString& testo)
{
    return QString::fromStdString(utenteConnesso->SendNewMessage(data.toStdString(), dest.toStdString(), ogg.toStdString(), testo.toStdString()));
}

bool ControllerImpiegato::eliminaMail(unsigned int i, bool ricevuta)
{
    return utenteConnesso->eliminaMail(i, ricevuta);
}

bool ControllerImpiegato::isMailRead(unsigned int indice) const
{
    return utenteConnesso->isMailRead(indice);
}

