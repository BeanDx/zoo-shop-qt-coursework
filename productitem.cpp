#include "productitem.h"
#include "ui_productitem.h"
#include "UserSession.h"

#include <QMessageBox>

// Конструктор, принимающий только id и parent
ProductItem::ProductItem(int id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
    , productId(id)
{
    ui->setupUi(this);
}

// Конструктор, принимающий id, name, description, price и parent
ProductItem::ProductItem(int id, const QString &name, const QString &description, double price, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
    , productId(id)
{
    ui->setupUi(this);
    setProductName(name);
    setProductDescription(description);
    setProductPrice(price);
}

ProductItem::~ProductItem()
{
    delete ui;
}

void ProductItem::setProductName(const QString &name) {
    ui->product_name->setText(name);
}

void ProductItem::setProductDescription(const QString &description) {
    ui->product_desc->setText(description);
}

void ProductItem::setProductPrice(double price) {
    ui->product_price->setText(QString::number(price, 'f', 2));
}

int ProductItem::getProductId() {
    return productId;
}

void ProductItem::addToCart() {
    int userId = UserSession::getInstance().getUserId(); // Получаем ID пользователя

    // Проверяем, авторизован ли пользователь
    if (userId == -1) { // Предполагаем, что -1 означает "пользователь не авторизован"
        QMessageBox::warning(this, "Authorization required", "To add items to your cart, you must log in to your account.");
        // Здесь можно было бы также автоматически открыть окно авторизации, если это уместно
        return; // Выходим из функции, не добавляя товар в корзину
    }

    QSqlQuery query;
    query.prepare("SELECT quantity FROM cart WHERE user_id = :userId AND product_id = :productId");
    query.bindValue(":userId", userId);
    query.bindValue(":productId", productId);
    if (query.exec() && query.next()) {
        int quantity = query.value(0).toInt() + 1;
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE cart SET quantity = :quantity WHERE user_id = :userId AND product_id = :productId");
        updateQuery.bindValue(":quantity", quantity);
        updateQuery.bindValue(":userId", userId);
        updateQuery.bindValue(":productId", productId);
        if (!updateQuery.exec()) {
            qDebug() << "Ошибка при обновлении количества товара в корзине: " << updateQuery.lastError().text();
        }
    } else {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO cart (user_id, product_id, quantity) VALUES (:userId, :productId, 1)");
        insertQuery.bindValue(":userId", userId);
        insertQuery.bindValue(":productId", productId);
        if (!insertQuery.exec()) {
            qDebug() << "Ошибка при добавлении товара в корзину: " << insertQuery.lastError().text();
        }
    }
}


void ProductItem::on_product_add_to_cart_btn_clicked() {
    addToCart();
}

void ProductItem::on_product_cancel_btn_clicked() {
    this->close();
}
