#ifndef BUTTONMAIL_H
#define BUTTONMAIL_H
#include <QPushButton>
class FinestreImpiegato;
class buttonMail: public QPushButton
{
    Q_OBJECT
private:
    int index;
    int page;
    bool ricevuta,OnlyUnread;
    FinestreImpiegato* finestra;
public:
    buttonMail(const QString& s, int i, bool r, bool O, QWidget* f);
public slots:
    void receiveClickSig()const;
    void elimMess()const;
};

#endif // BUTTONMAIL_H
