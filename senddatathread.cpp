#include "senddatathread.h"

#include <QDebug>

SendDataThread::SendDataThread(QObject *parent):
    QThread(parent)
{
    init();
}

SendDataThread::~SendDataThread()
{
    qDebug()<<"destroy SendDataThread!";
}

void SendDataThread::init()
{
    m_isStopped = false;
}

void SendDataThread::run()
{
    qDebug()<<"SendDataThread id:"<<QThread::currentThreadId();

    while (1)
    {
        QMutexLocker locker(&mutex);
        if (m_isStopped)
            break;

        QByteArray buff;
        buff.append ("hello");

        emit signalSendData (buff);

        msleep(400);
    }
    m_isStopped = false;
}

void SendDataThread::setThreadStop()
{
    QMutexLocker locker(&mutex);

    m_isStopped = true;
}
