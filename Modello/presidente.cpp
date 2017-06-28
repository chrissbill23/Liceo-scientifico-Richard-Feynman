#include "presidente.h"
#include "container.h"
#include <QDir>

string Presidente::PresFolder="/Presidente";

bool Presidente::aggiornaMailSegr(const string &NomeUtente, const string &nuovamail) const
{
    filexml f("/Segretari/NUSegr.xml");
    if(f.esisteTesto(NomeUtente)){
        filexml f2(f.daiTestoIn("schedaPersonale",f.posNodo("NomeUtente",NomeUtente)));
        f2.editFiglioText("mailScuola",nuovamail,f2.posNodo("schedaPersonale","mailScuola"));
        return f2.salva();
    }
    return false;
}

bool Presidente::aggiornaMailProf(const string &NomeUtente, const string &nuovamail) const
{
      filexml f("/Professori/NUProf.xml");
      if(f.esisteTesto(NomeUtente)){
          filexml f2(f.daiTestoIn("schedaPersonale",f.posNodo("NomeUtente",NomeUtente)));
          f2.editFiglioText("mailScuola",nuovamail,f2.posNodo("schedaPersonale","mailScuola"));
          return f2.salva();
      }
      return false;
}

Presidente::Presidente(string NomeUtente):Utente(NomeUtente){}

Presidente *Presidente::clone() const
{
    return new Presidente(*this);
}

bool Presidente::esiste() const
{
    filexml f(PresFolder+"/InfoPresid.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente", daiNomeUtente());

}

bool Presidente::VerificaPassword(const string &p) const
{
    filexml f(PresFolder+"/InfoPresid.xml");
    return f.apriFile() && f.akinTo("presidente", daiNomeUtente(),p);
}

void Presidente::InizializzaDatiPersonali()
{
filexml f(PresFolder+"/InfoPresid.xml");
string nome = f.daiTestoIn("Nome");
string cognome=f.daiTestoIn("Cognome");
string fotoID=QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+f.daiTestoIn("foto");
string mansione=f.daiTestoIn("mansione");
finecarriera=f.daiTestoIn("dataFineCarriera");
string mail=f.daiTestoIn("mailScuola");

Impiegato::InizializzaDatiPersonali(nome,cognome,fotoID, mansione, mail);
}

bool Presidente::CambiaFotoProfilo(const string &path) const
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return false;
    filexml f1(PresFolder+"/InfoPresid.xml");
    if(f1.apriFile()){
        const string& newFoto ="/immagini/FotoProfili/"+daiNomeUtente()+".jpg";
        if (QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
            QString::fromStdString(f1.daiTestoIn("foto"))) &&
            QFile::copy(QString::fromStdString(path), QDir::currentPath()+"/../progetto-pao-2017/Database"+
            QString::fromStdString(newFoto))){
            f1.editFiglioText("foto",newFoto);
            return f1.salva();
        }
    }
    return false;
}

bool Presidente::CambiaPassword(const string &newPass) const
{
    string check = checkForbiddenCharacters(newPass);
    if(check != "" || hasSpaceOrTab(newPass)|| newPass.size() < 8)
        return false;
    filexml f1(PresFolder+"/InfoPresid.xml");
    f1.editFiglioText("password",newPass);
    return f1.salva();
}

list<string> Presidente::DaiDatiPersonali() const
{
    list<string> l;
    l.push_back(Utente::daiCognome());
    l.push_back(Utente::daiNome());
    l.push_back(Utente::daiNomeUtente());
    l.push_back(daiMail());
    l.push_back(daiMansione());
    l.push_back(finecarriera);
    return l;
}

string Presidente::aggiungiMateria(const string &materia) const
{
    string check = checkForbiddenCharacters(materia);
    if(check != "")
        return check;
    if(HasNoChar(materia))
        return "il nome della materia non può essere vuoto";
    filexml f("/MaterieInsegnate.xml");
    if(f.apriFile()){
    if(f.daiTextContainingText("NomeMateria", materia).size() == 0){
       f.AggiungiNodoFiglio("materie","NomeMateria");
       f.AggiungiNodoFiglioToLastNode("NomeMateria",materia,true);
       if(f.salva())
       return "";
        }
    else
    return "Questa materia esiste già";
    }
    return "Errore con i file";
}

