#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "dbconnection.h"
#include "load_images.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        return -1;
    }

    // Переместите тестовый запрос сюда
    QSqlQuery query;
    if (query.exec("SELECT name, price FROM products")) {
        QString result = "Products:\n";
        while (query.next()) {
            QString name = query.value(0).toString();
            double price = query.value(1).toDouble();
            result += QString("%1 - %2\n").arg(name).arg(price);
        }
        QMessageBox::information(0, "Products List", result);
    } else {
        QMessageBox::warning(0, "Query Failed", query.lastError().text());
    }

    MainWindow w;
    w.show();

    loadImages();

    return a.exec();
}
