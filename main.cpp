#include "mainwindow.h"
#include "dbconnection.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        // Если соединение не удалось, выходим из приложения
        return -1;
    }

    // Соединение успешно, продолжаем
    MainWindow w;
    w.show();

    return a.exec();
}
