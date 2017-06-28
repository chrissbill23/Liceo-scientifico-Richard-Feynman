#include "gestioneprimopiano.h"
#include "buttonadminbiblio.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>

GestionePrimoPiano::GestionePrimoPiano(ControllerAdminBiblio *ptr, QWidget *parent): FinestreAdminBiblio(ptr,parent), contenuto(0),
    lay(new QVBoxLayout(this))
{
    BodyAndFooter();
    setLayout(lay);
}

void GestionePrimoPiano::reloadWindow()
{
    BodyAndFooter();
}

void GestionePrimoPiano::BodyAndFooter()
{
    setWindowTitle("Libri in primo piano");

    if(contenuto)
        delete contenuto;
    contenuto = new QGroupBox(this);

    QGridLayout* temp = new QGridLayout(contenuto);
    contenuto->setLayout(temp);

    QLabel* title = new QLabel("LIBRI PRIMO PIANO", contenuto);
    QFont t("Times", 16);
    t.setBold(true);
    title->setFont(t);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid white;"
                         "border-radius: 0;}");

    title->setFont(QFont("Times", 15));
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,4);
    temp->addWidget(new QLabel("Per aggiungere un libro, deve andare \nin Gestione libri e scegliere il libro"),1,0);


    QFont f("Times", 14);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Codice Libro", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,0,1,1,Qt::AlignTop);

    lab = new QLabel("Titolo", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,1,1,1,Qt::AlignTop);

    lab = new QLabel("Autore", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,2,1,1,Qt::AlignTop);

    lab = new QLabel("Anno Edizione", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,3,1,1,Qt::AlignTop);


    vector<string> v = getController()->codiciLibriPrimoPiano();
    ControllerAdminBiblio* ctrl = getController();
    if(v.size() > 0){

        lab = new QLabel(QString::number(v.size())+" Libri in primo piano", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 13);
        f.setBold(true);
        int row = 4;
        for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
            const QString& libr = QString::fromStdString(*it);
            lab = new QLabel(libr, contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiTitoloLibro(libr), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,1,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAutoreLibro(libr), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,2,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAnnoEdizioneLibro(libr), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,3,1,1,Qt::AlignTop);

            buttonAdminBiblio* b = new buttonAdminBiblio("vedi libro", QString::fromStdString(*it),false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));
            temp->addWidget(b,row,4,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("info libro", QString::fromStdString(*it),false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
            temp->addWidget(b,row,5,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("modifica info libro", QString::fromStdString(*it),false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(200,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(editBook()));
            temp->addWidget(b,row,6,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Rimuovi da primo piano", QString::fromStdString(*it),false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(200,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimDaPrimoPiano()));
            temp->addWidget(b,row,7,1,1,Qt::AlignTop);

            ++row;
        }
    }
    else{
        lab = new QLabel("Non ci sono ancora libri in primo piano", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }

    lay->addWidget(contenuto);
}
