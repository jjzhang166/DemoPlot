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

    while (!m_isStopped)
    {
        msleep(10);
    }
}

void SendDataThread::setThreadStop()
{
     m_isStopped = true;
}
