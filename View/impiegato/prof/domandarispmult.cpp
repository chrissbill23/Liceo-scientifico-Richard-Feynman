#include "domandarispmult.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

void DomandaRispMult::aggiungiRisposta()
{
    QFont f("Times",11);
    QLineEdit* risposta = new QLineEdit(this);
    risposta->setFixedHeight(30);
    risposta->setFont(f);
    totRisposte.push_back(risposta);
    QLabel* lab = new QLabel(QString::number(totRisposte.size()),risposta);
    lab->setFont(f);
    QCheckBox* ch = new QCheckBox(risposta);
    rispCorrette.push_back(ch);
    lay->addWidget(lab,totRisposte.size()+2,0,1,1,Qt::AlignLeft);
    lay->addWidget(risposta,totRisposte.size()+2,1);
    lay->addWidget(ch,totRisposte.size()+2,2,1,1,Qt::AlignCenter);
}

DomandaRispMult::DomandaRispMult(QWidget *parent): DomandeCompito(parent), domanda(0),lay(0)
{

}

void DomandaRispMult::setIntoCreateWidg()
{
    domanda = new QLineEdit(this);
    domanda->setFixedHeight(30);
    lay = new QGridLayout(this);
    lay->addWidget(domanda,0,0,1,3);

    QPushButton* b = new QPushButton("Aggiungi risposta", this);
    b->setFixedSize(200,40);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(aggiungiRisposta()));
    lay->addWidget(b, 1,0,1,2,Qt::AlignLeft);

    lay->addWidget(new QLabel("Risposta corretta"), 1,2);

    aggiungiRisposta();
    aggiungiRisposta();

}

void DomandaRispMult::setIntoAnswWidg()
{
      if(!lay)
          lay = new QGridLayout(this);
      QLabel* lab = new QLabel(Domanda,this);
      lab->setFont(QFont("Times",12));
      lay->addWidget(lab,0,0,1,3,Qt::AlignLeft);
        int row = 1;
        qDeleteAll(rispCorrette);
      for(QList<string>::const_iterator it = Risposte.begin(); it != Risposte.end(); ++it){
          lab = new QLabel(QString::number(row)+")",this);
          lab->setFont(QFont("Times",10));
          lay->addWidget(lab, row,0);

          lab = new QLabel(QString::fromStdString(*it),this);
          lab->setFont(QFont("Times",10));
          lay->addWidget(lab, row,1,1,1,Qt::AlignLeft);

          QCheckBox* ch = new QCheckBox(this);
          rispCorrette.push_back(ch);
          lay->addWidget(ch, row, 2);

          ++row;
      }
      setLayout(lay);
}

void DomandaRispMult::EditRisp(const QString &Doman, const QList<string> &risposte, const QList<string> &corrette)
{
    Domanda = Doman;
    Risposte = risposte;
    Corrette = corrette;
}

bool DomandaRispMult::isOK(QString & error) const
{
    if(domanda->text() == ""){
        error = "E' richiesto inserire il testo della domanda";
        return false;
    }
    bool esisteRispCorretta = false;
    QList<QCheckBox*>::const_iterator it2 = rispCorrette.begin();
    for(QList<QLineEdit*>::const_iterator it = totRisposte.begin();
        it != totRisposte.end() && it2 != rispCorrette.end(); ++it)
    {
        if((*it)->text() == ""){
            error = "E' richiesto inserire il testo di tutte le risposte";
            return false;
        }
        if(!esisteRispCorretta && (*it2)->isChecked())
            esisteRispCorretta = true;
        ++it2;
    }
    if(!esisteRispCorretta)
        error = "E' richiesto checkare almeno una risposta corretta per la correzione automatica";
    return esisteRispCorretta;
}

QString DomandaRispMult::getDomanda() const
{
    return domanda->text();
}

QList<string> DomandaRispMult::getRisposte() const
{
    QList<string> l;
    for(QList<QLineEdit*>::const_iterator it = totRisposte.begin();
        it != totRisposte.end(); ++it)
    {
        l.push_back((*it)->text().toStdString());
    }
    return l;
}

QList<bool> DomandaRispMult::getRisposteCorrette() const
{
    QList<bool> l;
    for(QList<QCheckBox*>::const_iterator it = rispCorrette.begin();
        it != rispCorrette.end(); ++it)
    {
        l.push_back((*it)->isChecked());
    }
    return l;
}

bool DomandaRispMult::isCorrect() const
{
    QList<string>::const_iterator it2 = Corrette.begin();
    bool correct = false;
    for(QList<QCheckBox*>::const_iterator it = rispCorrette.begin();
        it != rispCorrette.end() && it2 != Corrette.end(); ++it)
    {
        if((*it)->isChecked()){
            if((*it2 == "0")){
                (*it)->setStyleSheet("border: 2px solid red;");
            }
            else{
                (*it)->setStyleSheet("border: 2px solid green;");
                correct = true;
            }
        }
        ++it2;
    }
    return correct;
}

QString DomandaRispMult::stampa() const
{
    QString temp = Domanda+"\n\n"+"Risposte:\n";
    QList<QCheckBox*>::const_iterator it2 = rispCorrette.begin();
    for(QList<string>::const_iterator it = Risposte.begin();
        it != Risposte.end() && it2 != rispCorrette.end(); ++it)
    {
        if((*it2)->isChecked()){
            temp = temp + QString::fromStdString(*it) +"\n";
        }
        ++it2;
    }

    return temp;
}
