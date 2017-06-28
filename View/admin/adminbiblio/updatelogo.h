#ifndef UPDATELOGO_H
#define UPDATELOGO_H

#include <QDialog>

class QLineEdit;
class ControllerAdminBiblio;
class QVBoxLayout;
class updateLogo : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* path;
    ControllerAdminBiblio* ctrl;
    QVBoxLayout* lay;
public:
    updateLogo(ControllerAdminBiblio* c, QWidget* parent = 0);
public slots:
    void salva();
    void carica()const;
};

#endif // UPDATELOGO_H
