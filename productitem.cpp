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
ProductItem::ProductItem(const QString &name, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductItem)
{
    ui->setupUi(this);
    setProductName(name);
    // Если вы хотите также инициализировать описание, добавьте соответствующий код здесь
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

void ProductItem::on_product_cancel_btn_clicked()
{
    this -> close();
}

