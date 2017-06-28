#ifndef TUTTIIPOSTGRUPPO_H
#define TUTTIIPOSTGRUPPO_H

#include "gruppoview.h"

class QLineEdit;
class QVBoxLayout;
class QScrollArea;

class TuttiIPostGruppo: public GruppoView
{
    Q_OBJECT
private:
    ControllerGruppoUser* ctrl;
    QString groupName;
    QLineEdit* searchbox;
    QScrollArea* sc;
    QVBoxLayout* layout;
    QGroupBox* loadPost(int indice);
    vector<int> post;
    int totPage, currPage;
    static int maxPerPage;
public:
    TuttiIPostGruppo(ControllerGruppoUser *c, const QString &n, QWidget* parent = 0);
    void Header();
    void BodyAndFooter();
private slots:
    void cercaPost();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
};

#endif // TUTTIIPOSTGRUPPO_H
