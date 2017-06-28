#ifndef HOMEPAGESTUD_H
#define HOMEPAGESTUD_H
#include <QWidget>
class QGroupBox;
class QVBoxLayout;
class ControllerStud;
class HomePageStud: public QWidget{
Q_OBJECT
private:
    QGroupBox* gruppi;
    QGroupBox* compiti;
    QGroupBox* profile;
    QGroupBox* wallnews;
    ControllerStud* ctrl;
    void InsertInGruppi() const;
    void InsertInCompiti() const;
    void InsertInProfile() const;
    void InsertInNews() const;
public:
    HomePageStud(ControllerStud *contrl=0, QWidget* parent=0);
public slots:
    void signout();

};

#endif // HOMEPAGESTUD_H
