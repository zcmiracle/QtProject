#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>u>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 通过 ui-> 访问文件中的2个按钮
    // 系统转为槽 自动生成的
    ui->pushButton->setFixedSize(100, 50);
    // 自己修改名字生成的button
    ui->registerButton->setFixedSize(100, 30);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 点击ui中的按钮，右键选择【转为槽】，自动生成此函数
void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked()";
}

// 事件的名字
void MainWindow::on_registerButton_clicked()
{
    qDebug() << "on_registerButton_clicked()";
}
