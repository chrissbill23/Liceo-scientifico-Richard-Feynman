#include "filexml.h"
#include <fstream>
#include <QDir>
#include <QDomNode>

using std::endl;
//-------------NodoXml----------------

filexml::nodo::nodo(const QDomNode& n, nodo*pare, nodo*pf , nodo*prevs, nodo*ns):nome(""), value(""), text(false),
    Parent(pare), PrimoFiglio(pf), Prevsibling(prevs), Nextsibling(ns)
{
    if(!n.isNull()){
        if(!n.isText())
            nome = n.nodeName().toStdString();
        else{
            value =n.nodeValue().toStdString();
            text = true;
        }
        if(!n.nextSibling().isNull())
         Nextsibling = new nodo(n.nextSibling(),Parent,0,this);

        if(n.hasChildNodes())
            PrimoFiglio = new nodo(n.firstChild(),this);

    }

}

filexml::nodo::nodo(const string &n, bool t, const string& v, nodo*pare, nodo*pf , nodo*prevs, nodo*ns): nome(n), value(v),
    text(t), Parent(pare), PrimoFiglio(pf), Prevsibling(prevs), Nextsibling(ns){}

filexml::nodo::nodo(const filexml::nodo &n):nome(n.nome), value(n.value),
    text(n.text), Parent(0), PrimoFiglio(0), Prevsibling(0), Nextsibling(0)
{}

filexml::nodo::~nodo()
{

}

string filexml::nodo::getName() const
{
    return nome;
}

string filexml::nodo::getText() const
{
    return value;
}

string filexml::nodo::StampaTuttiTesti() const
{
    string s = "";
     if(text)
         s = value;
     if(PrimoFiglio)
     s = s + PrimoFiglio->StampaTuttiTesti();
     if(Nextsibling)
        s = s + Nextsibling->StampaTuttiTesti();
     return s;

}

int filexml::nodo::totNodi() const
{
    int conta = 1;
    if(PrimoFiglio)
       conta = conta + PrimoFiglio->totNodi();
    if(Nextsibling)
        conta = conta + Nextsibling->totNodi();

    return conta;
}

int filexml::nodo::totNodi(const string &name) const
{
    int conta = 0;
    if(nome == name || value == name)
        ++ conta;
    if(PrimoFiglio)
       conta = conta + PrimoFiglio->totNodi(name);
    if(Nextsibling)
        conta = conta + Nextsibling->totNodi(name);

    return conta;

}

bool filexml::nodo::esisteNodo(const string &s) const
{
   if(text && s==value)
       return true;
   if(!text && s==nome)
       return true;
   return (PrimoFiglio != NULL && PrimoFiglio->esisteNodo(s))||
           (Nextsibling != NULL && Nextsibling->esisteNodo(s));
}

bool filexml::nodo::esisteNodoText(const string& s) const
{
    if(text &&
      QString::fromStdString(value).indexOf(QString::fromStdString(s),
                                            0,Qt::CaseInsensitive) != -1)
        return true;
    return (PrimoFiglio != NULL && PrimoFiglio->esisteNodoText(s))||
            (Nextsibling != NULL && Nextsibling->esisteNodoText(s));
}

bool filexml::nodo::haFiglio(const string &s) const
{
    return PrimoFiglio && PrimoFiglio->esisteNodo(s);
}

bool filexml::nodo::isText() const
{
    return text;
}

bool filexml::nodo::hasText() const
{
    if(text)
        return true;
    return (PrimoFiglio != NULL && PrimoFiglio->hasText())||
            (Nextsibling != NULL && Nextsibling->hasText());
}

bool filexml::nodo::operator==(const nodo &n) const
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
                if(check && Nextsibling && n.Nextsibling)
                    return (*Nextsibling)== (*(n.Nextsibling));
                return check;
}


filexml::nodo *filexml::nodo::TrovaPrimoNodo(const string &nomeNodo)
{
    if(nomeNodo == nome || nomeNodo==value)
            return this;

    nodo* temp=0;
    if(PrimoFiglio)
        temp= PrimoFiglio->TrovaPrimoNodo(nomeNodo);
    if(!temp && Nextsibling)
        temp= Nextsibling->TrovaPrimoNodo(nomeNodo);
    return temp;
}

