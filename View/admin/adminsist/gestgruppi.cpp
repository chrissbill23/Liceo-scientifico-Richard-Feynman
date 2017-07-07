#include "gestgruppi.h"
#include "../../buttongroup.h"
#include "../../popupdialog.h"
#include "formeditgroup.h"
#include "gestpostsgroup.h"
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>

void GestGruppi::InsertInCategoria()
{
    list<string> l = ctrl->GroupsCathegory();

    if(int(l.size()) != categ->count() - 1){
        l.sort();
        categ->blockSignals(true);
        categ->clear();
        categ->addItem("Tutte le categorie",0);

             for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
                 const QString& cat = QString::fromStdString(*it);
                 categ->addItem(cat,cat);
             }
        categ->blockSignals(false);
        gruppi = ctrl->MyGroupsName();
    }
}

QGroupBox *GestGruppi::loadPage()
{
    QGroupBox* temp = new QGroupBox;
    QGridLayout* lay = new QGridLayout(temp);
    temp->setLayout(lay);

    QFont f("Times",11);
    f.setUnderline(true);

    QLabel* lab = new QLabel(QString::number(gruppi.size())+" gruppi trovati", temp);
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 4em;");
    lay->addWidget(lab,0,0,1,1,Qt::AlignTop);

    f = QFont("Times",12);
    f.setBold(true);

    lab = new QLabel("Nome gruppo",temp);
    lab->setFont(f);
    lab->setStyleSheet("margin-bottom: 1em;");
    lay->addWidget(lab,1,0,1,1,Qt::AlignTop);

     f = QFont("Times", 10);
    int row = 2;
     for(list<string>::const_iterator it=gruppi.begin(); it != gruppi.end(); ++it)
      {
        lab = new QLabel(QString::fromStdString((*it)),temp);
        lab->setFont(f);
        lab->setFixedWidth(300);
        lay->addWidget(lab,row,0,1,1,Qt::AlignTop);

        buttonGroup* b = new buttonGroup("Info gruppo",QString::fromStdString((*it)), this);
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b, SIGNAL(clicked(bool)), b, SLOT(viewInfoGroup()));
        lay->addWidget(b,row,1,1,1,Qt::AlignTop);

        b = new buttonGroup("Modifica info gruppo",QString::fromStdString((*it)), this);
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b, SIGNAL(clicked(bool)), this, SLOT(EditGroup()));
        lay->addWidget(b,row,2,1,1,Qt::AlignTop);

        b = new buttonGroup("Gestione post",QString::fromStdString((*it)), this);
        b->setFixedSize(150, 30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b, SIGNAL(clicked(bool)), this, SLOT(GestPost()));
        lay->addWidget(b,row,3,1,1,Qt::AlignTop);

        b = new buttonGroup("Elimina gruppo",QString::fromStdString((*it)), this);
        b->setFixedSize(150, 30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #990000;"
                         "color: white;"
                         " border-radius: 5px;}"
                         "QPushButton:pressed {"
                         " background-color:#660000;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b, SIGNAL(clicked(bool)), this, SLOT(ElimGroup()));
        lay->addWidget(b,row,4,1,1,Qt::AlignTop);

        ++row;
     }
     lay->setRowStretch(row+1,1);

     return temp;
}

GestGruppi::GestGruppi(ControllerAdminSistema *c, const QString &name, QWidget *parent) : GruppoView(c,name, parent), ctrl(c),head(0), body(0),
    searchBox(0), categ(0),lay(new QVBoxLayout(this))
{
    setWindowTitle("Gestione gruppi");
    Header();
    BodyAndFooter();
    setLayout(lay);
    setStyleSheet("QPushButton{"
                             "background-color: #336699; "
                             "border-radius: 5px 5px 5px 5px; "
                             "color: white;}"
                             "QPushButton:pressed {"
                            " background-color:#003300;}");
}

