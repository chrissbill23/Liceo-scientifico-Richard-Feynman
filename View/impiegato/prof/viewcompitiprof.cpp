#include "viewcompitiprof.h"
#include "../buttoncompito.h"
#include "../../../Controller/controllerprof.h"
#include "../../popupdialog.h"
#include "createcompito.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QComboBox>
#include <QMessageBox>


ViewCompitiProf::ViewCompitiProf(ControllerProf *c) : ViewCompiti(c), sc(new QScrollArea(this)),ctrl(c){
    Header();
    BodyAndFooter();
    setWindowTitle("Tutti i compiti/ esercizi");
}

QWidget *ViewCompitiProf::listaCompiti(int indice) const
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);
    temp->setLayout(lay);

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

    lab = new QLabel("Classi", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,3, 1,1,Qt::AlignLeft|Qt::AlignTop);
    lay->setRowStretch(1,0);
    if(l.size() > 0){
        vector<string> l2 = ctrl->giveCompitiTitle();
        vector<string> l3 = ctrl->giveCompitiDates();

        int inizio = l.size()-1*indice -1;
        int row = 1;
        int it = inizio;
        int it2 = inizio;
        int it3 = inizio;
        int conta = maxPerPage;
        for(; it >= 0 && it2 >= 0 && it3 >= 0 && conta > 0; --it){
            const QString& l1 = QString::fromStdString(l[it]);
            const QString& l2Q = QString::fromStdString(l2[it2]);
            const QString& l3Q = QString::fromStdString(l3[it3]);
            lab = new QLabel(l1,temp);
            lab->setFont(f);
            lay->addWidget(lab, row,0, 1,1,Qt::AlignTop);

            lab = new QLabel(l3Q,temp);
            lab->setFont(f);
            lay->addWidget(lab, row,1, 1,1,Qt::AlignTop);

            lab = new QLabel(l2Q, temp);
            lab->setFont(f);
            lay->addWidget(lab, row,2, 1,1,Qt::AlignTop);

            lab = new QLabel(temp);
            lab->setFont(f);
            lab->setScaledContents(true);
            list<string> temp = ctrl->classiCompito(l1);
            for(list<string>:: const_iterator it4 = temp.begin(); it4 != temp.end(); ++ it4){
                lab->setText(lab->text() + QString::fromStdString(*it4)+". ");
            }
            lay->addWidget(lab, row,3, 1,1,Qt::AlignTop);

            buttonCompito* b = new buttonCompito("Visualizza", l1,const_cast<ViewCompitiProf*>(this));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(ShowCompito()));
            lay->addWidget(b,row,4,1,1,Qt::AlignTop);

            b = new buttonCompito("Visualizza elaborati studenti", l1,
                                  const_cast<ViewCompitiProf*>(this));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewElaborati()));
            lay->addWidget(b,row,5, 1,1,Qt::AlignTop);

            b = new buttonCompito("Elimina compito", l1,const_cast<ViewCompitiProf*>(this));

            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimCompito()));
            lay->addWidget(b,row,6, 1,1,Qt::AlignTop);

            b = new buttonCompito("Aggiungi classe", l1,const_cast<ViewCompitiProf*>(this));

            connect(b,SIGNAL(clicked(bool)),b,SLOT(aggiungiClasse()));
            lay->addWidget(b,row,7, 1,1,Qt::AlignTop);

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
            lay->addWidget(b2,row+2,7,1,1,Qt::AlignRight);
        }

    }
    else{
        lay->addWidget(new QLabel("Non ha ancora assegnato compiti/esercizi ", temp),1,0,1,2);
    }

return temp;

}

void ViewCompitiProf::reloadWindow()
{
    if(sc){
        sc->setWidget(listaCompiti(0));
        sc->setWidgetResizable(true);
    }
}

