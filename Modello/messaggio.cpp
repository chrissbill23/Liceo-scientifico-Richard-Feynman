#include "messaggio.h"

Messaggio::Messaggio(string d, string e, string de, string c, string o, bool l):data(d),
    emittente(e),destinatario(de), oggetto(o),corpo(c), letto(l) {}

string Messaggio::daiData() const{  return data;}

string Messaggio::daiEmitt() const{    return emittente; }

string Messaggio::daiDest() const{ return destinatario; }

string Messaggio::daiOgge() const{

    return oggetto;
}

string Messaggio::daiMessaggio() const{  return corpo; }

bool Messaggio::isRead() const{   return letto; }

void Messaggio::setLetto(bool l){letto=l;}

bool Messaggio::operator==(const Messaggio & m) const
{
    return data == m.data && emittente == m.emittente &&
            destinatario == m.destinatario &&
            oggetto == m.oggetto && corpo == m.corpo;
}
