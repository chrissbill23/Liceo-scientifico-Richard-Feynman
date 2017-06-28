#include "listamail.h"
#include "buttonmail.h"
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

void listaMail::loadMails()
{
    if(ricevuti){
      tot = ctrl -> TotMessRic();
    }
    else{
        tot = ctrl -> TotMessInv();
    }

}

void listaMail::setMaxPerPage(int Max)
{
    max = Max;
    totPage = tot / max;
    if( tot % max > 0 || tot == 0)
        ++totPage;
}

QGroupBox* listaMail::setPageRic(int indice)
{

    QGroupBox* box = new QGroupBox;

    QFont f("Times",14);
    f.setBold(true);
    f.setUnderline(true);
    QGridLayout* temp = new QGridLayout(box);
    box->setLayout(temp);
    QLabel* lab = new QLabel("Data", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,0,Qt::AlignTop);
    lab = new QLabel("Oggetto", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,1,Qt::AlignTop);
     lab = new QLabel("Emittente", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,2,Qt::AlignTop);
    temp->setHorizontalSpacing(0);
        if(tot == 0){
            temp->addWidget(new QLabel("Nessun messaggio da mostrare",box),1,0,1,3);
            }
        else{

            int row = 0;
            int readMail = ctrl->totNuoviMess()-1;
            for(int i = tot - 1 - indice; i>= 0 && row < max; --i){


                lab = new QLabel(ctrl->LeggidataMail(i,ricevuti),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0;");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,0,Qt::AlignTop);

                lab = new QLabel(ctrl->LeggiMailOgge(i,ricevuti),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0; ");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,1,Qt::AlignTop);

                lab = new QLabel(ctrl->LeggiMailSender(i,ricevuti),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0;");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,2,Qt::AlignTop);

                if(ctrl->isMailRead(i)){
                buttonMail* b = new buttonMail("Visualizza",i,ricevuti,false, this);
                connect(b,SIGNAL(clicked(bool)),b,SLOT(receiveClickSig()));
                b->setFixedSize(200,50);
                temp->addWidget(b, row+1, 3,Qt::AlignTop);
                }
                else{
                    buttonMail* b = new buttonMail("Visualizza",readMail,ricevuti,true, this);
                    connect(b,SIGNAL(clicked(bool)),b,SLOT(receiveClickSig()));
                    b->setFixedSize(200,50);
                    temp->addWidget(b, row+1, 3,Qt::AlignTop);
                    --readMail;
                }

                buttonMail*b = new buttonMail("Elimina",i,ricevuti,false, this);
                connect(b,SIGNAL(clicked(bool)),b,SLOT(elimMess()));
                b->setFixedSize(200,50);
                temp->addWidget(b, row+1, 4,Qt::AlignTop);
                ++row;
              }

            QLabel* lab = new QLabel("Pagina: "+QString::number(currPage)+"/"+QString::number(totPage));
            temp->addWidget(lab,row+1,2);
                QIcon i1;
                if(currPage < totPage){
                    i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
                    QPushButton* b = new QPushButton("Next page",box);
                    b->setIcon(i1);
                    connect(b,SIGNAL(clicked(bool)),this,SLOT(goToNextPage()));
                    temp->addWidget(b,row+1,3,1,2);
                }
                if(currPage > 1){
                    i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
                    QPushButton* b = new QPushButton("Previous page",box);
                    b->setIcon(i1);
                    connect(b,SIGNAL(clicked(bool)),this,SLOT(goToPrevPage()));
                    temp->addWidget(b,row+1,0);
                }
        }
        return box;
}
void listaMail::ElimMail(unsigned int i, bool ricevuta)
{
    if(ctrl->eliminaMail(i,ricevuta)){
       loadMails();
       currPage = 1;
       if(currPage * max >= tot && currPage > 1){
           currPage --;
       }
       totPage = tot / max;
       if( tot % max > 0  || tot == 0)
           ++totPage;
       if(ricevuti)
        box->setWidget(setPageRic((currPage - 1) * max));
       else
            box->setWidget(setPageInv((currPage - 1) * max));
      box->setWidgetResizable(true);
    }
}

void listaMail::loadWindow()
{
    Header();
    BodyAndFooter();
}

void listaMail::reloadWindow()
{
    loadMails();
    if(!ricevuti)
    box->setWidget(setPageInv((currPage - 1) * max));
    else box->setWidget(setPageRic((currPage - 1) * max));
   box->setWidgetResizable(true);
}

void listaMail::goToNextPage()
{
        ++currPage;
    if(ricevuti)
     box->setWidget(setPageRic((currPage - 1) * max));
    else
         box->setWidget(setPageInv((currPage - 1) * max));
        box->setWidgetResizable(true);
}

void listaMail::goToPrevPage()
{
    if(currPage > 1){
    currPage --;
    if(ricevuti)
     box->setWidget(setPageRic((currPage - 1) * max));
    else
         box->setWidget(setPageInv((currPage - 1) * max));
    box->setWidgetResizable(true);
    }
}

void listaMail::Header()
{
    setWindowTitle("Le tue mail");
}

void listaMail::BodyAndFooter()
{
    p = new QVBoxLayout(this);
    box = new QScrollArea(this);
    if(ricevuti)
    box->setWidget(setPageRic(0));
    else
        box->setWidget(setPageInv(0));
    box->setWidgetResizable(true);
    p->addWidget(box);
    setLayout(p);
}

QGroupBox *listaMail::setPageInv(int indice)
{
    QGroupBox* box = new QGroupBox;

    QFont f("Times",14);
    f.setBold(true);
    f.setUnderline(true);
    QGridLayout* temp = new QGridLayout(box);
    box->setLayout(temp);
    QLabel* lab = new QLabel("Data", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,0,Qt::AlignTop);
    lab = new QLabel("Oggetto", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,1,Qt::AlignTop);
     lab = new QLabel("Destinatario", box);
    lab->setFont(f);
    lab->setFixedWidth(200);
    temp->addWidget(lab,0,2,Qt::AlignTop);

    temp->setHorizontalSpacing(0);
        if(tot == 0){
            temp->addWidget(new QLabel("Nessun messaggio da mostrare",box),1,0,1,3);
            }
        else{

            int row = 0;
            for(int i = tot - 1 - indice; i>= 0 && row < max; --i){


                lab = new QLabel(ctrl->LeggidataMail(i,ricevuti),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0;");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,0,Qt::AlignTop);

                lab = new QLabel(ctrl->LeggiMailOgge(i,ricevuti),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0; ");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,1,Qt::AlignTop);

                lab = new QLabel(ctrl->LeggiMailDest(i),box);
                lab->setFont(f);
                lab->setStyleSheet("padding: 10px 0 10px 0;");
                lab->setFixedWidth(200);
                temp->addWidget(lab,row+1,2,Qt::AlignTop);

                buttonMail* b = new buttonMail("Visualizza",i,ricevuti,false, this);
                connect(b,SIGNAL(clicked(bool)),b,SLOT(receiveClickSig()));
                b->setFixedSize(200,50);
                temp->addWidget(b, row+1, 3,Qt::AlignTop);

                b = new buttonMail("Elimina",i,ricevuti,false, this);
                connect(b,SIGNAL(clicked(bool)),b,SLOT(elimMess()));
                b->setFixedSize(200,50);
                temp->addWidget(b, row+1, 4,Qt::AlignTop);
                ++row;
              }

            QLabel* lab = new QLabel("Pagina: "+QString::number(currPage)+"/"+QString::number(totPage));
            temp->addWidget(lab,row+1,2);
                QIcon i1;
                if(currPage < totPage){
                    i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
                    QPushButton* b = new QPushButton("Next page",box);
                    b->setIcon(i1);
                    connect(b,SIGNAL(clicked(bool)),this,SLOT(goToNextPage()));
                    temp->addWidget(b,row+1,3,1,2);
                }
                if(currPage > 1){
                    i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
                    QPushButton* b = new QPushButton("Previous page",box);
                    b->setIcon(i1);
                    connect(b,SIGNAL(clicked(bool)),this,SLOT(goToPrevPage()));
                    temp->addWidget(b,row+1,0);
                }
        }
        return box;
}

listaMail::listaMail(ControllerImpiegato *c, bool ric): FinestreImpiegato(c), ctrl(c),
    tot(0),  max(1), currPage(1), totPage(1), ricevuti(ric), box(0), p(0)
{

}