void GestGruppi::Header()
{
    head = new QGroupBox(this);
    QVBoxLayout* layout = new QVBoxLayout(head);
    head->setLayout(layout);

    QPushButton* b = new QPushButton("Indietro", head);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFixedSize(200,40);
    b->setFont(QFont("Times", 11));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this, SLOT(TornaIndietro()));
    layout->addWidget(b,0, Qt::AlignLeft);

    searchBox = new QLineEdit(head);
    searchBox->setFixedSize(300,40);
    searchBox->setFont(QFont("Times",10));
    searchBox->setPlaceholderText("Cosa cerchi?");
    searchBox->setMaxLength(26);
    b = new QPushButton("Cerca",head);
    b->setFixedSize(100,40);
    b->setFont(QFont("Times",10));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(ShowResult()));
    layout->addWidget(searchBox,0,Qt::AlignRight);
    layout->addWidget(b,0,Qt::AlignRight);

    QHBoxLayout* p = new QHBoxLayout;
    categ = new QComboBox(head);
    categ->setFont(QFont("Times",10));
    categ->setFixedSize(220,40);
    categ->setCursor(QCursor(Qt::PointingHandCursor));
    InsertInCategoria();
    connect(categ,SIGNAL(currentIndexChanged(int)),this,SLOT(switchCath()));
    p->addWidget(categ,0,Qt::AlignTop|Qt::AlignHCenter);

    b = new QPushButton("Aggiungi categoria", head);
    b->setFixedSize(200,40);
    b->setFont(QFont("Times",9));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addCathegory()));
    p->addWidget(b,0,Qt::AlignLeft);

    b = new QPushButton("Elimina categoria", head);
    b->setFixedSize(200,40);
    b->setFont(QFont("Times",9));
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     "color: white;"
                     " border-radius: 5px;}"
                     "QPushButton:pressed {"
                     " background-color:#660000;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(removeCathegory()));
    p->addWidget(b,0,Qt::AlignLeft);

    b = new QPushButton("Aggiungi gruppo", head);
    b->setFixedSize(200,40);
    b->setFont(QFont("Times",9));
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px 5px 5px 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addNewGroup()));
    p->addWidget(b,1,Qt::AlignLeft);

    layout->addLayout(p);

    lay->addWidget(head,0,Qt::AlignTop);
}

void GestGruppi::BodyAndFooter()
{
    body = new QScrollArea(this);

    gruppi = ctrl->GiveGroupsInCathegory("");
    body->setWidget(loadPage());
    body->setWidgetResizable(true);
    body->setFrameShape(QFrame::NoFrame);
    lay->addWidget(body,1);
}

void GestGruppi::ShowResult()
{
    if(searchBox->text() != "")
    gruppi = ctrl->esisteGruppo(searchBox->text());
    else
        gruppi = ctrl->GiveGroupsInCathegory("");


     reloadWindow();
}

void GestGruppi::reloadWindow()
{
    InsertInCategoria();
    body->setWidget(loadPage());
    body->setWidgetResizable(true);
}

void GestGruppi::switchCath()
{
    if(categ->currentIndex() > 0){
        gruppi = ctrl->GiveGroupsInCathegory(categ->itemData(categ->currentIndex()).toString());
    }
    else
        gruppi = ctrl->GiveGroupsInCathegory("");

    body->setWidget(loadPage());
    body->setWidgetResizable(true);
}

