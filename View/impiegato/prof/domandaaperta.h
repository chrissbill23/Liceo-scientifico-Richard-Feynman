#ifndef DOMANDAAPERTA_H
#define DOMANDAAPERTA_H

#include "domandecompito.h"
class QTextEdit;
class QVBoxLayout;
class DomandaAperta: public DomandeCompito
{
private:
    QTextEdit* domanda;
    QString Domanda;
    QTextEdit* risposta;
    QVBoxLayout* lay;

public:
    DomandaAperta(QWidget* parent);
    void setIntoCreateWidg();
    void setIntoAnswWidg();
    bool isOK(QString&)const;
    void EditDomanda(const QString& d);
    QString getDomanda()const;
    QString stampa()const;
};

#endif // DOMANDAAPERTA_H
