#include "tuttelecategorie.h"
#include "bibliobutton.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QLineEdit>

int TutteleCategorie::maxPerPage = 10;
QGroupBox *TutteleCategorie::loadPage(int indice)
{
    QGroupBox* contenuto = new QGroupBox;

    QGridLayout* temp = new QGridLayout(contenuto);
    contenuto->setLayout(temp);

    QLabel* title = new QLabel("CATEGORIE", contenuto);
    title->setStyleSheet("QLabel{"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid;"
                         "border-radius: 0;}");

    title->setFont(QFont("Times", 14));
    title->setFixedHeight(50);

    temp->addWidget(title,0,0,1,3);


    QFont f("Times", 12);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Nome categoria", contenuto);
    lab->setFont(f);
    temp->addWidget(lab,3,0,1,1,Qt::AlignTop);

    int tot = categorie.size();
    if(tot > indice){

        lab = new QLabel(QString::number(categorie.size())+" Risultati", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,3,Qt::AlignTop);

        int row = 4;
        int it = indice;
        f = QFont("Times", 11);
        for(; it < tot && it < maxPerPage*currPage; ++it){

            lab = new QLabel(QString::fromStdString(categorie[it]), contenuto);
            lab->setFont(f);
            temp->addWidget(lab,row,0,1,1,Qt::AlignTop);

            bibliobutton* b = new bibliobutton("Libri di questa categoria", "",true, QString::fromStdString(categorie[it]),this);
            b->setFont(QFont("Times", 9));
            b->setFixedSize(220,35);
            b->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibriInCat()));
            temp->addWidget(b,row,1,1,1,Qt::AlignTop);

            ++row;
        }

        lab = new QLabel("pagina "+QString::number(currPage)+"/"+QString::number(totPage));
        lab->setFont(QFont("Times",9));
        temp->addWidget(lab,row+2,1,1,1,Qt::AlignHCenter);
        QIcon i1;
        if(indice > 0){
            i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
            QPushButton* b = new QPushButton(contenuto);
            b->setIcon(i1);
            b->setFixedSize(80,40);
            b->setIconSize(QSize(80,40));
            b->setCursor(QCursor(Qt::PointingHandCursor));
            temp->addWidget(b,row+2,0,1,1,Qt::AlignLeft);
            connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        }

        if(it < tot){
            i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
            QPushButton* b2 = new QPushButton(contenuto);
            b2->setIcon(i1);
            b2->setFixedSize(80,40);
            b2->setIconSize(QSize(80,40));
            b2->setCursor(QCursor(Qt::PointingHandCursor));
            connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
            temp->addWidget(b2,row+2,2,1,1,Qt::AlignRight);
        }



    }
    else{
        lab = new QLabel("0 categorie trovate", contenuto);
        lab->setFont(f);
        temp->addWidget(lab,2,0,1,1);
    }
    return contenuto;

}

TutteleCategorie::TutteleCategorie(Controller *c, QWidget *parent) : FinestreBiblioteca(c, parent), searchBox(0),currPage(1)
{
 categorie = c->CategorieBiblio();
 Header();
 BodyAndFooter();
 giveLayout()->addWidget(sc,2,0,1,4);
 setWindowTitle("Categorie");
}

void TutteleCategorie::reloadWindow()
{
    categorie = getController()->CategorieBiblio();
}

void TutteleCategorie::Header()
{
    FinestreBiblioteca::Header();

    searchBox = new QLineEdit(this);
    searchBox->setFixedSize(400,40);
    searchBox->setFont(QFont("Times",11));
    searchBox->setPlaceholderText("Che categoria cerchi?");
    searchBox->setStyleSheet("background-color: white;");

    giveLayout()->addWidget(searchBox,1,2);

    QPushButton* b = new QPushButton("Cerca",this);
    b->setFixedHeight(40);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(searchCategoria()));
    giveLayout()->addWidget(b,1,3);
}

void TutteleCategorie::BodyAndFooter()
{
    sc = new QScrollArea(this);

    currPage = 1;
    totPage = categorie.size() / maxPerPage;
    if(categorie.size() % maxPerPage != 0 || totPage == 0)
        ++totPage;

    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
    sc->setStyleSheet("QScrollArea{border: 0;}");


}

void TutteleCategorie::goNext()
{
    currPage++;
    sc->setWidget(loadPage((currPage-1)*maxPerPage));
    sc->setWidgetResizable(true);
}

void TutteleCategorie::goPrev()
{
    if(currPage > 1){
        currPage--;
        sc->setWidget(loadPage((currPage-1)*maxPerPage));
        sc->setWidgetResizable(true);
    }
}

void TutteleCategorie::searchCategoria()
{
    if(searchBox->text() == ""){
        categorie = getController()->CategorieBiblio();
    }
    else{
        const QString& key = searchBox->text();
        for(vector<string>::iterator it = categorie.begin(); it != categorie.end(); ++it){
            const QString& cat = QString::fromStdString(*it);
            if(cat.indexOf(key, 0,Qt::CaseInsensitive) == -1){
                categorie.erase(it);
                --it;
            }
        }
    }
    currPage = 1;
    totPage = categorie.size() / maxPerPage;
    if(categorie.size() % maxPerPage != 0 || totPage == 0)
        ++totPage;

    sc->setWidget(loadPage(0));
    sc->setWidgetResizable(true);
}
