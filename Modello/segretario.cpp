#include "segretario.h"
#include "container.h"
#include <QDir>

string Segretario::SegrFolder="/Segretari";
bool Segretario::esiste() const
{
    filexml f(SegrFolder+"/NUSegr.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente());
}

Segretario::Segretario(string NomeUtente): Utente(NomeUtente){}

Segretario *Segretario::clone() const
{
    return new Segretario(*this);
}

bool Segretario::VerificaPassword(const string &p) const
{
    filexml f(SegrFolder+"/NUSegr.xml");
    return f.apriFile() && f.akinTo("segretario", Utente::daiNomeUtente(), p);
}


void Segretario::InizializzaDatiPersonali()
{
    filexml f1(SegrFolder+"/NUSegr.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",Utente::daiNomeUtente())));
    if(f2.apriFile()){
                string nome = f2.daiTestoIn("Nome");
                string cognome=f2.daiTestoIn("Cognome");
                string fotoID=QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+f2.daiTestoIn("foto");
                string mansione=f2.daiTestoIn("mansione");
                string mail=f2.daiTestoIn("mailScuola");

                Impiegato::InizializzaDatiPersonali(nome,cognome,fotoID, mansione, mail);

            }


}

bool Segretario::CambiaFotoProfilo(const string &path) const
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return false;
    filexml f1(SegrFolder+"/NUSegr.xml");
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

bool Segretario::CambiaPassword(const string &newPass) const
{
    string check = checkForbiddenCharacters(newPass);
    if(check != "" || hasSpaceOrTab(newPass)|| newPass.size() < 8)
        return false;
    filexml f1(SegrFolder+"/NUSegr.xml");
    f1.editFiglioText("password",newPass,f1.posNodo("NomeUtente",daiNomeUtente()));
    return f1.salva();
}

bool Segretario::esisteMatricola(const string& matricola) const
{
    filexml f("/studenti/NUStud.xml");

    return f.esisteTesto(matricola);
}

string Segretario::createMatricola() const
{
    Container<filexml> c;
    c.AddFileDaLista("/studenti/NUStud.xml", "schedaPersonale");
    string ms= (c.ultimo())->daiTestoIn("Matricola");
    int m= QString::fromStdString(ms).toInt();
    m++;
    return QString::number(m).toStdString();
}

bool Segretario::esisteNomeUtenteStud(const string &nu) const
{
    filexml f1("/studenti/NUStud.xml");
    if(f1.apriFile()){
        return f1.esisteTesto("NomeUtente",nu);
    }
    return false;
}

string Segretario::InsertNewStud(const string& matricola, const string &nu, const string &pw,const string& cognome,
                                 const string& nome, const string& classe, const string &luogo,int g, int m, int a)
{
    string check = checkInputFormAddStud(matricola, nu, pw, cognome, nome,classe, luogo, g,m,a);
    if(check != "")
        return check;
    check = insertNewStudMatricola(matricola, nu);
    if(check != "")
        return check;
    check = EditStudCognome(matricola, cognome);
    if(check != "")
        return check;
    check = EditStudNome(matricola, nome);
    if(check != "")
        return check;
    check = setStudUserPassword(matricola, pw);
    if(check != "")
        return check;
    check = EditStudClasse(matricola, classe);
    if(check != "")
        return check;
    check = EditStudDataNascita(matricola, g,m,a);
    if(check != "")
        return check;
    check = EditStudLuogoNascita(matricola, luogo);
    if(check != "")
        return check;
    return check;
}

