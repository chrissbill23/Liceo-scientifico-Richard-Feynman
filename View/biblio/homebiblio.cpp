#include "homebiblio.h"
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include "primopianowidg.h"



void HomeBiblio::InsertInNav()
{
    QFont f("Times", 11);

    QGridLayout* temp = new QGridLayout(nav);

    QPushButton* b1 = new QPushButton("Categorie",nav);
    b1->setFixedHeight(40);
    b1->setFont(f);
    b1->setStyleSheet("QPushButton{"
                              "background-color: #29abe2; "
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                             " background-color:#003300;}");
    b1->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(AllCathegories()));
    temp->addWidget(b1,0,0,Qt::AlignTop);


    searchBox = new QLineEdit(nav);
    searchBox->setMaxLength(18);
    searchBox->setPlaceholderText("Inserisci titolo, autore ...");
    searchBox-> setStyleSheet("background-color: white; "
                              "border-radius: 5px;"
                              "color: black;"
                              "background-color:#f2f2f2;"
                              "padding-left: 0.5em;");
    searchBox->setFixedSize(300,40);
    searchBox->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    searchBox->setFont(f);
    temp->addWidget(searchBox,0,1,Qt::AlignTop);

    b1 = new QPushButton("Cerca libro", nav);
    b1->setFixedSize(200, 40);
    b1->setFont(f);
    b1->setStyleSheet("QPushButton{"
                              "background-color: #29abe2; "
                              "border-radius: 5px 5px 5px 5px; "
                              "color: white;}"
                              "QPushButton:pressed {"
                             " background-color:#003300;}");
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
    p->addWidget(nav,2,0,1,4);

    if(PrimoPiano)
        delete PrimoPiano;
    PrimoPiano = new PrimoPianoWidg(getController(),this);
    p->addWidget(PrimoPiano,3,0,1,4,Qt::AlignTop);

}

void HomeBiblio::Header()
{
    FinestreBiblioteca::Header();

    QGridLayout* p = giveLayout();
    if(!p){
        p = new QGridLayout(this);
        setLayout(p);
    }

    QLabel* label = new QLabel(this);
    label->setFixedSize(1100,200);
    label->setStyleSheet("color: #29abe2;");
    const QString& temp = getController()->ShowLogoBiblio();
    label->setPixmap(QPixmap(temp).scaled(QSize(label->width(), label->height())));
    p->addWidget(label,1,0,1,4, Qt::AlignCenter|Qt::AlignTop);

}

void HomeBiblio::SearchBookResult() const
{
    SearchBook(searchBox->text());
}
