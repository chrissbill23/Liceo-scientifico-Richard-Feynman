#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QStackedWidget>


class Homepage : public QStackedWidget
{
    Q_OBJECT

public:
    explicit Homepage(QStackedWidget *parent = 0);
    ~Homepage();


};

#endif // HOMEPAGE_H
