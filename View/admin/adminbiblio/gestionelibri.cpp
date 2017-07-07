#include "gestionelibri.h"
#include "buttonadminbiblio.h"
#include "finestreadminbiblio.h"
#include "../../../Controller/controlleradminbiblio.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>

GestioneLibri::GestioneLibri(ControllerAdminBiblio *ptr, FinestreAdminBiblio *parent) : SearchResultLibri(ptr,parent), contenuto(0),
    fi(parent), ctrl(ptr), currPage(1), totPage(1), lay(0)
{
    Header();
    lay = giveLayout();
    BodyAndFooter();
}

void GestioneLibri::reloadWindow()
{
    SortCan();
    vector<string> v = daiCodiciLibri();
    currPage = 1;
    totPage = v.size() / maxPerPage;
    if(v.size() % maxPerPage != 0 || totPage == 0)
        ++totPage;
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
}


void GestioneLibri::BodyAndFooter()
{
    if(!contenuto)
        contenuto = new QScrollArea(this);
    vector<string> v = daiCodiciLibri();
    currPage = 1;
    totPage = v.size() / maxPerPage;
    if(v.size() % maxPerPage != 0 || totPage == 0)
        ++totPage;
    contenuto->setWidget(loadPage(0));
    contenuto->setWidgetResizable(true);
    lay->addWidget(contenuto);
}

QGroupBox *GestioneLibri::loadPage(int indice)
{
    setWindowTitle("Gestione libri biblioteca");

    QGroupBox* content = new QGroupBox;
    content->setStyleSheet("QGroupBox{border: 0;}");

    QGridLayout* temp = new QGridLayout(content);
    content->setLayout(temp);

    QLabel* title = new QLabel("GESTIONE LIBRI", content);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid;"
                         "border-radius: 0;}");

    QFont t("Times", 13);
    t.setBold(true);
    title->setFont(t);

    temp->addWidget(title,0,0,1,6);


    QFont f("Times", 11);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Titolo", content);
    lab->setFont(f);
    temp->addWidget(lab,2,0,1,1,Qt::AlignTop);

    vector<string> l = daiCodiciLibri();
    int tot = l.size();
    if(tot > indice){

        lab = new QLabel(QString::number(l.size())+" Risultati", content);
        lab->setFont(f);
        temp->addWidget(lab,1,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 10);
        int row = 4;
        int it = indice;
        for(; it < tot && it < maxPerPage*currPage; ++it){

            const QString& libr = QString::fromStdString(l[it]);

            lab = new QLabel(ctrl->daiTitoloLibro(libr), content);
            lab->setFont(f);
            lab->setFixedWidth(230);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            buttonAdminBiblio* b = new buttonAdminBiblio("Leggi", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));
            temp->addWidget(b,row,1,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Info libro", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
            temp->addWidget(b,row,2,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Metti in primo piano", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(150,30);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(addToPrimoPiano()));
            temp->addWidget(b,row,3,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Modifica info libro", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(150,30);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(editBook()));
            temp->addWidget(b,row,4,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Elimina", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: #990000;"
                             "color: white;"
                             " border-radius: 5px;}"
                             "QPushButton:pressed {"
                             " background-color:#660000;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimLibro()));
            temp->addWidget(b,row,5,1,1,Qt::AlignTop);

            ++row;
        }

        QGroupBox* footer = new QGroupBox(content);
        footer->setStyleSheet("QGroupBox{border: 0;}");
        QGridLayout* footerLay = new QGridLayout(footer);
        footer->setLayout(footerLay);

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        footerLay->addWidget(lab,0,1,1,1,Qt::AlignHCenter);
        footerLay->setColumnStretch(0,1);
        footerLay->setColumnStretch(2,1);

        QIcon i1;
        if(indice > 0){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(content);
            b->setIcon(i1);
            b->setFixedSize(90,30);
            b->setIconSize(QSize(90,30));
            b->setCursor(QCursor(Qt::PointingHandCursor));
            footerLay->addWidget(b,0,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(it < tot){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(content);
            b2->setIcon(i1);
            b2->setFixedSize(90,30);
            b2->setIconSize(QSize(90,30));
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            footerLay->addWidget(b2,0,2,1,1,Qt::AlignRight);
        }

        temp->addWidget(footer,maxPerPage+4,0,1,6);

    }
    else{
        lab = new QLabel("0 libri trovati", content);
        lab->setFont(f);
        temp->addWidget(lab,3,0,1,1,Qt::AlignCenter);
    }

    return content;
}

void GestioneLibri::goNext()
{
    currPage++;
    contenuto->setWidget(loadPage((currPage-1)*maxPerPage));
    contenuto->setWidgetResizable(true);
}

void GestioneLibri::goPrev()
{
    if(currPage > 1){
        currPage--;
        contenuto->setWidget(loadPage((currPage-1)*maxPerPage));
        contenuto->setWidgetResizable(true);
    }
}

