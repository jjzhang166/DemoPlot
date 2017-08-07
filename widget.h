#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

Q_SIGNALS:

private Q_SLOTS:

private:
    SendDataThread  *m_pThread;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
