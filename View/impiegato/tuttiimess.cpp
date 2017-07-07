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
 setStyleSheet("QPushButton{background-color: #264d73; "
                                 "color: white; border-radius: 5px;}"
                                 "QPushButton:hover{"
                                        "color: #29abe2;}"
                                        "QPushButton:pressed {"
                                        "color:#660000;}");
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
  prevWindow->setFixedSize(200,40);
  prevWindow->setCursor(QCursor(Qt::PointingHandCursor));
  prevWindow->setStyleSheet("QPushButton{background-color: #669999; "
                   "color: white; border-radius: 5px;}"
                   "QPushButton:hover{"
                          "color: #29abe2;}"
                          "QPushButton:pressed {"
                          "color:#660000;}");
  connect(prevWindow, SIGNAL(clicked(bool)),this, SLOT(TornaIndietro()));
  temp2->addWidget(prevWindow,0,Qt::AlignLeft);

  QIcon i(QPixmap(":/Database/immagini/reload.png"));
  QPushButton* b = new QPushButton(this);
  b->setIcon(i);
  b->setToolTip("Ricarica finestra");
  b->setFixedSize(30,30);
  b->setCursor(QCursor(Qt::PointingHandCursor));
  b->setStyleSheet("QPushButton{background-color: #264d73; "
                   " border-radius: 5px;}");
  connect(b,SIGNAL(clicked(bool)),this, SLOT(reloadWindow()));
  temp2->addWidget(b,0, Qt::AlignRight);

  QPushButton* b2 = new QPushButton("Invia mail", this);
  b2->setFixedSize(120,40);
  b2->setCursor(QCursor(Qt::PointingHandCursor));
  connect(b2,SIGNAL(clicked(bool)),this, SLOT(InviaNuovoMess()));

  listric = new listaMail(ctrl);
  listric->loadMails();
  listric->setMaxPerPage(maxMailPerPage);
  listric->loadWindow();

  listinv = new listaMail(ctrl, false);
  listinv->loadMails();
  listinv->setMaxPerPage(maxMailPerPage);
  listinv->loadWindow();

  tab->addTab(listric,"Posta ricevuta");
  tab->addTab(listinv,"Posta inviata");
  tab->setStyleSheet("QTabWidget::tab-bar{width: 50em;}"
                   "QTabWidget{border-radius: 9px;}"
                   "QTabWidget::pane{ border-top: 2px solid #264d73;}"
                   "QTabBar::tab{min-width: 3ex; padding: 1em;}"
                   "QTabBar::tab:selected {"
                   "font: bold; color: #264d73;"
                   "}");
  temp->addLayout(temp2);
  temp->addWidget(b2, 0, Qt::AlignLeft);
  temp->addWidget(tab);
  setLayout(temp);
}
