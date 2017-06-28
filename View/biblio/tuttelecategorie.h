#ifndef TUTTELECATEGORIE_H
#define TUTTELECATEGORIE_H

#include "finestrebiblioteca.h"
#include "../../Controller/Controller.h"
class QLineEdit;
class QGroupBox;
class QScrollArea;
class TutteleCategorie : public FinestreBiblioteca
{
    Q_OBJECT
private:
    vector<string> categorie;
    QLineEdit* searchBox;
    QScrollArea* sc;
    int currPage;
    int totPage;
    static int maxPerPage;

    QGroupBox* loadPage(int);
public:
    TutteleCategorie(Controller* c, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
private slots:
    void searchCategoria();
};

#endif // TUTTELECATEGORIE_H
