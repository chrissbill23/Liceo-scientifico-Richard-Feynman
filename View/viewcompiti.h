#ifndef VIEWCOMPITI_H
#define VIEWCOMPITI_H

#include "finestre.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class QGridLayout;
class QComboBox;
class ControllerCompitiUser;

class ViewCompiti : public Finestre
{
    Q_OBJECT
private:
    QGridLayout* lay;
    vector<string> compiti;
    QComboBox* Materia;
    QComboBox* classe;
    ControllerCompitiUser* ctrl;
public:
    ViewCompiti(ControllerCompitiUser* c);
    QComboBox* Materie();
    QComboBox* Classi();
    vector<string> giveLista()const;
    virtual QWidget* listaCompiti(int) const = 0;
    bool sortbyMateria();
    bool sortbyClasse();
    virtual bool sort();
public slots:
    int TotPage()const;
    void parseCompitoFile(const QString&)const;
    void FiltraRisultati();
    void commentaRisp(const QString& codice, int risposta)const;
    void viewCommento(const QString& codice, int risposta) const;
    void elimCompito(const QString& codice);
    QGridLayout* giveLayout()const;
    virtual void goNext();
    virtual void goPrev();
    virtual void reloadWindow();
protected:
    static int maxPerPage;
    int totPage;
    int currPage;
    void Header();
    void setTotPage(int tot);
};

#endif // VIEWCOMPITI_H
