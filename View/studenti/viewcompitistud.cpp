#include "viewcompitistud.h"
#include "../impiegato/buttoncompito.h"
#include "../../Controller/controllerstud.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QComboBox>

ViewCompitiStud::ViewCompitiStud(ControllerStud *c):ViewCompiti(c),sc(new QScrollArea(this)), ctrl(c)
{
    Header();
    BodyAndFooter();
}

QWidget *ViewCompitiStud::listaCompiti(int indice) const
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);

    vector<string> l = giveLista();
    QFont f("Times", 13);
    QLabel* lab = new QLabel("Codice Compito", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,0, 1,1,Qt::AlignLeft|Qt::AlignTop);

    lab = new QLabel("Data", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,1, 1,1,Qt::AlignLeft|Qt::AlignTop);

    lab = new QLabel("Titolo", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,2, 1,1,Qt::AlignLeft|Qt::AlignTop);
    lay->setRowStretch(1,0);
    if(l.size() > 0){
        vector<string> l2 = ctrl->giveCompitiTitle();
        vector<string> l3 = ctrl->giveCompitiDates();

        int inizio = l.size()-1*indice -1;
        int it = inizio;
        int it2 = inizio;
        int it3 = inizio;

        int row = 1;
        int conta = maxPerPage;
        for(; it >= 0 && it2 >= 0 && it3 >= 0 && conta > 0; --it){
            const QString& lit = QString::fromStdString(l[it]);
            int myanswer = ctrl->MyAnswrCompito((lit));
            lab = new QLabel(lit,temp);
            lab->setFont(f);
            lay->addWidget(lab, row,0, 1,1,Qt::AlignTop);

            lab = new QLabel(QString::fromStdString(l3[it3]),temp);
            lab->setFont(f);
            lay->addWidget(lab, row,1, 1,1,Qt::AlignTop);

            lab = new QLabel(QString::fromStdString(l2[it2]), temp);
            lab->setFont(f);
            lay->addWidget(lab, row,2, 1,1,Qt::AlignTop);

            buttonCompito* b = new buttonCompito("Visualizza compito", lit,
                                                 const_cast<ViewCompitiStud*>(this));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(ShowCompito()));
            lay->addWidget(b,row,3,1,1,Qt::AlignTop);

            b = new buttonCompito("Visualizza commento prof", lit,
                                   const_cast<ViewCompitiStud*>(this), true,
                                  myanswer);
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewcommentRisp()));
            lay->addWidget(b,row,4, 1,1,Qt::AlignTop);

            if(ctrl->hasAnsweredCompito(lit)){
                b = new buttonCompito("Visualizza le tue risposte", lit,
                                       const_cast<ViewCompitiStud*>(this), true,
                                      myanswer, ctrl->getPathRispCompito(lit,myanswer));
                connect(b,SIGNAL(clicked(bool)),b,SLOT(viewElaborato()));
                lay->addWidget(b,row,5, 1,1,Qt::AlignTop);
            }

            --it2;
            --it3;
            --conta;
            ++row;

        }

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(f);
        lay->addWidget(lab,row+2,3,1,1,Qt::AlignHCenter);
        QIcon i1;
        if(currPage > 1){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(temp);
            b->setIcon(i1);
            b->setFixedSize(200,40);
            b->setIconSize(QSize(200,40));
            b->setStyleSheet("QPushButton{"
                             "background-color: white;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            lay->addWidget(b,row+2,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(currPage < TotPage()){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(temp);
            b2->setIcon(i1);
            b2->setFixedSize(200,40);
            b2->setIconSize(QSize(200,40));
            b2->setStyleSheet("QPushButton{"
                              "background-color: white;"
                              "border: 2px solid;"
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                              "background-color:#003300;}");
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            lay->addWidget(b2,row+2,5,1,1,Qt::AlignRight);
        }

    }
    else{
        lay->addWidget(new QLabel("Relax, non ci sono ancora compiti :) ", temp),1,0,1,2);
    }
    return temp;
}

void ViewCompitiStud::reloadWindow()
{
    if(sc){
        QWidget* p = sc->widget();
        if(p)
            delete p;
        sc->setWidget(listaCompiti(0));
        sc->setWidgetResizable(true);
    }
}

bool ViewCompitiStud::sort()
{
    ViewCompiti::reloadWindow();
    return sortbyMateria();
}

ViewCompitiStud::~ViewCompitiStud()
{
    if(sc){
        QWidget* p = sc->widget();
        if(p)
            delete p;
    }
}

void ViewCompitiStud::BodyAndFooter()
{
    QGridLayout* lay = giveLayout();
    if(!lay){
        lay = new QGridLayout(this);
    }
    QLabel* lab = new QLabel("Ordina per: ");
    lab->setFont(QFont("Times",14));
    lay->addWidget(lab,1,0,1,1, Qt::AlignRight);
    QComboBox* m = Materie();
    lay->addWidget(m,1,1, 1,1, Qt::AlignCenter);
    connect(m,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));
    QPushButton* b = new QPushButton("filtra risultati", this);
    b->setFixedSize(200,50);
    b->setFont(QFont("Times",12));
    b->setStyleSheet("QPushButton{"
                     "background-color: green;"
                     "border: 2px solid;"
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(FiltraRisultati()));
    lay->addWidget(b,1,2,1,1, Qt::AlignRight);


    sc->setWidget(listaCompiti(0));
    sc->setWidgetResizable(true);

    lay->addWidget(sc,2,0,1,3);
}

void ViewCompitiStud::goNext()
{
    ViewCompiti::goNext();
    sc->setWidget(listaCompiti((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void ViewCompitiStud::goPrev()
{
    ViewCompiti::goPrev();
        sc->setWidget(listaCompiti((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
}
