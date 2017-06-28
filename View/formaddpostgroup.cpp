#include "formaddpostgroup.h"
#include "../Controller/controllergruppouser.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDate>
#include <QLabel>

FormAddPostGroup::FormAddPostGroup(ControllerGruppoUser *c, const QString &group, QWidget *parent) : QDialog(parent), ctrl(c),
    titolo(new QLineEdit(this)), testo(new QTextEdit(this)), groupName(group)
{
    QFont f("Times",14);
    titolo->setMaxLength(70);
    titolo->setFixedHeight(50);
    titolo->setFont(f);
    titolo->setPlaceholderText("Inserire il titolo del post( massimo di 70 caratteri)");
    QLabel* testoTitle = new QLabel("Inserire il testo del post (3000 caratteri al massimo", testo);
    testoTitle->setFont(f);
    testo->setFont(f);
    testo->setFixedHeight(500);

    QPushButton* b = new QPushButton("Crea post", this);
    connect(b,SIGNAL(clicked(bool)), this, SLOT(salva()));
    QPushButton* b2 = new QPushButton("Annulla", this);
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(close()));

    QVBoxLayout* lay = new QVBoxLayout(this);

    lay->addWidget(titolo,0,Qt::AlignTop);
    lay->addWidget(testoTitle, 0, Qt::AlignTop);
    lay->addWidget(testo,0,Qt::AlignTop);
    lay->addWidget(b,0,Qt::AlignTop);
    lay->addWidget(b2,1,Qt::AlignTop);

    setWindowTitle("Crea post");

    setLayout(lay);
}

void FormAddPostGroup::salva()
{
    if(QMessageBox::information(this,"ATTENZIONE!", "Attenzione: non sarà più possibile\n"
                                "modificare questo post almeno di eliminarlo.\n"
                                "Sei sicuro di voler continuare?",QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes){
        if(titolo->text() =="" || testo->toPlainText() == "")
            QMessageBox::information(this,"Errore","Il titolo e il testo del post vanno inseriti");
        else{
        const QString& data = QDate::currentDate().toString("dd/MM/yyyy");
        const QString& title = titolo->text();
        const QString& text = testo->toPlainText();
        const QString& check = ctrl->addPost(groupName,data,title,text);
        if(check ==""){
            QMessageBox::information(this,"", "Salvato con successo!");
            close();
        }
        else QMessageBox::information(this,"Errore",check);
        }
    }
}