string Presidente::RimuoviMateria(const string &materia) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if(f1.apriFile()){
    Container<filexml> c;
    c.AddFileDaLista(f1,"riferimentoFile");
    for(Container<filexml>::Iteratore it = c.begin(); it != c.end(); ++it){
        if((*it).esisteTesto("NomeMateria",materia))
            return "Impossibile cancellare questa materia,\n è ancora insegnata";
    }
    filexml f("/MaterieInsegnate.xml");
    f.EliminaNodo("NomeMateria",materia,"materie", f.posNodo("materie",materia));
    if(f.salva())
        return "";
    }
    return "Errore con i file";
}

string Presidente::generaMail(const string &nome, const string &Cognome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(Cognome);
    if(check != "")
        return "";
    if(hasSpaceOrTabFirst(nome) || hasSpaceOrTabFirst(Cognome))
        return "";
    if(hasSpaceOrTabLast(nome) || hasSpaceOrTabLast(Cognome))
        return "";
    string mail = nome+"_"+Cognome;
    filexml f("/Messaggi/email.xml");
    list<string> l = f.daiTextContainingText("mail",mail);
    mail = mail + QString::number(l.size()+1).toStdString();
    mail = mail+"@mail.it";

    return mail;

}

string Presidente::generaNomeUtente(const string &nome, const string &cognome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(cognome);
    if(check != "")
        return "";
    if(hasSpaceOrTabFirst(nome) || hasSpaceOrTabFirst(cognome))
        return "";
    if(hasSpaceOrTabLast(nome) || hasSpaceOrTabLast(cognome))
        return "";
    filexml f("/Messaggi/email.xml");
    string nu = nome.substr(0,2)+cognome.substr(0,cognome.size());
    list<string> l = f.daiTextContainingText("NomeUtente",nu);
    nu = nu + QString::number(l.size()+1).toStdString();
    return nu;
}

string Presidente::generaPassword(const string &nome, const string &cognome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return "";
    check = checkForbiddenCharacters(cognome);
    if(check != "")
        return "";
    if(hasSpaceOrTabFirst(nome) || hasSpaceOrTabFirst(cognome))
        return "";
    if(hasSpaceOrTabLast(nome) || hasSpaceOrTabLast(cognome))
        return "";
    return nome.substr(0,2)+cognome.substr(0,2)+"pass";
}

vector<string> Presidente::giveProfNU() const
{
    filexml f1("/Professori/NUProf.xml");
    return f1.daiTestoDiNodiVect("NomeUtente");
}

vector<string> Presidente::giveSegrNU() const
{
    filexml f1("/Segretari/NUSegr.xml");
    return f1.daiTestoDiNodiVect("NomeUtente");
}

bool Presidente::AggiungiMailImpiegato(const string &NomeUtente, const string& nuovamail) const
{
    string check = checkForbiddenCharacters(nuovamail);
    if(check != "")
        return false;
    if(nuovamail != ""){
    filexml f("/Messaggi/email.xml");
    if(f.esisteTesto("mail",nuovamail))
        return false;
    if(!f.esisteTesto("NomeUtente", NomeUtente) &&
      filexml::createNewXml("/Messaggi/Messaggi Ricevuti/"+
                NomeUtente+"Ricevuti.xml","messaggiricevuti").apriFile() &&
     filexml::createNewXml("/Messaggi/Messaggi Inviati/"+NomeUtente+"Inviati.xml"
                           ,"messaggiinviati").apriFile()){
    f.AggiungiNodoFiglio("email","utente");
    f.AggiungiNodoFiglioToLastNode("utente","NomeUtente");
    f.AggiungiNodoFiglioToLastNode("NomeUtente",NomeUtente,true);
    f.AggiungiNodoFiglioToLastNode("utente","mail");
    f.AggiungiNodoFiglioToLastNode("mail","nessuna mail",true);
    f.AggiungiNodoFiglioToLastNode("utente","mailRicevuta");
    f.AggiungiNodoFiglioToLastNode("mailRicevuta","/Messaggi/Messaggi Ricevuti/"+NomeUtente+"Ricevuti.xml",true);
    f.AggiungiNodoFiglioToLastNode("utente","mailInviata");
    f.AggiungiNodoFiglioToLastNode("mailInviata","/Messaggi/Messaggi Inviati/"+NomeUtente+"Inviati.xml",true);
    }
    f.editFiglioText("mail", nuovamail, f.posNodo("mail",NomeUtente,"utente"));
    return f.salva() && (aggiornaMailProf(NomeUtente, nuovamail) || aggiornaMailSegr(NomeUtente,nuovamail));
    }
    return false;
}