filexml::nodo *filexml::nodo::TrovaPrimoNodo( const string& genitore, const string &nomeNodo, const string &akinTo)
{
    nodo* temp = 0;
    if(genitore == nome || genitore==value){
        if(PrimoFiglio && PrimoFiglio->esisteNodo(nomeNodo) && PrimoFiglio->esisteNodo(nomeNodo))
        temp = this;
    }
    else{
        if(PrimoFiglio)
            temp = PrimoFiglio->TrovaPrimoNodo(genitore,nomeNodo,akinTo);
    }
    if(!temp && Nextsibling)
        temp = Nextsibling->TrovaPrimoNodo(genitore,nomeNodo,akinTo);
    return temp;
}

filexml::nodo *filexml::nodo::TrovaPrimoNodo(const string &nomeNodo, const string &contenente)
{
    nodo* temp = 0;
    if(nomeNodo == nome || nomeNodo==value){
        if(PrimoFiglio && PrimoFiglio->esisteNodo(contenente))
        return this;
    }
    else{
        if(PrimoFiglio)
            temp = PrimoFiglio->TrovaPrimoNodo(nomeNodo,contenente);
    }
    if(!temp && Nextsibling)
        temp = Nextsibling->TrovaPrimoNodo(nomeNodo,contenente);
    return temp;
}

filexml::nodo *filexml::nodo::DaiNodo(const string &nomeNodo, int& pos)
{
    if(pos >= 0){
        if(nomeNodo == nome || nomeNodo==value){
            if(pos == 0)
                return this;
            else pos = pos-1;
        }

        nodo* temp = 0;

        if(PrimoFiglio)
            temp = PrimoFiglio->DaiNodo(nomeNodo, pos);
        if(!temp && Nextsibling)
            temp = Nextsibling->DaiNodo(nomeNodo, pos);
        return temp;
    }
    return 0;
}

list<filexml::nodo *> filexml::nodo::daiTuttiINodi()
{
    list<nodo*> l;
    list<nodo*> l1;
    list<nodo*> l2;
    if(Nextsibling)
    l1= Nextsibling->daiTuttiINodi();
    if(PrimoFiglio)
    l2= PrimoFiglio->daiTuttiINodi();
    l1.insert(l1.end(), l2.begin(),l2.end());
    l.insert(l.end(),l1.begin(), l1.end());
    l.push_front(this);
    return l;
}

list<filexml::nodo *> filexml::nodo::daiTuttiINodiFigli()
{
    list<nodo*> l;
    if(PrimoFiglio)
        l= PrimoFiglio->daiTuttiINodi();
    return l;

}
vector<filexml::nodo*> filexml::nodo::daiNodi(const string& nomeNodo, const string& contenente)
{

    vector<nodo*>l, l2;
    if(nomeNodo == nome || nomeNodo == value){
        if(contenente == "")
            l.push_back(this);
        else
                 if( PrimoFiglio && PrimoFiglio->esisteNodo(contenente))
                 l.push_back(this);
    }
    else
        if(PrimoFiglio)
        l = PrimoFiglio->daiNodi(nomeNodo, contenente);
    if(Nextsibling)
    l2 = Nextsibling->daiNodi(nomeNodo, contenente);
    l.insert(l.end(), l2.begin(), l2.end());
    return l;

}

list<string> filexml::nodo::daiNodiTesto(const string &parolachiave)
{
    list<string>l, l2, l3;
    if(text && parolachiave=="")
     l.push_back(value);
    else
        if(text && value.find(parolachiave) != string::npos)
            l.push_back(value);
    if(PrimoFiglio)
    l2 = PrimoFiglio->daiNodiTesto(parolachiave);
    if(Nextsibling)
    l3 = Nextsibling->daiNodiTesto(parolachiave);
    l.insert(l.end(), l2.begin(), l2.end());
    l.insert(l.end(), l3.begin(), l3.end());
    return l;
}
list<string> filexml::nodo::daiFigliNodiTesto()
{
    list<string>l, l2;
    if(text)
     l.push_back(value);
    if(PrimoFiglio)
    l2=PrimoFiglio->daiNodiTesto();
    l.insert(l.end(), l2.begin(), l2.end());
    return l;
}

