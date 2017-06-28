#ifndef FINESTREPRESIDE_H
#define FINESTREPRESIDE_H

#include "../finestreimpiegato.h"
#include "../../../Controller/controllerpreside.h"

class FinestrePreside: public FinestreImpiegato{
    Q_OBJECT
private:
ControllerPreside * ctrl;
public:
    FinestrePreside(ControllerPreside* p = 0, QWidget* parent = 0);
    ControllerPreside* getController()const;
public slots:
    void gestionePersonale()const;
    void gestioneClassi()const;
    virtual void viewInfoImpiegato(const QString& nomeUtente)const;
    virtual void rimuoviImpiegato(const QString& nomeUtente);
    virtual void CercaImpiegato();
    void addImpiegato();
    void rimuoviClasse(const QString& nome);
    void aggiungiClasse();
    void aggiungiSessClasse();
    void aggiungiIndirClasse();
    void aggiungiMateria();
    void rimuoviSessione();
    void rimuoviIndirizzo();
    void rimuoviMateria() const;
    void assegnaMateriaAProf(const QString& prof) const;
    void RimuoviMateriaAProf(const QString& prof) const;
};

#endif // FINESTREPRESIDE_H
