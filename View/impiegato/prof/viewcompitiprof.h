#ifndef VIEWCOMPITIPROF_H
#define VIEWCOMPITIPROF_H
#include "../../viewcompiti.h"

class ControllerProf;
class QScrollArea;
class ViewCompitiProf : public ViewCompiti
{
    Q_OBJECT
private:
    QScrollArea* sc;
    ControllerProf* ctrl;
public:
    ViewCompitiProf(ControllerProf* c);
    QWidget* listaCompiti(int) const;
    void viewElaborati(const QString& codice)const;
public slots:
    void reloadWindow();
    void createCompito();
    void aggiungiClasse(const QString &codice);
    void goNext();
    void goPrev();
protected:
    void BodyAndFooter();
};

#endif // VIEWCOMPITIPROF_H
