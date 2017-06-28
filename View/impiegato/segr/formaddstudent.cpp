#include "formaddstudent.h"
#include "../../../Controller/controllersegretario.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QScrollArea>
#include <QGroupBox>
#include <QMessageBox>


void FormAddStudent::insertInNascita() const
{
    ggNascita->addItem("Seleziona il giorno", -1);

    for(int i=1; i<=31; ++i)
        ggNascita->addItem(QString::number(i),i);

    mmNascita->addItem("Seleziona il mese", -1);
    mmNascita->addItem("Gennaio", 1);
    mmNascita->addItem("Febbraio", 2);
    mmNascita->addItem("Marzo", 3);
    mmNascita->addItem("Aprile", 4);
    mmNascita->addItem("Maggio", 5);
    mmNascita->addItem("Giugno", 6);
    mmNascita->addItem("Luglio", 7);
    mmNascita->addItem("Agosto", 8);
    mmNascita->addItem("Settembre", 9);
    mmNascita->addItem("Ottobre", 10);
    mmNascita->addItem("Novembre", 11);
    mmNascita->addItem("Dicembre", 12);

    annoNascita->addItem("Seleziona l'anno", -1);
    int currYear = QDate::currentDate().year();
    for(int i = currYear; i >= 1937; --i)
        annoNascita->addItem(QString::number(i),i);

}

void FormAddStudent::InsertInClasse() const
{
    classe->addItem("seleziona la classe", -1);
    vector<string> v = ctrl->Classi();
    for(vector<string>::const_iterator it= v.begin(); it != v.end(); ++it){
        classe->addItem(QString::fromStdString(*it));
    }
}

void FormAddStudent::Ricomincia()
{
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
}

bool FormAddStudent::checkDataNascita() const
{
    int g = (ggNascita->itemData(ggNascita->currentIndex())).toInt();
    int m = (mmNascita->itemData(mmNascita->currentIndex())).toInt();
    int a = (annoNascita->itemData(annoNascita->currentIndex())).toInt();

    if(g==-1 || m== -1 || a==-1){
        errore->setText("Tutti i dati sulla nascita vanno inseriti");
        return false;
    }
    if(m==2 && g==29 && a%4 != 0){
        errore->setText("La data di nascita inserita non è corretta");
        return false;
    }
    if((g>=30 && m==2) || (g>=31 && (m==4 || m==6 || m==9 || m==11 ))){
         errore->setText("Il giorno di nascita non è corretto");
        return false;
    }
    return true;
}

bool FormAddStudent::checkMatricola() const
{
        if((matricola->text()).toInt() == 0){
            errore->setText("Il numero di matricola deve essere "
                            "un numero di almeno 2 ciffre e di un massimo di 5 ciffre");
            return false;
        }
        return true;
}

bool FormAddStudent::checkNomeUtente() const
{
    const QString & nu = nomeutente->text();
    if(nu == ""){
        errore->setText("Inserire un nome utente corretto");
        return false;
    }
    if(ctrl->esisteNomeUtenteStud(nu)){
        errore->setText("Questo nome utente è già preso");
        return false;
    }
    return true;
}

