#ifndef FINESTREADMIN_H
#define FINESTREADMIN_H
#include "../finestre.h"
#include "../../Controller/controlleradmin.h"

class QGridLayout;
class finestreAdmin: public Finestre
{
private:
    ControllerAdmin * ctrl;
    QGridLayout* p;
public:
    finestreAdmin(ControllerAdmin *ptr, QWidget* parent = 0);
    QGridLayout* giveLayout()const;
    ControllerAdmin* getController()const;
protected:
    void Header();

};

#endif // FINESTREADMIN_H