list<string> filexml::nodo::daiFigliNodiTestoDi(const string &nodeName) const
{
    list<string>l, l2;
    if(nodeName == nome || nodeName == value){
       if(PrimoFiglio)
           l.push_back(PrimoFiglio->StampaTuttiTesti());
    }
    else {
        if(PrimoFiglio)
            l = PrimoFiglio->daiFigliNodiTestoDi(nodeName);
    }
    if(Nextsibling)
        l2 = Nextsibling->daiFigliNodiTestoDi(nodeName);
    l.insert(l.end(),l2.begin(),l2.end());
    return l;
}

vector<string> filexml::nodo::daiFigliNodiTestoDiVect(const string &nodeName) const
{
    vector<string>l, l2;
    if(nodeName == nome || nodeName == value){
       if(PrimoFiglio)
           l.push_back(PrimoFiglio->StampaTuttiTesti());
    }
    else {
        if(PrimoFiglio)
            l = PrimoFiglio->daiFigliNodiTestoDiVect(nodeName);
    }
    if(Nextsibling)
        l2 = Nextsibling->daiFigliNodiTestoDiVect(nodeName);
    l.insert(l.end(),l2.begin(),l2.end());
    return l;
}

vector<string> filexml::nodo::daiTestoDiNodiVect(const string &nodeName, const string &akinToNode, const string &genitore) const
{
    vector<string>v, v2;
    if(genitore == nome || genitore == value){
       if(PrimoFiglio && PrimoFiglio->esisteNodo(akinToNode))
           v = PrimoFiglio->daiFigliNodiTestoDiVect(nodeName);
    }
    else {
        if(PrimoFiglio)
            v = PrimoFiglio->daiTestoDiNodiVect(nodeName, akinToNode,genitore);
    }
    if(Nextsibling)
        v2 = Nextsibling->daiTestoDiNodiVect(nodeName, akinToNode,genitore);
    v.insert(v.end(),v2.begin(),v2.end());
    return v;
}

list<string> filexml::nodo::daiTestoDiNodi(const string &nodeName, const string &akinToNode, const string &genitore) const
{
    list<string>l, l2;
    if(genitore == nome || genitore == value){
       if(PrimoFiglio && PrimoFiglio->esisteNodo(akinToNode))
           l = PrimoFiglio->daiFigliNodiTesto(nodeName);
    }
    else {
        if(PrimoFiglio)
            l = PrimoFiglio->daiTestoDiNodi(nodeName, akinToNode,genitore);
    }
    if(Nextsibling)
        l2 = Nextsibling->daiTestoDiNodi(nodeName, akinToNode,genitore);
    l.insert(l.end(),l2.begin(),l2.end());
    return l;
}

list<string> filexml::nodo::daiFigliNodiTesto(const string &nodeName)
{

    list<string>l, l2, l3;
    if(nodeName == nome || nodeName == value){
       if( PrimoFiglio)
           l.push_back(PrimoFiglio->StampaTuttiTesti());
    }
    else
        if(PrimoFiglio)
        l2 = PrimoFiglio->daiFigliNodiTesto(nodeName);
    if(Nextsibling)
    l3 = Nextsibling->daiFigliNodiTesto(nodeName);
    l.insert(l.end(), l2.begin(), l2.end());
    l.insert(l.end(), l3.begin(), l3.end());
    return l;
}

void filexml::nodo::salvaSuFile(ofstream & OUT) const
{
        OUT<<"<"+nome+">";
        if(PrimoFiglio){
            if(PrimoFiglio->text)
                OUT<<PrimoFiglio->value;
            else{
                OUT<<endl<<"    ";
            PrimoFiglio->salvaSuFile(OUT);
            }
        }
        OUT<<"</"<<nome<<">"<<endl;
        if(Nextsibling)
            Nextsibling->salvaSuFile(OUT);
}

