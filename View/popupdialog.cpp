#include "popupdialog.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QScrollArea>

popUpDialog::popUpDialog(unsigned short mr, unsigned short mp, QWidget *parent): QDialog(parent), maxPerRow(mr),
    maxPerPage(mp),currRow(0), currCol(0),group(new QGroupBox(this)),
    p(new QGridLayout(group)), scroll(new QScrollArea(this)){
    if(maxPerRow == 0)
        maxPerRow = 1;
    if(maxPerPage == 0)
        maxPerPage = 1;
    group->setLayout(p);
    group->setStyleSheet("QGroupBox{border: 0;}");
    scroll->setWidget(group);
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(scroll);
    setLayout(lay);
}

void popUpDialog::push_back_Widget(QWidget* w)
{
    if(currRow < maxPerPage){
    l.push_front(w);
    p->addWidget(w,currRow, currCol,1,1,Qt::AlignTop);
    ++currCol;
    if(currCol >= maxPerRow){
        currCol = 0;
        ++currRow;
    }
    }

}

void popUpDialog::goToNextRow()
{
    ++currRow;
    currCol = 0;
}
popUpDialog::~popUpDialog()
{
    qDeleteAll(l);
}
