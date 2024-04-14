#ifndef CREATEPRODUCT_H
#define CREATEPRODUCT_H

#include <QWidget>

namespace Ui {
class CreateProduct;
}

class CreateProduct : public QWidget
{
    Q_OBJECT

public:
    explicit CreateProduct(QWidget *parent = nullptr);
    ~CreateProduct();

private slots:
    void on_cancel_btn_clicked();

private:
    Ui::CreateProduct *ui;
};

#endif // CREATEPRODUCT_H