void filexml::nodo::aggiungiNodoSibling(nodo * p)
{
    if(Nextsibling)
        Nextsibling->aggiungiNodoSibling(p);
    else{
        Nextsibling=p;
        p->Prevsibling = this;
    }
}

void filexml::nodo::aggiungiNodoFiglio(nodo *p)
{
    if(!PrimoFiglio)
        PrimoFiglio = p;
    else{
        PrimoFiglio->aggiungiNodoSibling(p);
    }
}


//--------FileXml-------------
string filexml::pathDB=QDir::currentPath().toStdString()+"/../progetto-pao-2017/Database";
filexml::nodo *filexml::copia(nodo *temp)
{
    if(temp){

        nodo* temp2 = new nodo(*temp);
        nodo* temp3 = 0;
        nodo* temp4 = 0;
        if(temp->Nextsibling){
        temp3 = copia(temp->Nextsibling);
        }
        if(temp->PrimoFiglio)
        {
            temp4 = copia(temp->PrimoFiglio);
        }
        temp2->PrimoFiglio = temp4;
            nodo* t = temp4;
            while(t){
                t->Parent = temp2;
                t = t->Nextsibling;
            }
        if(temp3){
            temp3->Prevsibling = temp2;
        }
        temp2->Nextsibling = temp3;

        return temp2;
    }
    return 0;
}

void filexml::distruggi(filexml::nodo *temp)
{
    if(temp){
        distruggi(temp->Nextsibling);
        distruggi(temp->PrimoFiglio);
        delete temp;
    }
}
filexml::filexml(): path(""), primoNodo(0),  errore("Nessun file dato"), modificato(false){}

filexml::filexml(const string &percorso):path(percorso), primoNodo(0),
                                  errore("E' avvenuto un errore nell'apertura del file"),
                                  modificato(false){
   QFile file(QString::fromStdString(pathDB+path));
    QDomDocument d;
        if (file.open(QIODevice::ReadOnly) && d.setContent(&file)){
            primoNodo = new nodo(QDomNode(d.documentElement()));
            errore = "nessun errore da mostrare";
        }
        file.close();
}

filexml::filexml(const filexml &p):path(p.path), primoNodo(copia(p.primoNodo)),errore(p.errore){

}

filexml &filexml::operator =(const filexml & p)
{
    if(this != &p){
        path = p.path;
        distruggi(primoNodo);
        primoNodo = copia(p.primoNodo);
            errore=p.errore;
    }
    return *this;
}

bool filexml::operator==(const filexml & p) const
{
    return primoNodo && p.primoNodo && (*primoNodo) == (*(p.primoNodo));
}

bool filexml::operator!=(const filexml & p) const
{
    return (primoNodo && p.primoNodo && (*primoNodo) == (*(p.primoNodo)))? false: true;
}

string filexml::daiErrore() const
{
    return errore;
}

string filexml::daiPath() const
{
   return path;
}

bool filexml::apriFile() const
{
    return primoNodo != NULL;
}

bool filexml::esisteNodo(const string &s) const
{
    return apriFile() && primoNodo->esisteNodo(s);
}

bool filexml::esisteTesto(const string& s) const
{
      return primoNodo && primoNodo->esisteNodoText(s);

}

bool filexml::esisteTesto(const string &padre, const string &figliotestuale) const
{
    if(apriFile()){
    vector<nodo*>l = primoNodo->daiNodi(padre);
    for(vector<nodo*>::const_iterator it=l.begin(); it != l.end(); ++it)
        if((*it)->haFiglio(figliotestuale))
            return true;
    }
    return false;
}

bool filexml::esisteTesto(const string &padre, const string &figliotestuale, int posNodopadre) const
{
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(padre, posNodopadre);
        if(temp && temp->PrimoFiglio)
            return temp->esisteNodoText(figliotestuale);
    }
    return false;
}

bool filexml::hasNodoTesto(const string &nodeName, int pos) const
{
    if(apriFile()){
       nodo* temp = primoNodo->DaiNodo(nodeName,pos);
       if(temp)
            return temp->hasText();
    }
    return false;
}

