#ifndef COMPITOPARSERXML_H
#define COMPITOPARSERXML_H

#include "compitoparser.h"

class QVBoxLayout;
class QScrollArea;
class QLabel;

class CompitoParserXml : public CompitoParser
{
    Q_OBJECT
private:
    QScrollArea* sc;
    QVBoxLayout* layout;
    QPushButton* risultDM;
    QPushButton* salva;
    QLabel* valAutomatica;

    bool hasAnsw;
    void emptyScrollbar();
public:
    CompitoParserXml(const QString & c, ControllerCompitiUser *ct, QWidget* parent = 0);
    void parse();
public slots:
    void CorrezioneAutomatica()const;
    void salvaRisposta();
};

#endif // COMPITOPARSERXML_H
