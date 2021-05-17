#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);

   // 自定义槽函数 声明
public slots:
    // 没有返回值
//    void handleExit();
    // 有返回值
    int handleExit(int value1, int value2);

    void handleExit1(int value1, int value2);
};
#endif // RECEIVER_H
