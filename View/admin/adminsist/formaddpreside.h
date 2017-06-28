#ifndef FORMADDPRESIDE_H
#define FORMADDPRESIDE_H

#include <QDialog>

class ControllerAdminSistema;
class QVBoxLayout;
class QLineEdit;
class FormAddPreside : public QDialog
{
    Q_OBJECT
private:
    ControllerAdminSistema* ctrl;
    QLineEdit* cognome, *nome,
    *nomeutente, *password, *dataFineCarr;
    QVBoxLayout* lay;

    QString inputCorretto()const;
public:
    FormAddPreside(ControllerAdminSistema* c, QWidget* parent = 0);
private slots:
    void salva();
};

#endif // FORMADDPRESIDE_H
