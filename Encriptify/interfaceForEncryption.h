#ifndef INTERFACEFORENCRYPTION_H
#define INTERFACEFORENCRYPTION_H

#include <QWidget>
#include <memory>
#include "backend.h"

namespace Ui {
class interfaceForEncryption;
}

class interfaceForEncryption : public QWidget
{
    Q_OBJECT

public:
    explicit interfaceForEncryption(QWidget *parent = nullptr);
    ~interfaceForEncryption();

signals:
    void showInitialWindow();

private:
    Ui::interfaceForEncryption *ui;
    std::unique_ptr<Backend> backend;
};

#endif // INTERFACEFORENCRYPTION_H
