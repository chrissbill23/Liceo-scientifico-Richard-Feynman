#include "searchview.h"
#include "finestre.h"
#include <QLineEdit>
#include <QGridLayout>

SearchView::SearchView(Finestre *parent): QWidget(parent),searchBox(0), researcher(parent){}

QString SearchView::giveTextSearch() const
{
    return searchBox->text();
}

void SearchView::Header(QBoxLayout * lay2)
{
    searchBox=new QLineEdit(this);
    QHBoxLayout* lay = new QHBoxLayout;
    setWindowTitle("Risultati della ricerca");
    QPushButton* b= new QPushButton("Indietro");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFixedSize(300,40);
    b->setFont(QFont("Times", 13));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),researcher, SLOT(TornaIndietro()));
    lay->addWidget(b,1, Qt::AlignLeft);

    searchBox->setMaxLength(25);
    searchBox->setFont(QFont("Times",12));
    searchBox->setFixedSize(500,50);
    lay->addWidget(searchBox,0);

    b = new QPushButton("Cerca",this);
    b->setFixedSize(200,50);  
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(ShowResult()));
    lay->addWidget(b,1);

    lay2->addLayout(lay);
}
