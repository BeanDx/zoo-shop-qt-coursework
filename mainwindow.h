#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadProducts(const QString &category = "");

private slots:
    void on_auth_btn_clicked();
    void showProductDetails(QListWidgetItem *item);
    void onSearchTextChanged(const QString &text);
    void on_cart_btn_clicked();
    void onCategoryChanged(const QString &category);  // Раскомментируйте или добавьте этот слот

public slots:
    void updateUserEmail(QString email);

private:
    Ui::MainWindow *ui;
    void loadCategories();
};
#endif // MAINWINDOW_H
