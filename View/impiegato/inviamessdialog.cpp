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
    setFixedSize(700,600);
    setWindowTitle("Scrivi un nuovo messaggio");
}

void InviaMessDialog::BodyAndFooter()
{
    QVBoxLayout* lay = new QVBoxLayout;

    QFont f("Times", 10);
    f.setBold(true);
    QLabel* title = new QLabel("Destinatario:", this);
    title->setFont(f);
    lay->addWidget(title);
    QHBoxLayout* lay2= new QHBoxLayout;
    InserisciContatti();

    destinatario->setFixedHeight(30);
    destinatario->setMaxLength(200);
    lay2->addWidget(destinatario);
    contatto->setFixedHeight(30);
    lay2->addWidget(contatto);
    connect(contatto, SIGNAL(currentIndexChanged(int)), this, SLOT(changeLineEditText()));

    lay->addLayout(lay2);

    title = new QLabel("Oggetto:");
    title->setFont(f);
    lay->addWidget(title);
    oggetto->setFixedHeight(30);
    oggetto->setMaxLength(50);
    oggetto->setPlaceholderText("max 50 caratteri");
    lay->addWidget(oggetto);

    title = new QLabel("Messaggio:");
    title->setFont(f);
    lay->addWidget(title);
    lay->addWidget(messaggio);

    lay2 = new QHBoxLayout;
    QPushButton*b = new QPushButton("Invia messaggio", this);
    b->setFixedHeight(40);
    b->setStyleSheet("QPushButton{background-color: #264d73; "
                     "color: white; border-radius: 5px;}"
                     "QPushButton:hover{"
                            "color: #29abe2;}"
                            "QPushButton:pressed {"
                            "color:#660000;}");
    connect(b,SIGNAL(clicked(bool)),this,SLOT(SendMessage()));
    lay2->addWidget(b);
    b = new QPushButton("Annulla", this);
    b->setFixedHeight(40);
    b->setStyleSheet("QPushButton{"
                     "background-color: #990000;"
                     " border-radius: 5px; color: white;}"
                     "QPushButton:hover{"
                            "color: red;}"
                            "QPushButton:pressed {"
                            "color:#660000;}");
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
    contatto->addItem("Scegli contatto",-1);
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
