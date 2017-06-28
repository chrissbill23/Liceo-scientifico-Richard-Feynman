#include "post.h"
#include "../Controller/controllergruppouser.h"
#include "groupboxrispostepost.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

QGroupBox *Post::Domanda()
{
    QGroupBox* temp = new QGroupBox(this);
    temp->setStyleSheet("QGroupBox{border: 0;}");

    QVBoxLayout* lay= new QVBoxLayout(temp);

    const QString& titolo = ctrl->daiPostTitolo(gruppo,post);
    const QString& autore = ctrl->daiPostAutore(gruppo,post);
    const QString& data = ctrl->daiPostData(gruppo,post);
    const QString& testo = ctrl->daiTestoPostGroup(gruppo,post);
    const QString& foto = ctrl->getGroupMemberFotoProfile(autore);

    QLabel* l = new QLabel("["+data+"]  "+titolo,temp);
    l->setFont(QFont("Times",13));
    lay->addWidget(l,0,Qt::AlignCenter|Qt::AlignTop);

    l = new QLabel(testo,temp);
    l->setFont(QFont("Times",11));
    lay->addWidget(l,0, Qt::AlignCenter|Qt::AlignTop);

    l = new QLabel(temp);
    l->setFixedSize(100,100);
    l->setStyleSheet("color: white;");
    if(foto != ""){
    l->setPixmap(QPixmap(foto));
    l->setScaledContents(true);
    }
    else {
        l->setText("Nessuna foto profilo");
        l->setFont(QFont("Times", 15));
    }
    lay->addWidget(l,0,Qt::AlignLeft|Qt::AlignTop);

    l = new QLabel(autore,temp);
    l->setFont(QFont("Times",10));
    lay->addWidget(l,1,Qt::AlignLeft|Qt::AlignTop);


    temp->setLayout(lay);
    return temp;
}

Post::Post(ControllerGruppoUser *c, const QString& n, int p): GruppoView(c,n),post(p), gruppo(n),
    Rispondi(0),Risposte(0), ctrl(c)
{
    setWindowTitle(ctrl->daiPostTitolo(gruppo,post));
    Header();
    BodyAndFooter();
    setStyleSheet("QGroupBox{ background-color: #29abe2;}");
}

void Post::BodyAndFooter()
{
    QHBoxLayout* lay = new QHBoxLayout;

    lay->addWidget(Domanda(),0);

    Risposte = new GroupBoxRispostePost(ctrl,gruppo,post,this);
    Risposte->setFixedWidth(1000);

    lay->addWidget(Risposte,0,Qt::AlignRight);
    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }
    p->addLayout(lay,1,0);
    setLayout(p);


}

void Post::reloadWindow()
{
    Risposte->reload();
}
