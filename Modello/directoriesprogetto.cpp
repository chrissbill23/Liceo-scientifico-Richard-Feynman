#include <QDir>
#include "directoriesprogetto.h"
string DirectoriesProgetto::pathDB=QDir::currentPath().toStdString()+"../progetto-pao-2017/Database";

string DirectoriesProgetto::pathStudDB()
{
    return pathDB+"/studenti";
}

string DirectoriesProgetto::pathImpiegatoDB()
{
    return pathDB+"/Impiegati";
}

string DirectoriesProgetto::pathMessDB()
{
    return pathDB+"/Messaggi";
}
