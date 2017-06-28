#include "editremovestud.h"
#include "../../../Controller/controllersegretario.h"
#include "buttongeststud.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>

int EditRemoveStud::maxPerPage = 8;
QGroupBox *EditRemoveStud::loadPage(int indice)
{

    QGroupBox* temp = new QGroupBox;

    QGridLayout* p = new QGridLayout(temp);
    temp->setLayout(p);
    QFont f("Times", 16);
    f.setBold(true);
    QLabel* title = new QLabel("Tutti gli studenti", temp);
    title->setFont(f);
    p->addWidget(title,0,0);

    int tot = matricola.size();

    f = QFont("Times", 14);
    f.setBold(true);

    title = new QLabel("Matricola", temp);
    title->setFont(f);
    p->addWidget(title,1,0);

    title = new QLabel("Nome", temp);
    title->setFont(f);
    p->addWidget(title,1,1);

    title = new QLabel("Cognome", temp);
    title->setFont(f);
    p->addWidget(title,1,2);

    title = new QLabel("Classe", temp);
    title->setFont(f);
    p->addWidget(title,1,3);

    f = QFont("Times", 14);
    f.setUnderline(true);
    title = new QLabel(QString::number(tot)+" studenti trovati", temp);
    title->setFont(f);
    p->addWidget(title,2,0);

    if(tot > indice){
    int row = 3;
    f = QFont("Times", 12);
    int i = indice;
    for(; i < tot && i < currPage*maxPerPage; ++i){

        title = new QLabel(QString::fromStdString(matricola[i]), temp);
        title->setFont(f);
        p->addWidget(title,row,0,1,1,Qt::AlignTop);

        title = new QLabel(QString::fromStdString(nome[i]), temp);
        title->setFont(f);
        p->addWidget(title,row,1,1,1,Qt::AlignTop);

        title = new QLabel(QString::fromStdString(cognome[i]), temp);
        title->setFont(f);
        p->addWidget(title,row,2,1,1,Qt::AlignTop);

        title = new QLabel(QString::fromStdString(classe[i]), temp);
        title->setFont(f);
        p->addWidget(title,row,3,1,1,Qt::AlignTop);

        buttonGestStud* b = new buttonGestStud("Info",QString::fromStdString(matricola[i]),this);
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfo()));
        p->addWidget(b,row,4,1,1,Qt::AlignTop);

        b = new buttonGestStud("Modifica info",QString::fromStdString(matricola[i]),this);
        connect(b,SIGNAL(clicked(bool)),b,SLOT(editStud()));
        p->addWidget(b,row,5,1,1,Qt::AlignTop);

        b = new buttonGestStud("Rimuovi studente",QString::fromStdString(matricola[i]),this);
        connect(b,SIGNAL(clicked(bool)),b,SLOT(removeStud()));
        p->addWidget(b,row,6,1,1,Qt::AlignTop);

        ++row;
    }

    QLabel* lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
    lab->setFont(f);
    p->addWidget(lab,row+2,2,1,1,Qt::AlignHCenter);
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
        p->addWidget(b,row+2,0,1,1,Qt::AlignLeft);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
    }

    if(i < tot){
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
        p->addWidget(b2,row+2,5,1,1,Qt::AlignRight);
    }
    }

p->setContentsMargins(10,0,10,0);

    return temp;
}


EditRemoveStud::EditRemoveStud(ControllerSegretario *ptr,QWidget* parent):FinestreSegretari(ptr,parent),cerca(new QLineEdit(this)),
    sc(0), lay(new QVBoxLayout(this)), totPage(1), currPage(1)
{
    Header();
    BodyAndFooter();
    setStyleSheet("background-color: none;");
    setLayout(lay);
}

void EditRemoveStud::reloadWindow()
{
    cercaStud();
}

