#include "notifichemailbox.h"
#include "finestreimpiegato.h"
#include "../../Controller/controllerimpiegato.h"
#include "buttonmail.h"
#include <QLabel>
#include <QGridLayout>
#include <QScrollArea>
void NotificheMailBox::Body()
{
    sottoBox = new QGroupBox(this);
    QGridLayout* temp2 = new QGridLayout(sottoBox);

    QLabel* title = new QLabel("MESSAGGI", sottoBox);
    title->setStyleSheet("QLabel{"
                         " padding-bottom: 0.4em; "
                         "border-radius:0;}");

    title->setFont(QFont("Times", 15));
    title->setFixedHeight(50);
    temp2->addWidget(title,0,0);

    QFont f("Times", 9);
    f.setUnderline(true);

    QPushButton* b = new QPushButton("Ricarica", sottoBox);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFont(QFont("Times", 9));
    b->setStyleSheet("QPushButton:hover{"
                            "color: #29abe2;}"
                            "QPushButton:pressed {"
                            "color:#660000;}");
    connect(b, SIGNAL(clicked(bool)), this, SLOT(reload()));
    temp2->addWidget(b,0,3);



    QLabel* l = new QLabel("Ricevuti recentemente", sottoBox);
    temp2->addWidget(l,2,0,1,4);
    l = new QLabel("DA", sottoBox);
    temp2->addWidget(l,3,0);
    l = new QLabel("OGGETTO", sottoBox);
    temp2->addWidget(l,3,1);
    l = new QLabel("DATA", sottoBox);
    temp2->addWidget(l,3,2);


    QScrollArea* s = new QScrollArea(sottoBox);


    int tot = ctrl->totNuoviMess();
    if(tot == 0)
        s->setWidget(new QLabel("Nessun nuovo messaggio", sottoBox));
    else{
        QGroupBox* elenco = new QGroupBox(s);
        QGridLayout* temp = new QGridLayout(elenco);
        int conta = 0;
        for(int i = tot-1; i >= 0; --i){
            temp->addWidget(new QLabel(ctrl->LeggiMailSender(i,true), sottoBox),conta,0,1,4);
            temp->addWidget(new QLabel(ctrl->LeggiMailOgge(i,true,true), sottoBox),conta,4,1,3);
            temp->addWidget(new QLabel(ctrl->LeggidataMail(i,true,true), sottoBox),conta,8,1,3);
            buttonMail* b = new buttonMail("Vedi",i,true,true,fi);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            b->setFixedSize(80,30);
            b->setStyleSheet("QPushButton{"
                                    "margin-left: 25px;"
                                    "background-color: #29abe2;}"
                                    "QPushButton:pressed {"
                                    "color:#660000;}");
            connect(b,SIGNAL(clicked(bool)),b, SLOT(receiveClickSig()));
            temp->addWidget(b,conta,12);
            ++conta;
        }
        elenco->setLayout(temp);
        elenco->setStyleSheet("margin-left: 4px;");
        s->setWidget(elenco);
        s->setWidgetResizable(true);
    }

    temp2->addWidget(s,4,0,1,4);


    b = new QPushButton("Invia Nuovo Messaggio", sottoBox);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFont(f);
    b->setStyleSheet("QPushButton:hover{"
                            "color: #29abe2;}"
                            "QPushButton:pressed {"
                            "color:#660000;}");
    connect(b, SIGNAL(clicked(bool)), fi, SLOT(InviaNuovoMess()));
    temp2->addWidget(b,5,0);

    b = new QPushButton("Tutti i messaggi",sottoBox);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFont(f);
    b->setStyleSheet("QPushButton:hover{"
                            "color: #29abe2;}"
                            "QPushButton:pressed {"
                            "color:#660000;}");
    connect(b, SIGNAL(clicked(bool)), fi, SLOT(SeeReceivedMails()));
    temp2->addWidget(b,5,1);
    sottoBox->setLayout(temp2);

    lay->addWidget(sottoBox);
}

NotificheMailBox::NotificheMailBox(ControllerImpiegato *c, QWidget *parent): QGroupBox(parent), ctrl(c),
    fi(dynamic_cast<FinestreImpiegato*>(parent)),sottoBox(0), lay(new QVBoxLayout(this))
{
    Body();
}

void NotificheMailBox::reload()
{
    if(sottoBox){
        delete sottoBox;
        sottoBox = 0;
    }
    Body();
}
