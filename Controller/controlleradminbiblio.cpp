#include "controlleradminbiblio.h"
#include "../View/admin/adminbiblio/homepageadminbiblio.h"
#include "../Modello/adminbiblio.h"
#include "../View/stackfinestre.h"

ControllerAdminBiblio::ControllerAdminBiblio(loginController *p1, StackFinestre *p2):Controller(p1,p2), utenteConnesso(0){}


bool ControllerAdminBiblio::inizializzaUtente(const QString &u)
{
    utenteConnesso = new AdminBiblio(u.toStdString());
    if(utenteConnesso->esiste()){
    setUtente(utenteConnesso);
    return true;
    }
    delete utenteConnesso;
    utenteConnesso = 0;
    return false;
}

bool ControllerAdminBiblio::esisteCategoria(const QString &cat) const
{
    return utenteConnesso->esisteCategoria(cat.toStdString());
}

bool ControllerAdminBiblio::aggiungiCategoria(const QString&nome) const
{
    return utenteConnesso->aggiungiCategoria(nome.toStdString());
}

QString ControllerAdminBiblio::aggiungiNuovoLibro(const QString&titolo, const QString&descrizione, const QString&filePath)
{
    return QString::fromStdString(utenteConnesso->aggiungiNuovoLibro(titolo.toStdString(),
                                                                     descrizione.toStdString(),filePath.toStdString()));
}

QString ControllerAdminBiblio::aggiungiInPrimoPiano(const QString&codiceLibro) const
{
    return QString::fromStdString(utenteConnesso->aggiungiInPrimoPiano(codiceLibro.toStdString()));
}

bool ControllerAdminBiblio::rimuoviLibroDaPrimoPiano(const QString&codiceLibro) const
{
    return utenteConnesso->rimuoviLibroDaPrimoPiano(codiceLibro.toStdString());
}

bool ControllerAdminBiblio::aggiungiCategoriaAlibro(const QString&codiceLibro, const QString&categoria)
{
    return utenteConnesso->aggiungiCategoriaAlibro(codiceLibro.toStdString(), categoria.toStdString());
}

bool ControllerAdminBiblio::ModificaTitololibro(const QString&codiceLibro, const QString&titolo)
{
    return utenteConnesso->ModificaTitololibro(codiceLibro.toStdString(),titolo.toStdString());
}

bool ControllerAdminBiblio::ModificaAutorelibro(const QString&codiceLibro, const QString&autore)
{
    return utenteConnesso->ModificaAutorelibro(codiceLibro.toStdString(),autore.toStdString());
}

bool ControllerAdminBiblio::ModificaDescrizione(const QString&codiceLibro, const QString&descrizione)
{
    return utenteConnesso->ModificaDescrizione(codiceLibro.toStdString(),descrizione.toStdString());
}

bool ControllerAdminBiblio::ModificaAnnoEdizione(const QString&codiceLibro, const QString&anno)
{
    return utenteConnesso->ModificaAnnoEdizione(codiceLibro.toStdString(),anno.toStdString());
}

bool ControllerAdminBiblio::ModificaCopertinaLibro(const QString&codiceLibro, const QString&filePath)
{
    return utenteConnesso->ModificaCopertinaLibro(codiceLibro.toStdString(), filePath.toStdString());
}

bool ControllerAdminBiblio::eliminaLibro(const QString&codiceLibro)
{
    return utenteConnesso->eliminaLibro(codiceLibro.toStdString());
}

bool ControllerAdminBiblio::eliminaCategoria(const QString&nomeCat)
{
    return utenteConnesso->eliminaCategoria(nomeCat.toStdString());
}

bool ControllerAdminBiblio::eliminaCategorieLibro(const QString&codiceLibro)
{
    return utenteConnesso->eliminaCategorieLibro(codiceLibro.toStdString());
}

bool ControllerAdminBiblio::cambiaLogo(const QString&pathLogo) const
{
    return utenteConnesso->cambiaLogo(pathLogo.toStdString());
}

void ControllerAdminBiblio::HomePage()
{
    StackFinestre*Stack = giveStack();
    if(Stack){
    int index =  Stack->addWidget(new HomePageAdminBiblio(this));
    Stack->setCurrentIndex(index);
    Stack->show();
    }
}
