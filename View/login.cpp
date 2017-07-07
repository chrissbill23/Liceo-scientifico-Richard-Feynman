#include"login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include<QApplication>
#include <QPixmap>
#include <QLineEdit>
#include <iostream>
#include <QKeyEvent>
#include "../Controller/loginController.h"


login::login(loginController *c,QWidget *parent):QWidget(parent),
                        nomeUtente(new QLineEdit(this)),
                        passWord(new QLineEdit(this)), accedi(new QPushButton(tr("Accedi"), this)), controller(c),
                        errore(new QLabel(this)), tentativi(0)
{
    QFont f("Times", 11);
    nomeUtente->setMaxLength(15);
    nomeUtente-> setStyleSheet("height: 3em; background-color: white; "
                               "color: black; border-radius: 10px; "
                               "padding-left: 0.5em;");
    nomeUtente->setFixedWidth(400);
    nomeUtente->setFont(f);
    nomeUtente->setPlaceholderText("Nome utente");

    passWord->setEchoMode(QLineEdit::Password);
    passWord->setFixedWidth(400);
    passWord->setMaxLength(15);
    passWord->setStyleSheet("height: 3em;background-color: white; "
                            "color: black; border-radius: 10px; "
                            "padding-left: 0.5em");
    passWord->setFont(f);
    passWord->setPlaceholderText("Password");

    accedi-> setStyleSheet("QPushButton{background-color: #206020; "
                           "color: white; "
                           "border-radius: 5px; "
                           "}"
                           " QPushButton:hover{background-color: #e62e00;}");
    accedi->setFont(f);
    accedi->setFixedSize(200,40);
    accedi->setCursor(QCursor(Qt::PointingHandCursor));
    connect(accedi, SIGNAL(clicked()), this, SLOT(loginCheck()));

    f=QFont("Times", 13, true);
    errore->setFont(f);
    errore->setStyleSheet("color: #990000");

    QLabel* label= new QLabel(this);
    label->setFixedSize(400,300);
    label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    label->setPixmap(QPixmap(":/Database/immagini/logoscuolablu.jpg").scaled(label->width(),label->height()));
    label->setStyleSheet("border: 2px solid #602020; border-radius: 10px;");



    QVBoxLayout* layout= new QVBoxLayout(this);
    layout->addWidget(label,0,Qt::AlignTop|Qt::AlignHCenter);
    layout->addWidget(errore,0,Qt::AlignTop);
    layout->addWidget(nomeUtente,0,Qt::AlignTop|Qt::AlignHCenter);
    layout->addWidget(passWord,0,Qt::AlignTop|Qt::AlignHCenter);
    layout->addWidget(accedi,1,Qt::AlignTop|Qt::AlignHCenter);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(11,100,11,11);

    setWindowTitle(tr("log in"));
    setStyleSheet(" background-color: #29abe2");
    qApp->setStyleSheet("QLineEdit:focus {border: 2px solid #194d19;}");
    setLayout(layout);
}

void login::loginCheck()
{
QString s = nomeUtente->text();

    ++tentativi;
    if(tentativi>=1000000)
        tentativi = 1;

   if(s!="" && controller->checkNomeUtente(s)){
       s = passWord->text();
       if(controller->passwordchecker(s)){
           controller->homepage();

       }
       else{
           errore->setText("Tentativo "+QString::number(tentativi)+": Password inserita non valida");
           passWord->setFocus();
       }
   }
   else{
       errore->setText("Tentativo "+QString::number(tentativi)+": Nome utente non valido");
       nomeUtente->setFocus();

   }

}

void login::keyPressEvent(QKeyEvent * e)
{
    if(e->key()==Qt::Key_Return || e->key()==Qt::Key_Enter)
        accedi->click();

    if(e->key()==Qt::Key_Up || e->key()==Qt::Key_Down ){
    QLineEdit*p = dynamic_cast<QLineEdit*>(focusWidget());
            if(p){
                    if(p == nomeUtente)
                        passWord->setFocus();
                    else
                        nomeUtente->setFocus();
                 }
    }
}
