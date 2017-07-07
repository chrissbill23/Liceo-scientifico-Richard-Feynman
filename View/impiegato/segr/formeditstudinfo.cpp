#include "formeditstudinfo.h"
#include "../../../Controller/controllersegretario.h"
#include "../../../Modello/filexml.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QScrollArea>
#include <QGroupBox>
#include <QMessageBox>

void FormEditStudInfo::insertInNascita() const
{
    filexml f;
    ctrl->schedaPersonaleStud(matricola,f);
    if(f.apriFile()){
        const QString& nascita = QString::fromStdString(f.daiTestoIn("DataNascita"));
        const QDate date = QDate::fromString(nascita,"dd/MM/yyyy");

        ggNascita->addItem(QString::number(date.day()), date.day());

    for(int i=1; i<=31; ++i)
        ggNascita->addItem(QString::number(i),i);

    mmNascita->addItem(date.toString("MMMM"), date.month());
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

    annoNascita->addItem(date.toString("yyyy"), date.year());
    int currYear = QDate::currentDate().year();
    for(int i = currYear; i >= 1937; --i)
        annoNascita->addItem(QString::number(i),i);
    }
}

void FormEditStudInfo::InsertInClasse() const
{
    filexml f;
    ctrl->schedaPersonaleStud(matricola,f);
    if(f.apriFile()){
     const QString& clas = QString::fromStdString(f.daiTestoIn("Classe"));
    classe->addItem(clas,clas);
    vector<string>l = ctrl->Classi();
    for(vector<string>::const_iterator it= l.begin(); it != l.end(); ++it){
        classe->addItem(QString::fromStdString(*it));
    }
    }
}

