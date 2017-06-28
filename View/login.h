#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
class QPushButton;
class QLabel;
class QLineEdit;
class loginController;
class login: public QWidget{
     Q_OBJECT
private:
    QLineEdit* nomeUtente;
    QLineEdit* passWord;
    QPushButton* accedi;
    loginController* controller;
    QLabel* errore;
    unsigned int tentativi;
public:
    login(loginController *c, QWidget* parent=0);

public slots:
   void loginCheck();
protected:
   void keyPressEvent(QKeyEvent*);


};

#endif // LOGIN_H
