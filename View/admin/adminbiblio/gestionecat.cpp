#include "gestionecat.h"
#include "buttonadminbiblio.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>


GestioneCat::GestioneCat(ControllerAdminBiblio *ptr, QWidget *parent): FinestreAdminBiblio(ptr,parent), contenuto(0),
lay(new QVBoxLayout(this))
{
    BodyAndFooter();
    setLayout(lay);
}

void GestioneCat::reloadWindow()
{
    BodyAndFooter();
}

void GestioneCat::BodyAndFooter()
{
    setWindowTitle("Gestione categorie");

    if(contenuto)
        delete contenuto;
    contenuto = new QGroupBox(this);

    QGridLayout* temp = new QGridLayout(contenuto);
    contenuto->setLayout(temp);

    QLabel* title = new QLabel("GESTIONE CATEGORIE", contenuto);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-radius: 0;}");
    QFont t("Times", 16);
    t.setBold(true);
    title->setFont(t);
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,4);


    QFont f("Times", 14);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Nome categoria", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,0,1,1,Qt::AlignTop);


    vector<string> l = getController()->CategorieBiblio();
    if(l.size() > 0){

        lab = new QLabel(QString::number(l.size())+" Risultati", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 13);
        f.setBold(true);
        int row = 4;
        for(vector<string>::const_iterator it = l.begin(); it != l.end(); ++it){

            lab = new QLabel(QString::fromStdString(*it), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            buttonAdminBiblio* b = new buttonAdminBiblio("vedi libri", "",true, QString::fromStdString(*it),this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibriInCat()));
            temp->addWidget(b,row,1,1,1,Qt::AlignTop);
            if(*it != "Non specificato"){
            b = new buttonAdminBiblio("Elimina categoria", "",true, QString::fromStdString(*it),this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(200,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimCat()));

            temp->addWidget(b,row,2,1,1,Qt::AlignTop);
            }

            ++row;
        }
    }
    else{
        lab = new QLabel("0 categorie create", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }

    lay->addWidget(contenuto);
}
