#ifndef FINESTREADMINBIBLIO_H
#define FINESTREADMINBIBLIO_H

#include "../finestreadmin.h"
#include "../../../Controller/controlleradminbiblio.h"

class FinestreAdminBiblio: public finestreAdmin
{
    Q_OBJECT
private:
ControllerAdminBiblio * ctrl;
public:
    FinestreAdminBiblio(ControllerAdminBiblio* ptr, QWidget* parent = 0);
    ControllerAdminBiblio* getController()const;
protected:
    void Header();
public slots:
    void CaricaNewBook();
    void addCategoria();
    void eliminaLibro(const QString& codice);
    void eliminaCateg(const QString& cath);
    void updateInfoLibro(const QString &code);
    void aggiungiPrimoPiano(const QString& code);
    void elimDaPrimoPiano(const QString& code);
    void cambiaLogo();
    void viewPdfFile(const QString&)const;
};

#endif // FINESTREADMINBIBLIO_H
