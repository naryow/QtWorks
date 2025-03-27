#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include "interfaceForEncryption.h"
#include "interfaceForDecryption.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void openEncryptWindow();
    void openDecryptWindow();
    void returnToMainWindow();


private:
    Ui::MainWindow *ui;
    interfaceForEncryption *encryptWindow;
    interfaceForDecryption *decryptWindow;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
};

#endif // MAINWINDOW_H
