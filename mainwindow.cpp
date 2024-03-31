#include "mainwindow.h"
#include "authorizationwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadProducts(); // Вызов функции загрузки продуктов при инициализации окна
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadProducts() {
    QSqlQuery query;
    if (query.exec("SELECT name, price FROM products")) {
        while (query.next()) {
            QString name = query.value(0).toString();
            double price = query.value(1).toDouble();
            QString itemText = QString("%1 - %2 грн").arg(name).arg(price);
            ui->productsListWidget->addItem(itemText); // Предполагается, что у вас есть QListWidget с именем productsListWidget в вашем UI
        }
    } else {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
    }
}

void MainWindow::on_auth_btn_clicked()
{
    AuthorizationWindow *authWindow = new AuthorizationWindow(this);
    connect(authWindow, &AuthorizationWindow::loginSuccessful, this, &MainWindow::updateUserEmail);
    authWindow->exec();
}

void MainWindow::updateUserEmail(QString email) {
    ui->auth_btn->setText(email);
}
