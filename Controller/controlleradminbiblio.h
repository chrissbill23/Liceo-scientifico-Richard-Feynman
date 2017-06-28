#ifndef CONTROLLERADMINBIBLIO_H
#define CONTROLLERADMINBIBLIO_H

#include "controlleradmin.h"

class AdminBiblio;
class ControllerAdminBiblio: public ControllerAdmin{
private:
    AdminBiblio* utenteConnesso;
public:
    ControllerAdminBiblio(loginController* p1, StackFinestre* p2=0);
    bool inizializzaUtente(const QString& u);
    bool esisteCategoria(const QString&cat)const;
    bool aggiungiCategoria(const QString& nome) const;
    QString aggiungiNuovoLibro(const QString& titolo, const QString& descrizione, const QString& filePath);
    QString aggiungiInPrimoPiano(const QString& codiceLibro)const;
    bool rimuoviLibroDaPrimoPiano(const QString& codiceLibro)const;
    bool aggiungiCategoriaAlibro(const QString& codiceLibro, const QString& categoria);
    bool ModificaTitololibro(const QString& codiceLibro, const QString& titolo);
    bool ModificaAutorelibro(const QString& codiceLibro, const QString& autore);
    bool ModificaDescrizione(const QString& codiceLibro, const QString& descrizione);
    bool ModificaAnnoEdizione(const QString& codiceLibro, const QString& anno);
    bool ModificaCopertinaLibro(const QString& codiceLibro, const QString& filePath);
    bool eliminaLibro(const QString& codiceLibro);
    bool eliminaCategoria(const QString& nomeCat);
    bool eliminaCategorieLibro(const QString& codiceLibro);
    bool cambiaLogo(const QString& pathLogo) const;
    void HomePage();

};

#endif // CONTROLLERADMINBIBLIO_H
