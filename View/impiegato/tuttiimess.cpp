#include "tuttiimess.h"
#include "listamail.h"
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>

int TuttiImess::maxMailPerPage = 10;

TuttiImess::TuttiImess(ControllerImpiegato *ptr):FinestreImpiegato(ptr), ctrl(ptr),
    prevWindow(new QPushButton("Torna indietro", this)),listric(0),
    listinv(0), tab(new QTabWidget(this))
{
 Header();
 BodyAndFooter();
}

void TuttiImess::reloadWindow()
{
    if(listric)
        listric->reloadWindow();
    if(listinv)
        listinv->reloadWindow();
}

void TuttiImess::Header()
{
   setWindowTitle("Tutti i messaggi");
}

void TuttiImess::BodyAndFooter()
{
 QVBoxLayout* temp = new QVBoxLayout;
 QHBoxLayout* temp2 = new QHBoxLayout;
 prevWindow->setFixedSize(300,50);
 connect(prevWindow, SIGNAL(clicked(bool)),this, SLOT(TornaIndietro()));
 temp2->addWidget(prevWindow,0,Qt::AlignLeft);

  QPushButton* b = new QPushButton("Ricarica finestra", this);
  b->setFixedSize(200,50);
  connect(b,SIGNAL(clicked(bool)),this, SLOT(reloadWindow()));
  temp2->addWidget(b,0, Qt::AlignCenter);

  b = new QPushButton("Invia nuovo messaggio", this);
  b->setFixedSize(200,50);
  connect(b,SIGNAL(clicked(bool)),this, SLOT(InviaNuovoMess()));
  temp2->addWidget(b);

  listric = new listaMail(ctrl);
  listric->loadMails();
  listric->setMaxPerPage(maxMailPerPage);
  listric->loadWindow();
  listric->setFixedHeight(700);

  listinv = new listaMail(ctrl, false);
  listinv->loadMails();
  listinv->setMaxPerPage(maxMailPerPage);
  listinv->loadWindow();
  listinv->setFixedHeight(700);

  tab->addTab(listric,"Posta ricevuta");
  tab->addTab(listinv,"Posta inviata");
  temp->addLayout(temp2);
  temp->addWidget(tab,1,Qt::AlignTop);
  setLayout(temp);
}
