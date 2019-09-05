#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    cnt = 0;
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(discoveryAgent,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
            );
    connect(ui->list,
            SIGNAL(itemActivated(QListWidgetItem*)),
            this,
            SLOT(itemActivated(QListWidgetItem*))
            );
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(readBluetoothDataEvent())
            );
    connect(socket,
            SIGNAL(connected()),
            this,
            SLOT(bluetoothConnectedEvent())
            );
    connect(socket,
            SIGNAL(disconnected()),
            this,
            SLOT(bluetoothDisconnectedEvent())
            );

    if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff ) {
        ui->commandLinkButton_6->setEnabled(true);
        ui->commandLinkButton_5->setEnabled(false);
    }else {
        ui->commandLinkButton_6->setEnabled(false);
        ui->commandLinkButton_5->setEnabled(true);
    }

    if( localDevice->hostMode() == QBluetoothLocalDevice::HostDiscoverable ) {
        ui->checkBox_discoverable->setChecked(true);
    }else {
        ui->checkBox_discoverable->setChecked(false);
    }
}

Widget::~Widget()
{
    delete ui;
}



void Widget::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);

    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::black));
        else
            item->setTextColor(QColor(Qt::red));
        item->setSizeHint(QSize(10,20));
        cnt++;
        if(cnt%2)
        {
            item->setBackgroundColor(QColor(204,204,204));
        }else {
            item->setBackgroundColor(QColor(133,242,242));
            }
        ui->list->addItem(item);
    }

}

void Widget::itemActivated(QListWidgetItem *item)
{
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));
    qDebug() << "You has choice the bluetooth address is " << address;
    qDebug() << "The device is connneting.... ";
    QMessageBox::information(this,tr("Info"),tr("The device is connecting..."));
    socket->connectToService(address, QBluetoothUuid(serviceUuid) ,QIODevice::ReadWrite);

}


void Widget::readBluetoothDataEvent()
{

    QByteArray line = socket->readAll();
    QString strData = line.toHex();
    comStr.append(strData);
    qDebug() <<"rec data is: "<< comStr;
    qDebug() <<"The comStr length is: " << comStr.length();
    if(comStr.length() >= 30) {

        ui->textEdit_info->append(comStr + "\n");
        comStr.clear();
    }
}

void Widget::bluetoothConnectedEvent()
{
    qDebug() << "The android device has been connected successfully!";
    QMessageBox::information(this,tr("Info"),tr("successful connection!"));
}

void Widget::bluetoothDisconnectedEvent()
{
    qDebug() << "The android device has been disconnected successfully!";
    QMessageBox::information(this,tr("Info"),tr("successful disconnection!"));
}


void Widget::on_commandLinkButton_clicked()
{
     ui->textEdit_info->clear();
}

void Widget::on_commandLinkButton_2_clicked()
{
    QByteArray arrayData;
    QString s(ui->textEdit_info->toPlainText().trimmed());
    arrayData = s.toUtf8();
    socket->write(arrayData);
}

void Widget::on_commandLinkButton_3_clicked()
{
    socket->disconnectFromService();
}

void Widget::on_commandLinkButton_4_clicked()
{
    discoveryAgent->start();
    ui->commandLinkButton_4->setEnabled(false);
}

void Widget::on_commandLinkButton_5_clicked()
{
    localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    ui->commandLinkButton_5->setEnabled(false);
    ui->commandLinkButton_6->setEnabled(true);
    ui->commandLinkButton_4->setEnabled(false);
}

void Widget::on_commandLinkButton_6_clicked()
{
    localDevice->powerOn();
    ui->commandLinkButton_5->setEnabled(true);
    ui->commandLinkButton_6->setEnabled(false);
    ui->commandLinkButton_4->setEnabled(true);
}
