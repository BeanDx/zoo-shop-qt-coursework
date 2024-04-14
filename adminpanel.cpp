#include "adminpanel.h"
#include "ui_adminpanel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

AdminPanel::AdminPanel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    loadProducts();

    connect(ui->deleteItemAdminPanel, &QPushButton::clicked, this, &AdminPanel::onDeleteItemClicked);

}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_cancel_btn_clicked()
{
    emit adminPanelClosed();
    this -> close();
}

void AdminPanel::loadProducts() {
    ui->adminPanelListWidget->clear();
    QSqlQuery query("SELECT product_id, name, price FROM products");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        double price = query.value(2).toDouble();
        QString itemText = QString("%1 - %2 грн").arg(name).arg(price);
        QListWidgetItem* newItem = new QListWidgetItem(itemText);
        newItem->setData(Qt::UserRole, id);
        ui->adminPanelListWidget->addItem(newItem);
    }
}

void AdminPanel::onDeleteItemClicked() {
    QListWidgetItem *currentItem = ui->adminPanelListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Помилка", "Товар не вибраний!");
        return;
    }
    int productId = currentItem->data(Qt::UserRole).toInt();
    qDebug() << "Product ID to delete: " << productId;

    QSqlQuery query;
    query.prepare("DELETE FROM products WHERE product_id = :id");
    query.bindValue(":id", productId);
    if (query.exec()) {
        delete currentItem;
        QMessageBox::information(this, "Успішно", "Товар видалено.");
        loadProducts();
    } else {
        QMessageBox::critical(this, "Помилка", "Неможливо видалити товар: " + query.lastError().text());
    }
}


// void AdminPanel::onChangeItemClicked() {
//     QListWidgetItem *currentItem = ui->adminPanelListWidget->currentItem();
//     if (!currentItem) {
//         QMessageBox::warning(this, "Ошибка", "Товар не выбран!");
//         return;
//     }
//     int productId = currentItem->data(Qt::UserRole).toInt();

//     ProductForm *form = new ProductForm(this, productId); // Диалог изменения существующего товара
//     form->exec();
//     loadProducts(); // Перезагрузить список товаров после изменения
// }