QGroupBox *FormAddStudent::loadPage()
{
    QGroupBox* temp = new QGroupBox;

    cognome = new QLineEdit(temp);
    nome = new QLineEdit(temp);
    ggNascita = new QComboBox(temp);
    mmNascita = new QComboBox(temp);
    annoNascita = new QComboBox(temp);
    LuogoNascita = new QLineEdit(temp);
    classe = new QComboBox(temp);
    matricola = new QLineEdit(temp);
    GenMatricola = new QPushButton("Genera una matricola",temp);
    nomeutente = new QLineEdit(temp);
    GenNomeUtente = new QPushButton("Genera un nome utente",temp);
    password = new QLineEdit(temp);
    GenPassword = new QPushButton("Genera una Password",temp);
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

    insertInNascita();

    QHBoxLayout* dataNascita = new QHBoxLayout;
    title = new QLabel("Giorno Nascita (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,6,0,Qt::AlignTop);
    ggNascita->setFixedSize(200,30);
    ggNascita->setFont(f);
    dataNascita->addWidget(ggNascita,0,Qt::AlignLeft);


    mmNascita->setFixedSize(200,30);
    mmNascita->setFont(f);
    dataNascita->addWidget(mmNascita,0,Qt::AlignLeft);

    dataNascita->addWidget(annoNascita,1,Qt::AlignLeft);
    annoNascita->setFixedSize(200,30);
    annoNascita->setFont(f);

    ly->addLayout(dataNascita,7,0);

    title = new QLabel("Luogo Nascita (*) ",temp);
    title->setFont(f);
    LuogoNascita->setFixedSize(400, 50);
    LuogoNascita->setMaxLength(20);;
    LuogoNascita->setFont(f);
    ly->addWidget(title,8,0,Qt::AlignTop);
    ly->addWidget(LuogoNascita,9,0,Qt::AlignTop);

    title = new QLabel("Classe anno scolastico corrente (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,10,0,Qt::AlignTop);
    classe->setFixedSize(230,30);
    classe->setFont(f);
    InsertInClasse();
    ly->addWidget(classe,11,0,Qt::AlignTop);

    QFont f2("Times",10);
    title = new QLabel("Matricola (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,12,0,Qt::AlignTop);
    QHBoxLayout* dataScuola= new QHBoxLayout;
    matricola->setFixedSize(400, 50);
    matricola->setMaxLength(20);
    matricola->setFont(f);
    dataScuola->addWidget(matricola,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenMatricola->setFixedSize(200, 50);
    GenMatricola->setFont(f2);
    connect(GenMatricola, SIGNAL(clicked(bool)),this, SLOT(RandMatricola()));
    dataScuola->addWidget(GenMatricola,1,Qt::AlignLeft);

    ly->addLayout(dataScuola,13,0,Qt::AlignTop);

    title = new QLabel("Nome utente (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,14,0,Qt::AlignTop);
    dataScuola = new QHBoxLayout;
    nomeutente->setFixedSize(400, 50);
    nomeutente->setMaxLength(20);
    nomeutente->setFont(f);
    dataScuola->addWidget(nomeutente,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenNomeUtente->setFixedSize(200, 50);
    GenNomeUtente->setFont(f2);
    connect(GenNomeUtente, SIGNAL(clicked(bool)),this, SLOT(RandNomeUtente()));
    dataScuola->addWidget(GenNomeUtente,1,Qt::AlignLeft);

    ly->addLayout(dataScuola,15,0,Qt::AlignTop);

    title = new QLabel("Password di accesso (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,16,0,Qt::AlignTop);
    dataScuola = new QHBoxLayout;
    password->setFixedSize(400, 50);
    password->setMaxLength(8);
    password->setFont(f);
    dataScuola->addWidget(password,0,Qt::AlignLeft);
    dataScuola->addWidget(new QLabel("Oppure", temp), 0, Qt::AlignLeft);
    GenPassword->setFixedSize(200, 50);
    GenPassword->setFont(f2);
    connect(GenPassword, SIGNAL(clicked(bool)),this, SLOT(RandPassword()));
    dataScuola->addWidget(GenPassword,1,Qt::AlignLeft);
    ly->addLayout(dataScuola,17,0,Qt::AlignTop);

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

    ly->addWidget(b,18,0,Qt::AlignLeft);
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
    ly->addWidget(b,18,0, Qt::AlignRight);

    temp->setLayout(ly);
    return temp;
}

FormAddStudent::FormAddStudent(ControllerSegretario *c, QWidget *parent):QDialog(parent), ctrl(c),
cognome(0), nome(0),ggNascita(0), mmNascita(0),
  annoNascita(0),LuogoNascita(0),classe(0),matricola(0),
  GenMatricola(0),nomeutente(0),GenNomeUtente(0),
  password(0), GenPassword(0),errore(0), sc(new QScrollArea(this))
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
    lay->addWidget(sc,0);
    setLayout(lay);
    setWindowTitle("Aggiungi nuovo studente");
}

bool FormAddStudent::inputCorretto() const
{
    errore->setText("");
    errore->setStyleSheet("color: red;");
    if(cognome->text() == "" || nome->text() == "" ||
        LuogoNascita->text() == "" || (classe->itemData(classe->currentIndex())).toInt() == -1 ||
            matricola->text() == "" || password->text() == ""){
        errore->setText("Alcuni campi Obbligatori non sono stati compilati");
        return false;
    }
    return checkDataNascita() && checkMatricola() && checkNomeUtente();
}

void FormAddStudent::salvaTutto()
{
    if(inputCorretto()){
    errore->setText("Un attimo sto salvando...");
    errore->setStyleSheet("color: blue;");

    const QString& matr = matricola->text();
    const QString& cogno = cognome->text();
    const QString& nom = nome->text();
    const QString& nu = nomeutente->text();
    const QString& pw = password->text();
    const QString& clas= classe->currentText();
    int g = ggNascita->itemData(ggNascita->currentIndex()).toInt();
    int m = mmNascita->itemData(mmNascita->currentIndex()).toInt();
    int a= annoNascita->itemData(annoNascita->currentIndex()).toInt();
    const QString& l= LuogoNascita->text();



    QString check = ctrl->InsertNewStud(matr,nu,pw,cogno,nom,clas,l,g,m,a);
    if(check != ""){
        errore->setText(check);
        errore->setStyleSheet("color: red;");
        return;
    }

    QMessageBox::information(this,"","Salvato con successo, continua l'inserimento, oppure annulla");
    Ricomincia();

    }
}

void FormAddStudent::RandMatricola() const
{
    errore->setText("");
    errore->setStyleSheet("color: blue;");
    matricola->setText(ctrl->getNewMatricola());
}

void FormAddStudent::RandNomeUtente() const
{
  errore->setText("");
  errore->setStyleSheet("color: blue;");
     if(cognome->text() == "" || nome->text() == "")
         errore->setText("Ho bisogno del nome e cognome "
                         "per generare un nome utente unico");
     else{
         nomeutente->setText(ctrl->getNewStudNomeUtente((nome->text()),(cognome->text())));
     }
}

void FormAddStudent::RandPassword() const
{
    int g = (ggNascita->itemData(ggNascita->currentIndex())).toInt();
    int m = (mmNascita->itemData(mmNascita->currentIndex())).toInt();
    int a = (annoNascita->itemData(annoNascita->currentIndex())).toInt();


    errore->setText("");
    errore->setStyleSheet("color: blue;");
     if(cognome->text()=="" || nome->text() =="" ||g==-1 || m== -1 || a==-1 )
         errore->setText("Ho bisogno del nome, cognome e della data di nascita "
                         "per generare una password unica");
     else{
         if(checkDataNascita())
           password->setText(ctrl->getNewStudPassword(nome->text(),cognome->text(), annoNascita->itemData(annoNascita->currentIndex()).toInt()));
     }
}
