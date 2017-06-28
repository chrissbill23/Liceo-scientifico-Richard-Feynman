#ifndef GESTCLASSI_H
#define GESTCLASSI_H

#include "finestrepreside.h"

class QVBoxLayout;
class QComboBox;
class GestClassi : public FinestrePreside
{
    Q_OBJECT
private:
    ControllerPreside* ctrl;
    QScrollArea* body;
    QComboBox* classi, *sessioni, *indirizzi;
    QVBoxLayout* lay;

    vector<string> classes;
    void InsertInComboBoxes();
    QWidget* loadPage(int);
public:
    GestClassi(ControllerPreside* c, QWidget* parent = 0);
protected:
    void Header();
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void viewInfoClasse(const QString& classe)const;
    void cercaClasse();
};

#endif // GESDTCLASSI_H
