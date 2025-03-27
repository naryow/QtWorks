#ifndef INTERFACEFORDECRYPTION_H
#define INTERFACEFORDECRYPTION_H

#include <QWidget>
#include <memory>
#include "backend.h"

namespace Ui {
class interfaceForDecryption;
}

class interfaceForDecryption : public QWidget
{
    Q_OBJECT

public:
    explicit interfaceForDecryption(QWidget *parent = nullptr);
    ~interfaceForDecryption();

signals:
    void showInitialWindow();

private:
    Ui::interfaceForDecryption *ui;
    std::unique_ptr<Backend> backend;
};

#endif // INTERFACEFORDECRYPTION_H
