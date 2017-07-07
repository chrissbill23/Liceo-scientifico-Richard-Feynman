#include "gestionepersonale.h"
#include "gestioneprofgroupbox.h"
#include "gestionesegrgroupbox.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QScrollArea>

GestionePersonale::GestionePersonale(ControllerPreside *c, QWidget *parent):FinestrePreside(c,parent),head(0)
 , body(0), prof(0), segr(0), dipendenti(0), lay(0)
{
    Header();
    BodyAndFooter();
    setStyleSheet("background-color: none;");
    setLayout(lay);
    setWindowTitle("Gestione impiegati");
}

void GestionePersonale::Header()
{
    head = new QGroupBox(this);
    head->setStyleSheet("QGroupBox{border: 0;}");

    QGridLayout* p = new QGridLayout(head);

    head->setLayout(p);

    QFont f("Times",11);
    QPushButton* previousWindow = new QPushButton("Indietro", head);
    previousWindow->setFixedSize(150, 40);
    previousWindow->setFont(f);
    previousWindow->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    previousWindow->setCursor(QCursor(Qt::PointingHandCursor));
    connect(previousWindow,SIGNAL(clicked(bool)),this,SLOT(TornaIndietro()));

    p->addWidget(previousWindow,0,0,1,1,Qt::AlignLeft);

    QPushButton* logout = new QPushButton("logout", head);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(logout,SIGNAL(clicked(bool)),this,SLOT(signout()));

    p->addWidget(logout,0,2,1,1,Qt::AlignRight);

    dipendenti = new QComboBox(head);
    dipendenti->addItem("Gestisci i professori",0);
    dipendenti->addItem("Gestisci i segretari",1);
    dipendenti->setFixedSize(300,40);
    dipendenti->setFont(f);
    connect(dipendenti, SIGNAL(currentIndexChanged(int)), this, SLOT(SwitchPage(int)));

    p->addWidget(dipendenti, 1,1,1,1,Qt::AlignHCenter);

    QPushButton* b = new QPushButton("Nuovo impiegato",this);
    b->setFont(QFont("Times",10));
    b->setFixedSize(150,40);
    b->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addImpiegato()));
    p->addWidget(b,1,2,1,1,Qt::AlignLeft);


    if(!lay)
        lay = new QVBoxLayout(this);
    lay->addWidget(head,0, Qt::AlignTop);
}

void GestionePersonale::BodyAndFooter()
{
    body = new QScrollArea(this);
    SwitchPage();
    lay->addWidget(body,1);
}

void GestionePersonale::SwitchPage(int indice)
{
    indice = dipendenti->currentIndex();
    if(indice == 0){
        prof = new GestioneProfGroupBox(getController(),this);
        body->setWidget(prof);
        body->setWidgetResizable(true);
    }
    else{
        segr = new GestioneSegrGroupBox(getController(), this);
        body->setWidget(segr);
        body->setWidgetResizable(true);
    }
}

void GestionePersonale::reloadWindow()
{
    dynamic_cast<FinestrePreside*>(body->widget())->reloadWindow();
}
