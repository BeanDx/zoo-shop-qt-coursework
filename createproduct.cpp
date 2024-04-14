#include "createproduct.h"
#include "ui_createproduct.h"

#include <QFileDialog>
#include <QMessageBox>

CreateProduct::CreateProduct(QWidget *parent)
    : QDialog(parent)
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


void CreateProduct::on_chooseImageBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Виберіть зображення"), "",
                                                    tr("Зображення (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!fileName.isEmpty()) { } else {
        QMessageBox::warning(this, tr("Помилка!"), tr("Файл не вибраний."));
    }
}

