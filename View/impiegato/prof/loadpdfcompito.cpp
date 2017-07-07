#include "loadpdfcompito.h"
#include "../../../Controller/controllerprof.h"
#include "createcompito.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QDate>

LoadPDFcompito::LoadPDFcompito(ControllerProf *c, QWidget *parent) : createFileCompito(c,parent), filePath(new QLineEdit(this))
{
    loadHeader();

    filePath->setFixedHeight(50);
    filePath->setFont(QFont("Times",14));

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(filePath,0);

    QPushButton* b = new QPushButton("Sfoglia",this);
    b->setFixedSize(150,40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    b->setFont(QFont("Times",9));
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadFile()));
    lay->addWidget(b,1);

    giveLayout()->addLayout(lay);

    b = new QPushButton("Carica file", this);
    b->setFixedHeight(40);
    b->setCursor(QCursor(Qt::PointingHandCursor));
    lay->addWidget(b,0,Qt::AlignTop);
    CreateCompito* grandParent = giveGrandParent();
    if(grandParent)
    connect(b,SIGNAL(clicked(bool)),grandParent,SLOT(salvaPdf()));

    giveLayout()->addWidget(b,1);

    setWindowTitle("Aggiungi compito pdf");

}

bool LoadPDFcompito::salva()
{
    if(isOk()){
    QLabel* error = giveError();
    if(filePath->text() == ""){

      error->setText("Nessun file selezionato");
      error->setStyleSheet("color: red;");
      return false;
    }
    return giveController()->loadCompitoPdf(filePath->text(),
                                            QDate::currentDate().toString("dd/MM/yyyy"),
                                             giveTitolo()->text(),
                                             giveDescr()->toPlainText(),
                                             giveMateria()->itemData(giveMateria()->currentIndex()).toString(),
                                             giveClasse()->itemData(giveClasse()->currentIndex()).toString());

    }
    return false;
}

void LoadPDFcompito::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(0,
            tr("Seleziona il file"), "",
            tr(" (*.pdf)"));

        if (fileName.isEmpty())
            return;
        else {
            filePath->setText(fileName);
        }
}
