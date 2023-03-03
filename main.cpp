#include "MyQtWidgets.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyQtWidgets w;
    w.show();
    return a.exec();
}
