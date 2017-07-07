#include "homepageprof.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>

HomePageProf::HomePageProf(ControllerProf *ptr):FinestreProf(ptr),
                                               compiti(new QGroupBox(this)),
                                               profilo(new QGroupBox(this))
{
    Header();
    BodyAndFooter();
    setWindowTitle("Home");
}

void HomePageProf::reloadWindow()
{

}

void HomePageProf::BodyAndFooter(){
    QFont f("Times", 10);
    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }


    compiti->setFont(f);
    compiti->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: white;");
    compiti->setMaximumWidth(450);
    InsertInCompiti();

    profilo->setFont(f);
    profilo->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #00b38f; color: white; ");
    profilo->setMaximumSize(460,260);
    InsertInProfilo();

    p->addWidget(compiti,2,1,1,2,Qt::AlignTop);
    p->addWidget(profilo,1,0,1,1,Qt::AlignTop);
    p->setRowStretch(3,1);

}


void HomePageProf::InsertInCompiti() const
{
    QVBoxLayout* temp2 = new QVBoxLayout(compiti);
    QFont f("Times", 12);
    QLabel* title = new QLabel("Compiti", compiti);
    title->setStyleSheet("QLabel{"
                         " padding-bottom: 0.4em; "
                         "border-bottom: 2px solid #29abe2;"
                         "border-radius:0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    temp2->addWidget(title);

    QPushButton* b = new QPushButton("Gestisci",compiti);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(vediCompiti()));

    temp2->addWidget(b);

    b = new QPushButton("Crea nuovo compito",compiti);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(CreateNewCompito()));

    temp2->addWidget(b);

    compiti->setLayout(temp2);
}

void HomePageProf::InsertInProfilo() const
{
    QGridLayout* temp2 = new QGridLayout(profilo);
    QFont f("Times", 12);
    QLabel* title = new QLabel("Profilo", profilo);
    title->setStyleSheet("QLabel{"
                         "margin-bottom: 0.4em; }");

    title->setFont(f);
    temp2->addWidget(title, 0,0);

    QLabel* g = new QLabel(profilo);
    g->setFixedSize(130,200);
    g->setPixmap(QPixmap(getController()->fotoprofilo()).scaled(g->width(),g->height()));
    temp2->addWidget(g,1, 0,6,1, Qt::AlignTop);

    QPushButton* b = new QPushButton("Cambia foto", profilo);
    b->setStyleSheet("QPushButton{"
                            "background-color: #336699;"
                            "border: 2px solid;"
                            "border-radius: 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(125,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    temp2->addWidget(b,1,1,1,1, Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiafotoProfilo()));

    b = new QPushButton("Cambia password", profilo);
    b->setStyleSheet("QPushButton{"
                            "background-color: #336699;"
                            "border: 2px solid;"
                            "border-radius: 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(150,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    temp2->addWidget(b,1,2,1,1, Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiaPassword()));

    list<string> v1 = getController()->CampiDatiProfile();
    list<string> v2 = getController()->DaiValoreCampiDatiProfile();

     int conta = 2;
     f = QFont("Times", 8);
                for(list<string>::const_iterator it = v1.begin(); it != v1.end(); ++it){
                             g=new QLabel(QString::fromStdString(*it)+":", profilo);
                             g->setStyleSheet("QLabel{color: white;}");
                             g->setFont(f);

                             temp2->addWidget(g,conta, 1,1,1, Qt::AlignTop);
                             ++conta;
                            }
                conta=2;
                for(list<string>::const_iterator it2 = v2.begin(); it2 != v2.end(); ++it2){
                    g = new QLabel(QString::fromStdString(*it2), profilo);
                    g->setStyleSheet("QLabel{border-radius: 3px; "
                                     "background-color: white; color: black; "
                                     "padding: 0.4em 0 0.4em 0.4em;}");

                    temp2->addWidget(g,conta, 2,1,1, Qt::AlignTop);
                    ++conta;

                }

    profilo->setLayout(temp2);
}


