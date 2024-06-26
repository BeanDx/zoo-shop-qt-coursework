#include "mainwindow.h"
#include "cartwindow.h"
#include "authorizationwindow.h"
#include "productitem.h"
#include "adminpanel.h"

#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "UserSession.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadCategories();
    loadProducts();

    // Подключаем сигнал выбора элемента в списке к слоту отображения деталей товара
    connect(ui->productsListWidget, &QListWidget::itemClicked, this, &MainWindow::showProductDetails);
    connect(ui->search_input, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->category_Combo_Box, &QComboBox::currentTextChanged, this, &MainWindow::onCategoryChanged);

    ui->AdminPanelBtn->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadProducts(const QString &category) {
    ui->productsListWidget->clear();
    QSqlQuery query;

    // Формирование SQL-запроса с использованием JOIN для связи таблиц products и categories
    QString queryString = "SELECT p.product_id, p.name, p.price FROM products p JOIN categories c ON p.category_id = c.id";

    // Добавляем условие WHERE, если категория не пуста
    if (!category.isEmpty()) {
        queryString += " WHERE c.name = :category";
        query.prepare(queryString);
        query.bindValue(":category", category);
    } else {
        query.prepare(queryString);
    }

    // Выполнение запроса и заполнение списка продуктами
    if (query.exec()) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            double price = query.value(2).toDouble();
            QString itemText = QString("%1 - %2 грн").arg(name).arg(price);

            QListWidgetItem* newItem = new QListWidgetItem(itemText);
            newItem->setData(Qt::UserRole, id);
            ui->productsListWidget->addItem(newItem);
        }
    } else {
        qDebug() << "Ошибка при выполнении запроса: " << query.lastError().text();
    }
}


void MainWindow::onCategoryChanged(const QString &category) {
    loadProducts(category);
}



void MainWindow::loadCategories() {
    ui->category_Combo_Box->addItem("", QVariant(-1));


    QSqlQuery query;
    if (query.exec("SELECT name FROM categories")) { // Предполагается, что у таблицы категорий есть столбец 'name'
        while (query.next()) {
            QString categoryName = query.value(0).toString();
            ui->category_Combo_Box->addItem(categoryName);
        }
    } else {
        qDebug() << "Ошибка при выполнении запроса на загрузку категорий: " << query.lastError().text();
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
        qDebug() << "Ошибка при виконанні запиту: " << query.lastError().text();
    }

    // Теперь создаем экземпляр ProductItem правильно, используя переменные
    ProductItem *productItemWindow = new ProductItem(productId, productName, productDescription, productPrice, this);
    productItemWindow->exec();
}


void MainWindow::onSearchTextChanged(const QString &text) {
    ui->productsListWidget->clear();

    QSqlQuery query;
    QString queryString = "SELECT product_id, name, price FROM products WHERE name LIKE '%" + text + "%'";
    if (query.exec(queryString)) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            double price = query.value(2).toDouble();
            QString itemText = QString("%1 - %2 грн").arg(name).arg(price);

            QListWidgetItem* newItem = new QListWidgetItem(itemText);
            newItem->setData(Qt::UserRole, id);
            ui->productsListWidget->addItem(newItem);
        }
    } else {
        qDebug() << "Error: " << query.lastError().text();
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

    if (email == "admin") {
        ui->AdminPanelBtn->setVisible(true);
    } else {
        ui->AdminPanelBtn->setVisible(false);
    }
}

void MainWindow::on_cart_btn_clicked()
{
    int userId = UserSession::getInstance().getUserId(); // Получаем ID пользователя из сессии

    if (userId == -1) {

        QMessageBox::information(this, "Реєстрація обов'язкова", "Ви повинні увійти в систему, щоб переглянути кошик.");
    } else {
        CartWindow *cartWindow = new CartWindow(this);
        cartWindow->exec();
    }
}

void MainWindow::reloadProducts() {
    loadProducts(ui->category_Combo_Box->currentText());
}

void MainWindow::on_AdminPanelBtn_clicked()
{
    AdminPanel *adminPanelWindow = new AdminPanel(this);
    adminPanelWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(adminPanelWindow, &AdminPanel::adminPanelClosed, this, &MainWindow::reloadProducts);
    adminPanelWindow->exec();
}

