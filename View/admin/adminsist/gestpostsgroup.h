#ifndef GESTPOSTSGROUP_H
#define GESTPOSTSGROUP_H

#include "../../gruppoview.h"

class ControllerAdminSistema;
class QCheckBox;
class QScrollArea;
class QVBoxLayout;
class QLineEdit;
class GestPostsGroup : public GruppoView
{
    Q_OBJECT
private:
    ControllerAdminSistema* ctrl;
    QString group;
    QGroupBox* head;
    QScrollArea* sc;
    QLineEdit* searchbox;
    int currPage, totPage;
    static int maxPerPage;
    vector<int> post;
    vector<QCheckBox*> v;
    QGroupBox* loadPage(int);
    QVBoxLayout* layout;

public:
    GestPostsGroup(ControllerAdminSistema* c, const QString& name, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
    void deletePost(unsigned int);
private slots:
    void cercaPost();

};

#endif // GESTPOSTSGROUP_H
