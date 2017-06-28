#ifndef ADMINBIBLIO_H
#define ADMINBIBLIO_H

#include "admin.h"
#include "filexml.h"

class AdminBiblio: public Admin{
private:
    static string pathDB;
    static int maxPrimoPiano;
    filexml file;
public:
    AdminBiblio(const string &nU);
    bool VerificaPassword(const string& p) const;
    bool esiste() const;
    bool esisteCategoria(const string &cat)const;
    bool aggiungiCategoria(const string& nome) const;
    string aggiungiNuovoLibro(const string& titolo, const string& descrizione, const string& filePath);
    string aggiungiInPrimoPiano(const string& codiceLibro)const;
    bool rimuoviLibroDaPrimoPiano(const string& codiceLibro)const;
    bool aggiungiCategoriaAlibro(const string& codiceLibro, const string& categoria);
    bool ModificaTitololibro(const string& codiceLibro, const string& titolo);
    bool ModificaAutorelibro(const string& codiceLibro, const string& autore);
    bool ModificaDescrizione(const string& codiceLibro, const string& descrizione);
    bool ModificaAnnoEdizione(const string& codiceLibro, const string& anno);
    bool ModificaCopertinaLibro(const string& codiceLibro, const string& filePath);
    bool eliminaLibro(const string& codiceLibro);
    bool eliminaCategoria(const string& nomeCat);
    bool eliminaCategorieLibro(const string& codiceLibro);
    bool cambiaLogo(const string& pathLogo) const;

};
#endif // ADMINBIBLIO_H
