#ifndef CREATEFILECOMPITO_H
#define CREATEFILECOMPITO_H

#include <QGroupBox>

class ControllerProf;
class QComboBox;
class QLineEdit;
class QTextEdit;
class QVBoxLayout;
class QLabel;
class DomandeCompito;
class CreateCompito;
class createFileCompito : public QGroupBox
{
     Q_OBJECT
private:
    ControllerProf* ctrl;
    QComboBox* Materia;
    QComboBox* classe;
    QLineEdit* titolo;
    QTextEdit* Descrizione;
    QVBoxLayout* lay;
    QLabel* error;
    CreateCompito* genitore;
protected:
    QWidget* InsertInMateria();
    QWidget* InsertInClasse();
    virtual bool isOk();
public slots:
    virtual bool salva() = 0;
public:
    createFileCompito(ControllerProf* c, QWidget* parent);
    void setMessage(QLabel* p);
    void loadHeader();
    ControllerProf* giveController()const;
    QComboBox* giveMateria()const;
    QComboBox* giveClasse()const;
    QLineEdit* giveTitolo()const;
    QTextEdit* giveDescr()const;
    QVBoxLayout* giveLayout() const;
    QLabel* giveError()const;
    CreateCompito* giveGrandParent()const;
};

#endif // CREATEFILECOMPITO_H
