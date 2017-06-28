#ifndef BUTTONGESTIMP_H
#define BUTTONGESTIMP_H

#include <QPushButton>

class FinestrePreside;
class buttonGestImp : public QPushButton
{
    Q_OBJECT
private:
    FinestrePreside* fi;
    QString nomeUtente;
public:
    buttonGestImp(const QString& text, const QString& nu, FinestrePreside* parent = 0);
public slots:
    void vediInfoImp()const;
    void AssegnaClasseProf()const;
    void RimuoviClasseProf()const;
    void ElimImp();
};

#endif // BUTTONGESTPROF_H
