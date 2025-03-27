#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_dot_clicked();

    void on_pushButton_AC_clicked();

    void on_pushButton_equal_clicked();



private:
    Ui::MainWindow *ui;

private:
    void digit_numbers();
    void operations();
    void math_operations();
};
#endif // MAINWINDOW_H
