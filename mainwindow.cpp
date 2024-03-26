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
    AuthorizationWindow *authWindow = new AuthorizationWindow(this);
    connect(authWindow, &AuthorizationWindow::loginSuccessful, this, &MainWindow::updateUserEmail);
    authWindow->exec();
}

void MainWindow::updateUserEmail(QString email) {
    ui->auth_btn->setText(email);
}
