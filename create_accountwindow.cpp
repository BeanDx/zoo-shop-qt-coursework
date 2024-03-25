#include "create_accountwindow.h"
#include "ui_create_accountwindow.h"

#include "authorizationwindow.h"

create_accountwindow::create_accountwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::create_accountwindow)
{
    ui->setupUi(this);
}

create_accountwindow::~create_accountwindow()
{
    delete ui;
}

void create_accountwindow::on_createAccount_cancel_btn_clicked()
{
    this -> close();
}


void create_accountwindow::on_createAccount_login_clicked()
{
    AuthorizationWindow authWindow(this);
    this->close();
    authWindow.exec();
}

