#include "controllercompitiuser.h"
#include "../Modello/compitiuser.h"
#include <QString>

ControllerCompitiUser::ControllerCompitiUser(compitiUser *u):utenteConnesso(u){}

void ControllerCompitiUser::setUtenteConnesso(compitiUser *u)
{
    utenteConnesso = u;
}
QString ControllerCompitiUser::getPdfCompitoPath(const QString& codice) const
{
   return QString::fromStdString(utenteConnesso->getPdfCompitoPath(codice.toStdString()));
}

vector<string> ControllerCompitiUser::codiciCompiti() const
{
    return utenteConnesso->codiciCompiti();
}

vector<string> ControllerCompitiUser::giveCompitiTitle() const
{
    return utenteConnesso->giveCompitiTitle();
}

QString ControllerCompitiUser::getCompitoData(const QString &code) const
{
    return QString::fromStdString(utenteConnesso->getCompitoData(code.toStdString()));
}

QString ControllerCompitiUser::getCompitoFormato(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoFormato(codice.toStdString()));
}

QString ControllerCompitiUser::getCompitoTitolo(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoTitolo(codice.toStdString()));
}

QString ControllerCompitiUser::getCompitoDescrizione(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoDescrizione(codice.toStdString()));
}

QString ControllerCompitiUser::getCompitoMateria(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoMateria(codice.toStdString()));
}

QString ControllerCompitiUser::getCompitoClasse(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoClasse(codice.toStdString()));
}

QString ControllerCompitiUser::getCompitoAutore(const QString& codice) const
{
    return QString::fromStdString(utenteConnesso->getCompitoAutore(codice.toStdString()));
}

list<string> ControllerCompitiUser::classiCompito(const QString&codice) const
{
    return utenteConnesso->classiCompito(codice.toStdString());
}

QString ControllerCompitiUser::giveCompitoXml(const QString&codice) const
{
    return QString::fromStdString(utenteConnesso->giveCompitoXml(codice.toStdString()));
}
bool ControllerCompitiUser::salvaRispCompito(QString risposte, const QString&codice) const
{
    return utenteConnesso->salvaRispCompito(risposte.toStdString(),codice.toStdString());
}

int ControllerCompitiUser::totRispCompito(const QString&codice) const
{
    return utenteConnesso->totRispCompito(codice.toStdString());
}

void ControllerCompitiUser::SortcodiciCompitibyMateria(vector<string>& l,const QString& materia) const
{
    utenteConnesso->SortcodiciCompitibyMateria(l, materia.toStdString());
}

void ControllerCompitiUser::SortcodiciCompitibyClasse(vector<string> & l, const QString& classe) const
{
    utenteConnesso->SortcodiciCompitibyClasse(l,classe.toStdString());
}

bool ControllerCompitiUser::hasAnsweredCompito(const QString& codice) const
{
    return utenteConnesso->hasAnsweredCompito(codice.toStdString());
}

bool ControllerCompitiUser::commentaRispCompito(const QString&codice, int risposta, const QString&commento) const
{
    return utenteConnesso->commentaRispCompito(codice.toStdString(),risposta,commento.toStdString());
}

bool ControllerCompitiUser::HasRispCompitoCom(const QString&codice, int risposta) const
{
    return utenteConnesso->HasRispCompitoCom(codice.toStdString(), risposta);
}

int ControllerCompitiUser::MyAnswrCompito(const QString&codice) const
{
    return utenteConnesso->MyAnswrCompito(codice.toStdString());
}

QString ControllerCompitiUser::getNomeRispCompito(const QString&codice, int risposta)
{
    return QString::fromStdString(utenteConnesso->getNomeRispCompito(codice.toStdString(), risposta));
}

QString ControllerCompitiUser::getCognomeRispCompito(const QString&codice, int risposta)
{
    return QString::fromStdString(utenteConnesso->getCognomeRispCompito(codice.toStdString(), risposta));
}

QString ControllerCompitiUser::getPathRispCompito(const QString&codice, int risposta)
{
    return QString::fromStdString(utenteConnesso->getPathRispCompito(codice.toStdString(), risposta));
}

vector<string> ControllerCompitiUser::giveCompitiDates() const
{
    return utenteConnesso->giveCompitiDates();
}

bool ControllerCompitiUser::eliminaCompito(const QString&codice) const
{
    return utenteConnesso->eliminaCompito(codice.toStdString());
}

QString ControllerCompitiUser::getRispCompComment(const QString&codice, int risp) const
{
    return QString::fromStdString(utenteConnesso->getRispCompComment(codice.toStdString(),risp));
}
