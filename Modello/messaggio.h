#ifndef MESSAGGIO_H
#define MESSAGGIO_H
#include <string>
using std::string;

class Messaggio{
private:
string data;
string emittente;
string destinatario;
string oggetto;
string corpo;
bool letto;
public:
Messaggio(string d, string e, string de, string c, string o="", bool l=true);
string daiData() const;
string daiEmitt()const;
string daiDest()const;
string daiOgge()const;
string daiMessaggio()const;
bool isRead()const;
void setLetto(bool l);
bool operator==(const Messaggio&)const;
};

#endif // MESSAGGIO_H
