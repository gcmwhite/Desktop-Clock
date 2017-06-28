#ifndef CLOCKDIALOG_H
#define CLOCKDIALOG_H

#include <QLCDNumber>
#include <QMouseEvent>
#include <QPoint>
#include <QMenu>
#include <QTimer>
#include <QLabel>
#include <QColor>
#include <QCloseEvent>
#include "settingdialog.h"
#include "restlabel.h"
#include "data.h"


class ClockDialog : public QLCDNumber
{
    Q_OBJECT
public:
    ClockDialog(QWidget *parent=0);
    ~ClockDialog();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);

private:
    bool showFlag,restFlag;
    QPoint dragPosition;
    QMenu *menu;
    QTimer *timer_warn;
    QTimer *timer_rest;
    RestLabel *restLabel;
    Data *dat;
public slots:
    void slotShowTime();
    void slotWarn();
    void slotRest();
    void slotSet();
    void slotColorSet(QColor);
    void initial();
    void slotReSetTimer();
signals:
    void closeSignal();
};

#endif // CLOCKDIALOG_H
