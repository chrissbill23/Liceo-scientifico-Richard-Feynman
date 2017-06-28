#include "personalspacegroupstud.h"
#include "../../Controller/controllergruppouser.h"
#include "../buttongroup.h"
#include <QRadioButton>
#include <QGridLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>

int PersonalSpaceGroupStud::maxPerPage = 3;
QGroupBox *PersonalSpaceGroupStud::MyPost(int indice)
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* la = new QGridLayout(temp);
    temp->setLayout(la);

    QFont f("Times",14);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(myPost.size())+" post trovati:");
    lab->setFont(f);
    la->addWidget(lab,0,0,1,1,Qt::AlignTop);

    f = QFont("Times",12);
    int i = myPost.size() -1-indice;
    int conta = 0;
    for(; i >= 0 && conta < maxPerPage; --i){
        lab = new QLabel("["+ctrl->daiPostData(nomeGroup,myPost[i])+"]:  "+
                        ctrl->daiPostTitolo(nomeGroup, myPost[i]));
        lab->setFont(f);
        buttonGroup* b = new buttonGroup("Vedi",nomeGroup,this,"",myPost[i]);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        b->setFont(f);
        connect(b,SIGNAL(clicked(bool)),b,SLOT(GotoPost()));

        buttonGroup* b2 = new buttonGroup("Elimina post",nomeGroup,this,"",myPost[i]);
        connect(b2,SIGNAL(clicked(bool)),b,SLOT(deletePost()));
        b2->setFont(f);
        la->addWidget(lab,conta+1,0,1,1,Qt::AlignTop);
        la->addWidget(b,conta+1,1,1,1,Qt::AlignTop);
        la->addWidget(b2,conta+1,2,1,1,Qt::AlignTop);
        ++conta;
    }

    lab = new QLabel("pagina "+QString::number(currPagePost)+"/"+QString::number(totPageP));
    lab->setFont(f);
    la->addWidget(lab,conta+2,1,1,1,Qt::AlignHCenter);
    QIcon i1;
    if(currPagePost > 1){
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
        la->addWidget(b,conta+2,0,1,1,Qt::AlignLeft);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
    }

    int tot = myPost.size();
    if(conta+indice < tot){
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
        la->addWidget(b2,conta+2,2,1,1,Qt::AlignRight);
    }

    return temp;
}

QGroupBox *PersonalSpaceGroupStud::MyAnsw(int indice)
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* la = new QGridLayout(temp);
    temp->setLayout(la);

    QFont f("Times",14);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(myAnsw.size())+" post trovati:");
    lab->setFont(f);
    la->addWidget(lab,0,0,1,1,Qt::AlignTop);

    f = QFont("Times",12);
    int i = myAnsw.size() -1-indice;
    int conta = 0;
    for(; i >= 0 && conta < maxPerPage; --i){
        lab = new QLabel("["+ctrl->daiPostData(nomeGroup,myAnsw[i])+"]:  "+
                        ctrl->daiPostTitolo(nomeGroup, myAnsw[i]));
        lab->setFont(f);
        buttonGroup* b = new buttonGroup("Vedi",nomeGroup,this,"",myAnsw[i]);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        b->setFont(f);
        connect(b,SIGNAL(clicked(bool)),b,SLOT(GotoPost()));

        la->addWidget(lab,conta+1,0,1,1,Qt::AlignTop);
        la->addWidget(b,conta+1,1,1,1,Qt::AlignTop);
        ++conta;
    }

    lab = new QLabel("pagina "+QString::number(currPageAnsw)+"/"+QString::number(totPageR));
    lab->setFont(f);
    la->addWidget(lab,conta+2,1,1,1,Qt::AlignHCenter);
    QIcon i1;
    if(currPageAnsw > 1){
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
        la->addWidget(b,conta+2,0,1,1,Qt::AlignLeft);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
    }

    int tot = myAnsw.size();
    if(indice+conta < tot){
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
        la->addWidget(b2,conta+2,2,1,1,Qt::AlignRight);
    }


    return temp;
}

