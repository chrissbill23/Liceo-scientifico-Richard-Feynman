#ifndef COMPITOPARSER_H
#define COMPITOPARSER_H

#include <QDialog>
class Controller;
class ControllerCompitiUser;
class CompitoParser : public QDialog
{
private:
    QString codice;
    ControllerCompitiUser* ctrl;
public:
    CompitoParser(const QString& c, ControllerCompitiUser* ct, QWidget* parent = 0);
    ControllerCompitiUser *giveController() const;
    QString giveCodice()const;
    virtual void parse() = 0;
};

#endif // COMPITOPARSER_H
