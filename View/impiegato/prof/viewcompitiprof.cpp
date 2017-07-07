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
    setWindowTitle("Compiti");
}

QWidget *ViewCompitiProf::listaCompiti(int indice) const
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);
    temp->setLayout(lay);

    vector<string> l = giveLista();
    QFont f("Times", 11);
    f.setBold(true);
    f.setUnderline(true);
    QLabel* lab = new QLabel("Titolo", temp);
    lab->setFont(f);
    lay->addWidget(lab,0,0, 1,1,Qt::AlignLeft|Qt::AlignTop);

    QPushButton*b = new QPushButton("Nuovo compito");
    b->setFixedSize(150,30);
    b->setFont(QFont("Times",9));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(createCompito()));
    lay->addWidget(b,0,5,1,1, Qt::AlignRight|Qt::AlignTop);

    if(l.size() > 0){

        int inizio = l.size()-1*indice -1;
        int row = 1;
        int it = inizio;
        int conta = maxPerPage;
        f =  QFont("Times", 10);
        for(; it >= 0 && conta > 0; --it){
            const QString& code = QString::fromStdString(l[it]);
            const QString& l2Q = ctrl->getCompitoTitolo(code);

            lab = new QLabel(l2Q, temp);
            lab->setFixedWidth(200);
            lab->setStyleSheet("margin: 0 1em 0 0;");
            lab->setFont(f);
            lay->addWidget(lab, row,0, 1,1,Qt::AlignTop);

            buttonCompito* b = new buttonCompito("Dettagli", code,const_cast<ViewCompitiProf*>(this));
            b->setFixedSize(125,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(Dettagli()));
            lay->addWidget(b,row,1,1,1,Qt::AlignTop);

            b = new buttonCompito("Apri", code,const_cast<ViewCompitiProf*>(this));
            b->setFixedSize(150,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(ShowCompito()));
            lay->addWidget(b,row,2,1,1,Qt::AlignTop);

            b = new buttonCompito("Elaborati studenti", code,
                                  const_cast<ViewCompitiProf*>(this));
            b->setFixedSize(150,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewElaborati()));
            lay->addWidget(b,row,3, 1,1,Qt::AlignTop);

            b = new buttonCompito("Aggiungi classe", code,const_cast<ViewCompitiProf*>(this));
            b->setFixedSize(150,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            lay->addWidget(b,row,4, 1,1,Qt::AlignTop);
            connect(b,SIGNAL(clicked(bool)),b,SLOT(aggiungiClasse()));

            b = new buttonCompito("Elimina", code,const_cast<ViewCompitiProf*>(this));
            b->setStyleSheet("QPushButton{ color: white;"
                                  "background-color: #990000;"
                                  " border-radius: 5px;}"
                                  "QPushButton:pressed {"
                                  " background-color:#660000;}");
            b->setFixedSize(150,40);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimCompito()));
            lay->addWidget(b,row,5, 1,1,Qt::AlignTop);

            --conta;
            ++row;

        }

        QGroupBox* footer = new QGroupBox(temp);
        footer->setStyleSheet("QGroupBox{border: 0;}");
        QGridLayout* footerLay = new QGridLayout(footer);
        footer->setLayout(footerLay);

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(QFont("Times",10));
        footerLay->addWidget(lab,0,1,1,1,Qt::AlignHCenter);
        footerLay->setColumnStretch(0,1);
        footerLay->setColumnStretch(2,1);
        QIcon i1;
        if(currPage > 1){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(temp);
            b->setIcon(i1);
            b->setFixedSize(100,40);
            b->setIconSize(QSize(100,30));
            b->setCursor(QCursor(Qt::PointingHandCursor));
            footerLay->addWidget(b,0,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(currPage < TotPage()){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(temp);
            b2->setIcon(i1);
            b2->setFixedSize(100,40);
            b2->setIconSize(QSize(100,30));
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            footerLay->addWidget(b2,0,2,1,1,Qt::AlignRight);
        }
        lay->addWidget(footer,row+2,0,1,6);

    }
    else{
        lay->addWidget(new QLabel("Nessun compito trovato", temp),1,0,1,1);
        lay->setRowStretch(2,1);
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
        temp.setWindowTitle("Elaborati studenti");
        temp.exec();
    }
    else{
        QMessageBox::information(&temp,"","Al momento non ci sono elaborati da visualizzare");
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
    classi->setFixedHeight(30);
    classi->setFont(QFont("Times",9));
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

    temp.setFixedSize(400,160);
    temp.setWindowTitle("Assegna compito a classe");

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

    QComboBox* m = Materie();
    m->setCursor(QCursor(Qt::PointingHandCursor));
    QComboBox* c = Classi();
    c->setCursor(QCursor(Qt::PointingHandCursor));
    lay->addWidget(m,1,1, 1,1, Qt::AlignCenter);
    lay->addWidget(c,1,2,1,1, Qt::AlignLeft);

    connect(m,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));
    connect(c,SIGNAL(currentIndexChanged(int)),this,SLOT(FiltraRisultati()));

    sc->setWidget(listaCompiti(0));
    sc->setWidgetResizable(true);

    lay->addWidget(sc,3,0,1,3);
}
