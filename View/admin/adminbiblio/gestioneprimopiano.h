#ifndef GESTIONEPRIMOPIANO_H
#define GESTIONEPRIMOPIANO_H

#include "finestreadminbiblio.h"

class QGroupBox;
class ControllerAdminBiblio;
class QVBoxLayout;

class GestionePrimoPiano : public FinestreAdminBiblio
{
    Q_OBJECT
private:
    QGroupBox* contenuto;
    QVBoxLayout* lay;
public:
    GestionePrimoPiano(ControllerAdminBiblio* ptr,QWidget* parent = 0);
public slots:
    void reloadWindow();
protected:
    void BodyAndFooter();
};

#endif // GESTIONEPRIMOPIANO_H
