#include "domandaaperta.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

DomandaAperta::DomandaAperta(QWidget *parent): DomandeCompito(parent), domanda(0), Domanda(""),
    risposta(0), lay(0)
{

}

void DomandaAperta::setIntoCreateWidg()
{
    if(!domanda)
    domanda = new QTextEdit(this);
    domanda->setFont(QFont("Times",12));

    if(!lay){
        lay = new QVBoxLayout(this);
        setLayout(lay);
    }
    lay->addWidget(domanda);
    setLayout(lay);
}

void DomandaAperta::setIntoAnswWidg()
{
    if(!lay){
        lay = new QVBoxLayout(this);
        setLayout(lay);
    }
    QLabel* lab = new QLabel(Domanda,this);
    lab->setFont(QFont("Times",12));
    lay->addWidget(lab,0,Qt::AlignLeft|Qt::AlignTop);

    lab = new QLabel("Risposta: ",this);
    lab->setFont(QFont("Times",10));
    lay->addWidget(lab,0,Qt::AlignLeft|Qt::AlignTop);

    if(!risposta)
        risposta = new QTextEdit(this);
    risposta->setFont(QFont("Times",8));
    lay->addWidget(risposta,1,Qt::AlignLeft|Qt::AlignTop);


}

bool DomandaAperta::isOK(QString & error) const
{
    if(domanda->toPlainText() == ""){
        error = "E' richiesto inserire il testo della domanda";
        return false;
    }
    return true;
}

void DomandaAperta::EditDomanda(const QString &d)
{
    Domanda = d;
}

QString DomandaAperta::getDomanda() const
{
    return domanda->toPlainText();
}

QString DomandaAperta::stampa() const
{
    QString temp = Domanda+"\n\n"+"Risposta: \n"+ risposta->toPlainText();
    return temp;
}
