#ifndef ATTRIBUTIXML_H
#define ATTRIBUTIXML_H

#include <QDomAttr>
#include<string>
#include<vector>
#include <string>

using std::string;

class attributixml{
private:
    string nome;
    string valore;
public:
    attributixml(QDomAttr attr);
    string daiNome()const;
    string daiValore()const;


};

#endif // ATTRIBUTIXML_H
