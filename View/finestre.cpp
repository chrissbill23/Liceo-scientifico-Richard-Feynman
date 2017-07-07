#include "finestre.h"
#include "biblio/homebiblio.h"
#include "popupdialog.h"
#include "../Controller/Controller.h"
#include "./biblio/bibliobutton.h"
#include "../Modello/filexml.h"
#include <QLineEdit>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>

Finestre::Finestre(Controller* c,QWidget *parent): QWidget(parent),ctrl(c)
                                                                {
}

void Finestre::setStyleSheet(const QString &s)
{
    QWidget::setStyleSheet(s);
}

Controller *Finestre::getController() const
{
    return ctrl;
}

void Finestre::signout()
{
    ctrl->signout();
}

void Finestre::HomePageBiblio() const
{
    ctrl->ShowNewWindow(new HomeBiblio(ctrl));
}

void Finestre::TornaIndietro() const
{
    ctrl->getPrevFinestra();
}

void Finestre::show()
{
    showMaximized();
}

void Finestre::viewPdfFile(const QString & path) const
{
     QDesktopServices::openUrl(QUrl("file:"+path, QUrl::TolerantMode));
}


void Finestre::viewInfoLibro(const QString& code) const
{
    popUpDialog temp(1,17);
    temp.setFixedSize(600,650);

    QLabel* lab = new QLabel(&temp);
    lab->setFixedSize(temp.width()-100,300);
    lab->setStyleSheet("color: #29abe2;");
    const QString& path = ctrl->daiCopertinaLibro(code);
    if(path != ""){
    lab->setPixmap(QPixmap(path));
    lab->setScaledContents(true);
    }
    else {
        lab->setText("Nessuna copertina per questo libro");
        lab->setFont(QFont("Times", 15));
    }
    temp.push_back_Widget(lab);

    QFont f("Times",14);
    f.setBold(true);
    QFont f2("Times",12);
    lab = new QLabel("Titolo: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    const QString& tit = ctrl->daiTitoloLibro(code);
    lab = new QLabel(tit, &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);
    temp.setWindowTitle(tit);

    lab = new QLabel("Autore: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->daiAutoreLibro(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Descrizione: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->daiDescrizioneLibro(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Anno Edizione: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(ctrl->daiAnnoEdizioneLibro(code), &temp);
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    lab = new QLabel("Categorie libro: ",&temp);
    lab->setFont(f);
    temp.push_back_Widget(lab);
    lab = new QLabel(&temp);
    lab->setFixedWidth(temp.width()-100);
    list<string> l = ctrl->daiCategorieLibro(code);
        for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it)
            lab->setText(lab->text()+QString::fromStdString(*it)+". ");
    lab->setFont(f2);
    temp.push_back_Widget(lab);

    temp.exec();

}

void Finestre::viewInfoClasse(const QString &classe) const
{
    const filexml& file = ctrl->giveSchedaClasse(classe);
    const QString& nome = QString::fromStdString(file.daiTestoIn("nomeClasse"));
    int materie = file.totNodi("materia");
    int alun = file.totNodi("NomeUtente");

    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);

    popUpDialog temp(1,materie+5);
    QLabel* tit = new QLabel("Nome classe:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(nome,&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    tit = new QLabel("Totale alunni:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    tit = new QLabel(QString::number(alun),&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);

    tit = new QLabel("Materie insegnate:",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    for(int i = 0; i < materie; ++i){
        const QString& mat = QString::fromStdString(file.daiTestoIn("NomeMateria",i));
        tit = new QLabel(mat,&temp);
        tit->setFont(f2);
        temp.push_back_Widget(tit);

    }

    temp.setFixedSize(500,500);
    temp.setWindowTitle("Scheda classe "+classe);

    temp.exec();

}

void Finestre::viewMaterieInsegnate() const
{

    list<string> li = ctrl->MaterieInsegnate();
    li.sort();

    QFont f("Times",15);
    f.setBold(true);
    QFont f2("Times",12);

    popUpDialog temp(1,li.size()+1);
    QLabel* tit = new QLabel(QString::number(li.size())+" materie trovate",&temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);

    for(list<string>::const_iterator it = li.begin(); it != li.end(); ++it){
    tit = new QLabel(QString::fromStdString(*it),&temp);
    tit->setFont(f2);
    temp.push_back_Widget(tit);
    }
    temp.setFixedSize(500,550);
    temp.setWindowTitle("Materie insegnate");
    temp.exec();
}

void Finestre::viewLibriInCateg(const QString &cath)
{
    list<string> l = ctrl->daiCodiciLibriCat(cath);
    popUpDialog temp(3,l.size()+1);
    temp.setWindowTitle(cath);

    QLabel* lab = new QLabel(QString::number(l.size())+" libri trovati");
    lab->setFont(QFont("Times",14));
    temp.push_back_Widget(lab);
    temp.goToNextRow();

    QFont f("Times",12);
    f.setUnderline(true);
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        const QString& libr = QString::fromStdString(*it);
        lab = new QLabel(ctrl->daiTitoloLibro(libr), &temp);
        lab->setFont(f);
        temp.push_back_Widget(lab);


        bibliobutton* b = new bibliobutton("vedi libro", QString::fromStdString(*it),false,"",this);
        b->setFont(QFont("Times", 9));
        b->setFixedSize(100,30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));
        temp.push_back_Widget(b);

        b = new bibliobutton("info libro", QString::fromStdString(*it),false,"",this);
        b->setFont(QFont("Times", 9));
        b->setFixedSize(100,30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #336699; "
                         "border-radius: 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
        temp.push_back_Widget(b);

    }
    temp.exec();
}

void Finestre::cambiaPassword()
{
    popUpDialog temp(1,4);

    QFont f("Times",13);
    QLabel* tit = new QLabel("La password:\n"
                             "-deve avere un minimo di 8 caratteri e al più 15 caratteri.\n"
                             "-Non puo' contenere spazi, tab, e i caratteri > < & \"", &temp);
    tit->setFont(f);
    temp.push_back_Widget(tit);


    QLineEdit* pass = new QLineEdit(&temp);
    pass->setPlaceholderText("Inserisci la nuova password");
    pass->setFixedSize(400,50);
    pass->setMaxLength(15);
    pass->setEchoMode(QLineEdit::Password);
    pass->setFont(f);
    temp.push_back_Widget(pass);

    QLineEdit* repass = new QLineEdit(&temp);
    repass->setPlaceholderText("Reinserisci la password");
    repass->setFixedSize(400,50);
    repass->setEchoMode(QLineEdit::Password);
    repass->setMaxLength(15);
    repass->setFont(f);
    temp.push_back_Widget(repass);

    QPushButton* b = new QPushButton("Salva",&temp);
    b->setFixedSize(400,30);
    connect(b,SIGNAL(clicked(bool)),&temp,SLOT(accept()));
    temp.push_back_Widget(b);

    temp.setFixedSize(650,400);
    temp.setWindowTitle("Cambio password");
    while(temp.exec() == QDialog::Accepted && ( pass->text() == "" || repass->text() == "")){
        if( pass->text() != "" ){
            if(pass->text().size() < 8 || pass->text().size() > 15)
               QMessageBox::information(&temp,"Errore", "La password deve essere almeno 8 caratteri\n"
                                                       "e al massimo 15 caratteri");
        }
        else
        QMessageBox::information(&temp,"Errore", "Tutti campi sono obbligatori");
    }

    if(temp.result() == QDialog::Accepted ){
        const QString& passText = pass->text();
        const QString& repassText = repass->text();
        if(passText.size() < 8 || repassText.size() < 8 ){
            QMessageBox::information(&temp,"ERRORE", "Password non corretta.\n"
                                                     "Sono richiesti almeno 8 caratteri e/o cifre");
            return;
        }
        if(passText == repassText){
         if(ctrl->CambioPassword(passText)){
             QMessageBox::information(&temp,"","Il cambio password è avvenuto con successo\n"
                                           "Le chiediamo di rieffettuare l'accesso");
             signout();
         }
         else QMessageBox::information(&temp,"ERRORE", "E' avvenuto un errore, verifica di aver inserito\n"
                                                       "correttamente la password. I caratteri seguenti sono vietati:"
                                                       "< & \" spazio tab");
        }
        else QMessageBox::information(&temp,"ERRORE", "Password non corretta");

    }

}

void Finestre::cambiafotoProfilo()const
{
    QString fileName = QFileDialog::getOpenFileName(0,
            tr("Seleziona il file"), "",
            tr(" (*.jpg)"));

        if (fileName.isEmpty())
            return;
        else {
            if(ctrl->CambiaFotoProfilo(fileName))
            QMessageBox::information(0, "", "Foto profilo cambiata con successo.\n"
                                            "Rifai l'accesso per visualizzare il cambiamento.");
            else QMessageBox::information(0, "ERRORE!", "Errore con i file");
        }
}
