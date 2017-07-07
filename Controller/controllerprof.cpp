#include "controllerprof.h"
#include"loginController.h"
#include "../View/impiegato/prof/homepageprof.h"
#include "../Modello/professore.h"
#include "../View/stackfinestre.h"

ControllerProf::ControllerProf(loginController* p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0)
{}

bool ControllerProf::inizializzaUtente(const QString &u)
{
  utenteConnesso = new Professore(u.toStdString());
  if(utenteConnesso->esiste()){
       setUtente(utenteConnesso);
       setUtenteConnesso(utenteConnesso);
      utenteConnesso->InizializzaDatiPersonali();
      return true;
  }
  delete utenteConnesso;
  utenteConnesso = 0;
  return false;
}

bool ControllerProf::CheckPassword(const QString &p) const
{
    return utenteConnesso && utenteConnesso->VerificaPassword(p.toStdString());
}


void ControllerProf::HomePage()
{
    StackFinestre*Stack = giveStack();
    if(Stack){
    int index =  Stack->addWidget(new HomePageProf(this));
    Stack->setCurrentIndex(index);
    Stack->show();
    }
}

list<string> ControllerProf::tipiFileCompito() const
{
    list<string> l;

    l.push_back("xml");
    l.push_back("pdf");
    return l;
}

QString ControllerProf::createNewCompitoXml(const QString &data, const QString &titolo, const QString &descr,
                                           const QString &materia, const QString &classe, QString& error)
{
    string check = "";
    QString temp = QString::fromStdString(utenteConnesso->createNewCompitoXml(data.toStdString(),titolo.toStdString(),
                                                                      descr.toStdString(),materia.toStdString(),classe.toStdString(), check));
    error = QString::fromStdString(check);
    return temp;
}

QString ControllerProf::aggiungiDomandaARispMult(const QString&path, const QString&domanda, const list<string> &risposte, const list<bool> &corrette)
{
    return QString::fromStdString(utenteConnesso->aggiungiDomandaARispMult(path.toStdString(),domanda.toStdString(),risposte, corrette));
}

QString ControllerProf::aggiungiDomandaAperta(const QString&path, const QString&domanda)
{
    return QString::fromStdString(utenteConnesso->aggiungiDomandaAperta(path.toStdString(), domanda.toStdString()));
}

bool ControllerProf::loadCompitoPdf(const QString&filePath, const QString& data, const QString&titolo, const QString&descr, const QString&materia, const QString&classe) const
{
    return utenteConnesso->loadCompitoPdf(filePath.toStdString(),data.toStdString(),
                                         titolo.toStdString(),descr.toStdString(),materia.toStdString(),classe.toStdString());
}

bool ControllerProf::cancellaCompito(const QString&codice) const
{
    return utenteConnesso->cancellaCompito(codice.toStdString());
}

QString ControllerProf::aggiungiClasseACompito(const QString&codice, const QString&classe) const
{
    return QString::fromStdString(utenteConnesso->aggiungiClasseACompito(codice.toStdString(),classe.toStdString()));
}

