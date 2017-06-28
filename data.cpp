#include "data.h"
#include <QDebug>
#include <QDataStream>

#define INIT "init.dat"

QColor Data::c;
bool Data::warnFlag;
int Data::timeWarn;
int Data::timeRest;
QString Data::warnText;


Data::Data()
{
    QFileInfo fileInfo(INIT);
    if (fileInfo.isFile())
    {
        qDebug() << "数据文件存在";
        readDat(INIT);
    }
    else
    {
        qDebug() << "数据文件不存在";
        writeDat(QColor(Qt::black),true,45,10,"休息时间到了！！！");
        readDat(INIT);
    }
}

void Data::readDat(QString fileName)       //读取配置文件
{
    QFile data(fileName);
    if (data.open(QIODevice::ReadOnly))
    {
        QDataStream in(&data);
        in >> Data::c >> Data::warnFlag >> Data::timeWarn >> Data::timeRest >> Data::warnText;
        qDebug() << "读取配置内容：" << Data::c << Data::warnFlag << Data::timeWarn << Data::timeRest << Data::warnText;
    }
    data.close();
}

void Data::writeDat(QColor c,bool warnFlag,int timeWarn,int timeRest,QString warnText)
{
    QFile data(INIT);
    QDataStream out(&data);
    if (data.open(QFile::WriteOnly | QIODevice::Truncate))
    {
        out <<  c << warnFlag << timeWarn << timeRest << warnText;
    }
    data.flush();
    data.close();
    qDebug() << "数据文件写入成功！";
}
