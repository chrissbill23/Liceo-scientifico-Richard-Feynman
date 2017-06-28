#include "biblioteca.h"
#include <QDesktopServices>
#include "filexml.h"
#include <QUrl>
#include <QDir>
string Biblioteca::path = "/Biblioteca";
Biblioteca::Biblioteca(){}

string Biblioteca::ShowLogo() const
{
    filexml file(path + "/InfoBiblio.xml");
    return QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+file.daiTestoIn("logo");
}

string Biblioteca::daiNomeBiblio() const
{
    filexml file(path + "/InfoBiblio.xml");
    return file.daiTestoIn("nome");
}

vector<string> Biblioteca::categorie() const
{
    filexml file(path + "/InfoBiblio.xml");
    return file.daiTestoDiNodiVect("nomecategoria");
}

vector<string> Biblioteca::codiciLibri() const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoDiNodiVect("codiceLibro");
}

vector<string> Biblioteca::codiciLibriPrimoPiano() const
{
    filexml file(path + "/InfoBiblio.xml");
    return file.daiTestoDiNodiVect("libroPrimoPiano");
}

list<string> Biblioteca::daiCodiciLibriCat(const string &nomeCat) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoDiNodi("codiceLibro",nomeCat,"libro");
}

vector<string> Biblioteca::findCodiciBook(const string &parolaChiave) const
{
    filexml file(path + "/InfoLibri.xml");
    list<string> l = file.daiTestoDiNodi("codiceLibro");
    vector<string> l2;
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        if(file.akinToTesto("libro",*it,parolaChiave))
            l2.push_back(*it);
    }
    return l2;
}

list<string> Biblioteca::daiCodiciLibriAnnoEdizione(const string &anno) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoDiNodi("codiceLibro",anno,"libro");
}

string Biblioteca::daiTitoloLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoIn("titolo",file.posNodo("codiceLibro",codice));
}

string Biblioteca::daiAutoreLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoIn("autore",file.posNodo("codiceLibro",codice));
}

string Biblioteca::daiAnnoEdizioneLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoIn("annoEdizione",file.posNodo("codiceLibro",codice));
}

string Biblioteca::daiDescrizioneLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoIn("descrizione",file.posNodo("codiceLibro",codice));
}

string Biblioteca::daiCopertinaLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    string percorso =  file.daiTestoIn("copertina",file.posNodo("codiceLibro",codice));
    if(percorso != "")
        percorso = QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+percorso;
    return percorso;
}

list<string> Biblioteca::daiCategorieLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return file.daiTestoDiNodi("categoria", codice, "libro");
}

string Biblioteca::daiPercorsoLibro(const string &codice) const
{
    filexml file(path + "/InfoLibri.xml");
    return QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database"+
            file.daiTestoIn("percorsoFile", file.posNodo("libro", codice));
}

void Biblioteca::SortLibriByCategoria(vector<string> &codiciLibri, const string &categoria) const
{
    filexml file(path + "/InfoLibri.xml");
    for(vector<string>::iterator it = codiciLibri.begin(); it != codiciLibri.end(); ++it){
        if(!file.akinTo("libro",*it,categoria)){
            codiciLibri.erase(it);
            --it;
        }
    }

}

void Biblioteca::SortLibriByAutore(vector<string> &codiciLibri, const string &autore) const
{
    filexml file(path + "/InfoLibri.xml");
    for(vector<string>::iterator it = codiciLibri.begin(); it != codiciLibri.end(); ++it){
        if(!file.akinTo("libro",*it,autore)){
            codiciLibri.erase(it);
            --it;
        }
    }
}

void Biblioteca::SortLibriByAnnoEdizione(vector<string> &codiciLibri, const string &anno) const
{
    filexml file(path + "/InfoLibri.xml");
    for(vector<string>::iterator it = codiciLibri.begin(); it != codiciLibri.end(); ++it){
        if(!file.akinTo("libro",*it,anno)){
            codiciLibri.erase(it);
            --it;
        }
    }
}