bool Presidente::esisteImpiegato(const string &NomeUtente)const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2("/Segretari/NUSegr.xml");

    return f1.esisteTesto(NomeUtente) || f2.esisteTesto(NomeUtente);
}

string Presidente::aggiungiSegretario(const string &NomeUtente, const string &password, const string& nome, const string& cognome) const
{
    string check = checkInputformAddImpieg(NomeUtente, password, nome, cognome);
    if(check != "")
        return check;
    if(!esisteImpiegato(NomeUtente)){
    filexml f1 = filexml::createNewXml("/Segretari/Schede Personali/"+NomeUtente+".xml", "schedaPersonale");
    filexml f2("/Segretari/NUSegr.xml");
    if(f1.apriFile() && f2.apriFile()){
        string n = QString::fromStdString(nome).toUpper().toStdString();
        string c = QString::fromStdString(cognome).toUpper().toStdString();
        f1.AggiungiNodo("nomeUtente");
        f1.AggiungiNodoFiglio("nomeUtente",NomeUtente,true);
        f1.AggiungiNodo("mailScuola");
        f1.AggiungiNodoFiglio("mailScuola", "nessuna mail", true);
        f1.AggiungiNodo("mansione");
        f1.AggiungiNodoFiglio("mansione","Segretario/a studenti",true);
        f1.AggiungiNodo("DatiPersonali");
        f1.AggiungiNodoFiglio("DatiPersonali","Nome");
        f1.AggiungiNodoFiglio("Nome",n,true);
        f1.AggiungiNodoFiglio("DatiPersonali","Cognome");
        f1.AggiungiNodoFiglio("Cognome",c,true);

        f1.AggiungiNodoFiglio("DatiPersonali","foto");
        const string& path1 = QDir::currentPath().toStdString()+
                "/../progetto-pao-2017/Database/immagini/FotoProfili/emptyFoto.jpg";
        const string& path2 = "/immagini/FotoProfili/"+NomeUtente+".jpg";
        QFile::copy(QString::fromStdString(path1), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                    QString::fromStdString(path2));
        f1.AggiungiNodoFiglio("foto",path2,true);

        f2.AggiungiNodoFiglio("NomeUtenti", "segretario");
        f2.AggiungiNodoFiglioToLastNode("segretario","NomeUtente");
        f2.AggiungiNodoFiglioToLastNode("NomeUtente",NomeUtente,true);
        f2.AggiungiNodoFiglioToLastNode("segretario","password");
        f2.AggiungiNodoFiglioToLastNode("password",password,true);
        f2.AggiungiNodoFiglioToLastNode("segretario","schedaPersonale");
        f2.AggiungiNodoFiglioToLastNode("schedaPersonale",f1.daiPath(), true);

        if(!f1.salva() || !f2.salva())
            check = "Errore nel salvataggio";
    }
    else check ="errore con i file";
    }
    return check;
}

