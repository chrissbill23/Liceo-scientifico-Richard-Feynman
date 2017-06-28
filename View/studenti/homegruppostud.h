#ifndef HOMEGRUPPOSTUD_H
#define HOMEGRUPPOSTUD_H

#include "../gruppoview.h"

class QTabWidget;
class TuttiIPostGruppo;
class QScrollArea;
class PersonalSpaceGroupStud;
class ControllerStud;
class HomeGruppoStud: public GruppoView
{
private:
    ControllerStud* ctrl;
    QScrollArea* sc;
    QTabWidget* tab;
    TuttiIPostGruppo* post;
    PersonalSpaceGroupStud* mySpace;
    QGroupBox* loadPage();
public:
    HomeGruppoStud(ControllerStud* c, const QString&  name);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
};

#endif // HOMEGRUPPOSTUD_H
