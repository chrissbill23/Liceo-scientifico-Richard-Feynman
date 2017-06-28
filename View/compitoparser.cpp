#include "compitoparser.h"

CompitoParser::CompitoParser(const QString &c, ControllerCompitiUser *ct, QWidget *parent) : QDialog(parent), codice(c), ctrl(ct)
{

}

ControllerCompitiUser *CompitoParser::giveController() const
{
    return ctrl;
}

QString CompitoParser::giveCodice() const
{
    return codice;
}
