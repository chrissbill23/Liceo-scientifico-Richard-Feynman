#include "homepagestud.h"
#include"../Controller/controllerstud.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

HomePageStud::HomePageStud(ControllerStud*contrl, QWidget *parent):QWidget(parent),gruppi(new QGroupBox( this)),
                                            compiti(new QGroupBox(this)),
                                            profile(new QGroupBox(this)),
                                            wallnews(new QGroupBox(this)),
                                            ctrl(contrl)
{
    resize(1500, 1000);
    QFont f("Times", 11);
    gruppi->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #476b6b;}");
    InsertInGruppi();
    compiti->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #4d2600; }");
    InsertInCompiti();
    profile->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #00004d;");
    InsertInProfile();
    wallnews->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: white;color: #29abe2;padding: 0;}");
    InsertInNews();
    QPushButton* biblio= new QPushButton("Visita la Biblioteca", this);
    biblio->setFixedSize(200, 40);
    biblio->setFont(f);
    biblio->setStyleSheet("QPushButton{"
                          "background-color: green; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    biblio->setCursor(QCursor(Qt::PointingHandCursor));
    QPushButton* logout= new QPushButton("logout", this);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(logout,SIGNAL(clicked()), this, SLOT(signout()));
    QGridLayout* p = new QGridLayout(this);
    p->addWidget(biblio, 0, 3);
    p->addWidget(logout, 0, 4);
    p->addWidget(wallnews, 1,0, 3,1);
    p->addWidget(gruppi, 1, 1,1,1);
    p->addWidget(compiti, 2, 1,1,1);
    p->addWidget(profile, 1, 3,1,2);
    setLayout(p);
    setStyleSheet(" background-color: #29abe2");
}

void HomePageStud::signout()
{
    ctrl->signout();
}

void HomePageStud::InsertInGruppi() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("I TUOI GRUPPI", gruppi);
    title->setStyleSheet("QLabel{"
                         "color: white;"
                         "background-color: #476b6b;"
                         "height: 2em;}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(gruppi);
    p->addWidget(title,0, 0,1,2);

    vector<string> v= ctrl->daiNomiGrupi();
    int size= v.size();

    if(size > 0){
     int conta =1;
            for(vector<string>::const_iterator it=v.begin(); it != v.end() && conta<= 8; ++it)
                    {
                             QLabel* g=new QLabel(QString::fromStdString((*it)), gruppi);
                             f= QFont("Times", 9);
                             g->setStyleSheet("QLabel{"
                                                      "color: white;"
                                                      "background-color: #476b6b;"
                                                      "}");
                             g->setFont(f);
                             QPushButton* b= new QPushButton("Clicca Per Entrare", gruppi);
                             b->setStyleSheet("QPushButton{"
                                              "background-color: green;"
                                              "border: 2px solid;"
                                              "border-radius: 5px 5px 5px 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                              "background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));

                             p->addWidget(g,conta, 0,1,3);
                             p->addWidget(b,conta, 4);
                             ++conta;
                            }
QPushButton* b=0;
    if(size> 8){
    b= new QPushButton("Vedi Altri Tuoi Gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: green;"
                     "border-radius: 5px 5px 5px 5px;"
                     "border: 2px solid;"
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#003300;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));

    p->addWidget(b,conta, 0);
    b=new QPushButton("Visita Altri Gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     "border-radius: 5px 5px 5px 5px;"
                     "border: 2px solid;"
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#660000;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));

    p->addWidget(b,conta, 1);
    }
    else{
        b=new QPushButton("Visita Altri Gruppi", gruppi);
        b->setStyleSheet("QPushButton{"
                         "background-color: #990000;"
                         "border-radius: 5px 5px 5px 5px;"
                         "border: 2px solid;"
                         "color: white;}"
                         "QPushButton:pressed {"
                         "background-color:#660000;}");
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));

        p->addWidget(b,conta, 0, 1, 3);
    }


    }
    else{
        QLabel* g=new QLabel("Non Sei Ancora Iscritto A Nessun Gruppo", gruppi);
        f= QFont("Times", 9);
        g->setStyleSheet("QLabel{"
                                 "color: white;"
                                 "background-color: #476b6b;"
                                 "}");
        g->setFont(f);
        p->addWidget(g,1, 0,2,3);
        QPushButton* b= new QPushButton("Scopri Tutti Gruppi", gruppi);
        b->setStyleSheet("QPushButton{"
                         "background-color: #990000;"
                         "border-radius: 5px 5px 5px 5px;"
                         "border: 2px solid;"
                         "color: white;}"
                         "QPushButton:pressed {"
                         "background-color:#660000;}");
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));

        p->addWidget(b,2, 0, 1, 3);
    }

    gruppi->setLayout(p);
}

