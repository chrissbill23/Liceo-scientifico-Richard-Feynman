#ifndef CONTATTOMAIL_H
#define CONTATTOMAIL_H
#include <string>
using std::string;

class ContattoMail
{
private:
   string nome, mail;
public:
    ContattoMail(string n, string m);
    string daiNomeContatto()const;
    string daiMailContatto()const;
    bool operator<(const ContattoMail& c)const;
};

#endif // CONTATTOMAIL_H
