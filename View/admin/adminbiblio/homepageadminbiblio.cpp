#include "homepageadminbiblio.h"
#include "gestionelibri.h"
#include "gestionecat.h"
#include "gestioneprimopiano.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>


HomePageAdminBiblio::HomePageAdminBiblio(ControllerAdminBiblio* ptr):FinestreAdminBiblio(ptr),
    SpazioLavoro(new QScrollArea(this)){
    Header();
    BodyAndFooter();
    setWindowTitle("Workspace");
}

void HomePageAdminBiblio::reloadWindow()
{
  dynamic_cast<Finestre*>(SpazioLavoro->widget())->reloadWindow();
}

void HomePageAdminBiblio::setOnGestioneLibri()
{
    GestioneLibri* gestL = new GestioneLibri(getController(),this);
    SpazioLavoro->setWidget(gestL);   
    gestL->setStyleSheet("GestioneLibri{background-color: #476b6b; color: white;}");
    SpazioLavoro->setWidgetResizable(true);
    SpazioLavoro->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #476b6b; color: white;");

}

void HomePageAdminBiblio::setOnGestioneCate()
{
    GestioneCat* gestC = new GestioneCat(getController(),this);
    gestC->setStyleSheet("GestioneLibri{background-color: #476b6b; color: white;}");
    SpazioLavoro->setWidget(gestC);
    SpazioLavoro->setWidgetResizable(true);
    SpazioLavoro->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #476b6b; color: white;");
}

void HomePageAdminBiblio::setOnGestionePrimoPiano()
{
    GestionePrimoPiano* gestP = new GestionePrimoPiano(getController(),this);
    SpazioLavoro->setWidget(gestP);   
    gestP->setStyleSheet("GestioneLibri{background-color: #476b6b; color: white;}");
    SpazioLavoro->setWidgetResizable(true);
    SpazioLavoro->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #476b6b; color: white;");
}


HomePageAdminBiblio::~HomePageAdminBiblio()
{
    QWidget* p = SpazioLavoro->widget();
    if(p)
        delete p;
}

void HomePageAdminBiblio::BodyAndFooter()
{
    QFont f("Times", 13);
    f.setBold(true);
    QRadioButton* b1 = new QRadioButton("Gestione libri", this);
    b1->setFont(f);
    b1->setChecked(true);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(setOnGestioneLibri()));
    QRadioButton* b2 = new QRadioButton("Gestione categorie", this);
    b2->setFont(f);
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(setOnGestioneCate()));
    QRadioButton* b3 = new QRadioButton("Libri in primo piano", this);
    b3->setFont(f);
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(setOnGestionePrimoPiano()));
    setOnGestioneLibri();
    giveLayout()->addWidget(b1,1,0);
    giveLayout()->addWidget(b2,1,1);
    giveLayout()->addWidget(b3,1,2);
    giveLayout()->addWidget(SpazioLavoro,2,0,5,5);


    QPushButton* b = new QPushButton("Cambio password", this);
    b->setFont(QFont("Times", 9));
    b->setFixedSize(300,30);
    b->setStyleSheet("QPushButton{"
                     "background-color: green;"
                     "border: 2px solid;"
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiaPassword()));
    giveLayout()->addWidget(b,1,3,1,2);
}
