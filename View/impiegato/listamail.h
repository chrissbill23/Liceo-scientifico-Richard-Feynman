#ifndef LISTAMAIL_H
#define LISTAMAIL_H

#include "finestreimpiegato.h"
class QVBoxLayout;
class listaMail : public FinestreImpiegato
{
    Q_OBJECT
private:
    ControllerImpiegato* ctrl;
    int tot;
    int max;
    int currPage;
    int totPage;
    bool ricevuti;
    QScrollArea* box;
    QVBoxLayout* p;
    QGroupBox *setPageRic(int indice);
    QGroupBox *setPageInv(int indice);
public:
    listaMail(ControllerImpiegato* c, bool ric = true);
    void loadMails();
    void setMaxPerPage(int Max);
    void ElimMail(unsigned int i, bool ricevuta);
    void loadWindow();
protected:
    void Header();
    void BodyAndFooter();
private slots:
    void goToNextPage();
    void goToPrevPage();
public slots:
    void reloadWindow();
};

#endif // LISTAMAIL_H
