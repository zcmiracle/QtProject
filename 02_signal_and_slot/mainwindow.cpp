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

     */

    QPushButton *button = new QPushButton;
    button->setText("登录");
    button->setFixedSize(100, 30);
    button->setParent(this);
}

MainWindow::~MainWindow()
{
}

