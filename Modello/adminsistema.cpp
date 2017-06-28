#include "adminsistema.h"
#include "filexml.h"
#include "container.h"
#include <QFile>
#include <QDir>

string AdminSistema::pathDB="/Admin";

void AdminSistema::InitialiseGruppi()
{
    map<string, Gruppo> g;
    filexml f("/Gruppi/TuttiIGruppi.xml");
    Container<filexml> contenitore;
    contenitore.AddFileDaLista(f, "riferimentoFile");
    if(contenitore.size() != totMygroups()){
    for(Container<filexml>::Iteratore it = contenitore.begin(); it != contenitore.end(); ++it){
            const string& nomeGr = it->daiTestoIn("nomeGruppo");
            g[nomeGr] = Gruppo(f.daiTestoIn("riferimentoFile", f.posNodo("nome",nomeGr)));
    }
    setGruppi(g);
    }
}

string AdminSistema::addGroupCathegory(const string &name) const
{
    string check = checkForbiddenCharacters(name);
    if(check != "")
        return check;
        if(HasNoChar(name))
            return "il nome della categoria non puo' essere vuoto";

    filexml f("/Gruppi/TuttiIGruppi.xml");
    if(f.apriFile()){
        if(f.daiTextContainingText("nomeCategoria", name).size() > 0)
            return "Questo gruppo esiste già";
        f.AggiungiNodoFiglio("categorie","nomeCategoria");
        f.AggiungiNodoFiglioToLastNode("nomeCategoria",name,true);
        if(f.salva())
            return "";
    }
    return "Errore con i file";
}

string AdminSistema::removeGroupCathegory(const string &name) const
{
    filexml f("/Gruppi/TuttiIGruppi.xml");
    if(f.apriFile()){
        if(f.daiTextContainingText("categoria", name).size() > 0)
            return "Impossibile rimuovere la categoria. Ci sono gruppi in questa categoria";
        f.EliminaNodo("nomeCategoria",name);
        if(f.salva())
            return "";
    }
    return "Errore con i file";
}

string AdminSistema::addNewGroup(const string &name, const string& Descr, const string &categoria) const
{
    string check = checkForbiddenCharacters(name);
    if(check == ""){
        if(HasNoChar(name))
            return "il nome del gruppo non puo' essere vuoto";
        check = checkForbiddenCharacters(Descr);
            if(check == ""){
                if(HasNoChar(Descr))
                    return "La descrizione non puo' essere vuota";
                check = checkForbiddenCharacters(categoria);
                if(check == ""){
                    if(HasNoChar(categoria))
                        return "La categoria non puo' essere vuota";

                    filexml f("/Gruppi/TuttiIGruppi.xml");
                    if(f.apriFile()){
                        if(!f.esisteTesto("nomeCategoria", categoria))
                            return "La categoria scelta non esiste";
                        if(f.daiTextContainingText("nome",name).size() > 0)
                            return "Questo gruppo esite già";
                        const string& path ="/Gruppi/"+name+".xml";
                        filexml f2 = filexml::createNewXml(path,"gruppo");
                        if(f2.apriFile()){
                            f2.AggiungiNodo("nomeGruppo");
                            f2.AggiungiNodo("descrizione");
                            f2.AggiungiNodo("membri");
                            f2.AggiungiNodo("TuttiIPost");
                            f2.AggiungiNodoFiglio("nomeGruppo",name,true);
                            f2.AggiungiNodoFiglio("descrizione",Descr,true);

                            f2.AggiungiNodoFiglioToLastNode("gruppo","nome");
                            f2.AggiungiNodoFiglioToLastNode("nome",name,true);
                            f2.AggiungiNodoFiglioToLastNode("gruppo","riferimentoFile");
                            f2.AggiungiNodoFiglioToLastNode("riferimentoFile",path,true);
                            f2.AggiungiNodoFiglioToLastNode("gruppo","categoria");
                            f2.AggiungiNodoFiglioToLastNode("categoria",categoria,true);

                            f.AggiungiNodo("gruppo");
                            f.AggiungiNodoFiglioToLastNode("gruppo", "nome");
                            f.AggiungiNodoFiglioToLastNode("gruppo", "riferimentoFile");
                            f.AggiungiNodoFiglioToLastNode("gruppo", "categoria");
                            f.AggiungiNodoFiglioToLastNode("nome", name,true);
                            f.AggiungiNodoFiglioToLastNode("riferimentoFile", path, true);
                            f.AggiungiNodoFiglioToLastNode("categoria", categoria,true);
                        if(f2.salva() && f.salva())
                            return "";
                        }
                    }
                    return "Errore con i file";
            }
        }
    }
    return check;

}

bool AdminSistema::editGroup(const string& oldName, const string &name, const string &Descr, const string &categoria) const
{
    string check = checkForbiddenCharacters(name);
    if(check == ""){
        if(HasNoChar(name))
            return "il nome del gruppo non puo' essere vuoto";
        check = checkForbiddenCharacters(Descr);
            if(check == ""){
                if(HasNoChar(Descr))
                    return "La descrizione non puo' essere vuota";
                check = checkForbiddenCharacters(categoria);
                if(check == ""){
                    if(HasNoChar(categoria))
                        return "La categoria non puo' essere vuota";

                    filexml f("/Gruppi/TuttiIGruppi.xml");
                    if(f.apriFile()){
                        if(!f.esisteTesto("nomeCategoria", categoria))
                            return false;
                        if(f.daiTextContainingText("nome",oldName).size() == 0)
                            return false;
                        filexml f2(f.daiTestoIn("riferimentoFile", f.posNodo("nome",oldName)));
                        if(f2.apriFile() && (QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database" +
                                                           QString::fromStdString(f2.daiPath())))){
                            f2.editFiglioText("nomeGruppo",name);
                            f2.editFiglioText("descrizione",Descr);

                            int pos = f.posNodo("gruppo",oldName);
                            f.editFiglioText("nome", name,pos);
                            f.editFiglioText("categoria",categoria, pos);
                            f.editFiglioText("riferimentoFile","/Gruppi/"+name+".xml",pos);

                            int tot = f2.totNodi("post");
                            for(int i = 0; i < tot; ++i){
                                QString pos = QString::fromStdString(f2.daiTestoIn("post",i));
                                filexml f3(pos.toStdString());
                                QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database" +pos);
                                int begin = pos.indexOf(QString::fromStdString(oldName),0);
                                pos = pos.replace(begin,oldName.size(),QString::fromStdString(name));
                                f3.salvaConNome(pos.toStdString());
                                f2.editFiglioText("post",pos.toStdString(),i);
                            }
                        return f2.salvaConNome("/Gruppi/"+name+".xml") && f.salva();
                        }
                    }

            }
        }
    }
    return false;

}

