#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

namespace Ui {
class ProductItem;
}

class ProductItem : public QDialog
{
    Q_OBJECT

public:
    // Конструктор для ситуаций, когда мы знаем только id и parent
    explicit ProductItem(int id, QWidget *parent = nullptr);
    // Конструктор для полного набора данных о продукте
    ProductItem(int id, const QString &name, const QString &description, double price, QWidget *parent = nullptr);
    ~ProductItem();

    void setProductName(const QString &name);
    void setProductDescription(const QString &description);
    void setProductPrice(double price);

    int getProductId(); // Получить ID продукта

private slots:
    void on_product_cancel_btn_clicked();
    void on_product_add_to_cart_btn_clicked();

private:
    Ui::ProductItem *ui;
    int productId;

    void addToCart();
};

#endif // PRODUCTITEM_H
