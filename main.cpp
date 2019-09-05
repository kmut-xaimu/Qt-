#include "mainwindow.h"
#include "basictransceiver.h"
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/images/paper-plane.png"));
    w.setWindowTitle(QStringLiteral("短学期"));
    w.show();

    return a.exec();
}