int filexml::totNodi(const string &nome) const
{
    if(apriFile()){
    if(nome != ""){
        vector<nodo*>l= primoNodo->daiNodi(nome);
        return l.size();
    }
    else{
        list<nodo*>l= primoNodo->daiTuttiINodi();
        return l.size();
    }
    }
    return 0;
}

int filexml::totNodiFigli(const string &nomeNodo) const
{
    if(apriFile()){
    nodo* temp = primoNodo->TrovaPrimoNodo(nomeNodo);
    if(temp && temp->PrimoFiglio)
        return temp->PrimoFiglio->totNodi();
    }
    return 0;
}

int filexml::totNodiFigli(const string &nomeNodo, int posNodo) const
{
    nodo* temp = primoNodo->DaiNodo(nomeNodo, posNodo);
    if(temp && temp->PrimoFiglio)
        return temp->PrimoFiglio->totNodi();
    return 0;
}

int filexml::totNodiFigli(const string &nomeNodo, int posNodo, const string &figlioName) const
{
    nodo* temp = primoNodo->DaiNodo(nomeNodo, posNodo);
    if(temp && temp->PrimoFiglio)
        return temp->PrimoFiglio->totNodi(figlioName);
    return 0;
}
string filexml::ReadTagNames() const
{

        return primoNodo ? primoNodo->getName(): "";
}

string filexml::StampaTesto() const
{
    return primoNodo ? primoNodo->StampaTuttiTesti() : "";
}

list<string> filexml::daiTestoDiNodi(const string &nodeName) const
{
    list<string>l2;
    if(apriFile()){
    vector<nodo*>v = primoNodo->daiNodi(nodeName);
    for(vector<nodo*>::const_iterator it=v.begin(); it != v.end(); ++it){
        nodo*temp = (*it)->PrimoFiglio;
        if(temp)
        l2.push_back(temp->StampaTuttiTesti());
    }
    }
    return l2;
}

vector<string> filexml::daiTestoDiNodiVect(const string &nodeName) const
{
    vector<string>v2;
    if(apriFile()){
        return primoNodo->daiFigliNodiTestoDiVect(nodeName);
    }
    return v2;
}

list<string> filexml::daiTestoDiNodi(const string &nodeName, const string& genitore, int posizione) const
{
    list<string> l;
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(genitore,posizione) ;
        if(temp && temp->PrimoFiglio){
        return temp->PrimoFiglio->daiFigliNodiTestoDi(nodeName);
        }
    }
    return l;
}

list<string> filexml::daiTestoDiNodi(const string &nodeName, const string &akinToNode, const string &genitore) const
{
    list<string> l;
    if(apriFile()){
       return primoNodo->daiTestoDiNodi(nodeName,akinToNode,genitore);
    }
    return l;
}

vector<string> filexml::daiTestoDiNodiVect(const string &nodeName, const string &akinToNode, const string &genitore) const
{
    vector<string> v;
    if(apriFile()){
        return primoNodo->daiTestoDiNodiVect(nodeName,akinToNode,genitore);
    }
    return v;
}

list<string> filexml::daiTextContainingText(const string &nodoPadre, const string &frase) const
{
    list<string> l2;
    if(apriFile()){
        list<string> l = daiTestoDiNodi(nodoPadre);
        const QString& phrase = QString::fromStdString(frase);
        for(list<string>::iterator it = l.begin(); it != l.end(); ++it){
            const QString& text = QString::fromStdString(*it);
            if(text.indexOf(phrase,0,Qt::CaseInsensitive) != -1){
                l2.push_back(*it);
                }
        }
    }
    return l2;
}

list<string> filexml::daiTextContainingText(const string &frase) const
{
    list<string> l2;
    if(apriFile()){
            list<string> l = primoNodo->daiNodiTesto();
            const QString& phrase = QString::fromStdString(frase);
            for(list<string>::iterator it = l.begin(); it != l.end(); ++it){
                const QString& text = QString::fromStdString(*it);
                if(text.indexOf(phrase,0,Qt::CaseInsensitive) != -1){
                    l2.push_back(*it);
                    }
            }

    }
    return l2;
}

