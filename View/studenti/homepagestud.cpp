#include "homepagestud.h"
#include "homegruppostud.h"
#include "../buttongroup.h"
#include "../searchgroup.h"
#include "../popupdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>

HomePageStud::HomePageStud(ControllerStud*contrl):FinestreStudenti(contrl),gruppi(0),
                                            compiti(0),
                                            profile(0)
{
    Header();
    BodyAndFooter();
    setWindowTitle("Home");
}

void HomePageStud::reloadWindow()
{
    clearNoGranChildren();
    if(profile){
        delete profile;
        profile = 0;
    }
    if(compiti){
        delete compiti;
        compiti = 0;
    }
    if(gruppi){
        delete gruppi;
        gruppi = 0;
    }
    BodyAndFooter();
}

void HomePageStud::BodyAndFooter()
{
    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }
    gruppi = new QGroupBox( this);
    compiti = new QGroupBox(this);
    profile = new QGroupBox(this);
    gruppi->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #476b6b;}");
    QVBoxLayout* l = new QVBoxLayout;
    QVBoxLayout* l2 =new QVBoxLayout;
    InsertInGruppi();
    gruppi->setFixedHeight(350);
    compiti->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #4d2600; }");
    InsertInCompiti();
    compiti->setFixedHeight(400);
    profile->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #00004d;}");
    profile->setFixedHeight(300);
    InsertInProfile();
    l->addWidget(gruppi);
    l->addWidget(compiti);
    p->addLayout(l2, 1,0,Qt::AlignTop);
    p->addLayout(l, 1, 1,Qt::AlignTop);
    p->addWidget(profile, 1, 3,1,2,Qt::AlignTop);

}

void HomePageStud::Cerca()
{
    getController()->ShowNewWindow(new SearchGroup(getController()));
}

void HomePageStud::TuttiIGruppi()
{
    list<string> v = getController()->daiNomiGrupi();
    popUpDialog win(2,v.size(),gruppi);
            for(list<string>::const_iterator it = v.begin(); it != v.end(); ++it)
                    {
                             QLabel* g = new QLabel(QString::fromStdString((*it)), &win);
                             QFont f = QFont("Times", 9);
                             g->setStyleSheet("QLabel{"
                                                      "color: white;"
                                                      "background-color: #476b6b;"
                                                      "}");
                             g->setFont(f);
                             buttonGroup* b = new buttonGroup("Clicca Per Entrare",QString::fromStdString((*it)));
                             b->setStyleSheet("QPushButton{"
                                              "background-color: green;"
                                              "border: 2px solid;"
                                              "border-radius: 5px 5px 5px 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                              "background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));
                             connect(b, SIGNAL(clicked(bool)), this, SLOT(HomePageGroup()));
                             win.push_back_Widget(g);
                             win.push_back_Widget(b);
                            }
            win.setFixedSize(600,600);
            win.setStyleSheet("QWidget{background-color: #476b6b;}");
            win.setWindowTitle("Tutti i tuoi gruppi");
            win.exec();
}

void HomePageStud::IscriviMiAGroup(const QString &group)
{
    getController()->IscrivimiAGroup(group);

}

void HomePageStud::RemoveMeFromGroup(const QString &group)
{
    getController()->ToglimiDaGroup(group);

}
void HomePageStud::InsertInGruppi()
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

    list<string> v = getController()->daiNomiGrupi();
    int size = v.size();

    if(size > 0){
     int conta = 1;
            for(list<string>::const_iterator it=v.begin(); it != v.end() && conta<= 8; ++it)
                    {
                             QLabel* g=new QLabel(QString::fromStdString((*it)), gruppi);
                             f = QFont("Times", 9);
                             g->setStyleSheet("QLabel{"
                                                      "color: white;"
                                                      "background-color: #476b6b;"
                                                      "}");
                             g->setFont(f);
                             buttonGroup* b = new buttonGroup("Clicca Per Entrare",QString::fromStdString((*it)));
                             b->setStyleSheet("QPushButton{"
                                              "background-color: green;"
                                              "border: 2px solid;"
                                              "border-radius: 5px 5px 5px 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                              "background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));
                             connect(b, SIGNAL(clicked(bool)), this, SLOT(HomePageGroup()));
                             p->addWidget(g,conta, 0,1,3);
                             p->addWidget(b,conta, 4);
                             ++conta;
                            }
