#ifndef GESTIONEPROFGROUPBOX_H
#define GESTIONEPROFGROUPBOX_H

#include "finestrepreside.h"
#include <QPushButton>

class QScrollArea;
class QVBoxLayout;
class QLineEdit;
class GestioneProfGroupBox : public FinestrePreside
{
    Q_OBJECT
private:
    ControllerPreside* ctrl;
    QLineEdit* searchBox;
    QScrollArea* contenuto;
    int currPage, totPage;
    vector<string> prof;
    QVBoxLayout* lay;
    static int maxPerPage;

    QGroupBox* loadPage(int);

public:
    GestioneProfGroupBox(ControllerPreside* c, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void viewInfoImpiegato(const QString& nomeUtente)const;
    void rimuoviImpiegato(const QString& nomeUtente);
    void CercaImpiegato();
};

#endif // GESTIONEPROFGROUPBOX_H
