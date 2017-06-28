#include "homepageadminsist.h"
#include "../../../Controller/controlleradmin.h"
#include <QScrollArea>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>

QWidget *HomePageAdminSist::loadPage()
{
    QGroupBox* temp = new QGroupBox;

    QFont f("Times", 15);

    QLabel* title = new QLabel("GESTIONE SISTEMA", temp);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid white;"
                         "border-radius: 0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    QVBoxLayout* p2 = new QVBoxLayout(temp);

    p2->addWidget(title,0,Qt::AlignTop);

    f = QFont("Times", 11);

    QPushButton* b = new QPushButton("Inserici un nuovo presidente", temp);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(500,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b, SIGNAL(clicked(bool)), this, SLOT(addPreside()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Rimuovi attuale preside", temp);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(500,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(removePreside()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Gestisci gruppi", temp);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(500,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this, SLOT(GestisciGruppi()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Cambio password", temp);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(500,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiaPassword()));
    p2->addWidget(b,1,Qt::AlignTop|Qt::AlignHCenter);

    temp->setLayout(p2);

    return temp;
}

HomePageAdminSist::HomePageAdminSist(ControllerAdminSistema *ptr):FinestreAdminSist(ptr),SpazioLavoro(new QScrollArea(this)){
    Header();
    BodyAndFooter();

    QGridLayout* p = giveLayout();
    p->addWidget(SpazioLavoro,1,0,2,4);

    setWindowTitle("Workspace");
}

void HomePageAdminSist::reloadWindow()
{
    SpazioLavoro->setWidget(loadPage());
    SpazioLavoro->setWidgetResizable(true);
}


void HomePageAdminSist::BodyAndFooter()
{

    SpazioLavoro->setWidget(loadPage());
    SpazioLavoro->setWidgetResizable(true);
    SpazioLavoro->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #476b6b; color: white;");

}

