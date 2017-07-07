#include "Utente.h"
#include "filexml.h"
#include "gruppo.h"
#include <QRegExp>


Utente::Utente(const string &s):NomeUtente(s), Nome(""), Cognome(""), fotoID(""){}

Utente::~Utente(){}

void Utente::InizializzaDatiPersonali(string nome, string cognome, string foto)
{
    Nome = nome;
    Cognome = cognome;
    fotoID = foto;
}

string Utente::daiNomeUtente() const{
    return NomeUtente;
}

string Utente::daiNome() const
{
    return Nome;
}

string Utente::daiCognome() const
{
    return Cognome;
}
string Utente::daifoto() const
{
    return fotoID;
}

list<string> Utente::daiMaterieInsegnate() const
{
    filexml f1("/MaterieInsegnate.xml");
    return f1.daiTestoDiNodi("NomeMateria");
}

vector<string> Utente::daiClassi() const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    return f1.daiTestoDiNodiVect("nome");
}

list<string> Utente::daiSessioniClassi() const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    return f1.daiTestoDiNodi("sessione");
}

list<string> Utente::daiIndirizzoClassi() const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    return f1.daiTestoDiNodi("indirizzo");
}



filexml Utente::giveSchedaClasse(const string &nome) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    return f1.daiTestoIn("riferimentoFile",f1.posNodo("nome",nome));
}

string Utente::checkForbiddenCharacters(const string &s)
{
    const QString& temp = QString::fromStdString(s);
    int i = temp.indexOf("<",0);
    if(i == -1)
        i = temp.indexOf(">",0);
    if(i == -1)
        i = temp.indexOf("&",0);
    if(i==-1)
       i = temp.indexOf("\"",0);
    if(i != -1)
        return "Sono vietati i seguenti caratteri: > < & \"";

    return "";
}

bool Utente::isNumeric(const string &s)
{
    QRegExp check("^[0-9]{1,}$");
    return check.indexIn(QString::fromStdString(s),0) != -1;
}

bool Utente::hasSpaceOrTab(const std::string &s)
{
    QRegExp check("[\\s\\t]{1,}");
    return check.indexIn(QString::fromStdString(s),0) != -1;
}

bool Utente::hasSpaceOrTabFirst(const string &s)
{
    QRegExp check("^[\\s,\\t]{1,}");
    return check.indexIn(QString::fromStdString(s),0) != -1;
}

bool Utente::hasSpaceOrTabLast(const string &s)
{
    QRegExp check("[\\s,\\t]{1,}$");
    return check.indexIn(QString::fromStdString(s),0) != -1;
}

bool Utente::HasNoChar(const std::string &s)
{
    QRegExp check("[a-z,A-Z,0-9]");
    return check.indexIn(QString::fromStdString(s),0) == -1;
}





