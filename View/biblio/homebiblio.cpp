#include "homebiblio.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include "primopianowidg.h"



void HomeBiblio::InsertInNav()
{
    QFont f("Times", 9);

    QGridLayout* temp = new QGridLayout(nav);

    QPushButton* b1 = new QPushButton("Categorie",nav);
    b1->setFixedSize(150,40);
    b1->setFont(f);
    b1->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(AllCathegories()));
    temp->addWidget(b1,0,0,Qt::AlignTop|Qt::AlignRight);


    searchBox = new QLineEdit(nav);
    searchBox->setMaxLength(18);
    searchBox->setPlaceholderText("Titolo, Autore ...");
    searchBox-> setStyleSheet("background-color: white; "
                              "border: 2px solid;"
                              "border-radius: 5px;"
                              "color: black;"
                              "background-color:#f2f2f2;"
                              "padding-left: 0.5em;");
    searchBox->setFixedSize(300,40);
    searchBox->setFont(f);
    temp->addWidget(searchBox,0,1,Qt::AlignTop);

    b1 = new QPushButton("Cerca", nav);
    b1->setFixedSize(150, 40);
    b1->setFont(f);
    b1->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b1, SIGNAL(clicked(bool)), this,SLOT(SearchBookResult()));
    temp->addWidget(b1,0,3,Qt::AlignTop);

    nav->setLayout(temp);

}


HomeBiblio::HomeBiblio(Controller *u): FinestreBiblioteca(u), nav(0),
   PrimoPiano(0)
{

    Header();
    BodyAndFooter();
    setWindowTitle("Biblioteca");
}

void HomeBiblio::reloadWindow()
{
    BodyAndFooter();
}

void HomeBiblio::BodyAndFooter()
{

    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }
    if(nav)
        delete nav;
    nav = new QGroupBox(this);
    InsertInNav();

    nav->setStyleSheet("border: 0;");
    p->addWidget(nav,2,0,1,4,Qt::AlignTop);

    if(PrimoPiano)
        delete PrimoPiano;
    PrimoPiano = new PrimoPianoWidg(getController(),this);
    p->addWidget(PrimoPiano,3,0,1,4,Qt::AlignTop);
    p->setRowStretch(4,1);

}

void HomeBiblio::SearchBookResult() const
{
    SearchBook(searchBox->text());
}
