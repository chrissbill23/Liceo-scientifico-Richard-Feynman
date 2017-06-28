#include "gestclassi.h"
#include "buttongestclassi.h"
#include "../../popupdialog.h"
#include "../../../Modello/filexml.h"
#include <QGroupBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>

void GestClassi::InsertInComboBoxes()
{


    if(classi->count() <= 0){
    classi->addItem("Seleziona la classe",0);
    classi->addItem("le prime",1);
    classi->addItem("le seconde",2);
    classi->addItem("le terze",3);
    classi->addItem("le quarte",4);
    classi->addItem("le quinte",5);
    }

    list<string> sess = ctrl->daiSessioniClassi();
    int size = sess.size();
    if(size != sessioni->count() - 1){
    sessioni->blockSignals(true);
    sessioni->clear();
    sessioni->addItem("Seleziona la sessione", 0);
    for(list<string>::const_iterator it = sess.begin(); it != sess.end(); ++it){
        const QString& sect = QString::fromStdString(*it);
        sessioni->addItem(sect,sect);
    }
    sessioni->blockSignals(false);
   }


    list<string> indir = ctrl->daiIndirizzoClassi();
    size = indir.size();
    if( size != indirizzi->count() - 1){
    indirizzi->blockSignals(true);
    indirizzi->clear();
    indirizzi->addItem("Seleziona l'indirizzo", 0);
    for(list<string>::const_iterator it = indir.begin(); it != indir.end(); ++it){
        const QString& sect = QString::fromStdString(*it);
        indirizzi->addItem(sect,sect);
    }
    indirizzi->blockSignals(false);
   }
}

QWidget *GestClassi::loadPage(int)
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* p = new QGridLayout(temp);

    temp->setLayout(p);

    QFont f("Times", 14);
    f.setBold(true);

    QLabel* lab = new QLabel("Classe",temp);
    lab->setFont(f);
    p->addWidget(lab,0,0,1,1,Qt::AlignTop);

    int tot = classes.size();

    lab = new QLabel(QString::number(tot)+" classi trovate",temp);
    lab->setFont(QFont("Times",12));
    p->addWidget(lab,1,0,1,1,Qt::AlignTop);

    f = QFont("Times",12);
    for(int i = 0; i < tot; ++i){
        const QString& cl = QString::fromStdString(classes[i]);
        lab = new QLabel(cl,temp);
        lab->setFont(f);
        p->addWidget(lab,i+2,0,1,1,Qt::AlignTop);

        buttonGestClassi* b = new buttonGestClassi("Info",cl,this);
        connect(b,SIGNAL(clicked(bool)),b, SLOT(viewInfoClasse()));
        p->addWidget(b,i+2,1,1,1,Qt::AlignTop);

        b = new buttonGestClassi("Rimuovi classe",cl,this);
        connect(b,SIGNAL(clicked(bool)),b, SLOT(removeClass()));
        p->addWidget(b,i+2,2,1,1,Qt::AlignTop);
    }

    return temp;
}

GestClassi::GestClassi(ControllerPreside *c, QWidget *parent):FinestrePreside(c, parent), ctrl(c), body(0),
    classi(0), sessioni(0), indirizzi(0), lay(0)
{
    Header();
    BodyAndFooter();
    setStyleSheet("background-color: none");
}

