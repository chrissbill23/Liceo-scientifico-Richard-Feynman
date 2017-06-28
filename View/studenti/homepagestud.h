#ifndef HOMEPAGESTUD_H
#define HOMEPAGESTUD_H

#include "finestrestudenti.h"

class QGroupBox;
class QVBoxLayout;
class QScrollArea;

class HomePageStud: public FinestreStudenti {
    Q_OBJECT
private:
    QGroupBox* gruppi;
    QGroupBox* compiti;
    QGroupBox* profile;
    void InsertInGruppi();
    void InsertInCompiti() const;
    void InsertInProfile() const;
    void clearNoGranChildren();
public:
    HomePageStud(ControllerStud *contrl = 0);
protected:
    void BodyAndFooter();
public slots:
    void reloadWindow();
    void Cerca();
    void TuttiIGruppi();
    void IscriviMiAGroup(const QString & group);
    void RemoveMeFromGroup(const QString& group);
};

#endif // HOMEPAGESTUD_H
