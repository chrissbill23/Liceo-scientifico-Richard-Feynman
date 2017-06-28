#include "finestreimpiegato.h"
#include "inviamessdialog.h"
#include "tuttiimess.h"
#include "messaggioview.h"
#include "agendabox.h"
#include "notifichemailbox.h"
#include "../../Modello/filexml.h"
#include "../popupdialog.h"
#include <QTime>
#include <QTimer>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QCloseEvent>
#include <QPushButton>

FinestreImpiegato::FinestreImpiegato(ControllerImpiegato *ptr, QWidget* parent): Finestre(ptr, parent),ctrl(ptr),
   FoglioPresenza(0),
   t(0),
   mess(0),
   Agenda(0),
   p(0){
}

void FinestreImpiegato::Header()
{
    if(p)
        delete p;
    if(Agenda)
        delete Agenda;
    if(mess)
        delete mess;
    if(t){
        t->stop();
        delete t;
    }
    if(FoglioPresenza)
        delete FoglioPresenza;

    FoglioPresenza = new QLabel(QDate::currentDate().toString("dd/MMMM/yyyy")+"\n"+QTime::currentTime().toString("hh:mm:ss"), this);
    t = new QTimer(this);
    mess = new NotificheMailBox(ctrl,this);
    Agenda = new AgendaBox(this);
    p = new QGridLayout(this);
    QFont f("Times", 15);
    t->setInterval(1000);
    t->start();
       connect(t, SIGNAL(timeout()), this, SLOT(updateLabel()));
    FoglioPresenza->setFont(f);
    FoglioPresenza->setStyleSheet("QLabel{"
                                  "background-color: white;"
                                  "border-radius: 15px 15px 15px 15px; "
                                  "color:#29abe2 ;"
                                  "padding-left: 1em;}");
    FoglioPresenza->setFixedSize(500,300);
    FoglioPresenza->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    QPushButton* biblio = new QPushButton("Biblioteca", this);
    biblio->setFixedSize(150, 40);
    biblio->setFont(f);
    biblio->setStyleSheet("QPushButton{"
                          "background-color: green; "
                          "border-radius: 5px 5px 5px 5px; "
                          "color: white;}"
                          "QPushButton:pressed {"
                         " background-color:#003300;}");
    biblio->setCursor(QCursor(Qt::PointingHandCursor));
    connect(biblio,SIGNAL(clicked()), this, SLOT(HomePageBiblio()));

    QPushButton* logout= new QPushButton("logout", this);
    logout->setFixedSize(150, 40);
    logout->setStyleSheet("QPushButton{"
                          "background-color: #990000;"
                          " border-radius: 5px 5px 5px 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    logout->setCursor(QCursor(Qt::PointingHandCursor));
    logout->setFont(f);
    connect(logout,SIGNAL(clicked()), this, SLOT(signout()));

    mess->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: #264d73; color: white;");
    mess->setFont(f);
    mess->setFixedWidth(500);

    Agenda->setStyleSheet("border-radius: 15px 15px 15px 15px; background-color: rgb(26, 163, 163); color: black;");
    Agenda->setFont(f);

    p->addWidget(FoglioPresenza,1,0,1,1, Qt::AlignTop);
    p->addWidget(biblio,0,2,Qt::AlignRight);
    p->addWidget(logout,0,3);
    p->addWidget(mess,1,1,1,1,Qt::AlignTop);
    p->addWidget(Agenda,1,2,1,2,Qt::AlignTop);
    setLayout(p);
}

QGridLayout *FinestreImpiegato::giveLayout() const
{
    return p;
}

void FinestreImpiegato::updateLabel() const
{
    FoglioPresenza->setText(QDate::currentDate().toString("dd/MMMM/yyyy")+"\n"+QTime::currentTime().toString("hh:mm:ss"));
}

void FinestreImpiegato::InviaNuovoMess()
{
        InviaMessDialog messSendbox(ctrl);
        messSendbox.exec();
}

void FinestreImpiegato::viewInfoStud(const QString &matricola) const
{
        filexml file;
       ctrl->schedaPersonaleStud(matricola,file);

        if(file.apriFile()){
            popUpDialog temp(1,17);
            temp.setFixedSize(700,700);


            QFont f("Times",14);
            f.setBold(true);
            QFont f2("Times",12);
            QLabel* lab = new QLabel("Cognome: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            const QString& tit = QString::fromStdString(file.daiTestoIn("Cognome"));
            lab = new QLabel(tit, &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);
            temp.setWindowTitle(tit);

            lab = new QLabel("Nome: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("Nome")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            lab = new QLabel("Matricola: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("Matricola")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            lab = new QLabel("Classe: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("Classe")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            lab = new QLabel("Data di nascita: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("DataNascita")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            lab = new QLabel("Luogo di nascita: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("LuogoNascita")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            lab = new QLabel("Nome utente: ",&temp);
            lab->setFont(f);
            temp.push_back_Widget(lab);
            lab = new QLabel(QString::fromStdString(file.daiTestoIn("nomeUtente")), &temp);
            lab->setFont(f2);
            temp.push_back_Widget(lab);

            temp.exec();
        }
    }



void FinestreImpiegato::ElimMail(unsigned int i, bool ricevuta)
{
    ctrl->eliminaMail(i, ricevuta);
}


void FinestreImpiegato::leggiMess(int i, bool ricevuta, bool OnlyUnread)
{

    MessaggioView read(ctrl);
    read.SelectMessage(i, ricevuta, OnlyUnread);
    read.exec();
    if(mess)
    mess->reload();
}

void FinestreImpiegato::SeeReceivedMails() const
{
    ctrl->ShowNewWindow(new TuttiImess(ctrl));
}



ControllerImpiegato *FinestreImpiegato::getController() const
{
    return ctrl;
}

void FinestreImpiegato::setStyleSheet(const QString & s)
{
    Finestre::setStyleSheet(s);
}

