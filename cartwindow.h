#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QDialog>

namespace Ui {
class CartWindow;
}

class CartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CartWindow(QWidget *parent = nullptr);
    ~CartWindow();

    void loadCartItems();

private slots:
    void on_Cart_cancel_btn_clicked();
    void updateDeleteButtonState();

private:
    Ui::CartWindow *ui;
};

#endif // CARTWINDOW_H
