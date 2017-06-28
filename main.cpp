#include <QApplication>
#include <QDesktopWidget>
#include "clockdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDesktopWidget *desktop = QApplication::desktop();
    ClockDialog clock;
    clock.move(desktop->width()*0.88,desktop->height()*0.02);
    clock.show();
    return a.exec();
}
