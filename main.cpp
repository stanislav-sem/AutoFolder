#include "autofolder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    autoFolder w;
    w.show();
    return a.exec();
}
