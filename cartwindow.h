#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QWidget>

namespace Ui {
class CartWindow;
}

class CartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CartWindow(QWidget *parent = nullptr);
    ~CartWindow();

private slots:
    void on_Cart_cancel_btn_clicked();
    void updateDeleteButtonState();

private:
    Ui::CartWindow *ui;
};

#endif // CARTWINDOW_H
