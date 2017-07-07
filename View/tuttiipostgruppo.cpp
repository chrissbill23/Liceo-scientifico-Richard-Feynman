#include "tuttiipostgruppo.h"
#include "buttongroup.h"
#include "../Controller/controllergruppouser.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QScrollArea>

int TuttiIPostGruppo::maxPerPage = 12;
QGroupBox *TuttiIPostGruppo::loadPost(int indice)
{
    QGroupBox* temp = new QGroupBox;

    QVBoxLayout* lay = new QVBoxLayout(temp);
    int totpost = post.size();
    if(ctrl->isIscrittoInGroup(groupName)){
    if(totpost==0){
        lay->addWidget(new QLabel("Non ci sono post"),0,Qt::AlignTop);
    }else{
        QFont f("Times",10);
        searchbox = new QLineEdit(temp);
        searchbox->setPlaceholderText("Cerca un post (al massimo 50 caratteri)");
        searchbox->setFont(f);
        searchbox->setMaxLength(50);
        searchbox->setFixedSize(400,40);
        QPushButton* b = new QPushButton("Cerca",temp);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        b->setFixedSize(150,30);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(cercaPost()));
        lay->addWidget(searchbox,0,Qt::AlignTop);
        lay->addWidget(b,0,Qt::AlignTop);

        QLabel* la = new QLabel(QString::number(totpost)+" post trovati");
        la->setFont(f);
        lay->addWidget(la,0,Qt::AlignTop);

        int i = totpost - 1 - indice;
        int conta = 0;
      for(; i >= 0 && conta < maxPerPage; --i){
        vector<string> v = ctrl->daiInfoPost(daiNomeGruppo(),post[i]);
        buttonGroup* b = new buttonGroup("["+QString::fromStdString(v[0])+"]  "
                +QString::fromStdString(v[1])+ ":  "+QString::fromStdString(v[2]),groupName,this,"",post[i]);
        b->setFont(f);
        b->setFixedHeight(40);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        b->setStyleSheet("padding: 0 1em 0 1em; ");
        connect(b,SIGNAL(clicked(bool)),b,SLOT(GotoPost()));
        lay->addWidget(b,0,Qt::AlignTop|Qt::AlignHCenter);
        ++conta;
        }
      QHBoxLayout* lay2 = new QHBoxLayout;

      QIcon i1;
      if(currPage > 1){
          i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
          QPushButton* b = new QPushButton(temp);
          b->setIcon(i1);
          b->setFixedSize(200,40);
          b->setIconSize(QSize(200,40));
          b->setStyleSheet("QPushButton{"
                           "background-color: #336699;"
                           "border: 2px solid;"
                           "border-radius: 5px 5px 5px 5px; "
                           "color: white;}"
                           "QPushButton:pressed {"
                           "background-color:#003300;}");
          b->setCursor(QCursor(Qt::PointingHandCursor));
          lay2->addWidget(b,0,Qt::AlignLeft);
          connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
      }
      QLabel* lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
      lab->setFont(f);
      lay2->addWidget(lab,0,Qt::AlignHCenter);


      if(conta+indice < totpost){
          i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
          QPushButton* b2 = new QPushButton(temp);
          b2->setIcon(i1);
          b2->setFixedSize(200,40);
          b2->setIconSize(QSize(200,40));
          b2->setStyleSheet("QPushButton{"
                            "background-color: #336699;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
          b2->setCursor(QCursor(Qt::PointingHandCursor));
          connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
          lay2->addWidget(b2,0,Qt::AlignRight);
      }
      lay->addLayout(lay2,1);
      lay->setStretch(indice+maxPerPage+2, 1);
    }
    }
    else{
        lay->addWidget(new QLabel("E' richiesta l'iscrizione al gruppo per visualizzare i post"),0,Qt::AlignTop);
    }
    temp->setLayout(lay);
    return temp;
}


TuttiIPostGruppo::TuttiIPostGruppo(ControllerGruppoUser *c, const QString& n, QWidget *parent): GruppoView(c,n,parent),ctrl(c),groupName(n),
    searchbox(0),sc(new QScrollArea(this)),layout(new QVBoxLayout(this)), totPage(1), currPage(1)
{
    Header();
    BodyAndFooter();
    layout->addWidget(sc,0);
}

void TuttiIPostGruppo::Header()
{
    setWindowTitle("Tutti i post");
}

void TuttiIPostGruppo::BodyAndFooter()
{
    post = GiveIndexesPost();
    int totpost = post.size();
    totPage = totpost / maxPerPage;    
    currPage = 1;
    if(totpost % maxPerPage > 0 || totpost == 0 )
        ++totPage;
    sc->setWidget(loadPost(0));
    sc->setWidgetResizable(true);
}

void TuttiIPostGruppo::cercaPost()
{
   post = GiveIndexesPost(searchbox->text());
   int totpost = post.size();
   totPage = totpost / maxPerPage;
   if(totpost % maxPerPage > 0 || totpost == 0 )
       ++totPage;
   sc->setWidget(loadPost(0));
   sc->setWidgetResizable(true);
}

void TuttiIPostGruppo::reloadWindow()
{
    BodyAndFooter();
}

void TuttiIPostGruppo::goNext()
{
    currPage++;
    sc->setWidget(loadPost((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void TuttiIPostGruppo::goPrev()
{
    if(currPage > 1){
        currPage--;
        sc->setWidget(loadPost((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
    }
}
