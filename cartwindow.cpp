#include "cartwindow.h"
#include "ui_cartwindow.h"

#include "UserSession.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

CartWindow::CartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CartWindow)
{
    ui->setupUi(this);
    loadCartItems();
    connect(ui->CartlistWidget, &QListWidget::itemSelectionChanged, this, &CartWindow::updateDeleteButtonState);
    connect(ui->Cart_Delete_Btn, &QPushButton::clicked, this, &CartWindow::on_Cart_Delete_Btn_clicked); // Подключаем кнопку удаления
}

CartWindow::~CartWindow()
{
    delete ui;
}

void CartWindow::updateDeleteButtonState() {
    ui->Cart_Delete_Btn->setEnabled(!ui->CartlistWidget->selectedItems().isEmpty());
}

void CartWindow::loadCartItems() {
    ui->CartlistWidget->clear(); // Очищаем список перед загрузкой новых элементов
    int userId = UserSession::getInstance().getUserId();
    double totalSum = 0.0;

    if (userId != -1) { // Проверяем, что пользователь авторизован
        QSqlQuery query;
        query.prepare("SELECT c.cart_id, p.name, c.quantity, p.price FROM cart c JOIN products p ON c.product_id = p.product_id WHERE c.user_id = :userId");
        query.bindValue(":userId", userId);

        if (query.exec()) {
            while (query.next()) {
                int cartId = query.value(0).toInt();
                QString name = query.value(1).toString();
                int quantity = query.value(2).toInt();
                double price = query.value(3).toDouble();

                double itemTotal = price * quantity;
                totalSum += itemTotal;

                QString itemText = QString("%1 x%2 - %3 грн").arg(name).arg(quantity).arg(price * quantity);
                QListWidgetItem* item = new QListWidgetItem(itemText);
                item->setData(Qt::UserRole, cartId); // Сохраняем cart_id в пользовательских данных элемента
                ui->CartlistWidget->addItem(item);
            }

            ui->total_sum->setText(QString::number(totalSum, 'f', 2));
        } else {
            qDebug() << "Ошибка при загрузке товаров в корзину: " << query.lastError().text();
        }
    } else {
        // Можете показать сообщение о необходимости авторизации, если это уместно
    }
}

void CartWindow::on_Cart_Delete_Btn_clicked() {
    QListWidgetItem *selectedItem = ui->CartlistWidget->currentItem();
    if (selectedItem) {
        int cartId = selectedItem->data(Qt::UserRole).toInt();

        QSqlQuery query;
        query.prepare("DELETE FROM cart WHERE cart_id = :cartId");
        query.bindValue(":cartId", cartId);
        if (!query.exec()) {
            qDebug() << "Ошибка при удалении товара из корзины: " << query.lastError().text();
        } else {
            loadCartItems(); // Перезагружаем элементы корзины, чтобы обновить список и общую сумму
        }
    }
}

void CartWindow::on_Cart_cancel_btn_clicked()
{
    this->close();
}


