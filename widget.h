#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QMainWindow>
#define MAX_LENGTH 256

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:


    void addBlueToothDevicesToList(const QBluetoothDeviceInfo&);
    void itemActivated(QListWidgetItem *item);
    void readBluetoothDataEvent();
    void bluetoothConnectedEvent();
    void bluetoothDisconnectedEvent();

    void on_commandLinkButton_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_commandLinkButton_5_clicked();

    void on_commandLinkButton_6_clicked();

private:

    Ui::Widget *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
    unsigned char comBuffer[15];
    unsigned int  comCount;
    QString comStr;
    int cnt;

};

#endif // WIDGET_H
