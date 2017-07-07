#include "Controller.h"
#include "../Modello/Utente.h"
#include "../View/biblio/homebiblio.h"
#include "loginController.h"
#include "../Modello/filexml.h"
#include "../View/stackfinestre.h"

Controller::Controller(loginController *log, StackFinestre *s, Utente *u):utenteConnesso(u),Stack(s), logCtrl(log)
{

}

void Controller::setUtente(Utente *u)
{
    if(utenteConnesso)
        delete utenteConnesso;
    utenteConnesso = u;
}

void Controller::setWidgets(StackFinestre *p)
{
    if(Stack)
        delete Stack;
    else
        Stack=p;

}

StackFinestre *Controller::giveStack() const
{
    return Stack;
}


bool Controller::CambiaFotoProfilo(const QString &path) const
{
    return utenteConnesso->CambiaFotoProfilo(path.toStdString());
}

bool Controller::CambioPassword(const QString &newpass) const
{
    return utenteConnesso->CambiaPassword(newpass.toStdString());
}

QString Controller::UtenteConnesso() const
{
    return QString::fromStdString(utenteConnesso->daiNomeUtente());
}

list<string> Controller::DaiValoreCampiDatiProfile() const
{
    return utenteConnesso->DaiDatiPersonali();
}

QString Controller::fotoprofilo() const
{
    return QString::fromStdString(utenteConnesso->daifoto());
}

void Controller::signout()
{
    logCtrl->signout();
}

void Controller::getPrevFinestra()
{
    Stack->setToPrevWidget();
}

void Controller::ShowNewWindow(QWidget *w)const
{
    int index = Stack->addWidget(w);
    Stack->setCurrentIndex(index);
}

void Controller::ReloadAllWindows()
{
    int tot = Stack->count();
    for(int i = 0; i < tot; ++i){
        Finestre* f = dynamic_cast<Finestre* > (Stack->widget(i));
        if(f)
            f->reloadWindow();
    }
}

QString Controller::ShowLogoBiblio() const
{
    return QString::fromStdString(b.ShowLogo());
}

QString Controller::ShowNomeBiblio() const
{
    return QString::fromStdString(b.daiNomeBiblio());
}

vector<string> Controller::CategorieBiblio() const
{
    return b.categorie();
}

vector<string> Controller::CodiciLibri() const
{
    return b.codiciLibri();
}

vector<string> Controller::codiciLibriPrimoPiano() const
{
    return b.codiciLibriPrimoPiano();
}

list<string> Controller::daiCodiciLibriCat(const QString&nomeCat) const
{
    return b.daiCodiciLibriCat(nomeCat.toStdString());
}

vector<string> Controller::findCodiciBook(const QString&parolaChiave) const
{
    return b.findCodiciBook(parolaChiave.toStdString());
}

list<string> Controller::daiCodiciLibriAnnoEdizione(const QString&anno) const
{
    return b.daiCodiciLibriAnnoEdizione(anno.toStdString());
}

QString Controller::daiTitoloLibro(const QString& codice) const
{
    return QString::fromStdString(b.daiTitoloLibro(codice.toStdString()));
}

QString Controller::daiAutoreLibro(const QString&codice) const
{
    return QString::fromStdString(b.daiAutoreLibro(codice.toStdString()));
}

QString Controller::daiAnnoEdizioneLibro(const QString&codice) const
{
    return QString::fromStdString(b.daiAnnoEdizioneLibro(codice.toStdString()));
}

QString Controller::daiDescrizioneLibro(const QString&codice) const
{
    return QString::fromStdString(b.daiDescrizioneLibro(codice.toStdString()));
}

QString Controller::daiCopertinaLibro(const QString&codice) const
{
    return QString::fromStdString(b.daiCopertinaLibro(codice.toStdString()));
}

QString Controller::daiPercorsoLibro(const QString&codice) const
{
    return QString::fromStdString(b.daiPercorsoLibro(codice.toStdString()));
}

list<string> Controller::daiCategorieLibro(const QString&codice) const
{
    return b.daiCategorieLibro(codice.toStdString());
}

void Controller::SortLibriByCategoria(vector<string> &codiciLibri, const QString&categoria) const
{
    return b.SortLibriByCategoria(codiciLibri, categoria.toStdString());
}

void Controller::SortLibriByAutore(vector<string> &codiciLibri, const QString&autore) const
{
    return b.SortLibriByAutore(codiciLibri,autore.toStdString());
}

void Controller::SortLibriByAnnoEdizione(vector<string> &codiciLibri, const QString&anno) const
{
    return b.SortLibriByAnnoEdizione(codiciLibri, anno.toStdString());
}


list<string> Controller::MaterieInsegnate() const
{
    return utenteConnesso->daiMaterieInsegnate();
}

vector<string> Controller::Classi() const
{
    return utenteConnesso->daiClassi();
}

list<string> Controller::daiSessioniClassi() const
{
    return utenteConnesso->daiSessioniClassi();
}

list<string> Controller::daiIndirizzoClassi() const
{
    return utenteConnesso->daiIndirizzoClassi();
}


filexml Controller::giveSchedaClasse(const QString&nome) const
{
    return utenteConnesso->giveSchedaClasse(nome.toStdString());
}

Controller::~Controller(){
    if(utenteConnesso)
    delete utenteConnesso;

}
