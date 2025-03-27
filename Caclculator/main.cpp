#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QResizeEvent>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
