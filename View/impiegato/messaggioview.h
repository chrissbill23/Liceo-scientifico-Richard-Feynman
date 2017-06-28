#ifndef MESSAGGIOVIEW_H
#define MESSAGGIOVIEW_H
#include <QDialog>

class ControllerImpiegato;
class QLabel;
class MessaggioView: public QDialog
{
private:
    ControllerImpiegato* ctrl;
    int index;
    QLabel* data;
    QLabel* oggetto;
    QLabel* emitt;
    QLabel* Messaggio;
public:
    MessaggioView(ControllerImpiegato* ptr, QWidget* parent=0);
    void SelectMessage(int index, bool ricevuta, bool OnlyUnread=false);
};

#endif // MESSAGGIOVIEW_H