int filexml::posNodo(const string &padre, const string& figlio) const
{
    int pos = -1;
    vector<nodo*>l = primoNodo->daiNodi(padre);
    if(l.size() > 0){
        pos = 0;
        bool esci = false;
        for(vector<nodo*>::const_iterator it= l.begin();
            it!= l.end() && !esci;++it){
            if((*it)->PrimoFiglio)
            esci = (*it)->PrimoFiglio->esisteNodo(figlio);
            if(!esci)
                ++pos;
        }
        if(!esci)
            pos = -1;
    }
    return pos;

}

int filexml::posNodo(const string &figlio, const string& akinto, const string& genitore) const
{
    vector<nodo*>v = primoNodo->daiNodi(genitore, figlio);
    for(unsigned int i = 0; i<v.size(); ++i)
        if((v[i])->haFiglio(akinto))
            return i;
    return -1;
}


string filexml::daiTestoIn(const string &nodeName) const
{
    if(apriFile()){
    nodo* temp= primoNodo->TrovaPrimoNodo(nodeName);
    if(temp){
    if(temp->text)
        return temp->StampaTuttiTesti();
    return temp->PrimoFiglio->StampaTuttiTesti();
        }
    }
    return "";
}

string filexml::daiTestoIn(const string& nodeName, int posizione) const
{
    if(apriFile()){
       nodo* temp = primoNodo->DaiNodo(nodeName,posizione);
       if(temp && temp->PrimoFiglio)
           return temp->PrimoFiglio->StampaTuttiTesti();
    }
    return "";
}

filexml::nodo *filexml::daiPrimoNodo(const string &nome) const
{
    vector<nodo*> v =primoNodo->daiNodi(nome);
    if(v.size() > 0){
        return (*(v.begin()));
    }
    return 0;
}

filexml::nodo *filexml::daiUltimoNodo(const string &nome) const
{
    vector<nodo*> l =primoNodo->daiNodi(nome);
    if(l.size() > 0){
        return (l.back());
    }
    return 0;
}

bool filexml::akinTo(const string &genitore, const string &figlio1, const string& figlio2) const
{
        vector<nodo*>l = primoNodo->daiNodi(genitore, figlio1);
        for(vector<nodo*>::const_iterator it=l.begin(); it != l.end(); ++it)
            if((*it)->haFiglio(figlio2))
                return true;
        return false;
}

bool filexml::akinToTesto(const string &genitore, const string &figlio1, const string &figlioTesto) const
{
    vector<nodo*>l = primoNodo->daiNodi(genitore, figlio1);
    for(vector<nodo*>::const_iterator it = l.begin(); it != l.end(); ++it)
        if((*it)->PrimoFiglio->esisteNodoText(figlioTesto))
            return true;
    return false;
}

void filexml::AggiungiNodo(const string& name, const string& sibl, bool text)
{
    nodo* temp;
    if(sibl =="" || sibl==primoNodo->getName()){
        temp=primoNodo->PrimoFiglio;
        if(!temp){
            modificato=true;
            if(!text)
                primoNodo->aggiungiNodoFiglio(new nodo(name));

            else
                primoNodo->aggiungiNodoFiglio(new nodo("", true, name,primoNodo));
            return;
        }

    }
     else{
            temp=daiPrimoNodo(sibl);
        }
    if(temp){
        modificato=true;
    if(!text)
        temp->aggiungiNodoSibling(new nodo(name));

    else
        temp->aggiungiNodoSibling(new nodo("", true, name));
    }
}

bool filexml::salva()
{
    if(modificato){
    ofstream OUT((pathDB+path).c_str());
    OUT<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    primoNodo->salvaSuFile(OUT);
    modificato = false;
    }
    return true;
}

bool filexml::salvaConNome(const string &percorsoWithFilename)
{
    path = percorsoWithFilename;
    modificato = true;
    return salva();
}

