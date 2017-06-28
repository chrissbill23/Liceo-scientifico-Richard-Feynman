#ifndef GESTIONESEGRGROUPBOX_H
#define GESTIONESEGRGROUPBOX_H

#include "finestrepreside.h"

class QScrollArea;
class QVBoxLayout;

class GestioneSegrGroupBox : public FinestrePreside
{
    Q_OBJECT
private:
    ControllerPreside* ctrl;
    QScrollArea* contenuto;
    int currPage, totPage;
    vector<string> segr;
    QVBoxLayout* lay;
    static int maxPerPage;

    QGroupBox* loadPage(int);

public:
    GestioneSegrGroupBox(ControllerPreside* c, QWidget* parent = 0);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void viewInfoImpiegato(const QString& nomeUtente)const;
    void rimuoviImpiegato(const QString& nomeUtente);
};

#endif // GESTIONESEGRGROUPBOX_H
