#include "gestioneprofgroupbox.h"
#include "buttongestimp.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include "../../popupdialog.h"
#include "../../../Modello/filexml.h"

int GestioneProfGroupBox::maxPerPage = 10;
QGroupBox *GestioneProfGroupBox::loadPage(int indice)
{
    QGroupBox* temp = new QGroupBox;
    temp->setStyleSheet("QGroupBox{border: 0;}");
    QGridLayout* p = new QGridLayout(temp);
    temp->setLayout(p);

    int tot = prof.size();

    QFont f("Times",9);
    f.setUnderline(true);
    QLabel* lab = new QLabel(QString::number(tot)+" professori trovati", temp);
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
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 2em;");
    p->addWidget(lab,1,1);

    int row = 2;
    f = QFont("Times",9);
    for(int i = indice; i < tot && i < maxPerPage; ++i){
        const QString& pr = QString::fromStdString(prof[i]);
        const QString& nomeutente = pr;
        const QString& cognome = ctrl->daiCognomeProf(pr);
        const QString& nome = ctrl->daiNomeProf(pr);

        lab = new QLabel(cognome, temp);
        lab->setFont(f);
        lab->setFixedWidth(150);
        p->addWidget(lab,row,0,1,1,Qt::AlignTop);

        lab = new QLabel(nome, temp);
        lab->setFont(f);
        lab->setFixedWidth(150);
        p->addWidget(lab,row,1,1,1,Qt::AlignTop);

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
        p->addWidget(b,row,2,1,1,Qt::AlignTop);

        b = new buttonGestImp("Assegna classe",nomeutente,this);
        b->setFont(f);
        b->setFixedSize(150,30);
        b->setStyleSheet("QPushButton{"
                              "background-color: #336699; "
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                             " background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(AssegnaClasseProf()));
        p->addWidget(b,row,3,1,1,Qt::AlignTop);

        b = new buttonGestImp("Togli classe",nomeutente,this);
        b->setFont(f);
        b->setFixedSize(150,30);
        b->setStyleSheet("QPushButton{"
                              "background-color: #336699; "
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                             " background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(RimuoviClasseProf()));
        p->addWidget(b,row,4,1,1,Qt::AlignTop);

        b = new buttonGestImp("Rimuovi",nomeutente,this);
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
        p->addWidget(b,row,5,1,1,Qt::AlignTop);

        ++row;

    }
    p->setRowStretch(row,1);


    return temp;

}

GestioneProfGroupBox::GestioneProfGroupBox(ControllerPreside *c, QWidget *parent): FinestrePreside(c,parent),
    ctrl(c), searchBox(0), contenuto(0), currPage(1), totPage(1), lay(0)
{
    Header();
    BodyAndFooter();
    setStyleSheet("background-color: none;");
}

void GestioneProfGroupBox::Header()
{

    searchBox = new QLineEdit(this);
    searchBox->setFixedSize(350,40);
    searchBox->setPlaceholderText("nome, cognome, materia, classe..");
    searchBox->setFont(QFont("Times",10));
    QHBoxLayout* temp = new QHBoxLayout;
    temp->addWidget(searchBox,1,Qt::AlignRight);

   QPushButton* b = new QPushButton("Cerca",this);
    b->setFixedSize(150,40);
    b->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(CercaImpiegato()));

    temp->addWidget(b,0,Qt::AlignRight);

    lay = new QVBoxLayout(this);

    lay->addLayout(temp,0);

    setLayout(lay);
}

void GestioneProfGroupBox::BodyAndFooter()
{
    prof = ctrl->giveProfNU();
    totPage = prof.size() / maxPerPage;
    if(prof.size() % maxPerPage > 0 || totPage == 0)
        ++totPage;
    contenuto = new QScrollArea(this);
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
    contenuto->setFrameShape(QFrame::NoFrame);

    lay->addWidget(contenuto,1);
}

void GestioneProfGroupBox::reloadWindow()
{
    vector<string> temp = ctrl->giveProfNU();
    if(temp.size() != prof.size())
        prof = temp;
    totPage = prof.size() / maxPerPage;
    if(prof.size() % maxPerPage > 0 || totPage == 0)
        ++totPage;
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
}

void GestioneProfGroupBox::viewInfoImpiegato(const QString &nomeUtente) const
{
    const filexml& file = ctrl->giveSchedaPersonaleProf(nomeUtente);
    const QString& cogn = QString::fromStdString(file.daiTestoIn("Cognome"));
    const QString& nome = QString::fromStdString(file.daiTestoIn("Nome"));
    int materie = file.totNodi("materia");
    int matClassi = file.totNodi("materia:classe");

    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);

    popUpDialog temp(1,materie+matClassi+8);
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

    tit = new QLabel("Materie insegnate:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    for(int i = 0; i < materie; ++i){
        const QString& mat = QString::fromStdString(file.daiTestoIn("materia",i));
        tit = new QLabel(mat,&temp);
        tit->setFont(f2);
        temp.push_back_Widget(tit);

    }

    tit = new QLabel("Materia:Classe",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);
    for(int i = 0; i < matClassi; ++i){
        const QString& matc = QString::fromStdString(file.daiTestoIn("materia:classe",i));
        tit = new QLabel(matc,&temp);
        tit->setFont(f2);
        temp.push_back_Widget(tit);
    }

    temp.setFixedSize(500,500);

    temp.exec();




}

void GestioneProfGroupBox::rimuoviImpiegato(const QString &nomeUtente)
{
    QString ris = ctrl->rimuoviProf(nomeUtente);
    if(ris != "")
        QMessageBox::information(0,"Errore", ris);
    else{
        QMessageBox::information(0,"", "Professore rimosso");
        reloadWindow();
    }
}

void GestioneProfGroupBox::CercaImpiegato()
{
        prof = ctrl->giveProfNU();
        const string& parola = searchBox->text().toStdString();
        for(unsigned int i = 0; i<prof.size(); ++i){
            filexml f = ctrl->giveSchedaPersonaleProf(QString::fromStdString(prof[i]));
            if(f.daiTextContainingText("DatiOccupazione",parola).size() == 0){
                prof.erase(prof.begin()+i);
                --i;
            }
        }
        totPage = prof.size() / maxPerPage;
        if(prof.size() % maxPerPage > 0 || totPage == 0)
            ++totPage;
        contenuto->setWidget(loadPage(0));
        contenuto->setWidgetResizable(true);
}

