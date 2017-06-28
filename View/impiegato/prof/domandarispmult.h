#ifndef DOMANDARISPMULT_H
#define DOMANDARISPMULT_H

#include "domandecompito.h"
#include <string>
using std::string;
class QLineEdit;
class QGridLayout;
class QCheckBox;

class DomandaRispMult: public DomandeCompito
{
private:
    Q_OBJECT
    QLineEdit* domanda;
    QString Domanda;
    QGridLayout* lay;
    QList<QLineEdit*> totRisposte;
    QList<string> Risposte;
    QList<QCheckBox*> rispCorrette;
    QList<string> Corrette;

private slots:
    void aggiungiRisposta();
public:
    DomandaRispMult(QWidget* parent);
    void setIntoCreateWidg();
    void setIntoAnswWidg();
    void EditRisp(const QString& Doman, const QList<string>& risposte, const QList<string>& corrette );
    bool isOK(QString&)const;
    QString getDomanda()const;
    QList<string> getRisposte() const;
    QList<bool> getRisposteCorrette() const;
    bool isCorrect()const;
    QString stampa()const;

};

#endif // DOMANDARISPMULT_H
