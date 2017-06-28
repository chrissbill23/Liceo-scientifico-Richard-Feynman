#ifndef COMPITINIWIDGBOX_H
#define COMPITINIWIDGBOX_H

#include <QGroupBox>

class FinestreProf;
class CompitiniWidgBox : public QGroupBox
{
private:
    FinestreProf* fi;
public:
    CompitiniWidgBox(FinestreProf* parent);
};

#endif // COMPITINIWIDGBOX_H
