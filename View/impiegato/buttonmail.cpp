#include "buttonmail.h"
#include "finestreimpiegato.h"

buttonMail::buttonMail(const QString &s, int i, bool r, bool O, QWidget *f):QPushButton(s,f), index(i),
    ricevuta(r), OnlyUnread(O), finestra(dynamic_cast<FinestreImpiegato*>(f))
{}

void buttonMail::receiveClickSig() const
{
    if(finestra)
    finestra->leggiMess(index,ricevuta,OnlyUnread);
}

void buttonMail::elimMess() const
{
    if(finestra)
    finestra->ElimMail(index,ricevuta);
}
