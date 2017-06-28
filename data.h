#ifndef DATA_H
#define DATA_H

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QColor>

class Data
{
public:
    Data();
    void readDat(QString);
    void writeDat(QColor c,bool warnFlag,int timeWarn,int timeRest,QString warnText);

    static QColor c;
    static bool warnFlag;
    static int timeWarn;
    static int timeRest;
    static QString warnText;
};

#endif // DATA_H
