#include "inviamessdialog.h"
#include "../../Controller/controllerimpiegato.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QCompleter>
#include <QMessageBox>
#include <QDate>

InviaMessDialog::InviaMessDialog(ControllerImpiegato *ptr, QDialog *parent):QDialog(parent),
    destinatario(new QLineEdit(this)), oggetto(new QLineEdit(this)), messaggio(new QTextEdit(this)),
    ctrl(ptr), sug(0), contatto(new QComboBox(this))
{
    BodyAndFooter();
    setFixedSize(700,700);
    setWindowTitle("Scrivi un nuovo messaggio");
}

void InviaMessDialog::BodyAndFooter()
{
    QVBoxLayout* lay = new QVBoxLayout;

    QLabel* title = new QLabel("Destinatario:", this);
    lay->addWidget(title);
    QHBoxLayout* lay2= new QHBoxLayout;
    InserisciContatti();

    connect(contatto, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLineEditText()));
    lay2->addWidget(destinatario);
    lay2->addWidget(contatto);
    lay->addLayout(lay2);

    title = new QLabel("Oggetto:");
    lay->addWidget(title);
    lay->addWidget(oggetto);

    title = new QLabel("Mesaggio:");
    lay->addWidget(title);
    lay->addWidget(messaggio);

    lay2 = new QHBoxLayout;
    QPushButton*b = new QPushButton("Invia messaggio", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(SendMessage()));
    lay2->addWidget(b);
    b = new QPushButton("Annulla", this);
    connect(b,SIGNAL(clicked(bool)), this, SLOT(reject()));
    lay2->addWidget(b);
    lay->addLayout(lay2);

    setLayout(lay);
}

void InviaMessDialog::InserisciContatti()
{
    int tot = ctrl->totContacts();
    QString s1;
    QString s2;
    QStringList l;
    contatto->addItem("Cerca un contatto",-1);
    for(int i=0; i<tot;++i){
        s1 = ctrl->daiNomeContatto(i);
        s2 = ctrl->daiMailContatto(i);
        contatto->addItem(s2+": "+s1,i);
        l.append(s2);
    }
    sug=new QCompleter(l,this);
    sug->setCaseSensitivity(Qt::CaseInsensitive);
    destinatario->setCompleter(sug);

}

void InviaMessDialog::Reset() const
{
    foreach(QLineEdit* child, findChildren<QLineEdit*>()) {
        child->clear();
    }
    foreach(QComboBox* child, findChildren<QComboBox*>()) {
        child->setCurrentIndex(0);
    }
    foreach(QTextEdit* child, findChildren<QTextEdit*>()) {
        child->clear();
    }
}

void InviaMessDialog::changeLineEditText()
{
    int i = contatto->itemData(contatto->currentIndex()).toInt();
    if(i != -1)
    destinatario->setText(ctrl->daiMailContatto(i));
    else
        destinatario->setText("");
}

void InviaMessDialog::SendMessage()
{
    const QString& check =ctrl->SendNewMessage(QDate::currentDate().toString("dd/MM/yyyy"),
                                               destinatario->text(),oggetto->text(),
                                               messaggio->toPlainText());
    if(check == "")
    {
        QMessageBox::information(this,"","Inviato con successo!");
        Reset();
    }
    else{
        QMessageBox::information(this,"",check);
    }
}
