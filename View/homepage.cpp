#include "homepage.h"


Homepage::Homepage(QStackedWidget *parent) :
    QStackedWidget(parent)
{
resize(1500, 1000);
setStyleSheet(" background-color: #29abe2");
}

Homepage::~Homepage(){}
