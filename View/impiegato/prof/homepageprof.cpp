#include "homepageprof.h"
#include "compitiniwidgbox.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

HomePageProf::HomePageProf(ControllerProf *ptr):FinestreProf(ptr),
                                               compiti(new CompitiniWidgBox(this)),
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
    QFont f("Times", 11);
    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }


    compiti->setFont(f);
    compiti->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #e8e3e3;");
    compiti->setFixedSize(500,300);

    profilo->setFont(f);
    profilo->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #00b38f; color: white; ");
    profilo->setFixedSize(500,300);
    InsertInProfilo();

    p->addWidget(compiti,2,1,2,1,Qt::AlignTop);
    p->addWidget(profilo,2,2,2,2,Qt::AlignTop);
    setLayout(p);

}


void HomePageProf::InsertInProfilo() const
{
    QGridLayout* temp2= new QGridLayout(profilo);
    QFont f("Times", 15);
    QLabel* title= new QLabel("Profilo", profilo);
    title->setStyleSheet("QLabel{"
                         " padding-bottom: 0.4em; "
                         "border-radius:0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    temp2->addWidget(title, 0,0);

    QLabel* g=new QLabel(profilo);
    g->setFixedSize(100,100);
    g->setPixmap(QPixmap(getController()->fotoprofilo()).scaled(g->width(),g->height()));
    g->setStyleSheet("QLabel{margin: 0 15px 0 0;}");
    temp2->addWidget(g,1, 0,1,2);

    QPushButton* b = new QPushButton("Cambia foto profilo", profilo);
    b->setStyleSheet("QPushButton{"
                            "background-color: #29abe2;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(150,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    temp2->addWidget(b,1,1,1,1);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiafotoProfilo()));

    b = new QPushButton("Cambia password", profilo);
    b->setStyleSheet("QPushButton{"
                            "background-color: #29abe2;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(150,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    temp2->addWidget(b,1,2,1,1);
    connect(b,SIGNAL(clicked(bool)),this, SLOT(cambiaPassword()));

    list<string> v1 = getController()->CampiDatiProfile();
    list<string> v2 = getController()->DaiValoreCampiDatiProfile();

     int conta =2;
     f = QFont("Times", 9);
                for(list<string>::const_iterator it = v1.begin(); it != v1.end(); ++it){
                             g=new QLabel(QString::fromStdString(*it)+":", profilo);
                             g->setStyleSheet("QLabel{color: white;}");
                             g->setFont(f);

                             temp2->addWidget(g,conta, 0);
                             ++conta;
                            }
                conta=2;
                for(list<string>::const_iterator it2 = v2.begin(); it2 != v2.end(); ++it2){
                    g=new QLabel(QString::fromStdString(*it2), profilo);
                    g->setStyleSheet("QLabel{border-radius: 15px 15px 15px 15px; background-color: white; color: black; padding-left: 1em;}");

                    temp2->addWidget(g,conta, 1,1,3);
                    ++conta;

                }

    profilo->setLayout(temp2);
}


