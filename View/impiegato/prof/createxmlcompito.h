#ifndef CREATEXMLCOMPITO_H
#define CREATEXMLCOMPITO_H

#include "createfilecompito.h"

class DomandeCompito;
class createXMLCompito: public createFileCompito
{
    Q_OBJECT
private:
    QVector<DomandeCompito*> totDom;
protected:
    bool isOk();
private slots:
    void aggiungiDomandaRispMult();
    void aggiungiDomandaAperta();
    void rimuoviUltimaDomanda();
    bool domandeCorrette()const;
public slots:
    bool salva();
public:
    createXMLCompito(ControllerProf* c, QWidget* parent);

};

#endif // CREATEXMLCOMPITO_H
