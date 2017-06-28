#pragma once
#ifndef FILEXML_H
#define FILEXML_H

/* PRECONDIZIONE: un oggetto della classe filexml rappresenta un filexml ben formato con nodi che ha nomi diversi dal padre
 */

#include <string>
#include <list>
#include <vector>
#include <iosfwd>
using std::ofstream;
using std::list;
using std::vector;
using std::string;

class QDomNode;
class filexml{
private:
    class nodo{
    public:
        string nome;
        string value;
        bool text;
        nodo* Parent;
        nodo* PrimoFiglio;
        nodo* Prevsibling;
        nodo* Nextsibling;
        nodo(const QDomNode &n, nodo*pare=0, nodo*pf=0 , nodo*prevs=0, nodo*ns=0);
        nodo(const string& n="", bool t=false, const string& v="",nodo*pare=0, nodo*pf=0 ,nodo*prevs=0, nodo*ns=0);
        nodo(const nodo&);
        ~nodo();
        string getName() const;
        string getText() const;
        string StampaTuttiTesti() const;
        int totNodi()const;
        int totNodi(const string& name)const;
        bool esisteNodo(const string& s) const;
        bool esisteNodoText(const string &s) const;
        bool haFiglio(const string& s) const;
        bool isText()const;
        bool hasText()const;
        bool operator==(const nodo& n) const;
        nodo* TrovaPrimoNodo(const string& nomeNodo);
        nodo* TrovaPrimoNodo(const string &genitore, const string &nomeNodo, const string& akinTo);
        nodo* TrovaPrimoNodo(const string &nomeNodo, const string& contenente);
        nodo *DaiNodo(const string& nomeNodo, int &pos);
        list<nodo*> daiTuttiINodi();
        list<nodo*>daiTuttiINodiFigli();
        vector<nodo *> daiNodi(const string& nomeNodo, const string& contenente="");
        list<string> daiNodiTesto(const string& parolachiave="");
        list<string> daiFigliNodiTesto();
        list<string> daiFigliNodiTestoDi(const string& nodeName)const;
        vector<string> daiFigliNodiTestoDiVect(const string& nodeName)const;
        vector<string> daiTestoDiNodiVect(const string& nodeName, const string& akinToNode, const string& genitore) const;
        list<string> daiTestoDiNodi(const string& nodeName, const string& akinToNode, const string& genitore) const;
        list<string> daiFigliNodiTesto(const string& nodeName);
        void salvaSuFile(ofstream& OUT)const;
        void aggiungiNodoSibling(nodo*p);
        void aggiungiNodoFiglio(nodo*p);

    };


    string path;
    nodo* primoNodo;
    string errore;
    bool modificato;
    static string pathDB;
    static nodo *copia(nodo* temp);
    static void distruggi(nodo* temp);
    nodo* daiPrimoNodo(const string& nome)const;
    nodo* daiUltimoNodo(const string& nome)const;
public:
    filexml();
    filexml(const string& percorso);
    filexml(const filexml&);
    filexml& operator =(const filexml&);
    bool operator==(const filexml&) const;
    bool operator!=(const filexml&) const;
    string daiErrore() const;
    string daiPath() const;
    bool apriFile() const;
    bool esisteNodo(const string &s) const;
    bool esisteTesto(const string& s) const;
    bool esisteTesto(const string& padre, const string& figliotestuale) const;
    bool esisteTesto(const string& padre, const string& figliotestuale, int posNodopadre) const;
    bool hasNodoTesto(const string& nodeName, int pos)const;
    int totNodi(const string& nome = "")const;
    int totNodiFigli(const string& nomeNodo)const;
    int totNodiFigli(const string& nomeNodo,int posNodo)const;
    int totNodiFigli(const string& nomeNodo, int posNodo, const string& figlioName)const;
    string ReadTagNames() const;
    string StampaTesto()const;
    list<string> daiTestoDiNodi(const string& nodeName) const;
    vector<string> daiTestoDiNodiVect(const string& nodeName) const;
    list<string> daiTestoDiNodi(const string& nodeName, const string &genitore, int posizione) const;
    list<string> daiTestoDiNodi(const string& nodeName, const string& akinToNode, const string& genitore) const;
    vector<string> daiTestoDiNodiVect(const string& nodeName, const string& akinToNode, const string& genitore) const;
    list<string> daiTextContainingText(const string& nodoPadre,const string & frase)const;
    list<string> daiTextContainingText(const string & frase)const;
    int posNodo(const string& padre, const string &figlio)const;
    int posNodo(const string& figlio, const string &akinto, const string &genitore)const;
    string daiTestoIn(const string& nodeName)const;
    string daiTestoIn(const string &nodeName, int posizione)const;
    bool akinTo(const string& genitore, const string& figlio1, const string &figlio2) const;
    bool akinToTesto(const string &genitore, const string &figlio1, const string &figlioTesto) const;
    void AggiungiNodo(const string& name, const string& sibl="", bool text=false);
    bool salva();
    bool salvaConNome(const string& percorsoWithFilename);
    void AggiungiNodoFiglio(const string& padre, const string &value, bool text=false);
    void AggiungiNodoFiglio(const string& padre, int pos, const string &value, bool text=false);
    void AggiungiNodoFiglio(const string& GrandParent, int posGrandParent, const string& padre, int posPadre,
                            const string &value, bool text=false);
    void AggiungiNodoFiglioToLastNode(const string& padre, const string &value, bool text=false);
    void EliminaNodo(const string& nome, int pos);
    void EliminaNodo(const string& nome, const string& akinTo, const string& genitore);
    void EliminaNodo(const string& nome,const string& genitore, int posGenitore);
    void EliminaNodo(const string& nomeNodo,const string& contenente,
                     const string& genitore, int posGenitore);
    void EliminaNodo(const string& nomeNodo,const string& contenente);
    void EliminaNodi(const string& nomeNodo);
    void editFiglioText(const string &padre, const string& valore);
    void editFiglioText(const string &padre, const string& valore, int pos);
    static filexml createNewXml(const string &path, const string& rootName);
    ~filexml();
};
#endif // FILEXML_H
