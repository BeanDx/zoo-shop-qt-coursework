#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QWidget>

namespace Ui {
class ProductItem;
}

class ProductItem : public QWidget
{
    Q_OBJECT

public:
    explicit ProductItem(QWidget *parent = nullptr);
    ~ProductItem();

private:
    Ui::ProductItem *ui;
};

#endif // PRODUCTITEM_H
