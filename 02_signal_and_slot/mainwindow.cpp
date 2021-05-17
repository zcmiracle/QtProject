#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /**
       信号Signal 与 槽Slot
       信号（Signal）：比如点击按钮就会发出一个点击信号
       槽（Slot）：一般也叫做槽函数，是用来处理信号的函数

       一个信号可以被多个槽同时处理，可以定义空信号和空槽
       一个槽可以处理多个信号

       通过connect函数可以将【信号的发送者】【信号】【信号的接收者】【槽】 者四个连接在一起
    */

    QPushButton *button = new QPushButton;
    button->setText("关闭");
    button->setFixedSize(100, 30);
    button->setParent(this);

    // connect(信号的发送者，信号，信号的接收者，槽)；
    // 点击按钮，关闭当前窗口
//    connect(button, &QPushButton::clicked, this, &MainWindow::close);
    connect(button, &QAbstractButton::clicked, this, &MainWindow::close);

    // 通过disconnect断开连接 写了这句上面那句断开连接失效
//    disconnect(button, &QPushButton::clicked, this, &MainWindow::close);
//    disconnect(button, &QAbstractButton::clicked, this, &MainWindow::close);

    /**
        自定义信号与槽

        信号的发送者和接收者都必须 继承QObject,Qt的控件最终都是继承自QObject，
        比如QMainWindow QPushButton等

        信号的发送者

     */

}

MainWindow::~MainWindow()
{
}

