#include "compitoparserxml.h"
#include "./impiegato/prof/domandarispmult.h"
#include "./impiegato/prof/domandaaperta.h"
#include "../Controller/Controller.h"
#include "../Controller/controllercompitiuser.h"
#include "../Modello/filexml.h"
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

void CompitoParserXml::emptyScrollbar()
{
    if(sc){
        QWidget* p = sc->widget();
        if(p)
            delete p;
    }
}

CompitoParserXml::CompitoParserXml(const QString & c, ControllerCompitiUser* ct, QWidget *parent): CompitoParser(c,ct,parent), sc(0),
    layout(0), risultDM(0), salva(0), valAutomatica(new QLabel(this)), hasAnsw(false)
{

}

void CompitoParserXml::parse()
{
    if(!sc)
        sc = new QScrollArea(this);
    else emptyScrollbar();

    QGroupBox* temp = new QGroupBox;
    QVBoxLayout* lay = new QVBoxLayout(temp);
    temp->setLayout(lay);

    filexml f(giveController()->giveCompitoXml(giveCodice()).toStdString());

    if(f.apriFile()){
        lay->addWidget(valAutomatica,0,Qt::AlignTop|Qt::AlignLeft);
        lay->addWidget(new QLabel(giveController()->getCompitoAutore(giveCodice()), temp),0,Qt::AlignTop|Qt::AlignLeft);
        lay->addWidget(new QLabel(QString::fromStdString(f.daiTestoIn("titolo"))),0,Qt::AlignTop|Qt::AlignCenter);
        int totDom = f.totNodi("domanda");
        bool DomandaRispmult = false;
        for(int i = 0; i < totDom; ++i){

            lay->addWidget(new QLabel("Domanda "+QString::number(i+1)+" :", this),0,Qt::AlignTop|Qt::AlignLeft);
            string s = f.daiTestoIn("tipoDomanda",i);

            if(s == "domanda a risposta multipla"){
                DomandaRispmult = true;
            DomandaRispMult* d = new DomandaRispMult(this);
            d->EditRisp(QString::fromStdString(f.daiTestoIn("testoDomanda",i)),
                        QList<string>::fromStdList(f.daiTestoDiNodi("testoRisposta","domanda",i)),
                        QList<string>::fromStdList(f.daiTestoDiNodi("corretta","domanda",i)));
            d->setIntoAnswWidg();
            d->setFixedWidth(200);
            d->setStyleSheet("border: 0;");
            lay->addWidget(d,1,Qt::AlignTop|Qt::AlignLeft);
            }
            else{
                DomandaAperta* d = new DomandaAperta(this);
                d->EditDomanda(QString::fromStdString(f.daiTestoIn("testoDomanda",i)));
                d->setIntoAnswWidg();
                d->setFixedWidth(500);
                d->setStyleSheet("QGroupBox{border: 0;}");
                lay->addWidget(d,1,Qt::AlignTop|Qt::AlignLeft);
            }
        }

        if(DomandaRispmult){
            if(risultDM)
                delete risultDM;
            risultDM = new QPushButton("Vedi correzione domande aperte",temp);
            connect(risultDM, SIGNAL(clicked(bool)),this,SLOT(CorrezioneAutomatica()));
            lay->addWidget(risultDM,0,Qt::AlignTop|Qt::AlignCenter);
        }
        hasAnsw = giveController()->hasAnsweredCompito(giveCodice());
        if(!hasAnsw){
            if(salva)
                delete salva;
            salva = new QPushButton("Salva Modifiche",temp);
            connect(salva, SIGNAL(clicked(bool)),this, SLOT(salvaRisposta()));
            lay->addWidget(salva,1,Qt::AlignTop|Qt::AlignCenter);
        }
    }
    else lay->addWidget(new QLabel("Errore nell'apertura del file"));

    sc->setWidget(temp);
    sc->setWidgetResizable(true);
    if(!layout){
        layout = new QVBoxLayout(this);
        setLayout(layout);
    }
    layout->addWidget(sc);


}

void CompitoParserXml::CorrezioneAutomatica() const
{
    if(hasAnsw){
    int tot = 0;
    int giuste = 0;

    foreach(DomandaRispMult* child, findChildren<DomandaRispMult*>()) {
        ++tot;
        if(child->isCorrect())
            ++giuste;
    }
    if(tot > 0){
        valAutomatica->setText("Hai risposto correttamente ai "+QString::number(giuste*100/tot)+"% "
                                "delle domande a risposta automatica");
        valAutomatica->setFont(QFont("Times",14));
        valAutomatica->setStyleSheet("color: green");
        delete risultDM;
    }
}
    else QMessageBox::information(0,"", "Devi prima salvare per avere la valutazione finale :)");
}

void CompitoParserXml::salvaRisposta()
{
    filexml f(giveController()->giveCompitoXml(giveCodice()).toStdString());

    QString s = QString::fromStdString(f.daiTestoIn("data")) + "\n\n\t\t\t\t\t\t\t\t\t\t";
    s = s + QString::fromStdString(f.daiTestoIn("titolo"))+"\n\n\n\n\n";
    foreach(QWidget* child, findChildren<QWidget*>()){
        DomandeCompito* p = dynamic_cast<DomandeCompito*>(child);
        if(p)
        s = s + p->stampa() + "\n\n\n";
    }

    if(!giveController()->salvaRispCompito(s,giveCodice())){
        QMessageBox::information(const_cast<CompitoParserXml*>(this), "Errore:", "E' avvenuto un errore");
    }
    else {
        QMessageBox::information(const_cast<CompitoParserXml*>(this), "", "Salvato con successo!");
        hasAnsw = true;
        delete salva;
    }
}
