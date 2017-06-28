#include "gestpostsgroup.h"
#include "../../buttongroup.h"
#include "../../../Controller/controlleradminsistema.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QScrollArea>
#include <QLineEdit>
#include <QMessageBox>

int GestPostsGroup::maxPerPage = 4;

QGroupBox *GestPostsGroup::loadPage(int indice)
{
    QGroupBox* temp = new QGroupBox;

    QGridLayout* lay = new QGridLayout(temp);
    int totpost = post.size();
    if(totpost==0){
        lay->addWidget(new QLabel("Non ci sono post"),0,Qt::AlignTop);
    }else{

        QFont f("Times",13);
        QLabel* la = new QLabel(QString::number(totpost)+" post trovati");
        la->setFont(f);
        lay->addWidget(la,0,0,1,1,Qt::AlignTop);

        int i = totpost - 1 - indice;
        int conta = 0;
      for(; i >= 0 && conta < maxPerPage; --i){
        vector<string> v = ctrl->daiInfoPost(daiNomeGruppo(),post[i]);

        la = new QLabel("["+QString::fromStdString(v[0])+"]  "
                +QString::fromStdString(v[1])+ ":  "+QString::fromStdString(v[2]), temp);
        la->setFont(f);
        la->setFixedWidth(500);
        la->setScaledContents(true);
        lay->addWidget(la,conta+1, 0,1,1,Qt::AlignTop);


        buttonGroup* b = new buttonGroup("Visualizza",group,this,"",post[i]);
        b->setFont(f);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(GotoPost()));
        lay->addWidget(b,conta+1, 1,1,1,Qt::AlignTop);

        b = new buttonGroup("Elimina post",group,this,"",post[i]);
        b->setFont(f);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(deletePost()));
        lay->addWidget(b,conta+1, 2,1,1,Qt::AlignTop);
        ++conta;
        }

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
          lay->addWidget(b,maxPerPage+1,0,1,1,Qt::AlignLeft);
          connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
      }
      QLabel* lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
      lab->setFont(f);
      lay->addWidget(lab,maxPerPage+1,1,1,1,Qt::AlignHCenter);


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
          lay->addWidget(b2,maxPerPage+1,2,1,1,Qt::AlignRight);
      }
    }
    temp->setLayout(lay);
    return temp;
}

GestPostsGroup::GestPostsGroup(ControllerAdminSistema *c, const QString &name, QWidget *parent) : GruppoView(c, name, parent), ctrl(c),
 group(name), head(0),
 sc(new QScrollArea(this)),searchbox(0), currPage(1),totPage(1),layout(new QVBoxLayout(this))
{
    Header();
    BodyAndFooter();
    layout->addWidget(sc,1);
}

void GestPostsGroup::Header()
{
    head = new QGroupBox(this);
    QVBoxLayout* lay = new QVBoxLayout(head);
    head->setLayout(lay);

    QPushButton* b = new QPushButton("Indietro", head);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFixedSize(300,40);
    b->setFont(QFont("Times", 13));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this, SLOT(TornaIndietro()));
    lay->addWidget(b,0, Qt::AlignLeft);

    QFont f("Times",13);
    searchbox = new QLineEdit(head);
    searchbox->setPlaceholderText("Cerca un post (al massimo 50 caratteri)");
    searchbox->setFont(f);
    searchbox->setMaxLength(50);
    searchbox->setFixedSize(400,50);
    b = new QPushButton("Cerca",head);
    b->setFont(f);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFixedSize(100,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cercaPost()));
    lay->addWidget(searchbox,0,Qt::AlignTop);
    lay->addWidget(b,0,Qt::AlignTop);

    layout->addWidget(head,0,Qt::AlignTop);
}

void GestPostsGroup::BodyAndFooter()
{
    post = GiveIndexesPost();
    int totpost = post.size();
    totPage = totpost / maxPerPage;
    if(totpost % maxPerPage > 0 || totpost == 0 )
        ++totPage;
    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
}

void GestPostsGroup::reloadWindow()
{
    int totpost = post.size();
    currPage = 1;
    totPage = totpost / maxPerPage;
    if(totpost % maxPerPage > 0 || totpost == 0 )
        ++totPage;
    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
}

void GestPostsGroup::goNext()
{
    currPage++;
    sc->setWidget(loadPage((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void GestPostsGroup::goPrev()
{
    if(currPage > 1){
        currPage--;
        sc->setWidget(loadPage((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
    }
}

void GestPostsGroup::deletePost(unsigned int i)
{
    if(ctrl->removePost(group, i)){
        QMessageBox::information(this,"","Post eliminato!");
        post = GiveIndexesPost();
        reloadWindow();
    }
    else
        QMessageBox::information(this,"Errore","E' avvenuto un errore");
}

void GestPostsGroup::cercaPost()
{
    post = GiveIndexesPost(searchbox->text());
    reloadWindow();
}
