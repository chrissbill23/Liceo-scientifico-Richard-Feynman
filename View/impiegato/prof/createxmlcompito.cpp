#include "createxmlcompito.h"
#include "../../../Controller/controllerprof.h"
#include "../../../Modello/Utente.h"
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
        error->setText("Errore: il compito deve avere almeno una domanda");
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
    for(QVector<DomandeCompito*>:: const_iterator it = totDom.begin(); it != totDom.end(); ++ it){
        DomandaRispMult* p = dynamic_cast<DomandaRispMult*>(*it);
        if(p){
            error->setText(QString::fromStdString(Utente::checkForbiddenCharacters(p->getDomanda().toStdString())));
            if(error->text()!= "")
                return false;
            if(Utente::HasNoChar(p->getDomanda().toStdString())){
                error->setText("Tutti i campi sono obbligatori");
                return false;
            }
            QList<string> l = p->getRisposte();
            for(QList<string>::const_iterator it = l.begin(); it!= l.end(); ++it){
                error->setText(QString::fromStdString(Utente::checkForbiddenCharacters(*it)));
                if(error->text()!= "")
                    return false;
                if(Utente::HasNoChar(*it)){
                    error->setText("Tutti i campi sono obbligatori");
                    return false;
                }
            }
        }
        else{
            DomandaAperta* p2 = dynamic_cast<DomandaAperta*>(*it);
            if(p2){
                error->setText(QString::fromStdString(Utente::checkForbiddenCharacters(p2->getDomanda().toStdString())));
                if(error->text()!= "")
                    return false;
                if(error->text() == "" && Utente::HasNoChar(p2->getDomanda().toStdString())){
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
       QString checkError = "";
       const QString& path = ctrl->createNewCompitoXml(QDate::currentDate().toString("dd/MM/yyyy"),
                                               giveTitolo()->text(),
                                               giveDescr()->toPlainText(),
                                               giveMateria()->itemData(giveMateria()->currentIndex()).toString(),
                                               giveClasse()->itemData(giveClasse()->currentIndex()).toString(), checkError);
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
       else error->setText(checkError);
   }
    return false;
}

createXMLCompito::createXMLCompito(ControllerProf *c, QWidget *parent):createFileCompito(c,parent)
{
    loadHeader();
    QVBoxLayout* lay = giveLayout();

    QPushButton* b = new QPushButton("Nuova domanda aperta", this);
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiDomandaAperta()));
    lay->addWidget(b,0,Qt::AlignTop);
    b = new QPushButton("Nuova domanda a risposta multipla", this);
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiDomandaRispMult()));
    lay->addWidget(b,0,Qt::AlignTop);
    b = new QPushButton("Rimuovi ultima domanda", this);
    b->setFixedHeight(40);
    b->setStyleSheet("QPushButton{ color: white;"
                          "background-color: #990000;"
                          " border-radius: 5px;}"
                          "QPushButton:pressed {"
                          " background-color:#660000;}");
    b->setCursor(QCursor(Qt::PointingHandCursor));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(rimuoviUltimaDomanda()));
    lay->addWidget(b,1,Qt::AlignTop);

    b = new QPushButton("Salva", this);
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    lay->addWidget(b,0,Qt::AlignTop);
    CreateCompito* grandParent = giveGrandParent();
    if(grandParent)
    connect(b,SIGNAL(clicked(bool)),grandParent,SLOT(salvaXml()));

    setWindowTitle("Nuovo compito xml");

}