string Presidente::aggiungiProfessore(const string &NomeUtente, const string &password, const string &nome, const string &cognome) const
{
    string check = checkInputformAddImpieg(NomeUtente, password, nome, cognome);
    if(check != "")
        return check;
    if(!esisteImpiegato(NomeUtente)){
    filexml f1 = filexml::createNewXml("/Professori/Schede Personali/"+NomeUtente+".xml", "schedaPersonale");
    filexml f2("/Professori/NUProf.xml");
    if(f1.apriFile() && f2.apriFile()){
        string n = QString::fromStdString(nome).toUpper().toStdString();
        string c = QString::fromStdString(cognome).toUpper().toStdString();
        f1.AggiungiNodo("nomeUtente");
        f1.AggiungiNodoFiglio("nomeUtente",NomeUtente,true);
        f1.AggiungiNodo("mailScuola");
        f1.AggiungiNodoFiglio("mailScuola", "nessuna mail", true);
        f1.AggiungiNodo("mansione");
        f1.AggiungiNodoFiglio("mansione","Professore",true);
        f1.AggiungiNodo("DatiPersonali");
        f1.AggiungiNodo("DatiOccupazione");
        f1.AggiungiNodoFiglio("DatiPersonali","Nome");
        f1.AggiungiNodoFiglio("Nome",n,true);
        f1.AggiungiNodoFiglio("DatiPersonali","Cognome");
        f1.AggiungiNodoFiglio("Cognome",c, true);


        f1.AggiungiNodoFiglio("DatiPersonali","foto");
        const string& path1 = QDir::currentPath().toStdString()+
                "/../progetto-pao-2017/Database/immagini/FotoProfili/emptyFoto.jpg";
        const string& path2 = "/immagini/FotoProfili/"+NomeUtente+".jpg";
        QFile::copy(QString::fromStdString(path1), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                    QString::fromStdString(path2));
        f1.AggiungiNodoFiglio("foto",path2,true);


        f1.AggiungiNodoFiglio("DatiOccupazione","materie");
        f1.AggiungiNodoFiglio("DatiOccupazione","classi");

        f2.AggiungiNodoFiglio("NomeUtenti", "professore");
        f2.AggiungiNodoFiglioToLastNode("professore","NomeUtente");
        f2.AggiungiNodoFiglioToLastNode("NomeUtente",NomeUtente, true);
        f2.AggiungiNodoFiglioToLastNode("professore","password");
        f2.AggiungiNodoFiglioToLastNode("password",password, true);
        f2.AggiungiNodoFiglioToLastNode("professore","schedaPersonale");
        f2.AggiungiNodoFiglioToLastNode("schedaPersonale",f1.daiPath(), true);

        if(!f1.salva() || !f2.salva())
            check = "Errore nel salvataggio";
    }
    else check = "errore con i file";
    }
    return check;
}

string Presidente::aggiungiClasseAProf(const string &NomeUtente, const string &classe) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    if(f2.apriFile()){
        if(!f2.esisteTesto(classe)){
        f2.AggiungiNodoFiglio("classi", "classe");
        f2.AggiungiNodoFiglioToLastNode("classe", classe,true);
         }
        if(f2.salva())
            return "";

    }
    return "Errore con i file";
}

string Presidente::aggiungiMaterieAProf(const string &NomeUtente, const string &materia) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    if(f2.apriFile()){
        if(!f2.esisteTesto(materia)){
        f2.AggiungiNodoFiglio("materie", "materia");
        f2.AggiungiNodoFiglioToLastNode("materia", materia,true);
        }
        if(f2.salva())
            return "";

    }
    return "Errore con i file";

}

