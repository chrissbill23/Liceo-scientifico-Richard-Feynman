#include "gruppouser.h"
#include "container.h"
#include <QDir>



void GruppoUser::InitialiseGruppi()
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    Container<filexml> contenitore;
    contenitore.AddFileDaLista(f, "riferimentoFile");
    if(ImieiGruppi.size() > 0)
        ImieiGruppi.clear();
    for(Container<filexml>::Iteratore it= contenitore.begin(); it != contenitore.end(); ++it){
        if(it->esisteTesto(Utente::daiNomeUtente())){
            string nomeGr = it->daiTestoIn("nomeGruppo");
            ImieiGruppi[nomeGr] = Gruppo(f.daiTestoIn("riferimentoFile", f.posNodo("nome",nomeGr)));
        }
    }
}

void GruppoUser::setGruppi(const map<string, Gruppo> group)
{
    if(ImieiGruppi.size() > 0)
        ImieiGruppi.clear();
    ImieiGruppi = group;
}

list<string> GruppoUser::CategorieGruppo() const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    list<string> l;
    if(f.apriFile())
        l = f.daiTestoDiNodi("nomeCategoria");
    return l;
}

list<string> GruppoUser::Gruppi()
{
    list<string> l;
    if(ImieiGruppi.size() == 0)
        InitialiseGruppi();
    for(map<string,Gruppo>::const_iterator it = ImieiGruppi.begin(); it != ImieiGruppi.end(); ++it){
            l.push_back(it->first);
    }
    return l;
}

int GruppoUser::totMygroups() const
{
    return ImieiGruppi.size();
}

list<string> GruppoUser::GroupsInCath(const string &cathegory) const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    list<string> l;
    if(f.apriFile()){
        l = f.daiTestoDiNodi("nome");
        if(cathegory != ""){
        list<string> l2;
        for(list<string>:: const_iterator it = l.begin(); it != l.end(); ++it)
            if(f.akinTo("gruppo",*it, cathegory))
            l2.push_back(*it);
        return l2;
        }
    }
    return l;
}

list<string> GruppoUser::esisteGruppo(const string &nome) const
{
    list<string> l;
    if( nome != ""){
        filexml f("/Gruppi/TuttiIGruppi.xml");
           if(f.apriFile()){
               l = f.daiTextContainingText("nome",nome);

           }
    }
    return l;
}

list<string> GruppoUser::GroupMembers(const string &nomeGroup) const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    list<string> l;
    if(f.apriFile()){
         l = Gruppo (f.daiTestoIn("riferimentoFile", f.posNodo("nome",nomeGroup))).daiMembri();
    }
    return l;
}

string GruppoUser::getGroupMemberFotoProfile(const string &nu) const
{
    nu.size();
    return (QDir::currentPath()+"/../progetto-pao-2017/Database" +
            "/immagini/FotoProfili/emptyFoto.jpg").toStdString();
}

int GruppoUser::totPostGruppo(const string &nome) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    return it != ImieiGruppi.end() ? (it->second).totPost(): 0;
}

bool GruppoUser::removeMeFromgroup(const string &group)
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    if(f.apriFile()){
        map<string,Gruppo>::iterator it = ImieiGruppi.find(group);
        if(it != ImieiGruppi.end()){
          ImieiGruppi.erase(it);
          return (Gruppo(f.daiTestoIn("riferimentoFile", f.posNodo("nome",group)))).removeMember(daiNomeUtente());
        }
    }
    return false;
}

list<string> GruppoUser::daiRispostaSuPost(const string &gruppo, unsigned int i, unsigned int j) const
{
    list<string> l;
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(gruppo);
    if(it != ImieiGruppi.end())
     l = (it->second).daiRispostaAPost(i,j);
    return l;
}

string GruppoUser::daiTestoPostGroup(const string &nome, unsigned int i) const
{

    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    return it != ImieiGruppi.end() ? (it->second).daiTestoPost(i) : "";
}

string GruppoUser::daiPostAutore(const string &nome, unsigned int i) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    return it != ImieiGruppi.end() ? (it->second).daiAutorePost(i) : "";
}

string GruppoUser::daiPostTitolo(const string &nome, unsigned int i) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    return it != ImieiGruppi.end() ? (it->second).daiTitoloPost(i) : "";
}

string GruppoUser::daiPostData(const string &nome, unsigned int i) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    return it != ImieiGruppi.end() ? (it->second).daiDataPost(i) : "";
}

vector<string> GruppoUser::daiInfoPostGroup(const string &nome, unsigned int i) const
{
    vector<string> v;
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nome);
    if(it != ImieiGruppi.end()){
        v.push_back((it->second).daiDataPost(i));
        v.push_back((it->second).daiAutorePost(i));
        v.push_back((it->second).daiTitoloPost(i));
    }
    return v;
}

