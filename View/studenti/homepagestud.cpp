#include "homepagestud.h"
#include "homegruppostud.h"
#include "../buttongroup.h"
#include "../searchgroup.h"
#include "../popupdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>

HomePageStud::HomePageStud(ControllerStud*contrl):FinestreStudenti(contrl),gruppi(0), compiti(0),
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
    compiti = new QPushButton("Fai i compiti",this);
    profile = new QGroupBox(this);
    gruppi->setStyleSheet("QGroupBox{border-radius: 15px; "
                          "background-color: #669999;}");
    QVBoxLayout* l = new QVBoxLayout;
    InsertInGruppi();
    gruppi->setFixedHeight(350);
    gruppi->setMaximumWidth(500);
    compiti->setStyleSheet("QPushButton{"
                            "background-color: #336699; "
                            "border-radius: 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                           " background-color:#003300;}");
    compiti->setFixedHeight(40);
    compiti->setMaximumWidth(500);
    compiti->setCursor(QCursor(Qt::PointingHandCursor));
    connect(compiti,SIGNAL(clicked(bool)),this,SLOT(vediCompiti()));
    profile->setStyleSheet("QGroupBox{border-radius: 15px; background-color: #D1CAB0;}");
    profile->setMaximumSize(500,600);
    InsertInProfile();
    l->addWidget(gruppi);
    l->addWidget(compiti);
    p->addLayout(l, 1, 0,Qt::AlignTop);
    p->addWidget(profile, 1, 1,1,2,Qt::AlignTop);
    p->setRowStretch(2,1);
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
                             g->setStyleSheet("QLabel{background-color: #669999; color: white; "
                                              "margin-bottom: 0.4em;}");

                             g->setFont(f);
                             buttonGroup* b = new buttonGroup("Entra",QString::fromStdString((*it)));
                             b->setStyleSheet("QPushButton{"
                                              "background-color: #336699; "
                                              "border-radius: 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                             " background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));
                             connect(b, SIGNAL(clicked(bool)), this, SLOT(HomePageGroup()));
                             win.push_back_Widget(g);
                             win.push_back_Widget(b);
                            }
            win.setFixedSize(600,600);
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
    title->setStyleSheet("QLabel{background-color: #669999; color: white;"
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
                             g->setStyleSheet("QLabel{background-color: #669999; color: white;"
                                                      "}");
                             g->setFont(f);
                             buttonGroup* b = new buttonGroup("Entra",QString::fromStdString((*it)));
                             b->setStyleSheet("QPushButton{"
                                              "background-color: #336699; "
                                              "border-radius: 5px; "
                                              "color: white;}"
                                              "QPushButton:pressed {"
                                             " background-color:#003300;}");
                             b->setFixedSize(150, 30);
                             b->setCursor(QCursor(Qt::PointingHandCursor));
                             connect(b, SIGNAL(clicked(bool)), this, SLOT(HomePageGroup()));
                             p->addWidget(g,conta, 0,1,3);
                             p->addWidget(b,conta, 4);
                             ++conta;
                            }
QPushButton* b;
    if(size> 8){
    b = new QPushButton("Tutti i tuoi gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(TuttiIGruppi()));
    p->addWidget(b,conta, 0);
    b = new QPushButton("Scopri altri Gruppi", gruppi);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(Cerca()));
    p->addWidget(b,conta, 1);
    }
    else{
        b = new QPushButton("Scopri altri Gruppi", gruppi);
        b->setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
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
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),this,SLOT(Cerca()));
        p->addWidget(b,2, 0, 1, 3);
    }

    gruppi->setLayout(p);
}



void HomePageStud::InsertInProfile() const
{
    QFont f("Times", 12);

    QLabel* title= new QLabel("PROFILO", profile);
    title->setStyleSheet("QLabel{background-color: #D1CAB0; "
                         "margin-bottom: 0.4em;}");

    title->setFont(f);

    ControllerStud* ctrl = getController();
    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    QLabel* g = new QLabel(profile);
    g->setFixedSize(150,200);
    g->setPixmap(QPixmap(ctrl->fotoprofilo()).scaled(g->width(),g->height()));
    p->addWidget(g,1, 0,5,1, Qt::AlignTop);

    list<string> v1 = ctrl->CampiDatiProfile();
    list<string> v2 = ctrl->DaiValoreCampiDatiProfile();

     int conta = 2;
                for(list<string>::const_iterator it=v1.begin(); it != v1.end(); ++it){
                             g = new QLabel(QString::fromStdString(*it)+":");
                             g->setStyleSheet("background-color: #D1CAB0;");

                             p->addWidget(g,conta, 1,1,1, Qt::AlignTop);
                             ++conta;
                            }
                conta = 2;
                for(list<string>::const_iterator it2 = v2.begin(); it2 != v2.end(); ++it2){
                    g = new QLabel(QString::fromStdString(*it2));
                    g->setStyleSheet("QLabel{border-radius: 5px;"
                                     " background-color: white; "
                                     "padding: 0.4em 0 0.4em 0.4em;}");

                    p->addWidget(g,conta, 2,1,1, Qt::AlignTop);
                    ++conta;

                }
    QPushButton* b = new QPushButton("Cambia foto", profile);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(125,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiafotoProfilo()));
    p->addWidget(b,1,1,1,1, Qt::AlignTop);
    b = new QPushButton("Cambia password", profile);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedSize(150,30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiaPassword()));
    p->addWidget(b,1,2,1,4);
    p->setSpacing(4);
    profile->setLayout(p);


}

void HomePageStud::clearNoGranChildren()
{
    foreach(buttonGroup* child, gruppi->findChildren<buttonGroup*>()) {
        delete child;
    }
}