std::string Presidente::checkInputformAddImpieg(const string& NomeUtente, const string &password, const string &nome, const string &cognome)const
{
    //------Nome utente---------
    string check = checkForbiddenCharacters(NomeUtente);
    if(check != "")
        return check;
    if(hasSpaceOrTab( NomeUtente))
        return "Il nome utente non può avere caratteri tab o di spaziatura";
    //--------Password------
    check = checkForbiddenCharacters(password);
    if(check != "")
        return check;
    if(hasSpaceOrTab( password))
        return "La password non può avere caratteri tab o di spaziatura";
    //------nome---------
    check = checkForbiddenCharacters(nome);
    if(check != "")
        return check;
    if(hasSpaceOrTabLast(nome) || hasSpaceOrTabFirst(nome))
        return "Non è concesso un carattere tab o di spaziatura all'inizio o alla fine del nome";
    //------Cognome---------
    check = checkForbiddenCharacters(cognome);
    if(check != "")
        return check;
    if(hasSpaceOrTabLast(cognome) || hasSpaceOrTabFirst(cognome))
        return "Non è concesso un carattere tab o di spaziatura all'inizio o alla fine del cognome";
    return "";
}

string Presidente::aggiungiClasseEMateriaAProf(const string &NomeUtente, const string &classe, const string &materia) const
{
    filexml f3("/Professori/NUProf.xml");
    filexml f4(f3.daiTestoIn("schedaPersonale",f3.posNodo("NomeUtente",NomeUtente)));
    string check = "Errore con  i file";
    if(f3.apriFile() && f4.apriFile()){
        if(!f4.esisteTesto("materia:classe",materia+":"+classe)){
            check = aggiungiClasseAProf(NomeUtente,classe);
            if(check == ""){
                f4 = filexml(f4.daiPath());
                check = aggiungiMaterieAProf(NomeUtente,materia);
                if( check == ""){
                    f4 = filexml(f4.daiPath());
                    filexml f1("/studenti/Classi/TutteLeClassi.xml");
                    filexml f2(f1.daiTestoIn("riferimentoFile",f1.posNodo("riferimentoFile",classe,"classe")));
                    if(f2.apriFile()){
                    int pos = f2.posNodo("NomeMateria",materia);
                    if(pos != -1)
                        f2.editFiglioText("Professore",NomeUtente,pos);
                    else{
                        f2.AggiungiNodoFiglio("Materie","materia");
                        f2.AggiungiNodoFiglioToLastNode("materia","NomeMateria");
                        f2.AggiungiNodoFiglioToLastNode("NomeMateria",materia,true);
                        f2.AggiungiNodoFiglioToLastNode("materia","Professore");
                        f2.AggiungiNodoFiglioToLastNode("Professore",NomeUtente,true);
                    }
            f4.AggiungiNodoFiglio("DatiOccupazione","materia:classe");
            f4.AggiungiNodoFiglioToLastNode("materia:classe",materia+":"+classe,true);
                if(f2.salva() && f4.salva())
                    check = "";
                 }
        }
    }
   } else check = "L'insegnato selezionato insegna già questa materia a questa classe";
  }
    return check;
}

string Presidente::rimuoviClasseAProf(const string &NomeUtente, const string &classe) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    if(f2.apriFile()){
        if(f2.daiTextContainingText("materia:classe",classe).size() <= 1){
        f2.EliminaNodo("classe",classe);
        }
        if(f2.salva())
        return "";
    }
    return "Errore con i file";
}

string Presidente::rimuoviMateriaAProf(const string &NomeUtente, const string &materia) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    if(f2.apriFile()){
        if(f2.daiTextContainingText("materia:classe",materia).size() <= 1){
        f2.EliminaNodo("materia",materia);
        }
        if(f2.salva())
        return "";
    }
    return "Errore con i file";
}

string Presidente::rimuoviProf(const string &NomeUtente) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    filexml f3("/Messaggi/email.xml");
    if(f2.apriFile() && f3.apriFile()){

        if(f2.totNodiFigli("classi",f2.posNodo("DatiOccupazione","classi")) > 0)
            return "Errore: questo docente è ancora assegnato a delle classi";

        int pos = f3.posNodo("NomeUtente",NomeUtente);

       if(QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
          QString::fromStdString(f2.daiTestoIn("foto"))) &&
          QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
          QString::fromStdString(f2.daiPath())) &&
          QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
          QString::fromStdString(f3.daiTestoIn("mailRicevuta",pos))) &&
         QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
         QString::fromStdString(f3.daiTestoIn("mailInviata",pos)))){

        f1.EliminaNodo("professore",NomeUtente);
        f3.EliminaNodo("utente",NomeUtente);
        if(f1. salva() && f3.salva())
            return "";
        }
    }
    return "Errore con i file";
}

