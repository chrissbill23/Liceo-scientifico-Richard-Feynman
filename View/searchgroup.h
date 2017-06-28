#ifndef SEARCHGROUP_H
#define SEARCHGROUP_H

#include "gruppoview.h"
#include <list>

using std::list;

class QLineEdit;
class QScrollArea;
class QVBoxLayout;
class QComboBox;
class ControllerGruppoUser;

class SearchGroup: public GruppoView
{
    Q_OBJECT
private:
    QGroupBox* head;
    QScrollArea* body;
    QLineEdit* searchBox;
    QComboBox* categ;
    ControllerGruppoUser* ctrl;
    list<string> gruppi;
    QVBoxLayout* layout;

    void InsertInCategoria();
    QGroupBox* loadPage();
public:
    SearchGroup(ControllerGruppoUser *c, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void ShowResult();
    void reloadWindow();
private slots:
    void switchCath();
};

#endif // SEARCHGROUP_H
