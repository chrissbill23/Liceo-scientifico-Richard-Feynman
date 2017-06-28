#include "email.h"
#include <algorithm>

string email::pathDBListaMail = "/Messaggi/email.xml";

email::email():account(""){}

email::email(string a):account(a), file(filexml(pathDBListaMail)){
if(file.apriFile()){
   int tot= file.totNodi("mail");
   for(int i=0; i<tot; ++i){
       const string& mail = file.daiTestoIn("mail",i);
       if(account != mail)
       v.push_back(ContattoMail(file.daiTestoIn("nome",i), mail));
   }
    std::sort(v.begin(), v.end());
}
emailRicevute::operator=(emailRicevute(account,file.daiTestoIn("mailRicevuta",file.posNodo("mail",account))));
emailInviate::operator=(emailInviate(account,file.daiTestoIn("mailInviata",file.posNodo("mail",account))));
}

string email::daiAccount() const{ return account; }

int email::totContatti() const
{
    return v.size();
}

string email::daiNomeContatto(unsigned int indice) const
{
    if(indice < v.size())
        return v[indice].daiNomeContatto();
    return "Errore: nessun contatto trovato";
}

string email::daiMailContatto(unsigned int indice) const
{
    if(indice < v.size())
        return v[indice].daiMailContatto();
    return "Errore: nessun contatto trovato";
}

bool email::SendNewMessage(string data, string dest, string ogg, string testo)
{
    filexml f(pathDBListaMail);
    return f.apriFile() && f.esisteTesto(dest) &&
            emailInviate::SendNewMessage(data,dest,ogg,testo,f.daiTestoIn("mailRicevuta",f.posNodo("mail",dest)));
}


emailRicevute::emailRicevute():account(""),pathtoDb(""){}

emailRicevute::emailRicevute(string acc,string path):account(acc),pathtoDb(path)
{
    if(pathtoDb!=""){
    filexml f(pathtoDb);
    if(f.apriFile()){
        unsigned int size=f.totNodi("mail");
        for(unsigned int i=0; i<size; ++i){
            string letto=f.daiTestoIn("letto", i);
            if(letto=="1")
                v.push_back(Messaggio(f.daiTestoIn("data",i), f.daiTestoIn("emittente",i),
                                         acc,f.daiTestoIn("messaggio",i),
                                         f.daiTestoIn("oggetto",i)));
            else
                v.push_back(Messaggio(f.daiTestoIn("data",i), f.daiTestoIn("emittente",i),
                                         acc,f.daiTestoIn("messaggio",i),
                                         f.daiTestoIn("oggetto",i), false));
        }
    }
    }
}

vector<const Messaggio *> emailRicevute::MailNonLetta() const
{
    vector<const Messaggio*> temp;
    for(vector<Messaggio>::const_iterator it= v.begin(); it != v.end(); ++ it){
        if(!it->isRead())
            temp.push_back(&(*it));
    }
    return temp;
}

int emailRicevute::giveMessageIndex(const Messaggio &m) const
{
    for(unsigned int i = 0; i < v.size(); ++i)
        if(v[i] == m)
            return i;
    return -1;
}

string emailRicevute::dataMailRic(unsigned int indice, bool OnlyUnread) const
{
    if(OnlyUnread){
        vector<const Messaggio*> l= MailNonLetta();
        if(l.size() > indice)
            return l[indice]->daiData();
    }
    else{
        if(v.size() > indice)
            return v[indice].daiData();
    }
    return "Errore: nessuna mail trovata";
}

string emailRicevute::MailSender(unsigned int indice, bool OnlyUnread) const
{
    if(OnlyUnread){
        vector<const Messaggio*> l= MailNonLetta();
        if(l.size() > indice)
            return l[indice]->daiEmitt();
    }
    else{
        if(v.size() > indice)
            return v[indice].daiEmitt();
    }
    return "Errore: nessuna mail trovata";
}


string emailRicevute::MailOggeRic(unsigned int indice, bool OnlyUnread) const
{
    if(OnlyUnread){
        vector<const Messaggio*> l= MailNonLetta();
        if(l.size() > indice)
            return l[indice]->daiOgge();
    }
    else{
        if(v.size() > indice)
            return v[indice].daiOgge();
    }
    return "Errore: nessuna mail trovata";
}

