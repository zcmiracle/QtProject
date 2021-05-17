#include "mainwindow.h"
#include "receiver.h"
#include "sender.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建对象
    Sender *sender = new Sender;
    Receiver *receiver = new Receiver;

    // 连接 建立连接
    connect(sender, &Sender::exit, receiver, &Receiver::handleExit);

    // 发出信号
//    emit sender->exit();
   qDebug() << emit sender->exit(10, 20);

    // 销毁对象
    delete sender;
    delete receiver;

    /**

     信号与槽都可以有参数和返回值
        + 发信号时 参数会传递给槽
        + 槽的返回值 会返回到发信号的位置

     */

}

MainWindow::~MainWindow()
{
}

