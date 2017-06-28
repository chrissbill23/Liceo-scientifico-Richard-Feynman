#ifndef POPUPDIALOG_H
#define POPUPDIALOG_H

#include <QDialog>

class QGridLayout;
class QGroupBox;
class QScrollArea;
class popUpDialog : public QDialog
{
private:
    QList<QWidget*> l;
    unsigned short int maxPerRow;
    unsigned short int maxPerPage;
    unsigned short int currRow;
    unsigned short int currCol;
    QGroupBox* group;
    QGridLayout* p;
    QScrollArea* scroll;
public:
    popUpDialog(unsigned short int mr,unsigned short int mp, QWidget* parent=0);
    void push_back_Widget(QWidget*);
    void goToNextRow();
    ~popUpDialog();
};

#endif // POPUPDIALOG_H
