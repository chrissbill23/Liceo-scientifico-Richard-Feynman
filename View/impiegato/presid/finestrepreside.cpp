#include "finestrepreside.h"
#include "gestionepersonale.h"
#include "gestclassi.h"
#include "../../popupdialog.h"
#include "formaddimpiegato.h"
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include <QLineEdit>
#include <algorithm>
#include <QPushButton>

FinestrePreside::FinestrePreside(ControllerPreside *p, QWidget *parent):FinestreImpiegato(p,parent), ctrl(p){
    setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px 5px 5px 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
}

ControllerPreside *FinestrePreside::getController() const
{
    return ctrl;
}

void FinestrePreside::gestionePersonale() const
{
    ctrl->ShowNewWindow(new GestionePersonale(ctrl));
}

void FinestrePreside::gestioneClassi() const
{
    ctrl->ShowNewWindow(new GestClassi(ctrl) );
}

void FinestrePreside::viewInfoImpiegato(const QString &nomeUtente) const
{
    QFont f2("Times",12);

    popUpDialog temp(1,1);
    QLabel* tit = new QLabel("Nessun impiego trovato per l'utente "+nomeUtente,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    temp.setFixedSize(500,500);

    temp.exec();

}

void FinestrePreside::rimuoviImpiegato(const QString &nomeUtente)
{
    QFont f2("Times",12);

    popUpDialog temp(1,1);
    QLabel* tit = new QLabel("Nessun impiego trovato per l'utente "+nomeUtente,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    temp.setFixedSize(500,500);

    temp.exec();
}

void FinestrePreside::CercaImpiegato()
{
    QFont f2("Times",12);

    popUpDialog temp(1,1);
    QLabel* tit = new QLabel("Nessun impiegato trovato ",&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    temp.setFixedSize(500,500);

    temp.exec();
}
void FinestrePreside::addImpiegato()
{
    FormAddImpiegato temp(ctrl);
    temp.setFixedSize(700,600);

    temp.exec();
    reloadWindow();
}

void FinestrePreside::rimuoviClasse(const QString &nome)
{
    const QString& ris = ctrl->rimuoviClasse(nome);
    if(ris == ""){
        QMessageBox::information(0, "", "la classe "+nome+" è stata rimossa");
        reloadWindow();
    }
    else QMessageBox::information(0,"ERRORE", ris);
}

void FinestrePreside::aggiungiClasse()
{
    popUpDialog temp(1,5);

    QFont f("Times",12);
    QComboBox* classi = new QComboBox(&temp);
    classi->setFixedSize(300,50);
    classi->setFont(f);
    classi->addItem("Seleziona la classe",0);
    for(int i = 1; i <= 5; ++i)
        classi->addItem(QString::number(i),i);

    temp.push_back_Widget(classi);


    QComboBox* sessioni = new QComboBox(&temp);
    sessioni->setFixedSize(300,50);
    sessioni->setFont(f);
    list<string> l = ctrl->daiSessioniClassi();
    sessioni->addItem("Seleziona sessione",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        sessioni->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(sessioni);


    QComboBox* indirizzo = new QComboBox(&temp);
    indirizzo->setFixedSize(300,50);
    indirizzo->setFont(f);
    list<string> l2 = ctrl->daiIndirizzoClassi();
    indirizzo->addItem("Seleziona l'indirizzo",0);
    for(list<string>::const_iterator it = l2.begin(); it != l2.end(); ++it)
        indirizzo->addItem(QString::fromStdString(*it),QString::fromStdString(*it));
    temp.push_back_Widget(indirizzo);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(450,300);
    temp.setWindowTitle("Nuova classe");

    QString cla = classi->itemData(classi->currentIndex()).toString();
    QString sess = sessioni->itemData(sessioni->currentIndex()).toString();
    QString indi =  indirizzo->itemData(indirizzo->currentIndex()).toString();
    QString ris = "errore";

    while((cla == "0" || sess == "0" || indi =="0" || ris != "")&& temp.exec() == QDialog::Accepted ){
        cla = classi->itemData(classi->currentIndex()).toString();
        sess = sessioni->itemData(sessioni->currentIndex()).toString();
        indi =  indirizzo->itemData(indirizzo->currentIndex()).toString();
        if(cla == "0" || sess == "0" || indi =="0")
            QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
        else{
            ris = ctrl->aggiungiClasse(cla,sess,indi);
            if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
        }
    }


    if(temp.result() == QDialog::Accepted && ris == ""){
            QMessageBox::information(&temp,"", "Aggiunta con successo!");
            reloadWindow();
    }

}

void FinestrePreside::aggiungiSessClasse()
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QLineEdit* sess = new QLineEdit(this);
    sess->setPlaceholderText("Inserisci il nome della sessione");
    sess->setFixedHeight(50);
    sess->setFont(f);

    temp.push_back_Widget(sess);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(500,200);
    temp.setWindowTitle("Nuova sessione");

    QString ris = "Errore";
    while((sess->text() == "" || ris != "") && temp.exec() == QDialog::Accepted){
     if(sess->text() == "")
     QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
     else{
         ris = ctrl->aggiungiSessioniClassi(sess->text());
         if(ris != "")
             QMessageBox::information(&temp,"Errore", ris);
     }
    }

    if(temp.result() == QDialog::Accepted && ris == "" ){
            QMessageBox::information(&temp,"", "Aggiunta con successo!");
            reloadWindow();
    }

}

void FinestrePreside::aggiungiIndirClasse()
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QLineEdit* ind = new QLineEdit(&temp);
    ind->setPlaceholderText("Inserisci il nome dell'indirizzo");
    ind->setFixedHeight(50);
    ind->setFont(f);

    temp.push_back_Widget(ind);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(500,200);
    temp.setWindowTitle("Nuovo indirizzo");

    QString ris = "Errore";
    while((ind->text() == "" || ris != "") && temp.exec() == QDialog::Accepted){
     if(ind->text() == "")
     QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
     else{
         ris = ctrl->aggiungiIndirizzoClassi(ind->text());
         if(ris != "")
             QMessageBox::information(&temp,"Errore", ris);
     }
    }

    if(temp.result() == QDialog::Accepted && ris == "" ){
            QMessageBox::information(&temp,"", "Aggiunta con successo!");
            reloadWindow();
    }
}

void FinestrePreside::aggiungiMateria()
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QLineEdit* ind = new QLineEdit(&temp);
    ind->setPlaceholderText("Inserisci il nome della materia");
    ind->setFixedHeight(50);
    ind->setFont(f);

    temp.push_back_Widget(ind);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(450,190);
    temp.setWindowTitle("Nuova materia");

    QString ris = "Errore";
    while((ind->text() == "" || ris != "") && temp.exec() == QDialog::Accepted){
     if(ind->text() == "")
     QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
     else{
         ris = ctrl->aggiungiMateria(ind->text());
         if(ris != "")
             QMessageBox::information(&temp,"Errore", ris);
     }
    }

    if(temp.result() == QDialog::Accepted && ris == "" ){
            QMessageBox::information(&temp,"", "Aggiunta con successo!");
            reloadWindow();
    }
}

void FinestrePreside::rimuoviSessione()
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QComboBox* sessioni = new QComboBox(&temp);
    sessioni->setFixedSize(300,50);
    sessioni->setFont(f);
    list<string> l = ctrl->daiSessioniClassi();
    sessioni->addItem("Seleziona sessione",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        sessioni->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(sessioni);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,200);
    temp.setWindowTitle("Rimuovi sessione");

    QString ris = "0";

    while( ris == "0" && temp.exec() == QDialog::Accepted){
        ris = sessioni->itemData(sessioni->currentIndex()).toString();
        if(ris == "0")
        QMessageBox::information(&temp,"Errore", "Deve selezionare una sessione");
    }
    if(temp.result() == QDialog::Accepted && ris != "0"){
        ris = ctrl->rimuoviSessioniClassi(ris);
                if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
                else{
                    QMessageBox::information(&temp,"", "Eliminata con successo");
                    reloadWindow();
                }
    }
}

