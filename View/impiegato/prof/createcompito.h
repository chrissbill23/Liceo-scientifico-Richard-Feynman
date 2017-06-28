#ifndef CREATECOMPITO_H
#define CREATECOMPITO_H

#include <QDialog>
class ControllerProf;
class QScrollArea;
class QGroupBox;
class CreateCompito: public QDialog
{
    Q_OBJECT
private:
    ControllerProf* ctrl;
    QScrollArea* sc;
    QGroupBox* FirstPage();
private slots:
    void gotoForm();
public slots:
    void salvaXml();
    void salvaPdf();
public:
    CreateCompito(ControllerProf* c, QWidget* parent = 0);
};

#endif // CREATECOMPITO_H
