#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QDialog>

namespace Ui {
class ProductItem;
}

class ProductItem : public QDialog
{
    Q_OBJECT

public:
    explicit ProductItem(QWidget *parent = nullptr);
    ProductItem(const QString &name, const QString &description, double price, QWidget *parent = nullptr);
    ~ProductItem();

    void setProductName(const QString &name);
    void setProductDescription(const QString &description);
    void setProductPrice(double price);

private slots:
    void on_product_cancel_btn_clicked();

private:
    Ui::ProductItem *ui;
};

#endif // PRODUCTITEM_H