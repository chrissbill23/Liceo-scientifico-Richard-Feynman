#include "buttongestimp.h"
#include "finestrepreside.h"

buttonGestImp::buttonGestImp(const QString &text, const QString &nu, FinestrePreside *parent) : QPushButton(text,parent), fi(parent),
    nomeUtente(nu)
{

}

void buttonGestImp::vediInfoImp() const
{
    fi->viewInfoImpiegato(nomeUtente);
}

void buttonGestImp::AssegnaClasseProf() const
{
    fi->assegnaMateriaAProf(nomeUtente);
}

void buttonGestImp::RimuoviClasseProf() const
{
    fi->RimuoviMateriaAProf(nomeUtente);
}

void buttonGestImp::ElimImp()
{
    fi->rimuoviImpiegato(nomeUtente);
}
