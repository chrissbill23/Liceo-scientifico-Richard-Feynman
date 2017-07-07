#ifndef VIEWCOMPITISTUD_H
#define VIEWCOMPITISTUD_H

#include "../viewcompiti.h"

class ControllerStud;
class QScrollArea;
class ViewCompitiStud : public ViewCompiti
{
private:
    QScrollArea* sc;
    ControllerStud* ctrl;
public:
    ViewCompitiStud(ControllerStud* c);
    QWidget* listaCompiti(int) const;
    bool sort();
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void goNext();
    void goPrev();
};

#endif // VIEWCOMPITISTUD_H