void PersonalSpaceGroupStud::setOnMyPosts()
{
    scroll->setWidget(MyPost(0));
    scroll->setWidgetResizable(true);
}

void PersonalSpaceGroupStud::setOnMyAnswers()
{
    scroll->setWidget(MyAnsw(0));
    scroll->setWidgetResizable(true);
}

PersonalSpaceGroupStud::PersonalSpaceGroupStud(ControllerGruppoUser *c, const QString &n, QWidget *parent) : GruppoView(c,n,parent), ctrl(c), nomeGroup(n),
    scroll(new QScrollArea(this)), lay(new QVBoxLayout(this)), mYpost(0), mYAnsw(0), totPageP(1), totPageR(1), currPagePost(1),
    currPageAnsw(1)
{
    myPost = ctrl->MyPost(nomeGroup);
    myAnsw = ctrl->PostIAnswered(nomeGroup);
    int tot = myPost.size();
    totPageP = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0 )
        ++totPageP;

    tot = myAnsw.size();
    totPageR = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0 )
        ++totPageR;
    Header();
    BodyAndFooter();
    setLayout(lay);
}

void PersonalSpaceGroupStud::reloadWindow()
{
    myPost = ctrl->MyPost(nomeGroup);
    myAnsw = ctrl->PostIAnswered(nomeGroup);

    currPageAnsw = 1;
    currPagePost = 1;
    int tot = myPost.size();
    totPageP = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0 )
        ++totPageP;

    tot = myAnsw.size();
    totPageR = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0 )
        ++totPageR;

    if(mYpost->isChecked()){
        scroll->setWidget(MyPost(0));
        scroll->setWidgetResizable(true);
    }
    else{
        scroll->setWidget(MyAnsw(0));
        scroll->setWidgetResizable(true);
    }
}

void PersonalSpaceGroupStud::goNext()
{

    if(mYpost->isChecked()){
        currPagePost++;
        scroll->setWidget(MyPost((currPagePost-1)*maxPerPage));
        scroll->setWidgetResizable(true);
    }
    else{
        currPageAnsw++;
        scroll->setWidget(MyAnsw((currPageAnsw-1)*maxPerPage));
        scroll->setWidgetResizable(true);
    }
}

void PersonalSpaceGroupStud::goPrev()
{

    if(mYpost->isChecked()){
        currPagePost--;
        scroll->setWidget(MyPost((currPagePost-1)*maxPerPage));
        scroll->setWidgetResizable(true);
    }
    else{
        currPageAnsw--;
        scroll->setWidget(MyAnsw((currPageAnsw-1)*maxPerPage));
        scroll->setWidgetResizable(true);
    }
}

void PersonalSpaceGroupStud::Header()
{
    QFont f("Times", 13);
    f.setBold(true);
    mYpost = new QRadioButton("I miei post", this);
    mYpost->setFont(f);
    mYpost->setChecked(true);
    connect(mYpost,SIGNAL(clicked(bool)),this,SLOT(setOnMyPosts()));
    mYAnsw = new QRadioButton("Le mie risposte a post", this);
    mYAnsw->setFont(f);
    connect(mYAnsw,SIGNAL(clicked(bool)),this,SLOT(setOnMyAnswers()));

    QPushButton* b = new QPushButton("Scrivi nuovo post", this);
    b->setFont(QFont("Times",11));
    b->setFixedSize(200,50);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(CreaNuovoPost()));
    b->setCursor(QCursor(Qt::PointingHandCursor));

    lay->addWidget(mYpost,0,Qt::AlignTop);
    lay->addWidget(mYAnsw,0, Qt::AlignTop);
    lay->addWidget(b,0, Qt::AlignTop|Qt::AlignRight);
}

void PersonalSpaceGroupStud::BodyAndFooter()
{
    scroll->setWidget(MyPost(0));
    scroll->setWidgetResizable(true);
    lay->addWidget(scroll);
}
