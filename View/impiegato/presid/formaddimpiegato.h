#ifndef FORMADDIMPIEGATO_H
#define FORMADDIMPIEGATO_H

#include <QDialog>
class QLineEdit;
class QComboBox;
class QPushButton;
class ControllerPreside;
class QLabel;
class QScrollArea;
class QGroupBox;

class FormAddImpiegato : public QDialog
{
    Q_OBJECT
private:
ControllerPreside* ctrl;
QLineEdit* cognome;
QLineEdit* nome;
QComboBox* mansione;
QLineEdit* nomeutente;
QPushButton* GenNomeUtente;
QLineEdit* password;
QPushButton* GenPassword;
QLineEdit* mail;
QPushButton* GenMail;
QLabel* errore;
QScrollArea* sc;

QGroupBox* loadPage();
bool inputCorretto()const;
void insertMansione() const;
bool checkNomeUtente()const;
public:
    FormAddImpiegato(ControllerPreside* c, QWidget* parent = 0);
public slots:
    void salvaTutto();
    void RandNomeUtente()const;
    void RandPassword()const;
    void RandMail()const;
    void reload();
};

#endif // FORMADDIMPIEGATO_H
