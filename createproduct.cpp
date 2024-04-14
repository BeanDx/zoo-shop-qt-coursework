#include "createproduct.h"
#include "ui_createproduct.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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

void CreateProduct::on_createProductBtn_clicked() {
    QString name = ui->nameProduct_input->text();
    QString description = ui->descriptionProduct_input->toPlainText();
    double price = ui->priceProduct_input->text().toDouble();

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Виберіть зображення"), "", tr("Зображення (*.png *.jpg *.jpeg)"));
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Помилка"), tr("Необхідно вибрати зображення для продукту!"));
        return;
    }

    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл изображения."));
        return;
    }
    QByteArray imageData = file.readAll();

    QSqlQuery query;
    query.prepare("INSERT INTO products (name, description, price, image, category_id) VALUES (:name, :description, :price, :image, :category_id)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":price", price);
    query.bindValue(":image", imageData);
    query.bindValue(":category_id", 3);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Помилка вставки"), query.lastError().text());
    } else {
        QMessageBox::information(this, tr("Успіх"), tr("Товар успішно доданий до бази даних!"));
        this->close();
    }
}





