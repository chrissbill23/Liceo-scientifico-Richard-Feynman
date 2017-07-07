#include "updatelogo.h"
#include "../../../Controller/controlleradminbiblio.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>

updateLogo::updateLogo(ControllerAdminBiblio *c, QWidget *parent) : QDialog(parent), path(new QLineEdit(this)),ctrl(c),
    lay(new QVBoxLayout(this))
{
    QLabel* lab = new QLabel("Carica logo (formato jpg) :",this);
    QFont f("Times",14);
    f.setBold(true);

    lab->setFont(f);
    lay->addWidget(lab,0,Qt::AlignTop);

    path->setFont(QFont("Times",12));
    lay->addWidget(path,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Sfoglia", this);
    b->setFont(QFont("Times",12));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(carica()));
    lay->addWidget(b,0,Qt::AlignTop);

    b = new QPushButton("Salva", this);
    b->setFont(QFont("Times",12));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salva()));
    lay->addWidget(b,0,Qt::AlignTop);

    b = new QPushButton("Annula", this);
    b->setFont(QFont("Times",12));
    lay->addWidget(b,1,Qt::AlignTop);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(close()));

    setLayout(lay);

}

void updateLogo::salva()
{
    if (path->text() == ""){
        QMessageBox::information(0,"Errore","Devi Selezionare un file");
    }
    else{
        if(ctrl->cambiaLogo(path->text()))
            QMessageBox::information(0,"","Salvato con successo");
        else QMessageBox::information(0,"Errore","Errore fatale nel salvataggio");
    }
}

void updateLogo::carica() const
{
    QString fileName = QFileDialog::getOpenFileName(path,
            tr("Seleziona il file"), "",
            tr(" (*.jpg)"));

        if (fileName.isEmpty())
            return;
        else {
            path->setText(fileName);
        }
}
