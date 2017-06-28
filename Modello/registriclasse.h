#ifndef REGISTRICLASSE_H
#define REGISTRICLASSE_H

#include "container.h"

class RegistriClasse
{
private:
    Container<filexml> c;
public:
    RegistriClasse();
    list<string>daiListaRegistri()const;
};

#endif // REGISTRICLASSE_H
