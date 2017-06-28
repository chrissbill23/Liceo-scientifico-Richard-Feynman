#ifndef STACKFINESTRE_H
#define STACKFINESTRE_H

#include <QStackedWidget>

class loginController;
class StackFinestre : public QStackedWidget
{
private:
    class nodo{
    public:
        QWidget* info;
        nodo*next;
        nodo* prec;
        int index;
        nodo(QWidget* w = 0, nodo* n = 0, nodo*p = 0, int i = 0);
        ~nodo();
    };

    loginController* logger;
    nodo*first;
    nodo*last;
    nodo* currentWidg;
    void AdaptStyleSheet();
    void TogliDistruggi(nodo *p);
public:
   StackFinestre (loginController* l,QStackedWidget *parent = 0);
   int addWidget(QWidget *w);
   void setCurrentIndex(int index);
   int insertWidget(int index, QWidget *w);
   void setToPrevWidget();
   void reset();
protected:
   void closeEvent(QCloseEvent* event);
};

#endif
