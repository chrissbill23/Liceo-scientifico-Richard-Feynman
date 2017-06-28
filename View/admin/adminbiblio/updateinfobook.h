#ifndef UPDATEINFOBOOK_H
#define UPDATEINFOBOOK_H

#include <QDialog>
#include "../../../Controller/controlleradminbiblio.h"

class QScrollArea;
class QVBoxLayout;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QGroupBox;

class updateInfoBook : public QDialog
{
    Q_OBJECT
private:
    ControllerAdminBiblio* ctrl;
    QString codebook;
    QScrollArea* form;
    QVBoxLayout* lay;
    QLineEdit* titolo, *autore, *copertina;
    QComboBox* annoEdizione;
    QTextEdit* Descrizione;
    vector<QComboBox*> categorie;

    static int maxCategorie;

    void anniEdizioni();
    void LoadCategorie();
public:
      updateInfoBook(const QString& codice, ControllerAdminBiblio* c, QWidget* parent = 0);
    QGroupBox *loadDialog();
public slots:
    void loadCopertina()const;
    void salva();

};

#endif // UPDATEINFOBOOK_H
