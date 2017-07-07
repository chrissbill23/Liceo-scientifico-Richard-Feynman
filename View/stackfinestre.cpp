#include "stackfinestre.h"
#include "finestre.h"
#include "../Controller/loginController.h"
#include <QCloseEvent>


void StackFinestre::AdaptStyleSheet()
{
    setStyleSheet(currentWidg->info->styleSheet());
    setWindowTitle(currentWidg->info->windowTitle());
}

void StackFinestre::TogliDistruggi(nodo* p)
{
    while(p){
    nodo*temp = p;
    removeWidget(p->info);
    p = p->next;
    delete temp;
    }
}

StackFinestre::StackFinestre(loginController *l, QStackedWidget *parent) :
    QStackedWidget(parent),logger(l),first(0), last(0), currentWidg(0){
    setMinimumSize(1024,768);
}


int StackFinestre::addWidget(QWidget *w)
{
    if(!first){
        first=last=currentWidg=new nodo(w);
        return QStackedWidget::addWidget(w);
    }
   TogliDistruggi(currentWidg->next);
    currentWidg->next=last=new nodo(w,0,currentWidg, currentWidg->index+1);
    return QStackedWidget::addWidget(w);
}

void StackFinestre::setCurrentIndex(int index)
{
    if(!first)
        return;
    if(index != currentWidg->index){
    currentWidg=first;
    }

    while(currentWidg && currentWidg->index != index){
        currentWidg=currentWidg->next;
    }
    AdaptStyleSheet();
    QStackedWidget::setCurrentWidget(currentWidg->info);
}

int StackFinestre::insertWidget(int index, QWidget *w)
{
    if(!first){
        first = last = currentWidg=new nodo(w);
        return QStackedWidget::insertWidget(0,w);
    }
    currentWidg = first;
    int i=index;
    while(i > 0 && currentWidg){
        currentWidg=currentWidg->next;
        --i;
    }
    if(currentWidg){
        nodo*temp=currentWidg;
        currentWidg=currentWidg->next;
        temp->next= new nodo(w,currentWidg, temp, index);
        while(currentWidg){
            currentWidg->info++;
            currentWidg=currentWidg->next;
        }
        currentWidg=temp;
        QStackedWidget::insertWidget(index, w);
    }
    return index;
}

void StackFinestre::setToPrevWidget()
{
    if(currentWidg && currentWidg->index > 0)
    {
        currentWidg->info->close();
        currentWidg = currentWidg->prec;
        AdaptStyleSheet();
        QStackedWidget::setCurrentWidget(currentWidg->info);
        TogliDistruggi(currentWidg->next);
        currentWidg->next = 0;
    }
}

void StackFinestre::reset()
{
    TogliDistruggi(first);
    first = last = currentWidg = 0;
}

void StackFinestre::closeEvent(QCloseEvent *event)
{
    event->accept();
   logger->closeAll();
}


StackFinestre::nodo::nodo(QWidget *w, StackFinestre::nodo *n, StackFinestre::nodo *p, int i):info(w), next(n),
    prec(p), index(i){}

StackFinestre::nodo::~nodo()
{
    if(info)
        delete info;
}

