#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include "create_accountwindow.h"

AuthorizationWindow::AuthorizationWindow(QWidget *parent)
    : QDialog(parent) // Исправлено на QDialog
    , ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
}

AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

void AuthorizationWindow::on_create_account_btn_clicked()
{
    create_accountwindow accountWindow(this);
    this -> close();
    accountWindow.exec();
}



void AuthorizationWindow::on_login_cancel_clicked()
{
    this -> close();
}

