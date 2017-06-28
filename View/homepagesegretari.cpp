#include "homepagesegretari.h"
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>
#include<QTime>
#include <QTimer>
#include <QLineEdit>
#include <QApplication>


void HomePageSegr::InsertInGestioneStudenti() const
{
    QFont f("Times", 11);
    QGridLayout* p = new QGridLayout(GestioneStudenti);

    QLineEdit* searchBox = new QLineEdit(GestioneStudenti);
    searchBox->setPlaceholderText("nome/cognome/nome utente");
    searchBox-> setStyleSheet("width: 15em; "
                              "height: 2em; background-color: white; "
                              "color: black;"
                              "padding-left: 0.5em;");
    searchBox->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    searchBox->setFont(f);
    QPushButton* b= new QPushButton("Cerca studente", GestioneStudenti);
    b->setFixedSize(150, 30);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");

    p->addWidget(searchBox,0, 0);
    p->addWidget(b,0, 1);

    b= new QPushButton("Inserici un nuovo studente", GestioneStudenti);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,1, 0, 1, 1, Qt::AlignLeft);

    b= new QPushButton("Rimuovi un ex studente", GestioneStudenti);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,2, 0, 1, 1, Qt::AlignLeft);

    b= new QPushButton("Gestisci Libretti", GestioneStudenti);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,3, 0, 1, 1, Qt::AlignLeft);

    b= new QPushButton("Tasse Pagate", GestioneStudenti);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(b,4, 0, 1, 1, Qt::AlignLeft);
    p->setContentsMargins(11,15,11,11);
    p->setSpacing(0);
    p->setRowStretch(2,0);
    GestioneStudenti->setLayout(p);

}

void HomePageSegr::InsertInGestioneRegistri() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("GESTIONE REGISTRI DI CLASSE", GestioneRegistri);
    title->setStyleSheet("QLabel{"
                         "color: yellow;"
                         "background-color: #4d2600;}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(GestioneRegistri);
    p->addWidget(title,0, 0,1,2);
}

void HomePageSegr::InsertInProfile() const
{
    QFont f("Times", 11);

    QLabel* title= new QLabel("IL TUO PROFILO", profile);
    title->setStyleSheet("QLabel{background-color: #00004d; color: #29abe2;}");

    title->setFont(f);
    title->setFixedHeight(20);

    QGridLayout* p = new QGridLayout(profile);
    p->addWidget(title,0, 0,1,2);
    profile->setLayout(p);
}

HomePageSegr::HomePageSegr(QWidget *parent):QWidget(parent),
    FoglioPresenza(new QLabel(QDate::currentDate().toString("dd/MMMM/yyyy")+"\n"+QTime::currentTime().toString("hh:mm:ss"), this)),
    GestioneStudenti(new QGroupBox("GESTIONE STUDENTI",this)),
    GestioneRegistri(new QGroupBox(this)),
    profile(new QGroupBox(this)),
    t(new QTimer(this))
{
    QFont f("Times", 11);
    QGridLayout* p= new QGridLayout(this);
    t->setInterval(1000);
    t->start();
       connect(t, SIGNAL(timeout()), this, SLOT(updateLabel()));
    FoglioPresenza->setFont(f);
    FoglioPresenza->setStyleSheet("QLabel{"
                                  "background-color: white;"
                                  "border-radius: 15px 15px 15px 15px; "
                                  "color:#29abe2 ;"
                                  "padding: 3em;}");
    FoglioPresenza->setFixedSize(500,200);
    FoglioPresenza->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    InsertInGestioneStudenti();
    GestioneStudenti->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #476b6b;}"
                                    "QGroupBox:title{"
                                    "color: white;"
                                     "height: 2em;"
                                    "margin: 2em 2em 0 2em;"
                                    "border-bottom: 2px solid white;}");
    GestioneStudenti->setFont(f);
    InsertInGestioneRegistri();
    GestioneRegistri->setStyleSheet("QGroupBox{border-radius: 15px 15px 15px 15px; background-color: #4d2600; }");
    InsertInProfile();
    profile->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #00004d;");
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
    QPushButton* firma= new QPushButton("Firma Presenza", this);
    firma->setFixedSize(150, 40);
    firma->setStyleSheet("QPushButton{"
                         "background-color: green; "
                         "border-radius: 5px 5px 5px 5px; "
                         "color: white;"
                         "margin-right: 3em;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
    firma->setCursor(QCursor(Qt::PointingHandCursor));
    p->addWidget(FoglioPresenza,0,0,1,1, Qt::AlignTop);
    p->addWidget(firma,0,0,1,1,Qt::AlignRight);
    p->addWidget(biblio,0,2,1,1,Qt::AlignTop);
    p->addWidget(logout,0,3,1,1,Qt::AlignTop);
    p->addWidget(GestioneStudenti,1,0);
    p->addWidget(GestioneRegistri,1,1);
    p->addWidget(profile, 1,2,1,2);
    resize(1500,1000);
    setStyleSheet(" background-color: #29abe2");
    setLayout(p);
}

void HomePageSegr::updateLabel()
{
FoglioPresenza->setText(QDate::currentDate().toString("dd/MMMM/yyyy")+"\n"+QTime::currentTime().toString("hh:mm:ss"));
}
