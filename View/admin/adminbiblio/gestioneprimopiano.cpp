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
    QFont t("Times", 13);
    t.setBold(true);
    title->setFont(t);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid;"
                         "border-radius: 0;}");

    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,6);


    QFont f("Times", 11);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Titolo", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,2,0,1,1,Qt::AlignTop);


    vector<string> v = getController()->codiciLibriPrimoPiano();
    if(v.size() > 0){

        lab = new QLabel(QString::number(v.size())+" Libri in primo piano", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,1,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 10);
        int row = 3;
        for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it){
            const QString& libr = QString::fromStdString(*it);
            lab = new QLabel(getController()->daiTitoloLibro(libr), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop|Qt::AlignLeft);

            buttonAdminBiblio* b = new buttonAdminBiblio("Rimuovi", QString::fromStdString(*it),false,"",this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: #990000;"
                             "color: white;"
                             " border-radius: 5px;}"
                             "QPushButton:pressed {"
                             " background-color:#660000;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimDaPrimoPiano()));
            temp->addWidget(b,row,1,1,1,Qt::AlignTop);

            ++row;
        }
        temp->setRowStretch(row+1,1);
    }
    else{
        lab = new QLabel("Non ci sono ancora libri in primo piano", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }

    lay->addWidget(contenuto);
}
