#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QPushButton>

class GruppoView;
class buttonGroup: public QPushButton
{
    Q_OBJECT
private:
    QString nomeGroup;
    QString cathegory;
    int post;
    GruppoView* fi;
public:
    buttonGroup(const QString &text, const QString &name, GruppoView *parent=0, const QString& cath="", int p=-1);
public slots:
    QString giveGroupName()const;
    void viewInfoGroup()const;
    void GiveHomeGroup();
    void GotoPost();
    void IscriviAGroup();
    void removeConnectedMember();
    void deletePost();
};

#endif // BUTTONGROUP_H
