#include "widget.h"
#include "ui_widget.h"

#include "senddatathread.h"


#include <QDebug>
#include <QThread>
#include <QCloseEvent>

#define PLOT_COUNT  16

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

    this->setWindowTitle ("devstone(kevinlq0912@163.com)http://kevinlq.com/");

    ui->label_led1->clear ();
    ui->label_led2->clear ();
    ui->label_led3->clear ();
    ui->label_value1->clear ();
    ui->label_value2->clear ();
    ui->label_value3->clear ();
    ui->label_value4->clear ();
    ui->label_value5->clear ();
    ui->label_value6->clear ();
    ui->label_value7->clear ();
    ui->label_value8->clear ();
    ui->label_value9->clear ();

    m_ledFlag = false;


    m_pThread = new SendDataThread;

    connect(qApp,SIGNAL(aboutToQuit()),
            m_pThread,SLOT(setThreadStop()));
    connect(m_pThread,SIGNAL(finished()),
            m_pThread,SLOT(deleteLater()));

    connect (m_pThread,SIGNAL(signalSendData(QByteArray)),
             this,SLOT(slotReData(QByteArray)));

    m_pThread->start();

}

void Widget::initPlot()
{
    m_plots.append (ui->plot1);
    m_plots.append (ui->plot2);
    m_plots.append (ui->plot3);

    m_plots.at (0)->yAxis->setLabel ("温度值(单位:°)");
    m_plots.at (1)->yAxis->setLabel ("湿度值(单位:%)");
    m_plots.at (2)->yAxis->setLabel ("力度值(单位:N)");

    //设置坐标轴范围
    m_plots.at (0)->yAxis->setRange (0,100);
    m_plots.at (1)->yAxis->setRange (0,100);
    m_plots.at (2)->yAxis->setRange (0,100);

    foreach (QCustomPlot *plot, m_plots) {
        plot->axisRect ()->insetLayout ()->setInsetAlignment (0,Qt::AlignTop |
                                                              Qt::AlignTop);
        plot->legend->setBrush (QColor(255,255,255,200));
        plot->replot ();
    }

    m_plots.at (0)->addGraph ();
    m_plots.at (0)->graph (0)->setName ("温度值(单位:°)");
    m_plots.at (0)->xAxis->setRange (0,PLOT_COUNT,Qt::AlignLeft);

    m_plots.at (1)->addGraph ();
    m_plots.at (1)->graph (0)->setName ("湿度值(单位:%)");
    m_plots.at (1)->xAxis->setRange (0,PLOT_COUNT,Qt::AlignLeft);

    m_plots.at (2)->addGraph ();
    m_plots.at (2)->graph (0)->setName ("力度值(单位:N)");
    m_plots.at (2)->xAxis->setRange (0,PLOT_COUNT,Qt::AlignLeft);
}

void Widget::initConnect()
{
}

void Widget::loadPlot1()
{
    plot1_key = QDateTime::currentDateTime ().toMSecsSinceEpoch ()/1000.0;
    plot1_value = qrand() %100;

    m_plots.at (0)->graph (0)->addData (plot1_key,plot1_value);
    m_plots.at (0)->graph (0)->removeDataBefore (plot1_key - PLOT_COUNT - 1);
    m_plots.at (0)->xAxis->setRange (plot1_key,PLOT_COUNT,Qt::AlignRight);

    m_plots.at (0)->replot ();
}

void Widget::loadPlot2()
{
    plot2_key = QDateTime::currentDateTime ().toMSecsSinceEpoch ()/1000.0 + 10.0;
    plot2_value = qrand() %100;

    m_plots.at (1)->graph (0)->addData (plot2_key,plot2_value);
    m_plots.at (1)->graph (0)->removeDataBefore (plot2_key - PLOT_COUNT - 1);
    m_plots.at (1)->xAxis->setRange (plot2_key,PLOT_COUNT,Qt::AlignRight);

    m_plots.at (1)->replot ();
}

void Widget::loadPlot3()
{
    plot3_key = QDateTime::currentDateTime ().toMSecsSinceEpoch ()/1000.0 + 20.0;
    plot3_value = qrand() %100;

    m_plots.at (2)->graph (0)->addData (plot3_key,plot3_value);
    m_plots.at (2)->graph (0)->removeDataBefore (plot3_key - PLOT_COUNT - 1);
    m_plots.at (2)->xAxis->setRange (plot3_key,PLOT_COUNT,Qt::AlignRight);

    m_plots.at (2)->replot ();
}

void Widget::loadText()
{
    int temperature = qrand () % 40;
    ui->label_value1->setText (QString("温度 :%1 °").arg (temperature));
    ui->label_value2->setText (QString("温度 :%1 °").arg (temperature + 3));
    ui->label_value3->setText (QString("温度 :%1 °").arg (temperature)+ 5);

    int humidity = qrand () % 60;
    ui->label_value4->setText (QString("湿度 :%1 °").arg (humidity));
    ui->label_value5->setText (QString("湿度 :%1 °").arg (humidity + 3));
    ui->label_value6->setText (QString("湿度 :%1 °").arg (humidity)+ 5);

    int power = qrand () % 100;
    ui->label_value7->setText (QString("力度 :%1 °").arg (power));
    ui->label_value8->setText (QString("力度 :%1 °").arg (power + 3));
    ui->label_value9->setText (QString("力度 :%1 °").arg (power)+ 5);
}

void Widget::loadLedStatus()
{
    if (m_ledFlag){
        ui->label_led1->setPixmap (QPixmap(":/images/led/light_on.png"));
        ui->label_led2->setPixmap (QPixmap(":/images/led/light_off.png"));
    }else{
        ui->label_led1->setPixmap (QPixmap(":/images/led/light_off.png"));
        ui->label_led2->setPixmap (QPixmap(":/images/led/light_on.png"));
    }

    int value = qrand() %10;
    ui->label_led3->setPixmap (QPixmap(QString(":/images/number/%1.png").arg (value)));

    m_ledFlag = !m_ledFlag;
}

void Widget::closeEvent(QCloseEvent *event)
{
    m_pThread->setThreadStop ();

    event->accept ();
}

void Widget::slotReData(const QByteArray &buf)
{
    qDebug()<<buf;

    loadPlot1 ();

    loadPlot2 ();

    loadPlot3 ();

    loadText ();

    loadLedStatus ();
}
