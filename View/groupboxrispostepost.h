#ifndef GROUPBOXRISPOSTEPOST_H
#define GROUPBOXRISPOSTEPOST_H

#include <QGroupBox>

class QScrollArea;
class ControllerGruppoUser;
class QTextEdit;
class QVBoxLayout;
class GroupBoxRispostePost : public QGroupBox
{
    Q_OBJECT
private:
    int post;
    QString gruppo;
    QTextEdit* Rispondi;
    QScrollArea* scroll;
    ControllerGruppoUser* ctrl;
    QVBoxLayout* lay;
    int totRisp, totPage, currPage;
    static int maxPerPage;

    QGroupBox* Risposte(int indice);

private slots:
    void rispondi();
    void goNext();
    void goPrev();
public:
    GroupBoxRispostePost(ControllerGruppoUser *c, const QString &n, int p, QWidget* parent = 0);
    void reload();
};

#endif // GROUPBOXRISPOSTEPOST_H
