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

    QFont f("Times", 10);
    f.setUnderline(true);
    f.setBold(true);
    if(codeBookPP.size() > indice){
        Controller* ctrl = getController();

        QIcon i1;
        int i = indice;
        bool checkPrev = false;
        if(i-1 >= 0){
        checkPrev = true;
        i1.addPixmap(QPixmap(":/Database/immagini/prev.png"));
        QPushButton* b = new QPushButton(contenuto);
        b->setIcon(i1);
        b->setFixedSize(100,150);
        b->setIconSize(QSize(100,150));
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),this,SLOT(goPrev()));
        lay->addWidget(b,1,0,1,1,Qt::AlignLeft);
            if(indice + 1 == codeBookPP.size())
                lay->setColumnStretch(1,1);
        }

        QLabel* title = new QLabel(ctrl->daiTitoloLibro(QString::fromStdString(codeBookPP[indice])));
        title->setFont(f);
        title->setAlignment(Qt::AlignCenter);
        lay->addWidget(title,0,1,1,1,Qt::AlignHCenter);

        QLabel* copert = new QLabel(contenuto);
        copert->setFixedSize(520,320);
        copert->setStyleSheet("color: red;");
        const QString& copertina = ctrl->daiCopertinaLibro(QString::fromStdString(codeBookPP[indice]));
        if(copertina == ""){
            copert->setText("Non ci sono copertine per questo libro");
            copert->setFont(f);
            copert->setAlignment(Qt::AlignCenter);
        }
        else{
            copert->setPixmap(QPixmap(copertina));
            copert->setScaledContents(true);
        }
        lay->addWidget(copert,1,1,1,1, Qt::AlignHCenter);


        bibliobutton* b = new bibliobutton("Dettagli",QString::fromStdString(codeBookPP[indice]), false,"",this);
        b->setFixedSize(200,30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewInfoLibro()));
        lay->addWidget(b,2,1,1,1,Qt::AlignHCenter);

        b = new bibliobutton("Leggi",QString::fromStdString(codeBookPP[indice]), false,"",this);
        b->setFixedSize(200,30);
        b->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b,SIGNAL(clicked(bool)),b,SLOT(viewLibro()));

        lay->addWidget(b,3,1,1,1,Qt::AlignHCenter);

        if(indice + 1 < codeBookPP.size()){
        i1.addPixmap(QPixmap(":/Database/immagini/next.png"));
        QPushButton* b2 = new QPushButton(contenuto);
        b2->setIcon(i1);
        b2->setFixedSize(100,150);
        b2->setIconSize(QSize(100,150));
        b2->setCursor(QCursor(Qt::PointingHandCursor));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(goNext()));
        lay->addWidget(b2,1,2,1,1,Qt::AlignRight);
        if(!checkPrev)
            lay->setColumnStretch(1,1);
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
    QFont f("Times", 14);
    f.setBold(true);

    QLabel* lab = new QLabel("PRIMO PIANO:",this);
    lab->setFont(f);
    lab->setStyleSheet("color: #663300;");

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
