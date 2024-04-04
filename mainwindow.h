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

private slots:
    void on_auth_btn_clicked();
    void showProductDetails(QListWidgetItem *item);
    void onSearchTextChanged(const QString &text);

public slots:
    void updateUserEmail(QString email);


private:
    Ui::MainWindow *ui;
    void loadProducts();
};
#endif // MAINWINDOW_H
