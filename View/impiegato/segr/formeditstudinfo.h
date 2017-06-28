#ifndef FORMEDITSTUDINFO_H
#define FORMEDITSTUDINFO_H

#include <QDialog>
class QLineEdit;
class QComboBox;
class QPushButton;
class ControllerSegretario;
class QLabel;
class QScrollArea;
class QGroupBox;

class FormEditStudInfo : public QDialog
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
QLabel* errore;
QScrollArea* sc;
QString matricola;

void insertInNascita() const;
void InsertInClasse() const;

bool checkDataNascita()const;
QString salvaNascitaDate()const;
QString salvaClasse()const;

QGroupBox *loadPage();
public:
    FormEditStudInfo(ControllerSegretario *c, const QString& matr, QWidget *parent = 0);
    bool inputCorretto()const;
public slots:
    void salvaTutto();
};

#endif // FORMEDITSTUDINFO_H