void EditRemoveStud::Header()
{
    QGroupBox* temp = new QGroupBox(this);
    setWindowTitle(tr("Modifica/Rimuovi Studente"));

    QPushButton* indietro = new QPushButton("Torna indietro",this);
    indietro->setFixedSize(200, 40);
    indietro->setFont(QFont("Times",12));
    indietro->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    indietro->setCursor(QCursor(Qt::PointingHandCursor));
    connect(indietro,SIGNAL(clicked(bool)),this,SLOT(TornaIndietro()));

    QLabel* title = new QLabel("Cerca uno studente:", temp);
    title->setFont(QFont("Times", 13));
    QFont f("Times", 10);
    cerca->setMaxLength(40);
    cerca->setFixedSize(500,40);
    cerca->setPlaceholderText("nome, cognome, nome utente dello studente...");
    cerca->setFont(f);
    QPushButton* search = new QPushButton("Cerca", temp);
    search->setFont(f);
    search->setFixedHeight(40);
    connect(search,SIGNAL(clicked(bool)),this,SLOT(cercaStud()));

    QGridLayout* p = new QGridLayout(temp);
      temp->setLayout(p);
    p->addWidget(indietro,0,0);
    p->addWidget(title,1,1,1,1,Qt::AlignRight);
    p->addWidget(cerca,2,1,1,1,Qt::AlignRight);
    p->addWidget(search, 3,1,1,1,Qt::AlignRight);

    temp->setFixedHeight(200);
    lay->addWidget(temp,0);


}

void EditRemoveStud::BodyAndFooter()
{
    getController()->TuttiGliStudenti(matricola,nomeUtente,cognome,nome,classe);

    currPage = 1;
    int tot = matricola.size();
    totPage = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++ totPage;


    sc = new QScrollArea(this);
    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
    lay->addWidget(sc,1);

}

void EditRemoveStud::cercaStud(const QString &key)
{
    cerca->setText(key);
    cercaStud();
}

void EditRemoveStud::cercaStud()
{
    const QString& key = cerca->text();
    classe.clear();
    nome.clear();
    cognome.clear();
    nomeUtente.clear();
    matricola.clear();
        getController()->TuttiGliStudenti(matricola,nomeUtente,cognome,nome,classe);
    if(key != ""){
        vector<string>::iterator it1 = matricola.begin();
       vector<string>::iterator it2 = nomeUtente.begin();
       vector<string>::iterator it3 = cognome.begin();
       vector<string>::iterator it4 = nome.begin();
       vector<string>::iterator it5 = classe.begin();
        for(; it1 != matricola.end(); ++it1){
            const QString& matr = QString::fromStdString(*it1);
            const QString& nu = QString::fromStdString(*it2);
            const QString& co = QString::fromStdString(*it3);
            const QString& nom = QString::fromStdString(*it4);
            const QString& cla = QString::fromStdString(*it5);
            if(matr.indexOf(key,0, Qt::CaseInsensitive) != -1 ||
               nu.indexOf(key,0, Qt::CaseInsensitive) != -1 ||
               co.indexOf(key,0, Qt::CaseInsensitive) != -1 ||
               nom.indexOf(key,0, Qt::CaseInsensitive) != -1 ||
               cla.indexOf(key,0, Qt::CaseInsensitive) != -1){

                ++it2;
                ++it3;
                ++it4;
                ++it5;
            }
            else{
                matricola.erase(it1);
                nomeUtente.erase(it2);
                cognome.erase(it3);
                nome.erase(it4);
                classe.erase(it5);
                --it1;

            }
        }
}
    int tot = matricola.size();
    totPage = tot / maxPerPage;
    if(tot % maxPerPage > 0 || tot == 0)
        ++ totPage;
    currPage = 1;
    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
}

void EditRemoveStud::goNext()
{
    if(currPage < totPage){
       ++currPage;
        sc->setWidget(loadPage((currPage-1) * maxPerPage));
    }
}

void EditRemoveStud::goPrev()
{
    if(currPage > 1){
       --currPage;
        sc->setWidget(loadPage((currPage-1) * maxPerPage));
    }
}
