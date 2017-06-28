#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "data.h"
#include <QColorDialog>
#include <QDebug>


SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    datSet = new Data;
    ui->setupUi(this);
    ui->pushButton->setPalette(Data::c);
    ui->checkBox->setChecked(Data::warnFlag);
    ui->lineEdit->setPlaceholderText(QString::number(Data::timeWarn));
    ui->lineEdit_2->setPlaceholderText(QString::number(Data::timeRest));
    ui->lineEdit_3->setPlaceholderText(Data::warnText);
}

SettingDialog::~SettingDialog()
{
    delete ui;
    delete datSet;
}

void SettingDialog::on_pushButton_clicked()
{
    QColor c = QColorDialog::getColor();
    ui->pushButton->setPalette(c);
    if (c != foregroundColor)
    {
        emit ColorSet(c);
        foregroundColor = c;
    }
}

QString SettingDialog::getLineEdit_restText()
{
    return QString(ui->lineEdit_3->text());
}


void SettingDialog::on_pushButton_2_clicked()
{

    Data::c = foregroundColor;
    Data::warnFlag = bool(ui->checkBox->checkState());
    if (!ui->lineEdit->text().isEmpty())
    {
        Data::timeWarn = ui->lineEdit->text().toInt();
    }
    if (!ui->lineEdit_2->text().isEmpty())
    {
        Data::timeRest = ui->lineEdit_2->text().toInt();
    }
    if (!ui->lineEdit_3->text().isEmpty())
    {
        Data::warnText = ui->lineEdit_3->text();
    }

    qDebug() << "读取设置内容：" << Data::c << Data::warnFlag << Data::timeWarn << Data::timeRest << Data::warnText;

    datSet->writeDat(Data::c,Data::warnFlag,Data::timeWarn,Data::timeRest,Data::warnText);

    qDebug() << "保存配置成功!";

    emit setChanged();
}



