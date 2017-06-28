#ifndef GESTGRUPPI_H
#define GESTGRUPPI_H

#include "../../gruppoview.h"
#include "../../../Controller/controlleradminsistema.h"


class QLineEdit;
class QScrollArea;
class QVBoxLayout;
class QComboBox;
class GestGruppi : public GruppoView
{
    Q_OBJECT
private:
    ControllerAdminSistema* ctrl;
    QGroupBox* head;
    QScrollArea* body;
    QLineEdit* searchBox;
    QComboBox* categ;
    list<string> gruppi;
    QVBoxLayout* lay;

    void InsertInCategoria();
    QGroupBox* loadPage();

public:
    GestGruppi(ControllerAdminSistema* c, const QString& name, QWidget*parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void ShowResult();
    void reloadWindow();
private slots:
    void switchCath();
    void addCathegory();
    void removeCathegory();
    void addNewGroup();
    void EditGroup();
    void ElimGroup();
    void GestPost()const;

};

#endif // GESTGRUPPI_H
