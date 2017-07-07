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
    SpazioLavoro->setWidgetResizable(true);
    SpazioLavoro->setFrameShape(QFrame::NoFrame);

}

void HomePageAdminBiblio::setOnGestioneCate()
{
    GestioneCat* gestC = new GestioneCat(getController(),this);
    SpazioLavoro->setWidget(gestC);
    SpazioLavoro->setWidgetResizable(true);
}

void HomePageAdminBiblio::setOnGestionePrimoPiano()
{
    GestionePrimoPiano* gestP = new GestionePrimoPiano(getController(),this);
    SpazioLavoro->setWidget(gestP);
    SpazioLavoro->setWidgetResizable(true);
}

void HomePageAdminBiblio::BodyAndFooter()
{
    QFont f("Times", 10);
    f.setBold(true);
    QRadioButton* b1 = new QRadioButton("Gestione libri", this);
    b1->setFont(f);
    b1->setCursor(QCursor(Qt::PointingHandCursor));
    b1->setChecked(true);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(setOnGestioneLibri()));
    QRadioButton* b2 = new QRadioButton("Gestione categorie", this);
    b2->setFont(f);
    b2->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(setOnGestioneCate()));
    QRadioButton* b3 = new QRadioButton("Primo piano", this);
    b3->setFont(f);
    b3->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(setOnGestionePrimoPiano()));
    setOnGestioneLibri();
    giveLayout()->addWidget(b1,1,0);
    giveLayout()->addWidget(b2,1,1);
    giveLayout()->addWidget(b3,1,2);
    giveLayout()->addWidget(SpazioLavoro,2,0,1,5);


    QPushButton* b = new QPushButton("Cambio password", this);
    b->setFont(QFont("Times", 9));
    b->setFixedSize(150,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiaPassword()));
    giveLayout()->addWidget(b,1,3,1,2);
}
