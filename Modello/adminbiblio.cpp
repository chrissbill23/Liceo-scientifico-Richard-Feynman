#include "adminbiblio.h"
#include <QFile>
#include <QDir>

string AdminBiblio::pathDB="/Admin";
int AdminBiblio::maxPrimoPiano = 7;
AdminBiblio::AdminBiblio(const string& nU):Utente(nU),file("/Biblioteca/InfoLibri.xml"){}

bool AdminBiblio::VerificaPassword(const string &p) const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return Admin::VerificaPassword(p)&& f.akinTo("admin",daiNomeUtente(), "amministratore biblioteca");
}

bool AdminBiblio::esiste() const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente())&&
            f.akinTo("admin",daiNomeUtente(), "amministratore biblioteca");;
}

bool AdminBiblio::esisteCategoria(const string& cat) const
{
    filexml f("/Biblioteca/InfoBiblio.xml");
    return f.esisteTesto("nomecategoria",cat);
}

bool AdminBiblio::aggiungiCategoria(const string &nome) const
{
    string check = checkForbiddenCharacters(nome);
    if(check != "" || HasNoChar(nome))
        return false;
    filexml f("/Biblioteca/InfoBiblio.xml");
    f.AggiungiNodoFiglioToLastNode("categorie","nomecategoria");
    f.AggiungiNodoFiglioToLastNode("nomecategoria",nome,true);
    return f.salva();

}

string AdminBiblio::aggiungiNuovoLibro(const string &titolo, const string &descrizione, const string &filePath)
{
    string check = checkForbiddenCharacters(titolo);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(descrizione);
    if(check != "")
        return check;
    check = checkForbiddenCharacters(filePath);
    if(check != "")
        return check;
    if(HasNoChar(titolo))
        return "il titolo non può essere vuoto";
    if(HasNoChar(descrizione))
        return "la descrizione non può essere vuota";
    if(HasNoChar(filePath))
        return "Il percorso al file è vuoto";

    string codiceLibro = QString::number(file.totNodi("libro")).toStdString();
    if(file.esisteTesto("codiceLibro",codiceLibro))
        codiceLibro = codiceLibro+"0";
    string path = "/Biblioteca/libri/libro"+codiceLibro+".pdf";
    if(QFile::copy(QString::fromStdString(filePath), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                   QString::fromStdString(path)) ){
    file.AggiungiNodoFiglioToLastNode("libri","libro");
    file.AggiungiNodoFiglioToLastNode("libro","codiceLibro");
    file.AggiungiNodoFiglioToLastNode("codiceLibro",codiceLibro,true);
    file.AggiungiNodoFiglioToLastNode("libro","titolo");
    file.AggiungiNodoFiglioToLastNode("titolo",titolo,true);
    file.AggiungiNodoFiglioToLastNode("libro","autore");
    file.AggiungiNodoFiglioToLastNode("autore","Non specificato",true);
    file.AggiungiNodoFiglioToLastNode("libro","annoEdizione");
    file.AggiungiNodoFiglioToLastNode("annoEdizione","Non specificato",true);
    file.AggiungiNodoFiglioToLastNode("libro","descrizione");
    file.AggiungiNodoFiglioToLastNode("descrizione",descrizione,true);
    file.AggiungiNodoFiglioToLastNode("libro","percorsoFile");
    file.AggiungiNodoFiglioToLastNode("percorsoFile",path,true);
    file.AggiungiNodoFiglioToLastNode("libro","categorieLibro");
    file.AggiungiNodoFiglioToLastNode("libro","copertina");
    if(file.salva())
        return codiceLibro;
    }

    return "";
}

string AdminBiblio::aggiungiInPrimoPiano(const string &codiceLibro) const
{
    filexml f("/Biblioteca/InfoBiblio.xml");
    int pos = f.posNodo("Biblioteca","libriPrimoPiano");
    if(f.apriFile()){
    if(f.totNodi("libroPrimoPiano") < maxPrimoPiano){
        if(f.esisteTesto("libroPrimoPiano",codiceLibro)){
            return "Questo libro è già in primo piano";
        }
        else{
            f.AggiungiNodoFiglio("libriPrimoPiano",pos,"libroPrimoPiano");
            f.AggiungiNodoFiglioToLastNode("libroPrimoPiano",codiceLibro,true);
            if(f.salva())
                return "";
            return "Errore fatale nel salvataggio";
        }

    }
    else return "Hai raggiunto il numero massimo di libri in primo piano";
    }
    return "Errore nell'apertura del file";
}

bool AdminBiblio::rimuoviLibroDaPrimoPiano(const string &codiceLibro) const
{
    filexml f("/Biblioteca/InfoBiblio.xml");
    f.EliminaNodo("libroPrimoPiano",codiceLibro, "libriPrimoPiano",f.posNodo("Biblioteca","libriPrimoPiano"));
    return f.salva();
}

bool AdminBiblio::aggiungiCategoriaAlibro(const string &codiceLibro, const string &categoria)
{
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
        file.AggiungiNodoFiglio("categorieLibro",pos,"categoria");
        int tot = file.totNodiFigli("categorieLibro", pos,"categoria");
        file.AggiungiNodoFiglio("categorieLibro",pos,"categoria",tot-1,categoria,true);
    return file.salva();
    }
    return false;

}

