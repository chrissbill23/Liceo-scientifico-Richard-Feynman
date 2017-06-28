#ifndef CONTROLLERIMPIEGATO_H
#define CONTROLLERIMPIEGATO_H

#include "Controller.h"
class loginController;
class Impiegato;

class ControllerImpiegato: virtual public Controller{
private:
    Impiegato* utenteConnesso;
    StackFinestre* Stack;
public:
    ControllerImpiegato(loginController* p2 = 0, StackFinestre* p1 = 0);
    void setWidgets(StackFinestre*p);
    void setUtente(Impiegato* u);
    list<string> CampiDatiProfile() const;
    int totNuoviMess()const;
    QString LeggidataMail(unsigned int indice, bool ricevuta, bool OnlyUnread = false) const;
    QString LeggiMailSender(unsigned int indice, bool ricevuta, bool unread = false) const;
    QString LeggiMailDest(unsigned int i)const;
    QString LeggiMailOgge(unsigned int indice, bool ricevuta, bool unread = false) const;
    QString LeggiMailTesto(unsigned int indice, bool ricevuta, bool unread = false);
    QString SendNewMessage(const QString& data, const QString& dest, const QString& ogg, const QString& testo);
    bool eliminaMail(unsigned int i, bool ricevuta = true);
    bool isMailRead(unsigned int indice)const;
    int TotMessRic()const;
    int TotMessInv()const;
    int totContacts()const;
    QString daiNomeContatto(unsigned int i)const;
    QString daiMailContatto(unsigned int i)const;
    void TuttiGliStudenti(vector<string>& matricola,vector<string>& NomeUtente,
                          vector<string>& Cognome, vector<string>& nome, vector<string>& classe)const;
    void schedaClasse(const QString& nomeclasse,filexml& file)const;
    void schedaPersonaleStud(const QString& matricola, filexml &file)const;
};

#endif // CONTROLLERIMPIEGATO_H