string emailRicevute::MailTestoRic(unsigned int indice, bool OnlyUnread)
{
    if(OnlyUnread){
        vector<const Messaggio*> l = MailNonLetta();
        if(l.size() > indice){
            (const_cast<Messaggio*>(l[indice]))->setLetto(true);
            filexml f(pathtoDb);
            f.editFiglioText("letto","1",giveMessageIndex(*(l[indice])));
            f.salva();
            return l[indice]->daiMessaggio();
        }
    }
    else{
        if(v.size() > indice)
            return v[indice].daiMessaggio();
    }
    return "Errore: nessuna mail trovata";
}

bool emailRicevute::elimMessRic(unsigned int i)
{
    if(v.size() > i){
    v.erase(v.begin()+i);
    filexml f(pathtoDb);
        f.EliminaNodo("mail",i);
        return f.salva();
    }
    return false;
}

bool emailRicevute::isMailRead(unsigned int i) const
{
    return v[i].isRead();
}

int emailRicevute::totMailRic() const
{
    return v.size();
}

int emailRicevute::totNuoviRic() const
{
    return (MailNonLetta()).size();
}

emailInviate::emailInviate():pathtoDb(""){}

emailInviate::emailInviate(string acc, string path):account(acc),pathtoDb(path)
{
    if(pathtoDb != ""){
    filexml f(pathtoDb);
    if(f.apriFile()){
        int size=f.totNodi("mail");
        for(int i=0; i<size; ++i){
                v.push_back(Messaggio(f.daiTestoIn("data",i), acc,f.daiTestoIn("destinatario",i),
                                         f.daiTestoIn("messaggio",i),
                                         f.daiTestoIn("oggetto",i) ));
        }
    }
    }
}
string emailInviate::dataMailInv(unsigned int indice) const
{
    if(v.size() > indice)
        return v[indice].daiData();
    return "Errore: nessuna mail trovata";
}

string emailInviate::MailDest(unsigned int indice) const
{
    if(v.size() > indice)
        return v[indice].daiDest();
    return "Errore: nessuna mail trovata";
}

string emailInviate::MailOggeInv(unsigned int indice) const
{
    if(v.size() > indice)
        return (v[indice]).daiOgge();
    return "Errore: nessuna mail trovata";
}

string emailInviate::MailTestoInv(unsigned int indice) const
{
    if(v.size() > indice)
        return v[indice].daiMessaggio();
    return "Errore: nessuna mail trovata";
}

bool emailInviate::SendNewMessage(string data, string dest, string ogg, string testo, string pathToDest)
{
    v.push_back(Messaggio(data,account,dest,ogg,testo));
    filexml f(pathtoDb);
    filexml f2(pathToDest);
    if(f.apriFile() && f2.apriFile()){
        f.AggiungiNodo("mail");
        f.AggiungiNodoFiglioToLastNode("mail","data");
        f.AggiungiNodoFiglioToLastNode("mail","destinatario");
        f.AggiungiNodoFiglioToLastNode("mail","oggetto");
        f.AggiungiNodoFiglioToLastNode("mail","messaggio");

        f.AggiungiNodoFiglioToLastNode("data",data, true);
        f.AggiungiNodoFiglioToLastNode("destinatario",dest, true);
        f.AggiungiNodoFiglioToLastNode("oggetto",ogg, true);
        f.AggiungiNodoFiglioToLastNode("messaggio",testo, true);

        f2.AggiungiNodo("mail");
        f2.AggiungiNodoFiglioToLastNode("mail","data");
        f2.AggiungiNodoFiglioToLastNode("mail","emittente");
        f2.AggiungiNodoFiglioToLastNode("mail","oggetto");
        f2.AggiungiNodoFiglioToLastNode("mail","letto");
        f2.AggiungiNodoFiglioToLastNode("mail","messaggio");

        f2.AggiungiNodoFiglioToLastNode("data",data, true);
        f2.AggiungiNodoFiglioToLastNode("emittente",account, true);
        f2.AggiungiNodoFiglioToLastNode("oggetto",ogg, true);
        f2.AggiungiNodoFiglioToLastNode("letto","0", true);
        f2.AggiungiNodoFiglioToLastNode("messaggio",testo, true);


        return f.salva() && f2.salva();
    }
    return false;
}

bool emailInviate::elimMessInv(unsigned int i)
{
    if(v.size() > i){
    v.erase(v.begin()+i);
    filexml f(pathtoDb);
        f.EliminaNodo("mail",i);
        return f.salva();
    }
    return false;
}

int emailInviate::totMailInv() const
{
    return v.size();
}
