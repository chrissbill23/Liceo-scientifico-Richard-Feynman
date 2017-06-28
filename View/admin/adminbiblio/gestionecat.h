#ifndef GESTIONECAT_H
#define GESTIONECAT_H

#include "finestreadminbiblio.h"

class QGroupBox;
class ControllerAdminBiblio;
class QVBoxLayout;
class GestioneCat : public FinestreAdminBiblio
{
    Q_OBJECT
private:
    QGroupBox* contenuto;
    QVBoxLayout* lay;
public:
    GestioneCat(ControllerAdminBiblio* ptr,QWidget* parent = 0);
public slots:
    void reloadWindow();
protected:
    void BodyAndFooter();
};

#endif // GESTIONECAT_H
