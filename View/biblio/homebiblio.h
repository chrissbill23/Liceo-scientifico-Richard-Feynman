#ifndef HOMEBIBLIO_H
#define HOMEBIBLIO_H

#include "finestrebiblioteca.h"
class QGroupBox;
class PrimoPianoWidg;
class QLineEdit;
class HomeBiblio: public FinestreBiblioteca
{
    Q_OBJECT
private:
    QGroupBox* nav;
    PrimoPianoWidg* PrimoPiano;
    QLineEdit* searchBox;
    void InsertInNav();
public:
    HomeBiblio(Controller* u);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void SearchBookResult()const;
};

#endif // HOMEBIBLIO_H
