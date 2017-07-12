#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QIcon icon;
    icon.addPixmap(QPixmap(":/images/terminal.png"));
    w.setWindowIcon(icon);

    w.show();

    return a.exec();
}

/*
 * 1. передать модель в делегата, затем выполнить select
*/
