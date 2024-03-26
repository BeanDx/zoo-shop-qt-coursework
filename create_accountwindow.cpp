#include "create_accountwindow.h"
#include "ui_create_accountwindow.h"

#include "dbconnection.h"

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


void create_accountwindow::on_createAccountBtn_clicked()
{
    QString name = ui->createAccount_name->text();
    QString surname = ui->createAccount_surname->text();
    QString email = ui->createAccount_email->text();
    QString password = ui->createAccount_password->text();

    // Проверяем, существует ли уже пользователь с таким email
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM users WHERE email = :email");
    checkQuery.bindValue(":email", email);
    if(checkQuery.exec()) {
        if(checkQuery.next()) {
            // Пользователь с таким email уже существует
            QMessageBox::warning(this, "Registration error", "A user with this email already exists.");
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Error executing request: " + checkQuery.lastError().text());
        return;
    }

    // Если пользователя с таким email нет, то создаем нового пользователя
    QSqlQuery query;
    query.prepare("INSERT INTO users (name, surname, email, user_password) VALUES (:name, :surname, :email, :user_password)");
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":email", email);
    query.bindValue(":user_password", password);

    if(!query.exec()) {
        QMessageBox::critical(this, "Error!", "Error adding user: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Successful registration", "You have successfully registered.");
        this->close();
    }
}


