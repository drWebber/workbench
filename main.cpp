#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QPixmap(":/images/terminal.png")));

    MainWindow w;
    w.show();

    return a.exec();
}

/*
 * 1. передать модель в делегата, затем выполнить select
*/
