#include "homegruppostud.h"
#include "../../Controller/controllerstud.h"
#include "../tuttiipostgruppo.h"
#include "personalspacegroupstud.h"
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QGroupBox>
#include "../buttongroup.h"

QGroupBox *HomeGruppoStud::loadPage()
{
    QGroupBox* temp = new QGroupBox;

    QFont f("Times",20);
    f.setBold(true);

    QLabel* title = new QLabel(daiNomeGruppo(),temp);
    title->setFont(f);

    buttonGroup* b1 = new buttonGroup("Info gruppo",daiNomeGruppo(),this);
    b1->setToolTip("Informazioni");
    b1->setFixedSize(200,50);
    connect(b1,SIGNAL(clicked(bool)),b1,SLOT(viewInfoGroup()));

    tab = new QTabWidget(temp);
    post = new TuttiIPostGruppo(ctrl,daiNomeGruppo(),temp);
    tab->addTab(post,"Tutti i post");
    if(ctrl->isIscrittoInGroup(daiNomeGruppo())){
    mySpace = new PersonalSpaceGroupStud(ctrl, daiNomeGruppo());
    tab->addTab(mySpace, "Spazio personale");
    }
    tab->setFont(QFont("Times",13));
    tab->setStyleSheet("QTabWidget::tab-bar{width: 80em;}"
                     "QTabWidget{border-radius: 15px;}"
                     "QTabWidget::pane{ border-top: 2px solid #336699;}"
                     "QTabBar::tab{min-width: 8ex; padding: 2em;}"
                     "QTabBar::tab:selected {"
                     "font: bold; color: #336699;"
                     "}");
    QIcon i(QPixmap(":/Database/immagini/reload.png"));
    QPushButton* b = new QPushButton(this);
    b->setIcon(i);
    b->setToolTip("Ricarica finestra");
    b->setFixedSize(50,50);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(reloadWindow()));
    QVBoxLayout* lay = new QVBoxLayout(temp);
    lay->addWidget(title,0,Qt::AlignHCenter);
    lay->addWidget(b,0,Qt::AlignRight);
    lay->addWidget(b1,0,Qt::AlignLeft);
    lay->addWidget(tab,1);

    temp->setLayout(lay);

    return temp;
}

HomeGruppoStud::HomeGruppoStud(ControllerStud *c, const QString& name): GruppoView(c,name),
    ctrl(c), sc(0),tab(0), post(0), mySpace(0){
    Header();
    BodyAndFooter();
    setWindowTitle(daiNomeGruppo());
    QGridLayout* p = giveLayout();
    p->addWidget(sc,1,0);
    setStyleSheet("QGroupBox{background-color: #476b6b;}"
                  "QPushButton{"
                   "background-color: green;"
                   "border: 2px solid;"
                   "border-radius: 5px 5px 5px 5px; "
                   "color: white;}"
                    "QPushButton:pressed {"
                    "background-color:#003300;}"
                  "QLabel{color: white;}");
}

void HomeGruppoStud::reloadWindow()
{
    GruppoView::reloadWindow();
    Header();

    post->reloadWindow();

    if(mySpace)
    mySpace->reloadWindow();
    else {
        mySpace = new PersonalSpaceGroupStud(ctrl,daiNomeGruppo(),this);
        tab->addTab(mySpace, "Spazio personale");
    }


}

void HomeGruppoStud::BodyAndFooter()
{
    sc = new QScrollArea(this);
    sc->setWidget(loadPage());
    sc->setWidgetResizable(true);
}

