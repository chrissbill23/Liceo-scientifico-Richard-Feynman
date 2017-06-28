#ifndef INVIAMESSDIALOG_H
#define INVIAMESSDIALOG_H

#include <QDialog>

class QLineEdit;
class QTextEdit;
class ControllerImpiegato;
class QCompleter;
class QComboBox;
class InviaMessDialog: public QDialog
{
    Q_OBJECT
private:
    QLineEdit* destinatario;
    QLineEdit* oggetto;
    QTextEdit* messaggio;
    ControllerImpiegato* ctrl;
    QCompleter* sug;
    QComboBox* contatto;
    void BodyAndFooter();
    void InserisciContatti();
    void Reset()const;
private slots:
    void changeLineEditText();
    void SendMessage();
public:
    InviaMessDialog(ControllerImpiegato* ptr, QDialog*parent = 0);

};

#endif // INVIAMESSDIALOG_H
