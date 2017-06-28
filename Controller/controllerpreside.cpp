#include "controllerpreside.h"
#include "../View/impiegato/presid/homepagepreside.h"
#include "loginController.h"
#include "../Modello/presidente.h"
#include "../View/stackfinestre.h"

ControllerPreside::ControllerPreside(loginController* p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0)
{}

bool ControllerPreside::inizializzaUtente(const QString& u)
{
  utenteConnesso = new Presidente(u.toStdString());
  if(utenteConnesso->esiste()){
       setUtente(utenteConnesso);
      utenteConnesso->InizializzaDatiPersonali();
      return true;
  }
  delete utenteConnesso;
  utenteConnesso = 0;
  return false;
}

bool ControllerPreside::CheckPassword(const QString &p) const
{
    return utenteConnesso && utenteConnesso->VerificaPassword(p.toStdString());
}

void ControllerPreside::HomePage()
{
    StackFinestre*Stack = giveStack();
    if(Stack){
    int index =  Stack->addWidget(new HomePagePreside(this));
    Stack->setCurrentIndex(index);
    Stack->show();
    }
}
list<string> ControllerPreside::CampiDatiProfile() const
{
    list<string> l;
    l.push_back("Cognome");
    l.push_back("Nome");
    l.push_back("Nome utente");
    l.push_back("Mail scuola");
    l.push_back("Mansione attuale");
    l.push_back("Data fine carriera");
    return l;
}

list<string> ControllerPreside::DaiValoreCampiDatiProfile() const
{
    return utenteConnesso->DaiDatiPersonali();
}

vector<string> ControllerPreside::giveProfNU() const
{
    return utenteConnesso->giveProfNU();
}

vector<string> ControllerPreside::giveSegrNU() const
{
    return utenteConnesso->giveSegrNU();
}


QString ControllerPreside::aggiungiMateria(const QString &materia) const
{
    return QString::fromStdString(utenteConnesso->aggiungiMateria(materia.toStdString()));
}

QString ControllerPreside::RimuoviMateria(const QString &materia) const
{
    return QString::fromStdString(utenteConnesso->RimuoviMateria(materia.toStdString()));
}

QString ControllerPreside::generaMail(const QString &nome, const QString &Cognome) const
{
    return QString::fromStdString(utenteConnesso->generaMail(nome.toStdString(),Cognome.toStdString()));
}

QString ControllerPreside::generaNomeUtente(const QString &nome, const QString &cognome) const
{
    return QString::fromStdString(utenteConnesso->generaNomeUtente(nome.toStdString(),cognome.toStdString()));
}

QString ControllerPreside::generaPassword(const QString &nome, const QString &cognome) const
{
    return QString::fromStdString(utenteConnesso->generaPassword(nome.toStdString(),cognome.toStdString()));
}

bool ControllerPreside::AggiungiMailImpiegato(const QString &NomeUtente, const QString &nuovamail) const
{
    return utenteConnesso->AggiungiMailImpiegato(NomeUtente.toStdString(),nuovamail.toStdString());
}

bool ControllerPreside::esisteImpiegato(const QString &NomeUtente) const
{
    return utenteConnesso->esisteImpiegato(NomeUtente.toStdString());
}

QString ControllerPreside::aggiungiSegretario(const QString &NomeUtente, const QString &password, const QString &nome, const QString &cognome) const
{
    return QString::fromStdString(utenteConnesso->aggiungiSegretario(NomeUtente.toStdString(),password.toStdString(),nome.toStdString(),cognome.toStdString()));
}

QString ControllerPreside::aggiungiProfessore(const QString &NomeUtente,const QString &password, const QString &nome, const QString &cognome) const
{
    return QString::fromStdString(utenteConnesso->aggiungiProfessore(NomeUtente.toStdString(),password.toStdString(),nome.toStdString(),cognome.toStdString()));
}

QString ControllerPreside::aggiungiClasseEMateriaAProf(const QString &NomeUtente, const QString &classe, const QString &materia) const
{
    return QString::fromStdString(utenteConnesso->aggiungiClasseEMateriaAProf(NomeUtente.toStdString(),classe.toStdString(),materia.toStdString()));
}

QString ControllerPreside::rimuoviMateriaEClasseAProf(const QString &NomeUtente, const QString &classe, const QString &materia) const
{
    return QString::fromStdString(utenteConnesso->rimuoviMateriaEClasseAProf(NomeUtente.toStdString(),classe.toStdString(),materia.toStdString()));
}


QString ControllerPreside::rimuoviProf(const QString &NomeUtente) const
{
    return QString::fromStdString(utenteConnesso->rimuoviProf(NomeUtente.toStdString()));
}

bool ControllerPreside::rimuoviSegr(const QString &NomeUtente) const
{
    return utenteConnesso->rimuoviSegr(NomeUtente.toStdString());
}

QString ControllerPreside::aggiungiIndirizzoClassi(const QString &nome) const
{
    return QString::fromStdString(utenteConnesso->aggiungiIndirizzoClassi(nome.toStdString()));
}

QString ControllerPreside::rimuoviIndirizzoClassi(const QString &nome) const
{
    return QString::fromStdString(utenteConnesso->rimuoviIndirizzoClassi(nome.toStdString()));
}

QString ControllerPreside::aggiungiSessioniClassi(const QString &nome) const
{
    return QString::fromStdString(utenteConnesso->aggiungiSessioniClassi(nome.toStdString()));
}

QString ControllerPreside::rimuoviSessioniClassi(const QString &nome) const
{
    return QString::fromStdString(utenteConnesso->rimuoviSessioniClassi(nome.toStdString()));
}

QString ControllerPreside::aggiungiClasse(const QString &classe, const QString &sessione, const QString &indirizzo) const
{
    return QString::fromStdString(utenteConnesso->aggiungiClasse(classe.toStdString(),sessione.toStdString(),indirizzo.toStdString()));
}

QString ControllerPreside::rimuoviClasse(const QString &classe) const
{
    return QString::fromStdString(utenteConnesso->rimuoviClasse(classe.toStdString()));
}

filexml ControllerPreside::giveSchedaPersonaleProf(const QString &NomeUtente) const
{
    return utenteConnesso->giveSchedaPersonaleProf(NomeUtente.toStdString());
}

filexml ControllerPreside::giveSchedaPersonaleSegr(const QString &NomeUtente) const
{
    return utenteConnesso->giveSchedaPersonaleSegr(NomeUtente.toStdString());
}

QString ControllerPreside::daiCognomeProf(const QString &NomeUtente) const
{
    return QString::fromStdString(utenteConnesso->daiCognomeProf(NomeUtente.toStdString()));
}

QString ControllerPreside::daiNomeProf(const QString &NomeUtente) const
{
    return QString::fromStdString(utenteConnesso->daiNomeProf(NomeUtente.toStdString()));
}

QString ControllerPreside::daiCognomeSegr(const QString &NomeUtente) const
{
    return QString::fromStdString(utenteConnesso->daiCognomeSegr(NomeUtente.toStdString()));
}

QString ControllerPreside::daiNomeSegr(const QString &NomeUtente) const
{
    return QString::fromStdString(utenteConnesso->daiNomeSegr(NomeUtente.toStdString()));
}