bool FormEditStudInfo::checkDataNascita() const
{
    int g = (ggNascita->itemData(ggNascita->currentIndex())).toInt();
    int m = (mmNascita->itemData(mmNascita->currentIndex())).toInt();
    int a = (annoNascita->itemData(annoNascita->currentIndex())).toInt();

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

QString FormEditStudInfo::salvaNascitaDate() const
{
    filexml f;
    ctrl->schedaPersonaleStud(matricola,f);
    const QString& nascita = QString::fromStdString(f.daiTestoIn("DataNascita"));
    const QDate& date = QDate::fromString(nascita,"dd/MM/yyyy");
   if(ggNascita->itemData(ggNascita->currentIndex()).toInt() != date.day() ||
           mmNascita->itemData(mmNascita->currentIndex()).toInt() != date.month() ||
           annoNascita->itemData(annoNascita->currentIndex()).toInt() != date.year()){
    int g = ggNascita->itemData(ggNascita->currentIndex()).toInt();
    int m = mmNascita->itemData(mmNascita->currentIndex()).toInt();
    int a = annoNascita->itemData(annoNascita->currentIndex()).toInt();
    return ctrl->ModificaStudDataNascita(matricola,g,m,a);
   }
   return "";
}

QString FormEditStudInfo::salvaClasse() const
{
    filexml f;
    ctrl->schedaPersonaleStud(matricola,f);
    const QString& cla = QString::fromStdString(f.daiTestoIn("Classe"));
    if(classe->itemData(classe->currentIndex()).toString() != cla){
    const QString& clas = classe->currentText();
    return ctrl->ModificaStudClasse(matricola,clas);
    }
    return "";

}



QGroupBox *FormEditStudInfo::loadPage()
{
    QGroupBox* temp = new QGroupBox;

    filexml file;
    ctrl->schedaPersonaleStud(matricola,file);

    if(file.apriFile()){
    cognome = new QLineEdit(temp);
    nome = new QLineEdit(temp);
    ggNascita = new QComboBox(temp);
    mmNascita = new QComboBox(temp);
    annoNascita = new QComboBox(temp);
    LuogoNascita = new QLineEdit(temp);
    classe = new QComboBox(temp);
    errore = new QLabel(temp);



    QGridLayout* ly = new QGridLayout(temp);
    QFont f("Times", 14);

    errore->setFont(f);
    ly->addWidget(errore,0,0, Qt::AlignTop);
    QLabel* title = new QLabel("I campi contrassegnati da (*) sono obbligatori",temp);
    title->setFont(f);
    ly->addWidget(title,1,0,Qt::AlignTop);

    f = QFont("Times", 11);
    title = new QLabel("Cognome (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,2,0,Qt::AlignTop);
    cognome->setFixedSize(400, 50);
    cognome->setMaxLength(20);
    cognome->setFont(f);
    cognome->setText(QString::fromStdString(file.daiTestoIn("Cognome")));
    ly->addWidget(cognome,3,0,Qt::AlignTop);

    title = new QLabel("Nome (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,4,0,Qt::AlignTop);
    nome->setFixedSize(600, 50);
    nome->setMaxLength(40);
    nome->setFont(f);
    nome->setText(QString::fromStdString(file.daiTestoIn("Nome")));
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
    LuogoNascita->setText(QString::fromStdString(file.daiTestoIn("LuogoNascita")));
    ly->addWidget(title,8,0,Qt::AlignTop);
    ly->addWidget(LuogoNascita,9,0,Qt::AlignTop);

    title = new QLabel("Classe anno scolastico corrente (*) ",temp);
    title->setFont(f);
    ly->addWidget(title,10,0,Qt::AlignTop);
    classe->setFixedSize(230,30);
    classe->setFont(f);
    InsertInClasse();
    ly->addWidget(classe,11,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Salva modifiche",temp);
    b->setFont(f);
    b->setFixedSize(150,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salvaTutto()));
    ly->addWidget(b,12,0,Qt::AlignTop|Qt::AlignCenter);


    b = new QPushButton("Annulla",temp);
    b->setFont(f);
    b->setFixedSize(150,40);
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     "color: white;"
                     " border-radius: 5px 5px 5px 5px;}"
                     "QPushButton:pressed {"
                     " background-color:#660000;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(close()));
    ly->addWidget(b,13,0,Qt::AlignTop|Qt::AlignCenter);



    temp->setLayout(ly);
    }
    return temp;
}

FormEditStudInfo::FormEditStudInfo(ControllerSegretario *c, const QString &matr, QWidget *parent) : QDialog(parent), ctrl(c),
    cognome(0), nome(0),ggNascita(0), mmNascita(0),
      annoNascita(0),LuogoNascita(0),classe(0),errore(0), sc(new QScrollArea(this)), matricola(matr)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
    lay->addWidget(sc,0);

    setWindowTitle("Modifica dati studente");
    setLayout(lay);

}

void FormEditStudInfo::salvaTutto()
{
    errore->setText("Un attimo sto salvando");
    errore->setStyleSheet("color: blue;");

    const QString& matr = matricola;
    const QString& cogno = cognome->text();
    const QString& nom = nome->text();
    const QString& l= LuogoNascita->text();

    QString check = ctrl->ModificaStudCognome(matr,cogno);
    if(check != ""){
        errore->setText(check);
        errore->setStyleSheet("color: red;");
        return;
    }
    check = ctrl->ModificaStudNome(matr,nom);
    if(check != ""){
       errore->setText(check);
       errore->setStyleSheet("color: red;");
       return;
        }
    check = salvaNascitaDate();
    if(check != ""){
       errore->setText(check);
       errore->setStyleSheet("color: red;");
       return;
      }

    check = salvaClasse();
    if(check != ""){
       errore->setText(check);
       errore->setStyleSheet("color: red;");
       return;
        }
    check = ctrl->ModificaStudLuogoNascita(matr,l);
    if(check != ""){
       errore->setText(check);
       errore->setStyleSheet("color: red;");
       return;
      }

        QMessageBox::information(0,"","Salvato con successo");
        close();



}

