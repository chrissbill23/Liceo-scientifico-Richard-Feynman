#ifndef FINESTRESTUDENTI_H
#define FINESTRESTUDENTI_H

#include "../finestre.h"
#include "../../Controller/controllerstud.h"

class QGridLayout;
class FinestreStudenti: public Finestre{
    Q_OBJECT
private:
    QGridLayout* p;
    ControllerStud * ctrl;
public:
    void Header();
    FinestreStudenti(ControllerStud* c, QWidget* parent = 0);
    QGridLayout* giveLayout()const;
    ControllerStud* getController()const;
public slots:
    void vediCompiti()const;
    void HomePageGroup();
};

#endif // FINESTRESTUDENTI_H
