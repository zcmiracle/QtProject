#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>u>

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
