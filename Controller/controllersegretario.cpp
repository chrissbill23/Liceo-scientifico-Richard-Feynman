#include "controllersegretario.h"
#include "../View/impiegato/segr/homepagesegretari.h"
#include "../Modello/segretario.h"
#include "../View/stackfinestre.h"

ControllerSegretario::ControllerSegretario(loginController *p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0)
{}


bool ControllerSegretario::inizializzaUtente(const QString &u)
{
    utenteConnesso = new Segretario(u.toStdString());
    if(utenteConnesso->esiste()){
       setUtente(utenteConnesso);
        utenteConnesso->InizializzaDatiPersonali();
        return true;
    }
    delete utenteConnesso;
    return false;
}

bool ControllerSegretario::CheckPassword(const QString &p) const
{
    return utenteConnesso && utenteConnesso->VerificaPassword(p.toStdString());
}


void ControllerSegretario::HomePage()
{
    StackFinestre*Stack = giveStack();
    if(Stack){
    int index=  Stack->addWidget(new HomePageSegr(this));
    Stack->setCurrentIndex(index);
    Stack->show();
    }
}

QString ControllerSegretario::getNewMatricola() const
{
    return QString::fromStdString(utenteConnesso->createMatricola());
}

QString ControllerSegretario::getNewStudPassword(const QString& n, const QString& c, int a) const
{
    return QString::fromStdString(utenteConnesso->CreateStudPassword(n.toStdString(),c.toStdString(),a));
}

bool ControllerSegretario::esisteNomeUtenteStud(const QString &nu) const
{
    return utenteConnesso->esisteNomeUtenteStud(nu.toStdString());
}

QString ControllerSegretario::insertNewStudMatricola(const QString& matri, const QString& nu) const
{
    return QString::fromStdString(utenteConnesso->insertNewStudMatricola(matri.toStdString(),nu.toStdString()));
}

QString ControllerSegretario::ModificaStudCognome(const QString& m, const QString& c) const
{
    return QString::fromStdString(utenteConnesso->EditStudCognome(m.toStdString(),c.toStdString()));
}

QString ControllerSegretario::ModificaStudNome(const QString &matricola, const QString &nome) const
{
    return QString::fromStdString(utenteConnesso->EditStudNome(matricola.toStdString(), nome.toStdString()));
}

QString ControllerSegretario::ModificaStudDataNascita(const QString& matricola, int g, int m, int a) const
{
    return QString::fromStdString(utenteConnesso->EditStudDataNascita(matricola.toStdString(), g, m, a));
}

QString ControllerSegretario::ModificaStudLuogoNascita(const QString &m, const QString &l) const
{
    return QString::fromStdString(utenteConnesso->EditStudLuogoNascita(m.toStdString(),l.toStdString()));
}

QString ControllerSegretario::ModificaStudClasse(const QString& matr, const QString& nclss) const
{
    return QString::fromStdString(utenteConnesso->EditStudClasse(matr.toStdString(), nclss.toStdString()));
}

QString ControllerSegretario::SetStudUserPassword(const QString& matricola, const QString& pw) const
{
    return QString::fromStdString(utenteConnesso->setStudUserPassword(matricola.toStdString(), pw.toStdString()));
}

QString ControllerSegretario::InsertNewStud(const QString &matricola, const QString &nu, const QString &pw, const QString &cognome, const QString &nome, const QString &classe, const QString &luogo, int g, int m, int a)
{
    return QString::fromStdString(utenteConnesso->InsertNewStud(matricola.toStdString(), nu.toStdString(), pw.toStdString(),
                                                                cognome.toStdString(), nome.toStdString(), classe.toStdString(),
                                                                luogo.toStdString(),g,m,a));
}

vector<string> ControllerSegretario::searchForStudent(const QString &keyword) const
{
    return utenteConnesso->searchForStudent(keyword.toStdString());
}

bool ControllerSegretario::removeStudente(const QString &matricola)
{
    return utenteConnesso->removeStudente(matricola.toStdString());
}

QString ControllerSegretario::getNewStudNomeUtente(const QString& n, const QString& c) const
{
    return QString::fromStdString(utenteConnesso->CreateStudNomeUtenteFromNomeCognome(n.toStdString(),c.toStdString()));
}
