#include "groupboxrispostepost.h"
#include "../Controller/controllergruppouser.h"
#include <QGridLayout>
#include <QTextEdit>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QDate>
#include <QMessageBox>

int GroupBoxRispostePost::maxPerPage = 3;

QGroupBox *GroupBoxRispostePost::Risposte(int indice)
{
    QGroupBox* temp = new QGroupBox;

    QGridLayout* p = new QGridLayout(temp);
    temp->setLayout(p);

    QFont f("Times",14);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(totRisp)+" Risposte",temp);
    p->addWidget(lab,0,0,1,1);
    lab->setFont(f);
    int i = totRisp - 1- indice;
    int conta = 0;
    for(; i >= 0 && conta <maxPerPage; --i){

        const QString& dataR = ctrl->daiDataRisposta(gruppo,post,i);
        const QString& autor = ctrl->daiAutoreRisposta(gruppo,post,i);
        const QString& foto = ctrl->getGroupMemberFotoProfile(autor);
        const QString& testo = ctrl->daiTestoRisposta(gruppo,post,i);


        lab = new QLabel(temp);
        lab->setFont(QFont("Times",10));
        lab->setFixedSize(60,60);
        if(foto != ""){
        lab->setPixmap(QPixmap(foto));
        lab->setScaledContents(true);
        }
        else {
            lab->setText("Nessuna foto profilo");
            lab->setFont(QFont("Times", 15));
        }
        p->addWidget(lab,conta*2+1,0,1,1,Qt::AlignTop);

        lab = new QLabel(autor,temp);
        lab->setFont(QFont("Times",10));
        p->addWidget(lab,conta*2+2,0,1,1,Qt::AlignTop);

        lab = new QLabel(dataR+"\n"+testo,temp);
        lab->setFont(QFont("Times",10));
        p->addWidget(lab,conta*2+1,1,1,1,Qt::AlignTop);
        p->setSpacing(3);
        ++conta;
    }

    lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
    lab->setFont(f);
    p->addWidget(lab,conta*2+2,1,1,1,Qt::AlignHCenter);
    QIcon i1;
    if(currPage > 1){
        i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
        QPushButton* b = new QPushButton(temp);
        b->setIcon(i1);
        b->setFixedSize(200,40);
        b->setIconSize(QSize(200,40));
        b->setStyleSheet("QPushButton{"
                         "border: 0;"
                         "border-radius: 5px 5px 5px 5px; }"
                         "QPushButton:pressed {"
                         "background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        p->addWidget(b,conta*2+2,0,1,1,Qt::AlignLeft);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
    }

    if(conta+indice < totRisp){
        i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
        QPushButton* b2 = new QPushButton(temp);
        b2->setIcon(i1);
        b2->setFixedSize(200,40);
        b2->setIconSize(QSize(200,40));
        b2->setStyleSheet("QPushButton{"
                          "border: 0;"
                          "border-radius: 5px 5px 5px 5px; }"
                          "QPushButton:pressed {"
                          "background-color:#003300;}");
        b2->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
        p->addWidget(b2,conta*2+2,2,1,1,Qt::AlignRight);
    }


    return temp;
}

void GroupBoxRispostePost::rispondi()
{
    const QString& commento = Rispondi->toPlainText();

   if(commento != ""){
       const QString& check = ctrl->addRispostaToPost(post,gruppo,
                                                      QDate::currentDate().toString("dd/MM/yyyy"),
                                                      commento);
      if(check == ""){
         QMessageBox::information(this,"","Salvato con successo!") ;
         Rispondi->setText("");
      reload();
      return;
      }
      else{
          QMessageBox::information(this,"",check) ;
          return;
      }
   }
   QMessageBox::information(this,"Errore","Deve scrivere una risposta") ;
}

void GroupBoxRispostePost::goNext()
{
    currPage++;
    scroll->setWidget(Risposte((currPage-1)* maxPerPage));
    scroll->setWidgetResizable(true);

}

void GroupBoxRispostePost::goPrev()
{
    if(currPage > 1){
        --currPage;
        scroll->setWidget(Risposte((currPage-1)* maxPerPage));
        scroll->setWidgetResizable(true);
    }
}

GroupBoxRispostePost::GroupBoxRispostePost(ControllerGruppoUser *c, const QString &n, int p, QWidget *parent): QGroupBox(parent),
    post(p),gruppo(n),Rispondi(0),scroll(0), ctrl(c),lay(new QVBoxLayout(this)), totRisp(0), totPage(1), currPage(1)
{
    Rispondi = new QTextEdit(this);
    Rispondi->setFixedSize(600,300);
    Rispondi->setFont(QFont("Times",11));
    QPushButton* b = new QPushButton("Invia",this);
    b->setFixedSize(300,40);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rispondi()));
    lay->addWidget(Rispondi,0,Qt::AlignTop);
    lay->addWidget(b,0,Qt::AlignTop);

    totRisp = ctrl->totRisposteAPost(gruppo,post);

    totPage = totRisp / maxPerPage;
    if(totRisp % maxPerPage > 0 || totRisp == 0)
        ++totPage;

    scroll = new QScrollArea(this);
    scroll->setWidget(Risposte(0));
    scroll->setWidgetResizable(true);

    lay->addWidget(scroll,1);

    setLayout(lay);
}

void GroupBoxRispostePost::reload()
{
    totRisp = ctrl->totRisposteAPost(gruppo,post);

    currPage = 1;
    totPage = totRisp / maxPerPage;
    if(totRisp % maxPerPage > 0 || totRisp == 0)
        ++totPage;

    scroll->setWidget(Risposte(0));
    scroll->setWidgetResizable(true);
}