string Presidente::rimuoviMateriaEClasseAProf(const string &NomeUtente, const string &classe, const string &materia) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    string check = "Errore con  i file";
    if(f1.apriFile() && f2.apriFile()){
        if(f2.esisteTesto("materia:classe",materia+":"+classe)){
            check = rimuoviMateriaAProf(NomeUtente,materia);
            if(check == ""){
                f2 = filexml(f2.daiPath());
                check = rimuoviClasseAProf(NomeUtente,classe);
                    if(check == ""){
                        f2 = filexml(f2.daiPath());
                        f2.EliminaNodo("materia:classe",materia+":"+classe);
                        filexml f3("/studenti/Classi/TutteLeClassi.xml");
                        filexml f4(f3.daiTestoIn("riferimentoFile",f3.posNodo("riferimentoFile",classe,"classe")));
                        f4.editFiglioText("Professore","Nessun insegnante",f4.posNodo("NomeMateria",materia));
                        if(!f2.salva() || !f4.salva())
                            check = "Errore con i file";
                        }
                }
        }
        else check = "L'insegnante da lei selezionato non insegna questa materia a questa classe";
    }
    return check;
}

bool Presidente::rimuoviSegr(const string &NomeUtente) const
{
    filexml f1("/Segretari/NUSegr.xml");
    filexml f2("/Messaggi/email.xml");
    filexml f3(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));

    if(QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
       QString::fromStdString(f3.daiTestoIn("foto"))) &&
       QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
                         QString::fromStdString(f3.daiPath()))){

        int pos = f2.posNodo("NomeUtente",NomeUtente);
       if(QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
          QString::fromStdString(f2.daiTestoIn("mailRicevuta",pos))) &&
         QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
         QString::fromStdString(f2.daiTestoIn("mailInviata",pos)))){
                f1.EliminaNodo("segretario",NomeUtente);
                f2.EliminaNodo("utente",NomeUtente);
                return f1.salva() && f2.salva();
       }
    }
    return false;
}

string Presidente::aggiungiIndirizzoClassi(const string &nome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return check;
    if(HasNoChar(nome))
        return "il nome dell'indirizzo non può essere vuoto";
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if(f1.apriFile()){
        if(f1.daiTextContainingText("indirizzo",nome).size() == 0){
            f1.AggiungiNodoFiglio("indirizzi","indirizzo");
            f1.AggiungiNodoFiglioToLastNode("indirizzo",nome,true);
            if(f1.salva())
                return "";
        }
        else return "Questo indirizzo esiste già";
    }
    return "Errore con i file";
}

string Presidente::rimuoviIndirizzoClassi(const string &nome) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if(f1.apriFile()){
    Container<filexml> c;
    c.AddFileDaLista(f1,"riferimentoFile");
    for(Container<filexml>::Iteratore it = c.begin(); it != c.end(); ++it){
        if((*it).esisteTesto("indirizzo",nome))
            return "Impossibile cancellare\n ci sono ancora classi in questo indirizzo";
    }
    f1.EliminaNodo("indirizzo",nome);
    if(f1.salva())
        return "";
    }
    return "Errore con i file";
}

string Presidente::aggiungiSessioniClassi(const string &nome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return check;
    if(HasNoChar(nome))
        return "il nome della sessione non può essere vuoto";
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if(f1.apriFile()){
        if(f1.daiTextContainingText("sessione",nome).size() == 0){
    f1.AggiungiNodoFiglio("sessioni","sessione");
    f1.AggiungiNodoFiglioToLastNode("sessione",nome,true);
    if(f1.salva())
    return "";
        }
        else return "Questa sessione esite già";
    }
    return "Errore con i file";
}

