#include "admin.h"
#include "container.h"

string Admin::pathDB="/Admin";

Admin::Admin(const string& nU):Utente(nU){}
bool Admin::esiste() const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return f.apriFile() && f.esisteTesto("NomeUtente",daiNomeUtente());
}

Utente *Admin::clone() const
{
return new Admin(*this);
}

bool Admin::VerificaPassword(const string &p) const
{
    filexml f(pathDB+"/InfoAdmin.xml");
    return f.apriFile() && f.akinTo("admin", Utente::daiNomeUtente(), p);
}

list<string> Admin::DaiDatiPersonali() const
{
list<string>l;
l.push_back(daiNomeUtente());
return l;
}

bool Admin::CambiaFotoProfilo(const string &path) const
{
    string check = checkForbiddenCharacters(path);
    if(check != "")
        return false;
    if(path != "")
    return true;
    return false;
}

bool Admin::CambiaPassword(const string &newPass) const
{
    string check = checkForbiddenCharacters(newPass);
    if(check != "" || hasSpaceOrTab(newPass) || newPass.size() < 8)
        return false;
    filexml f(pathDB+"/InfoAdmin.xml");
    f.editFiglioText("password",newPass,f.posNodo("NomeUtente",daiNomeUtente()));
    return f.salva();
}


