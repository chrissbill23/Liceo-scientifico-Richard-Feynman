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
    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);
    QLabel* tit = new QLabel("Tutti i campi sono obbligatori");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    f = QFont("Times", 13);
    f.setBold(true);

    tit = new QLabel("Cognome:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    cognome->setFixedHeight(50);
    cognome->setFont(f2);
    lay->addWidget(cognome,0,Qt::AlignTop);

    tit = new QLabel("Nome:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    nome->setFixedHeight(50);
    nome->setFont(f2);
    lay->addWidget(nome,0,Qt::AlignTop);

    tit = new QLabel("Nome utente di accesso:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    nomeutente->setFixedHeight(50);
    nomeutente->setFont(f2);
    lay->addWidget(nomeutente,0,Qt::AlignTop);

    tit = new QLabel("Password:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    password->setFixedHeight(50);
    password->setFont(f2);
    lay->addWidget(password,0,Qt::AlignTop);

    tit = new QLabel("Data fine carriera nel formato gg/mm/aaaa:");
    tit->setFont(f);
    lay->addWidget(tit,0,Qt::AlignTop);

    dataFineCarr->setFixedHeight(50);
    dataFineCarr->setFont(f2);
    lay->addWidget(dataFineCarr,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Salva",this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salva()));
    lay->addWidget(b,1,Qt::AlignTop);

    setLayout(lay);


}

void FormAddPreside::salva()
{
   const QString& ris = inputCorretto();

   if(ris != "")
       QMessageBox::information(this,"ERRORE", ris);
   else{
       const QString& nu = nomeutente->text();
       const QString& pass = password->text();
       const QString& cogn = cognome->text();
       const QString& nm =  nome->text();
       const QString& dFC =  dataFineCarr->text();
       const QString& ris2 = ctrl->addPreside(nu,pass, cogn,nm ,dFC);
       if(ris2 == ""){
       QMessageBox::information(this,"","Presidente aggiunto con successo!\n"
                                        "Ecco le credenziali di accesso del nuovo presidente:\n"
                                        "Nome utente: "+nu+"\n"
                                        "Password: "+pass);
       close();
       }
       else QMessageBox::information(this,"ERRORE!",ris2);
   }
}
