#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , encryptWindow(nullptr)
    , decryptWindow(nullptr)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/new/prefix1/5765804.jpg"));
    this->setWindowTitle("Encryptify");

    videoWidget = new QVideoWidget(this);
    videoWidget->setStyleSheet("background-color: transparent;");

    videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(videoWidget);


    mediaPlayer->setSource(QUrl("qrc:/new/prefix1/7048458_Animation_Motion Graphic_3840x2160.mp4"));
    mediaPlayer->play();
    mediaPlayer->setLoops(QMediaPlayer::Infinite);



    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(videoWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    // Абсолютное позиционирование кнопок
    ui->encrptButton->setParent(videoWidget);  // Делаем videoWidget родителем кнопок
    ui->decryptButton->setParent(videoWidget);


    layout->addWidget(ui->encrptButton);
    layout->addWidget(ui->decryptButton);


    connect(ui->encrptButton, &QPushButton::clicked, this, &MainWindow::openEncryptWindow);
    connect(ui->decryptButton, &QPushButton::clicked, this, &MainWindow::openDecryptWindow);




    ui->encrptButton->setStyleSheet("background-color: rgba(255, 255, 255, 150); color: black;");
    ui->decryptButton->setStyleSheet("background-color: rgba(255, 255, 255, 150); color: black;");


    this->setMinimumSize(892, 658);
    this->setMaximumSize(892,658);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete videoWidget;
    delete mediaPlayer;
    delete encryptWindow;
    delete decryptWindow;
}

void MainWindow::openEncryptWindow()
{
    if (!encryptWindow) {
        encryptWindow = new interfaceForEncryption();
        connect(encryptWindow, &interfaceForEncryption::showInitialWindow, this, &MainWindow::returnToMainWindow);
    }

    encryptWindow->show();

}

void MainWindow::openDecryptWindow()
{
    if (!decryptWindow) {
        decryptWindow = new interfaceForDecryption();
        connect(decryptWindow, &interfaceForDecryption::showInitialWindow, this, &MainWindow::returnToMainWindow);
    }
    decryptWindow->show();

}

void MainWindow::returnToMainWindow()
{
    if (encryptWindow) {
        encryptWindow->hide();
    }
    if (decryptWindow) {
        decryptWindow->hide();
    }
    this->show();
    this->activateWindow();
}

