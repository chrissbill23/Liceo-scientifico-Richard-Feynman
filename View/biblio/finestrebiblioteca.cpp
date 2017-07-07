#include "finestrebiblioteca.h"
#include "tuttelecategorie.h"
#include "searchresultlibri.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include "../../Controller/Controller.h"

FinestreBiblioteca::FinestreBiblioteca(Controller *u, QWidget *parent):Finestre(u, parent),
    logout(0),previousWindow(0),p(0){
    setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
}

void FinestreBiblioteca::Header()
{
    QFont f("Times", 11);
    if(p)
        delete p;
    p = new QGridLayout(this);
    if(previousWindow)
        delete previousWindow;
    if(logout)
        delete logout;
    logout = new QPushButton("logout", this);
    previousWindow = new QPushButton("Indietro", this);
    previousWindow->setFixedSize(150, 40);
    previousWindow->setFont(f);
    previousWindow->setStyleSheet("QPushButton{"
                          "background-color: #336699; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    previousWindow->setCursor(QCursor(Qt::PointingHandCursor));

    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);

    connect(logout,SIGNAL(clicked()), this, SLOT(signout()));
    connect(previousWindow,SIGNAL(clicked()), this, SLOT(TornaIndietro()));

    QGroupBox* temp2 = new QGroupBox(this);
    temp2->setStyleSheet("QGroupBox{border: 0;}");
    QHBoxLayout* tempL = new QHBoxLayout(temp2);
    temp2->setLayout(tempL);


    QLabel* Title = new QLabel(this);
    Title->setText(getController()->ShowNomeBiblio());
    Title->setFont(QFont("Times", 20));
    Title->setStyleSheet("color: #006600;");
    tempL->addWidget(Title,0);
    QLabel* logo = new QLabel(this);
    logo->setFixedSize(80,40);
    const QString& temp = getController()->ShowLogoBiblio();
    logo->setPixmap(QPixmap(temp).scaled(QSize(logo->width(), logo->height())));
    tempL->addWidget(logo,1);

    p->addWidget(logout, 0, 3);
    p->addWidget(previousWindow, 0, 0);
    p->addWidget(temp2, 0,1,1,2, Qt::AlignCenter);

    setLayout(p);
}

void FinestreBiblioteca::viewPdfFile(const QString & path) const
{
    const QString& path2 = getController()->daiPercorsoLibro(path);
    Finestre::viewPdfFile(path2);
}

void FinestreBiblioteca::AllCathegories() const
{
    getController()->ShowNewWindow(new TutteleCategorie(getController()));
}

void FinestreBiblioteca::SearchBook(const QString & key) const
{
    SearchResultLibri* temp = new SearchResultLibri(getController());
    temp->searchBook(key);
    temp->loadWindow();
    getController()->ShowNewWindow(temp);
}


QGridLayout *FinestreBiblioteca::giveLayout() const
{
    return p;
}