string Segretario::insertNewStudMatricola(const string &matricola, const string &nu) const{
    string check = checkForbiddenCharacters(matricola);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(nu);
    if(check != "")
        return check;
    if(!isNumeric(matricola))
        return "Il numero di matricola deve essere numerico.\n "
               "Non è permesso l'uso di lettere o caratteri speciali.";
    if(!esisteMatricola(matricola)){
    filexml f1=filexml::createNewXml("/studenti/Schede Personali/"+matricola+".xml", "schedaPersonale");
    filexml f2("/studenti/NUStud.xml");
    if(f1.apriFile() && f2.apriFile()){
        f1.AggiungiNodo("nomeUtente");
        f1.AggiungiNodo("DatiPersonali");
        f1.AggiungiNodoFiglio("DatiPersonali","Nome");
        f1.AggiungiNodoFiglio("DatiPersonali","Cognome");
        f1.AggiungiNodoFiglio("DatiPersonali","LuogoNascita");
        f1.AggiungiNodoFiglio("DatiPersonali","Matricola");
        f1.AggiungiNodoFiglio("Matricola",matricola, true);
        f1.AggiungiNodoFiglio("DatiPersonali","Classe");


        f1.AggiungiNodoFiglio("DatiPersonali","foto");
        const string& path1 = QDir::currentPath().toStdString()+
                "/../progetto-pao-2017/Database/immagini/FotoProfili/emptyFoto.jpg";
        const string& path2 = "/immagini/FotoProfili/"+nu+".jpg";
        QFile::copy(QString::fromStdString(path1), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                    QString::fromStdString(path2));
        f1.AggiungiNodoFiglio("foto",path2,true);


        f1.AggiungiNodoFiglio("DatiPersonali","DataNascita");

        f2.AggiungiNodoFiglio("NomeUtenti", "studente");
        f2.AggiungiNodoFiglioToLastNode("studente","Matricola");
        f2.AggiungiNodoFiglioToLastNode("studente","NomeUtente");
        f2.AggiungiNodoFiglioToLastNode("studente","password");
        f2.AggiungiNodoFiglioToLastNode("studente","schedaPersonale");
        f2.AggiungiNodoFiglioToLastNode("Matricola",matricola,true);
        f2.AggiungiNodoFiglioToLastNode("schedaPersonale",f1.daiPath(), true);

        if(f1.salva() && f2.salva())
            check =  EditStudNomeUtente(matricola,nu);
        else return "Errore nel salvataggio";


    }
    else check = "Errore con i file";
    }
    else check = "Questa matricola esiste già";
    return check;

}

string Segretario::EditStudCognome(const string &matricola, const string &cognome) const
{
    if(!isNumeric(matricola))
        return "Matricola non valida";
    string check = checkForbiddenCharacters(cognome);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(cognome) || hasSpaceOrTabLast(cognome))
        return "Il cognome non può contenere spazi/tab prima, e/o dopo";
    filexml f1("/studenti/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
    if(f2.apriFile()){
        string c = QString::fromStdString(cognome).toUpper().toStdString();
        if(f2.totNodiFigli("Cognome") == 0)
        f2.AggiungiNodoFiglio("Cognome", c,true);
        else f2.editFiglioText("Cognome",c);
        if(!f2.salva())
            check = "Errore nel salvataggio";
    }
    else check = "Errore nell'apertura del file. E' possibile che tale matricola non esista.";
    return check;
}

string Segretario::EditStudNome(const string &matricola, const string &nome) const
{
    if(!isNumeric(matricola))
        return "Matricola non valida";
    string check = checkForbiddenCharacters(nome);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(nome) || hasSpaceOrTabLast(nome))
        return "Il nome non può contenere spazi/tab prima, e/o dopo";
    filexml f1("/studenti/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
    if(f2.apriFile()){
        string n = QString::fromStdString(nome).toUpper().toStdString();
        if(f2.totNodiFigli("Nome") == 0)
        f2.AggiungiNodoFiglio("Nome", n,true);
        else f2.editFiglioText("Nome",n);
        if(!f2.salva())
            check = "Errore nel salvataggio";
    }
    else check = "Errore nell'apertura del file. E' possibile che tale matricola non esista.";
    return check;
}

