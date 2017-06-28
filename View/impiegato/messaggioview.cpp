#include "messaggioview.h"
#include"../../Controller/controllerimpiegato.h"
#include <QLabel>
#include <QVBoxLayout>

MessaggioView::MessaggioView(ControllerImpiegato *ptr, QWidget *parent):QDialog(parent),
    ctrl(ptr),index(-1), data(new QLabel(this)), oggetto(new QLabel(this)),emitt(new QLabel(this)), Messaggio(new QLabel(this))
{
    QVBoxLayout* layout= new QVBoxLayout(this);
    QFont f("Times", 13);
    f.setUnderline(true);
    QLabel * title = new QLabel("Data:", this);
    title->setFont(f);
    layout->addWidget(title,0);
    layout->addWidget(data,0);
    title = new QLabel("Oggetto:", this);
    title->setFont(f);
    layout->addWidget(title,0);
    layout->addWidget(oggetto,0);
    title = new QLabel("Da:", this);
    title->setFont(f);
    layout->addWidget(title,0);
    layout->addWidget(emitt,0);
    title = new QLabel("messaggio:", this);
    title->setFont(f);
    layout->addWidget(title,0);
    layout->addWidget(Messaggio,1,Qt::AlignTop);

    f = QFont("Times", 10);
    data->setFont(f);
    oggetto->setFont(f);
    emitt->setFont(f);
    Messaggio->setFont(f);
    setWindowTitle("Nessun messaggio selezionato");
    setFixedSize(800,800);

}

void MessaggioView::SelectMessage(int index, bool ricevuta, bool OnlyUnread)
{
   data->setText(ctrl->LeggidataMail(index,ricevuta,OnlyUnread));
   oggetto->setText(ctrl->LeggiMailOgge(index, ricevuta,OnlyUnread));
   emitt->setText(ctrl->LeggiMailSender(index, ricevuta,OnlyUnread));
   Messaggio->setText(ctrl->LeggiMailTesto(index, ricevuta,OnlyUnread));
   setWindowTitle(emitt->text());

}
