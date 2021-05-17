#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // 窗口标题设置
    setWindowTitle("主窗口");

    // 设置窗口大小
    resize(500, 500);

    // 设置窗口的固定大小
//    setFixedSize(600, 600);

    // 设置窗口的位置
    move(200, 200);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

