#include "professore.h"
#include <QDir>

string Professore::ProfFolder="/Professori";
Professore::Professore(string NomeUtente): Utente(NomeUtente){}

Professore *Professore::clone() const
{
    return new Professore(*this);
}

bool Professore::esiste() const
{
    filexml f(ProfFolder+"/NUProf.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente());
}

bool Professore::VerificaPassword(const string &p) const
{
    filexml f(ProfFolder+"/NUProf.xml");
    return f.apriFile() && f.akinTo("professore", Utente::daiNomeUtente(), p);
}

void Professore::InizializzaDatiPersonali()
{
    filexml f1(ProfFolder+"/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",Utente::daiNomeUtente())));
        if(f2.apriFile()){
                string nome=f2.daiTestoIn("Nome");
                string cognome=f2.daiTestoIn("Cognome");
                string fotoID=QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+f2.daiTestoIn("foto");
                string mansione=f2.daiTestoIn("mansione");
                string mail=f2.daiTestoIn("mailScuola");
                materie = f2.daiTestoDiNodi("materia");
                classi = f2.daiTestoDiNodiVect("classe");

                Impiegato::InizializzaDatiPersonali(nome,cognome,fotoID, mansione, mail);
        }
}

bool Professore::CambiaFotoProfilo(const string &path) const
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return false;
    filexml f1(ProfFolder+"/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",Utente::daiNomeUtente())));
    if(f2.apriFile()){
        const string& newFoto ="/immagini/FotoProfili/"+daiNomeUtente()+".jpg";
        if (QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
            QString::fromStdString(f2.daiTestoIn("foto"))) &&
            QFile::copy(QString::fromStdString(path), QDir::currentPath()+"/../progetto-pao-2017/Database"+
            QString::fromStdString(newFoto))){
            f2.editFiglioText("foto",newFoto);
            return f2.salva();
        }
    }
    return false;
}

bool Professore::CambiaPassword(const string &newPass) const
{
    string check = checkForbiddenCharacters(newPass);
    if(check != "" || hasSpaceOrTab(newPass)|| newPass.size() < 8)
        return false;
    filexml f1(ProfFolder+"/NUProf.xml");
    f1.editFiglioText("password",newPass,f1.posNodo("NomeUtente",daiNomeUtente()));
    return f1.salva();
}

string Professore::createNewCompitoXml(const string &data, const string &titolo, const string &descr,
                                     const string &materia, const string &classe, string& check) const
{
    check = checkForbiddenCharacters(data);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(titolo);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(descr);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(materia);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(classe);
    if(check != "")
        return "";
    if(HasNoChar(data) || HasNoChar(titolo)|| HasNoChar(descr)||HasNoChar(materia)||HasNoChar(classe)){
        check = "Tutti i campi sono obbligatori";
        return "";
    }
    filexml f1(ProfFolder+"/compiti/Info.xml");

  if(f1.apriFile()){
      string code = QString::number(f1.totNodi("compito")).toStdString();
      while(f1.esisteTesto(code))
          code = code + "0";
    string path = ProfFolder+"/compiti/xml/"+titolo+code+".xml";
    filexml f2 = filexml::createNewXml(path, "compito");
    f1.AggiungiNodoFiglio("compiti", "compito");
    f1.AggiungiNodoFiglioToLastNode("compito","codiceCompito");
    f1.AggiungiNodoFiglioToLastNode("codiceCompito",code,true);
    f1.AggiungiNodoFiglioToLastNode("compito","creatore");
    f1.AggiungiNodoFiglioToLastNode("creatore",daiNomeUtente(),true);
    f1.AggiungiNodoFiglioToLastNode("compito","data");
    f1.AggiungiNodoFiglioToLastNode("data",data,true);
    f1.AggiungiNodoFiglioToLastNode("compito","percorsoFile");
    f1.AggiungiNodoFiglioToLastNode("percorsoFile",path,true);
    f1.AggiungiNodoFiglioToLastNode("compito","FormatoFile");
    f1.AggiungiNodoFiglioToLastNode("FormatoFile","xml",true);
    f1.AggiungiNodoFiglioToLastNode("compito","titolo");
    f1.AggiungiNodoFiglioToLastNode("titolo",titolo,true);
    f1.AggiungiNodoFiglioToLastNode("compito","descrizione");
    f1.AggiungiNodoFiglioToLastNode("descrizione",descr,true);
    f1.AggiungiNodoFiglioToLastNode("compito","materia");
    f1.AggiungiNodoFiglioToLastNode("materia",materia,true);
    f1.AggiungiNodoFiglioToLastNode("compito","classi");
    f1.AggiungiNodoFiglioToLastNode("classi","classe");
    f1.AggiungiNodoFiglioToLastNode("classe",classe,true);
    if(f2.apriFile()){
    f2.AggiungiNodo("contenuto");
    f2.AggiungiNodoFiglioToLastNode("contenuto","data");
    f2.AggiungiNodoFiglioToLastNode("data",data,true);
    f2.AggiungiNodoFiglioToLastNode("contenuto","titolo");
    f2.AggiungiNodoFiglioToLastNode("titolo",titolo,true);
    f2.AggiungiNodoFiglioToLastNode("contenuto","descrizione");
    f2.AggiungiNodoFiglioToLastNode("descrizione",descr,true);
    f2.AggiungiNodoFiglioToLastNode("contenuto","materia");
    f2.AggiungiNodoFiglioToLastNode("materia",materia,true);
    f2.AggiungiNodoFiglioToLastNode("contenuto","classe");
    f2.AggiungiNodoFiglioToLastNode("classe",classe,true);
    f2.AggiungiNodoFiglioToLastNode("contenuto","domande");
    f2.AggiungiNodoFiglioToLastNode("contenuto","risposteUtenti");
    if(f1.salva() && f2.salva())
    return path;
    }
}
  check = "Errore con i file";
  return "";
}

