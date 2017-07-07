#include "gestionesegrgroupbox.h"
#include "buttongestimp.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QLabel>
#include <QMessageBox>
#include "../../popupdialog.h"
#include "../../../Modello/filexml.h"

int GestioneSegrGroupBox::maxPerPage = 10;
QGroupBox *GestioneSegrGroupBox::loadPage(int indice)
{
    QGroupBox* temp = new QGroupBox;
    temp->setStyleSheet("QGroupBox{border: 0;}");
    QGridLayout* p = new QGridLayout(temp);
    temp->setLayout(p);

    int tot = segr.size();

    QFont f("Times",9);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(tot)+" segretari");
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 5em;");
    p->addWidget(lab,0,0);

    f = QFont("Times",10);
    f.setBold(true);

    lab = new QLabel("Cognome",temp);
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 2em;");
    p->addWidget(lab,1,0);
    lab = new QLabel("Nome",temp);
    lab->setStyleSheet("margin-bottom: 2em;");
    lab->setFont(f);
    p->addWidget(lab,1,1);


    int row = 1;
    f = QFont("Times",9);
    for(int i = indice; i < tot && i < maxPerPage; ++i){
        const QString& seg = QString::fromStdString(segr[i]);
        const QString& nomeutente = seg;
        const QString& cognome = ctrl->daiCognomeSegr(seg);
        const QString& nome = ctrl->daiNomeSegr(seg);

        lab = new QLabel(cognome, temp);
        lab->setFont(f);
        lab->setFixedWidth(300);
        p->addWidget(lab,row+1,0,1,1,Qt::AlignTop);

        lab = new QLabel(nome, temp);
        lab->setFont(f);
        lab->setFixedWidth(300);
        p->addWidget(lab,row+1,1,1,1,Qt::AlignTop);

        buttonGestImp* b = new buttonGestImp("Dettagli",nomeutente,this);
        b->setFont(f);
        b->setFixedSize(150,30);
        b->setStyleSheet("QPushButton{"
                              "background-color: #336699; "
                              "border-radius: 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                             " background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(vediInfoImp()));
        p->addWidget(b,row+1,2,1,1,Qt::AlignTop);

        b = new buttonGestImp("Rimuovi segretario",nomeutente,this);
        b->setFont(f);
        b->setFixedSize(150,30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #990000;"
                         "color: white;"
                         " border-radius: 5px;}"
                         "QPushButton:pressed {"
                         " background-color:#660000;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(ElimImp()));
        p->addWidget(b,row+1,3,1,1,Qt::AlignTop);

        ++row;

    }
    p->setRowStretch(row,1);


    return temp;

}

GestioneSegrGroupBox::GestioneSegrGroupBox(ControllerPreside *c, QWidget *parent): FinestrePreside(c,parent),
        ctrl(c), contenuto(0), currPage(1), totPage(1), lay(0)
{
    BodyAndFooter();
    setStyleSheet("background-color: none;");
}

void GestioneSegrGroupBox::BodyAndFooter()
{
    segr = ctrl->giveSegrNU();
    totPage = segr.size() / maxPerPage;
    if(segr.size() % maxPerPage > 0 || totPage == 0)
        ++totPage;
    contenuto = new QScrollArea(this);
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
    contenuto->setFrameShape(QFrame::NoFrame);

    lay = new QVBoxLayout(this);
    lay->addWidget(contenuto,0);

    setLayout(lay);
}

void GestioneSegrGroupBox::reloadWindow()
{
    vector<string> temp = ctrl->giveSegrNU();
    if(temp.size() != segr.size())
        segr = temp;
    totPage = segr.size() / maxPerPage;
    if(segr.size() % maxPerPage > 0 || totPage == 0)
        ++totPage;
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
}

void GestioneSegrGroupBox::viewInfoImpiegato(const QString &nomeUtente) const
{
    const filexml& file = ctrl->giveSchedaPersonaleSegr(nomeUtente);
    const QString& cogn = QString::fromStdString(file.daiTestoIn("Cognome"));
    const QString& nome = QString::fromStdString(file.daiTestoIn("Nome"));

    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);

    popUpDialog temp(1,4);
    QLabel* tit = new QLabel("Nome:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(nome,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    tit = new QLabel("Cognome:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(cogn,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    temp.setFixedSize(500,500);

    temp.exec();
}

void GestioneSegrGroupBox::rimuoviImpiegato(const QString &nomeUtente)
{
    if(ctrl->rimuoviSegr(nomeUtente)){
        QMessageBox::information(0, "","Segretario/a rimosso/a ");
        reloadWindow();
    }
    else
        QMessageBox::information(0, "Errore","E' avvenuto un errore");
}
