#include "receiver.h"
#include <QDebug>

Receiver::Receiver(QObject *parent) : QObject(parent)
{

}

int Receiver::handleExit(int value1, int value2) {
    qDebug() << "Receiver::handleExit()" << "value1 = " << value1 << ", value2 = " << value2;
    return value1 + value2;
};

void Receiver::handleExit1(int value1, int value2) {
    qDebug() << "Receiver::handleExit1()" << "value1 = " << value1 << ", value2 = " << value2;
}
