#ifndef FINESTRE_H
#define FINESTRE_H

#include <QWidget>

class Controller;
class Finestre: public QWidget
{
    Q_OBJECT
private:
Controller* ctrl;

protected:
virtual void Header()=0;
virtual void BodyAndFooter()=0;

public:
    Finestre(Controller *c,QWidget* parent=0);
    void setStyleSheet(const QString &);
    virtual Controller* getController()const;
public slots: 
    virtual void reloadWindow() = 0;
    virtual void viewInfoClasse(const QString& classe)const;
    virtual void viewMaterieInsegnate()const;
    virtual void viewPdfFile(const QString&)const;
    void signout();
    void HomePageBiblio()const;
    void TornaIndietro()const;
    void show();
    void viewInfoLibro(const QString &code)const;
    void viewLibriInCateg(const QString& cath);
    void cambiaPassword();
    void cambiafotoProfilo() const;
};
#endif // FINESTRE_H
