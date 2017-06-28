#ifndef FINESTREADMINSIST_H
#define FINESTREADMINSIST_H

#include "../finestreadmin.h"
#include"../../../Controller/controlleradminsistema.h"

class FinestreAdminSist: public finestreAdmin
{
    Q_OBJECT
private:
ControllerAdminSistema * ctrl;
public:
    FinestreAdminSist(ControllerAdminSistema* ptr);
    ControllerAdminSistema* getController()const;
public slots:
    void addPreside() const;
    void removePreside() const;
    void GestisciGruppi() const;
};

#endif // FINESTREADMINSIST_H
