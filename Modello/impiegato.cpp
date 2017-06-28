#include"impiegato.h"
#include "container.h"

Impiegato::Impiegato(string NomeUtente) : Utente(NomeUtente), mansione(""){
}


int Impiegato::TotMailRic() const
{
    return em.totMailRic();
}

int Impiegato::TotMailInv() const
{
    return em.totMailInv();
}


int Impiegato::TotContatti() const
{
    return em.totContatti();
}

string Impiegato::daiNomeContatto(unsigned int i) const
{
    return em.daiNomeContatto(i);
}

string Impiegato::daiMailContatto(unsigned int i) const
{
    return em.daiMailContatto(i);
}

void Impiegato::schedaClasse(const string &nomeclasse,filexml & file) const
{
    filexml f1("/studenti/Classi/TutteLeClassi.xml");
    file = filexml(f1.daiTestoIn("riferimentoFile",f1.posNodo("nome",nomeclasse)));
}

void Impiegato::schedaPersonaleStud(const string &matricola, filexml & file) const
{
    filexml f1("/studenti/NUStud.xml");
   file = filexml(f1.daiTestoIn("schedaPersonale",f1.posNodo("Matricola",matricola)));
}

void Impiegato::TuttiGliStudenti(vector<string> &matricola, vector<string> &NomeUtente,
                                 vector<string> &Cognome, vector<string> &nome, vector<string> &classe) const
{
    Container<filexml> c;
    c.AddFileDaLista("/studenti/NUStud.xml","schedaPersonale");
    for(Container<filexml>::Iteratore it = c.begin(); it != c.end(); ++it){
        filexml& f = *it;
        if(f.apriFile()){
        matricola.push_back(f.daiTestoIn("Matricola"));
        NomeUtente.push_back(f.daiTestoIn("nomeUtente"));
        Cognome.push_back(f.daiTestoIn("Cognome"));
        nome.push_back(f.daiTestoIn("Nome"));
        classe.push_back(f.daiTestoIn("Classe"));
        }
    }
}

void Impiegato::InizializzaDatiPersonali(string n, string c, string f, string m, string mel)
{
    Utente::InizializzaDatiPersonali(n,c,f);
    mansione = m;
    em = mel;
}

list<string> Impiegato::DaiDatiPersonali() const
{
    list<string> l;
    l.push_back(Utente::daiCognome());
    l.push_back(Utente::daiNome());
    l.push_back(Utente::daiNomeUtente());
    l.push_back(em.daiAccount());
    l.push_back(mansione);
    return l;
}

int Impiegato::totMessNuovi() const
{
   return em.totNuoviRic();
}

string Impiegato::daiMansione() const
{
    return mansione;
}

string Impiegato::daiMail() const
{
    return em.daiAccount();
}

bool Impiegato::isMailRead(unsigned int indice) const
{
    return em.isMailRead(indice);
}

string Impiegato::LeggidataMail(unsigned int indice,bool ricevuta, bool unread) const
{
    return (ricevuta) ? em.dataMailRic(indice, unread): em.dataMailInv(indice);
}

string Impiegato::LeggiMailSender(unsigned int indice, bool ricevuta, bool unread) const
{
    return (ricevuta) ? em.MailSender(indice, unread): "Tu.";
}

string Impiegato::LeggiMailDest(unsigned int indice) const
{
    return em.MailDest(indice);
}

string Impiegato::LeggiMailOgge(unsigned int indice,bool ricevuta, bool unread) const
{
return (ricevuta) ? em.MailOggeRic(indice, unread): em.MailOggeInv(indice);
}

string Impiegato::LeggiMailTesto(unsigned int indice, bool ricevuta, bool unread)
{
    return (ricevuta) ? em.MailTestoRic(indice, unread): em.MailTestoInv(indice);
}

string Impiegato::SendNewMessage(const string& data, const string &dest, const string & ogg, const string &testo)
{
    string check = checkForbiddenCharacters(data);
    if(check == ""){
        check = checkForbiddenCharacters(dest);
        if(check == ""){
            check = checkForbiddenCharacters(ogg);
            if(check == ""){
                check = checkForbiddenCharacters(testo);
                if(check == ""){
                    if(em.SendNewMessage(data,dest,ogg,testo))
                    check = "";
                    else check = "Oops, non sono riuscito ad inviare il messaggio. "
                                 "Verifica che l'email del destinatario sia corretta. Se il problema persiste,"
                                 " la prego di farlo sapere all'aministratore";
                }
            }
        }
    }
    return check;
}

bool Impiegato::eliminaMail(unsigned int index, bool ricevuta)
{
    return ricevuta ? em.elimMessRic(index): em.elimMessInv(index);
}
