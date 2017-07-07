#include "homepagepreside.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QPushButton>
#include "../../../Controller/controllerpreside.h"

HomePagePreside::HomePagePreside(ControllerPreside *ptr):FinestrePreside(ptr),
    AreaLavoro(new QGroupBox(this)),
    profile(new QGroupBox(this))
{
Header();
BodyAndFooter();
setWindowTitle("Home");
setStyleSheet(" background-color: #29abe2");
}

void HomePagePreside::reloadWindow()
{

}

void HomePagePreside::BodyAndFooter()
{
    QFont f("Times", 15);

    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }
    AreaLavoro->setFont(f);
    AreaLavoro->setStyleSheet("border-radius: 15px; background-color: #e8e3e3;");
    AreaLavoro->setMaximumSize(450,300);
    InsertInAreaLavoro();


    profile->setStyleSheet("border-radius: 15px; background-color: #FFCC99;");
    InsertInProfile();
    profile->setMaximumSize(450,350);

    p->addWidget(AreaLavoro,2,1,1,2,Qt::AlignTop);
    p->addWidget(profile, 1,0,1,1,Qt::AlignTop);
    p->setRowStretch(3,1);

}


void HomePagePreside::InsertInAreaLavoro() const
{
    QVBoxLayout* temp2= new QVBoxLayout(AreaLavoro);
    QFont f("Times", 12);
    QLabel* title = new QLabel("Spazio lavoro", AreaLavoro);
    title->setStyleSheet("QLabel{"
                         " padding-bottom: 0.4em; "
                         "border-bottom: 2px solid #29abe2;"
                         "border-radius:0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    temp2->addWidget(title,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Gestione personale", AreaLavoro);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(gestionePersonale()));
    temp2->addWidget(b,0,Qt::AlignTop);

    b = new QPushButton("Gestione classi", AreaLavoro);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)), this, SLOT(gestioneClassi()));
    temp2->addWidget(b,1, Qt::AlignTop);

    AreaLavoro->setLayout(temp2);
}

void HomePagePreside::InsertInProfile() const
{
    QFont f("Times", 12);
    QLabel* title = new QLabel("PROFILO", profile);
    title->setStyleSheet("QLabel{"
                         "margin-bottom: 0.4em; }");

    title->setFont(f);

    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    QLabel* g=new QLabel(profile);
    g->setFixedSize(130,200);
    g->setPixmap(QPixmap(getController()->fotoprofilo()).scaled(g->width(),g->height()));
    p->addWidget(g,1, 0,7,1, Qt::AlignTop);

    QPushButton* b = new QPushButton("Cambia foto", profile);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(125,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,1,1,1,1, Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiafotoProfilo()));


    b = new QPushButton("Cambia password", profile);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(150,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,1,2,1,1, Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiaPassword()));

    list<string> v1 = getController()->CampiDatiProfile();
    list<string> v2 = getController()->DaiValoreCampiDatiProfile();

     int conta = 2;
     f = QFont("Times", 8);
                for(list<string>::const_iterator it=v1.begin(); it != v1.end(); ++it){
                             g = new QLabel(QString::fromStdString(*it)+":", profile);
                             g->setStyleSheet("QLabel{color: grey;}");
                             g->setFont(f);

                             p->addWidget(g,conta, 1,1,1,Qt::AlignTop);
                             ++conta;
                            }
                conta=2;
                for(list<string>::const_iterator it2 = v2.begin(); it2 != v2.end(); ++it2){
                    g=new QLabel(QString::fromStdString(*it2), profile);
                    g->setStyleSheet("QLabel{border-radius: 3px; "
                                     "background-color: white; "
                                     "padding: 0.4em 0 0.4em 0.4em;}");

                    p->addWidget(g,conta, 2,1,1, Qt::AlignTop);
                    ++conta;

                }
                profile->setLayout(p);
}

