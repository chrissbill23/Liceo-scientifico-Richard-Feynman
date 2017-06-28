#ifndef FINESTREBIBLIOTECA_H
#define FINESTREBIBLIOTECA_H

#include "../finestre.h"
class QGridLayout;
class QPushButton;
class FinestreBiblioteca: public Finestre
{
    Q_OBJECT
public:
    FinestreBiblioteca(Controller*u, QWidget* parent = 0);
    QGridLayout* giveLayout()const;
private:
    QPushButton* logout;
    QPushButton* previousWindow;
    QGridLayout* p;
protected:
    void Header();
public slots:
    void viewPdfFile(const QString&)const;
    void AllCathegories() const;
    void SearchBook(const QString&) const;



};

#endif // BIBLIOTECAVIEW_H
