#ifndef BUTTONGESTSTUD_H
#define BUTTONGESTSTUD_H

#include <QPushButton>

class FinestreSegretari;
class buttonGestStud : public QPushButton
{
    Q_OBJECT
private:
    QString matricola;
    FinestreSegretari* fi;
public:
    buttonGestStud(const QString& text, const QString& matr, FinestreSegretari* parent = 0);
public slots:
    void viewInfo()const;
    void editStud();
    void removeStud();

};

#endif // BUTTONGESTSTUD_H
