#include "attributixml.h"

attributixml::attributixml(QDomAttr attr):nome(""),valore("")
{
    if(!attr.isNull()){
    nome=attr.name().toStdString();
    valore=attr.value().toStdString();
    }
}

string attributixml::daiNome() const
{
    return nome;
}

string attributixml::daiValore() const
{
    return valore;
}
