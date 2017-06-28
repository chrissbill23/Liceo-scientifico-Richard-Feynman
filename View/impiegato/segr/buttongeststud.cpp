#include "buttongeststud.h"
#include "finestresegretari.h"

buttonGestStud::buttonGestStud(const QString &text, const QString &matr, FinestreSegretari *parent) : QPushButton(text, parent),
    matricola(matr), fi(parent)
{

}

void buttonGestStud::viewInfo() const
{
    fi->viewInfoStud(matricola);
}

void buttonGestStud::editStud()
{
    fi->editStudInfo(matricola);
}

void buttonGestStud::removeStud()
{
    fi->rimuoviStudente(matricola);
}
