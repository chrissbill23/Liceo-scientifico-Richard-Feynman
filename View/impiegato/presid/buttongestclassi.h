#ifndef BUTTONGESTCLASSI_H
#define BUTTONGESTCLASSI_H

#include <QPushButton>

class FinestrePreside;
class buttonGestClassi : public QPushButton
{
    Q_OBJECT
private:
    FinestrePreside* fi;
    QString classe;

public:
    buttonGestClassi(const QString& text, const QString& cla, FinestrePreside* parent = 0);
public slots:
    void removeClass();
    void viewInfoClasse();
};

#endif // BUTTONGESTCLASSI_H
