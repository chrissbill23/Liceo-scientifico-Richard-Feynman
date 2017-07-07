#ifndef POST_H
#define POST_H

#include "gruppoview.h"

class QTextEdit;
class QGroupBox;
class QScrollArea;
class GroupBoxRispostePost;

class Post: public GruppoView
{
    Q_OBJECT
private:
    int post;
    QString gruppo;
    QTextEdit* Rispondi;
    GroupBoxRispostePost* Risposte;
    ControllerGruppoUser* ctrl;
    QScrollArea *Domanda();
public:
    Post(ControllerGruppoUser *c, const QString &n, int p);
    void BodyAndFooter();
public slots:
    void reloadWindow();
};

#endif // POST_H