bool AdminBiblio::ModificaTitololibro(const string &codiceLibro, const string &titolo)
{
    string check = checkForbiddenCharacters(titolo);
    if(check != "" || HasNoChar(titolo))
        return false;
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
    if(file.hasNodoTesto("titolo",pos)){
        file.editFiglioText("titolo",titolo,pos);
    }
    else{
        file.AggiungiNodoFiglio("libro",pos,"titolo");
        file.AggiungiNodoFiglio("titolo",pos,titolo,true);
    }
    return file.salva();
    }
    return false;
}

bool AdminBiblio::ModificaAutorelibro(const string &codiceLibro, const string &autore)
{
    string check = checkForbiddenCharacters(autore);
    if(check != "" || HasNoChar(autore))
        return false;
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
    if(file.hasNodoTesto("autore",pos)){
        file.editFiglioText("autore",autore,pos);
    }
    else{
        file.AggiungiNodoFiglio("libro",pos,"autore");
        file.AggiungiNodoFiglio("autore",pos,autore,true);
    }
    return file.salva();
    }
    return false;
}

bool AdminBiblio::ModificaDescrizione(const string &codiceLibro, const string &descrizione)
{
    string check = checkForbiddenCharacters(descrizione);
    if(check != "" || HasNoChar(descrizione))
        return false;
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
    if(file.hasNodoTesto("descrizione",pos)){
        file.editFiglioText("descrizione",descrizione,pos);
    }
    else{
        file.AggiungiNodoFiglio("libro",pos,"descrizione");
        file.AggiungiNodoFiglio("descrizione",pos,descrizione,true);
    }
    return file.salva();
    }
    return false;
}

bool AdminBiblio::ModificaAnnoEdizione(const string &codiceLibro, const string &anno)
{
    string check = checkForbiddenCharacters(anno);
    if(check != "" || HasNoChar(anno))
        return false;
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
    if(file.hasNodoTesto("annoEdizione",pos)){
        file.editFiglioText("annoEdizione",anno,pos);
    }
    else{
        file.AggiungiNodoFiglio("libro",pos,"annoEdizione");
        file.AggiungiNodoFiglio("annoEdizione",pos,anno,true);
    }
    return file.salva();
    }
    return false;
}

bool AdminBiblio::ModificaCopertinaLibro(const string &codiceLibro, const string &filePath)
{
    string check = checkForbiddenCharacters(filePath);
    if(check != "")
        return false;
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
        string path = "/Biblioteca/libri/libro"+codiceLibro+".jpg";
    if(!file.hasNodoTesto("copertina",pos)){
        file.AggiungiNodoFiglio("copertina",pos,path,true);
        file.salva();
    }
    else{
        QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+QString::fromStdString(file.daiTestoIn("copertina",pos)));
    }
    return QFile::copy(QString::fromStdString(filePath), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                       QString::fromStdString(path));
    }
    return false;
}

bool AdminBiblio::eliminaLibro(const string &codiceLibro)
{
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
      bool check =  QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+QString::fromStdString(file.daiTestoIn("percorsoFile",pos)));
      QString copertina = QString::fromStdString(file.daiTestoIn("copertina",pos));
      if(copertina != "")
          check = QFile::remove(QDir::currentPath()+copertina);
        file.EliminaNodo("libro",pos);
        return check && file.salva();
    }
    return false;
}

bool AdminBiblio::eliminaCategoria(const string &nomeCat)
{
    list<string> l = file.daiTestoDiNodi("codiceLibro",nomeCat,"libro");
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        int pos = file.posNodo("libro",*it);
        file.EliminaNodo("categoria",nomeCat,"categorieLibro", pos);
        if(file.totNodiFigli("categorieLibro", pos) == 0)
            file.AggiungiNodoFiglio("categorieLibro", pos, "Non specificato", true);
    }
    filexml f("/Biblioteca/InfoBiblio.xml");
    f.EliminaNodo("nomecategoria",f.posNodo("nomecategoria", nomeCat));
    return file.salva() && f.salva();
}

bool AdminBiblio::eliminaCategorieLibro(const string &codiceLibro)
{
    int pos = file.posNodo("libro",codiceLibro);
    if(pos != -1){
        file.EliminaNodo("categorieLibro",pos);
        file.AggiungiNodoFiglio("libro",pos,"categorieLibro");
        return file.salva();
    }
    return false;
}

bool AdminBiblio::cambiaLogo(const string &pathLogo) const
{
    string check = checkForbiddenCharacters(pathLogo);
    if(check != "")
        return false;
    filexml f("/Biblioteca/InfoBiblio.xml");
    const string& path = "/Biblioteca/logo/logobiblioteca.jpg";
    if(!f.esisteTesto(path)){
        f.AggiungiNodoFiglioToLastNode("logo",path);

    }
    else QFile::remove(QDir::currentPath()+"/../progetto-pao-2017/Database"+QString::fromStdString(f.daiTestoIn("logo")));
    return QFile::copy(QString::fromStdString(pathLogo), QDir::currentPath()+"/../progetto-pao-2017/Database"+
                       QString::fromStdString(path)) && f.salva();
    return false;
}
