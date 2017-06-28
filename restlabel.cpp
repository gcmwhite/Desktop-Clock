#include "restlabel.h"
#include <QFont>
#include <QTime>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

/*
RestLabel::RestLabel(QWidget *parent)
    :QLabel(parent)
{

}
*/
RestLabel::RestLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text,parent,f)
{
    QFont font("宋体",25);
    this->setFont(font);
    //去除标题栏|任务栏|置顶窗口
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::X11BypassWindowManagerHint|Qt::WindowStaysOnTopHint);
    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //去除边框
    this->setFrameShape(QFrame::NoFrame);

    timer = new QTimer(this);
    this->connect(timer,SIGNAL(timeout()),this,SLOT(slotMove()));
    QTime time = QTime::currentTime();  //获得当前时间
    qsrand(time.msec()+time.second()*10000);    //用时间初始化随机数种子
//    timer->start(1000);
}

void RestLabel::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        this->close();
    }
    e->accept();
}

void RestLabel::slotMove()
{
    int wRand = qrand()%101;   //初始化随机数
    int hRand = qrand()%101;
//    qDebug() << "随机数" << wRand << " " << hRand;
    QDesktopWidget *desktop = QApplication::desktop();
    float w = float(wRand) / 100.0;
    float h = float(hRand) / 100.0;
//    qDebug() << w << " " << h;
    this->move(desktop->width()*w,desktop->height()*h);
}

void RestLabel::moveStart()
{
    timer->start(1000);
}
