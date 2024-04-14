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


void CreateProduct::on_chooseImageBtn_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this,
                                             tr("Выберите изображение"), "",
                                             tr("Изображения (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!imagePath.isEmpty()) {
        qDebug() << "Выбран файл:" << imagePath;
        // Опционально: можно обновить элемент интерфейса, показывающий выбранное изображение
        // Например, если у вас есть QLabel для показа изображения:
        // ui->imageLabel->setPixmap(QPixmap(imagePath));
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не выбран."));
        qDebug() << "Файл не выбран";
    }
}



void CreateProduct::on_createProductBtn_clicked()
{
    // Считывание данных из полей ввода
    QString name = ui->nameProduct_input->text();
    QString description = ui->descriptionProduct_input->toPlainText();
    double price = ui->priceProduct_input->text().toDouble();

    // Проверка корректности пути к изображению
    if (imagePath.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Необходимо выбрать изображение для продукта!"));
        return;
    }

    // Создание и подготовка SQL запроса
    QSqlQuery query;
    // Добавляем category_id со значением 3
    query.prepare("INSERT INTO products (name, description, price, image, category_id) VALUES (:name, :description, :price, :image, :category_id)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":price", price);
    query.bindValue(":image", imagePath);
    query.bindValue(":category_id", 3); // Здесь указываем, что category_id всегда будет 3

    // Выполнение запроса и обработка результата
    if (!query.exec()) {
        QMessageBox::critical(this, tr("Помилка вставки"), query.lastError().text());
    } else {
        QMessageBox::information(this, tr("Успіх"), tr("Товар успішно доданий до бази даних!"));
        this->close();
    }
}



