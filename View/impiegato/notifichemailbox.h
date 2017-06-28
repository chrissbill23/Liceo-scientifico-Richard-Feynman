#ifndef NOTIFICHEMAILBOX_H
#define NOTIFICHEMAILBOX_H

#include <QGroupBox>

class ControllerImpiegato;
class FinestreImpiegato;
class QVBoxLayout;
class NotificheMailBox: public QGroupBox
{
    Q_OBJECT
private:
   ControllerImpiegato* ctrl;
   FinestreImpiegato* fi;
   QGroupBox* sottoBox;
   QVBoxLayout* lay;
   void Body();
public:
    NotificheMailBox(ControllerImpiegato* c, QWidget* parent = 0);
public slots:
    void reload();

};

#endif // NOTIFICHEMAILBOX_H