void ViewCompitiProf::viewElaborati(const QString &codice) const
{
    int tot = ctrl->totRispCompito(codice);

    popUpDialog temp(3,20);
    if(tot > 0){
        for(int i = 0; i< tot;  ++i){
            QLabel* lab = new QLabel(ctrl->getCognomeRispCompito(codice,i),&temp);
            lab->setText(lab->text()+" "+ctrl->getNomeRispCompito(codice,i));
            temp.push_back_Widget(lab);
            buttonCompito* b = new buttonCompito("vedi",codice,const_cast<ViewCompitiProf*>(this),true,i,ctrl->getPathRispCompito(codice,i));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewElaborato()));
            temp.push_back_Widget(b);
            if(!ctrl->HasRispCompitoCom(codice,i)){
            b = new buttonCompito("commenta",codice,const_cast<ViewCompitiProf*>(this),true,i,
                                       ctrl->getPathRispCompito(codice,i));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(commentaRispCompito()));
            temp.push_back_Widget(b);
            }
            else{
                lab = new QLabel("Ha commentato questo elaborato");
                temp.push_back_Widget(lab);
            }
        }
        temp.setFixedSize(600,600);
        temp.exec();
    }
    else{
        QMessageBox::information(&temp,"","Al momento non ci sono elaborati da visualizzare");
    }

}

ViewCompitiProf::~ViewCompitiProf()
{
    if(sc){
        QWidget* p = sc->widget();
        if(p)
            delete p;
    }
}

void ViewCompitiProf::createCompito()
{
    CreateCompito n(dynamic_cast<ControllerProf*>(getController()));
    n.exec();
    reloadWindow();
}

void ViewCompitiProf::aggiungiClasse(const QString &codice)
{
    popUpDialog temp(1,3);

    QComboBox* classi = new QComboBox(&temp);

    classi->addItem("Seleziona la classe",-1);
    vector<string> l = ctrl->Classi();
    for(vector<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        classi->addItem(QString::fromStdString(*it),QString::fromStdString(*it));
    temp.push_back_Widget(classi);


    QPushButton* b = new QPushButton("Salva modifiche", & temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,400);

    while( temp.exec() == QDialog::Accepted){
        if(classi->itemData(classi->currentIndex()).toInt() == -1)
            QMessageBox::information(&temp,"Errore", "Deve selezionare una classe");
        else{
            const QString& ris = ctrl->aggiungiClasseACompito(codice,classi->itemData(classi->currentIndex()).toString());
            if(ris == ""){
                QMessageBox::information(&temp,"","Salvato con successo!");
                temp.setResult(0);
            }
            else
                QMessageBox::information(&temp,"Errore",ris);
        }
    }
    reloadWindow();
}

void ViewCompitiProf::goNext()
{
    ViewCompiti::goNext();
    sc->setWidget(listaCompiti((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void ViewCompitiProf::goPrev()
{
    ViewCompiti::goPrev();
        sc->setWidget(listaCompiti((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
}

void ViewCompitiProf::BodyAndFooter()
{
    QGridLayout* lay = giveLayout();
    if(!lay){
        lay = new QGridLayout(this);
    }
    QLabel* lab = new QLabel("Ordina per: ");
    lab->setFont(QFont("Times",14));
    lay->addWidget(lab,1,0,1,1, Qt::AlignRight);

    QComboBox* m = Materie();
    QComboBox* c = Classi();
    lay->addWidget(m,1,1, 1,1, Qt::AlignCenter);
    lay->addWidget(c,1,2,1,1, Qt::AlignLeft);

    connect(m,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));
    connect(c,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));
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

    b = new QPushButton("Aggiungi compito", this);
    b->setFixedSize(300,50);
    b->setFont(QFont("Times",12));
    b->setStyleSheet("QPushButton{"
                     "background-color: green;"
                     "border: 2px solid;"
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                     "background-color:#003300;}");

    connect(b,SIGNAL(clicked(bool)),this,SLOT(createCompito()));
    lay->addWidget(b,2,2,1,1, Qt::AlignRight);


    sc->setWidget(listaCompiti(0));
    sc->setWidgetResizable(true);

    lay->addWidget(sc,3,0,1,3);
}