QPushButton* b;
    if(size> 8){
    b = new QPushButton("Vedi Altri Tuoi Gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: green;"
                     "border-radius: 5px 5px 5px 5px;"
                     "border: 2px solid;"
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#003300;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(TuttiIGruppi()));
    p->addWidget(b,conta, 0);
    b = new QPushButton("Visita Altri Gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     "border-radius: 5px 5px 5px 5px;"
                     "border: 2px solid;"
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#660000;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(Cerca()));
    p->addWidget(b,conta, 1);
    }
    else{
        b = new QPushButton("Visita Altri Gruppi", gruppi);
        b->setStyleSheet("QPushButton{"
                         "background-color: #990000;"
                         "border-radius: 5px 5px 5px 5px;"
                         "border: 2px solid;"
                         "color: white;}"
                         "QPushButton:pressed {"
                         "background-color:#660000;}");
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));

        connect(b,SIGNAL(clicked(bool)),this,SLOT(Cerca()));
        p->addWidget(b,conta, 0, 1, 3);
    }


    }
    else{
        QLabel* g = new QLabel("Non Sei Ancora Iscritto A Nessun Gruppo", gruppi);
        f = QFont("Times", 9);
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
        connect(b,SIGNAL(clicked(bool)),this,SLOT(Cerca()));
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

    list<string> v = getController()->MaterieInsegnate();
     int conta =1;
                for(list<string>::const_iterator it=v.begin(); it != v.end(); ++it){
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
                             connect(b,SIGNAL(clicked(bool)),this,SLOT(vediCompiti()));

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
    connect(b,SIGNAL(clicked(bool)),this, SLOT(HomePageBiblio()));

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

    ControllerStud* ctrl = getController();
    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    QLabel* g = new QLabel(profile);
    g->setFixedSize(100,100);
    g->setPixmap(QPixmap(ctrl->fotoprofilo()).scaled(g->width(),g->height()));
    p->addWidget(g,1, 0,1,2);

    list<string> v1 = ctrl->CampiDatiProfile();
    list<string> v2 = ctrl->DaiValoreCampiDatiProfile();

     int conta = 2;
                for(list<string>::const_iterator it=v1.begin(); it != v1.end(); ++it){
                             g=new QLabel(QString::fromStdString(*it)+":", profile);
                             g->setStyleSheet("QLabel{color: #29abe2; background-color: #00004d;}");

                             p->addWidget(g,conta, 0);
                             ++conta;
                            }
                conta = 2;
                for(list<string>::const_iterator it2 = v2.begin(); it2 != v2.end(); ++it2){
                    g = new QLabel(QString::fromStdString(*it2), profile);
                    g->setStyleSheet("QLabel{border-radius: 15px 15px 15px 15px; background-color: white; padding-left: 1em;}");

                    p->addWidget(g,conta, 1,1,3);
                    ++conta;

                }
    QPushButton* b = new QPushButton("Cambia foto profilo", profile);
    b->setStyleSheet("QPushButton{border-radius: 15px;}");
    b->setFixedHeight(30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiafotoProfilo()));
    p->addWidget(b,conta+1,0,1,4);
    b = new QPushButton("Cambia password", profile);
    b->setStyleSheet("QPushButton{border-radius: 15px;}");
    b->setFixedHeight(30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiaPassword()));
    p->addWidget(b,conta+2,0,1,4);
    p->setSpacing(4);
    profile->setLayout(p);


}

void HomePageStud::clearNoGranChildren()
{
    foreach(buttonGroup* child, gruppi->findChildren<buttonGroup*>()) {
        delete child;
    }
}