void filexml::AggiungiNodoFiglio(const string &padre, const string& value, bool text)
{
    if(apriFile()){
    nodo*temp = 0;
    temp = daiPrimoNodo(padre);
    if(temp){
        modificato=true;
    if(!text)
        temp->aggiungiNodoFiglio(new nodo(value,false,"",temp));
    else
        temp->aggiungiNodoFiglio(new nodo("",true,value,temp));
    }
    }
}

void filexml::AggiungiNodoFiglio(const string &padre, int pos, const string &value, bool text)
{
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(padre,pos);
        if(temp){
        modificato = true;
        if(!text)
            temp->aggiungiNodoFiglio(new nodo(value,false,"",temp));
        else
            temp->aggiungiNodoFiglio(new nodo("",true,value,temp));
        }
    }
}

void filexml::AggiungiNodoFiglio(const string &GrandParent, int posGrandParent, const string &padre, int posPadre, const string &value, bool text)
{
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(GrandParent,posGrandParent);
        if(temp){
        modificato = true;
        nodo* temp2 = temp->DaiNodo(padre,posPadre);
        if(temp2){
        if(!text)
            temp2->aggiungiNodoFiglio(new nodo(value,false,"",temp2));
        else
            temp2->aggiungiNodoFiglio(new nodo("",true,value,temp2));
        }
        }
    }
}

void filexml::AggiungiNodoFiglioToLastNode(const string &padre, const string& value, bool text)
{
    if(apriFile()){
    nodo*temp = 0;
    temp = daiUltimoNodo(padre);
    if(temp){
        modificato = true;
        if(!text)
            temp->aggiungiNodoFiglio(new nodo(value,false,"",temp));
        else
            temp->aggiungiNodoFiglio(new nodo("",true,value,temp));
    }
    }
}

void filexml::EliminaNodo(const string &nome, int pos)
{
    if(apriFile()){
    nodo* temp = primoNodo->DaiNodo(nome, pos);
    if(temp){
        if(temp->Parent){
            if(!temp->Nextsibling && !temp->Prevsibling)
                temp->Parent->PrimoFiglio = 0;
            else{
                if(temp->Prevsibling)
                    temp->Prevsibling->Nextsibling = temp->Nextsibling;
                else temp->Parent->PrimoFiglio = temp->Nextsibling;
                if(temp->Nextsibling)
                    temp->Nextsibling->Prevsibling = temp->Prevsibling;
            }
        }
        else primoNodo = 0;
        distruggi( temp->PrimoFiglio);
        delete temp;
        modificato = true;
    }
    }
}

void filexml::EliminaNodo(const string &nome, const string &akinTo, const string &genitore)
{
    if(apriFile()){
    nodo* temp = primoNodo->TrovaPrimoNodo(nome,akinTo,genitore);
    if(temp){
        if(temp->Parent){
            if(!temp->Nextsibling && !temp->Prevsibling)
                temp->Parent->PrimoFiglio = 0;
            else{
                if(temp->Prevsibling)
                    temp->Prevsibling->Nextsibling = temp->Nextsibling;
                else temp->Parent->PrimoFiglio = temp->Nextsibling;
                if(temp->Nextsibling)
                    temp->Nextsibling->Prevsibling = temp->Prevsibling;
            }
        }
        else primoNodo = 0;
        distruggi( temp->PrimoFiglio);
        delete temp;
        modificato = true;
    }
    }
}

void filexml::EliminaNodo(const string &nome, const string &genitore, int posGenitore)
{
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(genitore,posGenitore);
        if(temp && temp->PrimoFiglio){
            nodo* temp2 = temp->PrimoFiglio->TrovaPrimoNodo(nome);
            if(temp2){
            if(temp2->Parent){
                if(!temp2->Nextsibling && !temp2->Prevsibling)
                    temp2->Parent->PrimoFiglio = 0;
                else{
                    if(temp2->Prevsibling)
                        temp2->Prevsibling->Nextsibling = temp2->Nextsibling;
                    else temp2->Parent->PrimoFiglio = temp2->Nextsibling;
                    if(temp2->Nextsibling)
                        temp2->Nextsibling->Prevsibling = temp2->Prevsibling;
                }
            }
            else primoNodo = 0;
            distruggi( temp2->PrimoFiglio);
            delete temp2;
            modificato = true;
            }
        }
    }
}

