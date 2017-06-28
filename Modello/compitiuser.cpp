#include "compitiuser.h"
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include "../Modello/filexml.h"

string compitiUser::getPdfCompitoPath(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return (QDir::currentPath()+"/../progetto-pao-2017/Database").toStdString()+
            f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice));
}
vector<string> compitiUser::codiciCompiti() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("codiceCompito");
}

void compitiUser::SortcodiciCompitibyMateria(vector<string>& l,const string & materia) const
{
    filexml f1("/Professori/compiti/Info.xml");
    for(vector<string>::iterator it = l.begin(); it != l.end(); ++it){
        if(!f1.akinTo("compito",*it,materia)){
            l.erase(it);
            --it;
        }
    }
}

void compitiUser::SortcodiciCompitibyClasse(vector<string> & l, const string & classe) const
{
    filexml f1("/Professori/compiti/Info.xml");
    for(vector<string>::iterator it = l.begin(); it != l.end(); ++it){
        if(!f1.akinTo("compito",*it,classe)){
            l.erase(it);
            --it;
        }
    }
}

vector<string> compitiUser::giveCompitiTitle() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("titolo");
}

list<string> compitiUser::classiCompito(const string& codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodi("classe",codice,"compito");
}

string compitiUser::getCompitoFormato(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("FormatoFile",f1.posNodo("codiceCompito",codice));
}

string compitiUser::getCompitoTitolo(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("titolo",f1.posNodo("codiceCompito",codice));
}

string compitiUser::getCompitoDescrizione(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("descrizione",f1.posNodo("codiceCompito",codice));
}

string compitiUser::getCompitoMateria(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("materia",f1.posNodo("codiceCompito",codice));
}

string compitiUser::getCompitoClasse(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("classe",f1.posNodo("codiceCompito",codice));
}

string compitiUser::getCompitoAutore(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("creatore",f1.posNodo("codiceCompito",codice));
}

vector<string> compitiUser::giveCompitiDates() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("data");
}

string compitiUser::giveCompitoXml(const string& codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice));
}
bool compitiUser::salvaRispCompito(string risposte, const string& codice) const
{
    string check = checkForbiddenCharacters(risposte);
    if(check != ""){
        return false;
    }
    if(risposte != ""){
        filexml f1("/Professori/compiti/Info.xml");
        if(f1.apriFile()){
            filexml f2(f1.daiTestoIn("percorsoFile", f1.posNodo("codiceCompito",codice)));
            if(f2.apriFile()){
                string path = "/Professori/compiti/risposte";
                f2.AggiungiNodoFiglioToLastNode("risposteUtenti","rispostaUtente");
                f2.AggiungiNodoFiglioToLastNode("rispostaUtente","nomeUtente");
                f2.AggiungiNodoFiglioToLastNode("nomeUtente",daiNomeUtente(),true);
                f2.AggiungiNodoFiglioToLastNode("rispostaUtente","nome");
                f2.AggiungiNodoFiglioToLastNode("nome",daiNome(),true);
                f2.AggiungiNodoFiglioToLastNode("rispostaUtente","cognome");
                f2.AggiungiNodoFiglioToLastNode("cognome",daiCognome(),true);
                f2.AggiungiNodoFiglioToLastNode("rispostaUtente","foglio");
                f2.AggiungiNodoFiglioToLastNode("foglio",path+"/risposta"+codice+
                                                QString::number(f2.totNodi("rispostaUtente")).toStdString()+".pdf",true);
                f2.AggiungiNodoFiglioToLastNode("rispostaUtente","commenti");
                f2.AggiungiNodoFiglioToLastNode("commenti","commentoAutore");

                  risposte = daiCognome()+" "+daiNome()+"\n\n\n\n" + risposte;
                 QPrinter printer(QPrinter::HighResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setPageSize(QPrinter::A4);
                 printer.setOutputFileName(QDir::currentPath()+"/../progetto-pao-2017/Database"+
                                           QString::fromStdString(path+ "/risposta"+codice)+
                                           QString::number(f2.totNodi("rispostaUtente"))+".pdf");
                 QPainter painter(&printer);
                 painter.setFont(QFont("Times",12));
                 painter.drawText(printer.pageRect(),Qt::TextWordWrap,QString::fromStdString(risposte));
                 painter.end();
                 return f2.salva();
            }
        }
    }
    return false;
}

int compitiUser::totRispCompito(const string &codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.totNodi("rispostaUtente");
}

string compitiUser::getNomeRispCompito(const string &codice, int risposta)
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.daiTestoIn("nome",risposta);
}

string compitiUser::getCognomeRispCompito(const string &codice, int risposta)
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.daiTestoIn("cognome",risposta);
}

string compitiUser::getPathRispCompito(const string &codice, int risposta)
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+ f2.daiTestoIn("foglio",risposta);
}

bool compitiUser::commentaRispCompito(const string &codice, int risposta, const string& commento) const
{
    string check = checkForbiddenCharacters(commento);
    if(check != "")
        return false;
    return codice != "" && risposta != -1 && commento != "";
}

bool compitiUser::HasRispCompitoCom(const string &codice, int risposta) const
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.hasNodoTesto("testoCommento",risposta);
}

bool compitiUser::eliminaCompito(const string &codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    string path = f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice));
    filexml f2(path);
    int tot = f2.totNodi("rispostaUtente");
    for(int i = 0; i < tot; ++i){
        QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
                      QString::fromStdString(f2.daiTestoIn("foglio",i)));
    }
    path = QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+ path;
    f1.EliminaNodo("compito",f1.posNodo("compito",codice));
    return f1.salva() && QFile::remove(QString::fromStdString(path));
}

bool compitiUser::hasAnsweredCompito(const string & codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.apriFile() && f2.esisteTesto("rispostaUtente", daiNomeUtente());
}

int compitiUser::MyAnswrCompito(const string &codice) const
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.posNodo("rispostaUtente",daiNomeUtente());
}
string compitiUser::getRispCompComment(const string &codice, int risp) const
{
    filexml f1("/Professori/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    return f2.daiTestoIn("testoCommento", risp);
}
