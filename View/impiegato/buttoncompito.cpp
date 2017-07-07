#include "buttoncompito.h"
#include "./prof/viewcompitiprof.h"

buttonCompito::buttonCompito(const QString &text, const QString &c, ViewCompiti *parent, bool r, int i, const QString &p): QPushButton(text,parent),
    fi(parent),
    codice(c),risposta(r),Indicerisposta(i), pathRisposta(p)
{

}

void buttonCompito::cancellaCompito() const
{
    /* ViewCompitiProf* p = dynamic_cast<ViewCompitiProf*>(fi);
   if(p)
        p->cancellaCompito(codice);*/
}

void buttonCompito::ShowCompito() const
{
    if(fi)
        fi->parseCompitoFile(codice);
}

void buttonCompito::viewElaborati() const
{
    ViewCompitiProf* p = dynamic_cast<ViewCompitiProf*>(fi);
       if(p)
           p->viewElaborati(codice);
}

void buttonCompito::viewElaborato() const
{
    if(fi && pathRisposta != "")
        fi->viewPdfFile(pathRisposta);
}

void buttonCompito::commentaRispCompito() const
{
    if(risposta)
        fi->commentaRisp(codice,Indicerisposta);
}

void buttonCompito::viewcommentRisp() const
{
    if(risposta)
        fi->viewCommento(codice,Indicerisposta);
}

void buttonCompito::elimCompito()
{
    fi->elimCompito(codice);
}

void buttonCompito::aggiungiClasse()
{
    ViewCompitiProf* p = dynamic_cast<ViewCompitiProf*>(fi);
       if(p)
           p->aggiungiClasse(codice);
}

void buttonCompito::Dettagli() const
{
    if(fi)
        fi->InfoCompito(codice);
}
