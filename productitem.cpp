#include "productitem.h"
#include "ui_productitem.h"
#include "UserSession.h"
#include <QBuffer>

#include <QMessageBox>

// Конструктор, принимающий только id и parent
ProductItem::ProductItem(int id, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
    , productId(id)
{
    ui->setupUi(this);
    loadProductImage();
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
    loadProductImage();
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
    if (userId == -1) {
        QMessageBox::warning(this, "Потрібна авторизація", "Щоб додати товари до кошика, ви повинні увійти у свій обліковий запис.");
        return;
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
        if (updateQuery.exec()) {
            QMessageBox::information(this, "Пункт оновлено", "У вашому кошику оновлено кількість товару.");
        } else {
            qDebug() << "Ошибка при обновлении количества товара в корзине: " << updateQuery.lastError().text();
        }
    } else {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO cart (user_id, product_id, quantity) VALUES (:userId, :productId, 1)");
        insertQuery.bindValue(":userId", userId);
        insertQuery.bindValue(":productId", productId);
        if (insertQuery.exec()) {
            QMessageBox::information(this, "Пункт додано", "Товар додано у ваш кошик.");
        } else {
            qDebug() << "Помилка при додаванні товару в кошик: " << insertQuery.lastError().text();
        }
    }
}

void ProductItem::loadProductImage() {
    QSqlQuery query;
    QString queryString = QString("SELECT image FROM products WHERE product_id = %1").arg(productId);
    if (query.exec(queryString) && query.next()) {
        QByteArray imageData = query.value(0).toByteArray();
        QPixmap pixmap;
        if (!pixmap.loadFromData(imageData)) {
            qDebug() << "Неможливо завантажити зображення з даних";
        } else {
            ui->productImageLabel->setPixmap(pixmap.scaled(ui->productImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    } else {
        qDebug() << "Ошибка загрузки изображения: " << query.lastError().text();
    }
}








void ProductItem::on_product_add_to_cart_btn_clicked() {
    addToCart();
}

void ProductItem::on_product_cancel_btn_clicked() {
    this->close();
}
