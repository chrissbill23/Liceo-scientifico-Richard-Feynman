#ifndef FORMADDSTUDENT_H
#define FORMADDSTUDENT_H
#include <QDialog>
class QLineEdit;
class QComboBox;
class QPushButton;
class ControllerSegretario;
class QLabel;
class QScrollArea;
class QGroupBox;
class FormAddStudent : public QDialog
{
    Q_OBJECT
private:
ControllerSegretario* ctrl;
QLineEdit* cognome;
QLineEdit* nome;
QComboBox* ggNascita;
QComboBox* mmNascita;
QComboBox* annoNascita;
QLineEdit* LuogoNascita;
QComboBox* classe;
QLineEdit* matricola;
QPushButton* GenMatricola;
QLineEdit* nomeutente;
QPushButton* GenNomeUtente;
QLineEdit* password;
QPushButton* GenPassword;
QLabel* errore;
QScrollArea* sc;

void insertInNascita() const;
void InsertInClasse() const;
void Ricomincia();
bool checkDataNascita()const;
bool checkMatricola()const;
bool checkNomeUtente()const;

bool inputCorretto()const;

QGroupBox* loadPage();

public:
    FormAddStudent(ControllerSegretario* c, QWidget* parent = 0);
public slots:
    void salvaTutto();
    void RandMatricola()const;
    void RandNomeUtente()const;
    void RandPassword()const;

};

#endif // FORMADDSTUDENT_H