void HomePageStud::InsertInCompiti() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("I TUOI COMPITI", compiti);
    title->setStyleSheet("QLabel{"
                         "color: yellow;"
                         "background-color: #4d2600;}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(compiti);
    p->addWidget(title,0, 0,1,2);

    vector<string> v = ctrl->DaiMaterie();
     int conta =1;
                for(vector<string>::const_iterator it=v.begin(); it != v.end(); ++it){
                             QLabel* g=new QLabel(QString::fromStdString(*it), compiti);
                             g->setStyleSheet("QLabel{color: yellow; background-color: #4d2600;}");

                             QPushButton* b= new QPushButton("Clicca Per Vedere", compiti);
                             b->setStyleSheet("QPushButton{"
                                              "background-color: green;"
                                              "border: 2px solid;"
                                              "border-radius: 5px 5px 5px 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                              "background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));

                             p->addWidget(g,conta, 0,1,3);
                             p->addWidget(b,conta, 4);
                             ++conta;
                            }
   QPushButton* b= new QPushButton("Cerca Un Eserciziario", gruppi);
    b->setStyleSheet("QPushButton{"
                                 "background-color: green;"
                                 "border-radius: 5px 5px 5px 5px;"
                                 "border: 2px solid;"
                                 "color: white;"
                                 "margin:0; }"
                                 "QPushButton:pressed {"
                                 "background-color:#003300;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));

    p->addWidget(b,conta, 0);

    compiti->setLayout(p);

}

void HomePageStud::InsertInProfile() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("IL TUO PROFILO", profile);
    title->setStyleSheet("QLabel{background-color: #00004d; color: #29abe2;}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    QLabel* g=new QLabel(profile);
    g->setFixedSize(100,100);
    string temp=ctrl->fotoprofilo();
    if(temp!="nessun info")
        g->setPixmap(QPixmap(QString::fromStdString(temp)).scaled(g->width(),g->height()));
   else
    g->setPixmap(QPixmap(":/immagini/Database/immagini/FotoProfili/emptyFoto.jpg").scaled(g->width(),g->height()));
    p->addWidget(g,1, 0,1,2);

    vector<string> v1= ctrl->CampiDatiProfile();
    vector<string> v2= ctrl->DaiValoreCampiDatiProfile();

     int conta =2;
                for(vector<string>::const_iterator it=v1.begin(); it != v1.end(); ++it){
                             g=new QLabel(QString::fromStdString(*it)+":", profile);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: #00004d;}");

                             p->addWidget(g,conta, 0);
                             ++conta;
                            }
                conta=2;
                for(vector<string>::const_iterator it2=v2.begin(); it2 != v2.end(); ++it2){
                    g=new QLabel(QString::fromStdString(*it2), profile);
                    g->setStyleSheet("QLabel{background-color: white; padding-left: 1em;}");

                    p->addWidget(g,conta, 1,1,3);
                    ++conta;

                }
    profile->setLayout(p);


}

void HomePageStud::InsertInNews() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("ULTIME NOTIZIE", wallnews);
    title->setStyleSheet("QLabel{color: #29abe2;background-color: white; border-bottom: 2px solid #29abe2}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(wallnews);
    p->addWidget(title,0, 0, 1,5);

     int conta =1;
                while(conta<=20){
                             QLabel* g=new QLabel("[data]", wallnews);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: white;}");
                             p->addWidget(g,conta, 0);
                             g=new QLabel("Utente"+QString::number(conta), wallnews);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: white;}");
                             p->addWidget(g,conta, 1);
                             g=new QLabel(" ha fatto blalala su", wallnews);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: white;}");
                             p->addWidget(g,conta, 2);
                             g=new QLabel("Compiti/Gruppi", wallnews);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: white;}");
                             p->addWidget(g,conta, 3);
                             QPushButton* b= new QPushButton("Vedi", wallnews);
                             b->setStyleSheet("QPushButton{"
                                              "background-color: #29abe2;"
                                              "border: 2px solid;"
                                              "border-radius: 5px 5px 5px 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                              "background-color:#003300;}");
                             b->setFixedSize(80, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));


                             p->addWidget(b,conta, 4);
                             ++conta;
                            }
    p->setSpacing(0);
    wallnews->setLayout(p);

}
