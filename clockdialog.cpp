#include "clockdialog.h"
#include <QTime>
#include <QDebug>
#include <QCursor>
#include <QPalette>
#include <QMessageBox>

ClockDialog::ClockDialog(QWidget *parent)
    :QLCDNumber(parent)
{
    //初始化d数据对象
    dat = new Data;
    //提示语
    restLabel = new RestLabel(Data::warnText);
    this->connect(this,SIGNAL(closeSignal()),restLabel,SLOT(close()));
    //智能提醒倒计时
    timer_warn = new QTimer(this);
    this->connect(timer_warn,SIGNAL(timeout()),this,SLOT(slotWarn()));
    //休息倒计时
    timer_rest = new QTimer(this);
    this->connect(timer_rest,SIGNAL(timeout()),this,SLOT(slotRest()));
    //数据初始化
    initial();

    //重设大小
    this->resize(150,60);
    //去除标题栏|任务栏|置顶窗口
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //去除边框
    this->setFrameShape(QFrame::NoFrame);



    //时间刷新
    QTimer *timer = new QTimer(this);
    this->connect(timer,SIGNAL(timeout()),this,SLOT(slotShowTime()));
    showFlag = true;
    timer->start(1000);
    slotShowTime();

    //创建菜单
    menu = new QMenu(this);
    menu->addAction(tr("重置倒计时"),this,SLOT(slotReSetTimer()));
    menu->addAction(tr("关闭提醒"),restLabel,SLOT(close()));
    menu->addAction(tr("设置"),this,SLOT(slotSet()));
    menu->addAction(tr("退出"),this,SLOT(close()));


}

ClockDialog::~ClockDialog()
{
    delete dat;
    delete restLabel;
}

void ClockDialog::slotShowTime()
{
    //取得当前时间并格式化
    QTime time = QTime::currentTime();
    QString timeStr = time.toString("hh:mm");
    if (showFlag)
    {
        timeStr[2] = ':';
        showFlag = false;
    }
    else
    {
        timeStr[2] = ' ';
        showFlag = true;
    }
    this->display(timeStr);
}

void ClockDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton)
    {
        menu->exec(QCursor::pos());
    }
}

void ClockDialog::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-dragPosition);
    event->accept();
}

void ClockDialog::slotWarn()
{
    timer_warn->stop();
    restLabel->show();
    restLabel->moveStart();
    timer_rest->start();
    qDebug() << "休息倒计时开始！";
}

void ClockDialog::slotRest()
{
    timer_rest->stop();
    restLabel->close();
    timer_warn->start();
    qDebug() << "开始休息！";
}

void ClockDialog::slotSet()
{
    SettingDialog *set = new SettingDialog;
    this->connect(set,SIGNAL(ColorSet(QColor)),this,SLOT(slotColorSet(QColor)));
    this->connect(set,SIGNAL(setChanged()),this,SLOT(initial()));
    set->show();
}

void ClockDialog::slotColorSet(QColor c)
{
    QPalette p = palette();
    p.setColor(QPalette::WindowText,c);
    this->setPalette(p);
}

void ClockDialog::initial()
{
    qDebug() << "初始化数据：" << Data::c << Data::warnFlag << Data::timeWarn << Data::timeRest << Data::warnText;
    restFlag = Data::warnFlag;
    slotColorSet(Data::c);
    timer_warn->setInterval(Data::timeWarn*60*1000);
    timer_rest->setInterval(Data::timeRest*60*1000);
    restLabel->setText(Data::warnText);

    timer_warn->stop();
    qDebug() << "程序运行" << timer_rest->isActive();
    if (timer_rest->isActive())
    {
        timer_rest->stop();
        restLabel->close();
    }
    if (restFlag)
    {
        timer_warn->start();
    }
}

void ClockDialog::slotReSetTimer()
{
    if (restFlag)
    {
        if (timer_rest->isActive())
        {
            timer_rest->stop();
            restLabel->close();
        }
        timer_warn->stop();
        timer_warn->start();
        QMessageBox::warning(NULL,tr("注意："),tr("重置成功！"));
    }
    else
    {
        QMessageBox::warning(NULL,tr("注意："),tr("您还没有开启智能提醒功能哦！"));
    }
}

void ClockDialog::closeEvent(QCloseEvent *)
{
    emit closeSignal();
}
