#include "mainwindow.h"
#include "authorizationwindow.h"
#include "productitem.h" // Убедитесь, что подключили заголовочный файл вашего окна с деталями товара
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

    // Подключаем сигнал выбора элемента в списке к слоту отображения деталей товара
    connect(ui->productsListWidget, &QListWidget::itemClicked, this, &MainWindow::showProductDetails);

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

void MainWindow::showProductDetails(QListWidgetItem *item) {
    // Получаем имя продукта
    QString productName = item->text().split(" - ").first();

    // Подготавливаем запрос для извлечения описания и цены из базы данных по имени продукта
    QSqlQuery query;
    query.prepare("SELECT description, price FROM products WHERE name = :name");
    query.bindValue(":name", productName);

    QString productDescription;
    double productPrice = 0.0;

    if (query.exec() && query.first()) {
        productDescription = query.value(0).toString();
        productPrice = query.value(1).toDouble();
    } else {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
    }

    // Создаем экземпляр ProductItem, передавая имя, описание и цену продукта
    ProductItem *productItemWindow = new ProductItem(productName, productDescription, productPrice, this);
    productItemWindow->exec(); // Отображаем окно с деталями товара
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
