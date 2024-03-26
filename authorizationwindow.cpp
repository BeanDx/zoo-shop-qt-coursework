#include "authorizationwindow.h"
#include "ui_authorizationwindow.h"

#include "dbconnection.h"

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


void AuthorizationWindow::on_login_btn_clicked()
{
    QString email = ui->login_email_input->text();
    QString password = ui->login_password_input->text();

    if(email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Вход невозможен", "Пожалуйста, заполните все поля.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = :email AND user_password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if(query.exec()) {
        if(query.next()) {
            QMessageBox::information(this, "Successful login", "Welcome to the system!");
            this->close();
        } else {
            QMessageBox::warning(this, "Login failed", "Incorrect email or password.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Error executing request: " + query.lastError().text());
    }
}
