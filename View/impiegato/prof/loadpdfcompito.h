#ifndef LOADPDFCOMPITO_H
#define LOADPDFCOMPITO_H

#include "createfilecompito.h"

class LoadPDFcompito : public createFileCompito
{
    Q_OBJECT
private:
    QLineEdit* filePath;
public:
    LoadPDFcompito(ControllerProf* c, QWidget* parent);
public slots:
    bool salva();
    void loadFile();
};

#endif // LOADPDFCOMPITO_H