string AdminSistema::removeGroup(const string &name) const
{
    filexml f1("/Gruppi/TuttiIGruppi.xml");
    int pos = f1.posNodo("nome",name);
    filexml f2(f1.daiTestoIn("riferimentoFile", pos));
    if(f2.apriFile()){
        int tot = f2.totNodi("post");

        while( tot > 0){
            const QString& path = QDir::currentPath()+"/../progetto-pao-2017/Database" +
                    QString::fromStdString(f2.daiTestoIn("post",tot-1));
            if(QFile::remove(path))
                --tot;
        }
        if(tot == 0  && QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database" +
                QString::fromStdString(f2.daiPath())) ){
        f1.EliminaNodo("gruppo",pos);
        if(f1.salva())
            return "";
        }
    }
    return "Errore con i file";
}


string AdminSistema::checkInputaddPreside(const string &nomeUtente, const string &pass, const string &Cognome, const string &Nome, const string &dataFineCarriera) const
{
    //------Nome utente---------
    string check = checkForbiddenCharacters(nomeUtente);
    if(check != "")
        return check;
    if(hasSpaceOrTab( nomeUtente))
        return "Il nome utente non può avere caratteri tab o di spaziatura";
    //--------Password------
    check = checkForbiddenCharacters(pass);
    if(check != "")
        return check;
    if(hasSpaceOrTab( pass))
        return "La password non può avere caratteri tab o di spaziatura";
    //------nome---------
    check = checkForbiddenCharacters(Nome);
    if(check != "")
        return check;
    if(hasSpaceOrTabLast(Nome) || hasSpaceOrTabFirst(Nome))
        return "Non è concesso un carattere tab o di spaziatura all'inizio o alla fine del nome";
    //------Cognome---------
    check = checkForbiddenCharacters(Cognome);
    if(check != "")
        return check;
    if(hasSpaceOrTabLast(Cognome) || hasSpaceOrTabFirst(Cognome))
        return "Non è concesso un carattere tab o di spaziatura all'inizio o alla fine del cognome";
    //------Data fine carriera---------
    check = checkForbiddenCharacters(dataFineCarriera);
    if(check != "")
        return check;
    return "";
}

AdminSistema::AdminSistema(const string& nU):Utente(nU){}

bool AdminSistema::VerificaPassword(const string &p) const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return Admin::VerificaPassword(p)&& f.akinTo("admin",daiNomeUtente(), "amministratore sistema");
}

bool AdminSistema::esiste() const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente())&&
            f.akinTo("admin",daiNomeUtente(), "amministratore sistema");
}

string AdminSistema::addPreside(const string &nomeUtente, const string &pass, const string &Cognome, const string &Nome, const string &dataFineCarriera) const
{
    const string& check = checkInputaddPreside(nomeUtente, pass, Cognome, Nome, dataFineCarriera);
    if(check != "")
        return check;

    filexml f("/Presidente/InfoPresid.xml");
    if(f.apriFile()){
        if(f.daiTestoIn("Nome") != "NULL" && f.daiTestoIn("Cognome") != "NULL")
            return "Impossibile aggungere un nuovo presidente senza rimuovere il precedente";
        const string& n = QString::fromStdString(Nome).toUpper().toStdString();
        const string& c = QString::fromStdString(Nome).toUpper().toStdString();
        f.AggiungiNodoFiglio("NomeUtente", nomeUtente,true);
        f.AggiungiNodoFiglio("presidente", "password");
        f.AggiungiNodoFiglio("password", pass,true);
        f.editFiglioText("Nome",n);
        f.editFiglioText("Cognome",c);
        f.editFiglioText("dataFineCarriera", dataFineCarriera);
        if(f.salva())
            return "";
    }
    return "Errore con i file";
}

bool AdminSistema::removePreside()
{
    filexml f("/Presidente/InfoPresid.xml");
    filexml f2("/Messaggi/email.xml");
    if(f.apriFile() && f2.apriFile() && f.totNodiFigli("NomeUtente") > 0){
        const string& mail = f.daiTestoIn("mailScuola");
        int pos = f2.posNodo("mail",mail);
        const string& pathric = f2.daiTestoIn("mailRicevuta", pos);
        const string& pathinv = f2.daiTestoIn("mailInviata", pos);

        filexml f3(pathric);
        filexml f4(pathinv);
        f3.EliminaNodi("mail");
        f4.EliminaNodi("mail");
        f.EliminaNodi(f.daiTestoIn("NomeUtente"));
        f.EliminaNodi("password");
        f.editFiglioText("Nome","NULL");
        f.editFiglioText("Cognome","NULL");
        f.editFiglioText("dataFineCarriera","NULL");
        return f.salva() && f3.salva() && f4.salva();
    }
    return false;
}