string Professore::aggiungiDomandaARispMult(const string &path, const string &domanda,
                                          const list<string> &risposte, const list<bool> &corrette)
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(domanda);
    if(check != "")
        return check;
    if(HasNoChar(domanda))
        return "Tutti i campi sono obbligatori";
    for(list<string>::const_iterator it = risposte.begin(); it != risposte.end(); ++ it){
        check = checkForbiddenCharacters(*it);
        if(check != "")
            return check;
        if(HasNoChar(*it))
            return "Tutti i campi sono obbligatori";
    }
    filexml f(path);
    if(f.apriFile() && risposte.size() == corrette.size()){
        f.AggiungiNodoFiglioToLastNode("domande","domanda");
        f.AggiungiNodoFiglioToLastNode("domanda","tipoDomanda");
        f.AggiungiNodoFiglioToLastNode("tipoDomanda","domanda a risposta multipla",true);
        f.AggiungiNodoFiglioToLastNode("domanda","testoDomanda");
        f.AggiungiNodoFiglioToLastNode("testoDomanda",domanda,true);
        f.AggiungiNodoFiglioToLastNode("domanda","risposte");

        list<bool>::const_iterator it2 = corrette.begin();
        for(list<string>::const_iterator it = risposte.begin(); it != risposte.end(); ++ it){
            f.AggiungiNodoFiglioToLastNode("risposte","risposta");
            f.AggiungiNodoFiglioToLastNode("risposta","testoRisposta");
            f.AggiungiNodoFiglioToLastNode("testoRisposta",*it,true);
            f.AggiungiNodoFiglioToLastNode("risposta","corretta");
            f.AggiungiNodoFiglioToLastNode("corretta",QString::number(*it2).toStdString(),true);
            ++it2;
        }
         if(!f.salva())
             check = "Errore nel salvataggio";
    }
    return check;
}

string Professore::aggiungiDomandaAperta(const string &path, const string &domanda)
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(domanda);
    if(check != "")
        return check;
    if(HasNoChar(domanda))
        return "Tutti i campi sono obbligatori";
    filexml f(path);
    if(f.apriFile()){
        f.AggiungiNodoFiglioToLastNode("domande","domanda");
        f.AggiungiNodoFiglioToLastNode("domanda","tipoDomanda");
        f.AggiungiNodoFiglioToLastNode("tipoDomanda","domanda aperta",true);
        f.AggiungiNodoFiglioToLastNode("domanda","testoDomanda");
        f.AggiungiNodoFiglioToLastNode("testoDomanda",domanda,true);
        if(!f.salva())
            check = "Errore nel salvataggio";
    }
    return check;
}

bool Professore::loadCompitoPdf(const string &filePath, const string & data, const string &titolo, const string &descr, const string &materia, const string &classe)const
{
    string check = checkForbiddenCharacters(filePath);
    if(check != "" || HasNoChar(filePath))
        return false;
    check = checkForbiddenCharacters(data);
    if(check != "" || HasNoChar(data))
        return false;
    check = checkForbiddenCharacters(titolo);
    if(check != "" || HasNoChar(titolo))
        return false;
    check = checkForbiddenCharacters(descr);
    if(check != "" || HasNoChar(descr))
        return false;
    check = checkForbiddenCharacters(materia);
    if(check != "" || HasNoChar(materia))
        return false;
    check = checkForbiddenCharacters(classe);
    if(check != "" || HasNoChar(classe))
        return false;

    filexml f1(ProfFolder+"/compiti/Info.xml");

  if(f1.apriFile()){
      string code = QString::number(f1.totNodi("compito")).toStdString();
      while(f1.esisteTesto(code))
          code = code + "0";
        string path = ProfFolder+"/compiti/pdf/"+titolo+code+".pdf";
      if(QFile::copy(QString::fromStdString(filePath),QDir::currentPath()+"/../progetto-pao-2017/Database"+QString::fromStdString(path))){

    f1.AggiungiNodoFiglio("compiti", "compito");
    f1.AggiungiNodoFiglioToLastNode("compito","codiceCompito");
    f1.AggiungiNodoFiglioToLastNode("codiceCompito",code,true);
    f1.AggiungiNodoFiglioToLastNode("compito","creatore");
    f1.AggiungiNodoFiglioToLastNode("creatore",daiNomeUtente(),true);
    f1.AggiungiNodoFiglioToLastNode("compito","data");
    f1.AggiungiNodoFiglioToLastNode("data",data,true);
    f1.AggiungiNodoFiglioToLastNode("compito","percorsoFile");
    f1.AggiungiNodoFiglioToLastNode("percorsoFile",path,true);
    f1.AggiungiNodoFiglioToLastNode("compito","FormatoFile");
    f1.AggiungiNodoFiglioToLastNode("FormatoFile","pdf",true);
    f1.AggiungiNodoFiglioToLastNode("compito","titolo");
    f1.AggiungiNodoFiglioToLastNode("titolo",titolo,true);
    f1.AggiungiNodoFiglioToLastNode("compito","descrizione");
    f1.AggiungiNodoFiglioToLastNode("descrizione",descr,true);
    f1.AggiungiNodoFiglioToLastNode("compito","materia");
    f1.AggiungiNodoFiglioToLastNode("materia",materia,true);
    f1.AggiungiNodoFiglioToLastNode("compito","classi");
    f1.AggiungiNodoFiglioToLastNode("classi","classe");
    f1.AggiungiNodoFiglioToLastNode("classe",classe,true);
    return f1.salva();
    }
  }
  return false;
}


