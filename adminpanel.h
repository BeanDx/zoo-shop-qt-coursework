#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QDialog>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();

signals:
    void adminPanelClosed();

private slots:
    void on_cancel_btn_clicked();

    void loadProducts();
    void onDeleteItemClicked();

    void on_createItemAdminPanel_clicked();

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_H
