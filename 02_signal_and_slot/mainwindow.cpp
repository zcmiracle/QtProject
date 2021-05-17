#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton *button = new QPushButton;
    button->setText("登录");
    button->setFixedSize(100, 30);
    button->setParent(this);
}

MainWindow::~MainWindow()
{
}

