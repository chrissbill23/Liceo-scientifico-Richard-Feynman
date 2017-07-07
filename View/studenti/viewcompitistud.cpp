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
    setWindowTitle("Compiti assegnati");
}

QWidget *ViewCompitiStud::listaCompiti(int indice) const
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);

    vector<string> l = giveLista();
    QFont f("Times", 11);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Data", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,0, 1,1,Qt::AlignLeft|Qt::AlignTop);

    lab = new QLabel("Titolo", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,1, 1,1,Qt::AlignLeft|Qt::AlignTop);
    lay->setRowStretch(1,0);
    if(l.size() > 0){

        int inizio = l.size()-1*indice -1;
        int it = inizio;

        int row = 1;
        int conta = maxPerPage;
        f = QFont("Times", 10);
        for(; it >= 0  && conta > 0; --it){
            const QString& lit = QString::fromStdString(l[it]);
            int myanswer = ctrl->MyAnswrCompito((lit));

            lab = new QLabel(ctrl->getCompitoData(lit),temp);
            lab->setFont(f);
            lab->setFixedWidth(150);
            lay->addWidget(lab, row,0, 1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->getCompitoTitolo(lit), temp);
            lab->setFont(f);
            lab->setFixedWidth(200);
            lab->setStyleSheet("margin: 0 1em 0 0;");
            lay->addWidget(lab, row,1, 1,1,Qt::AlignTop);

            buttonCompito* b = new buttonCompito("Dettagli", lit,const_cast<ViewCompitiStud*>(this));
            b->setFixedSize(125,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(Dettagli()));
            lay->addWidget(b,row,2,1,1,Qt::AlignTop);

            b = new buttonCompito("Apri", lit,const_cast<ViewCompitiStud*>(this));
            b->setFixedSize(125,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(ShowCompito()));
            lay->addWidget(b,row,3,1,1,Qt::AlignTop);

            b = new buttonCompito("Commento prof", lit,
                                   const_cast<ViewCompitiStud*>(this), true,
                                  myanswer);
            b->setFixedSize(150,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewcommentRisp()));
            lay->addWidget(b,row,4, 1,1,Qt::AlignTop);

            if(ctrl->hasAnsweredCompito(lit)){
                b = new buttonCompito("Le tue risposte", lit,
                                       const_cast<ViewCompitiStud*>(this), true,
                                      myanswer, ctrl->getPathRispCompito(lit,myanswer));
                b->setFixedSize(150,40);
                b->setCursor(QCursor(Qt::PointingHandCursor));
                connect(b,SIGNAL(clicked(bool)),b,SLOT(viewElaborato()));
                lay->addWidget(b,row,5, 1,1,Qt::AlignTop);
            }

            --conta;
            ++row;

        }

        QGroupBox* footer = new QGroupBox(temp);
        footer->setStyleSheet("QGroupBox{border: 0;}");
        QGridLayout* footerLay = new QGridLayout(footer);
        footer->setLayout(footerLay);

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(QFont("Times",8));
        footerLay->addWidget(lab,0,1,1,1,Qt::AlignHCenter);
        footerLay->setColumnStretch(0,1);
        footerLay->setColumnStretch(2,1);

        QIcon i1;
        if(currPage > 1){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(temp);
            b->setIcon(i1);
            b->setFixedSize(100,40);
            b->setIconSize(QSize(100,40));
            b->setCursor(QCursor(Qt::PointingHandCursor));
            footerLay->addWidget(b,0,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(currPage < TotPage()){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(temp);
            b2->setIcon(i1);
            b2->setFixedSize(100,40);
            b2->setIconSize(QSize(100,40));
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            footerLay->addWidget(b2,0,2,1,1,Qt::AlignRight);
        }
        lay->addWidget(footer,row+2,0,1,6);
    }
    else{
        lay->addWidget(new QLabel("Relax, non ci sono ancora compiti :) ", temp),1,0,1,5);
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


void ViewCompitiStud::BodyAndFooter()
{
    QGridLayout* lay = giveLayout();
    if(!lay){
        lay = new QGridLayout(this);
    }
    QLabel* lab = new QLabel("Ordina per: ");
    lab->setFont(QFont("Times",12));
    lay->addWidget(lab,1,0,1,1, Qt::AlignRight);
    QComboBox* m = Materie();
    lay->addWidget(m,1,1, 1,1, Qt::AlignCenter);
    connect(m,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));


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
