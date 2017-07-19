#ifndef TETHREAD_H
#define TETHREAD_H

#include <QThread>
#include <arkanoidGlobalDefines.h>

class TeThread : public QThread
{
    Q_OBJECT
public:
    explicit TeThread(int delay_ms, QObject *parent = nullptr);
signals:
    void timeOut();
protected:
    void run() override;
private:
    int m_delay_ms;
};

#endif // TETHREAD_H
