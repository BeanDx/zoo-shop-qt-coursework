#include "mainwindow.h"
#include "cartwindow.h"
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
    connect(ui->search_input, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadProducts() {
    QSqlQuery query;
    // Измените запрос, чтобы получать id продукта
    if (query.exec("SELECT product_id, name, price FROM products")) {
        while (query.next()) {
            int id = query.value(0).toInt(); // Получаем id
            QString name = query.value(1).toString();
            double price = query.value(2).toDouble();
            QString itemText = QString("%1 - %2 грн").arg(name).arg(price);

            // Создаем новый элемент списка
            QListWidgetItem* newItem = new QListWidgetItem(itemText);
            newItem->setData(Qt::UserRole, id); // Сохраняем id в данных элемента
            ui->productsListWidget->addItem(newItem);
        }
    } else {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
    }
}


void MainWindow::showProductDetails(QListWidgetItem *item) {
    int productId = item->data(Qt::UserRole).toInt(); // Извлекаем id продукта

    QString productName = item->text().split(" - ").first();

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

    // Теперь создаем экземпляр ProductItem правильно, используя переменные
    ProductItem *productItemWindow = new ProductItem(productId, productName, productDescription, productPrice, this);
    productItemWindow->exec();
}


void MainWindow::onSearchTextChanged(const QString &text) {
    ui->productsListWidget->clear(); // Очищаем список перед заполнением новыми данными

    QSqlQuery query;
    QString queryString = "SELECT name, price FROM products WHERE name LIKE '%" + text + "%'";
    if (query.exec(queryString)) {
        while (query.next()) {
            QString name = query.value(0).toString();
            double price = query.value(1).toDouble();
            QString itemText = QString("%1 - %2 грн").arg(name).arg(price);
            ui->productsListWidget->addItem(itemText);
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

void MainWindow::on_cart_btn_clicked()
{
    CartWindow *cartWindow = new CartWindow(this); // Создаем диалоговое окно корзины
    cartWindow->exec(); // Открываем окно как модальное диалоговое окно
}
