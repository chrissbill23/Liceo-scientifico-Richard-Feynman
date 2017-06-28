#include "compitiniwidgbox.h"
#include "finestreprof.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
CompitiniWidgBox::CompitiniWidgBox(FinestreProf *parent): QGroupBox(parent), fi(parent)
{
    QVBoxLayout* temp2 = new QVBoxLayout(this);
    QFont f("Times", 15);
    QLabel* title = new QLabel("Esercizi E Compiti", this);
    title->setStyleSheet("QLabel{"
                         " padding-bottom: 0.4em; "
                         "border-bottom: 2px solid #29abe2;"
                         "border-radius:0;}");

    title->setFont(f);
    title->setFixedHeight(50);
    temp2->addWidget(title);

    QPushButton* b = new QPushButton("Tutti i compiti/esercizi assegnati",this);
    b->setStyleSheet("QPushButton{"
                                "background-color: #29abe2;"
                                "border: 2px solid;"
                                "border-radius: 5px 5px 5px 5px; "
                                "color: white;}"
                                "QPushButton:pressed {"
                                "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),fi,SLOT(vediCompiti()));

    temp2->addWidget(b);

    b = new QPushButton("Aggiungi nuovo compito/esercizi",this);
    b->setStyleSheet("QPushButton{"
                            "background-color: #29abe2;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),fi,SLOT(CreateNewCompito()));

    temp2->addWidget(b);

    setLayout(temp2);


}
