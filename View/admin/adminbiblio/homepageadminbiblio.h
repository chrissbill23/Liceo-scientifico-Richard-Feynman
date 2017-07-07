#ifndef HOMEPAGEADMINBIBLIO_H
#define HOMEPAGEADMINBIBLIO_H

#include "finestreadminbiblio.h"

class QScrollArea;
class HomePageAdminBiblio: public FinestreAdminBiblio
{
    Q_OBJECT
private:
QScrollArea* SpazioLavoro;
public:
    HomePageAdminBiblio(ControllerAdminBiblio *ptr = 0);
public slots:
    void reloadWindow();
    void setOnGestioneLibri();
    void setOnGestioneCate();
    void setOnGestionePrimoPiano();
protected:
    void BodyAndFooter();
};

#endif // HOMEPAGEADMINBIBLIO_H
