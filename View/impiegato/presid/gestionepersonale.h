#ifndef GESTIONEPERSONALE_H
#define GESTIONEPERSONALE_H

#include "finestrepreside.h"

class QVBoxLayout;
class QComboBox;
class QLineEdit;
class GestioneProfGroupBox;
class GestioneSegrGroupBox;
class QScrollArea;
class GestionePersonale : public FinestrePreside
{
    Q_OBJECT
private:
   QGroupBox* head;
   QScrollArea* body;
   GestioneProfGroupBox* prof;
   GestioneSegrGroupBox* segr;
   QComboBox* dipendenti;
   QVBoxLayout* lay;
public:
    GestionePersonale(ControllerPreside* c, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
private slots:
    void SwitchPage(int indice = -1);
public slots:
    void reloadWindow();
};

#endif // GESTIONEPERSONALE_H
