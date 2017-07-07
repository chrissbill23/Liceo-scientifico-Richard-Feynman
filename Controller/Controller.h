#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../Modello/biblioteca.h"

class loginController;
class Utente;
class QString;
class StackFinestre;
class QWidget;
class Controller {
private:
    Utente* utenteConnesso;
    StackFinestre* Stack;
    loginController* logCtrl;
    Biblioteca b;

public:
    Controller(loginController* log=0, StackFinestre* s=0, Utente* u=0);
    virtual bool inizializzaUtente(const QString& u) =0;
    void setUtente(Utente* u);
    virtual bool CheckPassword(const QString& p) const=0;
    virtual void HomePage() =0;
    void setWidgets(StackFinestre* p);
    StackFinestre* giveStack()const;
    bool CambiaFotoProfilo(const QString& path)const;
    bool CambioPassword(const QString& newpass)const;
    virtual list<string> CampiDatiProfile() const =0;
    QString UtenteConnesso()const;
    list<string> DaiValoreCampiDatiProfile() const;
    QString fotoprofilo() const;
    void signout();
    void getPrevFinestra();
    void ShowNewWindow(QWidget* w) const;
    void ReloadAllWindows();
    QString ShowLogoBiblio()const;
    QString ShowNomeBiblio()const;
    vector<string> CategorieBiblio()const;
    vector<string> CodiciLibri()const;
    vector<string> codiciLibriPrimoPiano()const;
    list<string> daiCodiciLibriCat(const QString& nomeCat)const;
    vector<string> findCodiciBook(const QString& parolaChiave) const;
    list<string> daiCodiciLibriAnnoEdizione(const QString& anno) const;
    QString daiTitoloLibro(const QString &codice)const;
    QString daiAutoreLibro(const QString& codice)const;
    QString daiAnnoEdizioneLibro(const QString& codice)const;
    QString daiDescrizioneLibro(const QString& codice)const;
    QString daiCopertinaLibro(const QString& codice)const;
    QString daiPercorsoLibro(const QString& codice)const;
    list<string> daiCategorieLibro(const QString& codice)const;
    void SortLibriByCategoria(vector<string> &codiciLibri, const QString& categoria)const;
    void SortLibriByAutore(vector<string> &codiciLibri, const QString& autore)const;
    void SortLibriByAnnoEdizione(vector<string>& codiciLibri, const QString& anno)const;

    list<string> MaterieInsegnate()const;
    vector<string> Classi()const;
    list<string> daiSessioniClassi()const;
    list<string> daiIndirizzoClassi()const;


    filexml giveSchedaClasse(const QString& nome)const;
    virtual ~Controller();
};

#endif // CONTROLLER_H