void FinestrePreside::rimuoviIndirizzo()
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QComboBox* ind = new QComboBox(&temp);
    ind->setFixedSize(300,50);
    ind->setFont(f);
    list<string> l = ctrl->daiIndirizzoClassi();
    ind->addItem("Seleziona l'indirizzo",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        ind->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(ind);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,200);
    temp.setWindowTitle("Rimuovi indirizzo");

    QString ris = "0";

    while( ris == "0" && temp.exec() == QDialog::Accepted){
        ris = ind->itemData(ind->currentIndex()).toString();
        if(ris == "0")
        QMessageBox::information(&temp,"Errore", "Deve selezionare una sessione");
    }
    if(temp.result() == QDialog::Accepted && ris != "0"){
        ris = ctrl->rimuoviIndirizzoClassi(ris);
                if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
                else{
                    QMessageBox::information(&temp,"", "Eliminato con successo");
                    reloadWindow();
                }
    }
}

void FinestrePreside::rimuoviMateria() const
{
    popUpDialog temp(1,3);

    QFont f("Times",12);

    QComboBox* ind = new QComboBox(&temp);
    ind->setFixedSize(300,50);
    ind->setFont(f);
    list<string> l = ctrl->MaterieInsegnate();
    l.sort();
    ind->addItem("Seleziona la materia",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        ind->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(ind);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,200);
    temp.setWindowTitle("Rimuovi materia");

    QString ris = "0";

    while( ris == "0" && temp.exec() == QDialog::Accepted){
        ris = ind->itemData(ind->currentIndex()).toString();
        if(ris == "0")
        QMessageBox::information(&temp,"Errore", "Deve selezionare una sessione");
    }
    if(temp.result() == QDialog::Accepted && ris != "0"){
        ris = ctrl->RimuoviMateria(ris);
                if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
                else{
                    QMessageBox::information(&temp,"", "Eliminata con successo");
                }
    }
}

