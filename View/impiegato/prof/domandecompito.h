#ifndef DOMANDECOMPITO_H
#define DOMANDECOMPITO_H

#include <QGroupBox>

class DomandeCompito: public QGroupBox
{
public:
    DomandeCompito(QWidget* parent);
    virtual void setIntoCreateWidg() = 0;
    virtual void setIntoAnswWidg() =0;
    virtual QString stampa()const = 0;
    virtual bool isOK(QString&)const = 0;
};

#endif // DOMANDECOMPITO_H
