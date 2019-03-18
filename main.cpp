#include "MainWindowFME.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowFME w;
    w.show();

    return a.exec();
}
