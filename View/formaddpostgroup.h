#ifndef FORMADDPOSTGROUP_H
#define FORMADDPOSTGROUP_H

#include <QDialog>

class ControllerGruppoUser;
class QLineEdit;
class QTextEdit;
class FormAddPostGroup : public QDialog
{
    Q_OBJECT
private:
    ControllerGruppoUser* ctrl;
    QLineEdit* titolo;
    QTextEdit* testo;
    QString groupName;
public:
    FormAddPostGroup(ControllerGruppoUser* c, const QString& group, QWidget* parent = 0);
public slots:
    void salva();
};

#endif // FORMADDPOSTGROUP_H
