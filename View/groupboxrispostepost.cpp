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

int GroupBoxRispostePost::maxPerPage = 7;

QGroupBox *GroupBoxRispostePost::Risposte(int indice)
{
    QGroupBox* temp = new QGroupBox;

    QGridLayout* p = new QGridLayout(temp);
    temp->setLayout(p);

    QFont f("Times",11);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(totRisp)+" Risposte\n\n",temp);
    p->addWidget(lab,0,0,1,1);
    lab->setFont(f);
    int i = totRisp - 1- indice;
    int conta = 0;
    for(; i >= 0 && conta <maxPerPage; --i){

        const QString& dataR = ctrl->daiDataRisposta(gruppo,post,i);
        const QString& autor = ctrl->daiAutoreRisposta(gruppo,post,i);
        const QString& foto = ctrl->getGroupMemberFotoProfile(autor);
        QString testo = ctrl->daiTestoRisposta(gruppo,post,i);


        QVBoxLayout* l = new QVBoxLayout;
        lab = new QLabel(temp);
        lab->setFont(QFont("Times",10));
        lab->setFixedSize(60,60);
        if(foto != ""){
        lab->setPixmap(QPixmap(foto));
        lab->setScaledContents(true);
        }
        else {
            lab->setText("Nessuna foto profilo");
            lab->setFont(QFont("Times", 13));
        }
        l->addWidget(lab,0,Qt::AlignTop);

        lab = new QLabel(autor,temp);
        lab->setFont(QFont("Times",9));
        l->addWidget(lab,1,Qt::AlignTop);

        p->addLayout(l,conta*2+1,0,1,1,Qt::AlignTop);

        l = new QVBoxLayout;
        int tot = testo.size()/100;
        while(tot > 0){
            testo.insert(tot*50,"\n");
            --tot;
        }
        f = QFont("Times",9);
        f.setBold(true);
        lab = new QLabel(dataR,temp);
        lab->setFont(f);
        l->addWidget(lab,0,Qt::AlignTop);
        lab = new QLabel(testo+"\n\n",temp);
        lab->setFont(QFont("Times",10));
        l->addWidget(lab,1,Qt::AlignTop);

        p->addLayout(l,conta*2+2,0,1,1,Qt::AlignTop);
        p->setSpacing(3);
        ++conta;
    }

    QGroupBox* footer = new QGroupBox(temp);
    footer->setStyleSheet("QGroupBox{border: 0;}");
    QGridLayout* footerLay = new QGridLayout(footer);
    footer->setLayout(footerLay);

    lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
    lab->setFont(QFont("Times",8));
    footerLay->addWidget(lab,0,1,1,1,Qt::AlignHCenter);
    footerLay->setColumnStretch(0,1);
    footerLay->setColumnStretch(2,1);

    QIcon i1;
    if(currPage > 1){
        i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
        QPushButton* b = new QPushButton(temp);
        b->setIcon(i1);
        b->setFixedSize(150,30);
        b->setIconSize(QSize(150,30));
        b->setStyleSheet("QPushButton{"
                         "border: 0;"
                         "border-radius: 5px 5px 5px 5px; }"
                         "QPushButton:pressed {"
                         "background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        footerLay->addWidget(b,0,0,1,1,Qt::AlignLeft);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
    }

    if(conta+indice < totRisp){
        i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
        QPushButton* b2 = new QPushButton(temp);
        b2->setIcon(i1);
        b2->setFixedSize(150,30);
        b2->setIconSize(QSize(150,30));
        b2->setStyleSheet("QPushButton{"
                          "border: 0;"
                          "border-radius: 5px 5px 5px 5px; }"
                          "QPushButton:pressed {"
                          "background-color:#003300;}");
        b2->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
        footerLay->addWidget(b2,0,2,1,1,Qt::AlignRight);
    }

    p->addWidget(footer,conta*2,0,1,2);

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
    post(p),gruppo(n),Rispondi(0),scroll(0), ctrl(c),lay(new QHBoxLayout(this)), totRisp(0), totPage(1), currPage(1)
{
    Rispondi = new QTextEdit(this);
    Rispondi->setFont(QFont("Times",11));
    Rispondi->setFixedSize(500,200);
    Rispondi->setPlaceholderText("Rispondi...");
    QPushButton* b = new QPushButton("Invia",this);
    b->setFixedSize(150,40);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rispondi()));

    QVBoxLayout* lay2 = new QVBoxLayout;
    lay2->addWidget(Rispondi,0,Qt::AlignTop);
    lay2->addWidget(b,1,Qt::AlignTop);

    lay->addLayout(lay2,0);
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
