#ifndef FINESTREPROF_H
#define FINESTREPROF_H

#include "../finestreimpiegato.h"
#include "../../../Controller/controllerprof.h"

class FinestreProf: public FinestreImpiegato{
    Q_OBJECT
private:
    ControllerProf* ctrl;
public:
    FinestreProf(ControllerProf* p = 0);
    ControllerProf* getController()const;
public slots:
    void CreateNewCompito();
    void vediCompiti()const;
    void cancellaCompito(const QString& codice) const;
};

#endif // FINESTREPROF_H
