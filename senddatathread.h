#ifndef SENDDATATHREAD_H
#define SENDDATATHREAD_H

#include <QThread>
#include <QMutex>

class SendDataThread : public QThread
{
    Q_OBJECT
public:
    SendDataThread(QObject *parent = 0);
    ~SendDataThread();

private:
    void init();

protected:
    virtual void run();

Q_SIGNALS:
    void signalSendData(const QByteArray &buff);

public Q_SLOTS:
    void setThreadStop();

private:
    volatile bool m_isStopped;
    QMutex mutex;
};

#endif // SENDDATATHREAD_H
