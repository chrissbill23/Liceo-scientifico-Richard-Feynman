#include "primopianowidg.h"
#include "bibliobutton.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

void PrimoPianoWidg::switchBookPP(unsigned int indice)
{
    if(contenuto)
        delete contenuto;
    contenuto = new QGroupBox(this);

    contenuto->setStyleSheet("QGroupBox{border: 0;}");
    QGridLayout* lay = new QGridLayout(contenuto);

    QFont f("Times", 13);
    f.setUnderline(true);
    f.setBold(true);
    if(codeBookPP.size() > indice){
        Controller* ctrl = getController();

        QIcon i1;
        int i = indice;
        if(i-1 >= 0){
        i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
        QPushButton* b = new QPushButton(contenuto);
        b->setIcon(i1);
        b->setFixedSize(100,300);
        b->setIconSize(QSize(100,300));
        b->setStyleSheet("QPushButton{"
                         "background-color: #29abe2;"
                         "border: 2px solid;"
                         "border-radius: 5px 5px 5px 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                         "background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        lay->addWidget(b,1,0,1,1,Qt::AlignLeft);
        }

        QLabel* title = new QLabel(ctrl->daiTitoloLibro(QString::fromStdString(codeBookPP[indice])));
        title->setStyleSheet("color: black;");
        title->setFont(f);
        lay->addWidget(title,0,1,1,1,Qt::AlignHCenter);

        QLabel* copert = new QLabel(contenuto);
        copert->setFixedSize(800,300);
        copert->setStyleSheet("color: #29abe2;");
        const QString& copertina = ctrl->daiCopertinaLibro(QString::fromStdString(codeBookPP[indice]));
        if(copertina == ""){
            copert->setText("Non ci sono copertine per questo libro");
            copert->setFont(f);
        }
        else{
            copert->setPixmap(QPixmap(copertina));
            copert->setScaledContents(true);
        }
        lay->addWidget(copert,1,1,1,1, Qt::AlignHCenter);


        bibliobutton* b = new bibliobutton("Info libro",QString::fromStdString(codeBookPP[indice]), false,"",this);
        b->setFixedSize(200,30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #29abe2; "
                         "border-radius: 5px 5px 5px 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
        lay->addWidget(b,2,1,1,1,Qt::AlignHCenter);

        b = new bibliobutton("Leggi libro",QString::fromStdString(codeBookPP[indice]), false,"",this);
        b->setFixedSize(200,30);
        b->setStyleSheet("QPushButton{"
                         "background-color: #29abe2; "
                         "border-radius: 5px 5px 5px 5px; "
                         "color: white;}"
                         "QPushButton:pressed {"
                        " background-color:#003300;}");
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));

        lay->addWidget(b,3,1,1,1,Qt::AlignHCenter);

        if(indice + 1 < codeBookPP.size()){
        i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
        QPushButton* b2 = new QPushButton(contenuto);
        b2->setIcon(i1);
        b2->setFixedSize(100,300);
        b2->setIconSize(QSize(100,300));
        b2->setStyleSheet("QPushButton{"
                            "background-color: #29abe2;"
                            "border: 2px solid;"
                            "border-radius: 5px 5px 5px 5px; "
                            "color: white;}"
                            "QPushButton:pressed {"
                            "background-color:#003300;}");
        b2->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
        lay->addWidget(b2,1,2,1,1,Qt::AlignRight);
        }

    }
    else{
        QLabel* lab  = new QLabel("Non ci sono nuovi arrivi", contenuto);
        lab->setFont(f);
        lab->setStyleSheet("color: black;");

        lay->addWidget(lab, 0,0,1,5, Qt::AlignTop);
    }

    layout->addWidget(contenuto, 1);
}

PrimoPianoWidg::PrimoPianoWidg(Controller* c, QWidget* parent) : FinestreBiblioteca(c,parent),
    currBook(0), contenuto(0),
    layout(new QVBoxLayout(this))
{
    codeBookPP = c->codiciLibriPrimoPiano();
    BodyAndFooter();
}

void PrimoPianoWidg::reloadWindow()
{
    currBook = 0;
    codeBookPP = getController()->codiciLibriPrimoPiano();
    switchBookPP(0);
}

void PrimoPianoWidg::BodyAndFooter()
{
    QFont f("Times", 15);
    f.setBold(true);
    f.setUnderline(true);

    QLabel* lab = new QLabel("Primo piano:",this);
    lab->setFont(f);
    lab->setStyleSheet("color: black;");

    layout->addWidget(lab, 0);
    switchBookPP(0);

    setLayout(layout);
}

void PrimoPianoWidg::goNext()
{
    currBook++;

    int tot = codeBookPP.size();
    if(currBook < tot)
        switchBookPP(currBook);
}

void PrimoPianoWidg::goPrev()
{
    currBook--;
    if(currBook < 0)
        currBook = 0;
        switchBookPP(currBook);

}