string Segretario::EditStudDataNascita(const string &matricola, int g, int m, int a) const
{

    if((g<=0 || m<=0 || a <=0) ||(m==2 && g==29 && a%4 != 0)){
        return "La data di nascita inserita non è corretta";
    }
    if((g>=30 && m==2) || (g>=31 && (m==4 || m==6 || m==9 || m==11 ))){
         return "Il giorno di nascita non è corretto";
    }
    if(!isNumeric(matricola))
        return "Matricola non valida";
    filexml f1("/studenti/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
    if(f2.apriFile()){
        string gio = QString::number(g).toStdString();
        if(g<10)
            gio = "0"+QString::number(g).toStdString();
        string me = QString::number(m).toStdString();
        if(m<10)
            me = "0"+QString::number(m).toStdString();
        const string& data = gio +"/"+me+"/"+QString::number(a).toStdString();
        if(f2.totNodiFigli("DataNascita") == 0)
        f2.AggiungiNodoFiglio("DataNascita",data,true);
        else f2.editFiglioText("DataNascita",data);
        if(f2.salva())
            return "";
    }
    return "Errore con i file";
}

string Segretario::EditStudLuogoNascita(const string &matricola, const string &luogo) const
{
    if(!isNumeric(matricola))
        return "Matricola non valida";
    string check = checkForbiddenCharacters(luogo);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(luogo) || hasSpaceOrTabLast(luogo))
        return "Il luogo di nascita non può contenere spazi/tab prima, e/o dopo";
    filexml f1("/studenti/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
    if(f2.apriFile()){
        string l = QString::fromStdString(luogo).toUpper().toStdString();
        if(f2.totNodiFigli("LuogoNascita") == 0)
        f2.AggiungiNodoFiglio("LuogoNascita",l,true);
        else f2.editFiglioText("LuogoNascita",l);
        if(!f2.salva())
            check = "Errore nel salvataggio";
    }
    else check = "Errore nell'apertura del file. E' possibile che tale matricola non esista.";
    return check;
}

string Segretario::EditStudClasse(const string& matricola, const string& nuovaclasse) const
{
    if(!isNumeric(matricola))
        return "Matricola non corretta";
    filexml f1("/studenti/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
    filexml f3("/studenti/Classi/TutteLeClassi.xml");
    if(f2.apriFile() && f3.esisteTesto("nome",nuovaclasse) && !f2.esisteTesto("Classe", nuovaclasse)){
        if(f2.totNodiFigli("Classe") == 0)
        f2.AggiungiNodoFiglio("Classe",nuovaclasse,true);
        else{
            const string& classe = f2.daiTestoIn("Classe");
            filexml f4(f3.daiTestoIn("riferimentoFile",f3.posNodo("nome",classe)));
            f4.EliminaNodo("NomeUtente",f1.daiTestoIn("NomeUtente", f1.posNodo("studente",matricola)));
            f4.salva();
            f2.editFiglioText("Classe",nuovaclasse);
        }
        filexml f4(f3.daiTestoIn("riferimentoFile",f3.posNodo("nome",nuovaclasse)));
        f4.AggiungiNodoFiglio("Alunni","NomeUtente");
        f4.AggiungiNodoFiglioToLastNode("NomeUtente",f2.daiTestoIn("nomeUtente"),true);
        if(f2.salva() && f4.salva())
            return "";
        return "Errore nel salvataggio";
    }
    return "Errore con i file. E' possibile che:\n"
           "-Lo studente non esiste"
           "-Lo studente è già in questa classe"
           "-La classe non esiste";
}

string Segretario::EditStudNomeUtente(const string &matricola, const string &nu) const
{
    if(!isNumeric(matricola))
        return "Matricola non valida";
    string check = checkForbiddenCharacters(nu);
    if(check != "")
        return check;
    if(hasSpaceOrTab(nu))
        return "Non è consentito il carattere di spaziatura o tab";
    filexml f1("/studenti/NUStud.xml");
    if(f1.apriFile()){
        if(!esisteNomeUtenteStud(nu)){
            filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
            if(f2.apriFile()){
                f1.AggiungiNodoFiglio("NomeUtente",f1.posNodo("Matricola", matricola),nu,true);
                f2.AggiungiNodoFiglio("nomeUtente",nu,true);
                if(f1.salva()&& f2.salva())
                    return "";
                }
            return "Scheda personale dello studente non trovata";
        }
        return "Questo nome utente esiste già";
    }
    return "Errore con i file";
}

string Segretario::checkInputFormAddStud(const string &matricola, const string &nu, const string& pw,
                                         const string &cognome, const string &nome,const string &classe,
                                         const string& luogo, int g, int m, int a)
{
    //-----Classe-----------
    filexml f3("/studenti/Classi/TutteLeClassi.xml");
    if(!f3.apriFile())
        return "Errore con i file";
    if(!f3.esisteTesto("nome",classe))
        return "Classe inesistente";
    //-----Password---------
    string check = checkForbiddenCharacters(pw);
    if(check != "")
        return check;
    if(hasSpaceOrTab(pw))
        return "Non è consentito il carattere di spaziatura o tab nella password";
   //-----Check matricola-------
    if(!isNumeric(matricola))
        return "Il numero di matricola deve essere numerico.\n "
               "Non è permesso l'uso di lettere o caratteri speciali.";
    if(esisteMatricola(matricola))
        return "Questa matricola esiste già";
    //-----------Cognome---------
    check = checkForbiddenCharacters(cognome);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(cognome) || hasSpaceOrTabLast(cognome))
        return "Il cognome non può contenere spazi/tab prima, o dopo";
    //-----------Nome---------
    check = checkForbiddenCharacters(nome);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(nome) || hasSpaceOrTabLast(nome))
        return "Il nome non può contenere spazi/tab prima, e/o dopo";
    //--------Nome Utente----
    check = checkForbiddenCharacters(nu);
    if(check != "")
        return check;
    if(hasSpaceOrTab(nu))
        return "Non è consentito il carattere di spaziatura o tab nel nome utente";
    if(esisteNomeUtenteStud(nu))
        return "Questo nome utente esiste già";
    //-------Luogo di Nascita----
    check = checkForbiddenCharacters(luogo);
    if(check != "")
        return check;
    if(hasSpaceOrTabFirst(luogo) || hasSpaceOrTabLast(luogo))
        return "Il luogo di nascita non può contenere spazi/tab prima, o dopo";
    //-----------Data di nascita--------
    if((g<=0 || m<=0 || a <=0) ||(m==2 && g==29 && a%4 != 0)){
        return "La data di nascita inserita non è corretta";
    }
    if((g>=30 && m==2) || (g>=31 && (m==4 || m==6 || m==9 || m==11 ))){
         return "Il giorno di nascita non è corretto";
    }
    return check;
}

