#ifndef EMAIL_H
#define EMAIL_H
#include "messaggio.h"
#include "contattomail.h"
#include "filexml.h"
#include <vector>
using std::vector;

class emailRicevute{
private:
    string account;
    vector<Messaggio> v;
    string pathtoDb;
    vector<const Messaggio *> MailNonLetta()const;    
    int giveMessageIndex(const Messaggio& m) const;
public:
    emailRicevute();
    emailRicevute(string acc, string path);
    string dataMailRic(unsigned int indice, bool OnlyUnread=false) const;
    string MailSender(unsigned int indice, bool OnlyUnread=false) const;
    string MailOggeRic(unsigned int indice, bool OnlyUnread=false) const;
    string MailTestoRic(unsigned int indice, bool OnlyUnread=false);
    bool elimMessRic(unsigned int i);
    bool isMailRead(unsigned int i)const;
    int totMailRic()const;
    int totNuoviRic()const;
};
class emailInviate{
private:
    string account;
    vector<Messaggio> v;
    string pathtoDb;
protected:
    void setEmailInviate(string path);
public:
    emailInviate();
    emailInviate(string acc, string path);
    string dataMailInv(unsigned int indice) const;
    string MailDest(unsigned int indice) const;
    string MailOggeInv(unsigned int indice) const;
    string MailTestoInv(unsigned int indice) const;
    bool SendNewMessage(string data, string dest, string ogg, string testo, string pathToDest);
    bool elimMessInv(unsigned int i);
    int totMailInv()const;

};

class email: public emailRicevute, public emailInviate{
private:
    string account;
    filexml file;
    vector<ContattoMail> v;
    static string pathDBListaMail;
public:
    email();
    email(string a);
    string daiAccount() const;
    int totContatti()const;
    string daiNomeContatto(unsigned int indice)const;
    string daiMailContatto(unsigned int indice)const;
    bool SendNewMessage(string data,string dest,string ogg, string testo);
};

#endif // EMAIL_H
