#include "interfaceForDecryption.h"
#include "ui_interfaceForDecryption.h"
#include <QMessageBox>

interfaceForDecryption::interfaceForDecryption(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::interfaceForDecryption)
    , backend(std::make_unique<Backend>())
{
    ui->setupUi(this);

    this->setWindowTitle("Decipher");
    this->setWindowIcon(QIcon(":/new/prefix1/5765804.jpg"));

    connect(ui->sendBackToinit, &QPushButton::clicked, this, &interfaceForDecryption::showInitialWindow);

    ui->enterHash->setPlaceholderText("Введите хэш");
    ui->hashToText->setPlaceholderText("Ваш текст");
    ui->keyForDecryption->setPlaceholderText("Введите ваш ключ");
    this->setMinimumSize(892,658);
    this->setMaximumSize(892,658);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);


    connect(ui->decrypt_button, &QPushButton::clicked, [this]() {
        QString encryptedMessage = ui->enterHash->toPlainText();
        QString key = ui->keyForDecryption->text();

        if (encryptedMessage.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите зашифрованное сообщение.");
            return;
        }

        if (key.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите ключ для расшифровки.");
            return;
        }

        try {
            QString decrypted = backend->decrypt(encryptedMessage, key);
            ui->hashToText->setText("Decrypted: " + decrypted);
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    });
}

interfaceForDecryption::~interfaceForDecryption()
{
    delete ui;
}
