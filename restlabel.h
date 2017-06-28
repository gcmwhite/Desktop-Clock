#ifndef RESTLABEL_H
#define RESTLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QTimer>

class RestLabel : public QLabel
{
    Q_OBJECT
public:
//    explicit RestLabel(QWidget *parent = 0);
    explicit RestLabel(const QString &text, QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());
    void mousePressEvent(QMouseEvent *);
public slots:
    void slotMove();
    void moveStart();
private:
    QTimer *timer;
};

#endif // RESTLABEL_H
