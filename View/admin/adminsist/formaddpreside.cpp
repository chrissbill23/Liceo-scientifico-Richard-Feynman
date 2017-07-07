#include "formaddpreside.h"
#include "../../../Controller/controlleradminsistema.h"
#include <QLineEdit>
#include <QLabel>
#include <QDate>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

QString FormAddPreside::inputCorretto() const
{
    if(cognome->text() == "" || nome->text() == "" || nomeutente->text() == "" || password->text() == "" || dataFineCarr->text() == "" )
        return "Tutti i campi sono obbligatori";
    if(!QDate::fromString(dataFineCarr->text(),"dd/MM/yyyy").isValid())
        return "La data di carriera inserita non è valida";
    return "";
}

FormAddPreside::FormAddPreside(ControllerAdminSistema *c, QWidget *parent) : QDialog(parent), ctrl(c),
    cognome(new QLineEdit(this)), nome(new QLineEdit(this)), nomeutente(new QLineEdit(this)), password(new QLineEdit(this)),
    dataFineCarr(new QLineEdit(this)), lay(new QVBoxLayout(this))
{
    QFont f("Times",13);
    f.setBold(true);
    QFont f2("Times",9);
    QLabel* tit = new QLabel("Tutti i campi sono obbligatori");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    f = QFont("Times", 11);
    f.setBold(true);

    tit = new QLabel("Cognome:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    cognome->setFixedHeight(30);
    cognome->setFont(f2);
    lay->addWidget(cognome,0,Qt::AlignTop);

    tit = new QLabel("Nome:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    nome->setFixedHeight(30);
    nome->setFont(f2);
    lay->addWidget(nome,0,Qt::AlignTop);

    tit = new QLabel("Nome utente di accesso:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    nomeutente->setFixedHeight(30);
    nomeutente->setFont(f2);
    lay->addWidget(nomeutente,0,Qt::AlignTop);

    tit = new QLabel("Password:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    password->setFixedHeight(30);
    password->setFont(f2);
    lay->addWidget(password,0,Qt::AlignTop);

    tit = new QLabel("Data fine carriera nel formato gg/mm/aaaa:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    dataFineCarr->setFixedHeight(30);
    dataFineCarr->setFont(f2);
    lay->addWidget(dataFineCarr,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Salva",this);
    b->setFixedHeight(20);
    b->setStyleSheet("QPushButton{"
                     "background-color: #336699; "
                     "border-radius: 5px; "
                     "color: white;}"
                     "QPushButton:pressed {"
                    " background-color:#003300;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salva()));
    lay->addWidget(b,1,Qt::AlignTop);

    setLayout(lay);
    setWindowTitle("Nuovo presidente");


}

void FormAddPreside::salva()
{
   const QString& ris = inputCorretto();

   if(ris != "")
       QMessageBox::information(0,"ERRORE", ris);
   else{
       const QString& nu = nomeutente->text();
       const QString& pass = password->text();
       const QString& cogn = cognome->text();
       const QString& nm =  nome->text();
       const QString& dFC =  dataFineCarr->text();
       const QString& ris2 = ctrl->addPreside(nu,pass, cogn,nm ,dFC);
       if(ris2 == ""){
       QMessageBox::information(0,"","Presidente aggiunto con successo!\n"
                                        "Ecco le credenziali di accesso del nuovo presidente:\n"
                                        "Nome utente: "+nu+"\n"
                                        "Password: "+pass);
       close();
       }
       else QMessageBox::information(0,"ERRORE!",ris2);
   }
}