list<string> Professore::daiMaterieInsegnate() const
{
    return materie;
}

vector<string> Professore::daiClassi() const
{
    return classi;
}

vector<string> Professore::codiciCompiti() const
{
    filexml f1(ProfFolder+"/compiti/Info.xml");
    vector<string> v = f1.daiTestoDiNodiVect("codiceCompito",daiNomeUtente(),"compito");
    return v;
}

vector<string> Professore::giveCompitiTitle() const
{
    filexml f1(ProfFolder+"/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("titolo",daiNomeUtente(),"compito");
}

vector<string> Professore::giveCompitiDates() const
{
    filexml f1(ProfFolder+"/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("data",daiNomeUtente(),"compito");
}

void Professore::SortcodiciCompitibyMateria(vector<std::string> & l, const std::string & materia) const
{
    filexml f1("/Professori/compiti/Info.xml");
    for(vector<string>::iterator it = l.begin(); it != l.end(); ++it){
        if(!f1.akinTo("compito",*it,materia) || !f1.akinTo("compito",*it,daiNomeUtente())){
            l.erase(it);
            --it;
        }
    }
}

void Professore::SortcodiciCompitibyClasse(vector<std::string> & l, const std::string &classe) const
{
    filexml f1("/Professori/compiti/Info.xml");
    for(vector<string>::iterator it = l.begin(); it != l.end(); ++it){
        if(!f1.akinTo("compito",*it,classe) || !f1.akinTo("compito",*it,daiNomeUtente())){
            l.erase(it);
            --it;
        }
    }
}

bool Professore::commentaRispCompito(const string &codice, int risposta, const string &commento) const
{
    string check = checkForbiddenCharacters(codice);
    if(check != "")
        return false;
    check = checkForbiddenCharacters(commento);
    if(check != "")
        return false;

    filexml f1(ProfFolder+"/compiti/Info.xml");
    filexml f2(f1.daiTestoIn("percorsoFile",f1.posNodo("codiceCompito",codice)));
    f2.AggiungiNodoFiglio("commentoAutore", risposta,"testoCommento");
    f2.AggiungiNodoFiglio("testoCommento", risposta,commento,true);
    return f2.salva();
}

bool Professore::cancellaCompito(const string &codice) const
{
    filexml f1(ProfFolder+"/compiti/Info.xml");
    int pos = f1.posNodo("codiceCompito",codice);
    filexml f2 (f1.daiTestoIn("percorsoFile",pos));
    if(f2.apriFile()){
        int tot = f2.totNodi("foglio");
        while( tot > 0){
            const QString& path = QDir::currentPath()+"/../progetto-pao-2017/Database" +
                    QString::fromStdString(f2.daiTestoIn("foglio",tot-1));
            if(QFile::remove(path))
                --tot;
        }
   if(tot == 0  && QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database" +
          QString::fromStdString(f2.daiPath())) ){
    f1.EliminaNodo("compito",pos);
    return f1.salva();
   }
    }
    return false;
}

string Professore::aggiungiClasseACompito(const string &codice, const string &classe) const
{
    filexml f1(ProfFolder+"/compiti/Info.xml");
    int pos = f1.posNodo("codiceCompito",codice);
    if(pos != -1){
    if(f1.esisteTesto("classi",classe,pos))
        return "Errore: Ha già assegnato questo compito alla classe "+classe;
    f1.AggiungiNodoFiglio("classi",pos,"classe");
    f1.AggiungiNodoFiglio("compito",pos,"classe",f1.totNodiFigli("classi",pos,"classe")-1, classe,true);
    return (f1.salva()) ? "" : "Errore nel salvataggio";
    }
    return "Errore nell'apertura dei file";

}