int GruppoUser::totRisposteAPost(const string &nomegruppo, unsigned int i) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(nomegruppo);
    return it != ImieiGruppi.end() ? (it->second).totRisposteAPost(i): 0;
}

bool GruppoUser::IscriviMiAGroup(const string &groupName)
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    if(f.apriFile() && f.esisteTesto(groupName)){
       ImieiGruppi[groupName] = (Gruppo(f.daiTestoIn("riferimentoFile", f.posNodo("nome",groupName))));
        return (ImieiGruppi.find(groupName)->second).addMember(daiNomeUtente());
    }
    return false;
}

vector<int> GruppoUser::MyPost(const string &groupName) const
{
    vector<int> v;
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    if(it != ImieiGruppi.end()){
      v = (it->second).daiIndexesPostOf(daiNomeUtente());
    }
    return v;
}

vector<int> GruppoUser::PostIAnswered(const string &groupName) const
{
    vector<int> v;
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    if(it != ImieiGruppi.end()){
      v = (it->second).daiIndexesPostWithAnswOf(daiNomeUtente());
    }
    return v;
}

vector<int> GruppoUser::SearchPost(const string &groupName, const string &keyword) const
{
    vector<int> v;
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    if(it != ImieiGruppi.end()){
      v = (it->second).searchPost(keyword);
    }
    return v;
}

string GruppoUser::daiGroupCateg(const string &groupName) const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    return f.daiTestoIn("categoria",f.posNodo("gruppo",groupName));
}

string GruppoUser::daiGroupDescr(const string &groupName) const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    filexml file(f.daiTestoIn("riferimentoFile", f.posNodo("nome",groupName)));
    return file.daiTestoIn("descrizione");
}

string GruppoUser::daiDataRisposta(const string &groupName, unsigned int i, unsigned int j) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    return it != ImieiGruppi.end() ? (it->second).daiDataRisposta(i,j):"";
}

string GruppoUser::daiAutoreRisposta(const string &groupName, unsigned int i, unsigned int j) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    return it != ImieiGruppi.end() ? (it->second).daiAutoreRisposta(i,j):"";
}

string GruppoUser::daiTestoRisposta(const string &groupName, unsigned int i, unsigned int j) const
{
    map<string,Gruppo>::const_iterator it = ImieiGruppi.find(groupName);
    return it != ImieiGruppi.end() ? (it->second).daiTestoRisposta(i,j) : "";
}

string GruppoUser::addPost(const string &groupName, const string& data, const string &titolo, const string &testo)
{
    string check = checkForbiddenCharacters(data);
    if(check == ""){
        if(HasNoChar(data))
            return "la data non puo' essere vuota";
        check = checkForbiddenCharacters(titolo);
            if(check == ""){
                if(HasNoChar(titolo))
                    return "il titolo non puo' essere vuoto";
                check = checkForbiddenCharacters(testo);
                if(check == ""){
                    if(HasNoChar(testo))
                        return "Il testo non puo' essere vuoto";
                    map<string,Gruppo>::iterator it = ImieiGruppi.find(groupName);
                    if(it != ImieiGruppi.end() && (it->second).addPost(data, daiNomeUtente(),titolo,testo))
                     return "";
                    else check = "Oops, non sono riuscito a pubblicare il post";
            }
        }
    }
    return check;
}

string GruppoUser::addRispostaToPost(unsigned int i, const string &groupName, const string &data, const string &testo)
{
    string check = checkForbiddenCharacters(data);
    if(check != ""){
        return check;
    }
    check = checkForbiddenCharacters(testo);
        if(check != ""){
            return check;
        }
    if(HasNoChar(data))
        return "la data non puo' essere vuota";
    if(HasNoChar(testo))
        return "il testo non puo' essere vuoto";
    map<string,Gruppo>::iterator it = ImieiGruppi.find(groupName);
    if(it != ImieiGruppi.end() && (it->second).addRispostaToPost(i, data, daiNomeUtente(),testo))
        return "";
    return "Oops, non sono riuscito a pubblicare la risposta" ;

}

bool GruppoUser::removePost(const string &groupName, unsigned int i)
{
    map<string,Gruppo>::iterator it = ImieiGruppi.find(groupName);
    return it != ImieiGruppi.end() && (it->second).removePost(i);
}

filexml GruppoUser::giveSchedaGruppo(const string &groupName) const
{

    filexml f("/Gruppi/TuttiIGruppi.xml");
    filexml file(f.daiTestoIn("riferimentoFile", f.posNodo("nome",groupName)));
    return file;
}


bool GruppoUser::isIscrittoToGroup(const string &groupName) const
{
    return (ImieiGruppi.find(groupName) != ImieiGruppi.end());
}
