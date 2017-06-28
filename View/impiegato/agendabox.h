#ifndef AGENDABOX_H
#define AGENDABOX_H

#include <QGroupBox>

class QCalendarWidget;
class AgendaBox: public QGroupBox
{
private:
    QCalendarWidget* Agenda;
public:
    AgendaBox(QWidget* parent);
};

#endif // AGENDAVIEW_H