void GestClassi::Header()
{
    QGroupBox* head = new QGroupBox(this);
    QGridLayout* p = new QGridLayout(head);

    head->setLayout(p);

    QFont f("Times",14);
    QPushButton* previousWindow = new QPushButton("Torna Indietro", head);
    previousWindow->setFixedSize(200, 40);
    previousWindow->setFont(f);
    previousWindow->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    previousWindow->setCursor(QCursor(Qt::PointingHandCursor));
    connect(previousWindow,SIGNAL(clicked(bool)),this,SLOT(TornaIndietro()));

    p->addWidget(previousWindow,0,0,1,1,Qt::AlignLeft);

    QPushButton* logout = new QPushButton("logout", head);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(logout,SIGNAL(clicked(bool)),this,SLOT(signout()));

    p->addWidget(logout,0,6,1,1,Qt::AlignRight);

    classi = new QComboBox(head);
    sessioni = new QComboBox(head);
    indirizzi = new QComboBox(head);
    classi->setFixedSize(300,30);
    sessioni->setFixedSize(300,30);
    indirizzi->setFixedSize(300,30);
    InsertInComboBoxes();


    connect(classi,SIGNAL(currentIndexChanged(int)),this,SLOT(cercaClasse()));
    connect(sessioni,SIGNAL(currentIndexChanged(int)),this,SLOT(cercaClasse()));
    connect(indirizzi,SIGNAL(currentIndexChanged(int)),this,SLOT(cercaClasse()));

    p->addWidget(classi, 4,1,1,1,Qt::AlignLeft);
    p->addWidget(sessioni, 4,2,1,1,Qt::AlignLeft);
    p->addWidget(indirizzi, 4,3,1,1,Qt::AlignLeft);

    QPushButton* b = new QPushButton("Aggiungi nuova classe",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiClasse()));
    p->addWidget(b,1,0,1,1,Qt::AlignLeft);

    b = new QPushButton("Aggiungi nuova sessione",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiSessClasse()));
    p->addWidget(b,2,0,1,1,Qt::AlignLeft);
    b = new QPushButton("Rimuovi sessione",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rimuoviSessione()));
    p->addWidget(b,2,1,1,1,Qt::AlignLeft);

    b = new QPushButton("Aggiungi nuovo indirizzo",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiIndirClasse()));
    p->addWidget(b,3,0,1,1,Qt::AlignLeft);
    b = new QPushButton("Rimuovi indirizzo",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rimuoviIndirizzo()));
    p->addWidget(b,3,1,1,1,Qt::AlignLeft);

    b = new QPushButton("Tutte le materie",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(viewMaterieInsegnate()));
    p->addWidget(b,1,6,1,1,Qt::AlignLeft);
    b = new QPushButton("Aggiungi nuova materia",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiMateria()));
    p->addWidget(b,2,6,1,1,Qt::AlignLeft);
    b = new QPushButton("Rimuovi materia",this);
    b->setFixedSize(200,30);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rimuoviMateria()));
    p->addWidget(b,3,6,1,1,Qt::AlignLeft);


    if(!lay)
        lay = new QVBoxLayout(this);
    lay->addWidget(head,0, Qt::AlignTop);
}

void GestClassi::BodyAndFooter()
{
    classes = ctrl->Classi();
    body = new QScrollArea(this);
    body->setWidget(loadPage(0));
    body->setWidgetResizable(true);
    lay->addWidget(body,1);
}

void GestClassi::reloadWindow()
{
    classes = ctrl->Classi();

    InsertInComboBoxes();
    body->setWidget(loadPage(0));
    body->setWidgetResizable(true);
}

void GestClassi::viewInfoClasse(const QString &classe) const
{
    const filexml& file = ctrl->giveSchedaClasse(classe);
    const QString& nome = QString::fromStdString(file.daiTestoIn("nomeClasse"));
    int materie = file.totNodi("materia");
    int alun = file.totNodi("NomeUtente");

    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);

    popUpDialog temp(1,materie+5);
    QLabel* tit = new QLabel("Nome classe:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(nome,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    tit = new QLabel("Totale alunni:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(QString::number(alun),&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    tit = new QLabel("Materie insegnate:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    for(int i = 0; i < materie; ++i){
        const QString& mat = QString::fromStdString(file.daiTestoIn("NomeMateria",i));
        const QString& prof = QString::fromStdString(file.daiTestoIn("Professore",i));
        const QString& nomeProf = ctrl->daiNomeProf(prof);
        const QString& cognProf = ctrl->daiCognomeProf(prof);
        tit = new QLabel(mat+":  insegnato da   "+cognProf+" "+nomeProf,&temp);
        tit->setFont(f2);
        temp.push_back_Widget(tit);

    }

    temp.setFixedSize(600,700);
    temp.setWindowTitle("Scheda classe "+classe);

    temp.exec();
}

void GestClassi::cercaClasse()
{

    classes = ctrl->Classi();

        if(classi->currentIndex() > 0){
            const QString& index = classi->itemData(classi->currentIndex()).toString();
           for(unsigned int i = 0; i < classes.size(); ++i){
               const QString& cla = QString::fromStdString(classes[i]);
               if(cla.left(1) != index){
                   classes.erase(classes.begin()+i);
                   --i;
               }
           }
        }

        if(sessioni->currentIndex() > 0){
            const QString& key = sessioni->itemData(sessioni->currentIndex()).toString();
            for(unsigned int i = 0; i < classes.size(); ++i){
                filexml f = ctrl->giveSchedaClasse(QString::fromStdString(classes[i]));
                if(f.daiTextContainingText("sessione",key.toStdString()).size() == 0){
                    classes.erase(classes.begin()+i);
                    --i;
                }
            }
        }

        if(indirizzi->currentIndex() > 0){
            const QString& key = indirizzi->itemData(indirizzi->currentIndex()).toString();
            for(unsigned int i = 0; i < classes.size(); ++i){
                filexml f = ctrl->giveSchedaClasse(QString::fromStdString(classes[i]));
                if(f.daiTextContainingText("indirizzo",key.toStdString()).size() == 0){
                    classes.erase(classes.begin()+i);
                    --i;
                }
            }
        }
        InsertInComboBoxes();
        body->setWidget(loadPage(0));
        body->setWidgetResizable(true);
}
