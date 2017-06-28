#include "finestreadminbiblio.h"
#include "insertnewbook.h"
#include "updateinfobook.h"
#include "updatelogo.h"
#include "../../popupdialog.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>

FinestreAdminBiblio::FinestreAdminBiblio(ControllerAdminBiblio* ptr, QWidget *parent): finestreAdmin(ptr,parent), ctrl(ptr){}

ControllerAdminBiblio *FinestreAdminBiblio::getController() const
{
    return ctrl;
}

void FinestreAdminBiblio::Header()
{
    finestreAdmin::Header();
    QGridLayout* layout = giveLayout();

    QPushButton*b = new QPushButton("Inserici un nuovo libro/giornale", this);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(CaricaNewBook()));
    layout->addWidget(b,0,0,1,1,Qt::AlignLeft);

    b = new QPushButton("Aggiungi categoria", this);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addCategoria()));
    layout->addWidget(b,0,1,1,1,Qt::AlignLeft);


    b = new QPushButton("Cambia logo", this);
    b->setStyleSheet("QPushButton{"
                            "background-color: green;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
    b->setFixedSize(300, 40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(cambiaLogo()));

    layout->addWidget(b,0,2,1,1,Qt::AlignLeft);



}

void FinestreAdminBiblio::CaricaNewBook()
{
    InsertNewBook temp(ctrl);
    temp.setFixedSize(700,700);
    temp.exec();
    reloadWindow();
}

void FinestreAdminBiblio::addCategoria()
{
        popUpDialog temp(1,3);
        temp.setFixedSize(500,500);
        temp.setWindowTitle("Aggiungi categoria");

        QLabel* lab = new QLabel("Inserire il nome della categoria", &temp);
        lab->setFont(QFont("Times",14));
        temp.push_back_Widget(lab);

        QLineEdit* nome = new QLineEdit(&temp);
        nome->setFixedHeight(50);
        nome->setFont(QFont("Times",13));
        temp.push_back_Widget(nome);

        QPushButton* b = new QPushButton("Aggiungi",&temp);
        connect(b, SIGNAL(clicked(bool)), &temp, SLOT(accept()));

        temp.push_back_Widget(b);

        if(temp.exec() == QDialog::Accepted){
            const QString cat = nome->text();
            if(cat != "" && !ctrl->esisteCategoria(cat)){
                if(ctrl->aggiungiCategoria(cat)){
                    QMessageBox::information(&temp,"","Salvato con successo");
                    reloadWindow();
                }
                else QMessageBox::information(&temp,"Errore","Errore fatale nel salvataggio");
            }
            else QMessageBox::information(&temp,"Errore","E' probabile che la categoria inserita esiste già.\n"
                                                         "La preghiamo di riprovare con un altro nome di categoria");
        }
}

void FinestreAdminBiblio::eliminaLibro(const QString &codice)
{
    if(ctrl->eliminaLibro(codice)){
       QMessageBox::information(this,"","Eliminato con successo");
       reloadWindow();
    }
    else QMessageBox::information(this,"Errore","Errore fatale nella cancellazione");
}

void FinestreAdminBiblio::eliminaCateg(const QString &cath)
{
    if(ctrl->eliminaCategoria(cath)){
       QMessageBox::information(this,"","Eliminato con successo");
       reloadWindow();
    }
    else QMessageBox::information(this,"Errore","Errore fatale nella cancellazione");
}

void FinestreAdminBiblio::updateInfoLibro(const QString& code)
{
    updateInfoBook temp(code, ctrl);
    temp.setFixedSize(700,700);
    temp.exec();
    reloadWindow();
}

void FinestreAdminBiblio::aggiungiPrimoPiano(const QString &code)
{
    const QString& ris = ctrl->aggiungiInPrimoPiano(code);
    if(ris == ""){
       QMessageBox::information(this,"","Aggiunto al primo piano");
       reloadWindow();
    }
    else QMessageBox::information(this,"Errore",ris);
}

void FinestreAdminBiblio::elimDaPrimoPiano(const QString &code)
{
    if(ctrl->rimuoviLibroDaPrimoPiano(code)){
       QMessageBox::information(this,"","Rimosso da primo piano con successo!");
       reloadWindow();
    }
    else QMessageBox::information(this,"Errore","Errore durente la rimossione");
}

void FinestreAdminBiblio::cambiaLogo()
{
    updateLogo temp(ctrl);

    temp.setFixedSize(400,400);
    temp.exec();


}

void FinestreAdminBiblio::viewPdfFile(const QString & path) const
{
    const QString& path2 = getController()->daiPercorsoLibro(path);
    Finestre::viewPdfFile(path2);
}
