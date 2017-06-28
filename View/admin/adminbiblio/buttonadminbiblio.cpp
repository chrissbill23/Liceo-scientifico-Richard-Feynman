#include "buttonadminbiblio.h"
#include "finestreadminbiblio.h"

buttonAdminBiblio::buttonAdminBiblio(const QString &text, const QString &c, bool ca, const QString &nomeCat, FinestreAdminBiblio *parent): bibliobutton(text,c,ca,nomeCat,parent),
    fin(parent)
{

}

void buttonAdminBiblio::elimLibro()
{
    fin->eliminaLibro(daiCodice());
}

void buttonAdminBiblio::elimCat()
{
    if(isCat())
        fin->eliminaCateg(daiCat());
}

void buttonAdminBiblio::editBook()
{
    fin->updateInfoLibro(daiCodice());
}

void buttonAdminBiblio::addToPrimoPiano()
{
    fin->aggiungiPrimoPiano(daiCodice());
}

void buttonAdminBiblio::elimDaPrimoPiano()
{
    fin->elimDaPrimoPiano(daiCodice());
}
