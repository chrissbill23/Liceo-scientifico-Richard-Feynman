#ifndef GESTIONELIBRI_H
#define GESTIONELIBRI_H

#include "../../biblio/searchresultlibri.h"

class QGroupBox;
class QVBoxLayout;
class FinestreAdminBiblio;
class ControllerAdminBiblio;
class GestioneLibri : public SearchResultLibri
{
private:
   QScrollArea* contenuto;
   FinestreAdminBiblio* fi;
   ControllerAdminBiblio* ctrl;
   int currPage, totPage;
   QVBoxLayout* lay;
public:
    GestioneLibri(ControllerAdminBiblio* ptr,FinestreAdminBiblio* parent = 0);
protected:
    void BodyAndFooter();
    QGroupBox* loadPage(int);
public slots:
    void reloadWindow();
    virtual void goNext();
    virtual void goPrev();
};

#endif // GESTIONELIBRI_H
