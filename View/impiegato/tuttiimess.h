#ifndef TUTTIIMESS_H
#define TUTTIIMESS_H

#include "finestreimpiegato.h"

class QTabWidget;
class listaMail;
class QPushButton;
class TuttiImess: public FinestreImpiegato
{
    Q_OBJECT
private:
    ControllerImpiegato* ctrl;
    QPushButton* prevWindow;
    listaMail* listric;
    listaMail* listinv;
    QTabWidget* tab;
    static int maxMailPerPage;
public:
    TuttiImess(ControllerImpiegato* ptr);
public slots:
    void reloadWindow();
protected:
    void Header();
    void BodyAndFooter();
};

#endif // TUTTIIMESS_H
