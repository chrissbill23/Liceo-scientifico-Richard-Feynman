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
    QFont t("Times", 13);
    t.setBold(true);
    title->setFont(t);
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,3);


    QFont f("Times", 11);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = 0;


    vector<string> l = getController()->CategorieBiblio();
    if(l.size() > 0){

        lab = new QLabel(QString::number(l.size())+" Risultati", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 10);
        int row = 4;
        for(vector<string>::const_iterator it = l.begin(); it != l.end(); ++it){

            lab = new QLabel(QString::fromStdString(*it), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            buttonAdminBiblio* b = new buttonAdminBiblio("Libri", "",true, QString::fromStdString(*it),this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibriInCat()));
            temp->addWidget(b,row,1,1,1,Qt::AlignTop);
            if(*it != "Non specificato"){
            b = new buttonAdminBiblio("Elimina", "",true, QString::fromStdString(*it),this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: #990000;"
                             "color: white;"
                             " border-radius: 5px;}"
                             "QPushButton:pressed {"
                             " background-color:#660000;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimCat()));

            temp->addWidget(b,row,2,1,1,Qt::AlignTop);
            }

            ++row;
        }
        temp->setRowStretch(row,1);
    }
    else{
        lab = new QLabel("0 categorie create", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }

    lay->addWidget(contenuto);
}
