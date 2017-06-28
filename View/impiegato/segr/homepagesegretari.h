#ifndef HOMEPAGESEGRETARI_H
#define HOMEPAGESEGRETARI_H
#include "finestresegretari.h"

class QLineEdit;
class HomePageSegr: public FinestreSegretari{

    Q_OBJECT
private:
    QScrollArea* GestioneStudenti;
    QGroupBox* profile;
    QGroupBox* InsertInGestioneStudenti();
    QLineEdit* searchBox;
    void InsertInProfile() const;

public:
    HomePageSegr(ControllerSegretario* ptr);
protected:
    void BodyAndFooter();
private slots:
    void cercaStudente();
public slots:
    void reloadWindow();
};

#endif // HOMEPAGESEGRETARI_H
