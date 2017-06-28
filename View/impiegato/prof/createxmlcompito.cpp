#include "createxmlcompito.h"
#include "../../../Controller/controllerprof.h"
#include "domandarispmult.h"
#include "domandaaperta.h"
#include "createcompito.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDate>
#include <QFileInfo>
#include <QLineEdit>



bool createXMLCompito::isOk()
{
    QLabel* error = giveError();

    if(createFileCompito::isOk()){
    if(totDom.size() == 0){
        error->setText("Errore: Si può creare un nuovo compito con almeno una domanda");
        return false;
     }
    else{
        int conta = 0;
        for(QVector<DomandeCompito*>::const_iterator it = totDom.begin();
        it != totDom.end(); ++it)
        {
        ++conta;
        QString errore;
        if(!(*it)->isOK(errore)){
            error->setText("Errore domanda "+QString::number(conta)+" : "+errore);
            return false;
        }

        }
    return domandeCorrette();
    }
    }
    return false;

}

void createXMLCompito::aggiungiDomandaRispMult()
{
    DomandaRispMult* d = new DomandaRispMult(this);
    totDom.push_back(d);
    d->setIntoCreateWidg();
    d->setStyleSheet("QGroupBox{border: 2px solid green;}");
    d->setTitle("Domanda "+QString::number(totDom.size()));
    giveLayout()->insertWidget(giveLayout()->count()-4,d, 1,Qt::AlignTop);
}

void createXMLCompito::aggiungiDomandaAperta()
{
    DomandaAperta* d = new DomandaAperta(this);
    totDom.push_back(d);
    d->setIntoCreateWidg();
    d->setStyleSheet("QGroupBox{border: 2px solid green;}");
    d->setTitle("Domanda "+QString::number(totDom.size()));
    giveLayout()->insertWidget(giveLayout()->count()-4,d, 1,Qt::AlignTop);
}

void createXMLCompito::rimuoviUltimaDomanda()
{
    if(totDom.size() > 0){
    DomandeCompito* temp = totDom[totDom.size()-1];
    totDom.pop_back();
    delete temp;
    }
}

bool createXMLCompito::domandeCorrette() const
{
    QLabel* error = giveError();
    ControllerProf* ctrl = giveController();
    QRegExp check("[a-z,A-Z,0-9]");
    for(QVector<DomandeCompito*>:: const_iterator it = totDom.begin(); it != totDom.end(); ++ it){
        DomandaRispMult* p = dynamic_cast<DomandaRispMult*>(*it);
        if(p){
            error->setText(ctrl->checkForbiddenCharacters(p->getDomanda()));
            if(error->text()!= "")
                return false;
            if(ctrl->HasNoChar(p->getDomanda())){
                error->setText("Tutti i campi sono obbligatori");
                return false;
            }
            QList<string> l = p->getRisposte();
            for(QList<string>::const_iterator it = l.begin(); it!= l.end(); ++it){
                error->setText(ctrl->checkForbiddenCharacters(QString::fromStdString(*it)));
                if(error->text()!= "")
                    return false;
                if(ctrl->HasNoChar(QString::fromStdString(*it))){
                    error->setText("Tutti i campi sono obbligatori");
                    return false;
                }
            }
        }
        else{
            DomandaAperta* p2 = dynamic_cast<DomandaAperta*>(*it);
            if(p2){
                error->setText(ctrl->checkForbiddenCharacters(p2->getDomanda()));
                if(error->text()!= "")
                    return false;
                if(error->text() == "" && ctrl->HasNoChar(p2->getDomanda())){
                    error->setText("Tutti i campi sono obbligatori");
                    return false;
                }
            }
        }
    }
    return true;
}

bool createXMLCompito::salva()
{
    ControllerProf* ctrl = giveController();
    QLabel* error = giveError();
   if(isOk()){
       const QString& path = ctrl->createNewCompitoXml(QDate::currentDate().toString("dd/MM/yyyy"),
                                               giveTitolo()->text(),
                                               giveDescr()->toPlainText(),
                                               giveMateria()->itemData(giveMateria()->currentIndex()).toString(),
                                               giveClasse()->itemData(giveClasse()->currentIndex()).toString());
       if(path != ""){
            for(QVector<DomandeCompito*>:: iterator it = totDom.begin(); it != totDom.end(); ++ it){
                DomandaRispMult* p = dynamic_cast<DomandaRispMult*>(*it);
                if(p){
                    QString check = ctrl->aggiungiDomandaARispMult(path,p->getDomanda(),
                                                                   p->getRisposte().toStdList(),
                                                                   p->getRisposteCorrette().toStdList());
                    if(check != "")
                    {
                        error->setText(check);
                        return false;
                    }
                }
                else{
                    DomandaAperta* p2 = dynamic_cast<DomandaAperta*>(*it);
                    QString check = ctrl->aggiungiDomandaAperta(path,p2->getDomanda());
                    if(p2 && check != ""){
                        error->setText(check);
                        return false;
                    }
                }
            }
            return true;

       }
       else error->setText(path);
   }
    return false;
}

createXMLCompito::createXMLCompito(ControllerProf *c, QWidget *parent):createFileCompito(c,parent)
{
    loadHeader();
    QVBoxLayout* lay = giveLayout();

    QPushButton* b = new QPushButton("Aggiungi domanda aperta", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiDomandaAperta()));
    lay->addWidget(b,0,Qt::AlignTop);
    b = new QPushButton("Aggiungi domanda a risposta multipla", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiDomandaRispMult()));
    lay->addWidget(b,0,Qt::AlignTop);
    b = new QPushButton("Rimuovi l'ultima domanda aggiunta", this);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rimuoviUltimaDomanda()));
    lay->addWidget(b,1,Qt::AlignTop);

    b = new QPushButton("Salva modifiche", this);
    lay->addWidget(b,0,Qt::AlignTop);
    CreateCompito* grandParent = giveGrandParent();
    if(grandParent)
    connect(b,SIGNAL(clicked(bool)),grandParent,SLOT(salvaXml()));

    setWindowTitle("Aggiungi compito xml");

}

