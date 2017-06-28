#ifndef HOMEPAGEPRESIDE_H
#define HOMEPAGEPRESIDE_H

#include "finestrepreside.h"

class HomePagePreside: public FinestrePreside{
private:
    QGroupBox* AreaLavoro;
    QGroupBox* profile;
    void InsertInAreaLavoro() const;
    void InsertInProfile()const;
public:
    HomePagePreside(ControllerPreside* ptr);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
};

#endif // HOMEPAGEPRESIDE_H
