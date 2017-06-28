#include "formaddimpiegato.h"
#include "../../../Controller/controllerpreside.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QScrollArea>
#include <QGroupBox>
#include <QMessageBox>

QGroupBox *FormAddImpiegato::loadPage()
{
    QGroupBox* temp = new QGroupBox;

    cognome = new QLineEdit(temp);
    nome = new QLineEdit(temp);
    mansione = new QComboBox(temp);
    nomeutente = new QLineEdit(temp);
    GenNomeUtente = new QPushButton("Genera un nome utente",temp);
    password = new QLineEdit(temp);
    GenPassword = new QPushButton("Genera una Password",temp);
    mail = new QLineEdit(temp);
    GenMail = new QPushButton("Genera una mail", temp);
    errore = new QLabel(temp);



    QGridLayout* ly = new QGridLayout(temp);
    QFont f("Times", 15);

    errore->setFont(f);
    ly->addWidget(errore,0,0, Qt::AlignTop);
    QLabel* title = new QLabel("I campi contrassegnati da (*) sono obbligatori",temp);
    title->setFont(f);
    ly->addWidget(title,1,0,Qt::AlignTop);

    f = QFont("Times", 13);
    title = new QLabel("Cognome (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,2,0,Qt::AlignTop);
    cognome->setFixedSize(400, 50);
    cognome->setMaxLength(20);
    cognome->setFont(f);
    cognome->setPlaceholderText("Inserisci il cognome");
    ly->addWidget(cognome,3,0,Qt::AlignTop);

    title = new QLabel("Nome (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,4,0,Qt::AlignTop);
    nome->setFixedSize(600, 50);
    nome->setMaxLength(40);
    nome->setFont(f);
    nome->setPlaceholderText("Inserisci il nome");
    ly->addWidget(nome,5,0,Qt::AlignTop);

    insertMansione();

    mansione->setFixedSize(600, 50);
    mansione->setFont(f);
    ly->addWidget(mansione,6,0,Qt::AlignTop);

    QHBoxLayout* dataScuola = new QHBoxLayout;
    title = new QLabel("Nome utente (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,7,0,Qt::AlignTop);
    nomeutente->setFixedSize(400, 50);
    nomeutente->setMaxLength(20);
    nomeutente->setFont(f);
    dataScuola->addWidget(nomeutente,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenNomeUtente->setFixedSize(200, 50);
    GenNomeUtente->setFont(QFont("Times",10));
    connect(GenNomeUtente, SIGNAL(clicked(bool)),this, SLOT(RandNomeUtente()));
    dataScuola->addWidget(GenNomeUtente,1,Qt::AlignLeft);

    ly->addLayout(dataScuola,8,0,Qt::AlignTop);

    title = new QLabel("Password di accesso (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,9,0,Qt::AlignTop);
    dataScuola = new QHBoxLayout;
    password->setFixedSize(400, 50);
    password->setMaxLength(8);
    password->setFont(f);
    dataScuola->addWidget(password,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenPassword->setFixedSize(200, 50);
    GenPassword->setFont(QFont("Times",10));
    connect(GenPassword, SIGNAL(clicked(bool)),this, SLOT(RandPassword()));
    dataScuola->addWidget(GenPassword,1,Qt::AlignLeft);
    ly->addLayout(dataScuola,10,0,Qt::AlignTop);

    title = new QLabel("Email scuola",temp);
    title->setFont(f);
    ly->addWidget(title,11,0,Qt::AlignTop);
    dataScuola = new QHBoxLayout;
    mail->setFixedSize(400, 50);
    mail->setFont(f);
    dataScuola->addWidget(mail,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenMail->setFixedSize(200, 50);
    GenMail->setFont(QFont("Times",10));
    connect(GenMail, SIGNAL(clicked(bool)),this, SLOT(RandMail()));
    dataScuola->addWidget(GenMail,1,Qt::AlignLeft);
    ly->addLayout(dataScuola,12,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Salva Modifiche", temp);
    connect(b, SIGNAL(clicked(bool)), this ,SLOT(salvaTutto()));
    b->setFixedSize(200, 60);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");

    ly->addWidget(b,13,0,Qt::AlignLeft);
    b = new QPushButton("Annulla",temp);
    b->setFixedSize(200, 60);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setStyleSheet("QPushButton{"
                            "background-color: red;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    connect(b,SIGNAL(clicked()), this, SLOT(close()));
    ly->addWidget(b,13,0, Qt::AlignRight);

    temp->setLayout(ly);
    return temp;
}

bool FormAddImpiegato::inputCorretto() const
{
    errore->setText("");
    errore->setStyleSheet("color: red;");
    if(cognome->text() == "" || nome->text() == "" ||
            password->text() == "" || mansione->currentIndex() == 0){
        errore->setText("Alcuni campi Obbligatori non sono stati compilati");
        return false;
    }
    return checkNomeUtente();
}

void FormAddImpiegato::insertMansione() const
{
    mansione->addItem("Seleziona la mansione (*)", 0);
    mansione->addItem("Professore", 1);
    mansione->addItem("Segretario", 2);
}

bool FormAddImpiegato::checkNomeUtente() const
{
    const QString& nu = nomeutente->text();
    if(nu == ""){
        errore->setText("Inserire un nome utente corretto");
        return false;
    }
    if(ctrl->esisteImpiegato(nu)){
        errore->setText("Questo nome utente è già preso");
        return false;
    }
    return true;
}

FormAddImpiegato::FormAddImpiegato(ControllerPreside *c, QWidget *parent):QDialog(parent), ctrl(c),
    cognome(0), nome(0),nomeutente(0),GenNomeUtente(0),
      password(0), GenPassword(0), mail(0),GenMail(0), errore(0), sc(new QScrollArea(this))
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
    lay->addWidget(sc,0);
    setLayout(lay);
}

void FormAddImpiegato::salvaTutto()
{
    if(QMessageBox::information(this,"ATTENZIONE!","Attenzione!\n"
                                "Non sarà più possibile modificare "
                                "le informazioni inserite, "
                                "almeno di rimuovere l'utente.\n"
                                "Sei sicuro di voler continuare?",
                                QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes){
    if(inputCorretto()){
        const QString& nomU = nomeutente->text();
        const QString& pass = password->text();
        const QString& name = nome->text();
        const QString& cognom = cognome->text();
        const QString& mel = mail->text();

        if(mansione->currentIndex() == 1){
            const QString& ri = ctrl->aggiungiProfessore(nomU, pass,name,cognom);
            bool check = (ri == "" && mel != "" ) ? ctrl->AggiungiMailImpiegato(nomU,mel) : false;
            if(check){
            QMessageBox::information(this,"","Impiegato aggiunto con successo!");
            reload();
            return;
            }
            else {QMessageBox::information(this,"",ri); return;}
        }
        else{
            const QString& ri = ctrl->aggiungiSegretario(nomU, pass,name,cognom);
            if(ri == ""){
                bool check = (mel != "" ) ? ctrl->AggiungiMailImpiegato(nomU,mel) : true;
                if(check){
                QMessageBox::information(this,"","Impiegato aggiunto con successo!");
                reload();
                return;
                }
            }
            else QMessageBox::information(this,"","Impiegato aggiunto con successo!");
        }
        QMessageBox::information(this,"Errore","Oops E' avvenuto un errore");

    }
    }

}

void FormAddImpiegato::RandNomeUtente() const
{
    errore->setText("");
    errore->setStyleSheet("color: blue;");
       if(cognome->text() == "" || nome->text() == "")
           errore->setText("Ho bisogno del nome e cognome "
                           "per generare un nome utente unico");
       else{
           nomeutente->setText(ctrl->generaNomeUtente(nome->text(),cognome->text()));
       }
}

void FormAddImpiegato::RandPassword() const
{
    errore->setText("");
    errore->setStyleSheet("color: blue;");
       if(cognome->text() == "" || nome->text() == "")
           errore->setText("Ho bisogno del nome e cognome "
                           "per generare una password unica");
       else{
           password->setText(ctrl->generaPassword(nome->text(),cognome->text()));
       }
}

void FormAddImpiegato::RandMail() const
{
    errore->setText("");
    errore->setStyleSheet("color: blue;");
       if(cognome->text() == "" || nome->text() == "")
           errore->setText("Ho bisogno del nome e cognome "
                           "per generare una mail unica");
       else{
           mail->setText(ctrl->generaMail(nome->text(),cognome->text()));
       }
}

void FormAddImpiegato::reload()
{
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
}
