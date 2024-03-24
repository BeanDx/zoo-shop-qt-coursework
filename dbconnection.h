#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>

inline bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("zoo-shop");
    db.setUserName("beand");
    db.setPassword("Colobok123");

    if(!db.open()) {
        QMessageBox::warning(0, "Error DB", db.lastError().text());
        return false;
    }
    else {
        QMessageBox::information(0, "Nice!", "Connection OK");
        return true;
    }
}

inline void listTables()
{
    QSqlDatabase db = QSqlDatabase::database(); // Используем уже существующее соединение
    if (db.isOpen())
    {
        QStringList tables = db.tables();
        QString tableList = "Tables in the database:\n";
        foreach (QString table, tables)
        {
            tableList += table + "\n";
        }
        QMessageBox::information(0, "Database Tables", tableList);
    }
    else
    {
        QMessageBox::critical(0, "Error", "Database is not open!");
    }
}

#endif // DBCONNECTION_H
