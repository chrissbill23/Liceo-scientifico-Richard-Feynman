#ifndef NODOXML_H
#define NODOXML_H

#include <QDomNode>
#include <string>
#include <list>
using std::list;
using std::string;
class nodo{
private:
    string nome;
    string value;
    bool text;
    nodo* Firstsibling;
    nodo* PrimoFiglio;
    static nodo *copia(nodo* temp);
    static void distruggi(nodo* temp);

public:
    nodo( QDomNode n);
    nodo(const nodo &n);
    nodo& operator =(const nodo&);
    ~nodo();
    string getName() const;
    string getText() const;
    string StampaTuttiTesti() const;
    bool esisteNodo(string s) const;
    bool esisteNodoText(string s) const;
    bool haFiglio(string s) const;
    bool isText()const;
    bool operator==(const nodo& n) const;
    nodo*GiveFirstSibling() const;
    nodo*GivePrimoFiglio() const;
    nodo* TrovaPrimoNodo(string nomeNodo);
    list<nodo*> daiTuttiINodi();
    list<nodo*>daiTuttiINodiFigli();
    list<nodo*> daiNodi(string nomeNodo, string contenente="");
    list<nodo*> daiNodiTesto(string parolachiave="");
    list<nodo*> daiFigliNodiTesto();

};

#endif // NODOXML_H
