#include "searchgroup.h"
#include "buttongroup.h"
#include "../Controller/controllergruppouser.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QComboBox>

void SearchGroup::InsertInCategoria()
{
    list<string> l = ctrl->GroupsCathegory();

    categ->addItem("Tutte le categorie",0);

             for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
                 const QString& cat = QString::fromStdString(*it);
                 categ->addItem(cat,cat);
        }


}

QGroupBox *SearchGroup::loadPage()
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);
    temp->setLayout(lay);

    QFont f("Times",13);
    f.setUnderline(true);

    QLabel* lab = new QLabel(QString::number(gruppi.size())+" gruppi trovati", temp);
    if(searchBox->text() != "")
        lab->setText(lab->text()+" per \""+searchBox->text()+"\"");
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 4em;");
    lay->addWidget(lab,0,0,1,1,Qt::AlignTop);

    f = QFont("Times",14);
    f.setBold(true);

    lab = new QLabel("Nome gruppo",temp);
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 1em;");
    lay->addWidget(lab,1,0,1,1,Qt::AlignTop);

     f = QFont("Times", 9);
    int row = 2;
     for(list<string>::const_iterator it=gruppi.begin(); it != gruppi.end(); ++it)
      {
        lab = new QLabel(QString::fromStdString((*it)),temp);
        lab->setFont(f);
        lab->setFixedWidth(300);
        lay->addWidget(lab,row,0,1,1,Qt::AlignTop);

        buttonGroup* b = new buttonGroup("Visita Gruppo",QString::fromStdString((*it)), this);
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        b->setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        connect(b, SIGNAL(clicked(bool)), b, SLOT(GiveHomeGroup()));
        lay->addWidget(b,row,1,1,1,Qt::AlignTop);

        ++row;
     }

     lay->setRowStretch(row+1,1);

     return temp;

}

SearchGroup::SearchGroup(ControllerGruppoUser *c, QWidget *parent):GruppoView(c,"",parent), head(0), body(0),
    searchBox(0), categ(0), ctrl(c),layout(new QVBoxLayout(this)){
    setWindowTitle("Search groups");
    Header();
    BodyAndFooter();
    setLayout(layout);


}

void SearchGroup::Header()
{
    head = new QGroupBox(this);
    QVBoxLayout* lay = new QVBoxLayout(head);
    head->setLayout(lay);

    QPushButton* b = new QPushButton("Indietro", head);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFixedSize(300,40);
    b->setFont(QFont("Times", 11));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this, SLOT(TornaIndietro()));
    lay->addWidget(b,0, Qt::AlignLeft);

    searchBox = new QLineEdit(head);
    searchBox->setFixedSize(400,40);
    searchBox->setFont(QFont("Times",10));
    searchBox->setPlaceholderText("Inserisci una parola chiave");
    b = new QPushButton("Cerca",head);
    b->setFixedSize(100,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFont(QFont("Times",10));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(ShowResult()));
    lay->addWidget(searchBox,0,Qt::AlignRight);
    lay->addWidget(b,0,Qt::AlignRight);

    categ = new QComboBox(head);
    categ->setFont(QFont("Times",10));
    categ->setFixedSize(300,40);
    categ->setCursor(QCursor(Qt::PointingHandCursor));
    InsertInCategoria();
    connect(categ,SIGNAL(currentIndexChanged(int)),this,SLOT(switchCath()));
    lay->addWidget(categ,1,Qt::AlignTop|Qt::AlignHCenter);

    layout->addWidget(head,0,Qt::AlignTop);

}

void SearchGroup::BodyAndFooter()
{
    body = new QScrollArea(this);

    gruppi = ctrl->GiveGroupsInCathegory("");

    body->setWidget(loadPage());
    body->setWidgetResizable(true);
    body->setFrameShape(QFrame::NoFrame);
    layout->addWidget(body,1);
}

void SearchGroup::ShowResult()
{
   if(searchBox->text() != "")
   gruppi = ctrl->esisteGruppo(searchBox->text());
   else
       gruppi = ctrl->GiveGroupsInCathegory("");

    reloadWindow();
}

void SearchGroup::reloadWindow()
{
    body->setWidget(loadPage());
    body->setWidgetResizable(true);
}

void SearchGroup::switchCath()
{
    if(categ->currentIndex() > 0){
        gruppi = ctrl->GiveGroupsInCathegory(categ->itemData(categ->currentIndex()).toString());
    }
    else
        gruppi = ctrl->GiveGroupsInCathegory("");
    reloadWindow();

}
