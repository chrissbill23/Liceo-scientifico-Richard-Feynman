#ifndef GRUPPOVIEW_H
#define GRUPPOVIEW_H


#include <vector>
#include <string>
#include "finestre.h"
using std::vector;
using std::string;
class QGridLayout;
class ControllerGruppoUser;
class QGroupBox;
class GruppoView: public Finestre
{
    Q_OBJECT
private:
    ControllerGruppoUser* ctrl;
    QString nomeGroup;
    QGridLayout* p;
    QGroupBox* head;
public:
    GruppoView(ControllerGruppoUser* c = 0, const QString& name = "", QWidget* parent = 0);
    int totPost()const;
    QString daiNomeGruppo()const;
    vector<string> InfoPost(unsigned int i);
    void OpenPost(int i);
    QGridLayout* giveLayout()const;
protected:
    void Header();
    void BodyAndFooter();
    vector<int> GiveIndexesPost(const QString &key = "")const;
public slots:
    void reloadWindow();
    virtual void IscriviMiAGroup(const QString& group);
    virtual void RemoveMeFromGroup(const QString & group);
    void CreaNuovoPost();
    virtual void deletePost(unsigned int);
    virtual void HomePageGroup(const QString &);
    void InfoGruppo(const QString& group)const;


};

#endif // GRUPPOVIEW_H
