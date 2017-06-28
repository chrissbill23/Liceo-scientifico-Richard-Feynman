#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include <string>
#include <list>
#include <vector>
class filexml;
using std::list;
using std::vector;
using std::string;
class Biblioteca{
private:
    static string path;
public:
    Biblioteca();
    string ShowLogo()const;
    string daiNomeBiblio()const;
    vector<string> categorie()const;
    vector<string> codiciLibri()const;
    vector<string> codiciLibriPrimoPiano()const;
    list<string> daiCodiciLibriCat(const string& nomeCat)const;
    vector<string> findCodiciBook(const string& parolaChiave) const;
    list<string> daiCodiciLibriAnnoEdizione(const string& anno) const;
    string daiTitoloLibro(const string& codice)const;
    string daiAutoreLibro(const string& codice)const;
    string daiAnnoEdizioneLibro(const string& codice)const;
    string daiDescrizioneLibro(const string& codice)const;
    string daiCopertinaLibro(const string& codice)const;
    list<string> daiCategorieLibro(const string& codice)const;
    string daiPercorsoLibro(const string& codice)const;
    void SortLibriByCategoria(vector<string> &codiciLibri, const string& categoria)const;
    void SortLibriByAutore(vector<string>& codiciLibri, const string& autore)const;
    void SortLibriByAnnoEdizione(vector<string> &codiciLibri, const string& anno)const;
};

#endif // BIBLIOTECA_H
