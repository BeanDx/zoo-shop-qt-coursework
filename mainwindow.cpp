#include "mainwindow.h"

#include "authorizationwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::on_auth_btn_clicked()
// {

// }

void MainWindow::on_auth_btn_clicked()
{
    AuthorizationWindow authWindow(this); // Передайте 'this' как родитель, если хотите
    authWindow.exec(); // Открыть как модальное диалоговое окно
}
