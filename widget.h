#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qcustomplot.h"


class SendDataThread;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void init();

    void initForm();

    void initPlot();

    void initConnect();

    void loadPlot1();

    void loadPlot2();

    void loadPlot3();

    void loadText();

    void loadLedStatus();

protected:
    virtual void closeEvent ( QCloseEvent * event);

Q_SIGNALS:

private Q_SLOTS:
    void slotReData(const QByteArray &buf);

private:
    SendDataThread  *m_pThread;
    QList<QCustomPlot *>m_plots;

    double plot1_key;
    double plot1_value;

    double plot2_key;
    double plot2_value;

    double plot3_key;
    double plot3_value;

    bool m_ledFlag;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
