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

    QGridLayout* temp = new QGridLayout(content);
    content->setLayout(temp);

    QLabel* title = new QLabel("GESTIONE LIBRI", content);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid white;"
                         "border-radius: 0;}");

    QFont t("Times", 16);
    t.setBold(true);
    title->setFont(t);
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,9);


    QFont f("Times", 14);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Codice Libro", content);
    lab->setFont(f);
    temp->addWidget(lab,3,0,1,1,Qt::AlignTop);

    lab = new QLabel("Titolo", content);
    lab->setFont(f);
    temp->addWidget(lab,3,1,1,1,Qt::AlignTop);

    lab = new QLabel("Autore", content);
    lab->setFont(f);
    temp->addWidget(lab,3,2,1,1,Qt::AlignTop);

    lab = new QLabel("Anno Edizione", content);
    lab->setFont(f);
    temp->addWidget(lab,3,3,1,1,Qt::AlignTop);

    vector<string> l = daiCodiciLibri();
    int tot = l.size();
    if(tot > indice){

        lab = new QLabel(QString::number(l.size())+" Risultati", content);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,5,Qt::AlignTop);
        f = QFont ("Times", 13);
        f.setBold(true);
        int row = 4;
        int it = indice;
        for(; it < tot && it < maxPerPage*currPage; ++it){

            const QString& libr = QString::fromStdString(l[it]);
            lab = new QLabel(libr, content);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiTitoloLibro(libr), content);
            lab->setFont(f);
            temp->addWidget(lab,row,1,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAutoreLibro(libr), content);
            lab->setFont(f);
            temp->addWidget(lab,row,2,1,1,Qt::AlignTop);

            lab = new QLabel(ctrl->daiAnnoEdizioneLibro(libr), content);
            lab->setFont(f);
            temp->addWidget(lab,row,3,1,1,Qt::AlignTop);

            buttonAdminBiblio* b = new buttonAdminBiblio("vedi libro", QString::fromStdString(l[it]),false,"",fi);
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

            b = new buttonAdminBiblio("info libro", QString::fromStdString(l[it]),false,"",fi);
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

            b = new buttonAdminBiblio("aggiungi al primo piano", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(200,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(addToPrimoPiano()));
            temp->addWidget(b,row,6,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("modifica info libro", QString::fromStdString(l[it]),false,"",fi);
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
            temp->addWidget(b,row,7,1,1,Qt::AlignTop);

            b = new buttonAdminBiblio("Elimina libro", QString::fromStdString(l[it]),false,"",fi);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(100,30);
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            connect(b,SIGNAL(clicked(bool)),b,SLOT(elimLibro()));
            temp->addWidget(b,row,8,1,1,Qt::AlignTop);

            ++row;
        }

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(f);
        temp->addWidget(lab,maxPerPage+6,4,1,1,Qt::AlignHCenter);
        QIcon i1;
        if(indice > 0){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(content);
            b->setIcon(i1);
            b->setFixedSize(200,40);
            b->setIconSize(QSize(200,40));
            b->setStyleSheet("QPushButton{"
                             "background-color: green;"
                             "border: 2px solid;"
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                             "background-color:#003300;}");
            b->setCursor(QCursor(Qt::PointingHandCursor));
            temp->addWidget(b,maxPerPage+6,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(it < tot){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(content);
            b2->setIcon(i1);
            b2->setFixedSize(200,40);
            b2->setIconSize(QSize(200,40));
            b2->setStyleSheet("QPushButton{"
                              "background-color: green;"
                              "border: 2px solid;"
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                              "background-color:#003300;}");
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            temp->addWidget(b2,maxPerPage+6,8,1,1,Qt::AlignRight);
        }

    }
    else{
        lab = new QLabel("0 libri trovati", content);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
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

