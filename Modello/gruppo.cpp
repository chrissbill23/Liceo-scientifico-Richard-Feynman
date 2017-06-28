#include "gruppo.h"
#include <QFile>
#include <QDir>

Gruppo::Gruppo(string pathDB): file(pathDB)
{
    if(file.apriFile()){
        int tot=file.totNodi("post");
        for(int i=0; i<tot;++i){
            v.push_back(file.daiTestoIn("post",i));
        }
    }
}

Gruppo::Gruppo()
{

}

string Gruppo::daiNome() const
{
    return file.daiTestoIn("nomeGruppo");
}

int Gruppo::totPost() const
{
    return v.size();
}

int Gruppo::totRisposteAPost(unsigned int i) const
{
    return v[i].totRisposte();
}

string Gruppo::daiDataPost(unsigned int i) const
{
    if(i < v.size())
       return v[i].data;
    return "Errore Nessun Post trovato";
}

string Gruppo::daiAutorePost(unsigned int i) const
{
    if(i < v.size())
       return v[i].autore;
    return "Errore Nessun Post trovato";
}

string Gruppo::daiTitoloPost(unsigned int i) const
{
    if(i < v.size())
       return v[i].titolo;
    return "Errore Nessun Post trovato";
}

string Gruppo::daiTestoPost(unsigned int i) const
{
    if(i < v.size())
       return v[i].testo;
    return "Errore Nessun Post trovato";
}

string Gruppo::daiDataRisposta(unsigned int i, unsigned int j) const
{
    return (i < v.size()) ? v[i].daiDataRisposta(j) : "";
}

string Gruppo::daiAutoreRisposta(unsigned int i, unsigned int j) const
{
    return (i < v.size()) ?v[i].daiAutoreRisposta(j) : "";
}

string Gruppo::daiTestoRisposta(unsigned int i, unsigned int j) const
{
    return (i < v.size()) ? v[i].daiTestoRisposta(j) : "";
}

list<string> Gruppo::daiRispostaAPost(unsigned int i, int j) const
{
    list<string>l;
    if(i<v.size() && j<v[i].totRisposte()){
        l.push_back(v[i].daiDataRisposta(j));
        l.push_back(v[i].daiAutoreRisposta(j));
        l.push_back(v[i].daiTestoRisposta(j));
    }
    return l;
}

list<string> Gruppo::daiMembri() const
{
    return file.daiTestoDiNodi("nomeUtente");
}

bool Gruppo::addMember(const string &nUtente)
{
    file.AggiungiNodoFiglioToLastNode("membri","nomeUtente");
    file.AggiungiNodoFiglioToLastNode("nomeUtente",nUtente,true);
    return file.salva();
}

bool Gruppo::addPost(const string &data, const string &autore, const string &titolo, const string &testo)
{
    int tot = file.totNodi("post");
    string path = "/Gruppi/AttivitGruppi/"+daiNome()+"post"+( QString::number(tot+1)+".xml").toStdString();
    filexml f2 = filexml::createNewXml(path,"post");
    if(f2.apriFile()){
    file.AggiungiNodoFiglio("TuttiIPost","post");
    file.AggiungiNodoFiglioToLastNode("post", path,true);

    f2.AggiungiNodoFiglio("post","data");
    f2.AggiungiNodoFiglioToLastNode("data",data,true);
    f2.AggiungiNodoFiglio("post","autore");
    f2.AggiungiNodoFiglioToLastNode("autore",autore,true);
    f2.AggiungiNodoFiglio("post","titolo");
    f2.AggiungiNodoFiglioToLastNode("titolo",titolo,true);
    f2.AggiungiNodoFiglio("post","testo");
    f2.AggiungiNodoFiglioToLastNode("testo",testo,true);

    if(f2.salva()){
    v.push_back(Post(path));
    return file.salva();
    }
    }
    return false;
}

bool Gruppo::addRispostaToPost(unsigned int i, const string &data, const string &utente, const string &testo)
{
    return (v.size() > i) ? v[i].addRisposta(data, utente, testo) : false;
}

