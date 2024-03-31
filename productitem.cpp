#include "productitem.h"
#include "ui_productitem.h"

// Конструктор, принимающий только parent
ProductItem::ProductItem(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
{
    ui->setupUi(this);
}

// Конструктор, принимающий name и parent
ProductItem::ProductItem(const QString &name, const QString &description, double price, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
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
    ui->product_price->setText(QString::number(price, 'f', 2)); // форматируем число как строку с двумя знаками после запятой
}

void ProductItem::on_product_cancel_btn_clicked()
{
    this -> close();
}

