#include "nodoxml.h"
#include <QDomNamedNodeMap>

nodo* nodo::copia(nodo *temp)
{
    if(temp)
    return new nodo(*temp);
    return 0;

}


void nodo::distruggi(nodo *temp)
{
   if(temp)
       delete temp;
}

nodo::nodo(QDomNode n):nome(""), value(""), text(false), Firstsibling(0), PrimoFiglio(0)
{
    if(!n.isNull()){
        if(!n.isText())
            nome=n.nodeName().toStdString();
        else{
            value=n.nodeValue().toStdString();
            text= true;
        }
        if(!n.nextSibling().isNull())
         Firstsibling = new nodo(n.nextSibling());

        if(n.hasChildNodes())
            PrimoFiglio = new nodo(n.firstChild());
    }

}

nodo::nodo(const nodo &n):nome(n.nome),value(n.value), text(n.text),Firstsibling(copia(n.Firstsibling)),PrimoFiglio(copia(n.PrimoFiglio)){}

nodo &nodo::operator =(const nodo & n)
{
    if(this != &n){
    delete PrimoFiglio;
    delete Firstsibling;
    Firstsibling=copia(n.Firstsibling);
    PrimoFiglio=copia(n.PrimoFiglio);
    }
    return *this;
}

nodo::~nodo()
{
    distruggi(Firstsibling);
    distruggi(PrimoFiglio);
    value.erase(value.begin(), value.end());
    nome.erase(nome.begin(), nome.end());

}

string nodo::getName() const
{
    return nome;
}

string nodo::getText() const
{
    return value;
}

string nodo::StampaTuttiTesti() const
{
    string s1 ="", s2="";
     if(PrimoFiglio)
     s1= PrimoFiglio->StampaTuttiTesti();
     if(Firstsibling)
        s2= Firstsibling->StampaTuttiTesti();
     if(text)
         return value+s1+s2;
     return s1+s2;

}

bool nodo::esisteNodo(string s) const
{
   if(text && s==value)
       return true;
   if(!text && s==nome)
       return true;
   return (PrimoFiglio != NULL && PrimoFiglio->esisteNodo(s))||
           (Firstsibling != NULL && Firstsibling->esisteNodo(s));
}

bool nodo::esisteNodoText(string s) const
{
    if(text && s==value)
        return true;
    return (PrimoFiglio != NULL && PrimoFiglio->esisteNodoText(s))||
            (Firstsibling != NULL && Firstsibling->esisteNodoText(s));
}

bool nodo::haFiglio(string s) const
{
    return PrimoFiglio->esisteNodo(s);
}

bool nodo::isText() const
{
    return text;
}

bool nodo::operator==(const nodo &n) const
{
    bool check=false;
            if(text){
                    if(n.text && n.value==value)
                        check=true;

            }
            else{
                if(!n.text)
                    if(nome==n.nome)
                        check=true;
            }



                if(check && PrimoFiglio && n.PrimoFiglio )
                {
                   check = (*PrimoFiglio) == (*(n.PrimoFiglio));
                }
                if(check && Firstsibling && n.Firstsibling)
                    return (*Firstsibling)== (*(n.Firstsibling));
                return check;
}

nodo *nodo::GiveFirstSibling() const
{
    return Firstsibling;
}

nodo *nodo::GivePrimoFiglio() const
{
    return PrimoFiglio;
}

nodo *nodo::TrovaPrimoNodo(string nomeNodo)
{
    if(nomeNodo == nome || nomeNodo==value)
            return this;

    nodo* temp=0;
    if(PrimoFiglio)
        temp= PrimoFiglio->TrovaPrimoNodo(nomeNodo);
    if(!temp && Firstsibling)
        temp= Firstsibling->TrovaPrimoNodo(nomeNodo);
    return temp;
}

list<nodo *> nodo::daiTuttiINodi()
{
    list<nodo*> l;
    list<nodo*> l1;
    list<nodo*> l2;
    if(Firstsibling)
    l1= Firstsibling->daiTuttiINodi();
    if(PrimoFiglio)
    l2= PrimoFiglio->daiTuttiINodi();
    l1.insert(l1.end(), l2.begin(),l2.end());
    l.insert(l.end(),l1.begin(), l1.end());
    l.push_front(this);
    return l;
}

list<nodo *> nodo::daiTuttiINodiFigli()
{
    list<nodo*> l;
    if(PrimoFiglio)
        l= PrimoFiglio->daiTuttiINodi();
    return l;

}
list<nodo*> nodo::daiNodi(string nomeNodo, string contenente)
{

    list<nodo*>l, l2, l3;
    if(nomeNodo == nome || nomeNodo==value){
        if(contenente == "")
            l.push_back(this);
        else
                 if( PrimoFiglio && PrimoFiglio->esisteNodo(contenente))
                 l.push_back(this);
    }
    else
        if(PrimoFiglio)
        l2=PrimoFiglio->daiNodi(nomeNodo, contenente);
    if(Firstsibling)
    l3=Firstsibling->daiNodi(nomeNodo, contenente);
    l.insert(l.end(), l2.begin(), l2.end());
    l.insert(l.end(), l3.begin(), l3.end());
    return l;

}

list<nodo*> nodo::daiNodiTesto(string parolachiave)
{
    list<nodo*>l, l2, l3;
    if(text && parolachiave=="")
     l.push_back(this);
    else
        if(text && value.find(parolachiave) != string::npos)
            l.push_back(this);
    if(PrimoFiglio)
    l2=PrimoFiglio->daiNodiTesto(parolachiave);
    if(Firstsibling)
    l3=Firstsibling->daiNodiTesto(parolachiave);
    l.insert(l.end(), l2.begin(), l2.end());
    l.insert(l.end(), l3.begin(), l3.end());
    return l;
}
list<nodo *> nodo::daiFigliNodiTesto()
{
    list<nodo*>l, l2;
    if(text)
     l.push_back(this);
    if(PrimoFiglio)
    l2=PrimoFiglio->daiNodiTesto();
    l.insert(l.end(), l2.begin(), l2.end());
    return l;
}