vector<int> Gruppo::daiIndexesPostOf(const string & membro) const
{
    vector<int> temp;
    int tot = v.size();
    for(int i = 0; i < tot; ++i){
        if(v[i].autore == membro)
            temp.push_back(i);
    }
    return temp;
}

vector<int> Gruppo::daiIndexesPostWithAnswOf(const string &membro) const
{
    vector<int> temp;
    int tot = v.size();
    for(int i = 0; i < tot; ++i){
        if(v[i].IsThereAnswOf(membro))
            temp.push_back(i);
    }
    return temp;
}

vector<int> Gruppo::searchPost(const string &keyword) const
{
    vector<int> temp;
    int tot = v.size();
    for(int i = 0; i < tot; ++i){
        const QString& key = QString::fromStdString(keyword);
        const QString& memb = QString::fromStdString(v[i].autore);
        const QString& tit = QString::fromStdString(v[i].titolo);
        const QString& text = QString::fromStdString(v[i].testo);
        if(memb.indexOf(key,0,Qt::CaseInsensitive) != -1 ||
           tit.indexOf(key,0,Qt::CaseInsensitive) != -1 ||
           text.indexOf(key,0,Qt::CaseInsensitive) != -1)
            temp.push_back(i);
    }
    return temp;
}

bool Gruppo::removeMember(const string &member)
{
    int pos = file.posNodo("nomeUtente",member);
    if(pos != -1){
    file.EliminaNodo("nomeUtente", pos);
    return file.salva();
    }
    return false;
}

bool Gruppo::removePost(unsigned int i)
{
    if(v.size() > i){
    const QString& path = QDir::currentPath()+"/../progetto-pao-2017/Database"+
            QString::fromStdString(v[i].pathtoDb);
    if(QFile::remove(path)){
        file.EliminaNodo("post",v[i].pathtoDb);
        v.erase(v.begin()+i);
        return file.salva();
    }
    }
    return false;
}

const filexml &Gruppo::InfoGruppo() const
{
    return file;
}

Gruppo::Post::Post(const string& path): pathtoDb(path)
{
    filexml f(path);
    if(f.apriFile()){
        data=f.daiTestoIn("data");
        autore=f.daiTestoIn("autore");
        titolo=f.daiTestoIn("titolo");
        testo=f.daiTestoIn("testo");
        int tot= f.totNodi("risposta");
        for(int i=0; i<tot; ++i)
            v.push_back(risposta(f.daiTestoIn("dataR",i),
                                 f.daiTestoIn("membro",i),
                                 f.daiTestoIn("testoR",i)));
    }
}

int Gruppo::Post::totRisposte() const
{
    return v.size();
}

string Gruppo::Post::daiDataRisposta(unsigned int i) const
{
    return v[i].data;
}

string Gruppo::Post::daiAutoreRisposta(unsigned int i) const
{
    return v[i].membro;
}

string Gruppo::Post::daiTestoRisposta(unsigned int i) const
{
    return v[i].testo;
}

bool Gruppo::Post::IsThereAnswOf(const string &membro) const
{
    for(unsigned int i = 0; i < v.size(); ++i)
        if(v[i].membro == membro)
            return true;
    return false;
}

bool Gruppo::Post::addRisposta(const string &data, const string &utente, const string &testo)
{
    filexml f(pathtoDb);
    if(f.apriFile()){
        f.AggiungiNodoFiglio("post","risposta");
        f.AggiungiNodoFiglioToLastNode("risposta","dataR");
        f.AggiungiNodoFiglioToLastNode("dataR",data,true);
        f.AggiungiNodoFiglioToLastNode("risposta","membro");
        f.AggiungiNodoFiglioToLastNode("membro",utente,true);
        f.AggiungiNodoFiglioToLastNode("risposta","testoR");
        f.AggiungiNodoFiglioToLastNode("testoR",testo,true);
        v.push_back(risposta(data,utente,testo));
        return f.salva();
    }
    return false;
}

Gruppo::Post::risposta::risposta(const string &d, const string& m, const string &t): data(d),membro(m), testo(t){}
