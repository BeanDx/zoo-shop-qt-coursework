#include "cartwindow.h"
#include "ui_cartwindow.h"

CartWindow::CartWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CartWindow)
{
    ui->setupUi(this);
    connect(ui->CartlistWidget, &QListWidget::itemSelectionChanged, this, &CartWindow::updateDeleteButtonState);
}

CartWindow::~CartWindow()
{
    delete ui;
}

void CartWindow::updateDeleteButtonState() {
    ui->Cart_Delete_Btn->setEnabled(!ui->CartlistWidget->selectedItems().isEmpty());
}




void CartWindow::on_Cart_cancel_btn_clicked()
{
    this -> close();
}
