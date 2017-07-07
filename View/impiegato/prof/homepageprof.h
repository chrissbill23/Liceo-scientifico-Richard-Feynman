#ifndef HOMEPAGEPROF_H
#define HOMEPAGEPROF_H

#include "finestreprof.h"
class HomePageProf: public FinestreProf{
private:
    QGroupBox* compiti;
    QGroupBox* profilo;
    void InsertInCompiti() const;
    void InsertInProfilo() const;
public:
    HomePageProf(ControllerProf* ptr=0);
public slots:
    void reloadWindow();
protected:
    void BodyAndFooter();
};

#endif // HOMEPAGEPROF_H
