#include "interfaceForEncryption.h"
#include "ui_interfaceForEncryption.h"
#include <QMessageBox>

interfaceForEncryption::interfaceForEncryption(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::interfaceForEncryption)
    , backend(std::make_unique<Backend>())
{
    ui->setupUi(this);

    this->setWindowTitle("Encipher");
    this->setWindowIcon(QIcon(":/new/prefix1/5765804.jpg"));

    connect(ui->return_init, &QPushButton::clicked, this, &interfaceForEncryption::showInitialWindow);

    ui->input_key->setPlaceholderText("Введите пароль для ключа.");
    ui->input_text->setPlaceholderText("Введите текст для зашифровки!");
    ui->hash_label->setText("Чтобы скопировать хэш, выделите его!");
    this->setMinimumSize(892,658);
    this->setMaximumSize(892,658);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);



    connect(ui->encrypt_button, &QPushButton::clicked, [this]() {
        QString message = ui->input_text->toPlainText();
        QString key = ui->input_key->text();

        if (message.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите текст для шифрования.");
            return;
        }

        if (key.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите ключ для шифрования.");
            return;
        }

        try {
            QString encrypted = backend->encrypt(message, key);
            ui->hash_label->setText("Зашифровано:\n" + encrypted);
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    });
}

interfaceForEncryption::~interfaceForEncryption()
{
    delete ui;
}
