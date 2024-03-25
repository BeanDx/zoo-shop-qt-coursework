#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private slots:
    void on_create_account_btn_clicked();

    void on_login_cancel_clicked();

private:
    Ui::AuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H
