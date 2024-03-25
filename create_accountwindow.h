#ifndef CREATE_ACCOUNTWINDOW_H
#define CREATE_ACCOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class create_accountwindow;
}

class create_accountwindow : public QDialog
{
    Q_OBJECT

public:
    explicit create_accountwindow(QWidget *parent = nullptr);
    ~create_accountwindow();

private slots:
    void on_createAccount_cancel_btn_clicked();

    void on_createAccount_login_clicked();

private:
    Ui::create_accountwindow *ui;
};

#endif // CREATE_ACCOUNTWINDOW_H
