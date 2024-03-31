#include "productitem.h"
#include "ui_productitem.h"

ProductItem::ProductItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProductItem)
{
    ui->setupUi(this);
}

ProductItem::~ProductItem()
{
    delete ui;
}
