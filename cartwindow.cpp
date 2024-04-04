#include "cartwindow.h"
#include "ui_cartwindow.h"

#include "UserSession.h"
#include <QSqlQuery>

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

CartWindow::CartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CartWindow)
{
    ui->setupUi(this);
    loadCartItems();
    connect(ui->CartlistWidget, &QListWidget::itemSelectionChanged, this, &CartWindow::updateDeleteButtonState);
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
        query.prepare("SELECT p.name, c.quantity, p.price FROM cart c JOIN products p ON c.product_id = p.product_id WHERE c.user_id = :userId");
        query.bindValue(":userId", userId);

        if (query.exec()) {
            while (query.next()) {
                QString name = query.value(0).toString();
                int quantity = query.value(1).toInt();
                double price = query.value(2).toDouble();

                double itemTotal = price * quantity;
                totalSum += itemTotal;

                QString itemText = QString("%1 x%2 - %3 грн").arg(name).arg(quantity).arg(price * quantity); // Форматируем строку для отображения
                ui->CartlistWidget->addItem(itemText); // Добавляем строку в список
            }

            ui->total_sum->setText(QString::number(totalSum, 'f', 2));
        } else {
            qDebug() << "Ошибка при загрузке товаров в корзину: " << query.lastError().text();
        }
    } else {
        // Можете показать сообщение о необходимости авторизации, если это уместно
    }
}



void CartWindow::on_Cart_cancel_btn_clicked()
{
    this -> close();
}
