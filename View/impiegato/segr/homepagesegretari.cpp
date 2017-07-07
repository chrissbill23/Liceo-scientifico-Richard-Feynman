#include "homepagesegretari.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QCloseEvent>

HomePageSegr::HomePageSegr(ControllerSegretario *ptr):FinestreSegretari(ptr),
    GestioneStudenti(0),
    profile(0), searchBox(0)

{
    Header();
    BodyAndFooter();
    setWindowTitle("Home");

}

void HomePageSegr::reloadWindow()
{

}

void HomePageSegr::BodyAndFooter()
{
    QFont f("Times", 11);

    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }
    GestioneStudenti = new QScrollArea(this);
    profile = new QGroupBox(this);

    GestioneStudenti->setStyleSheet("border-radius: 15px 15px 15px 15px; color: white;");
    GestioneStudenti->setFont(f);
    GestioneStudenti->setWidget(InsertInGestioneStudenti());
    GestioneStudenti->setWidgetResizable(true);
    GestioneStudenti->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    GestioneStudenti->setMaximumWidth(450);


    InsertInProfile();
    profile->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #e8e3e3;");
    profile->setMaximumSize(450,260);

    p->addWidget(GestioneStudenti,2,1,1,2, Qt::AlignTop);
    p->addWidget(profile, 1,0,1,1,Qt::AlignTop);
    p->setRowStretch(2,1);
}

void HomePageSegr::cercaStudente()
{
    CercaStud(searchBox->text());
}


QGroupBox *HomePageSegr::InsertInGestioneStudenti()
{
    QFont f("Times", 13);
    QGroupBox* temp = new QGroupBox(GestioneStudenti);

    QLabel* title = new QLabel("GESTIONE STUDENTI", temp);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid white;"
                         "border-radius: 0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    QVBoxLayout*p2 = new QVBoxLayout(temp);

    p2->addWidget(title,0, Qt::AlignTop);

    f = QFont("Times", 11);
    searchBox = new QLineEdit(temp);
    searchBox->setPlaceholderText("nome/cognome/nome utente");
    searchBox-> setStyleSheet("width: 15em; "
                              "height: 2em; "
                              "background-color: white; "
                              "border-radius: 0;"
                              "color: black;"
                              "padding-left: 0.5em;");
    searchBox->setFixedHeight(40);
    searchBox->setFont(f);
    QPushButton* b = new QPushButton("Cerca", temp);
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cercaStudente()));

    p2->addWidget(searchBox,0, Qt::AlignTop);
    p2->addWidget(b,0, Qt::AlignTop);

    b = new QPushButton("Nuovo studente", temp);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked()), this, SLOT(aggiungiStud()));

    p2->addWidget(b,0, Qt::AlignTop);

    b = new QPushButton("Modifica", temp);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked()), this, SLOT(ModificaStudenti()));
    p2->addWidget(b,1,Qt::AlignTop);


    temp->setLayout(p2);
    return temp;

}

void HomePageSegr::InsertInProfile() const
{
    QFont f("Times", 12);
    QLabel* title = new QLabel("PROFILO", profile);
    title->setStyleSheet("QLabel{"
                         "margin-bottom: 0.4em; }");

    title->setFont(f);

    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    QLabel* g = new QLabel(profile);
    g->setFixedSize(130,200);
    g->setPixmap(QPixmap(getController()->fotoprofilo()).scaled(g->width(),g->height()));
    p->addWidget(g,1, 0,6,1, Qt::AlignTop);

    QPushButton* b = new QPushButton("Cambia foto", profile);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
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
                     "border-radius: 5px; "
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
                for(list<string>::const_iterator it = v1.begin(); it != v1.end(); ++it){
                             g = new QLabel(QString::fromStdString(*it)+":", profile);
                             g->setStyleSheet("QLabel{color: #29abe2;}");
                             g->setFont(f);

                             p->addWidget(g,conta, 1,1,1, Qt::AlignTop);
                             ++conta;
                            }
                conta = 2;
                for(list<string>::const_iterator it2=v2.begin(); it2 != v2.end(); ++it2){
                    g = new QLabel(QString::fromStdString(*it2), profile);
                    g->setStyleSheet("QLabel{border-radius: 3px;"
                                     " background-color: white; "
                                     "padding: 0.4em 0 0.4em 0.4em;}");

                    p->addWidget(g,conta, 2,1,1, Qt::AlignTop);
                    ++conta;

                }

    profile->setLayout(p);
}





