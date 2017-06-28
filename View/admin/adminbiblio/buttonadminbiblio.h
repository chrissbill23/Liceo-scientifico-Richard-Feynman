#ifndef BUTTONADMINBIBLIO_H
#define BUTTONADMINBIBLIO_H

#include "../../biblio/bibliobutton.h"

class FinestreAdminBiblio;

class buttonAdminBiblio : public bibliobutton
{
    Q_OBJECT
private:
    FinestreAdminBiblio* fin;
public:
    buttonAdminBiblio(const QString& text, const QString& c, bool ca = false, const QString& nomeCat = "", FinestreAdminBiblio* parent = 0);
public slots:
    void elimLibro();
    void elimCat();
    void editBook();
    void addToPrimoPiano();
    void elimDaPrimoPiano();
};

#endif // BUTTONADMINBIBLIO_H
