#include "buttongroup.h"
#include "gruppoview.h"

buttonGroup::buttonGroup(const QString& text, const QString& name, GruppoView *parent, const QString &cath,  int p): QPushButton(text,parent),
    nomeGroup(name), cathegory(cath),post(p), fi(parent){}

QString buttonGroup::giveGroupName() const
{
    return nomeGroup;
}

void buttonGroup::viewInfoGroup() const
{
    if(fi)
        fi->InfoGruppo(nomeGroup);
}

void buttonGroup::GiveHomeGroup()
{
    if(fi)
    fi->HomePageGroup(nomeGroup);
}

void buttonGroup::GotoPost()
{
    fi->OpenPost(post);
}

void buttonGroup::IscriviAGroup()
{
    if(fi && nomeGroup != "")
        fi->IscriviMiAGroup(nomeGroup);
}

void buttonGroup::removeConnectedMember()
{
    if(fi && nomeGroup != "")
        fi->RemoveMeFromGroup(nomeGroup);
}


void buttonGroup::deletePost()
{
    if(post != -1)
        fi->deletePost(post);
}
