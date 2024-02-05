#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    int val1 = ui->spinBox_TEST1->value();
    int val2 = ui->spinBox_TEST2->value();

    int addedValu = val1 * val2;

    ui->label_TEST->setText(QString::number(addedValu));


}

