#ifndef BIBLIOBUTTON_H
#define BIBLIOBUTTON_H

#include <QPushButton>

class Finestre;
class bibliobutton : public QPushButton
{
    Q_OBJECT
private:
    QString codiceLibro;
    Finestre* fi;
    bool cat;
    QString nomeCat;
public:
    bibliobutton(const QString& text, const QString c, bool ca = false, const QString& nomeCa = "",  Finestre* parent = 0);
    QString daiCodice()const;
    bool isCat()const;
    QString daiCat()const;
public slots:
    void viewLibro()const;
    void viewInfoLibro()const;
    void viewLibriInCat()const;
};

#endif // BIBLIOBUTTON_H
