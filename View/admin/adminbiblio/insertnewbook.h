#ifndef INSERTNEWBOOK_H
#define INSERTNEWBOOK_H

#include <QDialog>
#include "../../../Controller/controlleradminbiblio.h"

class QScrollArea;
class QVBoxLayout;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QGroupBox;

class InsertNewBook : public QDialog
{
    Q_OBJECT
private:
    ControllerAdminBiblio* ctrl;
    QScrollArea* form;
    QVBoxLayout* lay;
    QLineEdit* titolo, *autore, *copertina, *file;
    QComboBox* annoEdizione;
    QTextEdit* Descrizione;
    vector<QComboBox*> categorie;

    static int maxCategorie;

    void anniEdizioni();
    void LoadCategorie();
public:
    InsertNewBook(ControllerAdminBiblio* c, QWidget* parent = 0);
    QGroupBox* loadDialog();
public slots:
    void loadFile()const;
    void loadCopertina()const;
    void salva();
};

#endif // INSERTNEWBOOK_H