void FinestrePreside::assegnaMateriaAProf(const QString &prof) const
{
    popUpDialog temp(1,5);

    QFont f("Times",12);

    QLabel* lab = new QLabel("Scegli la materia:",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);

    QComboBox* ind = new QComboBox(&temp);
    ind->setFixedSize(300,50);
    ind->setFont(f);
    list<string> l = ctrl->MaterieInsegnate();
    l.sort();
    ind->addItem("Seleziona la materia",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        ind->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(ind);

    QComboBox* classe = new QComboBox(&temp);
    classe->setFixedSize(300,50);
    classe->setFont(f);
    vector<string> l2 = ctrl->Classi();
    std::sort(l2.begin(),l2.end());
    classe->addItem("Seleziona la classe",0);
    for(vector<string>::const_iterator it = l2.begin(); it != l2.end(); ++it)
        classe->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(classe);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,300);
    temp.setWindowTitle("Assegna classe");

    QString cla = classe->itemData(classe->currentIndex()).toString();
    QString mat = ind->itemData(ind->currentIndex()).toString();
    QString ris = "errore";

    while((cla == "0" || mat == "0" || ris != "")&& temp.exec() == QDialog::Accepted ){
       cla = classe->itemData(classe->currentIndex()).toString();
       mat = ind->itemData(ind->currentIndex()).toString();
        if(cla == "0" || mat == "0")
            QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
        else{
            ris = ctrl->aggiungiClasseEMateriaAProf(prof,cla,mat);
            if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
            else QMessageBox::information(&temp,"", "Classe e materia assegnata con successo!");
        }
    }
}

void FinestrePreside::RimuoviMateriaAProf(const QString &prof) const
{
    popUpDialog temp(1,5);

    QFont f("Times",12);

    QLabel* lab = new QLabel("Scegli la materia:",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);

    QComboBox* ind = new QComboBox(&temp);
    ind->setFixedSize(300,50);
    ind->setFont(f);
    list<string> l = ctrl->MaterieInsegnate();
    l.sort();
    ind->addItem("Seleziona la materia",0);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
        ind->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(ind);

    QComboBox* classe = new QComboBox(&temp);
    classe->setFixedSize(300,50);
    classe->setFont(f);
    vector<string> l2 = ctrl->Classi();
    std::sort(l2.begin(),l2.end());
    classe->addItem("Seleziona la classe",0);
    for(vector<string>::const_iterator it = l2.begin(); it != l2.end(); ++it)
        classe->addItem(QString::fromStdString(*it), QString::fromStdString(*it));
    temp.push_back_Widget(classe);

    QPushButton* b = new QPushButton("Salva",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    b = new QPushButton("Annulla",&temp);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(reject()));
    temp.push_back_Widget(b);

    temp.setFixedSize(400,300);
    temp.setWindowTitle("Togli classe a prof");

    QString cla = classe->itemData(classe->currentIndex()).toString();
    QString mat = ind->itemData(ind->currentIndex()).toString();
    QString ris = "errore";

    while((cla == "0" || mat == "0" || ris != "")&& temp.exec() == QDialog::Accepted ){
        cla = classe->itemData(classe->currentIndex()).toString();
        mat = ind->itemData(ind->currentIndex()).toString();
        if(cla == "0" || mat == "0")
            QMessageBox::information(&temp,"Errore", "Attenzione, tutti i campi sono obligatori");
        else{
            ris = ctrl->rimuoviMateriaEClasseAProf(prof,cla,mat);
            if(ris != "")
                QMessageBox::information(&temp,"Errore", ris);
            else QMessageBox::information(&temp,"", "Classe e materia tolte con successo!");
        }
    }
}
