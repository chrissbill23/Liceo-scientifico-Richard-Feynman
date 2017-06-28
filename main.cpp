#include <QApplication>
#include "./Controller/loginController.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   loginController* p= new loginController;
   p->comincia();
    return a.exec();
}