string Presidente::rimuoviSessioniClassi(const string &nome) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    Container<filexml> c;
    if(f1.apriFile()){
    c.AddFileDaLista(f1,"riferimentoFile");
    for(Container<filexml>::Iteratore it = c.begin(); it != c.end(); ++it){
        if((*it).esisteTesto("sessione",nome))
            return "Impossibile cancellare\n ci sono ancora classi di questa sessione";
    }
    f1.EliminaNodo("sessione",nome);
    if(f1.salva())
        return "";
    }
    return "Errore con i file";
}

string Presidente::aggiungiClasse(const string &classe, const string &sessione, const string &indirizzo) const
{
    string check = checkForbiddenCharacters(classe);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(sessione);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(indirizzo);
    if(check != "")
        return check;
    const string& nome = classe+sessione+" "+indirizzo;
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if( f1.apriFile())
    {
        if(!f1.esisteTesto("nome",nome)){
        const string& percorso = "/studenti/Classi/"+classe+sessione+"_"+indirizzo+".xml";
        filexml f2 = filexml::createNewXml(percorso,"schedaClasse");
        if(f2.apriFile()){
            f2.AggiungiNodoFiglio("schedaClasse","nomeClasse");
            f2.AggiungiNodoFiglioToLastNode("nomeClasse",nome,true);
            f2.AggiungiNodoFiglio("schedaClasse","sessione");
            f2.AggiungiNodoFiglioToLastNode("sessione",sessione,true);
            f2.AggiungiNodoFiglio("schedaClasse","indirizzo");
            f2.AggiungiNodoFiglioToLastNode("indirizzo",indirizzo,true);
            f2.AggiungiNodoFiglio("schedaClasse","Alunni");
            f2.AggiungiNodoFiglio("schedaClasse","Materie");

            f1.AggiungiNodoFiglio("TutteLeClassi","classe");
            f1.AggiungiNodoFiglioToLastNode("classe","nome");
            f1.AggiungiNodoFiglioToLastNode("nome",nome,true);
            f1.AggiungiNodoFiglioToLastNode("classe","riferimentoFile");
            f1.AggiungiNodoFiglioToLastNode("riferimentoFile",percorso,true);

            if(f1.salva() && f2.salva())
                return "";
        }
        }
        else return "Questa classe esiste già";
    }
    return "Errore con i file";
}

string Presidente::rimuoviClasse(const string &nomeclasse) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    if(f1.apriFile() && f1.esisteTesto(nomeclasse))
    {
        filexml f2(f1.daiTestoIn("riferimentoFile",f1.posNodo("nome",nomeclasse)));
        if(f2.apriFile()){
        if(f2.esisteNodo("NomeUtente")|| f2.esisteNodo("materia") )
            return " Ci sono ancora studenti e/o professori assegnati a questa classe";

        if(QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
                                               QString::fromStdString(f2.daiPath()))){
             f1.EliminaNodo("classe",nomeclasse,"TutteLeClassi",f1.posNodo("TutteLeClassi","classe"));
             if(f1.salva())
                 return "";

        }
        return "E' avvenuto un errore";
        }
    }
    return "Errore con i file";
}

string Presidente::daiCognomeProf(const string &NomeUtente) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2.daiTestoIn("Cognome");
}

string Presidente::daiNomeProf(const string &NomeUtente) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2.daiTestoIn("Nome");
}

string Presidente::daiCognomeSegr(const string &NomeUtente) const
{
    filexml f1("/Segretari/NUSegr.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2.daiTestoIn("Cognome");
}

string Presidente::daiNomeSegr(const string &NomeUtente) const
{
    filexml f1("/Segretari/NUSegr.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2.daiTestoIn("Nome");
}

filexml Presidente::giveSchedaPersonaleProf(const string &NomeUtente) const
{
    filexml f1("/Professori/NUProf.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2;
}

filexml Presidente::giveSchedaPersonaleSegr(const string &NomeUtente) const
{
    filexml f1("/Segretari/NUSegr.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",NomeUtente)));
    return f2;
}
