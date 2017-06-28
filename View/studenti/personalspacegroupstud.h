#ifndef PERSONALSPACEGROUPSTUD_H
#define PERSONALSPACEGROUPSTUD_H

#include "../gruppoview.h"

class QScrollArea;
class QVBoxLayout;
class QRadioButton;

class PersonalSpaceGroupStud : public GruppoView
{
    Q_OBJECT
private:
    ControllerGruppoUser* ctrl;
    QString nomeGroup;
    QScrollArea* scroll;
    QVBoxLayout* lay;
    QRadioButton* mYpost;
    QRadioButton* mYAnsw;
    vector<int> myPost;
    vector<int> myAnsw;
    QGroupBox* MyPost(int indice);
    QGroupBox* MyAnsw(int indice);
    int totPageP;
    int totPageR;
    int currPagePost;
    int currPageAnsw;
    static int maxPerPage;
private slots:
    void setOnMyPosts();
    void setOnMyAnswers();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
public:
    PersonalSpaceGroupStud(ControllerGruppoUser *c, const QString & n, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
};

#endif // PERSONASPACEGROUPSTUD_H
