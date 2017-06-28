#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QColor>
#include <QString>
#include "data.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
    QString getLineEdit_restText();
    void initialSet();

private:
    Ui::SettingDialog *ui;
    Data *datSet;
    QColor foregroundColor = QColor(Qt::black);
signals:
    void ColorSet(QColor);
    void setChanged();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // SETTINGDIALOG_H