void filexml::EliminaNodo(const string &nomeNodo, const string &contenente, const string &genitore, int posGenitore)
{
    if(apriFile()){
        nodo* temp = primoNodo->DaiNodo(genitore,posGenitore);
        if(temp && temp->PrimoFiglio){
            nodo* temp2 = temp->PrimoFiglio->TrovaPrimoNodo(nomeNodo,contenente);
            if(temp2){
            if(temp2->Parent){
                if(!temp2->Nextsibling && !temp2->Prevsibling)
                    temp2->Parent->PrimoFiglio = 0;
                else{
                    if(temp2->Prevsibling)
                        temp2->Prevsibling->Nextsibling = temp2->Nextsibling;
                    else temp2->Parent->PrimoFiglio = temp2->Nextsibling;
                    if(temp2->Nextsibling)
                        temp2->Nextsibling->Prevsibling = temp2->Prevsibling;
                }
            }
            else primoNodo = 0;
            distruggi( temp2->PrimoFiglio);
            delete temp2;
            modificato = true;
            }
        }
    }
}

void filexml::EliminaNodo(const string &nomeNodo, const string &contenente)
{
    if(apriFile()){
        nodo* temp = primoNodo->TrovaPrimoNodo(nomeNodo,contenente);
        if(temp){
            if(temp->Parent){
                if(!temp->Nextsibling && !temp->Prevsibling)
                    temp->Parent->PrimoFiglio = 0;
                else{
                    if(temp->Prevsibling)
                        temp->Prevsibling->Nextsibling = temp->Nextsibling;
                    else temp->Parent->PrimoFiglio = temp->Nextsibling;
                    if(temp->Nextsibling)
                        temp->Nextsibling->Prevsibling = temp->Prevsibling;
                }
            }
            else primoNodo = 0;
            distruggi( temp->PrimoFiglio);
            delete temp;
            modificato = true;
        }
    }
}

void filexml::EliminaNodi(const string &nomeNodo)
{
    if(apriFile()){
        nodo* temp = primoNodo->TrovaPrimoNodo(nomeNodo);
        while(temp){
            if(temp->Parent){
                if(!temp->Nextsibling && !temp->Prevsibling)
                    temp->Parent->PrimoFiglio = 0;
                else{
                    if(temp->Prevsibling)
                        temp->Prevsibling->Nextsibling = temp->Nextsibling;
                    else temp->Parent->PrimoFiglio = temp->Nextsibling;
                    if(temp->Nextsibling)
                        temp->Nextsibling->Prevsibling = temp->Prevsibling;
                }
            }
            else primoNodo = 0;
            distruggi( temp->PrimoFiglio);
            delete temp;
            modificato = true;
            temp = primoNodo->TrovaPrimoNodo(nomeNodo);
        }
    }
}

void filexml::editFiglioText(const string &padre, const string &valore)
{
    if(apriFile()){
        nodo* temp = primoNodo->TrovaPrimoNodo(padre);
        if(temp && temp->PrimoFiglio && temp->PrimoFiglio->text){
            temp->PrimoFiglio->value = valore;
            modificato = true;
        }
    }
}

void filexml::editFiglioText(const string& padre, const string &valore, int pos)
{
    if(apriFile()){
    nodo* temp = primoNodo->DaiNodo(padre,pos);
    if(temp && temp->PrimoFiglio && temp->PrimoFiglio->text){
            temp->PrimoFiglio->value = valore;
            modificato = true;
    }
    }
}

filexml filexml::createNewXml(const string& path, const string &rootName)
{
    ofstream OUT((pathDB+path).c_str());
    OUT<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    OUT<<"<"+rootName+">"<<endl;
    OUT<<"</"+rootName+">"<<endl;

    filexml f(path);
    return f;
}


filexml::~filexml()
{

    distruggi( primoNodo);
}
