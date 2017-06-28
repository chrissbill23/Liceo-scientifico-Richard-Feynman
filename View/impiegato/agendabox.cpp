#include "agendabox.h"
#include <QToolButton>
#include <QIcon>
#include <QPixmap>
#include <QCalendarWidget>
#include <QLabel>
#include <QGridLayout>

AgendaBox::AgendaBox(QWidget *parent): QGroupBox(parent), Agenda(new QCalendarWidget(this))
{
    QFont f("Times", 15);
    Agenda->setGridVisible(true);
    Agenda->setMinimumDate(QDate(2008,9,1));
    Agenda->setMaximumDate(QDate(2030,7,1));
    Agenda->setStyleSheet(
                     "QToolButton {icon-size: 30px, 30px;  height: 70px; }"

                     "QAbstractItemView {selection-background-color: rgb(0, 210, 255);}"

                     "QToolButton::menu-indicator{ width: 10px;}"

                     "QToolButton::menu-indicator:pressed,"

                     "QToolButton::menu-indicator:open{ top:10px; left: 10px;}");
    QIcon icon;
    icon.addPixmap(QPixmap(":/Database/immagini/next.png"));
    (Agenda->findChild<QToolButton*>("qt_calendar_nextmonth"))->setIcon(icon);
     QIcon icon2;
    icon2.addPixmap(QPixmap(":/Database/immagini/prev.png"));
    (Agenda->findChild<QToolButton*>("qt_calendar_prevmonth"))->setIcon(icon2);
    QLabel* title= new QLabel("CALENDARIO", this);
    title->setStyleSheet("QLabel{"
                         "color: white;"
                         "padding-bottom: 0.4em; "
                         "border-bottom: 2px solid white;"
                         "border-radius: 0;}");

    title->setFixedHeight(50);
    title->setFont(f);
    QGridLayout* p= new QGridLayout(this);
    p->addWidget(title,0,0);
    p->addWidget(Agenda,1,0);
    setLayout(p);
}
