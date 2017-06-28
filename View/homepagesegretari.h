#ifndef HOMEPAGESEGRETARI_H
#define HOMEPAGESEGRETARI_H
#include <QWidget>


class QLabel;
class QGroupBox;
class QTimer;
class HomePageSegr: public QWidget{
Q_OBJECT
private:
    QLabel* FoglioPresenza;
    QGroupBox* GestioneStudenti;
    QGroupBox* GestioneRegistri;
    QGroupBox* profile;
    QTimer* t;
    void InsertInGestioneStudenti() const;
    void InsertInGestioneRegistri() const;
    void InsertInProfile() const;
public:
    HomePageSegr(QWidget* parent=0);

public slots:
    void updateLabel();
};

#endif // HOMEPAGESEGRETARI_H
