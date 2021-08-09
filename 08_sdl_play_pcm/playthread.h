#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H
#include <QThread>

class PlayThread : public QThread {
public:
    PlayThread(QObject *parent = nullptr);
    ~PlayThread();

private:
    void run();

signals:

};

#endif // PLAYTHREAD_H
