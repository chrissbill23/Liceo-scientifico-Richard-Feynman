#include "gruppoview.h"
#include "../Controller/controllergruppouser.h"
#include "../Modello/filexml.h"
#include "formaddpostgroup.h"
#include "post.h"
#include "popupdialog.h"
#include "buttongroup.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

GruppoView::GruppoView(ControllerGruppoUser *c, const QString &name, QWidget *parent):Finestre(c,parent), ctrl(c), nomeGroup(name),p(0), head(0){}

int GruppoView::totPost() const
{
    return ctrl->totPostGroup(nomeGroup);
}

QString GruppoView::daiNomeGruppo() const
{
    return nomeGroup;
}

vector<string> GruppoView::InfoPost(unsigned int i)
{
    return ctrl->daiInfoPost(nomeGroup,i);
}

void GruppoView::OpenPost(int i)
{
    ctrl->ShowNewWindow(new Post(ctrl,nomeGroup,i));
}

void GruppoView::reloadWindow()
{
    if(head)
        delete head;
    head = 0;
}

void GruppoView::Header()
{
   if(!p){
   p = new QGridLayout(this);
   setLayout(p);
   }
    head = new QGroupBox(this);
    QHBoxLayout* lay = new QHBoxLayout(head);
        QPushButton* b = new QPushButton("Indietro",head);
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
        lay->addWidget(b,1, Qt::AlignLeft);

    if(!ctrl->isAdmin()){
        if(ctrl->isIscrittoInGroup(nomeGroup)){
                    buttonGroup* b2 = new buttonGroup("Annulla iscrizione",nomeGroup,this);
                    b2->setCursor(QCursor(Qt::PointingHandCursor));
                    b2->setFixedSize(300,40);
                    b2->setFont(QFont("Times", 13));
                    b2->setStyleSheet("QPushButton{"
                                     "background-color: #990000; "
                                     "border-radius: 5px 5px 5px 5px; "
                                     "color: white;}"
                                     "QPushButton:pressed {"
                                    " background-color:#003300;}");
                    connect(b2,SIGNAL(clicked(bool)),b2,SLOT(removeConnectedMember()));
                    lay->addWidget(b2);

        }
        else{
                    buttonGroup* b2 = new buttonGroup("Iscriviti",nomeGroup,this);
                    b2->setCursor(QCursor(Qt::PointingHandCursor));
                    b2->setFixedSize(300,40);
                    b2->setFont(QFont("Times", 13));
                    b2->setStyleSheet("QPushButton{"
                                     "background-color: #336699; "
                                     "border-radius: 5px 5px 5px 5px; "
                                     "color: white;}"
                                     "QPushButton:pressed {"
                                    " background-color:#003300;}");
                    connect(b2,SIGNAL(clicked(bool)),b2, SLOT(IscriviAGroup()));
                    lay->addWidget(b2);

        }
    }
        head->setLayout(lay);
        p->addWidget(head,0,0);

}

void GruppoView::BodyAndFooter()
{
    p->addWidget(new QLabel("Errore: niente da vedere. Verifica di aver effettuato l'accesso"));
}

vector<int> GruppoView::GiveIndexesPost(const QString &key) const
{
    vector<int> v;
    if(key == ""){
        int tot = totPost();
        for(int i = 0; i < tot; ++i)
            v.push_back(i);
    }
    else{
        v = ctrl->SearchPost(nomeGroup, key);
    }
    return v;
}

QGridLayout *GruppoView::giveLayout() const
{
    return p;
}

void GruppoView::IscriviMiAGroup(const QString &group)
{
    ctrl->IscrivimiAGroup(group);
}

void GruppoView::RemoveMeFromGroup(const QString &group)
{
    ctrl->ToglimiDaGroup(group);
}

void GruppoView::CreaNuovoPost()
{
    FormAddPostGroup temp(ctrl,nomeGroup);
    temp.setFixedSize(900,800);
    temp.exec();
    reloadWindow();
}

void GruppoView::deletePost(unsigned int i)
{
    if(ctrl->removePost(nomeGroup, i)){
        QMessageBox::information(0,"","Post eliminato!");
        reloadWindow();
    }
    else
        QMessageBox::information(0,"Errore","E' avvenuto un errore");
}

void GruppoView::HomePageGroup(const QString & groupName)
{
    ctrl->HomePageGroup(groupName);
}

void GruppoView::InfoGruppo(const QString &group) const
{
    const filexml& f = ctrl->giveSchedaGruppo(group);
    if(f.apriFile()){
        const QString& nome = QString::fromStdString(f.daiTestoIn("nomeGruppo"));
        const QString& descr = QString::fromStdString(f.daiTestoIn("descrizione"));
        const QString& categ = QString::fromStdString(f.daiTestoIn("categoria"));
        const QString& totMemb = QString::number(f.totNodi("nomeUtente"));
        const QString& totpost = QString::number(f.totNodi("post"));

        popUpDialog temp(1,10);
        QFont f1("Times",14);
        f1.setBold(true);

        QFont f2("Times",12);

        QLabel* lab = new QLabel("Nome Gruppo:",& temp);
        lab->setFont(f1);
        temp.push_back_Widget(lab);

        lab = new QLabel(nome,&temp);
        lab->setFont(f2);
        temp.push_back_Widget(lab);

        lab = new QLabel("Descrizione:",&temp);
        lab->setFont(f1);
        temp.push_back_Widget(lab);

        lab = new QLabel(descr,&temp);
        lab->setFont(f2);
        temp.push_back_Widget(lab);

        lab = new QLabel("Categoria:",&temp);
        lab->setFont(f1);
        temp.push_back_Widget(lab);

        lab = new QLabel(categ,&temp);
        lab->setFont(f2);
        temp.push_back_Widget(lab);

        lab = new QLabel("Totale membri:",&temp);
        lab->setFont(f1);
        temp.push_back_Widget(lab);

        lab = new QLabel(totMemb,&temp);
        lab->setFont(f2);
        temp.push_back_Widget(lab);

        lab = new QLabel("Totale post pubblicati:",&temp);
        lab->setFont(f1);
        temp.push_back_Widget(lab);

        lab = new QLabel(totpost,&temp);
        lab->setFont(f2);
        temp.push_back_Widget(lab);

        temp.setFixedSize(500,600);
        temp.setWindowTitle("Info sul gruppo "+group);
        temp.exec();
    }
}
