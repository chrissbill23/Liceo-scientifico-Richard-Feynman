#ifndef HOMEPAGEADMINSIST_H
#define HOMEPAGEADMINSIST_H

#include "finestreadminsist.h"

class QScrollArea;
class HomePageAdminSist: public FinestreAdminSist
{
private:
QScrollArea* SpazioLavoro;
QWidget* loadPage();
public:
    HomePageAdminSist(ControllerAdminSistema *ptr=0);
public slots:
    void reloadWindow();
protected:
    void BodyAndFooter();
};

#endif // HOMEPAGEADMINSIST_H
