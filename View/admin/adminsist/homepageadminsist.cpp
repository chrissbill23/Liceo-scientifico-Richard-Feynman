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

    QFont f("Times", 12);

    QLabel* title = new QLabel("GESTIONE SISTEMA", temp);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid;"
                         "border-radius: 0;}");

    title->setFont(f);
    QVBoxLayout* p2 = new QVBoxLayout(temp);

    p2->addWidget(title,0,Qt::AlignTop);

    f = QFont("Times", 10);

    QPushButton* b = new QPushButton("Gestisci gruppi", temp);
    b->setFixedSize(400,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this, SLOT(GestisciGruppi()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Cambio password", temp);
    b->setFixedSize(400,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiaPassword()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Inserici un nuovo presidente", temp);
    b->setFixedSize(400,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b, SIGNAL(clicked(bool)), this, SLOT(addPreside()));
    p2->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Rimuovi attuale preside", temp);
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     "color: white;"
                     " border-radius: 5px;}"
                     "QPushButton:pressed {"
                     " background-color:#660000;}");
    b->setFixedSize(400,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(removePreside()));
    p2->addWidget(b,1,Qt::AlignTop|Qt::AlignHCenter);

    temp->setLayout(p2);

    return temp;
}

HomePageAdminSist::HomePageAdminSist(ControllerAdminSistema *ptr):FinestreAdminSist(ptr),SpazioLavoro(new QScrollArea(this)){
    Header();
    BodyAndFooter();

    QGridLayout* p = giveLayout();
    p->addWidget(SpazioLavoro,1,0,1,1);

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


}

