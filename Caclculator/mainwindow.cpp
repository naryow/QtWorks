#include "mainwindow.h"
#include "./ui_mainwindow.h"


double num_first;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Калькулятор");

    setWindowIcon(QIcon(":/icons_of_clctr/calcuulator.png"));

    // Устанавливаем фиксированный размер окна
    setFixedSize(241, 379); // Размер, подходящий для калькулятора

    // Убираем кнопку "Максимизировать", оставляя только "Свернуть" и "Закрыть"
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    // Подключаем кнопки к слоту digit_numbers
    connect(ui->pushButton_0, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_1, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_2, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_3, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_4, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_5, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_6, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_7, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_8, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_9, &QPushButton::released, this, &MainWindow::digit_numbers);
    connect(ui->pushButton_pm, &QPushButton::released, this, &MainWindow::operations);
    connect(ui->pushButton_percectage, &QPushButton::released, this, &MainWindow::operations);
    connect(ui->pushButton_divide, &QPushButton::released, this, &MainWindow::math_operations);
    connect(ui->pushButton_minus, &QPushButton::released, this, &MainWindow::math_operations);
    connect(ui->pushButton_plus, &QPushButton::released, this, &MainWindow::math_operations);
    connect(ui->pushButton_multiplication, &QPushButton::released, this, &MainWindow::math_operations);

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::digit_numbers() {
    QPushButton * button = (QPushButton*)sender();

    double all_numbers;
    QString new_label;

    if(ui->label->text().contains(".") && button->text() == "0"){
        new_label = ui->label->text() + button->text();
    }else{

    all_numbers = (ui->label->text() +  button->text()).toDouble();
    new_label = QString::number(all_numbers,'g',15);
    }
    ui->label->setText(new_label);
}



void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->label->text().contains('.')))
        ui->label->setText(ui->label->text() + ".");
}



void MainWindow::operations() {
    QPushButton * button = (QPushButton*)sender();
    double all_numbers;
    QString new_label;

    if(button->text() == "+/-"){
    all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * -1;
    new_label = QString::number(all_numbers,'g',15);

    ui->label->setText(new_label);
    }else  if(button->text() == "%"){
        all_numbers = (ui->label->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers,'g',15);

        ui->label->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton* button = (QPushButton*)sender();

    num_first = ui->label->text().toDouble();
    ui->label->setText("");

    button->setChecked(true);
}


void MainWindow::on_pushButton_AC_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiplication->setChecked(false);

    ui->label->setText("0");
}


void MainWindow::on_pushButton_equal_clicked()
{

    double labelNumber, numSecond;
    QString newLabel;

    numSecond = ui->label->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNumber = num_first + numSecond;
        newLabel = QString::number(labelNumber,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    } else if(ui->pushButton_minus->isChecked()){
        labelNumber = num_first - numSecond;
        newLabel = QString::number(labelNumber,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }else if(ui->pushButton_divide->isChecked()){
        if(numSecond == 0){
            ui->label->setText("NONE");
        }else{
        labelNumber = num_first / numSecond;
        newLabel = QString::number(labelNumber,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
        }
    }else if(ui->pushButton_multiplication->isChecked()){
        labelNumber = num_first * numSecond;
        newLabel = QString::number(labelNumber,'g',15);

        ui->label->setText(newLabel);
        ui->pushButton_plus->setChecked(false);
    }
}

