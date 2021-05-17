#include "mainwindow.h"

#include "receiver.h"
#include "sender.h"

#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton *button = new QPushButton;
    button->setText("发送信号");
    button->setFixedSize(100, 40);
    button->setParent(this);
    // button 本身就是一个信号，点击发送也是一个信号，点击时候信号连接
    connect(button, &QPushButton::clicked, this, &MainWindow::handleClick);

    // 创建对象
    Sender *sender = new Sender;
    Receiver *receiver = new Receiver;

//    connect(button, &QPushButton::clicked, sender, &Sender::exit);
//    connect(button, &QPushButton::clicked, []() {
//        qDebug() << "发送信号按钮点击了";
//    });


    // 连接 建立连接
//    connect(sender, &Sender::exit, receiver, &Receiver::handleExit);
//    connect(sender, &Sender::exit1, receiver, &Receiver::handleExit1);
//    // 连接2个信号
//    connect(sender, &Sender::exit, sender, &Sender::exit1);

    // 发出信号
//    emit sender->exit();
//    qDebug() << emit sender->exit(10, 20);
//    emit sender->exit1();



    // [] 里面是捕获列表 Lambda表达式
//    connect(sender, &Sender::exit, [](int value1, int value2) {
//        qDebug() << "Lambda表达式" << value1 << value2;
//    });
    // 发送信号
    emit sender->exit(100, 200);

    // 销毁对象
    delete sender;
    delete receiver;

    /**

     信号与槽都可以有参数和返回值
        + 发信号时 参数会传递给槽
        + 槽的返回值 会返回到发信号的位置


     处理按钮点击可以使用 【Lambda的形式】 也可以使用 【自定义槽函数的形式】

     */

}

// 在mainwindow.h 中先声明了槽函数，这里实现
void MainWindow::handleClick() {
    qDebug() << "按钮点击了 - handleClick";
}

MainWindow::~MainWindow()
{
}

