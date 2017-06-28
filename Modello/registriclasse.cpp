#include "registriclasse.h"

RegistriClasse::RegistriClasse()
{
    c.AddFileDaLista("/studenti/Classi/TutteLeClassi.xml","registroClasse");
}

list<string> RegistriClasse::daiListaRegistri() const
{
    filexml f("/studenti/Classi/TutteLeClassi.xml");
    return f.daiTestoDiNodi("nome");
}
