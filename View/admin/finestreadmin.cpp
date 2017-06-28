#include "finestreadmin.h"
#include <QGridLayout>
#include <QPushButton>

finestreAdmin::finestreAdmin(ControllerAdmin* ptr, QWidget *parent):Finestre(ptr, parent), ctrl(ptr), p(0)
{

}

QGridLayout *finestreAdmin::giveLayout() const
{
    return p;
}

ControllerAdmin *finestreAdmin::getController() const
{
    return ctrl;
}

void finestreAdmin::Header()
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
    connect(biblio,SIGNAL(clicked(bool)),this,SLOT(HomePageBiblio()));

    QPushButton* logout = new QPushButton("logout", this);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(logout,SIGNAL(clicked()), this, SLOT(signout()));

    p->addWidget(biblio, 0, 3);
    p->addWidget(logout, 0, 4);
    setLayout(p);

}
