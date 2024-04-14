#include "createproduct.h"
#include "ui_createproduct.h"

CreateProduct::CreateProduct(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateProduct)
{
    ui->setupUi(this);
}

CreateProduct::~CreateProduct()
{
    delete ui;
}

void CreateProduct::on_cancel_btn_clicked()
{
    this -> close();
}

