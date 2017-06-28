#include "studente.h"
#include "container.h"
#include <QDir>

string Studente::StudFolder = "/studenti";

Studente::Studente(string NomeUtente): Utente(NomeUtente), matricola(""), classe(""){
}

Studente *Studente::clone() const
{
    return new Studente(*this);
}

bool Studente::esiste() const
{
    filexml f(StudFolder+"/NUStud.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente());
}

void Studente::InizializzaDatiPersonali()
{
    filexml f1(StudFolder+"/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",Utente::daiNomeUtente())));
        if(f2.apriFile()){
                string nome = f2.daiTestoIn("Nome");
                string cognome=f2.daiTestoIn("Cognome");
                matricola=f2.daiTestoIn("Matricola");
                classe=f2.daiTestoIn("Classe");
                string fotoID=QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+f2.daiTestoIn("foto");

                Utente::InizializzaDatiPersonali(nome,cognome, fotoID);
        }

}

bool Studente::VerificaPassword(const string &p) const
{
    filexml f(StudFolder+"/NUStud.xml");
    return f.apriFile() && f.akinTo("studente", Utente::daiNomeUtente(), p);
}

bool Studente::CambiaFotoProfilo(const string &path) const
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return false;
    filexml f1(StudFolder+"/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",Utente::daiNomeUtente())));
    if(f2.apriFile()){
        const string& newFoto ="/immagini/FotoProfili/"+daiNomeUtente()+".jpg";
        const string& path2 = QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+newFoto;
        if (QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+QString::fromStdString(f2.daiTestoIn("foto")))
            && QFile::copy(QString::fromStdString(path), QString::fromStdString(path2))){
            f2.editFiglioText("foto",newFoto);
            return f2.salva();
        }
    }
    return false;
}

bool Studente::CambiaPassword(const string &newPass) const
{
    string check = checkForbiddenCharacters(newPass);
    if(check != ""||hasSpaceOrTab(newPass) || newPass.size() < 8)
        return false;
    filexml f1(StudFolder+"/NUStud.xml");
    f1.editFiglioText("password",newPass,f1.posNodo("Matricola",matricola));
    return f1.salva();

}

string Studente::getGroupMemberFotoProfile(const string &nu) const
{
    filexml f1(StudFolder+"/NUStud.xml");
    filexml f2(f1.daiTestoIn("schedaPersonale",f1.posNodo("NomeUtente",nu)));
        if(f2.apriFile()){
                return QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+f2.daiTestoIn("foto");
        }
        return GruppoUser::getGroupMemberFotoProfile(nu);
}

list<string> Studente::DaiDatiPersonali() const
{
    list<string> l;
    l.push_back(Utente::daiCognome());
    l.push_back(Utente::daiNome());
    l.push_back(matricola);
    l.push_back(classe);
    return l;
}

list<string> Studente::daiMaterieInsegnate()const
{
    Container<filexml> contenitore;
    contenitore.AddFileDaLista(StudFolder+"/Classi/TutteLeClassi.xml", "riferimentoFile");
    list<string> l;
    for(Container<filexml>::Iteratore it= contenitore.begin(); it != contenitore.end(); ++it){
        if(it->esisteTesto(Utente::daiNomeUtente())){
            list<string> l1=it->daiTestoDiNodi("NomeMateria");
            l.insert(l.end(),l1.begin(),l1.end());
        }
    }
    return l;
}


vector<string> Studente::giveCompitiTitle() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("titolo",classe,"compito");
}

vector<string> Studente::giveCompitiDates() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("data",classe,"compito");
}

vector<string> Studente::codiciCompiti() const
{
    filexml f1("/Professori/compiti/Info.xml");
    return f1.daiTestoDiNodiVect("codiceCompito",classe,"compito");
}


