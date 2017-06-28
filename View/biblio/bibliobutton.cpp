#include "bibliobutton.h"
#include "../finestre.h"

bibliobutton::bibliobutton(const QString &text, const QString c, bool ca, const QString &nomeCa, Finestre *parent): QPushButton(text,parent),
    codiceLibro(c), fi(parent), cat(ca), nomeCat(nomeCa)
{

}

QString bibliobutton::daiCodice() const
{
    return codiceLibro;
}

bool bibliobutton::isCat() const
{
    return cat;
}

QString bibliobutton::daiCat() const
{
    return nomeCat;
}

void bibliobutton::viewLibro() const
{
    fi->viewPdfFile(codiceLibro);
}

void bibliobutton::viewInfoLibro() const
{
    fi->viewInfoLibro(codiceLibro);
}

void bibliobutton::viewLibriInCat() const
{
    if(cat)
        fi->viewLibriInCateg(nomeCat);
}
