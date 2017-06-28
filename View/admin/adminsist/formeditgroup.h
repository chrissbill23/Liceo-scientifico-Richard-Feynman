#ifndef FORMEDITGROUP_H
#define FORMEDITGROUP_H

#include <QDialog>

class ControllerAdminSistema;
class QLineEdit;
class QTextEdit;
class QComboBox;

class FormEditGroup : public QDialog
{
    Q_OBJECT
private:
ControllerAdminSistema * ctrl;
QLineEdit* name;
QTextEdit* descrizione;
QComboBox* categoria;
QString nomeGruppo;

void InsertInCategoria();
QString inputCorretto()const;

public:
    FormEditGroup(ControllerAdminSistema * c, const QString& group, QWidget* parent = 0);
private slots:
    void salva();
};

#endif // FORMEDITGROUP_H
