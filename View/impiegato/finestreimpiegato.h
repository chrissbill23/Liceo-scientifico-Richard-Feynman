#ifndef FINESTREIMPIEGATO_H
#define FINESTREIMPIEGATO_H

#include "../finestre.h"
#include "../../Controller/controllerimpiegato.h"

class QTimer;
class QLabel;
class QGroupBox;
class QScrollArea;
class AgendaBox;
class NotificheMailBox;
class QGridLayout;

class FinestreImpiegato: public Finestre{
    Q_OBJECT
private:
     ControllerImpiegato* ctrl;
     QLabel* FoglioPresenza;
     QTimer* t;
     NotificheMailBox* mess;
     AgendaBox* Agenda;
     QGridLayout* p;
public:
    FinestreImpiegato(ControllerImpiegato* ptr, QWidget* parent = 0);
    void leggiMess(int i, bool ricevuta, bool OnlyUnread = true);
    virtual void ElimMail(unsigned int i, bool ricevuta);
    QGridLayout* giveLayout()const;
    ControllerImpiegato* getController()const;
protected:
    void Header();
    void setStyleSheet(const QString &);
private slots:
    virtual void updateLabel() const;
    void SeeReceivedMails()const;
protected slots:
    void InviaNuovoMess();
public slots:
    void viewInfoStud(const QString& matricola)const;
};

#endif // FINESTREIMPIEGATO_H