void GestGruppi::addCathegory()
{
    popUpDialog temp(1,4);

    QFont f("Times",12);
    f.setBold(true);

    QLabel* tit = new QLabel("Inserisci il nome della categoria",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    QLineEdit* text = new QLineEdit(&temp);
    text->setFont(QFont("Times",13));
    text->setFixedHeight(40);
    temp.push_back_Widget(text);

    QPushButton* b = new QPushButton("Salva", &temp);
    connect(b, SIGNAL(clicked(bool)), &temp, SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla", &temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(500,200);
    temp.setWindowTitle("Aggiungi categoria");
    if(temp.exec() == QDialog::Accepted){
        const QString& testo = text->text();
        if(testo != ""){
            const QString& ris = ctrl->addGroupCathegory(testo);
            if(ris == ""){
                QMessageBox::information(&temp,"", "Salvato con successo!");
               reloadWindow();
            }
            else QMessageBox::information(&temp,"ERRORE!!", ris);
        }
        else QMessageBox::information(&temp,"ERRORE!!", "Deve inserire il nome della categoria");
    }
}

void GestGruppi::removeCathegory()
{
    popUpDialog temp(1,3);

    QComboBox* text = new QComboBox(&temp);
    text->addItem("Seleziona la categoria",-1);
    list<string> l = ctrl->GroupsCathegory();
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        const QString& cath = QString::fromStdString(*it);
        text->addItem(cath,cath);
    }
    text->setFont(QFont("Times",9));
    text->setFixedHeight(30);
    temp.push_back_Widget(text);

    QPushButton* b = new QPushButton("Salva", &temp);
    connect(b, SIGNAL(clicked(bool)), &temp, SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla", &temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(500,200);
    temp.setWindowTitle("Elimina categoria");
    if(temp.exec() == QDialog::Accepted){
        const QString& testo = text->itemData(text->currentIndex()).toString();
        if(testo != "-1"){
            const QString& ris = ctrl->removeGroupCathegory(testo);
            if(ris == ""){
                QMessageBox::information(&temp,"", "Eliminato con successo!");
                reloadWindow();
            }
            else QMessageBox::information(&temp,"ERRORE!!", ris);
        }
        else QMessageBox::information(&temp,"ERRORE!!", "Deve inserire il nome della categoria");
    }
}

void GestGruppi::addNewGroup()
{
    popUpDialog temp(1,7);

    QFont f("Times",12);
    f.setBold(true);

    QLabel* lab = new QLabel("Nome:",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);

    QLineEdit* name = new QLineEdit(&temp);
    name->setFont(QFont("Times",13));
    name->setFixedHeight(40);
    temp.push_back_Widget(name);

    lab = new QLabel("Descrizione:",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);

    QTextEdit* descr = new QTextEdit(&temp);
    descr->setFont(QFont("Times",13));
    temp.push_back_Widget(descr);

    QComboBox* catego = new QComboBox(&temp);
    catego->addItem("Seleziona la categoria",-1);
    list<string> l = ctrl->GroupsCathegory();
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        const QString& cath = QString::fromStdString(*it);
        catego->addItem(cath,cath);
    }
    catego->setFont(QFont("Times",9));
    catego->setFixedHeight(30);
    temp.push_back_Widget(catego);

    QPushButton* b = new QPushButton("Salva", &temp);
    connect(b, SIGNAL(clicked(bool)), &temp, SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla", &temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(500,400);
    temp.setWindowTitle("Aggiungi gruppo");

    while(temp.exec() == QDialog::Accepted &&
          (name->text() == "" || descr->toPlainText() == "" || catego->itemData(catego->currentIndex()).toString() == "" )){
         QMessageBox::information(&temp,"ERRORE!!", "Tutti i campi sono obbligatori");
    }

    if(temp.result() == QDialog::Accepted){
        const QString& nome = name->text();
        const QString& des = descr->toPlainText();
        const QString& cath = catego->itemData(catego->currentIndex()).toString();
        const QString& ris = ctrl->addNewGroup(nome,des,cath);
            if(ris == ""){
                QMessageBox::information(&temp,"", "Aggiunto con successo!");
                switchCath();
                reloadWindow();
            }
            else QMessageBox::information(&temp,"ERRORE!!", ris);
    }
}

void GestGruppi::EditGroup()
{
    QObject* o = sender();

    buttonGroup* b = dynamic_cast<buttonGroup*>(o);
    if(b){
        FormEditGroup temp(ctrl, b->giveGroupName());
        temp.setFixedSize(600,500);
        temp.exec();
    }
}

void GestGruppi::ElimGroup()
{
    QObject* o = sender();

    buttonGroup* b = dynamic_cast<buttonGroup*>(o);
    if(b){
        const QString ris = ctrl->removeGroup(b->giveGroupName());
        if( ris == ""){
        QMessageBox::information(0,"","Gruppo Eliminato!");
        switchCath();
        }
        else QMessageBox::information(0,"ERRORE!",ris);
    }
}

void GestGruppi::GestPost() const
{
    QObject* o = sender();

    buttonGroup* b = dynamic_cast<buttonGroup*>(o);
    if(b){
        ctrl->ShowNewWindow(new GestPostsGroup(ctrl,b->giveGroupName()) );
    }
}
