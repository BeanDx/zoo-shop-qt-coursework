#include "mainwindow.h"
#include "dbconnection.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Если соединение успешно, показываем список таблиц
    if (createConnection()) {
        listTables();
    }

    w.show();
    return a.exec();
}
