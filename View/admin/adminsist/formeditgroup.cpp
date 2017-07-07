#include "formeditgroup.h"
#include "../../../Controller/controlleradminsistema.h"
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

void FormEditGroup::InsertInCategoria()
{
    const QString& cat = ctrl->daiGroupCateg(nomeGruppo);
    categoria->addItem(cat,cat);
    list<string> l = ctrl->GroupsCathegory();
    for(list<string>::const_iterator it = l.begin(); it != l.end(); ++it){
        const QString& cath = QString::fromStdString(*it);
        if(cath != cat)
            categoria->addItem(cath,cath);
    }
}

QString FormEditGroup::inputCorretto() const
{
    if(name->text() == "" || descrizione->toPlainText() == "" )
        return "Tutti i campi sono obbligatori";
    return "";
}

FormEditGroup::FormEditGroup(ControllerAdminSistema * c, const QString& group, QWidget* parent) : QDialog(parent), ctrl(c),
 name(new QLineEdit(this)), descrizione(new QTextEdit(this)), categoria(new QComboBox(this)), nomeGruppo(group)
{
    QFont f1("Times",14);
    f1.setBold(true);
    QFont f2("Times",12);

    QVBoxLayout* lay = new QVBoxLayout(this);

    QLabel* tit = new QLabel("Nome gruppo:", this);
    tit->setFont(f1);
    lay->addWidget(tit,0,Qt::AlignTop);

    name->setText(nomeGruppo);
    name->setFont(f2);
    lay->addWidget(name,0,Qt::AlignTop);

    tit = new QLabel("Descrizione del gruppo:", this);
    tit->setFont(f1);
    lay->addWidget(tit,0,Qt::AlignTop);

    descrizione->setText(ctrl->daiGroupDescr(nomeGruppo));
    descrizione->setFont(f2);
    lay->addWidget(descrizione,0,Qt::AlignTop);

    tit = new QLabel("Categoria del gruppo:", this);
    tit->setFont(f1);
    lay->addWidget(tit,0,Qt::AlignTop);
    InsertInCategoria();
    categoria->setFont(f2);

    lay->addWidget(categoria,0,Qt::AlignTop);

    QPushButton* b = new QPushButton("Salva", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(salva()));
    lay->addWidget(b,0,Qt::AlignTop);

    b = new QPushButton("Annulla", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(reject()));
    lay->addWidget(b,1,Qt::AlignTop);


    setLayout(lay);
}

void FormEditGroup::salva()
{
    const QString& ris = inputCorretto();

    if(ris != "")
        QMessageBox::information(0,"ERRORE", ris);
    else{
        const QString& na = name->text();
        const QString& des = descrizione->toPlainText();
        const QString& cat = categoria->itemData(categoria->currentIndex()).toString();
        if(ctrl->editGroup(nomeGruppo,na,des, cat)){
        QMessageBox::information(0,"","Gruppo modificato con successo");
        close();
        }
        else QMessageBox::information(0,"ERRORE!","E' avvenuto un errore, potrebbe essere:\n"
                                                     "-un errore con i file"
                                                     "-ha inserito uno dei seguenti caratteri vietati: < & \""
                                                     "-Non ha inserito nessun carattere");
    }
}
