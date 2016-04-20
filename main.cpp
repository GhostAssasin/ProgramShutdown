#include "mainwindow.h"
#include <QApplication>
#include <QProxyStyle>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
