#include "tethread.h"

TeThread::TeThread(int delay_ms, QObject *parent):
    QThread(parent), m_delay_ms(delay_ms)
{}

void TeThread::run()
{
    while(true)
    {
        msleep(TIMER_DELAY);
        emit timeOut();
    }
}
