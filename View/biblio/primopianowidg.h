#ifndef PRIMOPIANOWIDG_H
#define PRIMOPIANOWIDG_H

#include"finestrebiblioteca.h"
#include "../../Controller/Controller.h"

class QVBoxLayout;
class QGroupBox;
class PrimoPianoWidg : public FinestreBiblioteca
{
    Q_OBJECT
private:
    vector<string> codeBookPP;
    int currBook;
    QGroupBox* contenuto;
    QVBoxLayout* layout;
    void switchBookPP(unsigned int indice);
public:
    PrimoPianoWidg(Controller* c, QWidget* parent = 0);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
};

#endif // PRIMOPIANOWIDG_H
