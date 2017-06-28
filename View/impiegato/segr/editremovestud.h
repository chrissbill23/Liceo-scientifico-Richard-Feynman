#ifndef EDITREMOVESTUD_H
#define EDITREMOVESTUD_H
#include "finestresegretari.h"

class QLineEdit;
class QScrollArea;
class QGroupBox;
class QVBoxLayout;

class EditRemoveStud: public FinestreSegretari
{
    Q_OBJECT
private:
    QLineEdit* cerca;
    QScrollArea* sc;
    QVBoxLayout* lay;
    vector<string> matricola;
    vector<string> nomeUtente;
    vector<string> cognome;
    vector<string> nome;
    vector<string> classe;
    int totPage;
    int currPage;
    static int maxPerPage;

    QGroupBox* loadPage(int);
public:
    EditRemoveStud(ControllerSegretario*ptr, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void cercaStud(const QString& key);
private slots:
    void cercaStud();
    void goNext();
    void goPrev();
};

#endif // EDITREMOVESTUD_H
