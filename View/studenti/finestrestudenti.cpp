#include "finestrestudenti.h"
#include "viewcompitistud.h"
#include "../buttongroup.h"
#include <QGridLayout>

FinestreStudenti::FinestreStudenti(ControllerStud *c, QWidget *parent):Finestre(c, parent), p(0), ctrl(c){
    setStyleSheet(" background-color: #29abe2");
}

QGridLayout *FinestreStudenti::giveLayout() const
{
    return p;
}

ControllerStud *FinestreStudenti::getController() const
{
    return ctrl;
}

void FinestreStudenti::vediCompiti() const
{
    ctrl->ShowNewWindow(new ViewCompitiStud(ctrl));
}

void FinestreStudenti::HomePageGroup()
{
    QObject* o = sender();

    buttonGroup* b = dynamic_cast<buttonGroup*>(o);
    if(b){
        ctrl->HomePageGroup(b->giveGroupName());
    }
}
void FinestreStudenti::Header()
{
    QFont f("Times", 11);
    if(p)
        delete p;
    p = new QGridLayout(this);
    QPushButton* biblio = new QPushButton("Visita la Biblioteca", this);
    biblio->setFixedSize(200, 40);
    biblio->setFont(f);
    biblio->setStyleSheet("QPushButton{"
                          "background-color: green; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    biblio->setCursor(QCursor(Qt::PointingHandCursor));
    QPushButton* logout= new QPushButton("logout", this);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(biblio,SIGNAL(clicked()), this, SLOT(HomePageBiblio()));
    connect(logout,SIGNAL(clicked()), this, SLOT(signout()));
    p->addWidget(biblio, 0, 3);
    p->addWidget(logout, 0, 4);
    setLayout(p);
}
