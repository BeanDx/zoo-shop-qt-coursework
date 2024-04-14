#ifndef CREATEPRODUCT_H
#define CREATEPRODUCT_H

#include <QDialog>

namespace Ui {
class CreateProduct;
}

class CreateProduct : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProduct(QWidget *parent = nullptr);
    ~CreateProduct();

// signals:
//     void productAdded();

private slots:
    void on_cancel_btn_clicked();

    void on_createProductBtn_clicked();

private:
    Ui::CreateProduct *ui;
    QString imagePath;
};



#endif // CREATEPRODUCT_H
