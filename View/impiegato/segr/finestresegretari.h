#ifndef FINESTRESEGRETARI_H
#define FINESTRESEGRETARI_H
#include "../finestreimpiegato.h"
#include "../../../Controller/controllersegretario.h"

class FinestreSegretari:public FinestreImpiegato{
    Q_OBJECT
private:
    ControllerSegretario* ctrl;
public:
    FinestreSegretari(ControllerSegretario* p, QWidget* parent = 0);
    ControllerSegretario* getController()const;
public slots:
    void aggiungiStud();
    void ModificaStudenti()const;
    void CercaStud(const QString& key)const;
    void editStudInfo(const QString& matricola);
    void rimuoviStudente(const QString& matricola);
};

#endif // FINESTRESEGRETARI_H
