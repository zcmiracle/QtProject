#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    // QObject 专属于qt,不属于c++
    Q_OBJECT
public:
    explicit Sender(QObject *parent = nullptr);

signals:
    // 自定义信号，只写函数声明。不需要写函数实现
    // 没有返回值
//    void exit();
    // 有返回值
    int exit(int value1, int value2);

    int exit1(int value1, int value2);
};

#endif // SENDER_H
