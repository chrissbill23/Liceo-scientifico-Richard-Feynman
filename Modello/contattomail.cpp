#include "contattomail.h"

ContattoMail::ContattoMail(string n,string m): nome(n),mail(m){}

string ContattoMail::daiNomeContatto() const
{
    return nome;
}

string ContattoMail::daiMailContatto() const
{
    return mail;
}

bool ContattoMail::operator<(const ContattoMail &c) const
{
    return nome < c.nome;
}