string Segretario::setStudUserPassword(const string& matricola, const string& pw) const
{
    string check = checkForbiddenCharacters(pw);
    if(check != "")
        return check;
    if(hasSpaceOrTab(pw))
        return "Non è consentito il carattere di spaziatura o tab";
    filexml f1("/studenti/NUStud.xml");
    if(f1.apriFile()){
        f1.AggiungiNodoFiglio("password",f1.posNodo("Matricola", matricola), pw, true);
        if(f1.salva())
            return "";
        return "Errore nel salvataggio";
    }
    return  "Errore con i file";
}

string Segretario::CreateStudPassword(const string &nome, const string &cognome, int anno) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != ""|| hasSpaceOrTabLast(nome) || hasSpaceOrTabFirst(nome))
        return "";
    check = checkForbiddenCharacters(cognome);
        if(check != "" || anno <= 0 || hasSpaceOrTabLast(cognome)|| hasSpaceOrTabFirst(nome))
            return "";
    if(nome.size() < 2 || cognome.size() <2)
        return "";
    string n = QString::fromStdString(nome).toLower().toStdString();
    string c = QString::fromStdString(cognome).toLower().toStdString();
    return n.substr(0,2)+c.substr(0,2)+QString::number(anno).toStdString();
}

vector<string> Segretario::searchForStudent(const string &keyword) const
{
    Container<filexml> c; vector<string> v;
    c.AddFileDaLista("/studenti/NUStud.xml","schedaPersonale");
    for(Container<filexml>:: Iteratore it = c.begin(); it != c.end(); ++it){
        if((*it).esisteTesto(keyword))
            v.push_back((*it).daiTestoIn("Matricola"));
    }
    return v;
}


bool Segretario::removeStudente(const string &matricola)
{
    filexml f1("/studenti/NUStud.xml");
    if(f1.esisteTesto("Matricola",matricola)){
        filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
        filexml f3("/studenti/Classi/TutteLeClassi.xml");
        filexml f4(f3.daiTestoIn("riferimentoFile", f3.posNodo("classe",f2.daiTestoIn("Classe"))));
        const string& nu = f2.daiTestoIn("nomeUtente");

        if(QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
           QString::fromStdString(f2.daiTestoIn("foto"))) &&
          QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+
          QString::fromStdString(f2.daiPath()))){
            f4.EliminaNodo("NomeUtente",nu);
            f1.EliminaNodo("studente", matricola,"NomeUtenti",0);
            return f1.salva() && f4.salva();
        }
    }
    return false;
}

string Segretario::CreateStudNomeUtenteFromNomeCognome(const string& nome, const string& cognome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != ""|| hasSpaceOrTabLast(nome) || hasSpaceOrTabFirst(nome))
        return "";
    check = checkForbiddenCharacters(cognome);
        if(check != "" || hasSpaceOrTabLast(cognome)|| hasSpaceOrTabFirst(cognome))
            return "";
    if(nome.size() < 2 || cognome.size() <2)
        return "";
    string nu;
    string n = QString::fromStdString(nome).toLower().toStdString();
    string c = QString::fromStdString(cognome).toLower().toStdString();
    if(cognome.size()<4)
    nu = n.substr(0,2)+c.substr(0,c.size());
    else
        nu = n.substr(0,2)+c.substr(0,3);
    filexml f("/studenti/NUStud.xml");

    nu = nu+QString::number(f.totNodi(nu)).toStdString();
    return nu;
}
