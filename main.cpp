#include "mainwindow.h"
#include "dbconnection.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
