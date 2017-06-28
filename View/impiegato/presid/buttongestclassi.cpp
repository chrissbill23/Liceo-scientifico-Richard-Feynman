#include "buttongestclassi.h"
#include "finestrepreside.h"

buttonGestClassi::buttonGestClassi(const QString &text, const QString &cla, FinestrePreside *parent) : QPushButton(text,parent), fi(parent), classe(cla)
{

}

void buttonGestClassi::removeClass()
{
    fi->rimuoviClasse(classe);
}

void buttonGestClassi::viewInfoClasse()
{
    fi->viewInfoClasse(classe);
}
