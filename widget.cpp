#include "widget.h"
#include "ui_widget.h"

#include "senddatathread.h"


#include <QDebug>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    qDebug()<<"widget id:"<<QThread::currentThreadId();

    initForm();

    initPlot();

    initConnect();
}

void Widget::initForm()
{
    this->showMaximized();

    m_pThread = new SendDataThread;

    connect(qApp,SIGNAL(aboutToQuit()),
            m_pThread,SLOT(setThreadStop()));
    connect(m_pThread,SIGNAL(finished()),
            m_pThread,SLOT(deleteLater()));

    m_pThread->start();
}

void Widget::initPlot()
{
    //
}

void Widget::initConnect()
{
    //
}
